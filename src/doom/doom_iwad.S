.section .doom_iwad, "a"
.global doom_iwad_start
.global doom_iwad_end
.global doom_iwad_size
.balign 4
doom_iwad_start:
.incbin "newdoom1_1lev.wad"
.balign 4
doom_iwad_end:
.set doom_iwad_size, doom_iwad_end - doom_iwad_start
