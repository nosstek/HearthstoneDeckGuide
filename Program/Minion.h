#pragma once

#include <map>

#include "Weapon.h"

enum MinionType
{
	noneofit = 1,
	beast
};

class Minion : public Weapon
{
	int m_BaseCost;
	MinionType m_MinionType;
	int m_SpellDamage;
	bool m_Taunt;
	bool m_Charge;
	bool m_Shield;
	bool m_Stealth;
	Effect* m_OnDamage;
	Effect* m_OnHeal;
public:
	static std::map<int,Minion> s_AllMinions;

	Minion();
	Minion(int wid, std::string wname, int wattack, int wdurability, bool wwindfury);
	Minion(int mid, int mcost, std::string mname, int mattack, int mdurability, MinionType mtype,
		int mspelldamage, bool mtaunt, bool mcharge, bool mwindfury, bool mshield, bool mstealth,
		Effect* wonattack, Effect* wondamage, Effect* wonheal, Effect* wonbattlecry, Effect* wondeathrattle);
	~Minion();
};

