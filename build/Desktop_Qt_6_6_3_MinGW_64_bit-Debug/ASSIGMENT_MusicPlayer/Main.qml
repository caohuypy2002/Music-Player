import QtQuick
import QtQuick.Layouts
import MusicLoader 1.0
import CustomImage 1.0

Window {
    id: root
    width: 640
    height: 280
    visible: true
    title: "Music Player"

    MusicLoader { id: musicLoader }

    // Kết nối trạng thái play/pause
    Connections {
        target: musicLoader
        function onPlayStateChanged(isPlaying) {
            playPause.isPlaying = isPlaying
        }
    }

    function formatTime(ms) {
        var totalSeconds = Math.floor(ms / 1000)
        var minutes = Math.floor(totalSeconds / 60)
        var seconds = totalSeconds % 60
        return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
    }

    Image {
        anchors.fill: parent
        source: "qrc:/Icon/rose-petals.svg"
        fillMode: Image.Stretch
        cache: false
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: albumArtSection
            Layout.fillHeight: true
            Layout.preferredWidth: root.width * 0.5
            color: "transparent"

            Rectangle {
                anchors.centerIn: parent
                width: Math.min(parent.width, parent.height) * 0.8
                height: Math.min(parent.width, parent.height) * 0.8
                radius: 20
                color: "transparent"
                clip: true
                layer.enabled: true
                layer.smooth: true

                ShaderEffectSource {
                    id: albumArtSource
                    sourceItem: albumArt
                    anchors.fill: parent
                    live: true
                    hideSource: false
                }

                CustomImage {
                    id: albumArt
                    anchors.fill: parent
                    pixmap: musicLoader.albumArt
                    visible: true
                    Connections {
                        target: musicLoader
                        function onAlbumArtChanged() {
                            albumArt.pixmap = musicLoader.albumArt
                        }
                    }
                }
            }
        }

        Rectangle {
            id: controlSection
            Layout.fillHeight: true
            Layout.preferredWidth: root.width * 0.5
            color: "transparent"

            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    Item { Layout.fillWidth: true }
                    Item { Layout.fillWidth: true }
                    CustomButton {
                        id: volumeBtn
                        iconSource: "qrc:/Icon/volume.svg"
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        onClicked: volumeContainer.visible = !volumeContainer.visible
                    }
                    CustomButton { iconSource: "qrc:/Icon/equalizer.svg"; Layout.fillWidth: true; Layout.fillHeight: true }
                    CustomButton { iconSource: "qrc:/Icon/threedotvertical.svg"; Layout.fillWidth: true; Layout.fillHeight: true }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 80
                    spacing: 4

                    Text {
                        id: songName
                        text: musicLoader.currentTitle
                        color: "white"
                        font.pixelSize: 28
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                    }

                    Text {
                        id: artistName
                        text: musicLoader.currentArtist
                        color: "lightgrey"
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40

                    CustomButton {
                        id: playlistBtn
                        iconSource: "qrc:/Icon/playlist.svg"
                        onClicked: playlistWindow.visible = !playlistWindow.visible
                    }
                    Item { Layout.fillWidth: true }
                    CustomButton { iconSource: "qrc:/Icon/heart.svg" }
                    Item { Layout.fillWidth: true }
                    CustomButton { iconSource: "qrc:/Icon/plus.svg" }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 60
                    spacing: 6

                    ProgressBar {
                        Layout.fillWidth: true
                        Layout.preferredHeight: parent.height / 8
                        Layout.alignment: Qt.AlignHCenter
                        duration: musicLoader.duration
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            id: currentTime
                            text: formatTime(musicLoader.position)
                            color: "white"
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignLeft
                        }
                        Text {
                            id: totalTime
                            text: formatTime(musicLoader.duration)
                            color: "white"
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignRight
                        }
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    spacing: 0

                    Item { Layout.fillWidth: true }

                    CustomButton {
                        id: shuffle
                        iconSource: "qrc:/Icon/shuffle.svg"
                        property bool isShuffling: false
                        opacity: isShuffling ? 1 : 0.5
                        onClicked: {
                            isShuffling = !isShuffling
                            musicLoader.setShuffle(isShuffling)
                            if(isShuffling) {
                                replayButton.isReplay = false
                                musicLoader.setReplay(false)
                            }
                        }
                    }

                    CustomButton {
                        id: previousTrack
                        iconSource: "qrc:/Icon/next-track.svg"
                        rotation: 180
                        onClicked: {
                            musicLoader.previousMusic()
                            playPause.isPlaying = true
                        }
                    }

                    CustomButton {
                        id: playPause
                        property bool isPlaying: true
                        iconSource: isPlaying ? "qrc:/Icon/pause.svg" : "qrc:/Icon/play.svg"
                        onClicked: {
                            isPlaying = !isPlaying
                            if(isPlaying) musicLoader.playMusic()
                            else musicLoader.pauseMusic()
                        }
                    }

                    CustomButton {
                        id: nextTrack
                        onClicked: {
                            musicLoader.nextMusic()
                            playPause.isPlaying = true
                        }
                        iconSource: "qrc:/Icon/next-track.svg"
                    }

                    CustomButton {
                        id: replayButton
                        iconSource: "qrc:/Icon/autoplay.svg"
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        property bool isReplay: false
                        opacity: isReplay ? 1 : 0.5
                        onClicked: {
                            isReplay = !isReplay
                            musicLoader.setReplay(isReplay)
                            if(isReplay) {
                                shuffle.isShuffling = false
                                musicLoader.setShuffle(false)
                            }
                        }
                    }

                    Item { Layout.fillWidth: true }
                }
            }

            Rectangle {
                id: volumeContainer
                width: 100
                height: 10
                color: "transparent"
                visible: false
                z: 10

                onVisibleChanged: {
                    if (visible) {
                        var pos = volumeBtn.mapToItem(controlSection, 0, volumeBtn.height)
                        x = pos.x + volumeBtn.width/2 - width/2
                        y = pos.y
                    }
                }

                VolumeBar {
                    anchors.fill: parent
                    rotation: -90
                    transformOrigin: Item.Center
                }
            }
        }
    }

    PlaylistView {
        id: playlistWindow
        musicLoader: musicLoader
        visible: false
    }
}
