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

        void Insert(Person* person);
        void UpdatePersonPosition(Person* person);
        std::vector<Person*> GetNeighbors(Person* person);
};