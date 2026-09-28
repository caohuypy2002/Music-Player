import QtQuick 2.15

Item {
    id: rootProgress
    width: 300
    height: 20

    property real progress: 0.0
    property int position: 0
    property int duration: 1
    property bool dragging: false
    property real hoverX: 0
    property bool isHovered: false

    function formatTime(ms) {
        var totalSeconds = Math.max(0, Math.floor(ms / 1000))
        var minutes = Math.floor(totalSeconds / 60)
        var seconds = totalSeconds % 60
        return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
    }

    // YouTube-style Floating Time Preview Bubble
    Rectangle {
        id: timePreview
        visible: (rootProgress.isHovered || rootProgress.dragging) && rootProgress.duration > 0
        width: previewText.implicitWidth + 12
        height: 20
        radius: 4
        color: "#dd1c0e1e"
        border.color: "#50ffffff"
        border.width: 1
        anchors.bottom: trackBg.top
        anchors.bottomMargin: 8
        x: Math.max(0, Math.min(rootProgress.width - width, rootProgress.hoverX - width / 2))
        z: 20

        Text {
            id: previewText
            anchors.centerIn: parent
            text: {
                if (rootProgress.width <= 0 || rootProgress.duration <= 0) return "0:00"
                var ratio = Math.max(0, Math.min(1, rootProgress.hoverX / rootProgress.width))
                return formatTime(ratio * rootProgress.duration)
            }
            color: "white"
            font.pixelSize: 11
            font.bold: true
        }
    }

    // Track Background
    Rectangle {
        id: trackBg
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        height: (rootProgress.isHovered || rootProgress.dragging) ? 6 : 4
        radius: height / 2
        color: "#40ffffff"

        Behavior on height {
            NumberAnimation { duration: 100 }
        }

        // Ghost Hover Bar (YouTube style)
        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: rootProgress.isHovered ? Math.max(0, Math.min(parent.width, rootProgress.hoverX)) : 0
            radius: height / 2
            color: "#30ffffff"
            visible: rootProgress.isHovered
        }

        // Active Progress Bar
        Rectangle {
            id: progressBar
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width * Math.max(0, Math.min(1, rootProgress.progress))
            color: "#3a86ff"
            radius: height / 2

            Behavior on width {
                enabled: !rootProgress.dragging
                NumberAnimation { duration: 100; easing.type: Easing.OutQuad }
            }
        }

        // Thumb Knob (Appears on Hover / Drag)
        Rectangle {
            id: thumb
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: progressBar.right
            width: (rootProgress.isHovered || rootProgress.dragging) ? 14 : 0
            height: width
            radius: width / 2
            color: "#ffffff"
            visible: width > 0

            Behavior on width {
                NumberAnimation { duration: 100 }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        anchors.topMargin: -8
        anchors.bottomMargin: -8
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        function updateProgress(x) {
            progress = Math.max(0, Math.min(1, x / width))
        }

        onPositionChanged: (mouse) => {
            rootProgress.hoverX = mouse.x
            if (rootProgress.dragging) {
                updateProgress(mouse.x)
            }
        }

        onEntered: {
            rootProgress.isHovered = true
        }

        onExited: {
            rootProgress.isHovered = false
        }

        onPressed: (mouse) => {
            rootProgress.dragging = true
            rootProgress.hoverX = mouse.x
            updateProgress(mouse.x)
        }

        onReleased: (mouse) => {
            if (rootProgress.dragging) {
                rootProgress.dragging = false
                if (duration > 0) {
                    var newPos = progress * duration
                    musicLoader.setPosition(newPos)
                    position = newPos
                }
            }
        }

        onClicked: (mouse) => {
            updateProgress(mouse.x)
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
