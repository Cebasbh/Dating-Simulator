#include <tuple>
#include <string>
#include "Person/Person.h"

class Grid {
    private:
        int CellSize;
        int Width;
        int Height;
        std::vector<std::vector<Person*>> GridPositions;
    public:
        Grid(int width, int height, int cellsize);

        void Insert(Person* p);
        std::vector<Person*> GetNeighbors(Person* p);
};