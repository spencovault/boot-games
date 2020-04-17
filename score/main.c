#include "player.h"
#include <stdio.h>

int main() 
{
    struct Player newPlayer;
    player_init(&newPlayer);
    printf("Current Score %i", newPlayer.currentScore);
    
    return 0;
}
