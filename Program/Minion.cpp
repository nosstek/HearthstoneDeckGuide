#include "stdafx.h"
#include "Minion.h"

std::map<int, Minion> Minion::s_AllMinions;

Minion::Minion()
{
}

Minion::Minion(int wid, std::string wname, int wattack, int wdurability, bool wwindfury)
{
	m_Id = wid;
	m_Name = wname;
	m_Attack = wattack;
	m_Durability = wdurability;
	m_Windfury = wwindfury;
}

Minion::Minion(int mid, int mcost, std::string mname, int mattack, int mdurability, MinionType mtype, int mspelldamage, bool mtaunt, bool mcharge, bool mwindfury, bool mshield, bool mstealth, Effect * wonattack, Effect * wondamage, Effect * wonheal, Effect * wonbattlecry, Effect * wondeathrattle)
{
}

Minion::~Minion()
{
}
