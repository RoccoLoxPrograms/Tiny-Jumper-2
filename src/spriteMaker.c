#include "spriteMaker.h"
#include "variables.h"
#include "engine.h"

#include <keypadc.h>
#include <ti/getcsc.h>
#include <sys/timers.h>

static void drawSquare(uint24_t cursorX, uint8_t cursorY, uint8_t color) {
  if (color == 79) {
    gfx_SetColor(34);
    gfx_FillRectangle_NoClip(cursorX, cursorY, 8, 8);
    gfx_SetColor(181);
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
  gfx_FillScreen(5);
  gfx_SetColor(21);
  gfx_FillRectangle_NoClip(0, 0, 320, 40);
  PrintCenteredText("Customize", 5, 183);
  gfx_PrintStringXY("Make a custom sprite", 90, 29);
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
      gfx_SetColor(colorNum);
      gfx_Rectangle_NoClip(cursorX, cursorY, 13, 10);
      if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
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
            cursorY += 10 * (cursorY < 170);
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
      colorNum = (cursorX - 16) / 13 + 96 + 16 * (cursorY / 10 - 9);
      gfx_SetColor(255);
      if (colorNum > 131 && colorNum % 8 > 3 && colorNum < 256) {
        gfx_SetColor(0);
      }
      gfx_Rectangle_NoClip(cursorX, cursorY, 13, 10);
      if (kb_IsDown(kb_Key2nd)) {
        pickColor = false;
        cursorX = 240;
        cursorY = 108;
        playerColor = colorNum;     
      }
    } else {
      gfx_SetColor(tinyJumperData[cursorX / 8 - 13 + cursorY - 108]);
      gfx_Rectangle_NoClip(cursorX, cursorY, 8, 8);
      if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
        switch (kb_Data[7]) {
          case kb_Right:
            cursorX += 8 * (cursorX < 296);
            break;
          case kb_Left:
            cursorX -= 8;
            if (cursorX < 240) {
              pickColor = true;
              cursorX = 211;
              cursorY -= cursorY % 10;
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
      colorNum = tinyJumperData[cursorX / 8 - 13 + cursorY - 108];
      gfx_SetColor(255);
      if (colorNum > 131 && colorNum % 8 > 3 && colorNum < 256) {
        gfx_SetColor(0);
      }
      gfx_Rectangle_NoClip(cursorX, cursorY, 8, 8);
      if (kb_IsDown(kb_KeyMode)) {
        pickColor = true;
        cursorX = 16;
        cursorY = 90;
      }
    }
  } while (!kb_IsDown(kb_KeyEnter) && !kb_IsDown(kb_KeyClear));
  gfx_BlitBuffer();
}
