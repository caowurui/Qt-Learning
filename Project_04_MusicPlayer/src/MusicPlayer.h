#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>

class QMediaPlayer;
class QAudioOutput;

class MusicPlayer : public QObject
{
    Q_OBJECT

public:
    explicit MusicPlayer(QObject *parent = nullptr);

public:
    void play(const QString &filePath);
    void play();
    void pause();
    void togglePlayPause();
    bool isPlaying() const;

    void setVolume(qreal volume);
    qreal volume() const;
    void setMuted(bool muted);

    qint64 position();
    qint64 duration();
    void setPosition(qint64 position);

signals:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void stateChanged(bool playing);
    void mediaFinished();

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};


#endif
