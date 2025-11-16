#include "Grid.h"
Grid::Grid(int width, int height, int cellsize){
    Width = width;
    Height = height;
    CellSize = cellsize;
    GridPositions = std::vector<std::vector<Person*>>(height, std::vector<Person*>(width, nullptr));
}

void Grid::Insert(Person* person) {
    while (true){
        int x = (int)NumberRandomizer(false, 0, Width - 1);
        int y = (int)NumberRandomizer(false, 0, Height - 1);
        if (GridPositions[y][x] == nullptr){
            GridPositions[y][x] = person;
            person->SetPosition(std::make_tuple(y, x));
            break;
        }
    }
}
void Grid::UpdatePersonPosition(Person* person) {
    int x = std::get<1>(person->GetPosition());
    int y = std::get<0>(person->GetPosition());
    
    if (x >= 0 && x < Width && y >= 0 && y < Height) {
        for (int i = 0; i < Height; i++) {
            for (int j = 0; j < Width; j++) {
                if (GridPositions[i][j] == person) {
                    GridPositions[i][j] = nullptr;
                }
            }
        }
        GridPositions[y][x] = person;
    }
}
/*No código, pero se ideó en base a esta pregunta en stackoverflow: https://stackoverflow.com/questions/55497134/using-a-spatial-index-to-find-points-within-range-of-each-other?*/
std::vector<Person*> Grid::GetNeighbors(Person* person) {
    std::vector<Person*> vecinos;
    int cy = std::get<0>(person->GetPosition());
    int cx = std::get<1>(person->GetPosition());
    for (int dy = -2; dy <= 2; dy++) {
        for (int dx = -2; dx <= 2; dx++){
            if (dx == 0 && dy == 0){
                continue;
            }
            int y = cy + dy;
            int x = cx + dx;
            if (x >=0 && y >= 0 && x < Width && y < Height && GridPositions[y][x] != nullptr) {
                vecinos.push_back(GridPositions[y][x]);
            }
        }
    }
    return vecinos;
}