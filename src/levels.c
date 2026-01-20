#include "levels.h"
#include "variables.h"
#include "engine.h"

#include <tice.h>
#include <stdint.h>
#include <stdbool.h>

static void levelSetup(float playerXStart, float playerYStart) {
  playerX = playerXStart;
  playerY = playerYStart;
  touched = false;
  playerQuicksand = false;
  playerAntiGravity = false;
  gfx_FillScreen(COLOR_DARK_PURPLE);
  gfx_SetColor(COLOR_GRAY);
  gfx_FillRectangle_NoClip(0, 235, 320, 5);
}

void level1(void) {
  levelSetup(5, 227);
  gfx_FillRectangle_NoClip(0, 0, 5, 240);
  gfx_FillRectangle_NoClip(315, 0, 5, 240);
  gfx_FillRectangle_NoClip(100, 215, 40, 5);
  gfx_FillRectangle_NoClip(170, 197, 25, 5);
  gfx_FillRectangle_NoClip(210, 179, 90, 5);
  gfx_FillRectangle_NoClip(307, 155, 9, 5);
  gfx_FillRectangle_NoClip(183, 132, 94, 5);
  gfx_FillRectangle_NoClip(48, 132, 96, 5);
  gfx_FillRectangle_NoClip(5, 112, 8, 5);
  gfx_FillRectangle_NoClip(34, 90, 252, 5);
  gfx_SetColor(COLOR_WHITE);
  gfx_FillTriangle_NoClip(252, 179, 256, 171, 260, 179);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(144, 133, 39, 4);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 0, 5, 240);
    rectPlatform(315, 0, 5, 240);
    rectPlatform(100, 215, 40, 5);
    rectPlatform(170, 197, 25, 5);
    rectPlatform(210, 179, 90, 5);
    spike(252, 171, 9, 8);
    rectPlatform(307, 155, 9, 5);
    spike(144, 133, 39, 4);
    rectPlatform(183, 132, 94, 5);
    rectPlatform(48, 132, 96, 5);
    rectPlatform(5, 112, 8, 5);
    rectPlatform(34, 90, 252, 5);
    endGoal(152, 74);
    drawPlayerAndTime(245, 80);
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
  gfx_SetColor(COLOR_WHITE);
  gfx_FillTriangle_NoClip(100, 61, 102, 58, 104, 61);
  gfx_FillTriangle_NoClip(150, 61, 152, 58, 154, 61);
  gfx_SetColor(COLOR_RED);
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
  levelSetup(5, 227);
  gfx_FillRectangle_NoClip(88, 216, 60, 5);
  gfx_FillRectangle_NoClip(166, 193, 35, 5);
  gfx_FillRectangle_NoClip(220, 135, 5, 73);
  gfx_FillRectangle_NoClip(150, 135, 30, 5);
  gfx_FillRectangle_NoClip(0, 0, 320, 5);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(60, 235, 135, 5);
  gfx_FillRectangle_NoClip(60, 0, 67, 5);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 60, 5);
    rectPlatform(195, 235, 125, 5);
    rectPlatform(88, 216, 60, 5);
    rectPlatform(166, 193, 35, 5);
    rectPlatform(220, 135, 5, 73);
    rectPlatform(150, 135, 30, 5);
    rectPlatform(0, 0, 60, 5);
    rectPlatform(127, 0, 193, 5);
    spike(60, 235, 135, 5);
    spike(60, 0, 67, 5);
    bouncePad(262, 233, 12, 10.5);
    antiGravity(0, 5, 210, 105);
    gfx_SetColor(COLOR_GRAY);
    gfx_FillRectangle_NoClip(162, 30, 6, 60);
    rectPlatform(162, 30, 6, 60);
    gfx_FillRectangle_NoClip(97, 25, 12, 6);
    rectPlatform(97, 25, 12, 6);
    playerAntiGravity = anyAntiGravity;
    endGoal(2, 5);
    drawPlayerAndTime(68, 132);
    endOfFrame();
  }
}

void level4(void) {
  levelSetup(300, 227);
  gfx_FillRectangle_NoClip(0, 0, 5, 240);
  gfx_FillRectangle_NoClip(50, 195, 45, 5);
  gfx_FillRectangle_NoClip(45, 50, 5, 150);
  gfx_FillRectangle_NoClip(50, 50, 180, 5);
  gfx_FillRectangle_NoClip(162, 110, 43, 5);
  gfx_SetColor(COLOR_WHITE);
  for (uint8_t spikeDrawer = 124; spikeDrawer < 150; spikeDrawer += 8) {
    gfx_FillTriangle_NoClip(spikeDrawer, 50, spikeDrawer + 4, 42, spikeDrawer + 8, 50);
  }
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

void level5(void) {
  levelSetup(8, 52);
  gfx_FillRectangle_NoClip(0, 60, 102, 6);
  gfx_FillRectangle_NoClip(196, 60, 98, 6);
  gfx_FillRectangle_NoClip(288, 66, 6, 124);
  gfx_FillRectangle_NoClip(58, 184, 230, 6);
  gfx_FillRectangle_NoClip(58, 106, 6, 78);
  gfx_FillRectangle_NoClip(13, 209, 29, 6);
  gfx_FillRectangle_NoClip(64, 106, 30, 6);
  gfx_FillRectangle_NoClip(124, 130, 30, 6);
  gfx_FillRectangle_NoClip(184, 154, 30, 6);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(102, 60, 94, 6);
  gfx_FillRectangle_NoClip(94, 112, 30, 24);
  gfx_FillRectangle_NoClip(154, 136, 30, 24);
  gfx_FillRectangle_NoClip(214, 160, 30, 24);
  gfx_SetColor(COLOR_WHITE);
  gfx_FillTriangle_NoClip(103, 235, 108, 225, 113, 235);
  gfx_FillTriangle_NoClip(163, 235, 168, 225, 173, 235);
  gfx_FillTriangle_NoClip(223, 235, 228, 225, 233, 235);
  struct portal_t portal1 = {
    .x = 108,
    .y = 32,
    .color = COLOR_BLUE,
    .direction = PORTAL_LEFT,
  };
  struct portal_t portal2 = {
    .x = 190,
    .y = 32,
    .color = COLOR_BLUE,
    .direction = PORTAL_LEFT,
  };
  portal1.exit = &portal2;
  portal2.exit = &portal1;
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 60, 102, 6);
    rectPlatform(196, 60, 98, 6);
    rectPlatform(288, 66, 6, 124);
    rectPlatform(58, 184, 230, 6);
    rectPlatform(58, 106, 6, 78);
    rectPlatform(13, 209, 29, 6);
    rectPlatform(64, 106, 30, 6);
    rectPlatform(124, 130, 30, 6);
    rectPlatform(184, 154, 30, 6);
    spike(102, 60, 94, 6);
    spike(94, 112, 30, 24);
    spike(154, 136, 30, 24);
    spike(214, 160, 30, 24);
    spike(103, 225, 11, 11);
    spike(163, 225, 11, 11);
    spike(223, 225, 11, 11);
    portal(&portal1);
    portal(&portal2);
    endGoal(269, 168);
    drawPlayerAndTime(14, 70);
    playerQuicksand = false;
    quicksand(0, 106, 58, 84);
    endOfFrame();
  }
}

void level6(void) {
  levelSetup(5, 72);
  gfx_FillRectangle_NoClip(0, 80, 40, 6);
  gfx_FillRectangle_NoClip(170, 134, 40, 6);
  gfx_FillRectangle_NoClip(0, 0, 320, 5);
  gfx_SetColor(COLOR_WHITE);
  for (int spikeDrawer = 0; spikeDrawer < 288; spikeDrawer += 8) {
    gfx_FillTriangle_NoClip(spikeDrawer, 235, spikeDrawer + 4, 227, spikeDrawer + 8, 235);
  }
  gfx_SetColor(COLOR_RED);
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
    drawPlayerAndTime(172, 6);
    playerQuicksand = false;
    quicksand(0, 5, 50, 12);
    quicksand(50, 5, 120, 6);
    quicksand(210, 5, 110, 6);
    quicksand(303, 5, 17, 150);
    gfx_SetColor(COLOR_WHITE);
    gfx_FillTriangle_NoClip(319, 76, 311, 80, 319, 84);
    endOfFrame();
  }
}

void level7(void) {
  levelSetup(5, 127);
  gfx_FillRectangle_NoClip(0, 135, 80, 5);
  gfx_FillRectangle_NoClip(250, 115, 70, 5);
  gfx_FillRectangle_NoClip(0, 95, 60, 5);
  gfx_FillRectangle_NoClip(260, 75, 60, 5);
  gfx_FillRectangle_NoClip(0, 55, 40, 5);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(215, 120, 8, 20);
  gfx_FillRectangle_NoClip(151, 75, 8, 20);
  gfx_FillRectangle_NoClip(87, 30, 8, 20);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 135, 80, 5);
    rectPlatform(250, 115, 70, 5);
    rectPlatform(0, 95, 60, 5);
    rectPlatform(260, 75, 60, 5);
    rectPlatform(0, 55, 40, 5);
    rectPlatform(0, 235, 320, 5);
    spike(217, 120, 8, 20);
    spike(151, 75, 8, 20);
    spike(85, 30, 8, 20);
    antiGravity(0, 140, 320, 95);
    playerAntiGravity = anyAntiGravity;
    endGoal(8, 39);
    drawPlayerAndTime(151, 65);
    endOfFrame();
  }
}

void level8(void) {
  levelSetup(312, 227);
  gfx_FillRectangle_NoClip(0, 235, 320, 5);
  gfx_FillRectangle_NoClip(0, 0, 6, 235);
  gfx_FillRectangle_NoClip(6, 0, 74, 6);
  gfx_FillRectangle_NoClip(80, 0, 6, 188);
  gfx_FillRectangle_NoClip(86, 182, 234, 6);
  gfx_FillRectangle_NoClip(86, 53, 191, 6);
  gfx_FillRectangle_NoClip(249, 59, 6, 80);
  gfx_FillRectangle_NoClip(314, 0, 6, 53);
  gfx_FillRectangle_NoClip(6, 211, 17, 6);
  gfx_FillRectangle_NoClip(48, 176, 32, 6);
  gfx_FillRectangle_NoClip(255, 133, 22, 6);
  gfx_FillRectangle_NoClip(292, 113, 22, 6);
  gfx_FillRectangle_NoClip(255, 93, 22, 6);
  gfx_FillRectangle_NoClip(292, 73, 22, 6);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(314, 53, 6, 129);
  gfx_SetColor(COLOR_WHITE);
  gfx_FillTriangle_NoClip(137, 235, 142, 225, 147, 235);
  gfx_FillTriangle_NoClip(86, 235, 91, 225, 96, 235);
  gfx_FillTriangle_NoClip(65, 175, 69, 167, 73, 175);
  gfx_FillTriangle_NoClip(134, 53, 139, 43, 144, 53);
  for (uint8_t x = 126; x < 214; x += 11) {
    gfx_FillTriangle_NoClip(x, 182, x + 5, 172, x + 10, 182);
  }
  struct portal_t portal1 = {
    .x = 42,
    .y = 16,
    .color = COLOR_BLUE,
    .direction = PORTAL_UP,
  };
    struct portal_t portal2 = {
    .x = 150,
    .y = 87,
    .color = COLOR_BLUE,
    .direction = PORTAL_RIGHT,
  };
  portal1.exit = &portal2;
  portal2.exit = &portal1;
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 0, 6, 235);
    rectPlatform(6, 0, 74, 6);
    rectPlatform(80, 0, 6, 188);
    rectPlatform(86, 182, 234, 6);
    rectPlatform(86, 53, 191, 6);
    rectPlatform(249, 59, 6, 80);
    rectPlatform(314, 0, 6, 53);
    rectPlatform(6, 211, 17, 6);
    rectPlatform(48, 176, 32, 6);
    rectPlatform(255, 133, 22, 6);
    rectPlatform(292, 113, 22, 6);
    rectPlatform(255, 93, 22, 6);
    rectPlatform(292, 73, 22, 6);
    antiGravity(6, 6, 74, 126);
    spike(314, 53, 6, 129);
    spike(137, 225, 11, 11);
    spike(86, 225, 11, 11);
    spike(65, 167, 9, 9);
    spike(126, 172, 88, 11);
    spike(134, 43, 11, 11);
    bouncePad(12, 209, 9, 8);
    bouncePad(50, 174, 9, 7);
    bouncePad(296, 180, 14, 8.5);
    portal(&portal1);
    portal(&portal2);
    endGoal(111, 37);
    playerAntiGravity = anyAntiGravity;
    drawPlayerAndTime(87, 23);
    endOfFrame();
  }
}

void level9(void) {
  levelSetup(28, 152);
  float screenMovement = 0;
  float platformY[] = {160, 140, 120, 100, 75, 30, -40, -120, -175, -200, -225, -245};
  int platformX[] = {20, 65, 90, 145, 180, 130, 200, 140, 105, 155, 195, 0};
  float lavaY = 230;
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    screenMovement = (0.3 + ((240 - playerY) / 200)) * (timer > 45 && platformY[11] < 60);
      playerY += screenMovement;
    for (uint8_t platformDrawer = 0; platformDrawer < 12; platformDrawer++) {
      platformY[platformDrawer] += screenMovement;
      if (platformY[platformDrawer] > -1 && platformY[platformDrawer] < 210) {
        gfx_SetColor(COLOR_DARK_PURPLE);
        gfx_FillRectangle_NoClip(platformX[platformDrawer], platformY[platformDrawer] - 2 - screenMovement, 25 + 125 * (platformDrawer == 11), 6);
        rectPlatform(platformX[platformDrawer], platformY[platformDrawer], 25 + 125 * (platformDrawer == 11), 5);
        gfx_SetColor(COLOR_GRAY);
        gfx_FillRectangle_NoClip(platformX[platformDrawer], platformY[platformDrawer], 25 + 125 * (platformDrawer == 11), 5);
      }
    }
    for (uint8_t bouncePadDrawer = 0; bouncePadDrawer < 3; bouncePadDrawer++) {
      if (platformY[bouncePadDrawer + 4] > 2 && platformY[bouncePadDrawer + 4] < 235) {
        bouncePad(platformX[bouncePadDrawer + 4] + 6, platformY[bouncePadDrawer + 4] - 2, 13, 8 + bouncePadDrawer);
      }
    }
    if (platformY[8] > -40 && platformY[8] < 210) {
      gfx_SetColor(COLOR_DARK_PURPLE);
      gfx_FillRectangle_NoClip(70, platformY[8] + 5 - screenMovement, 35, 5);
      antiGravity(70, platformY[8] + 5, 60, 35);
    }
    if (platformY[11] > 10) {
      gfx_SetColor(COLOR_DARK_PURPLE);
      gfx_FillRectangle_NoClip(25, platformY[11] - 16 - screenMovement, 16, 5);
      endGoal(25, platformY[11] - 16);
    }
    if (timer < 45) {
      lavaY -= 0.35;
    } else if (platformY[11] >= 60) {
      lavaY -= 0.55;
    } else {
      lavaY -= 0.1;
    }
    gfx_SetColor(COLOR_RED);
    gfx_FillRectangle_NoClip(0, lavaY, 320, 241 - lavaY);
    spike(0, lavaY, 320, 240 - lavaY);
    playerAntiGravity = anyAntiGravity;
    drawPlayerAndTime(260, 1);
    endOfFrame();
  }
}

void level10(void) {
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
  gfx_SetColor(COLOR_WHITE);
  gfx_FillTriangle_NoClip(64, 59, 69, 49, 74, 59);
  gfx_SetColor(COLOR_RED);
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
      gfx_SetColor((spikeNumber > 2) ? COLOR_LIGHT_PURPLE : COLOR_DARK_PURPLE);
      gfx_FillRectangle_NoClip(spikeXPos[spikeNumber], spikeYPos[spikeNumber] - 8, 9, 9);
      spike(spikeXPos[spikeNumber], spikeYPos[spikeNumber] - 8, 9, 8);
      spikeXPos[spikeNumber] += spikeXSpeed[spikeNumber];
      if (spikeXPos[spikeNumber] < spikeXMin[spikeNumber] || spikeXPos[spikeNumber] > spikeXMax[spikeNumber]) {
        spikeXSpeed[spikeNumber] *= -1;
      }
      gfx_SetColor(COLOR_WHITE);
      gfx_FillTriangle_NoClip(spikeXPos[spikeNumber], spikeYPos[spikeNumber], spikeXPos[spikeNumber] + 4, spikeYPos[spikeNumber] - 8, spikeXPos[spikeNumber] + 8, spikeYPos[spikeNumber]);
    }
    endGoal(41, 43);
    drawPlayerAndTime(7, 14);
    endOfFrame();
  }
}

void level11(void) {
  bool button = false;
  bool direction = true;
  levelSetup(305, 52);
  gfx_FillRectangle_NoClip(60, 60, 6, 175);
  gfx_FillRectangle_NoClip(66, 60, 254, 6);
  gfx_FillRectangle_NoClip(66, 152, 254, 6);
  gfx_FillRectangle_NoClip(160, 210, 6, 25);
  gfx_FillRectangle_NoClip(0, 0, 320, 5);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(66, 225, 94, 15);
  gfx_SetColor(COLOR_WHITE);
  for (unsigned int x = 72; x < 163; x += 15) {
    gfx_FillTriangle_NoClip(x, 152, x + 5, 142, x + 10, 152);
  }
  drawButton(234, 231);
  struct portal_t portal1 = {
    .x = 28,
    .y = 227,
    .color = COLOR_BLUE,
    .direction = PORTAL_DOWN,
  };
  struct portal_t portal2 = {
    .x = 90,
    .y = 180,
    .color = COLOR_BLUE,
    .direction = PORTAL_RIGHT,
  };
  portal1.exit = &portal2;
  portal2.exit = &portal1;
    struct portal_t portal3 = {
    .x = 311,
    .y = 207,
    .color = COLOR_GOAL_1,
    .direction = PORTAL_LEFT,
  };
  struct portal_t portal4 = {
    .x = 88,
    .y = 91,
    .color = COLOR_GOAL_1,
    .direction = PORTAL_UP,
  };
  portal3.exit = &portal4;
  portal4.exit = &portal3;
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(60, 60, 6, 175);
    rectPlatform(66, 60, 254, 6);
    rectPlatform(66, 152, 254, 6);
    rectPlatform(160, 210, 6, 25);
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 0, 320, 5);
    if (!button) {
      if (gfx_CheckRectangleHotspot(234, 231, 15, 4, playerX, playerY, 8, 8)) {
        button = true;
        gfx_SetColor(COLOR_DARK_PURPLE);
        gfx_FillRectangle_NoClip(234, 231, 15, 4);
      }
    } else {
      gfx_SetColor(COLOR_DARK_PURPLE);
      gfx_FillRectangle_NoClip(69, 87, 136, 9);
      if (direction) {
        if (portal4.x < 185) {
          portal4.x += 2;
        } else {
          portal4.x -= 2;
          direction = false;
        }
      } else {
        if (portal4.x > 88) {
          portal4.x -= 2;
        } else {
          portal4.x += 2;
          direction = true;
        }
      }
    }
    spike(66, 225, 94, 15);
    spike(72, 142, 101, 11);
    spike(83, 4, 11, 11);
    spike(133, 4, 11, 11);
    spike(183, 4, 11, 11);
    portal(&portal1);
    portal(&portal2);
    portal(&portal3);
    portal(&portal4);
    antiGravity(60, 5, 200, 55);
    antiGravity(0, 5, 60, 25);
    playerAntiGravity = anyAntiGravity;
    gfx_SetColor(COLOR_WHITE);
    gfx_FillTriangle_NoClip(83, 4, 88, 14, 93, 4);
    gfx_FillTriangle_NoClip(133, 4, 138, 14, 143, 4);
    gfx_FillTriangle_NoClip(183, 4, 188, 14, 193, 4);
    endGoal(282, 136);
    drawPlayerAndTime(147, 116);
    endOfFrame();
  }
}

void level12(void) {
  levelSetup(156, 42);
  playerX = 156;
  playerY = 42;
  touched = false;
  float scroll = 0;
  unsigned int time = 0;
  gfx_FillScreen(COLOR_DARK_PURPLE);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    gfx_FillScreen(COLOR_DARK_PURPLE);
    gfx_SetColor(COLOR_GRAY);
    gfx_FillRectangle_NoClip(0, 0, 6, 240);
    gfx_FillRectangle_NoClip(314, 0, 6, 240);
    rectPlatform(0, 0, 6, 240);
    rectPlatform(314, 0, 6, 240);
    if (scroll < 56) {
      for (unsigned int x = 25; x < 266; x += 60) {
        gfx_FillRectangle(x, 50 - scroll, 30, 6);
        rectPlatform(x, 50 - scroll, 30, 6);
      }
    }
    if (scroll > 394) {
      gfx_FillRectangle(0, 635 - scroll, 320, 5);
      rectPlatform(0, 635 - scroll, 320, 5);
    }
    if (scroll > 166) {
      gfx_FillRectangle(123, 406 - scroll, 92, 6);
      rectPlatform(123, 406 - scroll, 92, 6);
    }
    if (scroll < 197) {
      antiGravity(6, 92 - scroll, 85, 105);
    }
    if (scroll > 183) {
      antiGravity(96, 423 - scroll, 78, 60);
    }
    gfx_SetColor(COLOR_RED);
    if (scroll < 336) {
      gfx_FillRectangle(77, 232 - scroll, 78, 104);
      spike(77, 232 - scroll, 78, 104);
    }
    if (scroll > 157) {
      gfx_FillRectangle(11, 420 - scroll, 52, 52);
      spike(11, 420 - scroll, 52, 52);
    }
    if (scroll > 254) {
      gfx_FillRectangle(138, 494 - scroll, 92, 14);
      spike(138, 494 - scroll, 92, 14);
    }
    if (scroll > 379) {
      endGoal(198, 619 - scroll);
    }
    gfx_SetColor(COLOR_WHITE);
    if (scroll > 158) {
      for (unsigned int x = 124; x < 206; x += 9) {
        gfx_FillTriangle(x, 406 - scroll, x + 4, 398 - scroll, x + 8, 406 - scroll);
      }
      spike(124, 398 - scroll, 90 , 9);
    }
    if (scroll > 385) {
      gfx_FillTriangle(48, 635 - scroll, 53, 625 - scroll, 58, 635 - scroll);
      spike(48, 625 - scroll, 11, 11);
      gfx_FillTriangle(96, 635 - scroll, 101, 625 - scroll, 106, 635 - scroll);
      spike(96, 625 - scroll, 11, 11);
      gfx_FillTriangle(144, 635 - scroll, 149, 625 - scroll, 154, 635 - scroll);
      spike(144, 625 - scroll, 11, 11);
      gfx_FillTriangle(220, 635 - scroll, 225, 625 - scroll, 230, 635 - scroll);
      spike(220, 625 - scroll, 11, 11);
      gfx_FillTriangle(282, 635 - scroll, 287, 625 - scroll, 292, 635 - scroll);
      spike(282, 625 - scroll, 11, 11);
      gfx_FillTriangle(299, 635 - scroll, 304, 625 - scroll, 309, 635 - scroll);
      spike(299, 625 - scroll, 11, 11);
    }
    if (scroll < 12) {
      gfx_SetColor(COLOR_GOAL_1);
      gfx_FillEllipse(267, 7 - scroll, 19, 4);
      if (timer - time > 7 && gfx_CheckRectangleHotspot(267 - 18, 7 - scroll - 5, 36, 10, playerX, playerY, 8, 8)) {
        playerY = 116;
        scroll = 262;
        playerX = 41 + (playerX - 267);
        time = timer;
      }
    }
    if (scroll < 222) {
      gfx_SetColor(COLOR_BLUE);
      gfx_FillEllipse(41, 217 - scroll, 19, 4);
      if (timer - time > 7 && gfx_CheckRectangleHotspot(41 - 18, 217 - scroll - 5, 36, 10, playerX, playerY, 8, 8)) {
        scroll = 266;
        playerY = 116;
        playerX = 156 + (playerX - 41);
        time = timer;
      }
    }
    if (scroll > 138 && scroll < 387) {
      gfx_SetColor(COLOR_GOAL_1);
      gfx_FillEllipse(41, 382 - scroll, 19, 4);
      if (timer - time > 7 && gfx_CheckRectangleHotspot(41 - 18, 382 - scroll - 5, 36, 10, playerX, playerY, 8, 8)) {
        scroll = 0;
        playerY = 8;
        playerX = 267 + (playerX - 41);
        time = timer;
      }
    }
    if (scroll > 142 && scroll < 391) {
      gfx_SetColor(COLOR_BLUE);
      gfx_FillEllipse(156, 386 - scroll, 19, 4);
      if (timer - time > 7 && gfx_CheckRectangleHotspot(156 - 18, 386 - scroll - 5, 36, 10, playerX, playerY, 8, 8)) {
        scroll = 97;
        playerY = 116;
        playerX = 41 + (playerX - 156);
        time = timer;
      }
    }
    playerAntiGravity = anyAntiGravity;
    drawPlayerAndTime(1, 1);
    playerQuicksand = false;
    if (scroll < 249) {
      quicksand(194, 107 - scroll, 120, 142);
    }
    if (scroll > 77) {
      quicksand(241, 317 - scroll, 35, 228);
    }
    if (scroll > 255) {
      quicksand(43, 495 - scroll, 40, 40);
    }
    if ((playerY >= 116 || scroll > 0) && scroll < 400) {
      if ((scroll + playerY - 116) - 400 > 0) {
        scroll = 400;
        playerY += (scroll + playerY - 116) - 400;
      } else if ((scroll + playerY - 116) < 0) {
        scroll = 0;
        playerY += (scroll + playerY - 116);
      } else {
        scroll += playerY - 116;
        playerY = 116;
      }
    }
    endOfFrame();
  }
}

void level13(void) {
  bool button = false;
  unsigned int spikeX[6] = {14, 49, 82, 227, 260, 295};
  int8_t spikeXSpeed[6] = {1, 2, -1, 2, 1, -2};
  levelSetup(0, 109);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(0, 216, 320, 24);
  drawButton(295, 134);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    if (button) {
      antiGravity(0, 0, 320, 240);
    }
    playerAntiGravity = anyAntiGravity;
    gfx_SetColor(COLOR_GRAY);
    gfx_FillRectangle_NoClip(0, 0, 320, 5);
    gfx_FillRectangle_NoClip(0, 5, 130, 25);
    gfx_FillRectangle_NoClip(190, 5, 130, 25);
    gfx_FillRectangle_NoClip(0, 117, 35, 6);
    gfx_FillRectangle_NoClip(70, 117, 35, 6);
    gfx_FillRectangle_NoClip(140, 117, 40, 6);
    gfx_FillRectangle_NoClip(215, 117, 35, 6);
    gfx_FillRectangle_NoClip(215, 117, 35, 6);
    gfx_FillRectangle_NoClip(285, 96, 35, 6);
    gfx_FillRectangle_NoClip(285, 138, 35, 6);
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 0, 320, 5);
    rectPlatform(0, 5, 130, 25);
    rectPlatform(190, 5, 130, 25);
    rectPlatform(0, 117, 35, 6);
    rectPlatform(70, 117, 35, 6);
    rectPlatform(140, 117, 40, 6);
    rectPlatform(215, 117, 35, 6);
    rectPlatform(215, 117, 35, 6);
    rectPlatform(285, 96, 35, 6);
    rectPlatform(285, 138, 35, 6);
    spike(0, 216, 320, 24);
    gfx_SetColor(COLOR_WHITE);
    for (uint8_t i = 0; i < 6; i++) {
      gfx_FillTriangle_NoClip(spikeX[i], 29, spikeX[i] + 5, 39, spikeX[i] + 10, 29);
      spike(spikeX[i], 29, 11, 11);
      if (button) {
        spikeX[i] += spikeXSpeed[i];
        if (!(spikeX[i] >= 3 && spikeX[i] <= 308)) {
          spikeXSpeed[i] = -spikeXSpeed[i];
        }
      }
    }
    if (!button) {
      gfx_FillTriangle_NoClip(82, 117, 87, 107, 92, 117);
      gfx_FillTriangle_NoClip(227, 117, 232, 107, 237, 117);
      spike(82, 107, 11, 11);
      spike(227, 107, 11, 11);
    } else {
      gfx_FillTriangle_NoClip(82, 123, 87, 133, 92, 123);
      gfx_FillTriangle_NoClip(227, 123, 232, 133, 237, 123);
      spike(82, 123, 11, 11);
      spike(227, 123, 11, 11);
    }
    drawPlayerAndTime(141, 131);
    playerQuicksand = false;
    if (!button) {
      quicksand(35, 117, 35, 6);
      quicksand(105, 117, 35, 6);
      quicksand(180, 117, 35, 6);
      quicksand(250, 117, 23, 6);
      if (gfx_CheckRectangleHotspot(295, 134, 15, 4, playerX, playerY, 8, 8)) {
        button = true;
        gfx_SetColor(COLOR_DARK_PURPLE);
        gfx_FillRectangle_NoClip(295, 134, 15, 4);
      }
    }
    endGoal(152, 5);
    endOfFrame();
  }
}

void level14(void) {
  bool button = false;
  unsigned int lavaWidth = 6;
  uint8_t platformY[4] = {168, 117, 110, 132};
  int8_t platformYSpeed[4] = {-1, 1, -1, -2};
  levelSetup(35, 41);
  gfx_FillRectangle_NoClip(0, 0, 320, 5);
  gfx_FillRectangle_NoClip(0, 5, 6, 44);
  gfx_FillRectangle_NoClip(20, 49, 24, 6);
  gfx_FillRectangle_NoClip(44, 5, 6, 186);
  gfx_FillRectangle_NoClip(70, 140, 18, 6);
  gfx_FillRectangle_NoClip(88, 140, 6, 95);
  gfx_FillRectangle_NoClip(88, 5, 6, 95);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(94, 224, 226, 16);
  drawButton(40, 231);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 0, 320, 5);
    rectPlatform(0, 5, 6, 44);
    rectPlatform(20, 49, 24, 6);
    rectPlatform(44, 5, 6, 186);
    rectPlatform(70, 140, 18, 6);
    rectPlatform(88, 140, 6, 95);
    rectPlatform(88, 5, 6, 95);
    spike(94, 224, 226, 16);
    antiGravity(94, 5, 226, 44);
    playerAntiGravity = anyAntiGravity;
    gfx_SetColor(COLOR_WHITE);
    gfx_FillTriangle_NoClip(44, 113, 34, 118, 44, 123);
    spike(34, 113, 11, 11);
    gfx_FillTriangle_NoClip(44, 178, 34, 183, 44, 188);
    spike(34, 178, 11, 11);
    for (unsigned int x = 97; x < 308; x += 15) {
      gfx_FillTriangle_NoClip(x, 4, x + 5, 14, x + 10, 4);
      spike(x, 4, 11, 11);
    }
    bouncePad(74, 233, 10, 10.5);
    if (!button) {
      if (gfx_CheckRectangleHotspot(40, 231, 15, 4, playerX, playerY, 8, 8)) {
        button = true;
        gfx_SetColor(COLOR_DARK_PURPLE);
        gfx_FillRectangle_NoClip(40, 231, 15, 4);
      }
    } else {
      gfx_SetColor(COLOR_DARK_PURPLE);
      gfx_FillRectangle_NoClip(114, 49, 167, 175);
      lavaWidth++;
      for (uint8_t i = 0; i < 4; i++) {
        if (playerX >= 114 + i * 46 && playerX <= 114 + i * 46 + 26 && playerGrounded == 2) {
          playerY += platformYSpeed[i];
        }
        platformY[i] += platformYSpeed[i];
        if (platformY[i] < 50 || platformY[i] > 217) {
          platformYSpeed[i] = -platformYSpeed[i];
        }
      }
    }
    for (uint8_t i = 0; i < 4; i++) {
      gfx_SetColor(COLOR_GRAY);
      gfx_FillRectangle_NoClip(114 + i * 46, platformY[i], 26, 6);
      rectPlatform(114 + i * 46, platformY[i], 26, 6);
    }
    drawPlayerAndTime(282, 88);
    playerQuicksand = false;
    quicksand(282, 49, 38, 38);
    endGoal(304, 49);
    gfx_SetColor(COLOR_RED);
    gfx_FillRectangle_NoClip(0, 49, lavaWidth, 186);
    spike(0, 49, lavaWidth, 186);
    endOfFrame();
  }
}

void level15(void) {
  int8_t button = 0;
  levelSetup(5, 31);
  gfx_FillRectangle_NoClip(0, 40, 45, 6);
  for (uint8_t platformDrawer = 0; platformDrawer < 180; platformDrawer += 48) {
    gfx_FillRectangle_NoClip(platformDrawer + 80, platformDrawer / 2 + 40, 9, 80);
  }
  gfx_FillRectangle_NoClip(265, 45, 55, 5);
  gfx_SetColor(COLOR_RED);
  gfx_FillRectangle_NoClip(265, 50, 5, 142);
  gfx_FillRectangle_NoClip(157, 59, 3, 50);
  gfx_FillRectangle_NoClip(0, 235, 187, 5);
  drawButton(295, 231);
  gfx_BlitScreen();
  gfx_SetDrawBuffer();
  while (!dead && !quit && !goal) {
    player();
    spike(265, 50, 6, 142);
    spike(157, 59, 3, 50);
    spike(0, 234, 187, 6);
    rectPlatform(0, 235, 320, 5);
    rectPlatform(0, 40, 45, 5);
    rectPlatform(270, 45, 90, 5);
    for (uint8_t platformDrawer = 0; platformDrawer < 180; platformDrawer += 48) {
      rectPlatform(platformDrawer + 80, platformDrawer / 2 + 40, 9, 80);
    }
    switch (button) {
      case 0: // when the first button has yet to be pressed
        if (gfx_CheckRectangleHotspot(playerX, playerY, 8, 8, 295, 231, 15, 5)) {
          button = 1;
          gfx_SetColor(COLOR_DARK_PURPLE);
          gfx_FillRectangle_NoClip(295, 231, 15, 4);
          drawButton(15, 36);
        }
        drawPlayerAndTime(2, 48);
        break;
      case 1: // after the first button has been pressed
        playerQuicksand = false;
        drawPlayerAndTime(2, 48);
        quicksand(89, 65, 39, 108);
        quicksand(128, 144, 48, 29);
        quicksand(185, 113, 39, 99);
        if (gfx_CheckRectangleHotspot(playerX, playerY, 8, 8, 15, 37, 15, 5)) {
          button = 2;
          gfx_SetColor(COLOR_GRAY);
          gfx_FillRectangle_NoClip(80, 8, 9, 140);
          gfx_SetColor(COLOR_DARK_PURPLE);
          gfx_FillRectangle_NoClip(15, 36, 15, 4);
          gfx_FillRectangle_NoClip(89, 65, 39, 108);
          gfx_FillRectangle_NoClip(128, 144, 48, 29);
          gfx_FillRectangle_NoClip(185, 113, 39, 99);
        }
        break;
      default: // after the second button has been pressed
        for (uint8_t antiGravityDrawer = 0; antiGravityDrawer < 200; antiGravityDrawer += 48) {
          antiGravity(0, antiGravityDrawer / 2 + 96, antiGravityDrawer + 80, 25);
        }
        antiGravity(270, 50, 50, 167);
        rectPlatform(80, 8, 9, 90);
        drawPlayerAndTime(2, 48);
      break;
    }
    endGoal(287, 50);
    playerAntiGravity = anyAntiGravity;
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
