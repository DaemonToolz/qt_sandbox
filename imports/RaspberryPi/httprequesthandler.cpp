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
#include "src/stationcity.h"

HttpRequestHandler::HttpRequestHandler(QObject *parent)
    : QObject{parent}
{
    m_networkAccessManager = new QNetworkAccessManager(qApp);
}

void HttpRequestHandler::get(){
    auto status = connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, &HttpRequestHandler::requestReply);
    qDebug() << "Connection status:" << status;

    m_networkAccessManager->get(QNetworkRequest(QUrl("http://192.168.1.62:10000/api/air/v1/stations")));
}

void HttpRequestHandler::requestReply(QNetworkReply *reply){
    QJsonArray result = (QJsonDocument::fromJson(reply->readAll()).toVariant()).toJsonArray();
    QList<StationCity>* data = new QList<StationCity>();
    for(auto it = result.begin(); it != result.end(); it++){
        auto row = it->toObject();
        StationCity sc( row["cityName"].toString(),
                       row["name"].toString(),
                       row["category"].toString(),
                       row["iataStationCode"].toString(),
                       row["iso2CountryCode"].toString(),
                       row["regionCode"].toString());
        data->append(sc);
    }

    emit dataLoaded(*data);
    delete data;
}
