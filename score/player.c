#include "player.h"

void player_init(struct Player* player)
{
    player->initial[0] = "";
    player->initial[1] = "";
    player->initial[2] = "";

    player->currentScore = 0;

    player->highScore = 0;
}

char get_initial(struct Player currPlayer)
{
    return currPlayer.initial;
}

int get_current_score(struct Player currPlayer)
{
    return currPlayer.currentScore;
}

int get_high_score(struct Player currPlayer)
{
    return currPlayer.highScore;
}

void set_initial(char *playerChar, struct Player *player)
{
    for(int i = 0; playerChar[i] != 0; i++)
    {
        if (i > 3)
        {
            return;
        }
        player->initial[i] = playerChar[i];
    }
    return;
}

void set_current_score(int cScore, struct Player *player)
{
    player->currentScore = cScore;
    return;
}

void set_high_score(int hScore, struct Player *player)
{
    player->highScore = hScore;
    return;
}