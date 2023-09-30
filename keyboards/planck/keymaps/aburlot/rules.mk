EXTRAKEY_ENABLE = yes       # Audio control and System control
LAYOUTS = ortho_4x12

ifeq ($(strip $(AUDIO_ENABLE)), yes)
    SRC += muse.c
endif
