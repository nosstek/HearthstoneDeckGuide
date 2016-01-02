#pragma once

#include <string>
#include <map>

#include "Effect.h"

class Weapon
{
public:
	static std::map<int,Weapon> s_AllWeapons;

	int m_Id;
	std::string m_Name;
	int m_Attack;
	int m_Durability;
	bool m_Windfury;
	Effect* m_OnAttack;
	Effect* m_OnBattlecry;
	Effect* m_OnDeathrattle;
public:
	Weapon();
	Weapon(int wid, std::string wname, int wattack, int wdurability, bool wwindfury);
	Weapon(int wid, std::string wname, int wattack, int wdurability, bool wwindfury, Effect* wonattack, Effect* wonbattlecry, Effect* wondeathrattle);
	~Weapon();

	std::string toString() const;
};

