import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: rootButton
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: "transparent"
    radius: Math.min(width, height) / 2

    property alias iconSource: icon.source
    signal clicked()

    Image {
        id: icon
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        width: parent.width * 0.6
        height: parent.height * 0.6
        opacity: controlArea.pressed ? 0.6 : 1.0
    }

    MouseArea {
        id: controlArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: rootButton.clicked()
    }
}
