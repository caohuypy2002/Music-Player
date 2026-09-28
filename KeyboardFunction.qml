import QtQuick
import QtQuick.Controls

Item {
    id: keyboardHandlerItem
    property var musicLoader
    property var playlistWindow
    property var equalizerWindow
    property var volumeBar
    focus: true
    property bool isPlaying: false

    Connections {
        target: musicLoader
        function onPlayStateChanged(isPlaying) {
            keyboardHandlerItem.isPlaying = isPlaying
        }
    }

    Keys.onPressed: (event) => {
        switch (event.key) {
        case Qt.Key_Space:
            if (musicLoader && musicLoader.playing) {
                musicLoader.pauseMusic()
            } else if (musicLoader) {
                musicLoader.playMusic()
            }
            event.accepted = true
            break
        case Qt.Key_Right:
            if (musicLoader) musicLoader.nextMusic()
            event.accepted = true
            break
        case Qt.Key_Left:
            if (musicLoader) musicLoader.previousMusic()
            event.accepted = true
            break
        case Qt.Key_Up:
            if (musicLoader) musicLoader.setVolume(Math.min(musicLoader.volume + 0.05, 1.0))
            event.accepted = true
            break
        case Qt.Key_Down:
            if (musicLoader) musicLoader.setVolume(Math.max(musicLoader.volume - 0.05, 0.0))
            event.accepted = true
            break
        case Qt.Key_M:
            if (volumeBar) {
                volumeBar.toggleMute()
            } else if (musicLoader) {
                musicLoader.setVolume(musicLoader.volume > 0 ? 0 : 0.5)
            }
            event.accepted = true
            break
        case Qt.Key_F:
        case Qt.Key_L:
            if (musicLoader) musicLoader.toggleCurrentFavorite()
            event.accepted = true
            break
        case Qt.Key_P:
            if (playlistWindow) playlistWindow.toggle()
            event.accepted = true
            break
        case Qt.Key_E:
            if (equalizerWindow) equalizerWindow.toggle()
            event.accepted = true
            break
        }
    }
}
