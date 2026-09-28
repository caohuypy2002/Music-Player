import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: songInfoDialog
    width: 360
    height: 310
    minimumWidth: 360
    minimumHeight: 310
    maximumWidth: 360
    maximumHeight: 310
    visible: false
    title: "Song Information"
    color: "#180d1a"

    property var musicLoader

    function open() {
        if (root) {
            x = root.x + Math.max(0, (root.width - width) / 2)
            y = root.y + Math.max(0, (root.height - height) / 2)
        }
        visible = true
        requestActivate()
    }

    function close() {
        visible = false
    }

    function formatTime(ms) {
        var totalSeconds = Math.max(0, Math.floor(ms / 1000))
        var minutes = Math.floor(totalSeconds / 60)
        var seconds = totalSeconds % 60
        return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#281026" }
            GradientStop { position: 1.0; color: "#140816" }
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            // Header
            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: "🎵 Song Information"
                    color: "white"
                    font.pixelSize: 15
                    font.bold: true
                    Layout.fillWidth: true
                }
                Rectangle {
                    width: 26
                    height: 26
                    radius: 13
                    color: closeArea.containsMouse ? "#40ffffff" : "#20ffffff"
                    Text {
                        anchors.centerIn: parent
                        text: "✕"
                        color: "white"
                        font.pixelSize: 12
                    }
                    MouseArea {
                        id: closeArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: songInfoDialog.close()
                    }
                }
            }

            // Info Card
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 10
                color: "#18ffffff"
                border.color: "#25ffffff"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 9

                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "Title:"; color: "#888888"; font.pixelSize: 12; Layout.preferredWidth: 68 }
                        Text {
                            text: musicLoader ? musicLoader.currentTitle : "-"
                            color: "white"
                            font.pixelSize: 13
                            font.bold: true
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "Artist:"; color: "#888888"; font.pixelSize: 12; Layout.preferredWidth: 68 }
                        Text {
                            text: musicLoader ? musicLoader.currentArtist : "-"
                            color: "white"
                            font.pixelSize: 12
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "Duration:"; color: "#888888"; font.pixelSize: 12; Layout.preferredWidth: 68 }
                        Text {
                            text: musicLoader ? formatTime(musicLoader.duration) : "0:00"
                            color: "white"
                            font.pixelSize: 12
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "Format:"; color: "#888888"; font.pixelSize: 12; Layout.preferredWidth: 68 }
                        Text {
                            text: (musicLoader ? musicLoader.currentFileFormat : "-") + " • " + (musicLoader ? musicLoader.currentFileSize : "-")
                            color: "#60a5fa"
                            font.pixelSize: 11
                            font.bold: true
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "File:"; color: "#888888"; font.pixelSize: 12; Layout.preferredWidth: 68 }
                        Text {
                            text: musicLoader ? musicLoader.currentFileName : "-"
                            color: "#cccccc"
                            font.pixelSize: 11
                            elide: Text.ElideMiddle
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text { text: "Location:"; color: "#888888"; font.pixelSize: 12; Layout.preferredWidth: 68 }
                        Text {
                            text: musicLoader ? musicLoader.currentFilePath : "-"
                            color: locArea.containsMouse ? "#93c5fd" : "#60a5fa"
                            font.pixelSize: 11
                            font.underline: locArea.containsMouse
                            elide: Text.ElideMiddle
                            Layout.fillWidth: true

                            MouseArea {
                                id: locArea
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    if (musicLoader) musicLoader.openCurrentFileLocation()
                                }
                            }
                        }
                    }
                }
            }

            // Bottom Action Buttons
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Item { Layout.fillWidth: true }

                Rectangle {
                    width: 130
                    height: 30
                    radius: 15
                    color: openFolderArea.containsMouse ? "#30ffffff" : "#1effffff"
                    border.color: "#30ffffff"
                    border.width: 1

                    RowLayout {
                        anchors.centerIn: parent
                        spacing: 4
                        Text { text: "📁"; font.pixelSize: 11 }
                        Text { text: "Open in Explorer"; color: "white"; font.pixelSize: 11 }
                    }

                    MouseArea {
                        id: openFolderArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            if (musicLoader) musicLoader.openCurrentFileLocation()
                        }
                    }
                }

                Rectangle {
                    width: 80
                    height: 30
                    radius: 15
                    color: okArea.containsMouse ? "#3a86ff" : "#283a86ff"
                    border.color: "#60a5fa"
                    border.width: 1

                    Text {
                        anchors.centerIn: parent
                        text: "Close"
                        color: "white"
                        font.pixelSize: 11
                        font.bold: true
                    }

                    MouseArea {
                        id: okArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: songInfoDialog.close()
                    }
                }

                Item { Layout.fillWidth: true }
            }
        }
    }
}
