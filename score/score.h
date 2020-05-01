#ifndef SCORE_H
#define SCORE_H

#define APPLE 10
#define CHERRY 15
#define BANANA 20
#define WATERMELON 25
#define MULTIPLIER 1.0

struct Score {
    int multiplier;
    int appple;
    int cherry;
    int banana;
    int watermelon; 
};
/**
 * Initializes scoring variables for game start
 * @param scoreStart refernces struct Score to initialize scoring values and multiplier
 */
void score_init(struct Score *scoreStart);

#endif