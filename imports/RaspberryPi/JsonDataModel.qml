import QtQuick 6.2
import QtQuick.Window 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts
import HttpRequestHandler;
import AirlineRequestFilter;
import QtQuick.Controls.Material 6.2

Item {
    anchors.fill: parent


    AirlineRequestFilter{
        id: filterRequest
        onSelectedAirportChanged: (data) => {

                                  }
        onSelectedCountryUpdated:  (data) => {
                                       selectorBoxModel.clear();

                                       for(let i = 0; i < data.length; ++i){
                                           selectorBoxModel.append({value:data[i].iataStationCode})
                                       }
                                   }
        onSelectedRegionUpdated:  (data) => {
                                      selectorBoxModel.clear();

                                      for(let i = 0; i < data.length; ++i){
                                          selectorBoxModel.append({value:data[i].iso2CountryCode})
                                      }
                                  }
    }

    HttpRequestHandler{
        id: requestHandler
        onDataLoaded: (result, regions, countries) => {
                          stringSelector.target = "Region"
                          filterRequest.setAllStations(result);
                          selectorBoxModel.clear();
                          console.log(regions)
                          for(let i = 0; i < regions.length; ++i){
                              selectorBoxModel.append({value:regions[i]})
                          }

                          bIndicator.visible = false
                      }


        onDataLoadingFailed: (responseCode) => {
                                 bIndicator.visible = false
                                 errorCodePopup.visible = true
                                 errorCodePopupContent.text = qsTranslate("ErrorCodes", "http.code.%1".arg(responseCode))
                             }

    }


    Popup {
        id: errorCodePopup
        padding: 10
        width:250
        height:250
        x: (parent.width-250)/2
        y: (parent.height-250)/2
        visible: false

        contentItem: Text {
            id: errorCodePopupContent
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
                bIndicator.visible = true
                requestHandler.get()
            }
        }

        BusyIndicator{
            id: bIndicator
            visible: false
            Layout.fillWidth: true
            Layout.fillHeight: true
        }


        Component {
            id: itemSelectorDelegate
            Item {
                width: stringSelector.cellWidth;
                height: stringSelector.cellHeight
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 5
                    radius: 5
                    color: "#F0F0F0"

                    Label {
                        horizontalAlignment: "AlignHCenter"
                        verticalAlignment: "AlignVCenter"
                        width:parent.width
                        height:parent.height
                        text: qsTranslate(stringSelector.target, value)
                    }
                }

            }
        }

        GridView{
            cellWidth: 196
            cellHeight : 196
            id: stringSelector
            Layout.fillWidth: true
            Layout.fillHeight: true
            verticalLayoutDirection: Grid.TopToBottom
            layoutDirection: Qt.LeftToRight
            flow: Grid.TopToBottom
            flickableDirection: Flickable.HorizontalFlick
            keyNavigationWraps: false
            smooth: true

            property string target : "Region";

            model: ListModel{
                id: selectorBoxModel
            }

            MouseArea {
                anchors.fill: parent
                onClicked: (mouse) => {
                               let posInGridView = Qt.point(mouse.x, mouse.y)
                               let posInContentItem = mapToItem(stringSelector.contentItem, posInGridView)
                               let index = stringSelector.indexAt(posInContentItem.x, posInContentItem.y)
                               console.log(index, posInGridView, posInContentItem)
                               if(index === -1){
                                   return;
                               }

                               stringSelector.currentIndex = index

                               switch(stringSelector.target){
                                   case "Region":
                                   stringSelector.target = "Country"
                                   filterRequest.selectedRegion = selectorBoxModel.get(index).value;

                                   break;
                                   case "Country":
                                   stringSelector.target = "Airport";

                                   filterRequest.selectedCountry = selectorBoxModel.get(index).value;
                                   break;
                                   default:
                                   filterRequest.selectedAirport = selectorBoxModel.get(index).value;
                                   break;
                               }
                           }
            }
            delegate: itemSelectorDelegate
            add: Transition {
                NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 750 }
            }


        }

    }


    /*

    ListView {
        id: mainList
        Layout.fillWidth: true
        Layout.fillHeight: true
        visible:false
        model: ListModel {
            id: model
        }
        delegate: Row {
            id: myRow
            spacing: 5
            height:32

            Label {
                verticalAlignment: Text.AlignVCenter
                height:parent.height
                text: qsTranslate("RegionCode",regionCode)
            }

            Label {
                verticalAlignment: Text.AlignVCenter
                height:parent.height
                text: iso2CountryCode
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
