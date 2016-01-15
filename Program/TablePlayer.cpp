#include "stdafx.h"
#include "TablePlayer.h"

#include <string>

using namespace std;

TablePlayer::TablePlayer(Deck player_deck)
{
	m_Deck = player_deck;
}

void TablePlayer::initialize()
{
	m_ActionPoints = 0;

	m_Health = 30;
	m_Armor = 0;

	m_Weapon = 0;

	m_Class = m_Deck.m_Class;
	m_SpecialAbility = (int)m_Class;
	m_UsedAbility = false;
	m_TimesUsedAbility = 0;

	m_NextFatigueDamage = 1;
}

string TablePlayer::toString()
{
	string s = "HP: " + to_string(m_Health) + (m_Armor ? ("\tAR: " + to_string(m_Armor)) : "") + (m_Weapon ? ("\tWpn: " + to_string(m_Weapon)) : "") + "\tAP: " + to_string(m_ActionPoints) + "\n";
	return s;
}

TablePlayer::TablePlayer()
{
}