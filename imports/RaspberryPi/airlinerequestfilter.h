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

    Q_INVOKABLE void setAllStations(const QJsonArray& stations) {
        m_stations.clear();
        for(auto it = stations.begin(); it != stations.end(); it++){
            auto row = it->toObject();
            StationCity sc( row["cityName"].toString(),
                           row["name"].toString(),
                           row["category"].toString(),
                           row["iataStationCode"].toString(),
                           row["iso2CountryCode"].toString(),
                           row["regionCode"].toString());
            m_stations.append(sc);
        }

    }

    QString getSelectedRegion() const { return m_selectedRegion; }
    void setSelectedRegion(const QString& region) {
        m_selectedRegion = region;
        QJsonArray* data = new QJsonArray();
        for(auto it = m_stations.begin(); it != m_stations.end(); ++it){
            if(it->regionCode() == region){
                data->append(it->toJson());
            }
        }

       /* std::sort(data->begin(), data->end(), [](const QJsonObject& a, const QJsonObject& b) {
            return a["iso2CountryCode"].toString() < b["iso2CountryCode"].toString();
        });*/
        //data->erase(std::unique(data->begin(), data->end()));

        emit selectedRegionUpdated(*data);
        delete data;
    }

    QString getSelectedCountry() const { return m_selectedCountry; }
    void setSelectedCountry(const QString& country) {
        m_selectedCountry = country;
        QJsonArray* data = new QJsonArray();

        for(auto it = m_stations.begin(); it != m_stations.end(); ++it){
            if(it->iso2CountryCode() == country){
                data->append(it->toJson());
            }
        }


        emit selectedCountryUpdated(*data);
        delete data;
    }

    QString getSelectedAirport() const { return m_selectedCountry; }
    void setSelectedAirport(const QString& airport) {
        m_selectedAirport = airport;
        QJsonArray* data = new QJsonArray();

        for(auto it = m_stations.begin(); it != m_stations.end(); ++it){
            if(it->name() == airport && !data->contains(it->name())){
                data->append(it->toJson());
            }
        }
        emit selectedAirportUpdated(*data);
        delete data;
    }

signals:
    void selectedRegionUpdated (const QJsonArray& region);
    void selectedCountryUpdated(const QJsonArray& country);
    void selectedAirportUpdated(const QJsonArray& airport);

private:
    QList<StationCity> m_stations;
    QString m_selectedRegion, m_selectedCountry, m_selectedAirport;
};

#endif // AIRLINEREQUESTFILTER_H
