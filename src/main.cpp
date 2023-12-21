// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"
#include "../imports/RaspberryPi/filereader.h"
#include "../imports/RaspberryPi/translationengine.h"
#include <QResource>
#include <QTranslator>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    set_qt_environment();

    qmlRegisterType<FileReader>("FileReader", 1, 0, "FileReader");
    qmlRegisterType<TranslationEngine>("TranslationEngine", 1, 0, "TranslationEngine");

    QGuiApplication app(argc, argv);

    QTranslator translator;
    // On évite le NoDiscard attribute warning
    static_cast<void>(translator.load(":/qt/qml/translated/i18n/base"));

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

    TranslationEngine::instance().m_translator = &translator;
    TranslationEngine::instance().m_engine = &engine;

    return app.exec();
}
