import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: rootMenu
    width: 220
    height: menuCard.implicitHeight
    visible: opacity > 0.01
    opacity: isOpen ? 1.0 : 0.0

    property bool isOpen: false
    property var musicLoader

    Behavior on opacity {
        NumberAnimation { duration: 150; easing.type: Easing.InOutQuad }
    }

    function toggle(targetItem, parentItem) {
        if (isOpen) {
            isOpen = false
        } else {
            open(targetItem, parentItem)
        }
    }

    function open(targetItem, parentItem) {
        if (targetItem && parentItem) {
            var pos = targetItem.mapToItem(parentItem, targetItem.width - width, targetItem.height + 4)
            x = Math.max(10, Math.min(parentItem.width - width - 10, pos.x))
            y = pos.y
        }
        isOpen = true
    }

    function close() {
        isOpen = false
    }

    // Backdrop click-to-close is handled in Main.qml

    Rectangle {
        id: menuCard
        anchors.fill: parent
        color: "#f51c0e1e"
        radius: 12
        border.color: "#35ffffff"
        border.width: 1

        implicitHeight: contentColumn.implicitHeight + 20

        ColumnLayout {
            id: contentColumn
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 10
            spacing: 8

            // 1. Playback Speed (YouTube style)
            Text {
                text: "PLAYBACK SPEED"
                color: "#aaaaaa"
                font.pixelSize: 9
                font.bold: true
                font.letterSpacing: 1
                Layout.leftMargin: 6
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 4

                Repeater {
                    model: [0.5, 0.75, 1.0, 1.25, 1.5, 2.0]
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 24
                        radius: 6
                        color: (musicLoader && Math.abs(musicLoader.playbackRate - modelData) < 0.05) ? "#3a86ff" : (speedArea.containsMouse ? "#30ffffff" : "#18ffffff")

                        Text {
                            anchors.centerIn: parent
                            text: modelData + "x"
                            color: "white"
                            font.pixelSize: 9
                            font.bold: true
                        }

                        MouseArea {
                            id: speedArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                if (musicLoader) musicLoader.setPlaybackRate(modelData)
                            }
                        }
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#20ffffff"
            }

            // 2. Open Folder
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 32
                radius: 6
                color: folderArea.containsMouse ? "#25ffffff" : "transparent"

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 8
                    anchors.rightMargin: 8
                    spacing: 8

                    Text { text: "📁"; font.pixelSize: 13 }
                    Text {
                        text: "Open Music Folder"
                        color: "white"
                        font.pixelSize: 12
                        Layout.fillWidth: true
                    }
                }

                MouseArea {
                    id: folderArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if (musicLoader) {
                            Qt.openUrlExternally("file:///" + musicLoader.musicPath)
                        }
                        rootMenu.close()
                    }
                }
            }

            // 3. Rescan Library
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 32
                radius: 6
                color: rescanArea.containsMouse ? "#25ffffff" : "transparent"

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 8
                    anchors.rightMargin: 8
                    spacing: 8

                    Text { text: "🔄"; font.pixelSize: 13 }
                    Text {
                        text: "Rescan Music Library"
                        color: "white"
                        font.pixelSize: 12
                        Layout.fillWidth: true
                    }
                }

                MouseArea {
                    id: rescanArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if (musicLoader) musicLoader.ScanMusicFiles()
                        rootMenu.close()
                    }
                }
            }

            // 4. Song Info
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 32
                radius: 6
                color: infoArea.containsMouse ? "#25ffffff" : "transparent"

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 8
                    anchors.rightMargin: 8
                    spacing: 8

                    Text { text: "ℹ️"; font.pixelSize: 13 }
                    Text {
                        text: "Song Details"
                        color: "white"
                        font.pixelSize: 12
                        Layout.fillWidth: true
                    }
                }

                MouseArea {
                    id: infoArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        songInfoDialog.open()
                        rootMenu.close()
                    }
                }
            }
        }
    }
}
