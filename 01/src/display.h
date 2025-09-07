#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool init();
void setup(void);
bool process_input(void);
void update(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void draw_grid(void);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void render(void);
void destroy_window(void);