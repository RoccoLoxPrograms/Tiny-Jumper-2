#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdbool.h>
#include <stdint.h>
#include <graphx.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    COLOR_BLACK,
    COLOR_TRANSP,
    COLOR_DARK_PURPLE,
    COLOR_PURPLE,
    COLOR_LIGHT_PURPLE,
    COLOR_RED,
    COLOR_PINK,
    COLOR_TAN,
    COLOR_GRAY,
    COLOR_LIME,
    COLOR_GOAL_1,
    COLOR_GOAL_2,
    COLOR_GOAL_3,
    COLOR_GOAL_4,
    COLOR_OLIVE = COLOR_GOAL_4,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_GRAY,
    COLOR_GOLD,
    COLOR_WHITE = 255,
};

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
extern unsigned int tinyJumperData[84];
extern uint8_t golds;

extern const unsigned int goldTimes[16];
extern gfx_sprite_t *playerSprites[7];

#ifdef __cplusplus
}
#endif

#endif
