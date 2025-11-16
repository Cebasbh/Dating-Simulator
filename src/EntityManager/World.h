#pragma once
#include <string>
#include "HashLP/HashTable.h"
#include "Grid/Grid.h"

class World
{
    private:
        HashTable* Persons;
        Grid* Mundo;
    public:
        World(int width, int height, int cellsize);
        ~World();
        void CreatePerson(std::string name, enum Sex sex);
        void MakeMeeting(std::string nameA, std::string nameB);
        void CreateFight(std::string nameA, std::string nameB, enum Level level);
        void CreateBond(std::string nameA, std::string nameB, enum Level level);
        void CoupleUp(std::string nameA, std::string nameB);
        void Apocalypsis();

        void UpdateGrid();
        void MakeMeetings();
        void KillEveryone();
        std::vector<Person*> GetPersons();
};
