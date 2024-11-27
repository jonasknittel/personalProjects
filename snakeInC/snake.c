#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>

#define WINDOW_WIDTH (600)
#define WINDOW_HEIGHT (600)

int main(void) {
    // Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        printf("error initializing SDL, %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* win = SDL_CreateWindow("snake",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if (!win) {
        printf("error creating window, %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);

    // Define centered rectangle
    SDL_Rect r;

    r.h = 30;
    r.w = 30;
    r.x = (WINDOW_WIDTH / 2) - (r.w / 2);
    r.y = (WINDOW_HEIGHT / 2) - (r.h / 2);

    // Draw rectangle
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);

    // Game loop
    for (int i = 0; i < 5; i++) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // New Position
        r.y += 30;

        SDL_RenderFillRect(renderer, &r);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000);
    }

    // Exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    return 0;
}