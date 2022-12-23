    assume adl=1

    section .text

    public _invertPalette

_invertPalette:
    ld hl, $E30200 ; memory address of the palette
    ld c, 2

.loadLoop:
    ld b, 0

.loop:
    ld a, 255
    sub a, (hl)
    ld (hl), a
    inc hl
    djnz .loop
    dec c
    jr nz, .loadLoop
    ret
