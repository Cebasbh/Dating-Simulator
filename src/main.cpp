#include <SDL3/SDL.h>
#include "Game.h"
#include <spdlog/spdlog.h>

int main(int argc, char* argv[]) {
    spdlog::info("=== INICIANDO APLICACIÓN ===");
    
    try {
        Game game(5, 5);
        game.Initialize();
        game.Run();
    } 
    catch (const std::exception& e) {
        spdlog::critical("EXCEPCIÓN NO MANEJADA: {}", e.what());
        return 1;
    }
    
    spdlog::info("=== APLICACIÓN FINALIZADA ===");
    return 0;
}