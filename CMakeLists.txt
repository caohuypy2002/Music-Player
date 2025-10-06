cmake_minimum_required(VERSION 3.16)

project(ASSIGMENT_MusicPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)
find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia)
find_package(Qt6 REQUIRED COMPONENTS Core Multimedia)
find_package(Qt6 REQUIRED COMPONENTS Core)


qt_add_executable(appASSIGMENT_MusicPlayer
    main.cpp
)

qt_add_qml_module(appASSIGMENT_MusicPlayer
    URI ASSIGMENT_MusicPlayer
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES
        QML_FILES CustomButton.qml
        QML_FILES ProgressBar.qml
        RESOURCES
        RESOURCES
        RESOURCES Icon/vinyl.png Icon/rose-petals.svg Icon/autoplay.svg Icon/equalizer.svg Icon/heart.svg Icon/next-track.svg Icon/pause.svg Icon/play.svg Icon/playlist.svg Icon/plus.svg Icon/repeat.svg Icon/shuffle.svg Icon/threedotvertical.svg Icon/volume.svg
        RESOURCES Resource.qrc
        SOURCES musicloader.h musicloader.cpp
        RESOURCES
        QML_FILES VolumeBar.qml
        SOURCES
        SOURCES
        SOURCES
        SOURCES customimage.h customimage.cpp
        QML_FILES PlaylistView.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appASSIGMENT_MusicPlayer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appASSIGMENT_MusicPlayer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appASSIGMENT_MusicPlayer
    PRIVATE Qt6::Quick Qt6::Multimedia
)
target_link_libraries(appASSIGMENT_MusicPlayer PRIVATE Qt6::Core Qt6::Multimedia
)
target_link_libraries(appASSIGMENT_MusicPlayer PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appASSIGMENT_MusicPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
