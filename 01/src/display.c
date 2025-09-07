#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t *color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int window_width;
int window_height;

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    window_width = display_mode.w;
    window_height = display_mode.h;

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    return true;
}

void setup(void) {
    // Allocate memory for color buffer
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    // Create a SDL texture to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
}

bool process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            return false;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}

void update(void) {
    // Placeholder for update logic
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int draw_x = x + j;
            int draw_y = y + i;
            if (draw_x >= 0 && draw_x < window_width && draw_y >= 0 && draw_y < window_height) {
                color_buffer[draw_y * window_width + draw_x] = color;
            }
        }
    }
}

void draw_grid(void) {
    int grid_size = 10;
    uint32_t grid_color = 0xFF000000; // ARGB format for black

    for (int x = 0; x < window_width; x += grid_size) {
        for (int y = 0; y < window_height; y++) {
            color_buffer[y * window_width + x] = grid_color;
        }
    }

    for (int y = 0; y < window_height; y += grid_size) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[y * window_width + x] = grid_color;
        }
    }
}

void render_color_buffer(void) {
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width * sizeof(uint32_t)));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
    for (int i = 0; i < window_width * window_height; i++) {
        color_buffer[i] = color;
    }
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_grid();
    draw_rect(50, 50, 200, 200, 0xFFFF0000); // ARGB format for blue
    render_color_buffer();
    clear_color_buffer(0xFFFFFF00); // ARGB format for red
    SDL_RenderPresent(renderer);
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}