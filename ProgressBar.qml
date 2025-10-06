import QtQuick 2.15

Item {
    width: 300
    height: 20

    property real progress: 0.0
    property int position: 0
    property int duration: 1
    property bool dragging: false

    Rectangle {
        anchors.fill: parent
        color: "lightgray"
        radius: height / 2
    }

    Rectangle {
        id: progressBar
        width: parent.width * progress
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

        function updateProgress(x) {
            progress = Math.max(0, Math.min(1, x / width))
        }

        onPressed: {
            dragging = true
            updateProgress(mouseX)
        }

        onPositionChanged: {
            if (dragging) updateProgress(mouseX)
        }

        onReleased: {
            if (dragging) {
                dragging = false
                if (duration > 0) {
                    var newPos = progress * duration
                    musicLoader.setPosition(newPos)
                    position = newPos
                }
            }
        }

        onClicked: {
            updateProgress(mouseX)
            if (duration > 0) {
                var newPos = progress * duration
                musicLoader.setPosition(newPos)
                position = newPos
            }
        }
    }

    Connections {
        target: musicLoader
        function onPositionChanged(pos) {
            position = pos
            if (!dragging) {
                progress = duration > 0 ? position / duration : 0
            }
        }

        function onResetProgress() {
            position = 0
            progress = 0
        }
    }
}
