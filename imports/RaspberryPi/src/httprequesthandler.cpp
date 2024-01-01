#include "httprequesthandler.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include "qapplicationstatic.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include <QJsonArray>
#include <QVariantList>
#include <QList>
#include <QVariant>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include "stationcity.h"
#include <exception>

HttpRequestHandler::HttpRequestHandler(QObject *parent)
    : QObject{parent}
{
    m_networkAccessManager = new QNetworkAccessManager(qApp);
    static_cast<void>(connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, &HttpRequestHandler::requestReply));
}

void HttpRequestHandler::get(){
    m_networkAccessManager->get(QNetworkRequest(QUrl("http://192.168.1.62:10000/api/air/v1/stations")));
}

inline void swap(QJsonValueRef v1, QJsonValueRef v2)
{
    QJsonValue temp(v1);
    v1 = QJsonValue(v2);
    v2 = temp;
}

inline QStringList distinctList(QJsonArray result, const QString& toExtract){

    QStringList buffer;
    for(auto it = result.begin(); it != result.end(); it++){
        buffer.append(it->toObject().value(toExtract).toString());
    }
    std::sort(buffer.begin(), buffer.end());
    buffer.erase(std::unique(buffer.begin(), buffer.end()), buffer.end());
    return buffer;
}

inline void addToArray(QJsonArray* origins, QJsonArray* destination){
    for(auto it = origins->begin(); it != origins->end(); it++){
        auto row = it->toObject();
        StationCity sc( row["iataStationCode"].toString(),
                       row["name"].toString(),
                       row["cityName"].toString(),
                       row["category"].toString(),
                       row["iso2CountryCode"].toString(),
                       row["regionCode"].toString());
        destination->append(sc.toJson());
    }


}


void HttpRequestHandler::requestNetworkError(QNetworkReply::NetworkError* error){

}

bool hasHttpError(QNetworkReply* reply){
    bool wasOnError = true;
    switch(reply->error()){
    case QNetworkReply::NoError:
        wasOnError = false;
        break;
    case QNetworkReply::ConnectionRefusedError:
    case QNetworkReply::RemoteHostClosedError:
    case QNetworkReply::HostNotFoundError:
    case QNetworkReply::TimeoutError:
    case QNetworkReply::OperationCanceledError:
    case QNetworkReply::SslHandshakeFailedError:
    case QNetworkReply::TemporaryNetworkFailureError:
    case QNetworkReply::NetworkSessionFailedError:
    case QNetworkReply::BackgroundRequestNotAllowedError:
    case QNetworkReply::TooManyRedirectsError:
    case QNetworkReply::InsecureRedirectError:
    case QNetworkReply::UnknownNetworkError:
    case QNetworkReply::ProxyConnectionRefusedError:
    case QNetworkReply::ProxyConnectionClosedError:
    case QNetworkReply::ProxyNotFoundError:
    case QNetworkReply::ProxyTimeoutError:
    case QNetworkReply::ProxyAuthenticationRequiredError:
    case QNetworkReply::UnknownProxyError:
    case QNetworkReply::ContentAccessDenied:
    case QNetworkReply::ContentOperationNotPermittedError:
    case QNetworkReply::ContentNotFoundError:
    case QNetworkReply::AuthenticationRequiredError:
    case QNetworkReply::ContentReSendError:
    case QNetworkReply::ContentConflictError:
    case QNetworkReply::ContentGoneError:
    case QNetworkReply::UnknownContentError:
    case QNetworkReply::ProtocolUnknownError:
    case QNetworkReply::ProtocolInvalidOperationError:
    case QNetworkReply::ProtocolFailure:
    case QNetworkReply::InternalServerError:
    case QNetworkReply::OperationNotImplementedError:
    case QNetworkReply::ServiceUnavailableError:
    case QNetworkReply::UnknownServerError:

        break;
    }

    return wasOnError;
}

void HttpRequestHandler::requestReply(QNetworkReply *reply){
    reply->deleteLater();
    if(hasHttpError(reply)){
        int errCode = -1;
        qDebug() << (errCode = reply->error());

        emit dataLoadingFailed(errCode);

        return;
    }

    QJsonArray result = (QJsonDocument::fromJson(reply->readAll()).toVariant()).toJsonArray();
    QJsonArray* data = new QJsonArray();
    QStringList resultRegions, resultCountries;
    try {
        std::sort(result.begin(), result.end(), [](const QJsonValue &v1, const QJsonValue &v2) {
            return v1.toObject()["regionCode"].toString() < v2.toObject()["regionCode"].toString()
                   && v1.toObject()["iso2CountryCode"].toString() < v2.toObject()["iso2CountryCode"].toString()
                   && v1.toObject()["cityName"].toString() < v2.toObject()["cityName"].toString()
                   && v1.toObject()["name"].toString() < v2.toObject()["name"].toString();
        });

        QFuture<QStringList> distinctRegionsFuture =QtConcurrent::run(&distinctList, result, "regionCode");
        QFuture<QStringList> distinctCountriesFuture =QtConcurrent::run(&distinctList, result, "iso2CountryCode");
        QFuture addToArrayFuture =QtConcurrent::run(&addToArray, &result, data);

        resultRegions = distinctRegionsFuture.result();
        resultCountries = distinctCountriesFuture.result();
        addToArrayFuture.waitForFinished();
    } catch(std::exception& error){
        qDebug() << error.what();
    }


    emit dataLoaded(*data, resultRegions, resultCountries);
    delete data;
}
