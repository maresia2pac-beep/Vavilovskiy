#include <iostream>
#include "windows.h"
#include "GameClasses.h"
#include "BaseClasses.h"
#include "Evil.h"
#include <fstream> 
using namespace std;

enum class ValueQuality
{
    МУСОР, ОБЫЧНОЕ, РЕДКОЕ, МИФИЧЕСКОЕ, ЛЕГЕНДАРНОЕ 
};

struct Treasure
{
    Treasure() = default;
    string name{ "добыча" };
    ValueQuality quality = ValueQuality::МИФИЧЕСКОЕ;
    unsigned int price{ 0 };
    Treasure(ValueQuality quality)
    {
        switch (quality)
        {
        case ValueQuality::МУСОР:
            cout << "качество плохое\n";
            break;
        case ValueQuality::ОБЫЧНОЕ:
            cout << "качество средненькое\n";
            break;
        case ValueQuality::РЕДКОЕ:
            cout << "качество хорошее\n";
            break;
        case ValueQuality::МИФИЧЕСКОЕ:
            cout << "качество крутое\n";
            break;
        case ValueQuality::ЛЕГЕНДАРНОЕ:
            cout << "качество идеальное\n";
            break;
        default:
            break;
        }
    }
}; 

struct Сloth : Treasure 
{
    Сloth(ValueQuality quality) : Treasure(quality) {};
    string valueSite[5]{ "обувь", "перчатки", "шлем", "нагрудник", "пояс" };
    string site{NULL};
    unsigned short armor{ 1 };
};

enum class CharacterType {
    UNKNOWN = 0,
    WARRIOR,
    WIZARD,
    PALADIN
};

enum class EnemyType {
    КРЕСТЬЯНИН_АНДРЕЙ = 1,
    ЗЛОБНЫЙ_КРОЛИК,
    ЗЕЛИБОБА_С_УЛИЦЫ_СЕЗАМ,
    ГОНЧАР_РОМАНОВ,
    ВАХТЕРША_ЗИНА,
};

unsigned short TestChoise(unsigned short maxChoise, string text)
{
    unsigned short choise = 1;
    cin >> choise;
    while (choise > maxChoise || choise < 1)
    {
        cout << text << endl;
        cin >> choise;
    }
    return choise;
};

// Фабрика для создания персонажей
unique_ptr<Npc> CreateCharacter(CharacterType type)
{
    switch (type)
    {
    case CharacterType::UNKNOWN:
        return make_unique<Npc>();
        break;
    case CharacterType::WARRIOR:
        return make_unique<Warrior>();
        break;
    case CharacterType::WIZARD:
        return make_unique<Wizard>();
        break;
    case CharacterType::PALADIN:
        return make_unique<Paladin>();
        break;
    default:
        invalid_argument("Неизвестный тип персонажа");
        break;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Player* player = new Player();


    cout << "Привет, путник\nПрисядь у костра и расскажи о себе\nТы впервые тут?\n\t1 - новый персонаж,\n\t2 - загрузить\n";
    if (TestChoise(2, "Наверное ты ошибся, повтори снова"))
    {
        cout << "Расскажи о своих навыках\n\t1 - Воин\n\t2 - Волшебник\n\t3 - Паладин\n";
        unique_ptr<Npc> character;
        switch (TestChoise(3, "Такого еще не было в наших краях\nНе мог бы ты повторить"))
        {
            case 1:
                character = CreateCharacter(CharacterType::WARRIOR);
                break;
            case 2: 
                character = CreateCharacter(CharacterType::WIZARD);
                break;
            case 3: 
                character = CreateCharacter(CharacterType::PALADIN);
                break;
        }
        player->Create(move(character));
    }
    else
    {
        ifstream loadSystem("save.txt", ios::binary);
        if (!loadSystem.is_open())
        {
            cout << "Связь с космосом потеряна\nПамять о ваших прошлых путешествиях повреждена\n";
        }
        else
        {
            //реализация загрузки
        }
    }

    //процесс игры

    cout << "Перед вами развилочка, куда повернёте?" << endl;
    cout << "1 - Налево\n 2 - Направо" << endl;
    unsigned short choisee = TestChoise(2, "Вышел за рамки");
    Evil enemy = Evil("Нет");
    switch(choisee)
    {
        case 1:
            cout << "Вы повернули налево" << endl;
            break;
        case 2:
            enemy = Evil("Хрыч", 20, 15);
            cout << "Вы повернули направо" << endl;
            cout << player->GetCharacter()->GetHealth() << endl;
            cout << "На вас напал " << enemy.GetName() << endl;
            cout << "Вас ударил " << enemy.GetName() << endl;
            player->GetCharacter()->TakeDamage(enemy.GetDamage());
            cout << player->GetCharacter()->GetHealth() << endl;
            break;
    }
    if (enemy.GetName() != "Нет")
    {
        cout << "1 - Ударить в ответ\n 2 - Схавать яблочко(+10hp)\n" << endl;
  
        choisee = TestChoise(2, "Вышел за рамки");
        switch (choisee)
        {
        case 1:
            cout << "Вы дали сдачи" << endl;
            enemy.TakeDamage(player->GetCharacter()->GetDamage());
            cout << "Вы нанесли" << enemy.GetName() << player->GetCharacter()->GetDamage() << "урона" << endl;
            break;
        case 2:
            cout << "Вы схавали яблочко" << endl;
            player->GetCharacter()->Health(10);
            cout << player->GetCharacter()->GetHealth();
            break;
        }
    }
    return 0;
}
