import QtQuick 2.0
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtCharts 2.0

import Qt.cpp.qobjectSingleton 1.0 as Cpp
import "PlatformCharts.js" as Js

Item {
    id: platform_charts

    StackView {
        id: stack_view
        width: parent.width
        height: parent.height
        initialItem: slide_languages_1
    }

    property string cb_year_s1_text : "2020"
    property string cb_month_s1_text : "January"

    property string cb_year_s2_text : "2020"
    property string cb_language_s2_text : "All languages"

    property Item slide_languages_1
    property Item slide_languages_2

    property bool chart_loading: false

    property int active_slide_index : 0

    property CategoryAxis axisX_chart_2: CategoryAxis {}



    /* SLIDE LANGUAGES 1 */

    slide_languages_1: Item {

        ColumnLayout {
            width: window.width
            height: window.height

            Item {
                id: header_s1
                Layout.fillWidth: true
                height: 38

                Row {
                    id: row
                    anchors.fill: parent
                    anchors.topMargin: 12
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10

                    Image {
                        id: arrow_left_s1
                        source: "resources/arrow_left.svg"
                        sourceSize.height: parent.height+5
                    }

                    Row {
                        id: header_part_center_s1
                        width: parent.width/1.3
                        height: parent.height
                        anchors.centerIn: parent

                        ComboBox {
                            id: cb_year_s1
                            editable: true
                            height: parent.height+5
                            model: ListModel {
                                ListElement { text: "2020" }
                                ListElement { text: "2019" }
                                ListElement { text: "2018" }
                                ListElement { text: "2017" }
                                ListElement { text: "2016" }
                                ListElement { text: "2015" }
                                ListElement { text: "2014" }
                            }
                            onActivated: {
                                cb_year_s1_text = currentValue
                                Js.updateSlide(true);
                            }
                        }

                        ComboBox {
                            id: cb_month_s1
                            editable: true
                            height: parent.height+5
                            model: ListModel {
                                ListElement { text: "January" }
                                ListElement { text: "February" }
                                ListElement { text: "March" }
                                ListElement { text: "April" }
                                ListElement { text: "May" }
                                ListElement { text: "June" }
                                ListElement { text: "July" }
                                ListElement { text: "August" }
                                ListElement { text: "September" }
                                ListElement { text: "October" }
                                ListElement { text: "November" }
                                ListElement { text: "December" }
                                ListElement { text: "Whole year" }
                            }
                            onActivated: {
                                cb_month_s1_text = currentValue
                                Js.updateSlide(true);
                            }
                        }

                    }

                    Button {
                        font.pixelSize: 15
                        height: parent.height+5
                        anchors.right: header_part_center_s1.right
                        text: {
                            if(git_platform_selected == "gitlab")
                                qsTr("Switch to github");
                            else
                                qsTr("Switch to gitlab");
                        }

                        onClicked: {
                            if(git_platform_selected == "gitlab")
                                git_platform_selected = "github"
                            else
                                git_platform_selected = "gitlab"
                        }
                    }

                    Image {
                        id: arrow_right_s1
                        source: "resources/arrow_right.svg"
                        sourceSize.height: parent.height+5
                        anchors.right: parent.right

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                active_slide_index = 1;
                                updateSlide(true);
                            }
                        }
                    }
                }
            }

            Item {
                id: part_center_s1
                Layout.fillWidth: true
                Layout.fillHeight: true

                Loading {
                    id: loading_s1
                    objectName: "loading_s1"
                }


                ChartView {
                    id: chartview_s1
                    width: parent.width
                    height: parent.height
                    antialiasing: true
                    theme: ChartView.ChartThemeLight

                    BarSeries {
                        id: barseries_s1
                        axisY: ValueAxis {tickCount: 14; labelFormat: "%hd"}
                        barWidth: 1
                        labelsVisible : true
                    }
                }
            }
        }
    }




    /* SLIDE LANGUAGES 2 */

    slide_languages_2: Item {

        ColumnLayout {
            width: window.width
            height: window.height

            Item {
                id: header_s2
                Layout.fillWidth: true
                height: 38

                Row {
                    id: row_s2
                    anchors.fill: parent
                    anchors.topMargin: 12
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10

                    Image {
                        id: arrow_left_s2
                        source: "resources/arrow_left.svg"
                        sourceSize.height: parent.height+5
                    }

                    Row {
                        id: header_part_center_s2
                        width: parent.width/1.3
                        height: parent.height
                        anchors.centerIn: parent

                        ComboBox {
                            id: cb_year_s2
                            editable: true
                            height: parent.height+5
                            model: ListModel {
                                ListElement { text: "2020" }
                                ListElement { text: "2019" }
                                ListElement { text: "2018" }
                                ListElement { text: "2017" }
                                ListElement { text: "2016" }
                                ListElement { text: "2015" }
                                ListElement { text: "2014" }
                                ListElement { text: "Always" }
                            }
                            onActivated: {
                                cb_year_s2_text = currentValue
                                Js.updateSlide(true);
                            }
                        }

                        ComboBox {
                            id: cb_language_s2
                            editable: true
                            height: parent.height+5
                            model: ListModel {
                                ListElement { text: "All languages" }
                                ListElement { text: "Javascript" }
                                ListElement { text: "Python" }
                                ListElement { text: "Java" }
                                ListElement { text: "C++" }
                                ListElement { text: "C" }
                                ListElement { text: "PHP" }
                                ListElement { text: "C#" }
                                ListElement { text: "Shell" }
                                ListElement { text: "Go" }
                                ListElement { text: "TypeScript" }
                            }
                            onActivated: {
                                cb_language_s2_text = currentValue
                                Js.updateSlide(true);
                            }
                        }
                    }

                    Button {
                        font.pixelSize: 15
                        height: parent.height+5
                        anchors.right: header_part_center_s2.right
                        text: {
                            if(git_platform_selected == "gitlab")
                                qsTr("Switch to github");
                            else
                                qsTr("Switch to gitlab");
                        }

                        onClicked: {
                            if(git_platform_selected == "gitlab")
                                git_platform_selected = "github"
                            else
                                git_platform_selected = "gitlab"
                        }
                    }

                    Image {
                        id: arrow_right_s2
                        source: "resources/arrow_right.svg"
                        sourceSize.height: parent.height+5
                        anchors.right: parent.right

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                if(!chart_loading){
                                    active_slide_index = 0;
                                    Js.updateSlide(true);
                                }
                            }
                        }
                    }
                }
            }

            Item {
                id: part_center_s2
                Layout.fillWidth: true
                Layout.fillHeight: true

                Loading {
                    id: loading_s2
                    objectName: "loading_s1"
                }

                ChartView {
                    id: chartview_s2
                    width: parent.width
                    height: parent.height
                    antialiasing: true
                    theme: ChartView.ChartThemeLight
                }
            }
        }
    }
    function updateSlide(new_download_process){
        Js.updateSlide(new_download_process);
    }
}



