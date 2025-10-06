import QtQuick

Item {
    width: 120
    height: 20
    property real volume: musicLoader.volume
    property bool dragging: false

    Rectangle {
        anchors.fill: parent
        color: "lightgray"
        radius: height / 2
    }

    Rectangle {
        width: parent.width * volume
        height: parent.height
        color: "blue"
        radius: height / 2

        Behavior on width {
            NumberAnimation { duration: 10; easing.type: Easing.InOutQuad }
        }
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        function updateVolume(x) {
            volume = Math.max(0, Math.min(1, x / width))
            musicLoader.setVolume(volume)
        }

        onPressed: {
            dragging = true
            updateVolume(mouseX)
        }
        onPositionChanged: if (dragging) updateVolume(mouseX)
        onReleased: dragging = false
        onClicked: updateVolume(mouseX)
    }

    Connections {
        target: musicLoader
        function onVolumeChanged(vol) {
            if (!dragging) volume = vol
        }
    }
}
