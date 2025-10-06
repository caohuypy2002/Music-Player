import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import CustomImage 1.0

Window {
    id: playlistWindow
    width: 300
    height: 400
    visible: false
    title: "Playlist"
    property var musicLoader

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Image {
            anchors.fill: parent
            source: "qrc:/Icon/rose-petals.svg"
            fillMode: Image.Stretch
            cache: false
        }

        ListView {
            id: listView
            anchors.fill: parent
            model: musicLoader ? musicLoader.playlist : []
            spacing: 2
            clip: true

            delegate: Rectangle {
                width: listView.width
                height: 60
                color: index === musicLoader.currentIndex ? "#444444" : "transparent"

                RowLayout {
                    anchors.fill: parent
                    spacing: 8
                    anchors.margins: 4

                    CustomImage {
                        width: 50
                        height: 50
                        // luôn lấy album art từ metadata
                        pixmap: musicLoader.getAlbumArt(modelData)
                    }

                    ColumnLayout {
                        spacing: 2
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter

                        Text {
                            text: musicLoader.getTitle(modelData)
                            font.pixelSize: 14
                            color: "white"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }

                        Text {
                            text: musicLoader.getArtist(modelData)
                            font.pixelSize: 12
                            color: "#aaaaaa"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (musicLoader) {
                            musicLoader.playAt(index)
                        }
                        playlistWindow.visible = false
                    }
                }
            }

            // Cập nhật khi playlist hoặc bài hiện tại thay đổi
            Connections {
                target: musicLoader
                function onPlaylistChanged() {
                    listView.model = musicLoader.playlist
                }
                function onCurrentSongChanged() {
                    listView.forceLayout()
                }
            }
        }
    }
}
