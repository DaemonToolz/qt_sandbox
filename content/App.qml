// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QtQuick.Window 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import RaspberryPi

ApplicationWindow {
    width: 1680
    height: 800

    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }

    visible: true
    title: "RaspberryPi"

    StackLayout {
        anchors.margins: 5
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Screen01 {}
        Screen02 {}
    }



    footer:
        TabBar {
        id: tabBar
        width: parent.width
        TabButton {
            text: qsTranslate("MainWindow","tabbar.home")
        }
        TabButton {
            text: qsTranslate("MainWindow","tabbar.settings")
        }
        position: TabBar.Footer
        activeFocusOnTab: true
        anchors.horizontalCenter: parent.horizontalCenter

    }
}

