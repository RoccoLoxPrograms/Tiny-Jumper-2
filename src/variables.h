#ifndef VARIABLES_H
#define VARIABLES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <graphx.h>

// these are the player's variables and many states of existence
extern float playerX;
extern float playerY;
extern float playerXVelocity;
extern float playerYVelocity;
extern bool playerHasJumped;
extern uint8_t playerGrounded;
extern bool playerAntiGravity;
extern bool anyAntiGravity;
extern bool playerQuicksand;
extern bool invincibleMode;
extern bool speedrunnerMode;

// the game runs at 30.00732601 frames a second, or .0333251953 seconds per frame
extern unsigned int timer;

extern char strTemp[10];
extern uint8_t prevDeathMsg;
extern bool dead;
extern bool quit;
extern bool goal;
extern uint8_t level;
extern uint8_t levelX;
extern uint8_t levelY;
extern unsigned int tinyJumperData[82];
extern uint8_t golds;
extern uint8_t goalColor;

extern const unsigned int goldTimes[16];
extern gfx_sprite_t *playerSprites[7];

#ifdef __cplusplus
}
#endif

#endif
