#include "stationcity.h"

StationCity::StationCity() {}
StationCity::StationCity(const QString& iataStationCode,
            const QString& name,
            const QString& cityName,
            const QString& category,
            const QString& iso2CountryCode,
            const QString& regionCode){
    this->m_iataStationCode = iataStationCode;
    this->m_name = name;
    this->m_cityName = cityName;
    this->m_category = category;
    this->m_iso2CountryCode = iso2CountryCode;
    this->m_regionCode = regionCode;
}

StationCity::StationCity(const StationCity& ref){
    m_iataStationCode = ref.iataStationCode();
    m_name = ref.name();
    m_cityName = ref.cityName();
    m_category = ref.category();
    m_iso2CountryCode = ref.iso2CountryCode();
    m_regionCode = ref.regionCode();
}

StationCity::~StationCity(){}

StationCity StationCity::operator=(const StationCity& ref){
    return StationCity(ref);
}
