#include "musicloader.h"
#include <QDir>
#include <QMediaMetaData>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QSettings>
#include <QDesktopServices>

MusicLoader::MusicLoader(QObject *parent)
    : QObject{parent}
{
    m_mediaPlayer = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_mediaPlayer->setAudioOutput(m_audioOutput);

    connect(this, &MusicLoader::musicLoadDone, this, &MusicLoader::loadMusicIntoPlayer);
    connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &MusicLoader::handleMediaStatusChanged);
    connect(m_mediaPlayer, &QMediaPlayer::metaDataChanged, this, &MusicLoader::handleMetaDataChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicLoader::positionChanged);
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &MusicLoader::durationChanged);

    m_audioOutput->setVolume(0.3);
    emit volumeChanged(0.3);

    loadFavorites();

    srand(static_cast<unsigned int>(time(nullptr)));
    ScanMusicFiles();
}

void MusicLoader::playMusic() {
    lastPlayState = true;
    m_mediaPlayer->play();
    emit playStateChanged(true);
}

void MusicLoader::pauseMusic() {
    lastPlayState = false;
    m_mediaPlayer->pause();
    emit playStateChanged(false);
}

void MusicLoader::nextMusic() {
    if (m_musicFiles.isEmpty()) return;
    currentIndex = (currentIndex + 1) % m_musicFiles.size();
    QString path = m_musicFiles.at(currentIndex);

    if (m_metaMap.contains(path)) {
        m_currentTitle = m_metaMap[path].title;
        m_currentArtist = m_metaMap[path].artist;
        if (!m_metaMap[path].albumArt.isNull()) {
            m_albumArt = m_metaMap[path].albumArt;
            emit albumArtChanged(m_albumArt);
        }
    } else {
        m_currentTitle = QFileInfo(path).completeBaseName();
        m_currentArtist = "Unknown Artist";
    }

    m_mediaPlayer->setSource(QUrl::fromLocalFile(path));
    emit resetProgress();
    m_mediaPlayer->setPosition(0);
    m_mediaPlayer->play();
    lastPlayState = true;
    emit playStateChanged(true);
    emit currentSongChanged();
    emit favoriteChanged();
}

void MusicLoader::previousMusic() {
    if (m_musicFiles.isEmpty()) return;
    currentIndex = (currentIndex - 1 + m_musicFiles.size()) % m_musicFiles.size();
    QString path = m_musicFiles.at(currentIndex);

    if (m_metaMap.contains(path)) {
        m_currentTitle = m_metaMap[path].title;
        m_currentArtist = m_metaMap[path].artist;
        if (!m_metaMap[path].albumArt.isNull()) {
            m_albumArt = m_metaMap[path].albumArt;
            emit albumArtChanged(m_albumArt);
        }
    } else {
        m_currentTitle = QFileInfo(path).completeBaseName();
        m_currentArtist = "Unknown Artist";
    }

    m_mediaPlayer->setSource(QUrl::fromLocalFile(path));
    emit resetProgress();
    m_mediaPlayer->setPosition(0);
    m_mediaPlayer->play();
    lastPlayState = true;
    emit playStateChanged(true);
    emit currentSongChanged();
    emit favoriteChanged();
}

void MusicLoader::playAt(int index) {
    if (m_musicFiles.isEmpty()) return;
    if (index < 0 || index >= m_musicFiles.size()) return;
    currentIndex = index;
    QString path = m_musicFiles.at(currentIndex);

    if (m_metaMap.contains(path)) {
        m_currentTitle = m_metaMap[path].title;
        m_currentArtist = m_metaMap[path].artist;
        if (!m_metaMap[path].albumArt.isNull()) {
            m_albumArt = m_metaMap[path].albumArt;
            emit albumArtChanged(m_albumArt);
        }
    } else {
        m_currentTitle = QFileInfo(path).completeBaseName();
        m_currentArtist = "Unknown Artist";
    }

    m_mediaPlayer->setSource(QUrl::fromLocalFile(path));
    emit resetProgress();
    m_mediaPlayer->setPosition(0);
    m_mediaPlayer->play();
    lastPlayState = true;
    emit playStateChanged(true);
    emit currentSongChanged();
    emit favoriteChanged();
}

void MusicLoader::ScanMusicFiles() {
    QDir musicDir(m_musicPath);
    qDebug() << "Scanning folder:" << m_musicPath << "Exists?" << musicDir.exists();
    QStringList nameFilters = {"*.mp3", "*.wav", "*.flac", "*.m4a", "*.aac", "*.ogg"};
    QStringList temp = musicDir.entryList(nameFilters, QDir::Files);

    m_musicFiles.clear();
    m_metaMap.clear();

    for (const QString &fileName : temp) {
        QString filePath = musicDir.absoluteFilePath(fileName);
        m_musicFiles.append(filePath);

        m_metaMap[filePath] = {QFileInfo(filePath).completeBaseName(), "Unknown Artist", QPixmap(":/Icon/vinyl.png"), false};

        // Asynchronously extract metadata using background player without playing audio
        QMediaPlayer *tmpPlayer = new QMediaPlayer(this);
        tmpPlayer->setSource(QUrl::fromLocalFile(filePath));

        connect(tmpPlayer, &QMediaPlayer::mediaStatusChanged, this, [this, tmpPlayer, filePath](QMediaPlayer::MediaStatus status) {
            if (status == QMediaPlayer::LoadedMedia) {
                auto meta = tmpPlayer->metaData();
                QString title = meta.stringValue(QMediaMetaData::Title);
                QString artist = meta.stringValue(QMediaMetaData::ContributingArtist);
                if (artist.isEmpty()) artist = meta.stringValue(QMediaMetaData::AlbumArtist);
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

                // If currently playing this file, update live
                if (!m_musicFiles.isEmpty() && m_musicFiles.at(currentIndex) == filePath) {
                    if (!title.isEmpty()) m_currentTitle = title;
                    if (!artist.isEmpty()) m_currentArtist = artist;
                    if (!album.isNull()) {
                        m_albumArt = album;
                        emit albumArtChanged(m_albumArt);
                    }
                    emit currentSongChanged();
                }

                emit playlistChanged();
                tmpPlayer->deleteLater();
            }
        });
    }

    if (!m_musicFiles.isEmpty()) {
        currentIndex = 0;
        QString firstPath = m_musicFiles.first();
        m_currentTitle = QFileInfo(firstPath).completeBaseName();
        m_currentArtist = "Unknown Artist";
        m_mediaPlayer->setSource(QUrl::fromLocalFile(firstPath));
        emit currentSongChanged();
        emit favoriteChanged();
    }

    emit musicLoadDone(m_musicFiles);
    emit playlistChanged();
}

void MusicLoader::addMusicFile(const QString &fileUrlOrPath) {
    QString localPath = fileUrlOrPath;
    if (localPath.startsWith("file:///")) {
        localPath = QUrl(fileUrlOrPath).toLocalFile();
    }
    if (localPath.isEmpty() || !QFileInfo::exists(localPath)) return;
    if (m_musicFiles.contains(localPath)) return;

    m_musicFiles.append(localPath);
    m_metaMap[localPath] = {QFileInfo(localPath).completeBaseName(), "Unknown Artist", QPixmap(":/Icon/vinyl.png"), false};

    QMediaPlayer *tmpPlayer = new QMediaPlayer(this);
    tmpPlayer->setSource(QUrl::fromLocalFile(localPath));

    connect(tmpPlayer, &QMediaPlayer::mediaStatusChanged, this, [this, tmpPlayer, localPath](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::LoadedMedia) {
            auto meta = tmpPlayer->metaData();
            QString title = meta.stringValue(QMediaMetaData::Title);
            QString artist = meta.stringValue(QMediaMetaData::ContributingArtist);
            if (artist.isEmpty()) artist = meta.stringValue(QMediaMetaData::AlbumArtist);
            QVariant coverVar = meta.value(QMediaMetaData::ThumbnailImage);
            QPixmap album;
            if (coverVar.isValid()) {
                QImage img = coverVar.value<QImage>();
                if (!img.isNull()) album = QPixmap::fromImage(img);
            }

            if (!title.isEmpty()) m_metaMap[localPath].title = title;
            if (!artist.isEmpty()) m_metaMap[localPath].artist = artist;
            if (!album.isNull()) m_metaMap[localPath].albumArt = album;

            m_metaMap[localPath].loaded = true;
            emit playlistChanged();

            if (!m_musicFiles.isEmpty() && m_musicFiles.at(currentIndex) == localPath) {
                if (!title.isEmpty()) m_currentTitle = title;
                if (!artist.isEmpty()) m_currentArtist = artist;
                if (!album.isNull()) {
                    m_albumArt = album;
                    emit albumArtChanged(m_albumArt);
                }
                emit currentSongChanged();
            }

            tmpPlayer->deleteLater();
        }
    });

    emit playlistChanged();

    if (m_musicFiles.size() == 1) {
        currentIndex = 0;
        m_mediaPlayer->setSource(QUrl::fromLocalFile(localPath));
        m_mediaPlayer->play();
        lastPlayState = true;
        emit playStateChanged(true);
        emit currentSongChanged();
        emit favoriteChanged();
    }
}

void MusicLoader::addMusicFiles(const QStringList &fileUrlsOrPaths) {
    for (const QString &p : fileUrlsOrPaths) {
        addMusicFile(p);
    }
}

void MusicLoader::removeMusicAt(int index) {
    if (index < 0 || index >= m_musicFiles.size()) return;
    QString removedFile = m_musicFiles.at(index);
    bool wasCurrent = (index == currentIndex);
    m_musicFiles.removeAt(index);
    if (m_favorites.contains(removedFile)) {
        m_favorites.remove(removedFile);
        saveFavorites();
        m_favoriteRevision++;
        emit favoriteChanged();
    }
    emit playlistChanged();
    if (m_musicFiles.isEmpty()) {
        m_mediaPlayer->stop();
        m_currentTitle = "";
        m_currentArtist = "";
        m_albumArt = QPixmap(":/Icon/vinyl.png");
        emit albumArtChanged(m_albumArt);
        emit currentSongChanged();
        emit favoriteChanged();
    } else if (wasCurrent) {
        if (currentIndex >= m_musicFiles.size()) currentIndex = 0;
        playAt(currentIndex);
    } else if (index < currentIndex) {
        currentIndex--;
        emit currentSongChanged();
    }
}

void MusicLoader::openCurrentFileLocation() {
    QString path = currentFilePath();
    if (!path.isEmpty()) {
        QFileInfo fi(path);
        QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absolutePath()));
    }
}

void MusicLoader::loadFavorites() {
    QSettings settings("FPTProject", "MusicPlayer");
    QStringList favs = settings.value("favorites").toStringList();
    m_favorites = QSet<QString>(favs.begin(), favs.end());
    m_favoriteRevision++;
    emit favoriteChanged();
}

void MusicLoader::saveFavorites() {
    QSettings settings("FPTProject", "MusicPlayer");
    QStringList favs;
    for (const QString &f : m_favorites) favs.append(f);
    settings.setValue("favorites", favs);
}

void MusicLoader::loadMusicIntoPlayer(QStringList &musicFiles) {
    if (!musicFiles.isEmpty()) {
        m_mediaPlayer->setSource(QUrl::fromLocalFile(musicFiles.first()));
        m_mediaPlayer->play();
    }
}

void MusicLoader::handleMetaDataChanged() {
    auto meta = m_mediaPlayer->metaData();
    QString title = meta.stringValue(QMediaMetaData::Title);
    QString artist = meta.stringValue(QMediaMetaData::ContributingArtist);
    if (artist.isEmpty()) artist = meta.stringValue(QMediaMetaData::AlbumArtist);
    QVariant coverVar = meta.value(QMediaMetaData::ThumbnailImage);

    QString path = currentFilePath();
    if (!title.isEmpty()) {
        m_currentTitle = title;
        if (!path.isEmpty()) m_metaMap[path].title = title;
    }
    if (!artist.isEmpty()) {
        m_currentArtist = artist;
        if (!path.isEmpty()) m_metaMap[path].artist = artist;
    }
    if (coverVar.isValid()) {
        QImage coverImg = coverVar.value<QImage>();
        if (!coverImg.isNull()) {
            m_albumArt = QPixmap::fromImage(coverImg);
            if (!path.isEmpty()) m_metaMap[path].albumArt = m_albumArt;
            emit albumArtChanged(m_albumArt);
        }
    }
    emit currentSongChanged();
}

void MusicLoader::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    switch (status) {
    case QMediaPlayer::LoadingMedia:
        break;

    case QMediaPlayer::LoadedMedia:
        emit resetProgress();
        handleMetaDataChanged();
        emit currentSongChanged();
        emit favoriteChanged();
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
            playAt(currentIndex);
        } else {
            currentIndex = (currentIndex + 1) % m_musicFiles.size();
            playAt(currentIndex);
        }
        break;

    default:
        break;
    }
}
