#include "MusicPlayer.h"
#include <QMediaPlayer>
#include <QAudioOutput>

MusicPlayer::MusicPlayer(QObject *parent)
    : QObject(parent)
{
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    // connect(player,&QMediaPlayer::positionChanged,
    //     this, [this](qint64 position){
    //         emit positionChanged(position);
    //     });
    // connect(player,&QMediaPlayer::durationChanged,
    //     this, [this](qint64 duration){
    //         emit durationChanged(duration);
    //     });
    // connect(player,&QMediaPlayer::mediaStatusChanged,
    //     this, [this](bool playing){

    //     });
    // connect(player,&QMediaPlayer::playbackStateChanged,
    //     this,[this](){

    //     });
}

void MusicPlayer::play(const QString &filePath)
{
    player->setSource(QUrl(filePath));
    play();
}

void MusicPlayer::play()
{
    player->play();
}

void MusicPlayer::pause()
{
    player->pause();
}

void MusicPlayer::togglePlayPause()
{
    if(isPlaying()) pause();
    else play();
}

bool MusicPlayer::isPlaying() const
{
    return player->isPlaying();
}

void MusicPlayer::setVolume(qreal volume)
{
    audioOutput->setVolume(volume);
}

qreal MusicPlayer::volume() const
{
    return audioOutput->volume();
}

void MusicPlayer::setMuted(bool muted)
{
    audioOutput->setMuted(muted);
}

qint64 MusicPlayer::position()
{
    return player->position();
}

qint64 MusicPlayer::duration()
{
    return player->duration();
}

void MusicPlayer::seek(qint64 position)
{
    player->setPosition(position);
}
