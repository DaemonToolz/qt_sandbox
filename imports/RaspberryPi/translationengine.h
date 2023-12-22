#ifndef TRANSLATIONENGINE_H
#define TRANSLATIONENGINE_H

#include "qqmlapplicationengine.h"
#include <QObject>
#include <QTranslator>
#include <QCoreApplication>
#include <map>
class TranslationEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList availableLanguages READ getAllLanguages CONSTANT)
    Q_PROPERTY(QString currentLanguage READ currentLanguage NOTIFY currentLanguageChanged)
protected:
    std::map<std::string, std::string> m_translatorMap;
public:

    static TranslationEngine &instance() { static TranslationEngine object; return object; }
    static void addToTranslation(const QString& language, const QString& path);
    static void addToTranslation(const QString& language);

    QQmlApplicationEngine* m_engine;

    Q_INVOKABLE void switchToLanguage(const QString &language);
    Q_INVOKABLE QStringList getAllLanguages();

    QString currentLanguage() const { return m_currLanguage; }
    explicit TranslationEngine(QObject *parent = nullptr);

signals:
    void currentLanguageChanged(const QString& newLang);

public slots:

private:
    QString m_currLanguage;
};

#endif // TRANSLATIONENGINE_H
