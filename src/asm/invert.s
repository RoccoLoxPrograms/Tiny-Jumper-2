    .assume adl=1

    .global _invertPalette
    .type   _invertPalette, @function

    .section .text

_invertPalette:
    ld hl, $E30200 ; memory address of the palette
    ld b, 0

.loop:
    ld a, (hl)
    cpl
    ld (hl), a
    inc hl
    ld a, (hl)
    cpl
    ld (hl), a
    inc hl
    djnz .loop
    ret
