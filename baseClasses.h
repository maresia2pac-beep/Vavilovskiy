#pragma once
using namespace std;
#include <fstream> 
#include <iostream>

//базовый класс - абстрактный (класс у которого все методы виртуальные)
class Npc
{
protected: //модификатор 0 защищенный (дает доступ внутри класса родителя и наследника)
	//но все еще не дает доступ в основном потоке программы
	string name{ "персонаж" };
	unsigned int health{ 10 };
	float damage{ 5 };
	unsigned short lvl{ 1 };
public: //публичный модификатор доступ (использовать метод можно в любом месте)

	//геттер - когда можно получить информацию о поле, но только для чтения (нельзя перезаписать)
	string GetName() const
	{
		return name;
	}
	unsigned int GetHealth() const
	{
		return health;
	}
	float GetDamage() const
	{
		return damage;
	}
	unsigned short GetLvl() const
	{
		return lvl;
	}
	void TakeDamage(int damage)
	{
		health -= damage;
	}
	void Health(int hill)
	{
		hill += hill;
	}

	virtual void GetInfo() //метод класса
	{
		cout << "Имя - " << name << endl;
		cout << "Здоровье - " << health << endl;
		cout << "Урон - " << damage << endl;
	}
	virtual void Create() {};
	virtual bool Save() {
		ofstream saveSystem("save.bin", ios::binary);
		if (saveSystem.is_open())
		{
			size_t nameLength = name.length();
			saveSystem.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
			saveSystem.write(name.c_str(), nameLength);
			saveSystem.write(reinterpret_cast<const char*>(&health), sizeof(health));
			saveSystem.write(reinterpret_cast<const char*>(&damage), sizeof(damage));
			saveSystem.write(reinterpret_cast<const char*>(&lvl), sizeof(lvl));
			saveSystem.close();
			return true;
		}
		else
		{
			cout << "Сохранение не удалось\nПопробуйте позже\n";
			return false;
		}
	};
	virtual bool Load()
	{
		ifstream loadSystem("save.bin", ios::binary);
		if (loadSystem.is_open())
		{
			size_t nameLength;
			loadSystem.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
			char* buffer = new char[nameLength + 1];
			loadSystem.read(buffer, nameLength);
			buffer[nameLength] = '\0';
			name = string(buffer);
			delete[] buffer;

			loadSystem.read(reinterpret_cast<char*>(&health), sizeof(health));
			loadSystem.read(reinterpret_cast<char*>(&damage), sizeof(damage));
			loadSystem.read(reinterpret_cast<char*>(&lvl), sizeof(lvl));
			return loadSystem.good();
		}
		else
		{
			cout << "Связь с небесами нарушена\nПамять о ваших прошлых путешествиях повреждена\n";
			return false;
		}
		loadSystem.close();
	};

	virtual ~Npc() = default; //default - по умолчанию, чтобы не писать {} тело пустое
};

class Player
{
private:
	unique_ptr<Npc> currentCharacter{nullptr};
public:
	void Create(unique_ptr<Npc> player)
	{
		currentCharacter = move(player);
		currentCharacter->Create();
	}
	void Create()
	{
		if(currentCharacter != nullptr)
			currentCharacter->Create();
	}
	bool Save()
	{
		return currentCharacter ? currentCharacter->Save() : false;
	}
	bool Load(unique_ptr<Npc> player)
	{
		if (player->Load()) {
			currentCharacter = move(player);
			return true;
		}
		return false;
	}
	Npc* GetCharacter() {
		return currentCharacter.get();
	}
};
