#include "stdafx.h"
#include "Player.h"

std::map<int, Player> Player::s_AllPlayers;

Player::Player()
{
}

Player::Player(int pid, std::string pname)
{
	m_Id = pid;
	m_Name = pname;
}

Player::Player(int pid, std::string pname, CardsCollection pcollection, CardsCollection pdeck)
{
	m_Id = pid;
	m_Name = pname;
	m_Collection = pcollection;
	m_Deck = pdeck;
}

Player::~Player()
{
}

std::string Player::toString(bool with_collection) const
{
	std::string s = std::to_string(m_Id)  + "\t" + m_Name + "\n";
	if (with_collection)
		s += m_Collection.toString();
	return s;
}
