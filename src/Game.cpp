#include "Game.h"
std::vector<std::string> ReadFile(const std::string& file){
    std::ifstream input(file);
    if (!input.is_open())
    {
        spdlog::error("No se pudo abrir el archivo de datos");
    }

    nlohmann::json data;
    input >> data;

    std::vector<std::string> names;

    for (const auto& name : data["names"])
    {
        names.push_back(name);
    }

    return names;
}

Game::Game(int males, int females){
    window = nullptr;
    renderer = nullptr;
    Males = males;
    Females = females;

    AnchoAlto = std::make_tuple(1920 * 1.0f, 1080 * 1.0f);
    isRunning = false;
    world = new World(Width,Height,Cellsize);
}

void Game::Initialize()
{
    //Creación de pantalla
    this->window = SDL_CreateWindow(
        "Dating Simulator", 
        std::get<0>(this->AnchoAlto),
        std::get<1>(this->AnchoAlto),
        SDL_WINDOW_FULLSCREEN
    );
    this->renderer =  SDL_CreateRenderer(window, nullptr);

    //Control y logeo de errores
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        spdlog::error("Error inicializando SDL");
    }
    if (window == nullptr)
    {
        spdlog::error("Error creando ventana SDL");
    }
    if (renderer == nullptr)
    {
        spdlog::error("Error obteniendo renderer SDL");
    }
}

void Game::Run()
{
    Start();
    Uint64 lastFrame = SDL_GetTicks();
    this->isRunning = true;
    while (isRunning) //Esto se ejecuta cada vez por frame
    {
        // Setear el DeltaTime
        Uint64 now = SDL_GetTicks();
        float deltaTime = (now - lastFrame) / 1000.0f;
        lastFrame = now;
        ProcessInput();
        Update(deltaTime);
        Render();
    }

}

void Game::Start()
{
    //Lectura del Json y agarre de sus datos
    std::vector<std::string> NombresHombres = ReadFile("./assets/hombres.json");
    std::vector<std::string> NombresMujeres = ReadFile("./assets/mujeres.json");

    for (int i = 0; i < Males; i++)
    {
        world->CreatePerson(NombresHombres[i], MALE);
    }
    for (int i = 0; i < Females; i++)
    {
        world->CreatePerson(NombresMujeres[i], FEMALE);
    }
}

void Game::ProcessInput()
{
    // Getting Input data from player
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {   
            //Salirse de la pantalla, apaga el programa
            case SDL_EVENT_QUIT:
                isRunning = false;
                break;
            //Presionar esc, apaga el programa
            case SDL_EVENT_KEY_DOWN:
                if (!event.key.repeat && event.key.key == SDLK_ESCAPE){
                    isRunning = false;
                }
                if (!event.key.repeat && event.key.key == SDLK_1){
                    spdlog::info("Eres un monstruo");
                    world->Apocalypsis();
                }
                break;
        }
    }
}

void Game::Update(float deltaTime) {
    static float simulationTimer = 0.0f;
    simulationTimer += deltaTime;
    
    bool shouldMove = false;
    if (simulationTimer >= 3.0f) {
        shouldMove = true;
        simulationTimer = 0.0f;
    }
    
    for (Person* person : world->GetPersons()) {
        if (!person->IsAlive()){
            continue;
        }
        if (shouldMove) {
            if (NumberRandomizer(false, 0, 1) == 0) {
                int direction = NumberRandomizer(false, 0, 3);
                int currentY = std::get<0>(person->GetPosition());
                int currentX = std::get<1>(person->GetPosition());
                
                switch (direction) {
                    case 0:
                        if (currentY - 1 >= 0) {
                            person->SetPosition(std::make_tuple(currentY - 1, currentX));
                        }
                        break;
                    case 1:
                        if (currentY + 1 < Height) {
                            person->SetPosition(std::make_tuple(currentY + 1, currentX));
                        }
                        break;
                    case 2:
                        if (currentX + 1 < Width) {
                            person->SetPosition(std::make_tuple(currentY, currentX + 1));
                        }
                        break;
                    case 3:
                        if (currentX - 1 >= 0) {
                            person->SetPosition(std::make_tuple(currentY, currentX - 1));
                        }
                        break;
                }
            }
        }
    }
    if (shouldMove) {
        world->UpdateGrid();
    }
    world->MakeMeetings();
}

void Game::Render()
{
    // Renderer
    SDL_FRect rectFondo{0, 0, 1920, 1080};
    SDL_Surface* surfacefondo = IMG_Load("./assets/desktop-wallpaper-backgrounds-for-visual-novel-school-yard-anime.jpg");
    SDL_Texture* texturebackground = SDL_CreateTextureFromSurface(renderer, surfacefondo);
    SDL_DestroySurface(surfacefondo);
    SDL_RenderTexture(renderer, texturebackground, nullptr, &rectFondo);

    int gridWidth = Width * Cellsize;
    int gridHeight = Height * Cellsize;
    int offsetX = (1920 - gridWidth) / 2;
    int offsetY = (1080 - gridHeight) / 2;
    
    // Renderizar bordes de la grilla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int x = 0; x <= Width; x++) {
        SDL_RenderLine(renderer, 
            offsetX + x * Cellsize, offsetY, 
            offsetX + x * Cellsize, offsetY + gridHeight);
    }
    for (int y = 0; y <= Height; y++) {
        SDL_RenderLine(renderer,
            offsetX, offsetY + y * Cellsize,
            offsetX + gridWidth, offsetY + y * Cellsize);
    }
    
    for (Person* person : world->GetPersons()){
        std::string nombre = person->GetName();
        enum Sex sexo = person->GetSex();
        
        if (sexo == FEMALE) {
            SDL_SetRenderDrawColor(renderer, 255, 182, 193, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        }
        
        int personY = std::get<0>(person->GetPosition());
        int personX = std::get<1>(person->GetPosition());
        
        SDL_FRect rectPersona{
            (float)offsetX + personX * Cellsize,
            (float)offsetY + personY * Cellsize,
            Cellsize, 
            Cellsize
        };
        SDL_RenderFillRect(renderer, &rectPersona);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderRect(renderer, &rectPersona);
        
        if (!nombre.empty()) {
            char primeraLetra = nombre[0];
            std::string letraStr(1, primeraLetra);
            float textX = offsetX + personX * Cellsize + Cellsize/2 - 8;
            float textY = offsetY + personY * Cellsize + Cellsize/2 - 8;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDebugText(renderer, textX, textY, letraStr.c_str());
        }
    }
    SDL_RenderPresent(renderer);
}