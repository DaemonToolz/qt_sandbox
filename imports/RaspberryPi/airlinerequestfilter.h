#ifndef AIRLINEREQUESTFILTER_H
#define AIRLINEREQUESTFILTER_H

#include <QStringList>
#include "src/stationcity.h"
#include <QObject>
#include <QJsonArray>

class AirlineRequestFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString selectedRegion READ getSelectedRegion WRITE setSelectedRegion NOTIFY selectedRegionUpdated)
    Q_PROPERTY(QString selectedCountry READ getSelectedCountry WRITE setSelectedCountry NOTIFY selectedCountryUpdated)
    Q_PROPERTY(QString selectedAirport READ getSelectedAirport WRITE setSelectedAirport NOTIFY selectedAirportUpdated)

public:
    explicit AirlineRequestFilter(QObject *parent = nullptr);

    Q_INVOKABLE void setAllStations(const QJsonArray& stations);
    QString getSelectedRegion() const;
    QString getSelectedCountry() const;
    QString getSelectedAirport() const;
    void setSelectedRegion(const QString& region);
    void setSelectedCountry(const QString& country);
    void setSelectedAirport(const QString& airport);
signals:
    void selectedRegionUpdated (const QJsonArray& region);
    void selectedCountryUpdated(const QJsonArray& country);
    void selectedAirportUpdated(const QJsonArray& airport);

private:
    QList<StationCity> m_stations;
    QString m_selectedRegion, m_selectedCountry, m_selectedAirport;
};

#endif // AIRLINEREQUESTFILTER_H
