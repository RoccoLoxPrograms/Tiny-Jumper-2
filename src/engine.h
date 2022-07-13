#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void drawPlayerAndTime(int, uint8_t);
void endOfFrame(void);
void drawButton(uint24_t, uint8_t);
void resetData(void);
void toString(float, uint8_t);
void rectPlatform(float, float, float, float);
void spike(float, float, float, float);
void endGoal(float, float);
void bouncePad(float, float, float, float);
void antiGravity(float, float, float, float);
void quicksand(float, float, float, float);
void player(void);
void deadScreen(void);
void goalScreen(void);
void PrintCenteredText(const char *text, uint8_t, uint8_t);

#ifdef __cplusplus
}
#endif

#endif
