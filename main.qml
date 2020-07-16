import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Git thermometer")

    signal _GithubImageSelected
    signal _GitlabImageSelected

    property string git_platform_selected;


    Menu {
        objectName: "menu"
        id: menu_frame
        visible: true
    }

    PlatformCharts {
        objectName: "platform_charts"
        id: platforms_charts_frame
        visible: false
    }

    function setVisibleMenu(visible){
        menu_frame.visible = visible
    }

    function setVisiblePlatformCharts(visible){
        platforms_charts_frame.visible = visible;
    }
}

