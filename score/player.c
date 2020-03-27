#include "player.h"

void player_init(struct Player* player)
{
    player->initial[0] = "";
    player->initial[1] = "";
    player->initial[2] = "";

    player->currentScore = 0;

    player->highScore = 0;
}

char *get_initial(struct Player currPlayer)
{
    return currPlayer.initial;
}

int *get_current_score(struct Player currPlayer)
{
    return currPlayer.currentScore;
}

int *get_high_score(struct Player currPlayer)
{
    return currPlayer.highScore;
}
