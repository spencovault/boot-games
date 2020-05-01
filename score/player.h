#ifndef PLAYER_H
#define PLAYER_H

/**
 * @file player.h
 *  
 * @brief Includes player functions to track player initials and scores and update them 
 * when necessary
 * 
 * @author Nathaniel Price
 */
/**
 * Defines variables for the Player struct to be initialized and modified in player.c
 * 
 */
struct Player {
  char initial[3];
  int currentScore;
  int personalBest;
  int highScore;
};

/**
 * Initializes player intials to empty char values and scores to zero when a new player struct
 * is called
 * @param player references the Player struct to initialize/create a new player
 */ 
void player_init(struct Player* player);

/**
 * Gets the player's current score
 * @param currPlayer references the current player for Player struct to be modified
 * @return returns player currentScore value
 */
int get_current_score(struct Player currPlayer);

/**
 * Gets the player's high score
 * @param currPlayer references the current player for Player struct to be modified
 * @return returns player highScore value
 */ 
int get_high_score(struct Player currPlayer);

/**
 * Gets the player's initials
 * @param currPlayer references the current player for Player stuct to be modified
 * @return returns player's initials
 */ 
char get_initial(struct Player currPlayer);

/**
 * Sets the player's initials if called
 * @param playerChar references initial in Player struct to be modified based on input of characters
 * for initials
 * @param player references specific Player struct to modify the player initials
 */ 
void set_initial(char *playerChar, struct Player *player);

/**
 * Sets player's current score if called
 * @param cScore references currentScore in Player struct to be modified based on current score of game
 * @param player references specific Player struct to modify the player's current score  
 */
void set_current_score(int cScore, struct Player *player);
/**
 * Sets player's high score if called
 * @param hScore references highScore in player struct to be modified based on if the player has acheived
 * a new high score
 * @param player references specific Player struct to modify the player's high score
 */ 
void set_high_score(int hScore, struct Player *player);

#endif
