import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: eqWindow
    width: 360
    height: 380
    minimumWidth: 360
    minimumHeight: 380
    maximumWidth: 360
    maximumHeight: 380
    visible: false
    title: "Equalizer & Audio FX"
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

    function toggle() {
        if (visible) close()
        else open()
    }

    // Presets data
    property var presets: [
        { name: "Flat", values: [0, 0, 0, 0, 0] },
        { name: "Bass Boost", values: [8, 6, 2, 0, -1] },
        { name: "Rock", values: [5, 3, -1, 4, 6] },
        { name: "Pop", values: [-1, 2, 5, 3, -2] },
        { name: "Vocal", values: [-2, 1, 6, 4, 1] },
        { name: "Electronic", values: [6, 4, 0, 3, 7] }
    ]
    property int currentPresetIndex: 0

    // Band frequencies
    readonly property var bands: [
        { label: "60Hz", desc: "Sub" },
        { label: "230Hz", desc: "Bass" },
        { label: "910Hz", desc: "Mid" },
        { label: "3.6kHz", desc: "High" },
        { label: "14kHz", desc: "Treble" }
    ]

    property var bandValues: [0, 0, 0, 0, 0]

    function applyPreset(index) {
        currentPresetIndex = index
        var targetVals = presets[index].values
        bandValues = targetVals.slice()
    }

    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#281026" }
            GradientStop { position: 1.0; color: "#120815" }
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            // Header
            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: "Equalizer & Audio FX"
                    color: "white"
                    font.pixelSize: 16
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
                        onClicked: eqWindow.visible = false
                    }
                }
            }

            // Animated Visualizer Spectrum (Dancing Bars)
            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 46
                color: "#20000000"
                radius: 8
                border.color: "#25ffffff"
                border.width: 1

                Row {
                    anchors.centerIn: parent
                    spacing: 8

                    Repeater {
                        model: 12
                        Rectangle {
                            id: bar
                            width: 12
                            anchors.bottom: parent.bottom
                            radius: 3
                            color: "#3a86ff"

                            property real randomHeight: 8
                            height: (musicLoader && musicLoader.playing) ? randomHeight : 6

                            Behavior on height {
                                NumberAnimation { duration: 120; easing.type: Easing.OutQuad }
                            }
                        }
                    }

                    Timer {
                        interval: 120
                        running: eqWindow.visible && musicLoader && musicLoader.playing
                        repeat: true
                        onTriggered: {
                            for (var i = 0; i < parent.children.length - 1; i++) {
                                var child = parent.children[i]
                                if (child && child.randomHeight !== undefined) {
                                    child.randomHeight = 6 + Math.random() * 32
                                }
                            }
                        }
                    }
                }
            }

            // Preset Pills
            Text {
                text: "PRESETS"
                color: "#aaaaaa"
                font.pixelSize: 10
                font.bold: true
                font.letterSpacing: 1
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 6

                Repeater {
                    model: presets
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 28
                        radius: 14
                        color: currentPresetIndex === index ? "#3a86ff" : (presetArea.containsMouse ? "#30ffffff" : "#18ffffff")
                        border.color: currentPresetIndex === index ? "#60a5fa" : "#30ffffff"
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: modelData.name
                            color: "white"
                            font.pixelSize: 10
                            font.bold: currentPresetIndex === index
                        }

                        MouseArea {
                            id: presetArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: applyPreset(index)
                        }
                    }
                }
            }

            // Frequency Sliders
            Item { Layout.preferredHeight: 4 }

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 8

                Repeater {
                    model: bands

                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 4

                        // dB value
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            text: (bandValues[index] > 0 ? "+" : "") + Math.round(bandValues[index]) + "dB"
                            color: bandValues[index] !== 0 ? "#60a5fa" : "#888888"
                            font.pixelSize: 10
                            font.bold: true
                        }

                        // Slider Track
                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            // Center 0dB dashed line
                            Rectangle {
                                anchors.centerIn: parent
                                width: parent.width * 0.6
                                height: 1
                                color: "#40ffffff"
                            }

                            // Vertical track
                            Rectangle {
                                id: sliderTrack
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: 4
                                height: parent.height - 16
                                anchors.verticalCenter: parent.verticalCenter
                                radius: 2
                                color: "#30ffffff"

                                Rectangle {
                                    id: sliderThumb
                                    width: 14
                                    height: 14
                                    radius: 7
                                    color: "white"
                                    border.color: "#3a86ff"
                                    border.width: 2
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    // Y map from -12..+12 to parent.height..0
                                    y: {
                                        var ratio = 1.0 - ((bandValues[index] + 12) / 24)
                                        return ratio * (parent.height - height)
                                    }

                                    Behavior on y {
                                        NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
                                    }
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                function updateValue(mouseY) {
                                    currentPresetIndex = -1 // custom
                                    var trackH = sliderTrack.height - 14
                                    var relY = mouseY - (parent.height - sliderTrack.height) / 2
                                    var clamped = Math.max(0, Math.min(trackH, relY))
                                    var ratio = 1.0 - (clamped / trackH) // 0..1
                                    var db = -12 + ratio * 24
                                    var newVals = bandValues.slice()
                                    newVals[index] = Math.round(db)
                                    bandValues = newVals
                                }
                                onPressed: (mouse) => updateValue(mouse.y)
                                onPositionChanged: (mouse) => { if (pressed) updateValue(mouse.y) }
                            }
                        }

                        // Frequency label
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            text: modelData.label
                            color: "white"
                            font.pixelSize: 10
                            font.bold: true
                        }
                    }
                }
            }

            // Bottom Actions (Reset)
            RowLayout {
                Layout.fillWidth: true
                Item { Layout.fillWidth: true }
                Rectangle {
                    width: 90
                    height: 28
                    radius: 14
                    color: resetArea.containsMouse ? "#3a86ff" : "#25ffffff"
                    Text {
                        anchors.centerIn: parent
                        text: "Reset (0 dB)"
                        color: "white"
                        font.pixelSize: 11
                    }
                    MouseArea {
                        id: resetArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: applyPreset(0)
                    }
                }
                Item { Layout.fillWidth: true }
            }
        }
    }
}
