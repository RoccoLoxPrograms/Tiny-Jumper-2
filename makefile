# ----------------------------
# Makefile Options
# ----------------------------

NAME = TNYJMPR2
ICON = icon.png
DESCRIPTION = "Sequel to the classic Tiny Jumper"
COMPRESSED = YES
COMPRESSED_MODE = zx0
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

FONTDIR = $(SRCDIR)/font
FONT = $(FONTDIR)/TinyJumperFont.fnt
FONT_INC = $(FONTDIR)/TinyJumperFont.inc

DEPS = $(FONT_INC)

# ----------------------------

include $(shell cedev-config --makefile)

# ----------------------------

$(FONT_INC): $(FONT)
	$(Q)$(call MKDIR,$(@D))
	$(Q)convfont -o carray -f $< -a 1 -b 1 -w bold -c 2 -x 9 -l 0x0B -Z $@

