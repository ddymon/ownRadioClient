#include "PlayPositionStack.h"

PlayPosition::PlayPosition(int _Track, qint64 _Pos) {
    Track = _Track;
    Pos = _Pos;
}

PlayPositionStack::PlayPositionStack(QMediaPlayer *_Player) {
    player = _Player;
}

PlayPosition *PlayPositionStack::currentPos() {
   return new PlayPosition(player->playlist()->currentIndex(), player->position());
}
