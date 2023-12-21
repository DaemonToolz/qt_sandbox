#include "translationengine.h"
#include <QCoreApplication>
#include <exception>
TranslationEngine::TranslationEngine(QObject *parent)
    : QObject{parent}
{

}

Q_INVOKABLE void TranslationEngine::switchToLanguage(const QString &language)
{
    try {
        QString str;
        if(language ==  instance().m_crrentLang){
            str = QString::fromStdString("fr");
        } else {
            str = language;
        }
        QTranslator translator;

        bool result = (translator.load(":/qt/qml/translated/i18n/qml_" + str));
        qDebug() << "IS LANG " << str << " LOADED:" << result;

        QCoreApplication::installTranslator(&translator);
        instance().m_engine->retranslate();
        instance().m_crrentLang = str;
    } catch(std::exception& ex){
        qDebug() << ex.what();
    } catch (...) {
        qDebug() << "ERROR";
    }
}
