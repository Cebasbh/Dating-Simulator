#include "Person.h"

int Person::Count = 1;

Person::Person(std::string name, enum Sex sex){
    Id = Count;
    Name = name;
    Sex = sex;
    Couple = nullptr;
    Alive = true;
    Available = true;    
    Chars = CharsGenerator();
    Likings = LikingsGenerator();
    FriendsIds = new AVLTree();
    FriendsComp = new AVLTree();
    Count++;
}

std::vector<int> Person::CharsGenerator(){
    std::vector<std::vector<std::vector<int>>> Chars(Person::ScopePerPerson, std::vector<std::vector<int>>(Person::CharsPerScope, std::vector<int>(Person::ValuesPerChar, 0)));
    std::vector<int> finalChars;
    for (int i = 0; i < Person::ScopePerPerson; i++){
        for (int j = 0; j < Person::CharsPerScope; j++){
            int index = NumberRandomizer(false, 0, 2);
            Chars[i][j][index] = 1;
        }
    }
    for (int i = 0; i < Person::ScopePerPerson; i++){
        for (int j = 0; j < Person::CharsPerScope; j++){
            for (int k = 0; k < Person::ValuesPerChar; k++){
                finalChars.push_back(Chars[i][j][k]); 
            }
        }
    }
    return finalChars;
}

WeightTree* Person::LikingsGenerator(){
    WeightTree* tree = new WeightTree();
    int counter = (Id - 1) * (ScopePerPerson * CharsPerScope * ValuesPerChar + ScopePerPerson * CharsPerScope  + ScopePerPerson + 1) + 1;
    //Crear nodos capa 1
    for (int i = 0; i < ScopePerPerson; i++){
        for (int j = 0; j < CharsPerScope; j++){
            std::vector<float> values = FractionRandomizer(ValuesPerChar);
            for (int k = 0; k < ValuesPerChar; k++){
                tree->AddNode(values[k],{});
            }
        }
    }
    //Crear nodos capa 2 y asignarles sus padres de capa 1
    for (int i = 0; i < ScopePerPerson; i++){
        std::vector<float> chars = FractionRandomizer(CharsPerScope);
        for (int j = 0; j < CharsPerScope; j++){
            std::vector<int> valuess;
            for (int k = 0; k < ValuesPerChar; k++){
                valuess.push_back(counter++);
            }
            tree->AddNode(chars[j],valuess);
        }
    }
    //Crear nodos capa 3 y asignarles sus padres de capa 2
    std::vector<float> scopes = FractionRandomizer(ScopePerPerson);
    for (int i = 0; i < ScopePerPerson; i++){
        std::vector<int> charss;
        for (int j = 0; j < CharsPerScope; j++){
            charss.push_back(counter++);
        }
        tree->AddNode(scopes[i],charss);
    }
    //Crear nodo final y asignarles sus padres de capa 3
    std::vector<int> scopess;
    for (int i = 0; i < ScopePerPerson; i++){
        scopess.push_back(counter++);
    }
    tree->AddNode(1,scopess);
    return tree;
}

void Person::Meet(Person* newfriend)
{   
    if(!newfriend){
        return;
    }
    if(!newfriend->IsAlive()){
        std::cout << newfriend->GetName() << " está muerto :( " <<"\n";
        return;
    }
    if (Sex == newfriend->GetSex()){
        std::cout << "Bro? " << Name << " y " << newfriend->GetName() << " son del mismo sexo :/" << "\n";
    }
    else{
        FriendsIds->SetRoot(FriendsIds->InsertbyId(std::make_tuple(newfriend,Compatibility(newfriend))));
        FriendsComp->SetRoot(FriendsComp->InsertbyComp(std::make_tuple(newfriend,Compatibility(newfriend))));

        newfriend->GetFriendsIds()->SetRoot(newfriend->GetFriendsIds()->InsertbyId(std::make_tuple(this,newfriend->Compatibility(this))));
        newfriend->GetFriendsComp()->SetRoot(newfriend->GetFriendsComp()->InsertbyComp(std::make_tuple(this,newfriend->Compatibility(this))));
        std::cout << Name << " y " << newfriend->GetName() << " ahora son amigos!"<< "\n";
    }
    std::cout <<"\n";
}
void Person::FightFriend(Person* otherperson, enum Level quantity){
    if(!otherperson){
        return;
    }
    AVLNode* person = FriendsIds->SearchbyId(otherperson);
    if(!person){
        std::cout << Name << " y " << otherperson->GetName() << " no se conocen :c" << "\n";
        return;
    }
    if(!otherperson->IsAlive()){
        std::cout << otherperson->GetName() << " está muerto :( " <<"\n";
        return;
    }
    float actualcompability = std::get<1>(person->GetKey());
    FriendsComp->DeletebyComp(actualcompability);

    float newcompatibility = actualcompability * (1 - quantity / 100.0f);
    FriendsComp->SetRoot(FriendsComp->InsertbyComp(std::make_tuple(otherperson,newcompatibility)));
    person->SetKey(newcompatibility);

    AVLTree* otherpersontree = otherperson->GetFriendsComp();
    AVLNode* me = otherperson->FriendsIds->SearchbyId(this);
    actualcompability = std::get<1>(me->GetKey());
    otherpersontree->DeletebyComp(actualcompability);

    newcompatibility = actualcompability * (1 - quantity / 100.0f);
    otherpersontree->SetRoot(otherpersontree->InsertbyComp(std::make_tuple(this,newcompatibility)));
    me->SetKey(newcompatibility);
    if (quantity == COUPLE_EVENTS){
        std::cout << Name << " y " << otherperson->GetName() << " sienten menos pasión (merecido)"<< "\n";
    }
    else if (quantity == HIGH){
        std::cout <<  otherperson->GetName() << " ahora odia a " << Name << "\n";
    }
    else{
        std::cout << Name << " se peleó con " << otherperson->GetName() << "\n";
    }
    std::cout <<"\n";
}
void Person::BondFriend(Person* otherperson, enum Level quantity){
    if(!otherperson){
        return;
    }
    if(!otherperson->IsAlive()){
        std::cout << otherperson->GetName() << " está muerto :( " <<"\n";
        return;
    }
    AVLNode* person = FriendsIds->SearchbyId(otherperson);
    if(!person){
        std::cout << Name << " y " << otherperson->GetName() << " no se conocen :c" << "\n";
        return;
    }
    float actualcompability = std::get<1>(person->GetKey());
    FriendsComp->DeletebyComp(actualcompability);

    float newcompatibility = actualcompability * (1 + quantity / 100.0f);
    FriendsComp->SetRoot(FriendsComp->InsertbyComp(std::make_tuple(otherperson,newcompatibility)));
    person->SetKey(newcompatibility);

    AVLTree* otherpersontree = otherperson->GetFriendsComp();
    AVLNode* me = otherperson->FriendsIds->SearchbyId(this);
    actualcompability = std::get<1>(me->GetKey());
    otherpersontree->DeletebyComp(actualcompability);

    newcompatibility = actualcompability * (1 + quantity / 100.0f);
    otherpersontree->SetRoot(otherpersontree->InsertbyComp(std::make_tuple(this,newcompatibility)));
    me->SetKey(newcompatibility);
    if (quantity == COUPLE_EVENTS){
        std::cout << Name << " y " << otherperson->GetName() << " se aman más que nunca :') "<< "\n";
    }
    else{
        std::cout << Name << " se relacionó con " << otherperson->GetName() << "\n";
    }
    std::cout <<"\n";
}

bool Person::Date(Person* pretender){
    if(!pretender){
        return false;
    }
    if(!pretender->IsAlive()){
        std::cout << pretender->GetName() << " está muerto :( " <<"\n";
        return false;
    }
    std::cout << pretender->GetName() << " le coquetea a " << Name << " :O" <<"\n";
    if (!Couple){
        pretender->SetCouple(this);
        Couple = pretender;
        std::cout << Name << " y " << Couple->GetName() << " empezaron a salir!" << "\n";
        std::cout <<"\n";
        return true;
    }
    else{
        std::cout << "...incluso sabiendo que " << Couple->GetName() << " es su pareja???" << "\n";
        if (Compatibility(pretender) < Compatibility(Couple)){
            std::cout << Name << " y " << Couple->GetName() << " se mantienen fuerte como pareja!" << "\n";
            std::cout << "Aumentaron su ligeramente compatibildad!" << "\n";
            BondFriend(Couple, COUPLE_EVENTS);
            std::cout <<"\n";
            return false;
        }
        else {
            std::cout << Name << " y " << Couple->GetName() << " se separaron!" << "\n";
            FightFriend(Couple, HIGH);

            std::cout << Name << " y " << pretender->GetName() << " ahora son pareja!" << "\n";
            std::cout << "...pero desconfían uno del otro?" << "\n";
            std::cout << "Disminuyen ligeramente su compatibildad!" << "\n";
            Couple->SetCouple(nullptr);
            Couple = pretender;
            pretender->SetCouple(this);
            FightFriend(Couple, COUPLE_EVENTS);
            std::cout <<"\n";
            return true;
        }
    }
}
void Person::PrintChars(){
    std::vector<std::string> datachars = {
        //Características físicas
        "Pelo Negro", "Pelo Castaño", "Pelo Rubio",                   // Color de Pelo
        "Ojos Marrones", "Ojos Azules", "Ojos Negros",                 // Color de Ojos
        "Altura Baja", "Altura Media", "Altura Alta",                  // Altura
        "Figura Delgada", "Figura Promedio", "Figura Atlética",        // Figura
        "Piel Clara", "Piel Café", "Piel Oscura",                     // Tono de piel
        "Rostro Ovalado", "Rostro Redondo", "Rostro Cuadrado",         // Tipo de rostro
        "Pelo Lacio", "Pelo Ondulado", "Pelo Rizado",                  // Tipo de pelo
        "Cejas Delgadas", "Uniceja", "Cejas Gruesas",                 // Cejas

        //Características de personalidad
        "Introvertido", "Ambivertido", "Extrovertido",        // Nivel Social
        "Sarcástico", "Absurdo", "Inteligente",               // Tipo de Humor
        "Tecnología", "Arte", "Deporte",                      // Hobby Principal
        "Casero", "Energético", "Aventuroso",                 // Plan Ideal
        "Directa", "Amigable", "Analítica",                   // Comunicación
        "Gusta Perros", "Gusta Gatos", "No le gustan mascotas", // Mascotas
        "Muy Ordenado", "Flexible", "Desordenado",            // Nivel de Orden
        "Rock", "Electrónica", "Reggaeton",                   // Gusto Musical

        //Características emocionales
        "Calmado", "Ansioso", "Reactivo",                // Manejo del Estrés
        "Optimista", "Realista", "Pesimista",            // Perspectiva
        "Muy empático", "Selectivo", "Pragmático",       // Nivel de Empatía
        "Paciente", "Moderado", "Impaciente",           // Nivel de Paciencia
        "Verbal", "Físico", "Reservado",                 // Expresión de Afecto
        "Evasivo", "Mediador", "Confrontacional",        // Manejo de Conflicto
        "Seguro", "Modesto", "Inseguro",                 // Confianza
        "Abierto", "Selectivo", "Privado"                // Apertura Emocional
    };
    std::cout << "Características de "<< Name << ": ";
    for (int i = 0; i < Chars.size(); i++){
        if (Chars[i] == 1){
            std::cout << datachars[i] << " / ";
        }
    }
    std::cout << "\n";
}

void Person::PrintFriendsList(){
    int counter = 1;
    FriendsComp->ReversedInorder(counter);
    std::cout <<"\n";
}

std::vector<std::tuple<Person*,float>> Person::GetFriendList(){
    return FriendsComp->ReversedInorderVector();
}

Person* Person::FavoriteFriend(AVLNode* node){
    if (node == nullptr)
        node = FriendsComp->GetRoot();
    if(!node){
        std::cout << Name << " no tiene persona preferida" << "\n";
        std::cout <<"\n";
        return nullptr;
    }
    if(!node->GetRight()){
        std::cout << "La persona preferida de "<< Name << " es " << std::get<0>(node->GetKey())->GetName() << "\n";
        std::cout <<"\n";
        return std::get<0>(node->GetKey());
    }
    else{
        return FavoriteFriend(node->GetRight());
    }
}

float Person::Compatibility(Person* potentialcouple){
    AVLNode* person = FriendsIds->SearchbyId(potentialcouple);
    if (!person){
        return Likings->CalculateFinalValue(potentialcouple->GetChars());
    }
    else{
        return std::get<1>(person->GetKey());
    }
}

void Person::Die(){
    if (Alive == false){
        std::cout << "No puede morir dos veces, ya déja descansar en paz"<< "\n";
    }
    else{
        if (Couple) {
            Couple->SetCouple(nullptr);
            Couple = nullptr;
        }
        std::cout << Name << " ha muerto..."<< "\n";
        int counter = 0;
        std::vector<std::tuple<Person*,float>>  amigos = GetFriendList();
        for (int i = 0; i < amigos.size(); i++){
            if (std::get<0>(amigos[i])->IsAlive()){
                std::cout << std::get<0>(amigos[i])->GetName() <<" lloró la muerte de " << Name << "\n";
                counter++;
            }
        }
        if (counter == 0){
            std::cout << "Pero no quedó nadie que pudiera llorar por "<< Name << "..." "\n";
        }
        Alive = false;
        Available = false;
    }
    std::cout << "\n";
}
bool Person::IsAlive(){
    return Alive;
}
bool Person::IsAvailable(){
    return Available;
}
void Person::BreakHeart(){
    Available = false;
}
Person::~Person(){
}
std::string Person::GetName(){
    return Name;
}
int Person::GetId(){
    return Id;
}
enum Sex Person::GetSex(){
    return Sex;
}
Person* Person::GetCouple(){
    return Couple;
}
void Person::SetCouple(Person* couple){
    Couple = couple;
}
std::tuple <int,int> Person::GetPosition(){
    return Position;
}
void Person::SetPosition(std::tuple <int,int> position){
    Position = position;
}
std::vector<int> Person::GetChars(){
    return Chars;
}
WeightTree* Person::GetLikings(){
    return Likings;
}
AVLTree* Person::GetFriendsComp(){
    return FriendsComp;
}
AVLTree* Person::GetFriendsIds(){
    return FriendsIds;
}
