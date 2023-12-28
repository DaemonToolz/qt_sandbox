#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

#include "qnetworkaccessmanager.h"
#include "qqmlengine.h"
#include <QObject>
#include <QJsonArray>
#include <QNetworkReply>
class HttpRequestHandler : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequestHandler(QObject *parent = nullptr);
    Q_INVOKABLE void get();

signals:
    void dataLoaded(const QJsonArray& result, const QStringList& regions, const QStringList& countries);
    void dataLoadingFailed(const int& responseCode);
public slots:
    void requestReply(QNetworkReply *reply);
    void requestNetworkError(QNetworkReply::NetworkError* error);
private:
    QNetworkAccessManager* m_networkAccessManager;
};

#endif // HTTPREQUESTHANDLER_H
