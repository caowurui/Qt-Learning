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

    connect(openFileBtn,&QPushButton::clicked,
        this,[this](){
            QString file = QFileDialog::getOpenFileName(this,"选择音乐文件");
            if(!file.isEmpty())
            {
                player->play(file);
            }
        });
}
