#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QSlider;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);


private:
    QPushButton *lastSongBtn;
    QPushButton *nextSongBtn;
    QPushButton *stopBtn;
    QPushButton *enableVolumeBtn;
    QSlider *volumeSlider;

    QLabel *currentTimeLabel;
    QSlider *processSlider;
    QLabel *totalTimeLabel;
};

#endif
