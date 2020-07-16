import QtQuick 2.0
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: menu
    width: window.width/1.5
    height: window.height/1.5
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    ColumnLayout {
        id: columnLayout
        anchors.fill: menu

        Item {
            height: (menu.height/100)*5
            Layout.fillWidth: true

            Text {
                id: text_git_platform
                width: parent.width
                color: "#000000"
                text: qsTr("Choose a git platform")
                elide: Text.ElideLeft
                fontSizeMode: Text.HorizontalFit
                horizontalAlignment: Text.AlignHCenter
                lineHeight: 1
                styleColor: "#000000"
                font.pixelSize: (parent.width/100)*7
                Layout.alignment: Qt.AlignTop
            }
        }

        RowLayout {
            id: rowLayout
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 20

            Item {
                Layout.fillWidth: true;
                height: (menu.height/100)*50

                Image {
                    id: gitlab_image;
                    sourceSize.height: 0
                    sourceSize.width: parent.width
                    fillMode: Image.PreserveAspectFit
                    source: "resources/gitlab.png"

                    Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        border.width: 2
                        border.color: "red"
                        anchors.topMargin: -parent.width/16
                        anchors.bottomMargin: -parent.width/16
                        radius: 15

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                window.setVisibleMenu(false);
                                window.setVisiblePlatformCharts(true);

                                git_platform_selected = "gitlab"

                                window._GithubImageSelected()
                            }

                        }
                    }
                }
            }

            Item {
                Layout.fillWidth: true
                height: (menu.height/100)*50

                Image {
                    id: github_image
                    sourceSize.height: 0
                    sourceSize.width: parent.width+5
                    fillMode: Image.PreserveAspectFit
                    source: "resources/github.png"

                    Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                        border.width: 2
                        border.color: "red"
                        anchors.topMargin: -parent.width/16
                        anchors.bottomMargin: -parent.width/16
                        radius: 15

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                window.setVisibleMenu(false);
                                window.setVisiblePlatformCharts(true);

                                git_platform_selected = "github"

                                window._GitlabImageSelected();
                            }
                        }
                    }
                }
            }
        }
    }
}




