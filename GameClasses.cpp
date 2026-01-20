#include "GameClasses.h"
#include <iostream>
#include <fstream>

using namespace std;

// Warrior implementation
Warrior::Warrior()
{
	name = "воин";
	health = 35;
	damage = 10;
}

Warrior::Warrior(std::string name, unsigned int health, float damage)
{
	cout << "кастомный конструктор война" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
}

void Warrior::GetWeapons()
{
	cout << name << " взял в руки " << weapons[lvl - 1];
}

void Warrior::GetInfo()
{
	Npc::GetInfo();
	cout << "Сила - " << strenght << endl;
	cout << "Доступное оружие - ";
	for (int i = 0; i < lvl; i++)
	{
		cout << weapons[i] << endl;
	}
}

void Warrior::Create()
{
	cout << "Вы создали война" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	GetInfo();
	GetWeapons();
}

bool Warrior::operator == (const Warrior& warrior) const
{
	return (warrior.damage == this->damage) &&
		(warrior.health == this->health) &&
		(warrior.strenght == this->strenght);
}

Warrior& Warrior::operator = (const Npc& npc)
{
	if (this != &npc)
	{
		this->name = npc.GetName();
		this->health = npc.GetHealth();
		this->damage = npc.GetDamage();
		this->lvl = npc.GetLvl();
		return *this;
	}
	return *this;
}

bool Warrior::Save()
{
	ofstream saveSystem("save.bin", ios::binary);
	if (saveSystem.is_open())
	{
		if (!Npc::Save())
		{
			cout << "Сохранение не удалось\nПопробуйте позже\n";
			return false;
		}

		saveSystem.write(reinterpret_cast<const char*>(&strenght), sizeof(strenght));
		saveSystem.close();
		return true;
	}
	else
	{
		cout << "Сохранение не удалось\nПопробуйте позже\n";
		return false;
	}
}

bool Warrior::Load()
{
	ifstream loadSystem("save.bin", ios::binary);
	if (loadSystem.is_open())
	{
		if (!Npc::Load())
		{
			cout << "Связь с небесами нарушена\nПамять о ваших прошлых путешествиях повреждена\n";
			return false;
		}
		loadSystem.read(reinterpret_cast<char*>(&strenght), sizeof(strenght));
		loadSystem.close();
		return true;
	}
	else
	{
		cout << "Связь с небесами нарушена\nПамять о ваших прошлых путешествиях повреждена\n";
		return false;
	}
}

Warrior::~Warrior()
{
	cout << name << " пал смертью храбрых" << endl;
}

// Wizard implementation
Wizard::Wizard()
{
	name = "волшебник";
	health = 245;
	damage = 15;
	// Инициализация заклинаний через вызов конструкторов
	spells[0] = Spell("огненный шар", 20, 50, false, 3);
	spells[1] = Spell("волшебные стрелы", 10, 30, false, 1);
	spells[2] = Spell("ледяной шок", 10, 20, false);
	spells[3] = Spell("возгорание", 10, 25, true, 5);
	spells[4] = Spell("проклятие", 5, 10, false, 10);
}

Wizard::Wizard(std::string name, unsigned int health, float damage)
{
	cout << "кастомный конструктор волшебника" << endl;
	this->name = name;
	this->health = health;
	this->damage = damage;
	// Инициализация заклинаний через вызов конструкторов
	spells[0] = Spell("огненный шар", 20, 50, false, 3);
	spells[1] = Spell("волшебные стрелы", 10, 30, false, 1);
	spells[2] = Spell("ледяной шок", 10, 20, false);
	spells[3] = Spell("возгорание", 10, 25, true, 5);
	spells[4] = Spell("проклятие", 5, 10, false, 10);
}

void Wizard::GetInfo()
{
	Npc::GetInfo();
	cout << "Интеллект - " << intellect << endl;
	cout << "Доступные заклинания в книге заклинаний - ";
	GetSpellsInfo();
}

void Wizard::GetSpellsInfo()
{
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << " заклинание:\n";
		for (int j = 0; j < 5; j++)
		{
			cout << spells[i][j] << endl;
		}
		cout << endl;
	}
}

void Wizard::Create()
{
	cout << "Вы создали волшебника" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	GetInfo();
}

Wizard Wizard::operator + (const Wizard& wizard) const
{
	return Wizard(
		this->name,
		(this->health + wizard.health),
		(this->damage + wizard.damage)
	);
}

bool Wizard::Save()
{
	ofstream saveSystem("save.bin", ios::binary);
	if (saveSystem.is_open())
	{
		if (!Npc::Save())
		{
			cout << "Сохранение не удалось\nПопробуйте позже\n";
			return false;
		}

		saveSystem.write(reinterpret_cast<const char*>(&intellect), sizeof(intellect));
		saveSystem.close();
		return true;
	}
	else
	{
		cout << "Сохранение не удалось\nПопробуйте позже\n";
		return false;
	}
}

Wizard::~Wizard()
{
	cout << name << " испустил дух" << endl;
}

// Wizard::Spell implementation
Wizard::Spell::Spell(std::string name, unsigned short damage, unsigned short price, bool isCurse, int timeCast)
{
	this->name = name;
	this->damage = damage;
	this->price = price;
	this->isCurse = isCurse;
	this->timeCast = timeCast;
}

std::string Wizard::Spell::operator[](unsigned index) const
{
	switch (index)
	{
	case 0: return "Название - " + name; break;
	case 1: return "Урон - " + std::to_string(damage); break;
	case 2: return "Стоимость применения - " + std::to_string(price) + " маны"; break;
	case 3:
	{
		if (isCurse)
		{
			return "периодичный урон";
		}
		else {
			return "произносимое заклинание";
		}
		break;
	}
	case 4:
		return isCurse ? "Длительность негативного эффекта - " + std::to_string(timeCast) :
			"Длительность применения - " + std::to_string(timeCast);
		break;
	default: return "такого свойства заклинания не существует"; break;
	}
}

unsigned short Wizard::Spell::CastSpell()
{
	cout << "Вы применили " << name << " на противнике" << endl;
	return damage;
}

// Paladin implementation
Paladin::Paladin()
{
	name = "паладин";
	health = 25;
	damage = 12;
	strenght = 27;
	// Инициализация заклинаний для паладина (так как он наследует от Wizard)
	spells[0] = Spell("огненный шар", 20, 50, false, 3);
	spells[1] = Spell("волшебные стрелы", 10, 30, false, 1);
	spells[2] = Spell("ледяной шок", 10, 20, false);
	spells[3] = Spell("возгорание", 10, 25, true, 5);
	spells[4] = Spell("проклятие", 5, 10, false, 10);
}

void Paladin::GetInfo()
{
	Warrior::GetInfo();
	cout << "Интеллект - " << intellect << endl;
	cout << "Доступные заклинания в книге заклинаний - ";
	GetSpellsInfo();
}

void Paladin::Create()
{
	cout << "Вы создали паладина" << endl;
	cout << "Введите имя персонажа\t";
	cin >> name;
	GetInfo();
	GetWeapons();
}

bool Paladin::Save()
{
	ofstream saveSystem("save.bin", ios::binary);
	if (saveSystem.is_open())
	{
		if (!Warrior::Save())
		{
			cout << "Сохранение не удалось\nПопробуйте позже\n";
			return false;
		}

		saveSystem.write(reinterpret_cast<const char*>(&intellect), sizeof(intellect));
		saveSystem.close();
		return true;
	}
	else
	{
		cout << "Сохранение не удалось\nПопробуйте позже\n";
		return false;
	}
}
