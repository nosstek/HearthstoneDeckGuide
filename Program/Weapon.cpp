#include "stdafx.h"
#include "Weapon.h"

std::map<int, Weapon> Weapon::s_AllWeapons;

Weapon::Weapon()
{
}

Weapon::Weapon(int wid, std::string wname, int wattack, int wdurability, bool wwindfury)
{
	m_Id = wid;
	m_Name = wname;
	m_Attack = wattack;
	m_Durability = wdurability;
	m_Windfury = wwindfury;
}

Weapon::Weapon(int wid, std::string wname, int wattack, int wdurability, bool wwindfury, Effect* wonattack, Effect* wonbattlecry, Effect* wondeathrattle)
{
	m_Id = wid;
	m_Name = wname;
	m_Attack = wattack;
	m_Durability = wdurability;
	m_Windfury = wwindfury;
	m_OnAttack = wonattack;
	m_OnBattlecry = wonbattlecry;
	m_OnDeathrattle = wondeathrattle;
}

Weapon::~Weapon()
{
}

std::string Weapon::toString() const
{
	std::string s = std::to_string(m_Id) + "\t" + m_Name + "\n";
	return s;
}