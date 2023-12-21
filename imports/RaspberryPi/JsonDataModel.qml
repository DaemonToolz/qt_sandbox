import QtQuick 6.2
import QtQuick.Window 6.2
import QtQuick.Controls 6.2
import FileReader;
import QtQuick.Controls.Material 6.2

Item {
    id: myBookModel
    FileReader{
        id: fReader
    }

    Column {
        anchors.fill: parent
        spacing: 5
        Text {
           id: totalItemsLabel
           text: "fReader.data.length"
        }

        Text {
           id: totalItems
        }

        ListView {
            id: mainList
            width: 750
            height: 750
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
    }

    Component.onCompleted: {
        totalItems.text =  fReader.data.book.length
    }

}
