// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "imports/RaspberryPi/src/filereader.h"
#include "imports/RaspberryPi/src/translationengine.h"
#include "imports//RaspberryPi/src/httprequesthandler.h"
#include "imports/RaspberryPi/src/airlinerequestfilter.h"
#include <QResource>
#include <QTranslator>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    set_qt_environment();

    qmlRegisterType<FileReader>("FileReader", 1, 0, "FileReader");
    qmlRegisterType<TranslationEngine>("TranslationEngine", 1, 0, "TranslationEngine");
    qmlRegisterType<HttpRequestHandler>("HttpRequestHandler", 1, 0, "HttpRequestHandler");
    qmlRegisterType<AirlineRequestFilter>("AirlineRequestFilter", 1, 0, "AirlineRequestFilter");

    QGuiApplication app(argc, argv);

    QTranslator translator;
    // On évite le NoDiscard attribute warning
    static_cast<void>(translator.load(":/qt/qml/translated/i18n/base"));
    TranslationEngine::addToTranslation("fr", true);
    TranslationEngine::addToTranslation("en");
    app.installTranslator(&translator);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    TranslationEngine::instance().m_engine = &engine;

    return app.exec();
}
