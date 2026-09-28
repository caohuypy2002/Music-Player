#ifndef MUSICLOADER_H
#define MUSICLOADER_H

#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QStringList>
#include <QAudioOutput>
#include <QtGlobal>
#include <QTime>
#include <QMediaMetaData>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QPixmap>
#include <QSet>
#include <QSettings>
#include <QUrl>

class MusicLoader : public QObject
{
    Q_OBJECT
public:
    explicit MusicLoader(QObject *parent = nullptr);

    Q_PROPERTY(bool playing READ isPlaying NOTIFY playStateChanged)
    bool isPlaying() const { return lastPlayState; }

    Q_PROPERTY(QStringList playlist READ playlist NOTIFY playlistChanged)
    QStringList playlist() const { return m_musicFiles; }

    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentSongChanged)
    int getCurrentIndex() const { return currentIndex; }

    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    qint64 position() const { return m_mediaPlayer ? m_mediaPlayer->position() : 0; }

    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    qint64 duration() const { return m_mediaPlayer ? m_mediaPlayer->duration() : 0; }

    Q_PROPERTY(bool isReplay READ isReplay WRITE setReplay NOTIFY replayChanged)
    bool isReplay() const { return m_isReplay; }

    Q_PROPERTY(bool isShuffle READ isShuffle WRITE setShuffle NOTIFY shuffleChanged)
    bool isShuffle() const { return m_isShuffle; }

    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)
    qreal volume() const { return m_audioOutput ? m_audioOutput->volume() : 0.0; }

    Q_PROPERTY(qreal playbackRate READ playbackRate WRITE setPlaybackRate NOTIFY playbackRateChanged)
    qreal playbackRate() const { return m_mediaPlayer ? m_mediaPlayer->playbackRate() : 1.0; }

    Q_PROPERTY(bool isCurrentFavorite READ isCurrentFavorite NOTIFY favoriteChanged)
    bool isCurrentFavorite() const {
        QString path = currentFilePath();
        return !path.isEmpty() && m_favorites.contains(path);
    }

    Q_PROPERTY(int favoriteRevision READ favoriteRevision NOTIFY favoriteChanged)
    int favoriteRevision() const { return m_favoriteRevision; }

    Q_PROPERTY(int favoriteCount READ favoriteCount NOTIFY favoriteChanged)
    int favoriteCount() const { return m_favorites.size(); }

    Q_PROPERTY(QStringList favoriteList READ favoriteList NOTIFY favoriteChanged)
    QStringList favoriteList() const { return QStringList(m_favorites.begin(), m_favorites.end()); }

    Q_PROPERTY(QString musicPath READ musicPath CONSTANT)
    QString musicPath() const { return m_musicPath; }

    // Synchronized track properties
    Q_PROPERTY(QString currentTitle READ currentTitle NOTIFY currentSongChanged)
    QString currentTitle() const {
        QString path = currentFilePath();
        if (!path.isEmpty() && m_metaMap.contains(path) && !m_metaMap[path].title.isEmpty()) {
            return m_metaMap[path].title;
        }
        if (!m_currentTitle.isEmpty()) {
            return m_currentTitle;
        }
        return path.isEmpty() ? QString("-") : QFileInfo(path).completeBaseName();
    }

    Q_PROPERTY(QString currentArtist READ currentArtist NOTIFY currentSongChanged)
    QString currentArtist() const {
        QString path = currentFilePath();
        if (!path.isEmpty() && m_metaMap.contains(path) && !m_metaMap[path].artist.isEmpty() && m_metaMap[path].artist != "Unknown") {
            return m_metaMap[path].artist;
        }
        if (!m_currentArtist.isEmpty()) {
            return m_currentArtist;
        }
        return QString("Unknown Artist");
    }

    Q_PROPERTY(QString currentFilePath READ currentFilePath NOTIFY currentSongChanged)
    QString currentFilePath() const {
        if (!m_musicFiles.isEmpty() && currentIndex >= 0 && currentIndex < m_musicFiles.size()) {
            return m_musicFiles.at(currentIndex);
        }
        if (m_mediaPlayer && !m_mediaPlayer->source().isEmpty()) {
            return m_mediaPlayer->source().toLocalFile();
        }
        return QString();
    }

    Q_PROPERTY(QString currentFileName READ currentFileName NOTIFY currentSongChanged)
    QString currentFileName() const {
        QString p = currentFilePath();
        return p.isEmpty() ? QString("-") : QFileInfo(p).fileName();
    }

    Q_PROPERTY(QString currentFileSize READ currentFileSize NOTIFY currentSongChanged)
    QString currentFileSize() const {
        QString p = currentFilePath();
        if (p.isEmpty()) return QString("-");
        qint64 bytes = QFileInfo(p).size();
        if (bytes <= 0) return QString("-");
        double mb = bytes / (1024.0 * 1024.0);
        return QString::number(mb, 'f', 2) + " MB";
    }

    Q_PROPERTY(QString currentFileFormat READ currentFileFormat NOTIFY currentSongChanged)
    QString currentFileFormat() const {
        QString p = currentFilePath();
        if (p.isEmpty()) return QString("-");
        return QFileInfo(p).suffix().toUpper();
    }

    Q_PROPERTY(QPixmap albumArt READ albumArt NOTIFY albumArtChanged)
    QPixmap albumArt() const { return m_albumArt; }

    // Invokable playback controls
    Q_INVOKABLE void playMusic();
    Q_INVOKABLE void pauseMusic();
    Q_INVOKABLE void nextMusic();
    Q_INVOKABLE void previousMusic();
    Q_INVOKABLE void playAt(int index);

    Q_INVOKABLE void setReplay(bool value) {
        if (m_isReplay != value) {
            m_isReplay = value;
            emit replayChanged();
        }
        if (m_isReplay) {
            m_isShuffle = false;
            emit shuffleChanged();
        }
    }

    Q_INVOKABLE void setShuffle(bool value) {
        if (m_isShuffle != value) {
            m_isShuffle = value;
            emit shuffleChanged();
            if (m_isShuffle) {
                setReplay(false);
            }
        }
    }

    Q_INVOKABLE void setVolume(qreal vol) {
        if (!m_audioOutput) return;
        qreal newVol = qBound(0.0, vol, 1.0);
        if (qAbs(newVol - m_audioOutput->volume()) > 0.0001) {
            m_audioOutput->setVolume(newVol);
            emit volumeChanged(newVol);
        }
    }

    Q_INVOKABLE void setPlaybackRate(qreal rate) {
        if (m_mediaPlayer && rate > 0.0) {
            m_mediaPlayer->setPlaybackRate(rate);
            emit playbackRateChanged();
        }
    }

    Q_INVOKABLE void setPosition(qint64 pos) {
        if (m_mediaPlayer) m_mediaPlayer->setPosition(pos);
    }

    // Favorites
    Q_INVOKABLE bool isFavorite(const QString &file) const {
        return m_favorites.contains(file);
    }
    Q_INVOKABLE void toggleCurrentFavorite() {
        QString path = currentFilePath();
        if (!path.isEmpty()) toggleFavorite(path);
    }
    Q_INVOKABLE void toggleFavorite(const QString &file) {
        if (m_favorites.contains(file)) {
            m_favorites.remove(file);
        } else {
            m_favorites.insert(file);
        }
        m_favoriteRevision++;
        saveFavorites();
        emit favoriteChanged();
    }

    // Playlist & Library Operations
    Q_INVOKABLE void addMusicFile(const QString &fileUrlOrPath);
    Q_INVOKABLE void addMusicFiles(const QStringList &fileUrlsOrPaths);
    Q_INVOKABLE void removeMusicAt(int index);
    Q_INVOKABLE void ScanMusicFiles();
    Q_INVOKABLE void openCurrentFileLocation();

    // Metadata getters for delegates
    Q_INVOKABLE QString getTitle(const QString &file) const {
        return m_metaMap.contains(file) ? m_metaMap[file].title : QFileInfo(file).completeBaseName();
    }

    Q_INVOKABLE QString getArtist(const QString &file) const {
        return m_metaMap.contains(file) ? m_metaMap[file].artist : "Unknown";
    }

    Q_INVOKABLE QPixmap getAlbumArt(const QString &file) const {
        return (m_metaMap.contains(file) && !m_metaMap[file].albumArt.isNull()) ? m_metaMap[file].albumArt : QPixmap(":/Icon/vinyl.png");
    }

    const QString m_musicPath = "C:/Users/Asus/Downloads/CRANES/FPTPROJECT/MusicPlayer/Music";
    QStringList m_musicFiles;
    QMediaPlayer* m_mediaPlayer = nullptr;
    QAudioOutput* m_audioOutput = nullptr;

    struct SongMeta {
        QString title;
        QString artist;
        QPixmap albumArt;
        bool loaded = false;
    };
    QMap<QString, SongMeta> m_metaMap;

private:
    int currentIndex = 0;
    bool m_isReplay = false;
    bool m_isShuffle = false;
    QPixmap m_albumArt;
    bool lastPlayState = true;
    QString m_currentTitle;
    QString m_currentArtist;
    QSet<QString> m_favorites;
    int m_favoriteRevision = 0;

    void loadFavorites();
    void saveFavorites();

private slots:
    void loadMusicIntoPlayer(QStringList &musicFiles);
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handleMetaDataChanged();

signals:
    void musicLoadDone(QStringList &musicFiles);
    void positionChanged(qint64);
    void durationChanged(qint64);
    void resetProgress();
    void currentSongChanged();
    void replayChanged();
    void shuffleChanged();
    void volumeChanged(qreal);
    void albumArtChanged(QPixmap);
    void playlistChanged();
    void playStateChanged(bool isPlaying);
    void playbackRateChanged();
    void favoriteChanged();
};

#endif // MUSICLOADER_H
