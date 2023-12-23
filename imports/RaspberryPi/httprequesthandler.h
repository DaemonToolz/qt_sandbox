#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H

#include "qnetworkaccessmanager.h"
#include "qqmlengine.h"
#include <QObject>
#include "src/stationcity.h"
class HttpRequestHandler : public QObject
{
    Q_OBJECT
public:
    explicit HttpRequestHandler(QObject *parent = nullptr);
    Q_INVOKABLE void get();

signals:
    void dataLoaded(const QList<StationCity>& result);

public slots:
    void requestReply(QNetworkReply *reply);

private:
    QNetworkAccessManager* m_networkAccessManager;
};

#endif // HTTPREQUESTHANDLER_H
