#include "MainWindow.h"
#include "MusicPlayer.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
    :QMainWindow(parent)
{
    QWidget * upperControl = new QWidget;
    QHBoxLayout *upperLayout = new QHBoxLayout;
    lastSongBtn = new QPushButton("<<");
    nextSongBtn = new QPushButton(">>");
    stopBtn = new QPushButton("▶");
    enableVolumeBtn = new QPushButton("🔊");
    volumeSlider = new QSlider(Qt::Orientation::Horizontal);
    openFileBtn = new QPushButton("打开...");
    upperControl->setLayout(upperLayout);
    upperLayout->addWidget(openFileBtn);
    upperLayout->addWidget(lastSongBtn);
    upperLayout->addWidget(stopBtn);
    upperLayout->addWidget(nextSongBtn);
    upperLayout->addWidget(enableVolumeBtn);
    upperLayout->addWidget(volumeSlider);
    QWidget *lowerWidget = new QWidget;
    QHBoxLayout *lowerLayout = new QHBoxLayout;
    currentTimeLabel = new QLabel("00:00");
    processSlider = new QSlider(Qt::Orientation::Horizontal);
    totalTimeLabel = new QLabel("00:00");
    lowerWidget->setLayout(lowerLayout);
    lowerLayout->addWidget(currentTimeLabel);
    lowerLayout->addWidget(processSlider);
    lowerLayout->addWidget(totalTimeLabel);
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralWidget->setLayout(centralLayout);
    centralLayout->addWidget(upperControl);
    centralLayout->addWidget(lowerWidget);
    setCentralWidget(centralWidget);


    player = new MusicPlayer(this);
    isPause = true;
    isMuted = false;
    volumeSlider->setRange(0,100);
    volumeSlider->setSingleStep(1);
    volumeSlider->setValue(70);

    connect(openFileBtn,&QPushButton::clicked,
        this,[this](){
            QString file = QFileDialog::getOpenFileName(this,"选择音乐文件");
            if(!file.isEmpty())
            {
                player->play(file);
                stopBtn->setText("⏸");
                isPause=false;
                processSlider->setValue(0);
            }
        });
    connect(stopBtn,&QPushButton::clicked,
        this,[this](){
            if(isPause)
            {
                stopBtn->setText("⏸");
                player->play();
                isPause = false;
            }
            else{
                stopBtn->setText("▶");
                player->pause();
                isPause = true;
            }
        });
    connect(enableVolumeBtn,&QPushButton::clicked,
        this,[this](){
            if(isMuted)
            {
                enableVolumeBtn->setText("🔊");
                isMuted = false;
                player->setMuted(false);
                player->setVolume(volume/100.0);
            }
            else{
                enableVolumeBtn->setText("🔇");
                isMuted = true;
                player->setMuted(true);
            }
        });
    connect(volumeSlider,&QSlider::valueChanged,
        this,[this](int value){
            volume = value;
            if(!isMuted)
            {
                player->setVolume(value/100.0);
            }
        });
    connect(processSlider,&QSlider::sliderMoved,
        this,[this](int value){
            player->setPosition(value);
        });
    connect(player,&MusicPlayer::positionChanged,
        this,[this](qint64 position){
            processSlider->setValue(position);

            QString time = QString("%1:%2")
                .arg(position/60000,2,10,QChar('0'))
                .arg(position/1000%60,2,10,QChar('0'));
            currentTimeLabel->setText(time);
        });
    connect(player,&MusicPlayer::durationChanged,
        this,[this](qint64 duration){
            processSlider->setRange(0,duration);

            QString time = QString("%1:%2")
                .arg(duration/60000,2,10,QChar('0'))
                .arg(duration/1000%60,2,10,QChar('0'));
            totalTimeLabel->setText(time);
        });
    connect(player,&MusicPlayer::mediaFinished,
        this,[this](){
            stopBtn->click();
        });
}
