#ifndef MUSICLOADER_H
#define MUSICLOADER_H
#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QStringList>
#include <QAudioOutput>
#include <QtGlobal>
#include <QTime>
#include<QmediaMetaData>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QPixmap>
class MusicLoader : public QObject
{
    Q_OBJECT
public:
    explicit MusicLoader(QObject *parent = nullptr);
    Q_INVOKABLE void playMusic();
    Q_INVOKABLE void pauseMusic();
    Q_INVOKABLE void nextMusic();
    Q_INVOKABLE void previousMusic();
    Q_PROPERTY(QStringList playlist READ playlist NOTIFY playlistChanged)// playlist property
    Q_INVOKABLE void playAt(int index);// play music at specific index
    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentSongChanged) // current index property
    QStringList playlist() const; // playlist getter
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged) // position property
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged) // duration property
    Q_PROPERTY(bool isReplay READ isReplay WRITE setReplay NOTIFY replayChanged) // replay property
    Q_PROPERTY(bool isShuffle READ isShuffle WRITE setShuffle NOTIFY shuffleChanged) // shuffle property
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)// volume property
    Q_PROPERTY(QString currentTitle READ currentTitle NOTIFY currentSongChanged) // current title property
    Q_PROPERTY(QString currentArtist READ currentArtist NOTIFY currentSongChanged) // current artist property
    Q_PROPERTY(QPixmap albumArt READ albumArt NOTIFY albumArtChanged) // album art property
    Q_INVOKABLE QString getTitle(const QString &file) const {
        return m_metaMap.contains(file) ? m_metaMap[file].title : file;
    }

    Q_INVOKABLE QString getArtist(const QString &file) const {
        return m_metaMap.contains(file) ? m_metaMap[file].artist : "Unknown";
    }

    Q_INVOKABLE QPixmap getAlbumArt(const QString &file) const {
        return m_metaMap.contains(file) ? m_metaMap[file].albumArt : QPixmap(":/Icon/vinyl.png");
    }
    QString m_currentTitle;
    QString m_currentArtist;
    int getCurrentIndex() const { return currentIndex; }
    bool isReplay() const { return m_isReplay; }
    Q_INVOKABLE void setReplay(bool value) {
        if (m_isReplay != value) {
            m_isReplay = value;
            emit replayChanged();
        }
        if(m_isReplay) {// nếu bật replay thì tắt shuffle
            m_isShuffle = false;
            emit shuffleChanged();
        }
    }
    bool isShuffle() const { return m_isShuffle; }
    Q_INVOKABLE void setShuffle(bool value) {
        if (m_isShuffle != value) {
            m_isShuffle = value;
            emit shuffleChanged();
            if (m_isShuffle) { // nếu bật shuffle thì tắt replay
                setReplay(false);
            }
        }
    }
    qreal volume() const { return m_audioOutput->volume(); }
    Q_INVOKABLE void setVolume(qreal vol) {
        if (!m_audioOutput) return;
        qreal newVol = qBound(0.0, vol, 1.0);
        if (qAbs(newVol - m_audioOutput->volume()) > 0.0001) {
            m_audioOutput->setVolume(newVol);
            emit volumeChanged(newVol);
        }
    }
    QString currentTitle() const { return m_currentTitle; }
    QString currentArtist() const { return m_currentArtist; }

    Q_INVOKABLE void setPosition(qint64 pos) {
        m_mediaPlayer->setPosition(pos);
    }
    qint64 position() const { return m_mediaPlayer->position(); }
    qint64 duration() const { return m_mediaPlayer->duration(); }
    QPixmap albumArt() const { return m_albumArt; } // album art property
    const QString m_musicPath = "C:/Users/Asus/Downloads/CRANES/FPTPROJECT/ASSIGMENT_MusicPlayer/Music" ;
    QStringList m_musicFiles;
    QMediaPlayer* m_mediaPlayer;
    QAudioOutput* m_audioOutput;
    struct SongMeta {
        QString title;
        QString artist;
        QPixmap albumArt;
        bool loaded = false;
    };
    QMap<QString, SongMeta> m_metaMap;
    void ScanMusicFiles();
private:
    int currentIndex = 0;
    bool m_isReplay = false;
    bool m_isShuffle = false;
    QPixmap m_albumArt;
    bool lastPlayState = true;
private slots:
    void loadMusicIntoPlayer(QStringList &musicFiles);
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
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
};

#endif // MUSICLOADER_H
