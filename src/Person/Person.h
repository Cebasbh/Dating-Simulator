#pragma once
#include <tuple>
#include <vector>
#include "AVL/AVLTree.h"
#include "SupportFunctions/Randomizers.h"
#include "WeightTree/WeightTree.h"
class AVLTree;
class AVLNode;

enum Level {
    COUPLE_EVENTS = 5,
    LOW = 10,
    MEDIUM = 20,
    HIGH = 30
};

enum Sex {
    MALE = 0,
    FEMALE = 1
};

class Person {
    private:
        static int Count;
        int Id;
        std::string Name;
        enum Sex Sex;
        bool Alive;
        bool Available;
        Person* Couple;
        std::tuple <int,int> Position;
        std::vector<int> Chars;
        WeightTree* Likings;
        AVLTree* FriendsIds;
        AVLTree* FriendsComp;

    public:
        Person(std::string name, enum Sex sex);
        ~Person();
        static const int ValuesPerChar = 3;
        static const int CharsPerScope = 8;
        static const int ScopePerPerson = 3;

        bool IsAlive();
        std::string GetName();
        int GetId();
        enum Sex GetSex();
        Person* GetCouple();
        bool IsAvailable();
        void SetCouple(Person* couple);
        std::tuple <int,int> GetPosition();
        void SetPosition(std::tuple <int,int> position);

        std::vector<int> GetChars();
        WeightTree* GetLikings();
        AVLTree* GetFriendsIds();
        AVLTree* GetFriendsComp();
        
        std::vector<int> CharsGenerator();
        WeightTree* LikingsGenerator();

        float Compatibility(Person* potentialcouple);
        void Meet(Person* newfriend);
        std::vector<std::tuple<Person*,float>> GetFriendList();
        Person* FavoriteFriend(AVLNode* node = nullptr);
        void FightFriend(Person* otherperson, enum Level quantity);
        void BondFriend(Person* otherperson, enum Level quantity);
        bool Date(Person* pretender);
        void Die();
        void BreakHeart();

        void PrintChars();
        void PrintFriendsList();
};
