#ifndef PLAYPOSITIONSTACK_H
#define PLAYPOSITIONSTACK_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStack>

class PlayPosition
{
public:
    PlayPosition(int _Track, qint64 _Pos);

    int Track;
    qint64 Pos;

};

class PlayPositionStack: public QStack<PlayPosition*>
{
    QMediaPlayer * player;
public:
    PlayPositionStack(QMediaPlayer * _Player);
    PlayPosition *currentPos();


};

#endif // PLAYPOSITIONSTACK_H
