#include "font.h"

static const uint8_t TJFontData[] = {
	#include "TinyJumperFont.inc"
};

const fontlib_font_t *TJFont = (fontlib_font_t *)TJFontData;
