#ifndef PLAYER_H
#define PLAYER_H

/**
 * Player C structure to allow for object oriented programming for player 
 * objects that contain initials, current score, personal best, and high score parameters
 */
struct Player {
  char initial[3];
  int currentScore;
  int personalBest;
  int highScore;
};
/**
 * Function signature to define functions in player.c 
 */ 
void player_init(struct Player* player);
int get_current_score(struct Player currPlayer);
int get_high_score(struct Player currPlayer);
void set_initial(char *playerChar, struct Player *player);
void set_current_score(int cScore, struct Player *player);
void set_high_score(int hScore, struct Player *player);

#endif
