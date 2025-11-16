#include <SDL3/SDL.h>
#include "Game.h"
#include <spdlog/spdlog.h>

int main() {
    Game game(26, 26);
    game.Initialize();
    game.Run();
    return 0;
}