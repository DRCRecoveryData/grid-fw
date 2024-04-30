
#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "grid_gui.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t grid_color_t;

struct grid_font_model {

  void* font_handle;
  uint8_t foo;
};

extern struct grid_font_model grid_font_state;

int grid_font_init(struct grid_font_model* font);

int grid_font_draw_character(struct grid_font_model* font, struct grid_gui_model* gui, uint16_t x, uint16_t y, int size, int character, int* cursor_jump);

#ifdef __cplusplus
}
#endif
