import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: rootButton
    implicitWidth: 38
    implicitHeight: 38
    Layout.preferredWidth: implicitWidth
    Layout.preferredHeight: implicitHeight
    Layout.fillWidth: false
    Layout.fillHeight: false

    property alias iconSource: icon.source
    property alias containsMouse: controlArea.containsMouse
    property real iconSize: 22
    property real iconRotation: 0

    signal clicked()
    signal entered()
    signal exited()
    signal wheel(var wheel)

    Rectangle {
        id: bgCircle
        anchors.fill: parent
        radius: Math.min(width, height) / 2
        color: controlArea.pressed ? "#40ffffff" : (controlArea.containsMouse ? "#20ffffff" : "transparent")

        Behavior on color {
            ColorAnimation { duration: 120 }
        }
    }

    Image {
        id: icon
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        width: rootButton.iconSize
        height: rootButton.iconSize
        rotation: rootButton.iconRotation
        opacity: controlArea.pressed ? 0.6 : (controlArea.containsMouse ? 0.85 : 1.0)

        Behavior on opacity {
            NumberAnimation { duration: 100 }
        }
    }

    MouseArea {
        id: controlArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: rootButton.clicked()
        onEntered: rootButton.entered()
        onExited: rootButton.exited()
        onWheel: (wheel) => rootButton.wheel(wheel)
    }
}
