#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"

bool is_running = false;

int main(void) {
    is_running = init();

    setup();

    while(is_running) {
        is_running = process_input();
        update();
        render();
        SDL_Delay(16); // Roughly 60 FPS
    }

    destroy_window();

	return 0;
}
