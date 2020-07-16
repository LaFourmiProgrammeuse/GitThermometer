import QtQuick 2.0

Item {
    anchors.fill: parent

    property int n_max_request

    Column {
        anchors.fill: parent
        anchors.topMargin: parent.height/7

        AnimatedImage {
            source: "resources/Gear.gif";
            width: parent.width/4.2
            height: parent.width/4.2
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: progression
            text: ""
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    function setProgression(_progression){
        var percent = Math.floor((_progression/n_max_request)*100)
        progression.text = _progression+"/"+n_max_request+" ("+percent+"%)"
    }

    function setMaxRequest(_n_max_request){
        n_max_request = _n_max_request;
    }
}
