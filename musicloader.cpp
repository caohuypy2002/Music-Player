#include "musicloader.h"
#include <QDir>
#include <QMediaMetaData>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QImage>
#include <QPixmap>
#include <QDebug>

MusicLoader::MusicLoader(QObject *parent)
    : QObject{parent}
{
    m_mediaPlayer = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_mediaPlayer->setAudioOutput(m_audioOutput);

    connect(this, &MusicLoader::musicLoadDone, this, &MusicLoader::loadMusicIntoPlayer);
    connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &MusicLoader::handleMediaStatusChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicLoader::positionChanged);
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &MusicLoader::durationChanged);

    m_audioOutput->setVolume(0.3);
    emit volumeChanged(0.3);

    srand(static_cast<unsigned int>(time(nullptr)));
    ScanMusicFiles();
}

void MusicLoader::playMusic() {
    lastPlayState = true;
    m_mediaPlayer->play();
}

void MusicLoader::pauseMusic() {
    lastPlayState = false;
    m_mediaPlayer->pause();
}

void MusicLoader::nextMusic() {
    if (m_musicFiles.isEmpty()) return;
    currentIndex = (currentIndex + 1) % m_musicFiles.size();
    m_mediaPlayer->setSource(QUrl::fromLocalFile(m_musicFiles.at(currentIndex)));
    emit resetProgress();
    m_mediaPlayer->setPosition(0);
    m_mediaPlayer->play();
    emit currentSongChanged();
}

void MusicLoader::previousMusic() {
    if (m_musicFiles.isEmpty()) return;
    currentIndex = (currentIndex - 1 + m_musicFiles.size()) % m_musicFiles.size();
    m_mediaPlayer->setSource(QUrl::fromLocalFile(m_musicFiles.at(currentIndex)));
    emit resetProgress();
    m_mediaPlayer->setPosition(0);
    m_mediaPlayer->play();
    emit currentSongChanged();
}
QStringList MusicLoader::playlist() const
{
return m_musicFiles;
}
void MusicLoader::playAt(int index) {
    if (m_musicFiles.isEmpty()) return;
    if (index < 0 || index >= m_musicFiles.size()) return;
    currentIndex = index;
    m_mediaPlayer->setSource(QUrl::fromLocalFile(m_musicFiles.at(currentIndex)));
    emit resetProgress();
    m_mediaPlayer->setPosition(0);
    if (!m_mediaPlayer->isPlaying()) {
        m_mediaPlayer->play();
    }
    lastPlayState = true;
    emit playStateChanged(true);
    emit currentSongChanged();

}
void MusicLoader::ScanMusicFiles() {
    QDir musicDir(m_musicPath);
    QStringList nameFilters = {"*.mp3", "*.wav", "*.flac"};
    QStringList temp = musicDir.entryList(nameFilters, QDir::Files);

    m_musicFiles.clear();
    m_metaMap.clear();

    for (const QString &fileName : temp) {
        QString filePath = musicDir.absoluteFilePath(fileName);
        m_musicFiles.append(filePath);

        // Tạo mặc định meta
        m_metaMap[filePath] = {QFileInfo(filePath).completeBaseName(), "Unknown", QPixmap(), false};

        // Load metadata album art trong background
        QMediaPlayer *tmpPlayer = new QMediaPlayer;
        QAudioOutput *tmpOutput = new QAudioOutput;
        tmpPlayer->setAudioOutput(tmpOutput);
        tmpPlayer->setSource(QUrl::fromLocalFile(filePath));

        QObject::connect(tmpPlayer, &QMediaPlayer::mediaStatusChanged, [=]() {
            if (tmpPlayer->mediaStatus() == QMediaPlayer::LoadedMedia) {
                auto meta = tmpPlayer->metaData();
                QString title = meta.stringValue(QMediaMetaData::Title);
                QString artist = meta.stringValue(QMediaMetaData::ContributingArtist);
                QVariant coverVar = meta.value(QMediaMetaData::ThumbnailImage);
                QPixmap album;
                if (coverVar.isValid()) {
                    QImage img = coverVar.value<QImage>();
                    if (!img.isNull()) album = QPixmap::fromImage(img);
                }

                if (!title.isEmpty()) m_metaMap[filePath].title = title;
                if (!artist.isEmpty()) m_metaMap[filePath].artist = artist;
                if (!album.isNull()) m_metaMap[filePath].albumArt = album;

                m_metaMap[filePath].loaded = true;
                emit playlistChanged();

                tmpPlayer->deleteLater();
                tmpOutput->deleteLater();
            }
        });

        tmpPlayer->play(); // chỉ để trigger load metadata
    }

    if (!m_musicFiles.isEmpty()) {
        currentIndex = 0;
        m_mediaPlayer->setSource(QUrl::fromLocalFile(m_musicFiles.first()));

        // Chờ mediaStatus = LoadedMedia mới emit
        connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
            if(status == QMediaPlayer::LoadedMedia) {
                emit playlistChanged(); // đảm bảo album art đầu tiên đã load
            }
        });
        emit currentSongChanged();
    }


    emit musicLoadDone(m_musicFiles);
    emit playlistChanged();
}

void MusicLoader::loadMusicIntoPlayer(QStringList &musicFiles) {
    if (!musicFiles.isEmpty()) {
        m_mediaPlayer->setSource(QUrl::fromLocalFile(musicFiles.first()));
        m_mediaPlayer->play();
    }
}

void MusicLoader::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    switch (status) {
    case QMediaPlayer::LoadingMedia:
        qDebug() << "Loading media...";
        break;

    case QMediaPlayer::LoadedMedia:
        qDebug() << "Media loaded successfully.";
        emit resetProgress();

        // Title và Artist
        m_currentTitle = m_mediaPlayer->metaData().value(QMediaMetaData::Title).toString();
        m_currentArtist = m_mediaPlayer->metaData().value(QMediaMetaData::ContributingArtist).toString();

        // Lấy album art
        {
            QVariant coverVar = m_mediaPlayer->metaData().value(QMediaMetaData::ThumbnailImage);
            if (coverVar.isValid()) {
                QImage coverImg = coverVar.value<QImage>();
                if (!coverImg.isNull()) m_albumArt = QPixmap::fromImage(coverImg);
            } else {
                m_albumArt = QPixmap(":/Icon/vinyl.png"); // mặc định
            }
            emit albumArtChanged(m_albumArt);
        }

        emit currentSongChanged();
        break;

    case QMediaPlayer::InvalidMedia:
        qDebug() << "Failed to load media.";
        break;

    case QMediaPlayer::EndOfMedia:
        if (m_musicFiles.isEmpty()) return;

        if (m_isReplay) {
            m_mediaPlayer->setPosition(0);
            m_mediaPlayer->play();
        } else if (m_isShuffle) {
            currentIndex = QRandomGenerator::global()->bounded(m_musicFiles.size());
            m_mediaPlayer->setSource(QUrl::fromLocalFile(m_musicFiles.at(currentIndex)));
            m_mediaPlayer->play();
            emit currentSongChanged();

        } else {
            currentIndex = (currentIndex + 1) % m_musicFiles.size();
            m_mediaPlayer->setSource(QUrl::fromLocalFile(m_musicFiles.at(currentIndex)));
            m_mediaPlayer->play();
            emit currentSongChanged();
        }
        break;

    default:
        break;
    }
}
