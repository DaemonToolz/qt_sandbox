#ifndef FILEREADER_H
#define FILEREADER_H

#include <qqml.h>

#include <QJsonDocument>
#include <QJsonObject>

#include <QObject>

class FileReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject data READ data CONSTANT)
public:
    explicit FileReader(QObject *parent = nullptr);
    QJsonObject read();
    QJsonObject data();
signals:

private:
    QJsonObject m_data;
    QString source;
};

#endif // FILEREADER_H
