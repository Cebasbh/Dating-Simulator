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
    #warning puedes hacer un enum pequeño / mediano / grande
    world = new World(Width,Height,Cellsize);
}

void Game::Initialize()
{
    //Creación de pantalla
    this->window = SDL_CreateWindow(
        #warning PONERLE NOMBREAAAAA
        "Megaman X", 
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
        // Lógica de movimiento cada 3 segundos
        if (shouldMove) {
            if (NumberRandomizer(false, 0, 3) == 0) {
                int TILE_SIZE = 50.0f;
                
                // Elegir dirección aleatoria
                int direction = NumberRandomizer(false, 0, 3);
                
                switch (direction) {
                    case 0: // Arriba
                        person->SetPosition(
                            std::make_tuple(std::get<0>(person->GetPosition()) - TILE_SIZE,std::get<1>(person->GetPosition()))
                        );
                        break;
                    case 1: // Abajo
                        person->SetPosition(
                            std::make_tuple(std::get<0>(person->GetPosition()) + TILE_SIZE,std::get<1>(person->GetPosition()))
                        );
                        break;
                    case 2: // Derecha
                        person->SetPosition(
                            std::make_tuple(std::get<0>(person->GetPosition()), std::get<1>(person->GetPosition()) + TILE_SIZE)
                        );
                        break;
                    case 3: // Izquierda
                        person->SetPosition(
                            std::make_tuple(std::get<0>(person->GetPosition()), std::get<1>(person->GetPosition()) - TILE_SIZE)
                        );
                        break;
                }
                world->MakeMeetings();
            }
        }
    }
}

void Game::Render()
{
    // Renderer
    SDL_FRect rectFondo{0, 0, 1920, 1080};
    
    SDL_Surface* surfacefondo = IMG_Load("./assets/desktop-wallpaper-backgrounds-for-visual-novel-school-yard-anime.jpg");
    SDL_Texture* texturebackground = SDL_CreateTextureFromSurface(renderer, surfacefondo);
    SDL_DestroySurface(surfacefondo);

    SDL_RenderTexture(renderer, texturebackground, nullptr, &rectFondo);
    
    for (Person* person : world->GetPersons()){
        // Obtener información de la persona
        std::string nombre = person->GetName();
        enum Sex sexo = person->GetSex();
        
        // Elegir color según el sexo
        if (sexo == FEMALE) {
            // Rosa para chicas
            SDL_SetRenderDrawColor(renderer, 255, 182, 193, 255); // Color rosa
        } 
        else {
            // Azul para chicos  
            SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Color azul claro
        }
        
        // Dibujar el cuadro de la persona
        SDL_FRect rectPersona{
            (float)std::get<1>(person->GetPosition()), 
            (float)std::get<0>(person->GetPosition()), 
            Cellsize, 
            Cellsize
        };
        SDL_RenderFillRect(renderer, &rectPersona);
        
        // Dibujar borde del cuadro
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Borde negro
        SDL_RenderRect(renderer, &rectPersona);
        
        // Renderizar la primera letra del nombre
        if (!nombre.empty()) {
            char primeraLetra = nombre[0];
            std::string letraStr(1, primeraLetra);
            
            // Crear superficie con la letra (necesitarás una fuente)
            SDL_Color colorTexto = {0, 0, 0, 255}; // Texto negro
            
            // Si tienes TTF cargado:
            // TTF_Font* font = TTF_OpenFont("assets/font.ttf", 24);
            // SDL_Surface* textSurface = TTF_RenderText_Solid(font, letraStr.c_str(), colorTexto);
            // SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            
            // Posicionar la letra en el centro del cuadro
            float textX = std::get<1>(person->GetPosition()) + Cellsize/2 - 5;
            float textY = std::get<0>(person->GetPosition()) + Cellsize/2 - 5;
            SDL_FRect textRect{textX, textY, 10, 10};
            
            // SDL_RenderTexture(renderer, textTexture, nullptr, &textRect);
            // SDL_DestroyTexture(textTexture);
            // SDL_DestroySurface(textSurface);
            
            // Versión temporal: dibujar un punto para representar la letra
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderPoint(renderer, textX + 5, textY + 5);
        }
        // Opcional: mostrar estado de disponibilidad con el borde
        if (!person->IsAvailable()) {
            // Corazón roto - borde rojo
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderRect(renderer, &rectPersona);
        }
    }
    SDL_RenderPresent(renderer);
}