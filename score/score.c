#include "score.h"
#include "player.h"


void score_init(struct Score *scoreStart)
{
    scoreStart->apple = APPLE;
    scoreStart->cherry = CHERRY;
    scoreStart->banana = BANANA;
    scoreStart->watermelon = WATERMELON;
    scoreStart->multiplier = MULTIPLIER;
}

int apple_point(struct Player *player, struct Score points)
{
    player->currentScore += points.apple;
    return player->currentScore;
}

int cherry_point(struct Player *player, struct Score points)
{
    player->currentScore += points.cherry;
    return player->currentScore;
}

int banana_point(struct Player *player, struct Score points)
{
    player->currentScore += points.banana;
    return player->currentScore;
}

int watermelon_point(struct Player *player, struct Score points)
{
    player->currentScore += points.watermelon;
    return player->currentScore;
}