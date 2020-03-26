#include "player.h"

char *getInitial(struct Player currPlayer)
{
    return currPlayer.initial;
}

int *getCurrentScore(struct Player currPlayer)
{
    return currPlayer.currentScore;
}

int *getHighScore(struct Player currPlayer)
{
    return currPlayer.highScore;
}
