import QtQuick
import QtQuick.Layouts
import QtQuick.Dialogs
import MusicLoader 1.0
import CustomImage 1.0

Window {
    id: root
    width: 640
    height: 280
    minimumWidth: 500
    minimumHeight: 260
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
        var totalSeconds = Math.max(0, Math.floor(ms / 1000))
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
                width: Math.min(parent.width * 0.85, parent.height * 0.85)
                height: width
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
                anchors.leftMargin: 16
                anchors.rightMargin: 16
                anchors.topMargin: 8
                anchors.bottomMargin: 8
                spacing: 0

                // 1. Top Toolbar Row
                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 44
                    Layout.fillHeight: false
                    spacing: 4

                    Item { Layout.fillWidth: true } // Pushes controls to the right

                    // YouTube-Style Expandable Volume Bar
                    VolumeBar {
                        id: volumeBar
                        musicLoader: musicLoader
                        Layout.alignment: Qt.AlignVCenter
                    }

                    CustomButton {
                        id: equalizerBtn
                        iconSource: "qrc:/Icon/equalizer.svg"
                        iconSize: 20
                        Layout.preferredWidth: 38
                        Layout.preferredHeight: 38
                        onClicked: equalizerWindow.toggle()
                    }

                    CustomButton {
                        id: moreBtn
                        iconSource: "qrc:/Icon/threedotvertical.svg"
                        iconSize: 20
                        Layout.preferredWidth: 38
                        Layout.preferredHeight: 38
                        onClicked: moreMenu.toggle(moreBtn, controlSection)
                    }
                }

                Item { Layout.fillHeight: true }

                // 2. Song Title & Artist
                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 65
                    Layout.fillHeight: false
                    spacing: 4

                    Text {
                        id: songName
                        text: musicLoader.currentTitle
                        color: "white"
                        font.pixelSize: Math.min(30, Math.max(20, root.width * 0.035))
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                    }

                    Text {
                        id: artistName
                        text: musicLoader.currentArtist
                        color: "lightgrey"
                        font.pixelSize: Math.min(18, Math.max(13, root.width * 0.022))
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                    }
                }

                Item { Layout.fillHeight: true }

                // 3. Action Row (Playlist, Heart/Favorite, Plus/Add File)
                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 38
                    Layout.fillHeight: false

                    CustomButton {
                        id: playlistBtn
                        iconSource: "qrc:/Icon/playlist.svg"
                        iconSize: 22
                        Layout.preferredWidth: 38
                        Layout.preferredHeight: 38
                        onClicked: playlistWindow.toggle()
                    }

                    Item { Layout.fillWidth: true }

                    // Heart / Favorite Song Button
                    CustomButton {
                        id: heartBtn
                        iconSource: (musicLoader && musicLoader.isCurrentFavorite) ? "qrc:/Icon/heart-filled.svg" : "qrc:/Icon/heart.svg"
                        iconSize: 22
                        Layout.preferredWidth: 38
                        Layout.preferredHeight: 38
                        scale: (musicLoader && musicLoader.isCurrentFavorite) ? 1.15 : 1.0
                        Behavior on scale {
                            NumberAnimation { duration: 150; easing.type: Easing.OutBack }
                        }
                        onClicked: {
                            if (musicLoader) musicLoader.toggleCurrentFavorite()
                        }
                    }

                    Item { Layout.fillWidth: true }

                    // Plus / Add Music File Button
                    CustomButton {
                        id: plusBtn
                        iconSource: "qrc:/Icon/plus.svg"
                        iconSize: 22
                        Layout.preferredWidth: 38
                        Layout.preferredHeight: 38
                        onClicked: addMusicDialog.open()
                    }
                }

                Item { Layout.fillHeight: true }

                // 4. Seek Progress Bar & Time
                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 46
                    Layout.fillHeight: false
                    spacing: 4

                    ProgressBar {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 18
                        Layout.alignment: Qt.AlignHCenter
                        duration: musicLoader.duration
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Text {
                            id: currentTime
                            text: formatTime(musicLoader.position)
                            color: "white"
                            font.pixelSize: 11
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignLeft
                        }
                        Text {
                            id: totalTime
                            text: formatTime(musicLoader.duration)
                            color: "white"
                            font.pixelSize: 11
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignRight
                        }
                    }
                }

                Item { Layout.fillHeight: true }

                // 5. Bottom Playback Controls (Shuffle, Prev, Play/Pause, Next, Replay)
                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 48
                    Layout.fillHeight: false
                    spacing: 12
                    Layout.alignment: Qt.AlignHCenter

                    Item { Layout.fillWidth: true }

                    CustomButton {
                        id: shuffle
                        iconSource: "qrc:/Icon/shuffle.svg"
                        iconSize: 20
                        Layout.preferredWidth: 36
                        Layout.preferredHeight: 36
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
                        iconRotation: 180
                        iconSize: 22
                        Layout.preferredWidth: 38
                        Layout.preferredHeight: 38
                        onClicked: {
                            musicLoader.previousMusic()
                            playPause.isPlaying = true
                        }
                    }

                    CustomButton {
                        id: playPause
                        property bool isPlaying: true
                        iconSource: isPlaying ? "qrc:/Icon/pause.svg" : "qrc:/Icon/play.svg"
                        iconSize: 26
                        Layout.preferredWidth: 46
                        Layout.preferredHeight: 46
                        onClicked: {
                            isPlaying = !isPlaying
                            if(isPlaying) musicLoader.playMusic()
                            else musicLoader.pauseMusic()
                        }
                    }

                    CustomButton {
                        id: nextTrack
                        iconSource: "qrc:/Icon/next-track.svg"
                        iconSize: 22
                        Layout.preferredWidth: 38
                        Layout.preferredHeight: 38
                        onClicked: {
                            musicLoader.nextMusic()
                            playPause.isPlaying = true
                        }
                    }

                    CustomButton {
                        id: replayButton
                        iconSource: "qrc:/Icon/autoplay.svg"
                        iconSize: 20
                        Layout.preferredWidth: 36
                        Layout.preferredHeight: 36
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

                Item { Layout.preferredHeight: 4 }
            }

            // More Options Menu Popup
            MoreMenu {
                id: moreMenu
                musicLoader: musicLoader
                z: 100
            }
        }
    }

    // Windows & Dialogs
    PlaylistView {
        id: playlistWindow
        musicLoader: musicLoader
        visible: false
    }

    EqualizerView {
        id: equalizerWindow
        musicLoader: musicLoader
        visible: false
    }

    SongInfoDialog {
        id: songInfoDialog
        musicLoader: musicLoader
        visible: false
    }

    FileDialog {
        id: addMusicDialog
        title: "Select Audio Files"
        fileMode: FileDialog.OpenFiles
        nameFilters: ["Audio Files (*.mp3 *.wav *.flac *.m4a *.aac *.ogg)", "All Files (*)"]
        onAccepted: {
            for (var i = 0; i < selectedFiles.length; i++) {
                musicLoader.addMusicFile(selectedFiles[i])
            }
        }
    }

    KeyboardFunction {
        id: keyboardHandler
        musicLoader: musicLoader
        playlistWindow: playlistWindow
        equalizerWindow: equalizerWindow
        volumeBar: volumeBar
        focus: true
        Component.onCompleted: forceActiveFocus()
    }
}
