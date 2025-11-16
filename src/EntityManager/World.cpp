#include "World.h"
World::World(int width, int height, int cellsize){
    Persons = new HashTable();
    Mundo = new Grid(width,height,cellsize);
}

World::~World(){
}
void World::CreatePerson(std::string name, enum Sex sex){
    Person* NewPerson = new Person(name, sex);
    Persons->Insert(name,NewPerson);
    Mundo->Insert(NewPerson);
}
void World::MakeMeeting(std::string nameA, std::string nameB){
    Person* Ap = Persons->Search(nameA);
    Person* Bp = Persons->Search(nameB);
    Ap->Meet(Bp);
}
void World::CreateFight(std::string nameA, std::string nameB, enum Level level){
    Person* Ap = Persons->Search(nameA);
    Person* Bp = Persons->Search(nameB);
    Ap->FightFriend(Bp,level);
}
void World::CreateBond(std::string nameA, std::string nameB, enum Level level){
    Person* Ap = Persons->Search(nameA);
    Person* Bp = Persons->Search(nameB);
    Ap->BondFriend(Bp,level);
}
void World::CoupleUp(std::string nameA, std::string nameB){
    Person* Ap = Persons->Search(nameA);
    Person* Bp = Persons->Search(nameB);
    Ap->Date(Bp);
}
void World::KillEveryone(){
    HashEntry** Bins = Persons->GetBins();
    for (int i = 0; i < Persons->GetSize(); ++i) {
        if (Bins[i] != nullptr && !Bins[i]->GetIsDeleted() && Bins[i]->GetValue()->IsAlive()){
            Bins[i]->GetValue()->Die();
        }
    }
}
void World::UpdateGrid(){
    HashEntry** Bins = Persons->GetBins();
    for (int i = 0; i < Persons->GetSize(); ++i){
        if (Bins[i] != nullptr && !Bins[i]->GetIsDeleted() && Bins[i]->GetValue() != nullptr){
                Mundo->UpdatePersonPosition(Bins[i]->GetValue());
        }
    }
}
void World::MakeMeetings(){
    HashEntry** Bins = Persons->GetBins();
    for (int i = 0; i < Persons->GetSize(); ++i) {
        if (Bins[i] != nullptr && !Bins[i]->GetIsDeleted() && Bins[i]->GetValue()->IsAvailable() && Bins[i]->GetValue()->GetCouple() == nullptr && Bins[i]->GetValue()->GetSex() == MALE){
                Person* alfamale = Bins[i]->GetValue();
                std::vector<Person*> peopletomeet = Mundo->GetNeighbors(alfamale);
                if (peopletomeet.size() > 0){
                    for (Person* p : peopletomeet){
                        if (p->GetSex() == FEMALE && alfamale->GetFriendsIds()->SearchbyId(p) == nullptr){
                            alfamale->Meet(p);
                        }
                    }
                }
            }
    }
}
void World::Apocalypsis(){
    std::cout << "Se ve algo raro a lo lejos" << "\n";
    std::cout << "ES UN METEORITO!!!" << "\n";
    std::cout << "Todos se apresuran a buscar pareja, para compartir el fin del mundo con alguien" << "\n";
    std::cout << "\n";
    HashEntry** Bins = Persons->GetBins();
    while (true){
        bool EveryoneHasCouple = true;
        for (int i = 0; i < Persons->GetSize(); ++i) {
            if (Bins[i] != nullptr && !Bins[i]->GetIsDeleted() && Bins[i]->GetValue()->IsAvailable() && Bins[i]->GetValue()->GetCouple() == nullptr && Bins[i]->GetValue()->GetSex() == MALE){
                Person* alfamale = Bins[i]->GetValue();
                EveryoneHasCouple = false;
                std::vector<std::tuple<Person*,float>> list = Bins[i]->GetValue()->GetFriendsComp()->ReversedInorderVector();
                if (list.size() == 0){
                    std::cout << Bins[i]->GetValue()->GetName() << " no conoce a nadie :c " << "\n";
                    EveryoneHasCouple = true;
                    continue;
                }
                std::cout << "Intereses amorosos en orden de " << Bins[i]->GetValue()->GetName() << ": " << "\n";
                for (int k = 0; k < list.size(); ++k) {
                    std::cout << "Nombre: " << std::get<0>(list[k])->GetName() << " / Match%: " << std::get<1>(list[k]) << "\n";
                }
                std::cout <<  "\n";
                for (int j = 0; j < list.size(); ++j) {
                    bool success = std::get<0>(list[j])->Date(alfamale);
                    if (success){
                        break;
                    }
                    if (!success && j + 1 == list.size()){
                        Bins[i]->GetValue()->BreakHeart();
                    }
                    }
                }
            }
        if (EveryoneHasCouple){
            break;
        }
    }
    std::cout << "PAREJAS FINALES: " << "\n";
    std::cout << "\n";
    for (int i = 0; i < Persons->GetSize(); ++i) {
        if (Bins[i] != nullptr && !Bins[i]->GetIsDeleted() && Bins[i]->GetValue()->GetCouple() != nullptr && Bins[i]->GetValue()->GetSex() == MALE){
            std::cout << Bins[i]->GetValue()->GetName() << " se quedó con " << Bins[i]->GetValue()->GetCouple()->GetName() << "\n";
        }
        if (Bins[i] != nullptr && !Bins[i]->GetIsDeleted() && Bins[i]->GetValue()->GetCouple() == nullptr){
            std::cout << Bins[i]->GetValue()->GetName() << " se quedó sin pareja... que sad hermano :'v " << "\n";
        }
    }
    std::cout << "\n";
    KillEveryone();
    
}

std::vector<Person*> World::GetPersons(){
    std::vector<Person*> persons;
    HashEntry** Bins = Persons->GetBins();
    for (int i = 0; i < Persons->GetSize(); ++i){
        if (Bins[i] != nullptr && !Bins[i]->GetIsDeleted() && Bins[i]->GetValue() != nullptr){
                persons.push_back(Bins[i]->GetValue());
            }
        }
    return persons;
}