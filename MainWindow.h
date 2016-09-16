#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SimpleTable.h"
#include "PlayPositionStack.h"

#include <QURL>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMainWindow>
#include <QDir>
#include <QtDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SimpleTableModel *tblModel;
    QStringList fnameList, fsizeList;
    QDir cache;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    PlayPositionStack *playstack;
private slots:
    void on_btnPlay_clicked();
    void on_btnNext_clicked();
private:
    Ui::MainWindow *ui;
    void startPerform();
};

#endif // MAINWINDOW_H
