#include <SDL3/SDL.h>
#include "Game.h"
#include <spdlog/spdlog.h>

int main() {
    Game game(25, 25);
    game.Initialize();
    game.Run();
    return 0;
}