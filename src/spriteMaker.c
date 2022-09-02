#include "spriteMaker.h"
#include "variables.h"
#include "engine.h"

#include <keypadc.h>
#include <ti/getcsc.h>
#include <sys/timers.h>

void drawTransparentSquare(uint24_t cursorX, uint8_t cursorY) {
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
  for (uint8_t spriteDrawer = 17; spriteDrawer < 81; spriteDrawer++) {
    tinyJumperData[spriteDrawer] = 79;
    if (tinyJumperData[spriteDrawer] == 79) {
      drawTransparentSquare(cursorX, cursorY);
    } else {
      gfx_SetColor(tinyJumperData[spriteDrawer]);
      gfx_FillRectangle_NoClip(cursorX, cursorY, 8, 8);
    }
    cursorX += 8;
    if (cursorX > 303) {
        cursorX = 240;
        cursorY += 8;
    }
  }
  cursorX = 240;
  cursorY = 108;
  ////////////////////////////uint8_t color = 0;
  // draw the palette color chooser thing
  while (kb_AnyKey()) {
    kb_Scan();
  }
  bool keyPressed;
  do {
    // code for deciding what color to make the cursor
    gfx_SetColor(255);
    gfx_Rectangle_NoClip(cursorX, cursorY, 8, 8);
    kb_Scan();
    if (!kb_AnyKey()) {
      keyPressed = false;
      timer_Set(1, 0);
    }
    if (kb_Data[7] && (!keyPressed || timer_Get(1) > 3000)) {
      switch (kb_Data[7]) {
        case kb_Right:
          cursorX += 8;
          break;
        case kb_Left:
          cursorX -= 8;
          break;
        case kb_Up:
          cursorY -= 8;
          break;
        case kb_Down:
          cursorY += 8;
          break;
        default:
          break;
      }
      if (!keyPressed) {
        while (timer_Get(1) < 9000 && kb_Data[7]) {
          kb_Scan();
        }
      }
      keyPressed = true;
      timer_Set(1, 0);
    }
  } while (!kb_IsDown(kb_KeyEnter) && !kb_IsDown(kb_KeyClear));
  gfx_BlitBuffer();
}
