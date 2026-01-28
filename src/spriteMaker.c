#include "spriteMaker.h"
#include "variables.h"
#include "engine.h"

#include <keypadc.h>
#include <ti/getcsc.h>
#include <sys/timers.h>

static void drawSquare(uint24_t cursorX, uint8_t cursorY, uint8_t color) {
  if (color == COLOR_TRANSP) {
    gfx_SetColor(COLOR_WHITE);
    gfx_FillRectangle_NoClip(cursorX, cursorY, 8, 8);
    gfx_SetColor(COLOR_LIGHT_GRAY);
    uint24_t transparentDrawerX = cursorX;
    for (uint8_t transparentDrawerY = cursorY; transparentDrawerY < cursorY + 8; transparentDrawerY += 2){
      do {
        gfx_Rectangle_NoClip(transparentDrawerX, transparentDrawerY, 2, 2);
        transparentDrawerX += 4;
      } while (transparentDrawerX < cursorX + 7);
      transparentDrawerX -= 6 + 4 * (transparentDrawerX == cursorX + 10);
    }
  } else {
    gfx_SetColor(color);
    gfx_FillRectangle_NoClip(cursorX, cursorY, 8, 8);
  }
}

void spriteMaker(void) {
  gfx_BlitScreen();
  gfx_FillScreen(COLOR_DARK_PURPLE);
  gfx_SetColor(COLOR_OLIVE);
  gfx_FillRectangle_NoClip(0, 0, 320, 40);
  PrintCenteredText("Customize", 5, COLOR_LIGHT_GREEN);
  gfx_SetTextBGColor(COLOR_OLIVE);
  gfx_SetTextFGColor(COLOR_LIGHT_GREEN);
  gfx_PrintStringXY("Make a custom sprite", 90, 29);
  gfx_SetTextBGColor(COLOR_PURPLE);
  gfx_SetTextFGColor(COLOR_WHITE);
  gfx_PrintStringXY("Press 2ND to draw, MODE to select color,", 6, 200);
  gfx_PrintStringXY("ALPHA to erase, CLEAR to quit without saving,", 6, 212);
  gfx_PrintStringXY("and ENTER to save the design.", 6, 224);
  uint24_t cursorX = 240;
  uint8_t cursorY = 108;
  uint8_t playerColor = 255;
  for (uint8_t spriteDrawer = 17; spriteDrawer < 81; spriteDrawer++) {
    drawSquare(cursorX, cursorY, tinyJumperData[spriteDrawer]);
    cursorX += 8;
    if (cursorX > 303) {
        cursorX = 240;
        cursorY += 8;
    }
  }
  cursorX = 240;
  cursorY = 108;
  // draw the palette color chooser thing
  uint8_t colorNum = 96;
  uint8_t paletteY = 90;
  do {
    for (uint8_t paletteX = 16; paletteX < 224; paletteX += 13) {
      gfx_SetColor(colorNum);
      gfx_FillRectangle_NoClip(paletteX, paletteY, 13, 10);
      colorNum++;
    }
    paletteY += 10;
  } while (colorNum);
  while (kb_AnyKey()) {
    kb_Scan();
  }
  bool keyPressed;
  bool pickColor = false;
  do {
    kb_Scan();
    if (!kb_AnyKey()) {
      keyPressed = false;
      timer_Set(1, 0);
    }
    if (pickColor) {
      if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
        gfx_SetColor(colorNum);
        gfx_Rectangle_NoClip(cursorX, cursorY, 13, 10);
        switch (kb_Data[7]) {
          case kb_Right:
            cursorX += 13;
            if (cursorX > 211) {
              pickColor = false;
              cursorX = 240;
              cursorY -= cursorY % 8 + 4;
              if (cursorY < 108) {
                cursorY = 108;
              } else if (cursorY > 164) {
                cursorY = 164;
              }
            }
            break;
          case kb_Left:
            cursorX -= 13 * (cursorX > 16);
            break;
          case kb_Up:
            cursorY -= 10 * (cursorY > 90);
            break;
          case kb_Down:
            cursorY += 10 * (cursorY < 180);
            break;
          default:
            break;
        }
        while (!keyPressed && timer_Get(1) < 3000 && kb_Data[7]) {
          kb_Scan();
        }
        keyPressed = true;
        timer_Set(1, 0);
      }
      if (kb_IsDown(kb_Key2nd)) {
        gfx_SetColor(colorNum);
        gfx_Rectangle_NoClip(cursorX, cursorY, 13, 10);
        pickColor = false;
        cursorX = 240;
        cursorY = 108;
        playerColor = colorNum;
        while (kb_AnyKey());
      }
      colorNum = (cursorX - 16) / 13 + 96 + 16 * (cursorY / 10 - 9);
      gfx_SetColor(COLOR_WHITE);
      if (colorNum > 131 && colorNum % 8 > 3) {
        gfx_SetColor(COLOR_BLACK);
      }
      if (pickColor) {
        gfx_Rectangle_NoClip(cursorX, cursorY, 13, 10);
      }
    } else {
      if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
        drawSquare(cursorX, cursorY, gfx_GetPixel(cursorX + 1, cursorY + 1) + (COLOR_TRANSP - COLOR_LIGHT_GRAY) * (gfx_GetPixel(cursorX + 1, cursorY + 1) == COLOR_LIGHT_GRAY));
        switch (kb_Data[7]) {
          case kb_Right:
            cursorX += 8 * (cursorX < 296);
            break;
          case kb_Left:
            cursorX -= 8;
            if (cursorX < 240) {
              cursorX = 240;
              if (!kb_IsDown(kb_Key2nd) && !kb_IsDown(kb_KeyAlpha)) {
                pickColor = true;
                cursorX = 211;
                cursorY -= cursorY % 10;
              }
            }
            break;
          case kb_Up:
            cursorY -= 8 * (cursorY > 108);
            break;
          case kb_Down:
            cursorY += 8 * (cursorY < 164);
            break;
          default:
            break;
        }
        while (!keyPressed && timer_Get(1) < 3000 && kb_Data[7]) {
          kb_Scan();
        }
        keyPressed = true;
        timer_Set(1, 0);
      }
      if (kb_IsDown(kb_Key2nd)) {
        drawSquare(cursorX, cursorY, playerColor);
      } else if (kb_IsDown(kb_KeyAlpha)) {
        drawSquare(cursorX, cursorY, COLOR_TRANSP);
      } else if (kb_IsDown(kb_KeyMode)) {
        drawSquare(cursorX, cursorY, gfx_GetPixel(cursorX + 1, cursorY + 1) + (COLOR_TRANSP - COLOR_LIGHT_GRAY) * (gfx_GetPixel(cursorX + 1, cursorY + 1) == COLOR_LIGHT_GRAY));
        pickColor = true;
        cursorX = 16;
        cursorY = 90;
      }
      colorNum = gfx_GetPixel(cursorX + 1, cursorY + 1);
      gfx_SetColor(COLOR_WHITE);
      if (colorNum > 131 && colorNum % 8 > 3) {
        gfx_SetColor(COLOR_BLACK);
      }
      if (!pickColor) {
        gfx_Rectangle_NoClip(cursorX, cursorY, 8, 8);
      }
    }
  } while (!kb_IsDown(kb_KeyEnter) && !kb_IsDown(kb_KeyClear));
  if (kb_IsDown(kb_KeyEnter)) {
    for (int8_t i = 0; i < 8; i++) {
      for (int8_t j = 0; j < 8; j++) {
        if (gfx_GetPixel(8 * i + 241, 8 * j + 109) == COLOR_LIGHT_GRAY) {
          tinyJumperData[17 + i + 8 * j] = COLOR_TRANSP;
        } else {
          tinyJumperData[17 + i + 8 * j] = gfx_GetPixel(8 * i + 241, 8 * j + 109);
        }
        gfx_SetColor(tinyJumperData[17 + i + 8 * j]);
        gfx_SetPixel(i, j);
      }
    }
  gfx_GetSprite(playerSprites[0], 0, 0);
  }
  gfx_BlitBuffer();
  gfx_SetColor(COLOR_DARK_PURPLE);
  gfx_FillRectangle_NoClip(68, 56, 24, 24);
  gfx_ScaledTransparentSprite_NoClip(playerSprites[0], 68, 56, 3, 3);
}
