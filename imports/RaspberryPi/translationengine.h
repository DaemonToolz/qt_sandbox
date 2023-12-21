#ifndef TRANSLATIONENGINE_H
#define TRANSLATIONENGINE_H

#include "qqmlapplicationengine.h"
#include <QObject>
#include <QTranslator>
#include <QCoreApplication>

class TranslationEngine : public QObject
{
    Q_OBJECT
public:
    static TranslationEngine &instance() { static TranslationEngine object; return object; }
    QQmlApplicationEngine* m_engine;
    QTranslator* m_translator;
    Q_INVOKABLE void switchToLanguage(const QString &language);

    explicit TranslationEngine(QObject *parent = nullptr);
signals:

public slots:

private:
    QString m_crrentLang;

};

#endif // TRANSLATIONENGINE_H
