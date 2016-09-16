#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , player(new QMediaPlayer(this))
    , playlist(new QMediaPlaylist)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList *clist[] = {&fnameList, &fsizeList};
    QString ctitle[] = { "Name", "Size" };
    tblModel = new SimpleTableModel(2, (QStringList**)clist, (QString*)ctitle);
    cache.setPath(QDir::currentPath() + "/LocalCache");
    cache.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QStringList filters;
    filters << "*.mp3";
    cache.setNameFilters(filters);
    qDebug() << "+++ using LocalCache:" << cache.path();
    fnameList.clear();
    fsizeList.clear();
    QList<QMediaContent> content;
    for (int i = 0; i < cache.entryInfoList().count(); i++) {
        fnameList.append(cache.entryInfoList()[i].fileName());
        fsizeList.append(QString::number(cache.entryInfoList()[i].size()));
        qDebug() << fnameList[i];
        QString playfile(cache.path() + "/" + fnameList[i]);
        content.push_back(QUrl::fromLocalFile(playfile));
    }
    playlist->addMedia(content);
    tblModel->adjustRows();
    ui->tableView->setModel(tblModel);
    playlist->setCurrentIndex(1);
    player->setVolume(50);
    player->setPlaybackRate(1.0);
    player->setPlaylist(playlist);
    playstack = new PlayPositionStack(player);
    playstack->push(playstack->currentPos());
    ui->statusBar->setStatusTip(player->errorString());
    qDebug() << "+++ media player created";
}

MainWindow::~MainWindow()
{
    delete tblModel;
    delete ui;
}

void MainWindow::on_btnPlay_clicked()
{
    qDebug() << "+++ button clicked:" << ui->btnPlay->text();
    if(ui->btnPlay->text() == tr("PLAY"))
    {
        PlayPosition *cp = playstack->pop();
        playlist->setCurrentIndex(cp->Track);
        player->setPosition(cp->Pos);
        startPerform();
        ui->btnPlay->setText(tr("PAUSE"));
    }
    else if(ui->btnPlay->text() == tr("PAUSE"))
    {
        playstack->push(playstack->currentPos());
        player->stop();
        ui->statusBar->setStatusTip(tr("PAUSE"));
        ui->btnPlay->setText(tr("PLAY"));
    }
}

void MainWindow::on_btnNext_clicked()
{
    qDebug() << "+++ button clicked: \"NEXT\"";
    PlayPosition *cp = playstack->currentPos();
    player->stop();
    cp->Track++;
    int mCount = playlist->mediaCount();
    if (cp->Track > mCount) {
        cp->Track = 1;
    }
    playlist->setCurrentIndex(cp->Track);
    player->setPosition(0);
    startPerform();
}

void MainWindow::startPerform()
{
    player->play();
    QMediaContent mc = playlist->currentMedia();
    QUrl url = mc.canonicalUrl();
    QString currName = url.fileName();
    if (currName.isEmpty()) {
        currName = "***unrecgnized***";
    }
    qDebug() << currName;
    ui->statusBar->setStatusTip(currName);
    player->play();
    return;
}
