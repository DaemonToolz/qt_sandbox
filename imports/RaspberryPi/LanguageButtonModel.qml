import QtQuick 6.2
import TranslationEngine;
import QtQuick.Controls 6.2

Button {
    anchors.centerIn: parent
    width: parent.width / 2
    height: parent.height / 2
    text: qsTranslate("Screen02", "btn.change_lang")
    TranslationEngine{id: engine}

    onClicked:{

        engine.switchToLanguage("en");
    }
}

