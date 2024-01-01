import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2

Item {
    id: airportSelectionRoot;
    anchors.fill: parent
    /*
    enum AirportChoice {
        None,
        Arrival,
        Depature
    }
    */
    function showFilters(target){
        airportSelectionRoot.displayFilters = target !==  0;
        airportSelectionRoot.choice = target;
    }

    function updateData(data){
        switch(airportSelectionRoot.choice){
        case 2:
            airportSelectionRoot.departureFrom = data
            break

        case 1:
            airportSelectionRoot.arrivalTo = data
            break;
        }

        airportSelectionRoot.displayFilters = false;
        airportSelectionRoot.choice = 0
    }

    property bool displayFilters: false
    property string departureFrom
    property string arrivalTo
    property int choice: 0;

    GridLayout{
        columns: 2
        anchors.fill: parent
        visible: !airportSelectionRoot.displayFilters
        Button{
            id: searchDeparture
            Layout.fillWidth: true
            width: parent.fillWidth
            height: 64
            contentItem: ColumnLayout {
                spacing: 5
                Text {
                    text :  qsTranslate("JsonDataModel", "btn.departure")
                }
                Text {
                    text :  qsTranslate("Airports", airportSelectionRoot.departureFrom)
                }
            }
            onClicked: {
                airportSelectionRoot.showFilters(2);
            }
        }


        Button{
            id: searchArrival
            Layout.fillWidth: true
            width: parent.fillWidth
            height: 64
            contentItem: ColumnLayout {
                spacing: 5
                Text {
                    text :  qsTranslate("JsonDataModel", "btn.arrival")
                }
                Text {
                    text :  qsTranslate("Airports", airportSelectionRoot.arrivalTo)
                }
            }
            onClicked: {
                airportSelectionRoot.showFilters(1);
            }
        }
    }

    JsonDataModel{
        id: airportSelection
        anchors.fill: parent
        visible: airportSelectionRoot.displayFilters
        //GridLayout.columnSpan: 2
        onAirportSelected: (airport)=>{
                             airportSelectionRoot.updateData(airport);

                         }

    }

}
