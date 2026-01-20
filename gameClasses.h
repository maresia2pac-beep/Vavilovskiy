#pragma once
#include "BaseClasses.h"
#include <string>

class Warrior : public virtual Npc
{
protected:
	unsigned short strenght{ 31 };
	std::string weapons[4] = { "кастет", "дубинка", "клинок", "меч" };
public:
	Warrior();
	Warrior(std::string name, unsigned int health, float damage);
	void GetWeapons();
	void GetInfo() override;
	void Create() override;
	bool operator == (const Warrior& warrior) const;
	Warrior& operator = (const Npc& npc);
	bool Save() override;
	bool Load() override;
	~Warrior();
};

class Wizard : public virtual Npc
{
public:
	class Spell
	{
	protected:
		std::string name{ "заклинание" };
		unsigned short damage{ 0 };
		unsigned short price{ 0 };
		bool isCurse{ false };
		int timeCast{ 0 };
	public:
		Spell(std::string name = "заклинание", unsigned short damage = 0, unsigned short price = 0, bool isCurse = false, int timeCast = 0);
		std::string operator[](unsigned index) const;
		unsigned short CastSpell();
	};
protected:
	unsigned short intellect = 27;
	Spell spells[5]; // Объявляем массив заклинаний
public:
	Wizard();
	Wizard(std::string name, unsigned int health, float damage);
	void GetInfo() override;
	void Create() override;
	Wizard operator + (const Wizard& wizard) const;
	bool Save() override;
	void GetSpellsInfo();
	~Wizard();
};

class Paladin : public Warrior, public Wizard
{
public:
	Paladin();
	void GetInfo() override;
	void Create() override;
	bool Save() override;
};
