#ifndef STATIONCITY_H
#define STATIONCITY_H
#include <QString>
#include <QJsonObject>
class StationCity{
    Q_GADGET
public:
    Q_PROPERTY(QString iataStationCode READ iataStationCode CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString cityName READ cityName CONSTANT)
    Q_PROPERTY(QString iso2CountryCode READ iso2CountryCode CONSTANT)
    Q_PROPERTY(QString regionCode READ regionCode CONSTANT)
    Q_PROPERTY(QString category READ category CONSTANT)

    QString iataStationCode() const {return m_iataStationCode;};
    QString name() const {return m_name;};
    QString cityName() const {return m_cityName;};
    QString iso2CountryCode() const {return m_iso2CountryCode;};
    QString regionCode() const {return m_regionCode;};
    QString category() const {return m_category;};

    explicit StationCity();
    StationCity(const QString& iataStationCode,
                const QString& name,
                const QString& cityName,
                const QString& category,
                const QString& iso2CountryCode,
                const QString& regionCode);
    StationCity(const StationCity& ref);

    ~StationCity();

    StationCity operator=(const StationCity& ref);

    QJsonObject toJson() const;

private:
    QString m_iataStationCode;
    QString m_name;
    QString m_cityName;
    QString m_iso2CountryCode;
    QString m_regionCode;
    QString m_category;

};


#endif // STATIONCITY_H
