import QtQuick
import QtQuick.Controls

Item {
    id: rootVolume
    property var musicLoader
    property bool isDragging: false
    property bool isHovered: false
    property real lastNonZeroVolume: 0.5
    readonly property bool isExpanded: isHovered || isDragging

    implicitWidth: sliderContainer.width + speakerBtn.width
    implicitHeight: 40

    Timer {
        id: collapseTimer
        interval: 350
        repeat: false
        onTriggered: {
            if (!isDragging) {
                isHovered = false
            }
        }
    }

    function toggleMute() {
        if (!musicLoader) return
        if (musicLoader.volume > 0) {
            lastNonZeroVolume = musicLoader.volume
            musicLoader.setVolume(0)
        } else {
            musicLoader.setVolume(lastNonZeroVolume > 0 ? lastNonZeroVolume : 0.5)
        }
    }

    Row {
        anchors.verticalCenter: parent.verticalCenter
        spacing: 4

        // 1. YouTube-style Expandable Horizontal Slider
        Item {
            id: sliderContainer
            width: rootVolume.isExpanded ? 76 : 0
            height: 36
            clip: false
            opacity: rootVolume.isExpanded ? 1.0 : 0.0
            visible: width > 0

            Behavior on width {
                NumberAnimation { duration: 180; easing.type: Easing.OutQuad }
            }
            Behavior on opacity {
                NumberAnimation { duration: 150 }
            }

            // Floating Tooltip %
            Rectangle {
                id: tooltip
                anchors.bottom: trackBg.top
                anchors.bottomMargin: 8
                anchors.horizontalCenter: thumb.horizontalCenter
                width: tooltipText.implicitWidth + 10
                height: 18
                radius: 4
                color: "#dd1e1022"
                border.color: "#40ffffff"
                border.width: 1
                visible: rootVolume.isExpanded
                z: 10

                Text {
                    id: tooltipText
                    anchors.centerIn: parent
                    text: musicLoader ? Math.round(musicLoader.volume * 100) + "%" : "0%"
                    color: "white"
                    font.pixelSize: 10
                    font.bold: true
                }
            }

            // Slider Track
            Rectangle {
                id: trackBg
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                height: 4
                radius: 2
                color: "#50ffffff"

                // Active Volume Level
                Rectangle {
                    id: trackFill
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    width: parent.width * (musicLoader ? Math.max(0, Math.min(1, musicLoader.volume)) : 0)
                    radius: 2
                    color: "#ffffff"

                    Behavior on width {
                        enabled: !rootVolume.isDragging
                        NumberAnimation { duration: 80; easing.type: Easing.OutQuad }
                    }
                }

                // Thumb Knob
                Rectangle {
                    id: thumb
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: trackFill.right
                    width: sliderMouseArea.containsMouse || rootVolume.isDragging ? 12 : 8
                    height: width
                    radius: width / 2
                    color: "#ffffff"

                    Behavior on width {
                        NumberAnimation { duration: 100 }
                    }
                }
            }

            // Mouse interaction for the slider
            MouseArea {
                id: sliderMouseArea
                anchors.fill: parent
                anchors.topMargin: -8
                anchors.bottomMargin: -8
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor

                function updateVolumeFromMouse(mouseX) {
                    if (!musicLoader || sliderContainer.width <= 0) return
                    var clampedX = Math.max(0, Math.min(sliderContainer.width, mouseX))
                    var newVol = clampedX / sliderContainer.width
                    musicLoader.setVolume(newVol)
                }

                onPressed: (mouse) => {
                    collapseTimer.stop()
                    rootVolume.isDragging = true
                    updateVolumeFromMouse(mouse.x)
                }
                onPositionChanged: (mouse) => {
                    if (rootVolume.isDragging) {
                        collapseTimer.stop()
                        updateVolumeFromMouse(mouse.x)
                    }
                }
                onReleased: {
                    rootVolume.isDragging = false
                    if (!containsMouse && !speakerBtnArea.containsMouse) {
                        collapseTimer.restart()
                    }
                }
                onEntered: {
                    collapseTimer.stop()
                    rootVolume.isHovered = true
                }
                onExited: {
                    if (!rootVolume.isDragging && !speakerBtnArea.containsMouse) {
                        collapseTimer.restart()
                    }
                }
                onWheel: (wheel) => {
                    if (!musicLoader) return
                    collapseTimer.stop()
                    rootVolume.isHovered = true
                    var step = wheel.angleDelta.y > 0 ? 0.05 : -0.05
                    musicLoader.setVolume(Math.max(0.0, Math.min(1.0, musicLoader.volume + step)))
                    collapseTimer.restart()
                }
            }
        }

        // 2. Speaker Button (Click to Mute, Hover to Expand)
        Rectangle {
            id: speakerBtn
            width: 36
            height: 36
            radius: 18
            color: speakerBtnArea.containsMouse ? "#20ffffff" : "transparent"

            Behavior on color {
                ColorAnimation { duration: 120 }
            }

            Image {
                id: speakerIcon
                anchors.centerIn: parent
                width: 22
                height: 22
                fillMode: Image.PreserveAspectFit
                source: (musicLoader && musicLoader.volume > 0) ? "qrc:/Icon/volume.svg" : "qrc:/Icon/mute.png"
                opacity: speakerBtnArea.pressed ? 0.6 : 1.0
            }

            MouseArea {
                id: speakerBtnArea
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor

                onEntered: {
                    collapseTimer.stop()
                    rootVolume.isHovered = true
                }
                onExited: {
                    if (!rootVolume.isDragging && !sliderMouseArea.containsMouse) {
                        collapseTimer.restart()
                    }
                }
                onClicked: {
                    rootVolume.toggleMute()
                    collapseTimer.stop()
                    rootVolume.isHovered = true
                    collapseTimer.restart()
                }
                onWheel: (wheel) => {
                    if (!musicLoader) return
                    collapseTimer.stop()
                    rootVolume.isHovered = true
                    var step = wheel.angleDelta.y > 0 ? 0.05 : -0.05
                    musicLoader.setVolume(Math.max(0.0, Math.min(1.0, musicLoader.volume + step)))
                    collapseTimer.restart()
                }
            }
        }
    }

    Connections {
        target: musicLoader
        function onVolumeChanged(vol) {
            if (vol > 0) {
                rootVolume.lastNonZeroVolume = vol
            }
        }
    }
}
