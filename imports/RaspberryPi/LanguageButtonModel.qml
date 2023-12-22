import QtQuick 6.2
import QtQuick.Layouts
import TranslationEngine;
import QtQuick.Controls 6.2

Item{
    anchors.fill: parent
    TranslationEngine{
        id: engine
        onCurrentLanguageChanged: {
            reload();
        }
    }

    Component {
        id: languageSelectorDelegate
        Item {
            width: languageSelector.cellWidth;
            height: languageSelector.cellHeight
            Column {
                anchors.fill: parent
                anchors.margins: 5
                spacing: 5
                IconImage {
                    name: value + "_flag"
                    width: parent.width
                    height: 64
                    horizontalAlignment: "AlignHCenter"
                    source: "qrc:/assets/svgIcons/"+ value +"_flag"
                    color:"transparent"
                }

                Label {
                    horizontalAlignment: "AlignHCenter"
                    width:parent.width
                    text: qsTranslate("Languages", value)
                }
            }
        }
    }


    ColumnLayout {
        anchors.fill: parent
        spacing: 2

        Label{
            text: qsTranslate("Languages", "select_language")
            font.bold: true
            font.pixelSize: 24
            Layout.alignment: Qt.AlignHCenter
        }

        GridView{
            cellWidth: 128
            cellHeight : 96
            id: languageSelector
            Layout.fillWidth: true
            Layout.fillHeight: true

            focus: true
            highlightFollowsCurrentItem: true
            keyNavigationWraps: false
            smooth: true
            highlight: Rectangle {
                opacity: 0.25
                color: "teal";
                radius: 5
            }
            model: ListModel{
                id: languageBoxModel
            }

            MouseArea {
                anchors.fill: parent
                onClicked: (mouse) => {
                               let posInGridView = Qt.point(mouse.x, mouse.y)
                               let posInContentItem = mapToItem(languageSelector.contentItem, posInGridView)
                               let index = languageSelector.indexAt(posInContentItem.x, posInContentItem.y)
                               console.log(index, posInGridView, posInContentItem)
                               if(index === -1){
                                   return;
                               }

                               engine.switchToLanguage(engine.availableLanguages[index])
                               languageSelector.currentIndex = index
                           }
            }
            delegate: languageSelectorDelegate
            add: Transition {
                NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 500 }
                NumberAnimation { property: "scale"; easing.type: Easing.OutBounce; from: 0; to: 1.0; duration: 750 }
            }
        }


        Component.onCompleted: {
            reload();
        }

        function reload(){
            languageBoxModel.clear();
            for(let i = 0; i < engine.availableLanguages.length; ++i){
                console.log(engine.availableLanguages[i])
                languageBoxModel.append({"value": engine.availableLanguages[i]})
            }
        }
    }
}

/*
Item{
    anchors.fill: parent

    TranslationEngine{
        id: engine
        onCurrentLanguageChanged: {
            reload();
        }
    }


    ComboBox{
        id: languageSelector
        textRole: "value"
        width: parent.width - 20
        model: ListModel{
            id: languageBoxModel
        }
        onActivated: engine.switchToLanguage(currentText)

        contentItem: Row {

            spacing: 5
            IconImage {
                name: languageSelector.displayText + "_flag"
                width: 64
                verticalAlignment: "AlignVCenter"
                source: "qrc:/assets/svgIcons/"+ languageSelector.displayText +"_flag"
                color:"transparent"
            }

            Label {
                verticalAlignment: "AlignVCenter"
                height:parent.height
                text: qsTranslate("Languages",languageSelector.displayText)
            }
        }

        delegate: ItemDelegate {
            id: delegate

            required property var model
            required property int index

            width: languageSelector.width
            contentItem: Row {
                spacing: 5
                IconImage {
                    name: delegate.model[languageSelector.textRole] + "_flag"
                    width: 64
                    verticalAlignment: "AlignVCenter"
                    source: "qrc:/assets/svgIcons/"+ delegate.model[languageSelector.textRole] +"_flag"
                    color:"transparent"
                }

                Label {
                    verticalAlignment: "AlignVCenter"
                    height:parent.height
                    text: qsTranslate("Languages", delegate.model[languageSelector.textRole])
                }
            }
            highlighted: languageSelector.highlightedIndex === index
        }

    }


    Component.onCompleted: {
        reload();
    }

    function reload(){
        for(let i = 0; i < engine.availableLanguages.length; ++i){
            console.log(engine.availableLanguages[i])
            languageBoxModel.append({"value": engine.availableLanguages[i]})
        }
    }

}
*/
