#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <random>
#include <fstream>
#include <spdlog/spdlog.h>
#include <json.hpp>
#include "EntityManager/World.h"


class Game{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        int Males;
        int Females;

        std::tuple<float,float> AnchoAlto;

        bool inputActive;
        int pendingFunction;
        std::string textBuffer;
        
        bool isRunning;

        World* world;
        void Start();
        void ProcessInput();
        void Update(float deltaTime);
        void Render();
        void ExecuteFunction();
    public:
        static const int Width = 25;
        static const int Height = 25;
        static const int Cellsize = 35;
        Game(int males, int females);
        void Initialize();
        void Run();
};

std::vector<std::string> ReadFile(const std::string& file);
