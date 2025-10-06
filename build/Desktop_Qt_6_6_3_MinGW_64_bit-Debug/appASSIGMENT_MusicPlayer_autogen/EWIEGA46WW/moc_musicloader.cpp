/****************************************************************************
** Meta object code from reading C++ file 'musicloader.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../musicloader.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMusicLoaderENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMusicLoaderENDCLASS = QtMocHelpers::stringData(
    "MusicLoader",
    "musicLoadDone",
    "",
    "QStringList&",
    "musicFiles",
    "positionChanged",
    "durationChanged",
    "resetProgress",
    "currentSongChanged",
    "replayChanged",
    "shuffleChanged",
    "volumeChanged",
    "albumArtChanged",
    "playlistChanged",
    "playStateChanged",
    "isPlaying",
    "loadMusicIntoPlayer",
    "handleMediaStatusChanged",
    "QMediaPlayer::MediaStatus",
    "status",
    "playMusic",
    "pauseMusic",
    "nextMusic",
    "previousMusic",
    "playAt",
    "index",
    "getTitle",
    "file",
    "getArtist",
    "getAlbumArt",
    "setReplay",
    "value",
    "setShuffle",
    "setVolume",
    "vol",
    "setPosition",
    "pos",
    "playlist",
    "currentIndex",
    "position",
    "duration",
    "isReplay",
    "isShuffle",
    "volume",
    "currentTitle",
    "currentArtist",
    "albumArt"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMusicLoaderENDCLASS_t {
    uint offsetsAndSizes[94];
    char stringdata0[12];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[11];
    char stringdata5[16];
    char stringdata6[16];
    char stringdata7[14];
    char stringdata8[19];
    char stringdata9[14];
    char stringdata10[15];
    char stringdata11[14];
    char stringdata12[16];
    char stringdata13[16];
    char stringdata14[17];
    char stringdata15[10];
    char stringdata16[20];
    char stringdata17[25];
    char stringdata18[26];
    char stringdata19[7];
    char stringdata20[10];
    char stringdata21[11];
    char stringdata22[10];
    char stringdata23[14];
    char stringdata24[7];
    char stringdata25[6];
    char stringdata26[9];
    char stringdata27[5];
    char stringdata28[10];
    char stringdata29[12];
    char stringdata30[10];
    char stringdata31[6];
    char stringdata32[11];
    char stringdata33[10];
    char stringdata34[4];
    char stringdata35[12];
    char stringdata36[4];
    char stringdata37[9];
    char stringdata38[13];
    char stringdata39[9];
    char stringdata40[9];
    char stringdata41[9];
    char stringdata42[10];
    char stringdata43[7];
    char stringdata44[13];
    char stringdata45[14];
    char stringdata46[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMusicLoaderENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMusicLoaderENDCLASS_t qt_meta_stringdata_CLASSMusicLoaderENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "MusicLoader"
        QT_MOC_LITERAL(12, 13),  // "musicLoadDone"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 12),  // "QStringList&"
        QT_MOC_LITERAL(40, 10),  // "musicFiles"
        QT_MOC_LITERAL(51, 15),  // "positionChanged"
        QT_MOC_LITERAL(67, 15),  // "durationChanged"
        QT_MOC_LITERAL(83, 13),  // "resetProgress"
        QT_MOC_LITERAL(97, 18),  // "currentSongChanged"
        QT_MOC_LITERAL(116, 13),  // "replayChanged"
        QT_MOC_LITERAL(130, 14),  // "shuffleChanged"
        QT_MOC_LITERAL(145, 13),  // "volumeChanged"
        QT_MOC_LITERAL(159, 15),  // "albumArtChanged"
        QT_MOC_LITERAL(175, 15),  // "playlistChanged"
        QT_MOC_LITERAL(191, 16),  // "playStateChanged"
        QT_MOC_LITERAL(208, 9),  // "isPlaying"
        QT_MOC_LITERAL(218, 19),  // "loadMusicIntoPlayer"
        QT_MOC_LITERAL(238, 24),  // "handleMediaStatusChanged"
        QT_MOC_LITERAL(263, 25),  // "QMediaPlayer::MediaStatus"
        QT_MOC_LITERAL(289, 6),  // "status"
        QT_MOC_LITERAL(296, 9),  // "playMusic"
        QT_MOC_LITERAL(306, 10),  // "pauseMusic"
        QT_MOC_LITERAL(317, 9),  // "nextMusic"
        QT_MOC_LITERAL(327, 13),  // "previousMusic"
        QT_MOC_LITERAL(341, 6),  // "playAt"
        QT_MOC_LITERAL(348, 5),  // "index"
        QT_MOC_LITERAL(354, 8),  // "getTitle"
        QT_MOC_LITERAL(363, 4),  // "file"
        QT_MOC_LITERAL(368, 9),  // "getArtist"
        QT_MOC_LITERAL(378, 11),  // "getAlbumArt"
        QT_MOC_LITERAL(390, 9),  // "setReplay"
        QT_MOC_LITERAL(400, 5),  // "value"
        QT_MOC_LITERAL(406, 10),  // "setShuffle"
        QT_MOC_LITERAL(417, 9),  // "setVolume"
        QT_MOC_LITERAL(427, 3),  // "vol"
        QT_MOC_LITERAL(431, 11),  // "setPosition"
        QT_MOC_LITERAL(443, 3),  // "pos"
        QT_MOC_LITERAL(447, 8),  // "playlist"
        QT_MOC_LITERAL(456, 12),  // "currentIndex"
        QT_MOC_LITERAL(469, 8),  // "position"
        QT_MOC_LITERAL(478, 8),  // "duration"
        QT_MOC_LITERAL(487, 8),  // "isReplay"
        QT_MOC_LITERAL(496, 9),  // "isShuffle"
        QT_MOC_LITERAL(506, 6),  // "volume"
        QT_MOC_LITERAL(513, 12),  // "currentTitle"
        QT_MOC_LITERAL(526, 13),  // "currentArtist"
        QT_MOC_LITERAL(540, 8)   // "albumArt"
    },
    "MusicLoader",
    "musicLoadDone",
    "",
    "QStringList&",
    "musicFiles",
    "positionChanged",
    "durationChanged",
    "resetProgress",
    "currentSongChanged",
    "replayChanged",
    "shuffleChanged",
    "volumeChanged",
    "albumArtChanged",
    "playlistChanged",
    "playStateChanged",
    "isPlaying",
    "loadMusicIntoPlayer",
    "handleMediaStatusChanged",
    "QMediaPlayer::MediaStatus",
    "status",
    "playMusic",
    "pauseMusic",
    "nextMusic",
    "previousMusic",
    "playAt",
    "index",
    "getTitle",
    "file",
    "getArtist",
    "getAlbumArt",
    "setReplay",
    "value",
    "setShuffle",
    "setVolume",
    "vol",
    "setPosition",
    "pos",
    "playlist",
    "currentIndex",
    "position",
    "duration",
    "isReplay",
    "isShuffle",
    "volume",
    "currentTitle",
    "currentArtist",
    "albumArt"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMusicLoaderENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
      10,  221, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  164,    2, 0x06,   11 /* Public */,
       5,    1,  167,    2, 0x06,   13 /* Public */,
       6,    1,  170,    2, 0x06,   15 /* Public */,
       7,    0,  173,    2, 0x06,   17 /* Public */,
       8,    0,  174,    2, 0x06,   18 /* Public */,
       9,    0,  175,    2, 0x06,   19 /* Public */,
      10,    0,  176,    2, 0x06,   20 /* Public */,
      11,    1,  177,    2, 0x06,   21 /* Public */,
      12,    1,  180,    2, 0x06,   23 /* Public */,
      13,    0,  183,    2, 0x06,   25 /* Public */,
      14,    1,  184,    2, 0x06,   26 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    1,  187,    2, 0x08,   28 /* Private */,
      17,    1,  190,    2, 0x08,   30 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      20,    0,  193,    2, 0x02,   32 /* Public */,
      21,    0,  194,    2, 0x02,   33 /* Public */,
      22,    0,  195,    2, 0x02,   34 /* Public */,
      23,    0,  196,    2, 0x02,   35 /* Public */,
      24,    1,  197,    2, 0x02,   36 /* Public */,
      26,    1,  200,    2, 0x102,   38 /* Public | MethodIsConst  */,
      28,    1,  203,    2, 0x102,   40 /* Public | MethodIsConst  */,
      29,    1,  206,    2, 0x102,   42 /* Public | MethodIsConst  */,
      30,    1,  209,    2, 0x02,   44 /* Public */,
      32,    1,  212,    2, 0x02,   46 /* Public */,
      33,    1,  215,    2, 0x02,   48 /* Public */,
      35,    1,  218,    2, 0x02,   50 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 18,   19,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::QString, QMetaType::QString,   27,
    QMetaType::QString, QMetaType::QString,   27,
    QMetaType::QPixmap, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::QReal,   34,
    QMetaType::Void, QMetaType::LongLong,   36,

 // properties: name, type, flags
      37, QMetaType::QStringList, 0x00015001, uint(9), 0,
      38, QMetaType::Int, 0x00015001, uint(4), 0,
      39, QMetaType::LongLong, 0x00015001, uint(1), 0,
      40, QMetaType::LongLong, 0x00015001, uint(2), 0,
      41, QMetaType::Bool, 0x00015003, uint(5), 0,
      42, QMetaType::Bool, 0x00015003, uint(6), 0,
      43, QMetaType::QReal, 0x00015103, uint(7), 0,
      44, QMetaType::QString, 0x00015001, uint(4), 0,
      45, QMetaType::QString, 0x00015001, uint(4), 0,
      46, QMetaType::QPixmap, 0x00015001, uint(8), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject MusicLoader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSMusicLoaderENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMusicLoaderENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMusicLoaderENDCLASS_t,
        // property 'playlist'
        QtPrivate::TypeAndForceComplete<QStringList, std::true_type>,
        // property 'currentIndex'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'position'
        QtPrivate::TypeAndForceComplete<qint64, std::true_type>,
        // property 'duration'
        QtPrivate::TypeAndForceComplete<qint64, std::true_type>,
        // property 'isReplay'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'isShuffle'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'volume'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // property 'currentTitle'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'currentArtist'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'albumArt'
        QtPrivate::TypeAndForceComplete<QPixmap, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MusicLoader, std::true_type>,
        // method 'musicLoadDone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList &, std::false_type>,
        // method 'positionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'durationChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'resetProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentSongChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replayChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shuffleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'volumeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'albumArtChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPixmap, std::false_type>,
        // method 'playlistChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'loadMusicIntoPlayer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList &, std::false_type>,
        // method 'handleMediaStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>,
        // method 'playMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pauseMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'nextMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'previousMusic'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'playAt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'getTitle'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'getArtist'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'getAlbumArt'
        QtPrivate::TypeAndForceComplete<QPixmap, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setReplay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setShuffle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setVolume'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qreal, std::false_type>,
        // method 'setPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>
    >,
    nullptr
} };

void MusicLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MusicLoader *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->musicLoadDone((*reinterpret_cast< std::add_pointer_t<QStringList&>>(_a[1]))); break;
        case 1: _t->positionChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 2: _t->durationChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 3: _t->resetProgress(); break;
        case 4: _t->currentSongChanged(); break;
        case 5: _t->replayChanged(); break;
        case 6: _t->shuffleChanged(); break;
        case 7: _t->volumeChanged((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 8: _t->albumArtChanged((*reinterpret_cast< std::add_pointer_t<QPixmap>>(_a[1]))); break;
        case 9: _t->playlistChanged(); break;
        case 10: _t->playStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->loadMusicIntoPlayer((*reinterpret_cast< std::add_pointer_t<QStringList&>>(_a[1]))); break;
        case 12: _t->handleMediaStatusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 13: _t->playMusic(); break;
        case 14: _t->pauseMusic(); break;
        case 15: _t->nextMusic(); break;
        case 16: _t->previousMusic(); break;
        case 17: _t->playAt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: { QString _r = _t->getTitle((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 19: { QString _r = _t->getArtist((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 20: { QPixmap _r = _t->getAlbumArt((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPixmap*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->setReplay((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: _t->setShuffle((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 23: _t->setVolume((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 24: _t->setPosition((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MusicLoader::*)(QStringList & );
            if (_t _q_method = &MusicLoader::musicLoadDone; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)(qint64 );
            if (_t _q_method = &MusicLoader::positionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)(qint64 );
            if (_t _q_method = &MusicLoader::durationChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)();
            if (_t _q_method = &MusicLoader::resetProgress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)();
            if (_t _q_method = &MusicLoader::currentSongChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)();
            if (_t _q_method = &MusicLoader::replayChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)();
            if (_t _q_method = &MusicLoader::shuffleChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)(qreal );
            if (_t _q_method = &MusicLoader::volumeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)(QPixmap );
            if (_t _q_method = &MusicLoader::albumArtChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)();
            if (_t _q_method = &MusicLoader::playlistChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MusicLoader::*)(bool );
            if (_t _q_method = &MusicLoader::playStateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MusicLoader *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStringList*>(_v) = _t->playlist(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getCurrentIndex(); break;
        case 2: *reinterpret_cast< qint64*>(_v) = _t->position(); break;
        case 3: *reinterpret_cast< qint64*>(_v) = _t->duration(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->isReplay(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isShuffle(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = _t->volume(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->currentTitle(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->currentArtist(); break;
        case 9: *reinterpret_cast< QPixmap*>(_v) = _t->albumArt(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MusicLoader *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setReplay(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setShuffle(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setVolume(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *MusicLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMusicLoaderENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MusicLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 25;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MusicLoader::musicLoadDone(QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MusicLoader::positionChanged(qint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MusicLoader::durationChanged(qint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MusicLoader::resetProgress()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MusicLoader::currentSongChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MusicLoader::replayChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MusicLoader::shuffleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MusicLoader::volumeChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MusicLoader::albumArtChanged(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MusicLoader::playlistChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MusicLoader::playStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
