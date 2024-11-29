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
    SDL_Delay(1000);

    // Set to 1 when window is closed
    int close_requested = 0;

    // Speed
    int x = 0;
    int y = 0;

    // Game loop
    while (!close_requested) {
        // Handle close request
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            // Event handler
            switch (event.type) {
            case SDL_QUIT: 
                close_requested = 1; 
                break;
            case SDL_KEYDOWN:
                // Speed and direction
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_UP:
                    case SDL_SCANCODE_W:
                        // Set speed
                        y = -30;
                        x = 0;
                        break;
                    case SDL_SCANCODE_DOWN:
                    case SDL_SCANCODE_S:
                        // Set speed
                        y = 30;
                        x= 0;
                        break;
                    case SDL_SCANCODE_LEFT:
                    case SDL_SCANCODE_A:
                        // Set speed
                        y = 0;
                        x = -30;
                        break;
                    case SDL_SCANCODE_RIGHT:
                    case SDL_SCANCODE_D:
                        // Set speed
                        y = 0;
                        x = 30;
                        break;
                }
                break;
            }
        }

        // Render stuff
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // New Position
        r.y += y;
        r.x += x;

        SDL_RenderFillRect(renderer, &r);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000);
    }

    // Exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    return 0;
}