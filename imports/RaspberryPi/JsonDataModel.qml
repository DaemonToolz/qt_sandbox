import QtQuick 6.2
import QtQuick.Window 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts
import HttpRequestHandler;
import QtQuick.Controls.Material 6.2

Item {
    anchors.fill: parent


    HttpRequestHandler{
        id: requestHandler
        onDataLoaded: (result) => {

            console.log( JSON.stringify(result))

            for(let i = 0; i < result.length; ++i){
                //model.append(result[i])
                //console.log(i)
            }
        }

    }


    ColumnLayout {
        anchors.fill: parent
        spacing: 2
        Button{
            id: searchBtn
            Layout.fillWidth: true
            width: parent.fillWidth
            height: 64
            text: qsTranslate("JsonDataModel", "btn.load")
            onClicked: {
                requestHandler.get()
            }
        }


        ListView {
            id: mainList
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: ListModel {
                id: model
            }
            delegate: Row {
                id: myRow
                spacing: 5

                Label {
                    verticalAlignment: Text.AlignVCenter
                    height:parent.height
                    text: iataStationCode
                }


                Label {
                    verticalAlignment: Text.AlignVCenter
                    height:parent.height
                    text: name
                }

                Label {
                    verticalAlignment: Text.AlignVCenter
                    height:parent.height
                    text: cityName
                }

                Label {
                    verticalAlignment: Text.AlignVCenter
                    height:parent.height
                    text: iso2CountryCode
                }

                Label {
                    verticalAlignment: Text.AlignVCenter
                    height:parent.height
                    text: regionCode
                }

                Label {
                    verticalAlignment: Text.AlignVCenter
                    height:parent.height
                    text: category
                }


            }
        }

        /*
        ListView {
            id: mainList
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: ListModel {
                id: model
            }
            delegate: Row {
                id: myRow
                spacing: 5
                Button {
                    icon.name: "shopping_cart"
                    icon.source: "qrc:/assets/svgIcons/shopping_cart.svg"
                    icon.color:"transparent"
                    display: "IconOnly"
                }

                Label {
                    verticalAlignment: Text.AlignVCenter
                    height:parent.height
                    text: name
                }

                IconImage {
                    name: "payment"
                    height: parent.height
                    verticalAlignment: "AlignVCenter"
                    source: "qrc:/assets/svgIcons/payments.svg"
                    color:"transparent"
                }

                Label {
                    verticalAlignment: Text.AlignVCenter
                    height:parent.height
                    text: ("%1 %2").arg(price).arg(qsTranslate("JsonDataModel",currency))
                }
            }
            Component.onCompleted: {
                for(let i = 0; i < fReader.data.book.length; ++i){
                    model.append(fReader.data.book[i])
                }
            }
        }
    */
    }


}
