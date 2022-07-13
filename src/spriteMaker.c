#include "font/font.h"

#include "spriteMaker.h"
#include "variables.h"
#include "engine.h"

#include <graphx.h>
#include <fontlibc.h>
#include <keypadc.h>

void spriteMaker(void) {
  gfx_BlitScreen();
  gfx_FillScreen(5);
  gfx_SetColor(21);
  gfx_FillRectangle_NoClip(0, 0, 320, 40);
  PrintCenteredText("Customize", 5, 183);
  gfx_PrintStringXY("Make a custom sprite", 90, 29);
  uint8_t cursorX = 128;
  uint8_t cursorY = 108;
  for (uint8_t spriteDrawer = 17; spriteDrawer < 81; spriteDrawer++) {
    if (tinyJumperData[spriteDrawer] == 79) {
      gfx_SetColor(34);
      gfx_FillRectangle_NoClip(cursorX, cursorY, 8, 8);
      gfx_SetColor(181);
      uint8_t transparentDrawerX = cursorX;
      for (uint8_t transparentDrawerY = cursorY; transparentDrawerY < cursorY + 8; transparentDrawerY += 2){
        do {
          gfx_FillRectangle_NoClip(transparentDrawerX, transparentDrawerY, 2, 2);
          transparentDrawerX += 4;
        } while (transparentDrawerX < cursorX + 6);
        transparentDrawerX -= 6;
      }
    } else {
      gfx_SetColor(tinyJumperData[spriteDrawer]);
      gfx_FillRectangle_NoClip(cursorX, cursorY, 8, 8);
    }
    cursorX += 8;
    if (cursorX > 191) {
        cursorX = 128;
        cursorY += 8;
    }
  }

  while (kb_AnyKey()) {
    kb_Scan();
  }
  do {
    kb_Scan();
  } while (!kb_AnyKey());

  gfx_BlitBuffer();
}
