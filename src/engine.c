#include "engine.h"
#include "gfx/sprites.h"
#include "variables.h"

#include <tice.h>
#include <keypadc.h>
#include <fontlibc.h>
#include <math.h>
#include <stdbool.h>

// this function gets called at the end of every frame
void drawPlayerAndTime(int stringXpos, uint8_t stringYpos) {
  if (playerX < 0) playerX = 0;     // if the player hits the edge of the screen, then they stop
  if (playerX > 312) playerX = 312; // if the player hits the other edge of the screen, then they stop
  if (playerY < 0) playerY = 0;     // if the player hits the top, they stop
  if (playerY > 232) {              // if the player is on the bottom of the screen, then they stop
    playerY = 232;
    playerYVelocity = 0;
    playerGrounded = 3;
  }
  gfx_SetColor(5);
  gfx_FillRectangle(stringXpos, stringYpos, 40, 10);
  if (tinyJumperData[16] < 256) {
    gfx_SetColor(tinyJumperData[16]);
    gfx_FillRectangle_NoClip(playerX, playerY, 8, 8);
  } else if (tinyJumperData[16] > 255) {
    if (playerAntiGravity) gfx_TransparentSprite_NoClip(playerSprites[6], playerX, playerY);
    else gfx_TransparentSprite_NoClip(playerSprites[tinyJumperData[16] - 256], playerX, playerY);
  }
  gfx_SetTextFGColor(255);
  gfx_SetTextBGColor(5);
  gfx_PrintStringXY(strTemp, stringXpos, stringYpos);
  if (gfx_CheckRectangleHotspot(playerX, playerY, 8, 8, stringXpos, stringYpos, 36, 10)) gfx_PrintStringXY(strTemp, stringXpos, stringYpos + 10);
}

void endOfFrame(void) {
  gfx_BlitBuffer();
  while (timer_Get(1) < 1092);
}

void resetData(void) {
  tinyJumperData[0] = 0;
  tinyJumperData[15] = 0;
  for (uint8_t levelNumber = 1; levelNumber < 15; levelNumber++) {
    tinyJumperData[levelNumber] = 0xFFFFFF;
  }
  for (uint8_t appvarOffset = 17; appvarOffset < 81; appvarOffset++) {
    tinyJumperData[appvarOffset] = 255;
  }
  tinyJumperData[16] = 21;
  tinyJumperData[81] = 0;
  tinyJumperData[82] = 0;
}

// converts a float to a string
void toString(float i, uint8_t precision) {
  real_t realTemp = os_FloatToReal(i);
  os_RealToStr(strTemp, &realTemp, 8, 1, precision);
}

// the collision for regular platforms
void rectPlatform(float x, float y, float width, float height) {
  // the collisions for the top and bottom
  if (playerX + 8 > x && playerX < x + width) {
    if (playerYVelocity >= 0 && playerY + 8 >= y && playerY + 7 - playerYVelocity - playerQuicksand * playerYVelocity * 1.5 < y) {
      playerY = y - 8;
      playerYVelocity = 0;
      playerGrounded = 3 * !playerAntiGravity;
    } else if (playerYVelocity < 0 && playerY <= y + height && playerY + 1 - playerYVelocity - playerQuicksand * playerYVelocity * 1.5 > y + height) {
      playerYVelocity = 0;
      playerY = y + height;
      playerGrounded = 3 * playerAntiGravity;
    }
  }
  // the collisions for the sides
  if (playerY + 8 > y && playerY < y + height) {
    if (playerXVelocity >= 0 && playerX + 8 >= x && playerX + 7 - playerXVelocity < x) {
      playerX = x - 8;
      playerXVelocity = 0;
    } else if (playerXVelocity < 0 && playerX <= x + width && playerX - playerXVelocity + 1 > x + width) {
      playerX = x + width;
      playerXVelocity = 0;
    }
  }
}

// the collision for the spikes (and by extension, the lava) 
void spike(float x, float y, float width, float height) {
  if (gfx_CheckRectangleHotspot(x, y, width, height, playerX, playerY, 8, 8)) dead = !invincibleMode; // the player only dies if they have invincible mode off
}

// the looks and collision for the end goal
void endGoal(float x, float y) {
  if (gfx_CheckRectangleHotspot(playerX, playerY, 8, 8, x, y, 16, 16)) goal = true;
  // this controls how the goal's colors change
  goalColor -= timer % 2;
  for (uint8_t rectOffset = 0; rectOffset < 4; rectOffset++) {
    if (goalColor > 23) goalColor = 20;
    gfx_SetColor(goalColor);
    gfx_FillRectangle_NoClip(x + 2 * rectOffset, y + 2 * rectOffset, 16 - 4 * rectOffset, 16 - 4 * rectOffset);
    goalColor++;
  }
}

// the looks and collision for the bounce pads
void bouncePad(float x, float y, float width, float bounceSpeed) {
  // if the player jumps while on the bouncepad, then their speed is changed to the bounceSpeed
  if (playerX + 9 - playerXVelocity >= x && playerX - playerXVelocity - 1 <= x + width && playerY + 12.5 >= y && playerY + 10.5 <= y && playerYVelocity == -5) playerYVelocity = -bounceSpeed;
  // re-draws the bouncepad
  gfx_SetColor(249);
  gfx_FillRectangle_NoClip(x, y, width, 3);
}

// the anti-gravity!
void antiGravity(float x, float y, float width, float height) {
  // draws the anti-gravity
  gfx_SetColor(147);
  gfx_FillRectangle_NoClip(x, y, width, height);
  // collision and stuff for the anti-gravity
  if (gfx_CheckRectangleHotspot(x, y, width, height, playerX, playerY, 8, 8)) {
    if (!playerAntiGravity) playerHasJumped = false;
    anyAntiGravity = true;
  }
}

void quicksand(float x, float y, float width, float height) {
  gfx_SetColor(70);
  gfx_FillRectangle_NoClip(x, y, width, height);
  if (gfx_CheckRectangleHotspot(x, y, width, height, playerX, playerY, 8, 8)) {
    playerXVelocity /= 3;
    playerGrounded = !(kb_Data[1] & kb_2nd);
    playerQuicksand = true;
  }
}

// the player function
void player(void) {
  timer_Set(1, 0); // because the player() function is called every frame at the beginning of that frame, I can put this timer function in here.
  // this is the "speedrun" timer. It keeps track of your time and stores it into strTemp
  if (timer < 0xFFFFFE) timer++;
  toString(timer * .0333251953, 2);
  kb_Scan();
  if (kb_Data[7] & kb_Right) {                        // if the right key is pressed, then
    playerXVelocity += .75;
    if (playerXVelocity > 3) playerXVelocity = 3;   // increase the XVelocity unless the player is going the max speed of 3.
  } else if (kb_Data[7] & kb_Left) {                  // (same for if the left key is pressed, but in the opposite direction)
    playerXVelocity -= .75;
    if (playerXVelocity < -3) playerXVelocity = -3;
  } else {
    if (fabsf(playerXVelocity) < .75) playerXVelocity = 0;
    playerXVelocity -= .75 * fabsf(playerXVelocity) / playerXVelocity;  // if no keys are being pressed, then the player slides to a stop
  }
  if (kb_Data[1] & kb_2nd && playerGrounded) { // if the [2nd] key is pressed, then that means jump. Also, the player has to be grounded in order to jump
    playerYVelocity = (3 * playerQuicksand + 11) * playerAntiGravity - (5.5 + 1.5 * playerQuicksand);
    playerGrounded = 0;
    playerHasJumped = true;
  }
  if (playerGrounded < 3 && (2 * playerAntiGravity - 1)) {
    playerYVelocity -= (2 * playerAntiGravity - 1) * .5;
    if ((2 * playerAntiGravity - 1) * -playerYVelocity >= 0) playerHasJumped = false;
  }
  if (playerHasJumped && !(kb_Data[1] & kb_2nd)) playerYVelocity = .5 * floor(playerYVelocity); // if the [2nd] key is released while jumping, then the jump is reduced. This gives the player more control.
  else playerYVelocity *= 1 - .6 * playerQuicksand;
  gfx_SetColor(5);
  gfx_FillRectangle_NoClip(playerX, playerY, 8, 8); // erase the player before moving it
  // the player moves according to its velocities
  playerX += playerXVelocity;
  playerY += playerYVelocity + playerQuicksand * playerYVelocity * 1.5;
  if (kb_Data[6] & kb_Clear) quit = true; // quit the level if [clear] is pressed
  if (playerGrounded) playerGrounded--; // the playerGrounded variable is set to 3 if you're on the ground, and then decriment each frame that you're not on the ground. This essentially gives the player 2 extra frames to jump when they fall off the ledge, called "coyote time"
  anyAntiGravity = false; // to test if the player is in anti-gravity, the game first has to assume the player is not, before testing to see if they actually are
}

// this screen pops up when you die, and then restarts the level
void deadScreen(void) {
  gfx_SetDrawScreen();
  gfx_ZeroScreen();
  uint8_t randDeathMsg = 22;
  // picks a random variable that is different from the previous random variable
  if (randInt(0, 500)) {
    do {
      randDeathMsg = randInt(0, 21);
    } while (randDeathMsg == prevDeathMsg);
  }
  prevDeathMsg = randDeathMsg;
  // the infamous death messages
  if (tinyJumperData[81] == 0) {
    switch (randDeathMsg) {
      case 0:
        PrintCenteredText("Ouch. You died.", 70, 255);
        break;
      case 1:
        PrintCenteredText("That looked like", 70, 255);
        PrintCenteredText("it hurt.", 92, 255);
        break;
      case 2:
        PrintCenteredText("Tu es mort...", 70, 255);
        PrintCenteredText("encore.", 92, 255);
        break;
      case 3:
        PrintCenteredText("That death...", 70, 255);
        PrintCenteredText("was glorious.", 92, 255);
        break;
      case 4:
        PrintCenteredText("Estas muerto...", 70, 255);
        PrintCenteredText("de nuevo.", 92, 255);
        break;
      case 5:
        PrintCenteredText("Were you", 70, 255);
        PrintCenteredText("even trying?", 92, 255);
        break;
      case 6:
        PrintCenteredText("#$&...*+", 70, 255); // displays japanese characters for "shinda...mata"
        break;
      case 7:
        PrintCenteredText("Don't die!", 70, 255);
        PrintCenteredText("Oops, too late.", 92, 255);
        break;
      case 8:
        PrintCenteredText("So disappointing.", 70, 255);
        break;
      case 9:
        PrintCenteredText("You died.", 70, 255);
        PrintCenteredText("But it was", 92, 255);
        PrintCenteredText("just a dream.", 114, 255);
        break;
      case 10:
        PrintCenteredText("You could've died", 70, 255);
        PrintCenteredText("better than that.", 92, 255);
        break;
      case 11:
        PrintCenteredText("I'm getting a", 70, 255);
        PrintCenteredText("bit tired of", 92, 255);
        PrintCenteredText("respawning you.", 114, 255);
        break;
      case 12:
        PrintCenteredText("Why would you go", 70, 255);
        PrintCenteredText("and die like that?", 92, 255); 
        break;
      case 13:
        PrintCenteredText("Have you given up?", 70, 255);
        break;
      case 14:
        PrintCenteredText("Somebody in", 70, 255);
        PrintCenteredText("this vicinity", 92, 255);
        PrintCenteredText("died recently.", 114, 255);
        break;
      case 15:
        PrintCenteredText("That death will be", 70, 255);
        PrintCenteredText("our little secret.", 92, 255);
        break;
      case 16:
        PrintCenteredText("Could you do", 70, 255);
        PrintCenteredText("that again?", 92, 255);
        PrintCenteredText("I wasn't looking.", 114, 255);
        break;
      case 17:
        PrintCenteredText("You're deader", 70, 255);
        PrintCenteredText("than my", 92, 255);
        PrintCenteredText("childhood dog.", 114, 255);
        break;
      case 18:
        PrintCenteredText("You meant to do", 70, 255);
        PrintCenteredText("that, didn't you?", 92, 255);
        break;
      case 19:
        PrintCenteredText("M4n that de4th", 70, 255);
        PrintCenteredText("wuz stoopid. C4n u", 92, 255);
        PrintCenteredText("even re4d this?", 114, 255);
        msleep(200);
        break;
      case 20:
        PrintCenteredText("I wonder if people", 70, 255);
        PrintCenteredText("even read these.", 92, 255);
        break;
      case 21:
        PrintCenteredText("Dying is for", 70, 255);
        PrintCenteredText("noobs (get pwned!)", 92, 255);
        break;
      default:
        PrintCenteredText("More dark humor.", 70, 51);
        PrintCenteredText("A real nugget!", 92, 51);
        msleep(500);
        break;
    }
    msleep(1000);
  }
  msleep(200);
  kb_Scan();
  dead = false;
  goal = false;
  if (!speedrunnerMode) timer = 0;
}

// this screen pops up when you get to the goal, and then puts you in the next level
void goalScreen(void) {
  gfx_SetDrawScreen();
  gfx_ZeroScreen();
  PrintCenteredText("Wow, you did it.", 50, 255);
  PrintCenteredText("Your time was:", 72, 255);
  PrintCenteredText(strTemp, 94, 255);
  // This checks to see if you got a better time, or if you beat the gold time. If invincible mode is active, it won't
  if ((timer < tinyJumperData[level - 1] || tinyJumperData[level - 1] == 0) && !invincibleMode) {
    // if you've beaten the gold time for the first time, display this
    if ((tinyJumperData[level - 1] > goldTimes[level - 1] || tinyJumperData[level - 1] == 0) && timer <= goldTimes[level - 1]) {
      PrintCenteredText("You beat the", 136, 255);
      PrintCenteredText("gold time!", 158, 255);
    } else { // otherwise, you still beat your time, so display this
      PrintCenteredText("You got", 136, 255);
      PrintCenteredText("a personal best!", 158, 255);
    }
    // unlocks the next level - but only if it is locked to begin with. Locked levels have a time of 16,777,215 (or 0xFFFFFF). Unlocked but uncompleted levels have a time of 0.
    if (level != 15 && tinyJumperData[level] == 0xFFFFFF) tinyJumperData[level] = 0;
    tinyJumperData[level - 1] = timer; // save that best time permanently (or at least until you beat it again)
  }
  // displays what level you're playing
  gfx_SetTextBGColor(0);
  gfx_SetTextFGColor(255);
  gfx_PrintStringXY("Level ", 1, 232);
  gfx_PrintInt(level, 1);
  // if invincible mode is active, display this
  if (invincibleMode) gfx_PrintStringXY("Invincible Mode is on.", 176, 232);
  // reset these settings for the menu
  goal = false;
  // waits for you to stop pressing a button, before waiting for you to press it again. This allows you to either pause the screen, so you can show someone your time; or, it allows you to skip this screen instead.
  while (kb_AnyKey());
  while (!(kb_AnyKey()));
  if (speedrunnerMode) level++;
  else quit = true;
}

void PrintCenteredText(const char *text, uint8_t textYPosition, uint8_t forecolor) {
  fontlib_SetForegroundColor(forecolor);
  fontlib_SetCursorPosition(160 - fontlib_GetStringWidth(text) / 2, textYPosition);
  fontlib_DrawString(text);
}
