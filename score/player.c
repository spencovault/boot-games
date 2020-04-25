#include "player.h"

/**
 * Player structure initializer/"constructor" to initialize player parameters to zero or " "
 * @param player has initials, current score, and high score initialized
 */
void player_init(struct Player *player)
{
    player->initial[0] = "";
    player->initial[1] = "";
    player->initial[2] = "";

    player->currentScore = 0;

    player->highScore = 0;
}
/**
 * @param currPlayer return values of player initial array 
 */
char get_initial(struct Player currPlayer)
{
    return currPlayer.initial;
}

/**
 * @param currPlayer return value of player current score
 */

int get_current_score(struct Player currPlayer)
{
    return currPlayer.currentScore;
}

/**
 * @param currPlayer return value of player high score
 */
int get_high_score(struct Player currPlayer)
{
    return currPlayer.highScore;
}

/**
 * @param playerChar player initial input to be put into *player
 * @param player set player initals based on playerChar input
 */ 
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
/**
 * @param cScore retrieve current score of game to be updated to *player
 * @param player update current score based on cScore value
 */
void set_current_score(int cScore, struct Player *player)
{
    player->currentScore = cScore;
    return;
}
/**
 * @param hScore retrieve player high score to modify player high score
 * @param player modify highScore value based on hScore
 */
void set_high_score(int hScore, struct Player *player)
{
    player->highScore = hScore;
    return;
}