#include "translationengine.h"
#include <QCoreApplication>
#include <QDir>
#include <map>

TranslationEngine::TranslationEngine(QObject *parent)
    : QObject{parent}
{

}

QStringList TranslationEngine::getAllLanguages(){
    QList<QString> qListStr;
    for(auto it = instance().m_translatorMap.begin(); it != instance().m_translatorMap.end(); ++it) {
        qListStr.append(QString::fromStdString(it->first));
    }
    return qListStr;
}

void TranslationEngine::addToTranslation(const QString& language){
    QTranslator translator;
    QString path = ":/qt/qml/translated/i18n/qml_"+language;
    bool added = translator.load(path);
    if(added){
        addToTranslation(language, path);
    }
}

void TranslationEngine::addToTranslation(const QString& language, const QString& path){
    instance().m_translatorMap[language.toStdString()] = path.toStdString();
}



Q_INVOKABLE void TranslationEngine::switchToLanguage(const QString &language)
{
    if(instance().currentLanguage() == language){
        return;
    }
    QTranslator tr;
    static_cast<void>(tr.load(QString::fromStdString(instance().m_translatorMap.at(language.toStdString()))));
    QCoreApplication::installTranslator(&tr);
    instance().m_engine->retranslate();
    instance().m_currLanguage = language;
    emit instance().currentLanguageChanged(language);
}
