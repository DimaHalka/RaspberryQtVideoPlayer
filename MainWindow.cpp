#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QAudioOutput>
#include <QBoxLayout>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QPushButton>
#include <QVideoWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QBoxLayout *layout = new QVBoxLayout(this);
    videoWidget = new QVideoWidget(this);
    layout->addWidget(videoWidget);

    QMediaPlayer *player = new QMediaPlayer(this);
    player->setVideoOutput(videoWidget);

    QAudioOutput* audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    QPushButton *openButton = new QPushButton("Open Video", this);
    layout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openVideo);

    setCentralWidget(new QWidget(this));
    centralWidget()->setLayout(layout);

    this->player = player;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openVideo() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Video File", "", "Video Files (*.m4v *.mkv)");
    if (!filePath.isEmpty()) {

        player->setSource(QUrl::fromLocalFile(filePath));
        player->play();
    }
}


