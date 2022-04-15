#include "levels.h"
#include "variables.h"
#include "engine.h"

#include <tice.h>
#include <stdint.h>
#include <stdbool.h>

static void levelSetup(float playerXStart, float playerYStart) {
  playerX = playerXStart;
  playerY = playerYStart;
  gfx_FillScreen(5);
  gfx_SetColor(45);
  gfx_FillRectangle_NoClip(0, 235, 320, 5);
}

void level1(void) {
  levelSetup(5, 227);
  gfx_FillRectangle_NoClip(200, 218, 100, 5);
  gfx_FillRectangle_NoClip(150, 201, 50, 5);
  gfx_FillRectangle_NoClip(100, 184, 50, 5);
  gfx_FillRectangle_NoClip(45, 167, 55, 5);
  gfx_FillRectangle_NoClip(0, 167, 25, 5);
  gfx_FillRectangle_NoClip(0, 147, 10, 5);
  gfx_FillRectangle_NoClip(15, 127, 10, 5);
  gfx_FillRectangle_NoClip(0, 107, 10, 5);
  gfx_FillRectangle_NoClip(15, 87, 50, 5);
  gfx_FillRectangle_NoClip(95, 87, 95, 5);
  gfx_FillRectangle_NoClip(210, 72, 110, 5);
  gfx_SetColor(255);
  gfx_FillTriangle_NoClip(54, 227, 50, 235, 58, 235);
  gfx_FillTriangle_NoClip(114, 227, 110, 235, 118, 235);
  // these last ones are the bits of lava
  gfx_SetColor(43);
  gfx_FillRectangle_NoClip(25, 168, 20, 4);
  gfx_FillRectangle_NoClip(65, 88, 30, 4);
  gfx_BlitScreen(); // copies this base frame to the buffer
  gfx_SetDrawBuffer(); // everything will now get drawn to the buffer
  while (!dead && !quit && !goal) {
    player(); // move the player
    // the collisions for all the platforms
    rectPlatform(0, 235, 320, 5);
    rectPlatform(200, 218, 100, 5);
    rectPlatform(150, 201, 50, 5);
    rectPlatform(100, 184, 50, 5);
    rectPlatform(45, 167, 55, 5);
    rectPlatform(0, 167, 25, 5);
    rectPlatform(0, 147, 10, 5);
    rectPlatform(15, 127, 10, 5);
    rectPlatform(0, 107, 10, 5);
    rectPlatform(15, 87, 50, 5);
    rectPlatform(95, 87, 95, 5);
    rectPlatform(210, 72, 110, 5);
    spike(50, 230, 9, 8);
    spike(110, 230, 9, 8);
    spike(25, 168, 20, 4);
    spike(65, 88, 30, 4);
    endGoal(300, 56);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level2(void) {
  levelSetup(5, 224);
  gfx_FillRectangle_NoClip(0, 233, 100, 7);
  gfx_FillRectangle_NoClip(220, 229, 100, 11);
  gfx_FillRectangle_NoClip(0, 60, 80, 6);
  gfx_FillRectangle_NoClip(80, 62, 100, 4);
  gfx_FillRectangle_NoClip(180, 60, 80, 6);
  gfx_FillRectangle_NoClip(288, 210, 26, 5);
  gfx_FillRectangle_NoClip(255, 195, 26, 5);
  gfx_SetColor(255);
  gfx_FillTriangle_NoClip(100, 61, 102, 58, 104, 61);
  gfx_FillTriangle_NoClip(150, 61, 152, 58, 154, 61);
  gfx_SetColor(43);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 60, 80, 6);
    rectPlatform(80, 62, 100, 4);
    rectPlatform(180, 60, 80, 6);
    rectPlatform(288, 210, 26, 5);
    rectPlatform(255, 195, 26, 5);
    bouncePad(263, 193, 10, 10.5);
    rectPlatform(0, 233, 100, 7);
    rectPlatform(220, 229, 100, 11);
    spike(101, 58, 3, 3);
    spike(151, 58, 3, 3);
    endGoal(0, 44);
    drawPlayerAndTime(208, 67);
    playerQuicksand = false;
    quicksand(80, 61, 100, 2);
    quicksand(260, 61, 60, 60);
    quicksand(100, 234, 120, 6);
    quicksand(180, 230, 40, 4);
    endOfFrame();
  }
}

void level3(void) {
  levelSetup(300, 227);
  gfx_FillRectangle_NoClip(0, 0, 5, 240);
  gfx_FillRectangle_NoClip(50, 195, 45, 5);
  gfx_FillRectangle_NoClip(45, 50, 5, 150);
  gfx_FillRectangle_NoClip(50, 50, 180, 5);
  gfx_FillRectangle_NoClip(162, 110, 43, 5);
  gfx_SetColor(255);
  for (uint8_t spikeDrawer = 124; spikeDrawer < 150; spikeDrawer += 8) gfx_FillTriangle_NoClip(spikeDrawer, 50, spikeDrawer + 4, 42, spikeDrawer + 8, 50);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 0, 5, 240);
    rectPlatform(50, 195, 45, 5);
    rectPlatform(45, 50, 5, 150);
    rectPlatform(50, 50, 180, 5);
    rectPlatform(162, 110, 43, 5);
    rectPlatform(0, 235, 320, 5);
    spike(124, 42, 32, 8);
    antiGravity(235, 85, 85, 105);
    playerAntiGravity = anyAntiGravity;
    endGoal(67, 179);
    drawPlayerAndTime(284, 1);
    playerQuicksand = false;
    quicksand(5, 132, 6, 90);
    quicksand(39, 80, 6, 90);
    quicksand(5, 16, 6, 95);
    endOfFrame();
  }
}

void level4(void) {
  levelSetup(5, 72);
  gfx_FillRectangle_NoClip(0, 80, 40, 6);
  gfx_FillRectangle_NoClip(170, 134, 40, 6);
  gfx_FillRectangle_NoClip(0, 0, 320, 5);
  gfx_SetColor(255);
  for (int spikeDrawer = 0; spikeDrawer < 288; spikeDrawer += 8) gfx_FillTriangle_NoClip(spikeDrawer, 235, spikeDrawer + 4, 227, spikeDrawer + 8, 235);
  gfx_SetColor(43);
  gfx_FillRectangle_NoClip(290, 20, 4, 215);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 80, 40, 6);
    rectPlatform(170, 134, 40, 6);
    rectPlatform(0, 0, 320, 5);
    spike(290, 20, 3.5, 215);
    spike(311, 76, 9, 9);
    bouncePad(22, 78, 16, 10);
    bouncePad(182, 132, 16, 12.5);
    spike(0, 227, 290, 8);
    endGoal(304, 219);
    drawPlayerAndTime(170, 217);
    playerQuicksand = false;
    quicksand(0, 5, 50, 12);
    quicksand(50, 5, 120, 6);
    quicksand(210, 5, 110, 6);
    quicksand(303, 5, 17, 150);
    gfx_SetColor(255);
    gfx_FillTriangle_NoClip(319, 76, 311, 80, 319, 84);
    endOfFrame();
  }
}

void level5(void) {
  levelSetup(32, 110);
  int spikeXPos[6] = {74, 171, 94, 294, 275, 286};
  const uint8_t spikeYPos[6] = {117, 176, 176, 176, 117, 58};
  const int spikeXMin[6] = {74, 82, 86, 258, 265, 262};
  const int spikeXMax[6] = {134, 177, 174, 304, 297, 300};
  int8_t spikeXSpeed[6] = {1, 2, 2, 1, -1, 1};
  gfx_FillRectangle_NoClip(0, 118, 197, 6);
  gfx_FillRectangle_NoClip(0, 59, 256, 6);
  gfx_FillRectangle_NoClip(58, 177, 198, 6);
  gfx_FillRectangle_NoClip(0, 0, 6, 240);
  gfx_FillRectangle_NoClip(314, 0, 6, 240);
  gfx_FillRectangle_NoClip(0, 0, 320, 6);
  gfx_SetColor(255);
  gfx_FillTriangle_NoClip(64, 59, 69, 49, 74, 59);
  gfx_SetColor(43);
  gfx_FillRectangle_NoClip(250, 65, 6, 112);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 118, 197, 6);
    rectPlatform(0, 59, 256, 6);
    rectPlatform(58, 177, 198, 6);
    spike(250, 65, 6, 112);
    rectPlatform(0, 0, 6, 240);
    rectPlatform(314, 0, 6, 240);
    rectPlatform(0, 0, 320, 6);
    antiGravity(256, 6, 58, 200);
    spike(63, 49, 11, 11);
    playerAntiGravity = anyAntiGravity;
    for (int8_t spikeNumber = 0; spikeNumber < 6; spikeNumber++) {
      gfx_SetColor(5 + 142 * (spikeNumber > 2));
      gfx_FillRectangle_NoClip(spikeXPos[spikeNumber], spikeYPos[spikeNumber] - 8, 9, 9);
      spike(spikeXPos[spikeNumber], spikeYPos[spikeNumber] - 8, 9, 8);
      spikeXPos[spikeNumber] += spikeXSpeed[spikeNumber];
      if (spikeXPos[spikeNumber] < spikeXMin[spikeNumber] || spikeXPos[spikeNumber] > spikeXMax[spikeNumber]) spikeXSpeed[spikeNumber] *= -1;
      gfx_SetColor(255);
      gfx_FillTriangle_NoClip(spikeXPos[spikeNumber], spikeYPos[spikeNumber], spikeXPos[spikeNumber] + 4, spikeYPos[spikeNumber] - 8, spikeXPos[spikeNumber] + 8, spikeYPos[spikeNumber]);
    }
    endGoal(41, 43);
    drawPlayerAndTime(7, 14);
    endOfFrame();
  }
}

void level6(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level7(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level8(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level9(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level10(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level11(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level12(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level13(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level14(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void level15(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}

void bonusLevel2(void) {
  levelSetup(5, 227);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    drawPlayerAndTime(1, 1);
    endOfFrame();
  }
}
