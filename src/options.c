#include "options.h"
#include "gfx/sprites.h"
#include "variables.h"
#include "engine.h"
#include "asm/invert.h"

#include <tice.h>
#include <keypadc.h>
#include <fileioc.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

static void lockedBox(unsigned int x, uint8_t y, unsigned int width, uint8_t height) {
  gfx_SetColor(222);
  gfx_FillRectangle_NoClip(x, y, width, height);
  gfx_SetColor(0);
  gfx_Rectangle(x, y, width, height);
  gfx_Line_NoClip(x, y, x + (width - 1), y + (height - 1));
  gfx_Line_NoClip(x, y + (height - 1), x + (width - 1), y);
}

static void settingsSwitch(unsigned int x, uint8_t y, bool turnedOn) {
  if (!turnedOn) {
    gfx_SetColor(45);
    gfx_FillRectangle_NoClip(x, y, 16, 9);
    gfx_SetColor(255);
    gfx_FillRectangle_NoClip(x + 1, y + 1, 7, 7);
  } else {
    gfx_SetColor(36);
    gfx_FillRectangle_NoClip(x, y, 16, 9);
    gfx_SetColor(255);
    gfx_FillRectangle_NoClip(x + 8, y + 1, 7, 7);
  }
}

static void confirmReset(void) {
  gfx_Rectangle_NoClip(211, 179, 19, 11);
  bool keyPressed = false;
  int selectorX = 211;
  uint8_t selectorWidth = 19;
  gfx_SetColor(5);
  gfx_Rectangle_NoClip(198, 168, 82, 11);
  gfx_PrintStringXY("NO     YES", 213, 181);
  while (kb_AnyKey());
  while (!kb_IsDown(kb_KeyClear) && !kb_IsDown(kb_KeyEnter) && !kb_IsDown(kb_Key2nd)) {
    kb_Scan();
    if ((kb_IsDown(kb_KeyEnter) || kb_IsDown(kb_Key2nd)) && selectorX == 242) {
      resetData();
      quit = true;
      levelX = 1;
      levelY = 0;
    }
    if (!kb_Data[7]) keyPressed = false;
    if (kb_Data[7] && !keyPressed) {
      keyPressed = true;
      gfx_SetColor(5);
      gfx_Rectangle_NoClip(selectorX, 179, selectorWidth, 11);
      switch (kb_Data[7]) {
        case kb_Left:
          selectorX -= 31;
          selectorWidth = 19;
          if (selectorX == 180) {
            selectorX = 242;
            selectorWidth = 27;
          }
          break;
        case kb_Right:
          selectorX += 31;
          selectorWidth = 27;
          if (selectorX == 273) {
            selectorX = 211;
            selectorWidth = 19;
          }
          break;
        default:
          break;
      }
      gfx_SetColor(21);
      gfx_Rectangle_NoClip(selectorX, 179, selectorWidth, 11);
    }
  }
  gfx_SetColor(5);
  gfx_FillRectangle_NoClip(211, 179, 58, 11);
  gfx_SetColor(21);
  gfx_Rectangle_NoClip(198, 168, 82, 11);
  while (kb_AnyKey());
}

static void customizePlayer(void) {
  // find out where to put the cursor
  bool keyPressed;
  unsigned int playerColor = tinyJumperData[16];
  uint8_t cursorX = 16;
  uint8_t cursorY = 84;
  uint8_t width = 8;
  uint8_t height = 7;
  if (playerColor > 256) {
    cursorY = 173;
    cursorX = 18 * (playerColor - 257) + 35;
    width = 18;
    height = 18;
  } else if (playerColor == 256) {
    cursorX = 31;
    cursorY = 197;
    width = 98;
    height = 12;
  } else if (playerColor != 21) {
    cursorX = 16 + 8 * (playerColor % 16);
    cursorY = 49 + 7 * floor(playerColor / 16);
  }
  gfx_SetColor(5);
  gfx_Rectangle_NoClip(21, 213, 119, 12);
  gfx_BlitScreen();
  gfx_SetColor(255);
  if (playerColor > 131 && playerColor % 8 > 3 && playerColor < 256) {
    gfx_SetColor(0);
  }
  gfx_Rectangle_NoClip(cursorX, cursorY, width, height);
  while (kb_AnyKey());
  while (!kb_IsDown(kb_KeyEnter) && !kb_IsDown(kb_Key2nd)) {
    kb_Scan();
    if (!kb_AnyKey()) {
      keyPressed = false;
      timer_Set(1, 0);
    }
    if (kb_IsDown(kb_KeyClear)) {
      gfx_BlitBuffer();
      gfx_SetColor(21);
      gfx_Rectangle_NoClip(21, 213, 119, 12);
      while (kb_AnyKey());
      return;
    }
    if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
      if (kb_IsDown(kb_KeyRight)) {
        playerColor++;
        if (cursorY < 173 && cursorY > 84) {
          cursorX += 8;
          if (cursorX > 136) {
            if (cursorY == 154) {
              if (golds > 9) {
                playerColor++;
                cursorX = 35;
                cursorY = 173;
                width = 18;
                height = 18;
              } else {
                playerColor = 21;
                cursorX = 16;
                cursorY = 84;
                width = 8;
                height = 7;
              }
            } else {
              cursorX = 16;
              cursorY += 7;
            }
          }
        } else if (cursorY == 84) {
          cursorY += 7;
          playerColor = 96;
        } else if (cursorY == 173) {
          cursorX += 18;
          if (cursorX > 107) {
            if (golds < 15) {
              playerColor = 21;
              cursorX = 16;
              cursorY = 84;
              width = 8;
              height = 7;
            } else {
              playerColor = 256;
              cursorX = 31;
              cursorY = 197;
              width = 98;
              height = 12;
            }
          }
        } else if (cursorY == 197) {
          playerColor = 21;
          cursorX = 16;
          cursorY = 84;
          width = 8;
          height = 7;
        }
      } else if (kb_IsDown(kb_KeyLeft)) {
        playerColor--;
        if (cursorY < 173 && cursorY > 84) {
          cursorX -= 8;
          if (cursorX < 16) {
            if (cursorY == 91) {
              playerColor = 21;
              cursorX = 16;
              cursorY -= 7;
            } else {
              cursorX = 136;
              cursorY -= 7;
            }
          }
        } else if (cursorY == 84) {
          if (golds > 14) {
            playerColor = 256;
            cursorX = 31;
            cursorY = 197;
            width = 98;
            height = 12;
          } else if (golds > 9) {
            playerColor = 261;
            cursorX = 107;
            cursorY = 173;
            width = 18;
            height = 18;
          } else {
            playerColor = 255;
            cursorX = 136;
            cursorY = 154;
          }
        } else if (cursorY == 173) {
          cursorX -= 18;
          if (cursorX < 35) {
            playerColor--;
            cursorX = 136;
            cursorY = 154;
            width = 8;
            height = 7;
          }
        } else if (cursorY == 197) {
          playerColor = 261;
          cursorX = 107;
          cursorY = 173;
          width = 18;
          height = 18;
        }
      }
      if (kb_IsDown(kb_KeyDown)) {
        if (cursorY < 154 && cursorY > 83) {
          playerColor += 16;
          if (playerColor == 37) playerColor = 96;
          cursorY += 7;
        } else if (cursorY == 154) {
          if (golds > 9) {
            playerColor = 257;
            cursorY = 173;
            cursorX = 35;
            width = 18;
            height = 18;
          } else {
            playerColor = 21;
            cursorX = 16;
            cursorY = 84;
          }
        } else if (cursorY == 173) {
          if (golds > 14) {
            playerColor = 256;
            cursorX = 31;
            cursorY = 197;
            width = 98;
            height = 12;
          } else {
            playerColor = 21;
            cursorX = 16;
            cursorY = 84;
            width = 8;
            height = 7;
          }
        } else if (cursorY == 197) {
          playerColor = 21;
          cursorX = 16;
          cursorY = 84;
          width = 8;
          height = 7;
        }
      } else if (kb_IsDown(kb_KeyUp)) {
        if (cursorY < 173 && cursorY > 91) {
          playerColor -= 16;
          cursorY -= 7;
        } else if (cursorY == 91) {
          playerColor = 21;
          cursorX = 16;
          cursorY = 84;
        } else if (cursorY == 84) {
          if (golds > 14) {
            playerColor = 256;
            cursorX = 31;
            cursorY = 197;
            width = 98;
            height = 12;
          } else if (golds > 9) {
            playerColor = 261;
            cursorX = 107;
            cursorY = 173;
            width = 18;
            height = 18;
          } else {
            playerColor = 255;
            cursorX = 136;
            cursorY = 154;
          }
        } else if (cursorY == 197) {
          playerColor = 261;
          cursorX = 107;
          cursorY = 173;
          width = 18;
          height = 18;
        } else if (cursorY == 173) {
          playerColor = 255;
          cursorX = 136;
          cursorY = 154;
          width = 8;
          height = 7;
        }
      }
      gfx_BlitRectangle(gfx_buffer, 16, 84, 128, 125);
      gfx_SetColor(255);
      if (playerColor > 131 && playerColor % 8 > 3 && playerColor < 256) {
        gfx_SetColor(0);
      }
      gfx_Rectangle(cursorX, cursorY, width, height);
      if (!keyPressed) {
        while (timer_Get(1) < 9000 && kb_Data[7]) kb_Scan();
      }
      keyPressed = true;
      timer_Set(1, 0);
      gfx_SetColor(5);
      gfx_FillRectangle_NoClip(68, 56, 24, 24);
      if (playerColor < 256) {
        gfx_SetColor(playerColor);
        gfx_FillRectangle_NoClip(68, 56, 24, 24);
      } else {
        gfx_ScaledTransparentSprite_NoClip(playerSprites[playerColor - 256], 68, 56, 3, 3);
      }
    }
  }
  gfx_BlitRectangle(gfx_buffer, 16, 84, 128, 125);
  tinyJumperData[16] = playerColor;
  gfx_SetColor(21);
  gfx_Rectangle_NoClip(21, 213, 119, 12);
  while (kb_AnyKey());
}

void options(void) {
  bool keyPressed;
  uint8_t colorNum = 96;
  uint8_t paletteY = 91;
  uint8_t selectorX = 168;
  uint8_t selectorY = 58;
  uint8_t selectorWidth = 20;
  uint8_t selectorHeight = 13;
  gfx_SetDrawScreen();
  gfx_FillScreen(5);
  gfx_SetColor(21);
  gfx_FillRectangle_NoClip(0, 0, 320, 40);
  gfx_SetTextBGColor(5);
  gfx_SetTextFGColor(255);
  gfx_PrintStringXY("Tiny Jumper 2.0     (c) 2022 RoccoLox Programs", 8, 231);
  gfx_PrintStringXY("Customize Player", 23, 215);
  gfx_PrintStringXY("Disable death", 193, 60);
  gfx_PrintStringXY("messages", 193, 70);
  gfx_PrintStringXY("Invert Colors", 192, 90);
  gfx_PrintStringXY("Invinciblity Mode", 192, 120);
  gfx_PrintStringXY("(Times aren't saved)", 172, 132);
  gfx_PrintStringXY("Reset Times", 200, 170);
  if (golds > 14) {
    gfx_PrintStringXY("Custom Design", 33, 199);
    gfx_PrintStringXY("Speedrunner Mode", 193, 150);
    settingsSwitch(170, 150, speedrunnerMode);
  }
  gfx_SetTextFGColor(183);
  gfx_PrintStringXY("Your Player", 41, 44);
  gfx_PrintStringXY("Game Settings", 193, 44);
  gfx_PrintStringXY("Total gold times: ", 96, 29);
  gfx_PrintInt(golds, 2);
  if (golds > 14) {
    gfx_SetTextFGColor(7);
    gfx_PrintStringXY("Originally created", 177, 200);
    gfx_PrintStringXY("by KRoD", 215, 210);
  }
  PrintCenteredText("Options", 5, 183);
  gfx_SetColor(255);
  gfx_HorizLine_NoClip(5, 229, 311);
  gfx_VertLine_NoClip(160, 43, 183);
  if (tinyJumperData[16] < 256) {
    gfx_SetColor(tinyJumperData[16]);
    gfx_FillRectangle_NoClip(68, 56, 24, 24);
  } else {
    gfx_ScaledTransparentSprite_NoClip(playerSprites[tinyJumperData[16] - 256], 68, 56, 3, 3);
  }
  if (golds > 4) {
    gfx_SetColor(21);
    gfx_FillRectangle_NoClip(16, 84, 8, 7);
    do {
      for (uint8_t paletteX = 16; paletteX < 144; paletteX += 8) {
        gfx_SetColor(colorNum);
        gfx_FillRectangle_NoClip(paletteX, paletteY, 8, 7);
        colorNum++;
      }
      paletteY += 7;
    } while (colorNum);
  } else {
    lockedBox(16, 84, 128, 77);
    gfx_SetTextFGColor(0);
    gfx_PrintStringXY("5 golds", 56, 89);
  }
  if (golds > 9) {
    for (uint8_t displaySprites = 1; displaySprites < 6; displaySprites++) {
      gfx_ScaledTransparentSprite_NoClip(playerSprites[displaySprites], 18 * displaySprites + 18, 174, 2, 2);
    }
  } else {
    gfx_SetTextFGColor(255);
    gfx_PrintStringXY("10 golds", 53, 164);
    for (uint8_t displayBox = 0; displayBox < 5; displayBox++) {
      lockedBox(18 * displayBox + 36, 174, 16, 16);
    }
  }
  settingsSwitch(170, 60, tinyJumperData[81]);
  settingsSwitch(170, 90, tinyJumperData[82]);
  settingsSwitch(170, 120, invincibleMode);
  gfx_SetTextFGColor(255);
  gfx_SetColor(21);
  gfx_Rectangle_NoClip(selectorX, selectorY, selectorWidth, selectorHeight);
  while (kb_AnyKey());
  while (!quit) {
    kb_Scan();
    if (!kb_AnyKey()) {
      keyPressed = false;
      timer_Set(1, 0);
    }
    if (kb_IsDown(kb_KeyClear) || kb_IsDown(kb_KeyMode)) quit = true;
    if ((kb_IsDown(kb_KeyEnter) || kb_IsDown(kb_Key2nd)) && !keyPressed) {
      keyPressed = true;
      switch (selectorY) {
        case 58:
          tinyJumperData[81] = !tinyJumperData[81];
          settingsSwitch(selectorX + 2, selectorY + 2, tinyJumperData[81]);
          break;
        case 88:
          tinyJumperData[82] = !tinyJumperData[82];
          invertPalette();
          settingsSwitch(selectorX + 2, selectorY + 2, tinyJumperData[82]);
          break;
        case 118:
          invincibleMode = !invincibleMode;
          settingsSwitch(selectorX + 2, selectorY + 2, invincibleMode);
          break;
        case 148:
          speedrunnerMode = !speedrunnerMode;
          settingsSwitch(selectorX + 2, selectorY + 2, speedrunnerMode);
          break;
        case 168:
          confirmReset();
          break;
        case 213:
          if (golds > 4) {
            customizePlayer();
          }
          break;
        default:
          break;
      }
    }
    if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
      if (!(kb_IsDown(kb_KeyLeft) && selectorX == 21) && !(kb_IsDown(kb_KeyRight) && selectorX == 168)) {
        gfx_SetColor(5);
        gfx_Rectangle_NoClip(selectorX, selectorY, selectorWidth, selectorHeight);
      }
      switch (kb_Data[7]) {
        case kb_Left:
          selectorX = 21;
          selectorY = 213;
          selectorWidth = 119;
          selectorHeight = 12;
          break;
        case kb_Right:
          if (selectorX == 21) {
            selectorX = 168;
            selectorY = 58;
            selectorWidth = 20;
            selectorHeight = 13;
          }
          break;
        case kb_Up:
          if (selectorX != 21) {
            selectorY -= 30;
            if (selectorY == 138 && golds < 15) selectorY = 118;
            if (selectorY == 138) selectorY = 148;
            if (selectorY == 28) selectorY = 168;
            if (selectorY == 168) {
              selectorX = 198;
              selectorWidth = 82;
              selectorHeight = 11;
            } else {
              selectorX = 168;
              selectorWidth = 20;
              selectorHeight = 13;
            }
          }
          break;
        case kb_Down:
          if (selectorX != 21) {
            selectorY += 30;
            if (selectorY == 148 && golds < 15) selectorY = 168;
            if (selectorY == 178) selectorY = 168;
            if (selectorY == 198) selectorY = 58;
            if (selectorY == 168) {
              selectorX = 198;
              selectorWidth = 82;
              selectorHeight = 11;
            } else {
              selectorX = 168;
              selectorWidth = 20;
              selectorHeight = 13;
            }
          }
          break;
        default:
          break;
      }
      gfx_SetColor(21);
      gfx_Rectangle_NoClip(selectorX, selectorY, selectorWidth, selectorHeight);
      if (!keyPressed) {
        while (timer_Get(1) < 9000 && kb_Data[7]) kb_Scan();
      }
      keyPressed = true;
      timer_Set(1, 0);
    }
  }
  // resets these values for the home screen
  quit = false;
  gfx_SetDrawBuffer();
  gfx_SetTextScale(1, 1);
  level = 0;
}
