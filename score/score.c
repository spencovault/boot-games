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
