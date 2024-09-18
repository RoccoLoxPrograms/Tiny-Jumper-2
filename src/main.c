#include "gfx/sprites.h"
#include "font/font.h"
#include "variables.h"
#include "engine.h"
#include "levels.h"
#include "options.h"
#include "asm/invert.h"

#include <tice.h>
#include <keypadc.h>
#include <fileioc.h>

// these are the player's variables and many states of existence
float playerX;
float playerY;
float playerXVelocity;
float playerYVelocity;
bool playerHasJumped;
uint8_t playerGrounded;
bool playerAntiGravity;
bool anyAntiGravity;
bool playerQuicksand;
bool invincibleMode = false;
bool speedrunnerMode = false;

gfx_sprite_t *playerSprites[7];

// the game runs at 30.00732601 frames a second, or .0333251953 seconds per frame
unsigned int timer;

char strTemp[10];
uint8_t prevDeathMsg = 11;
bool dead = false;
bool quit = false;
bool goal = false;
uint8_t level = 0;
uint8_t levelX = 1;
uint8_t levelY = 0;
unsigned int tinyJumperData[84];
uint8_t golds = 0;
uint8_t goalColor = 20;

const unsigned int goldTimes[16] = {288, 300, 405, 360, 327, 405, 750, 201, 360, 1000, 1000, 1000, 1000, 1000, 1000, 1000};

static void endSpeedrun(void) {
  gfx_SetDrawScreen();
  gfx_ZeroScreen();
  PrintCenteredText("Dang, doggy, you", 50, 255);
  PrintCenteredText("finished that", 72, 255);
  PrintCenteredText("speedrun! Your", 94, 255);
  PrintCenteredText("final time was:", 116, 255);
  PrintCenteredText(strTemp, 138, 255);
  tinyJumperData[83] = timer;
  goal = false;
  while (kb_AnyKey());
  while (!(kb_AnyKey()));
  quit = true;
}

static void menu(void) {
  bool keyFirstPressed;
  playerAntiGravity = false;
  playerQuicksand = false;
  quit = false;
  golds = 0;
  gfx_SetDrawScreen();
  gfx_FillScreen(5);
  gfx_SetTextFGColor(0);
  for (uint8_t levelDrawerY = 0; levelDrawerY < 3; levelDrawerY++) {
    for (uint8_t levelDrawerX = 0; levelDrawerX < 5; levelDrawerX++) {
      if (tinyJumperData[levelDrawerX + 5 * levelDrawerY] == 0xFFFFFF) { // if the level is locked,
        gfx_SetColor(181);                                            // set the color to gray
        gfx_SetTextBGColor(181);
      } else if (!tinyJumperData[levelDrawerX + 5 * levelDrawerY]) { // if the level is incomplete,
        gfx_SetColor(183);                                           // set the color to very light green
        gfx_SetTextBGColor(183);
      } else if (tinyJumperData[levelDrawerX + 5 * levelDrawerY] <= goldTimes[levelDrawerX + 5 * levelDrawerY]) { // if the level is under the gold time,
        gfx_SetColor(72);                                                                                         // set the color to yellow (aka "gold" colored)
        gfx_SetTextBGColor(72);
        golds++;
      } else {
        gfx_SetColor(21); // otherwise, the level is green to show that it's completed
        gfx_SetTextBGColor(21);
      }
      gfx_FillRectangle_NoClip(levelDrawerX * 60 + 21, levelDrawerY * 60 + 61, 38, 38);
      if (tinyJumperData[levelDrawerX + 5 * levelDrawerY] <= goldTimes[levelDrawerX + 5 * levelDrawerY] && tinyJumperData[levelDrawerX + 5 * levelDrawerY] != 0) {
        gfx_ScaledTransparentSprite_NoClip(GoldMedal, levelDrawerX * 60 + 22, levelDrawerY * 60 + 61, 2, 2);
      }
      // displays the number of the level in the center of the square
      toString(1 + levelDrawerX + 5 * levelDrawerY, 0);
      gfx_PrintStringXY(strTemp, levelDrawerX * 60 + 40 - gfx_GetStringWidth(strTemp) / 2, levelDrawerY * 60 + 76);
    }
  }
  gfx_SetTextFGColor(255);
  gfx_SetTextBGColor(5);
  gfx_SetTextTransparentColor(5);
  gfx_PrintStringXY("Press [mode] for options", 77, 47);
  ///////////////////////golds = 15;
  if (golds > 14) {
    gfx_PrintStringXY("BONUS LEVEL!", 118, 227);
  }
  gfx_SetColor(21);
  gfx_FillRectangle_NoClip(0, 0, 320, 40);
  gfx_SetTextBGColor(21);
  gfx_SetTextFGColor(183);
  PrintCenteredText("Tiny Jumper 2", 5, 183);
  gfx_SetTextScale(1, 1);
  gfx_PrintStringXY("Best time:", 6, 29);
  gfx_PrintStringXY("Gold time:", 215, 29);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (kb_AnyKey());
  while (!quit && !level) {
    // displays the cursor
    gfx_SetColor(255);
    if (levelY == 3) {
      levelX = 1;
      gfx_Rectangle_NoClip(116, 225, 89, 11);
    } else {
      gfx_Rectangle_NoClip(levelX * 60 - 40, levelY * 60 + 60, 40, 40);
    }
    // displays your current best time
    toString(tinyJumperData[levelX + 5 * levelY - 1] * .0333251953, 2);
    gfx_PrintStringXY(strTemp, 74, 29);
    // displays the time needed to get a golden level
    toString(goldTimes[levelX + 5 * levelY - 1] * .0333251953, 2);
    gfx_PrintStringXY(strTemp, 281, 29);
    gfx_BlitBuffer();
    while (kb_AnyKey() && timer_Get(1) < 3000 + 6000 * keyFirstPressed) {
      kb_Scan();
    }
    keyFirstPressed = false;
    while (!kb_AnyKey()) {
      kb_Scan();
      keyFirstPressed = true;
    }
    timer_Set(1, 0);
    // erases the cursor-box
    gfx_SetColor(5);
    if (levelY == 3) {
      gfx_Rectangle_NoClip(116, 225, 89, 11);
    } else {
      gfx_Rectangle_NoClip(levelX * 60 - 40, levelY * 60 + 60, 40, 40);
    }
    // erases the best time/golden time
    gfx_SetColor(21);
    gfx_FillRectangle_NoClip(75, 29, 55, 10);
    gfx_FillRectangle_NoClip(277, 29, 40, 10);
    // decides which direction the cursor should go based on what buttons are being pressed
    do {
      if (kb_Data[7] & kb_Right) {
        levelX++;
        if (levelX == 6 - 4 * (levelY == 3)) {
          levelX = 1;
          levelY++;
        }
      } else if (kb_Data[7] & kb_Down) {
        levelY++;
      } else if (kb_Data[7] & kb_Left) {
        levelX--;
        if (levelX == 0) {
          levelX = 5;
          levelY--;
        }
      } else if (kb_Data[7] & kb_Up) {
        levelY--;
      }
      if (levelY == 255) {
        levelY = 2 + (golds > 14);
      }
      if (levelY == 3 + (golds > 14)) {
        levelY = 0;
      }
    } while (tinyJumperData[levelX + 5 * levelY - 1] == 0xFFFFFF);
    // if [mode] is pressed, then do the settings screen
    if (kb_Data[1] & kb_Mode) {
      level = 18;
    }
    // if clear is pressed, quit
    if (kb_Data[6] & kb_Clear) {
      quit = true;
    }
    // if [2nd] is pressed, play the selected level
    if ((kb_Data[1] & kb_2nd) || (kb_Data[6] & kb_Enter)) {
      level = levelX + 5 * levelY; // starts the level that the cursor has selected
      gfx_SetDrawScreen();
      // display this text in order to give the person time to get ready
      gfx_ZeroScreen();
      PrintCenteredText("Are you ready?", 70, 255);
      msleep(600);
      PrintCenteredText("Get set...", 92, 255);
      msleep(600);
      if (tinyJumperData[16] > 255) {
        gfx_FlipSpriteX(playerSprites[tinyJumperData[16] - 256], playerSprites[6]);
      }
      gfx_SetTextScale(1, 1);
      gfx_SetTextBGColor(247);
      timer = 0;
    }
  }
}

int main(void) {
  ti_var_t tinyDataSlot = ti_Open("TJ2Data", "r");
  // if the appvar "TJ2Data" does not exist, then reset all the times
  if (!tinyDataSlot) {
    resetData();
  } else {
    ti_Read(&tinyJumperData, 252, 1, tinyDataSlot);
  }
  gfx_Begin();
  fontlib_SetFont(TJFont, 0);
  fontlib_SetTransparency(true);
  gfx_SetTransparentColor(79);
  gfx_SetPalette((global_palette + 2), sizeof_global_palette, 0);
  if (tinyJumperData[82] == 1) {
    invertPalette();
  }
  gfx_UninitedSprite(Custom, 8, 8);
  Custom->height = 8;
  Custom->width = 8;
  gfx_SetDrawBuffer();
  for (int8_t drawOffset1 = 0; drawOffset1 < 8; drawOffset1++) {
    for (int8_t drawOffset2 = 0; drawOffset2 < 8; drawOffset2++) {
      gfx_SetColor(tinyJumperData[17 + drawOffset2 + 8 * drawOffset1]);
      gfx_SetPixel(drawOffset2, drawOffset1);
    }
  }
  gfx_GetSprite(Custom, 0, 0);
  playerSprites[0] = Custom;
  playerSprites[1] = Chomp;
  playerSprites[2] = Glitch;
  playerSprites[3] = Paint;
  playerSprites[4] = MushroomSkin;
  playerSprites[5] = RoccoLoxSkin;
  playerSprites[6] = Flipped;
  timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
  rtc_Enable(RTC_SEC_INT);
  srandom(rtc_Time());
  while (!quit) {
    playerXVelocity = 0;
    playerYVelocity = 1;
    switch (level) {
      case 1:
        level1();
        break;
      case 2:
        level2();
        break;
      case 3:
        level3();
        break;
      case 4:
        level4();
        break;
      case 5:
        level5();
        break;
      case 6:
        level6();
        break;
      case 7:
        level7();
        break;
      case 8:
        level8();
        break;
      case 9:
        level9();
        break;
      case 10:
        level10();
        break;
      case 11:
        level11();
        break;
      case 12:
        level12();
        break;
      case 13:
        level13();
        break;
      case 14:
        level14();
        break;
      case 15:
        level15();
        break;
      case 16:
        bonusLevel2();
        break;
      case 17:
        endSpeedrun();
        break;
      case 18:
        options();
        break;
      default:
        break;
    }
    if (dead) {
      deadScreen();
    }
    if (goal) {
      goalScreen();
    }
    level *= !quit;
    if (level == 0) {
      menu();
    }
  }
  gfx_End();
  tinyDataSlot = ti_Open("TJ2Data", "w+");
  ti_Write(&tinyJumperData, 252, 1, tinyDataSlot);
  ti_SetArchiveStatus(true, tinyDataSlot);
  return 0;
}
