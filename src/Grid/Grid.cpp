#include "Grid.h"
#warning reescribir variables
Grid::Grid(int width, int height, int cellsize){
    Width = width;
    Height = height;
    CellSize = cellsize;
    GridPositions = std::vector<std::vector<Person*>>(height, std::vector<Person*>(width, nullptr));
}

void Grid::Insert(Person* newperson) {
    while (true){
        int x = (int)NumberRandomizer(false, 0, Width - 1);
        int y = (int)NumberRandomizer(false, 0, Height - 1);
        if (GridPositions[y][x] == nullptr){
            GridPositions[y][x] = newperson;
            newperson->SetPosition(std::make_tuple(y*CellSize,x*CellSize));
            break;
        }
    }
}
std::vector<Person*> Grid::GetNeighbors(Person* person) {
    std::vector<Person*> vecinos;
    int cy = std::get<0>(person->GetPosition()) / CellSize;
    int cx = std::get<1>(person->GetPosition()) / CellSize;
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