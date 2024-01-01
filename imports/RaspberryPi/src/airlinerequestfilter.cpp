#include "airlinerequestfilter.h"


inline void swap(QJsonValueRef v1, QJsonValueRef v2)
{
    QJsonValue temp(v1);
    v1 = QJsonValue(v2);
    v2 = temp;
}

AirlineRequestFilter::AirlineRequestFilter(QObject *parent)
    : QObject{parent}
{}


Q_INVOKABLE void AirlineRequestFilter::setAllStations(const QJsonArray& stations) {
    m_stations.clear();
    for(auto it = stations.begin(); it != stations.end(); it++){
        auto row = it->toObject();
        StationCity sc( row["iataStationCode"].toString(),
                       row["name"].toString(),
                       row["cityName"].toString(),
                       row["category"].toString(),
                       row["iso2CountryCode"].toString(),
                       row["regionCode"].toString());
        m_stations.append(sc);
    }

}

QString AirlineRequestFilter::getSelectedRegion() const { return m_selectedRegion; }
void AirlineRequestFilter:: setSelectedRegion(const QString& region) {
    m_selectedRegion = region;
    QJsonArray* data = new QJsonArray();
    for(auto it = m_stations.begin(); it != m_stations.end(); ++it){
        if(it->regionCode() == region){
            if(auto findIfIt = std::find_if(data->begin(), data->end(), [=](const QJsonValue& e) {
                    return e.toObject()["iso2CountryCode"].toString() == it->iso2CountryCode();
                });findIfIt == data->end()){
                data->append(it->toJson());
            }
        }
    }

    std::sort(data->begin(), data->end(), [](const QJsonValue& a, const QJsonValue& b) {
        return a.toObject()["iso2CountryCode"].toString() < b.toObject()["iso2CountryCode"].toString();
    });

    emit selectedRegionUpdated(*data);
    delete data;
}

QString AirlineRequestFilter::getSelectedCountry() const { return m_selectedCountry; }
void AirlineRequestFilter::setSelectedCountry(const QString& country) {
    m_selectedCountry = country;
    QJsonArray* data = new QJsonArray();

    for(auto it = m_stations.begin(); it != m_stations.end(); ++it){
        if(it->iso2CountryCode() == country){
            if(auto findIfIt = std::find_if(data->begin(), data->end(), [=](const QJsonValue& e) {
                    return e.toObject()["iataStationCode"].toString() == it->iataStationCode();
                });findIfIt == data->end()){
                data->append(it->toJson());
            }
        }
    }
    std::sort(data->begin(), data->end(), [](const QJsonValue& a, const QJsonValue& b) {
        return a.toObject()["iataStationCode"].toString() < b.toObject()["iataStationCode"].toString();
    });



    emit selectedCountryUpdated(*data);
    delete data;
}

QString AirlineRequestFilter::getSelectedAirport() const { return m_selectedCountry; }
void AirlineRequestFilter::setSelectedAirport(const QString& airport) {
    m_selectedAirport = airport;
    if(auto findIfIt = std::find_if(m_stations.begin(),m_stations.end(), [=](const StationCity& e) {
            return e.iataStationCode() == airport;
        });findIfIt != m_stations.end()){
        emit selectedAirportUpdated(findIfIt->toJson());
    }

}
