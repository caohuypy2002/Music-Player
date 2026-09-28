import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import CustomImage 1.0

Window {
    id: playlistWindow
    width: 380
    height: 480
    minimumWidth: 340
    minimumHeight: 380
    visible: false
    title: "Playlist"
    property var musicLoader
    property bool showOnlyFavorites: false

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

    Rectangle {
        anchors.fill: parent
        color: "#180918"

        Image {
            anchors.fill: parent
            source: "qrc:/Icon/rose-petals.svg"
            fillMode: Image.Stretch
            cache: false
            opacity: 0.8
        }

        // Overlay to soften background
        Rectangle {
            anchors.fill: parent
            color: "#65000000"
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 12
            spacing: 10

            // 1. Header Bar with robust Layout (prevents button overlapping)
            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 32
                spacing: 10

                Text {
                    text: showOnlyFavorites
                          ? "Favorites (" + (musicLoader ? musicLoader.favoriteCount : 0) + ")"
                          : "Playlist (" + (musicLoader ? musicLoader.playlist.length : 0) + ")"
                    color: "white"
                    font.pixelSize: 15
                    font.bold: true
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }

                // Filter Favorites Toggle Pill
                Rectangle {
                    id: favFilterPill
                    Layout.preferredWidth: favFilterRow.implicitWidth + 20
                    Layout.preferredHeight: 28
                    Layout.alignment: Qt.AlignVCenter
                    radius: 14
                    color: showOnlyFavorites ? "#ff4757" : (filterArea.containsMouse ? "#30ffffff" : "#18ffffff")
                    border.color: showOnlyFavorites ? "#ff6b81" : "#30ffffff"
                    border.width: 1

                    Behavior on color {
                        ColorAnimation { duration: 150 }
                    }

                    RowLayout {
                        id: favFilterRow
                        anchors.centerIn: parent
                        spacing: 5

                        Text {
                            text: showOnlyFavorites ? "❤️" : "🤍"
                            font.pixelSize: 11
                            verticalAlignment: Text.AlignVCenter
                        }

                        Text {
                            text: showOnlyFavorites ? "Favorites" : "All"
                            color: "white"
                            font.pixelSize: 11
                            font.bold: true
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    MouseArea {
                        id: filterArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: showOnlyFavorites = !showOnlyFavorites
                    }
                }

                // Close Button
                Rectangle {
                    Layout.preferredWidth: 28
                    Layout.preferredHeight: 28
                    Layout.alignment: Qt.AlignVCenter
                    radius: 14
                    color: closeArea.containsMouse ? "#40ffffff" : "#20ffffff"

                    Behavior on color {
                        ColorAnimation { duration: 120 }
                    }

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
                        onClicked: playlistWindow.visible = false
                    }
                }
            }

            // 2. Playlist Area with Empty State
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true

                // Empty State Overlay
                ColumnLayout {
                    anchors.centerIn: parent
                    visible: (showOnlyFavorites && musicLoader && musicLoader.favoriteCount === 0) ||
                             (!showOnlyFavorites && (!musicLoader || musicLoader.playlist.length === 0))
                    spacing: 8
                    z: 5

                    Text {
                        text: (!musicLoader || musicLoader.playlist.length === 0) ? "📂" : "💔"
                        font.pixelSize: 36
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: (!musicLoader || musicLoader.playlist.length === 0)
                              ? "Playlist is empty"
                              : "No favorites yet"
                        color: "white"
                        font.pixelSize: 14
                        font.bold: true
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: (!musicLoader || musicLoader.playlist.length === 0)
                              ? "Click the '+' button on the main player to add songs."
                              : "Click the heart icon on any song to add it to your favorites."
                        color: "#aaaaaa"
                        font.pixelSize: 11
                        Layout.alignment: Qt.AlignHCenter
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.WordWrap
                        Layout.maximumWidth: 240
                    }
                }

                // Playlist ListView
                ListView {
                    id: listView
                    anchors.fill: parent
                    model: musicLoader ? musicLoader.playlist : []
                    spacing: 5
                    clip: true

                    delegate: Rectangle {
                        id: rowCard
                        width: listView.width
                        radius: 8

                        // Fully reactive favorite status: explicitly reads favoriteRevision!
                        readonly property bool isFav: {
                            if (!musicLoader) return false
                            var _rev = musicLoader.favoriteRevision
                            return musicLoader.isFavorite(modelData)
                        }

                        visible: !showOnlyFavorites || isFav
                        height: visible ? 56 : 0

                        color: {
                            if (index === musicLoader.currentIndex) return "#403a86ff"
                            if (rowMouse.containsMouse) return "#25ffffff"
                            return "#15ffffff"
                        }
                        border.color: index === musicLoader.currentIndex ? "#60a5fa" : "transparent"
                        border.width: 1

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 8
                            anchors.rightMargin: 8
                            spacing: 8

                            // Track number or playing indicator
                            Text {
                                text: {
                                    if (index === musicLoader.currentIndex) {
                                        return musicLoader.playing ? "▶" : "❚❚"
                                    }
                                    return (index + 1)
                                }
                                color: index === musicLoader.currentIndex ? "#60a5fa" : "#888888"
                                font.pixelSize: 11
                                font.bold: true
                                Layout.preferredWidth: 20
                                horizontalAlignment: Text.AlignHCenter
                            }

                            // Album Art Thumbnail
                            Rectangle {
                                width: 40
                                height: 40
                                radius: 6
                                clip: true
                                color: "transparent"

                                CustomImage {
                                    anchors.fill: parent
                                    pixmap: musicLoader.getAlbumArt(modelData)
                                }
                            }

                            // Title & Artist
                            ColumnLayout {
                                spacing: 2
                                Layout.fillWidth: true
                                Layout.alignment: Qt.AlignVCenter

                                Text {
                                    text: musicLoader.getTitle(modelData)
                                    font.pixelSize: 13
                                    font.bold: index === musicLoader.currentIndex
                                    color: index === musicLoader.currentIndex ? "#ffffff" : "#eeeeee"
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }

                                Text {
                                    text: musicLoader.getArtist(modelData)
                                    font.pixelSize: 11
                                    color: "#aaaaaa"
                                    elide: Text.ElideRight
                                    Layout.fillWidth: true
                                }
                            }

                            // Heart (Favorite) Toggle for this song
                            Rectangle {
                                width: 28
                                height: 28
                                radius: 14
                                color: itemFavArea.containsMouse ? "#20ffffff" : "transparent"

                                Image {
                                    anchors.centerIn: parent
                                    width: 16
                                    height: 16
                                    fillMode: Image.PreserveAspectFit
                                    source: isFav ? "qrc:/Icon/heart-filled.svg" : "qrc:/Icon/heart.svg"
                                    opacity: isFav ? 1.0 : (itemFavArea.containsMouse ? 0.9 : 0.5)
                                    scale: isFav ? 1.15 : 1.0

                                    Behavior on scale {
                                        NumberAnimation { duration: 150; easing.type: Easing.OutBack }
                                    }
                                }

                                MouseArea {
                                    id: itemFavArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        if (musicLoader) musicLoader.toggleFavorite(modelData)
                                    }
                                }
                            }

                            // Delete Button (Remove from Playlist)
                            Rectangle {
                                width: 24
                                height: 24
                                radius: 12
                                color: delArea.containsMouse ? "#30ff4757" : "transparent"

                                Text {
                                    anchors.centerIn: parent
                                    text: "✕"
                                    color: delArea.containsMouse ? "#ff4757" : "#66ffffff"
                                    font.pixelSize: 11
                                }

                                MouseArea {
                                    id: delArea
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        if (musicLoader) musicLoader.removeMusicAt(index)
                                    }
                                }
                            }
                        }

                        // Click anywhere on row to play
                        MouseArea {
                            id: rowMouse
                            anchors.fill: parent
                            anchors.rightMargin: 64 // Don't cover favorite and delete buttons
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                if (musicLoader) {
                                    musicLoader.playAt(index)
                                }
                            }
                        }
                    }

                    Connections {
                        target: musicLoader
                        function onPlaylistChanged() {
                            listView.model = musicLoader.playlist
                        }
                        function onCurrentSongChanged() {
                            listView.forceLayout()
                        }
                        function onFavoriteChanged() {
                            // isFav will be re-evaluated automatically via favoriteRevision binding
                        }
                    }
                }
            }
        }
    }
}
