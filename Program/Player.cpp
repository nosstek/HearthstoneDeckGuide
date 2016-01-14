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

Player::Player(int pid, std::string pname, CardsCollection pcollection)
{
	m_Id = pid;
	m_Name = pname;
	m_Collection = pcollection;
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

CardsCollection Player::GetDeck()
{
	std::map<int, std::string>::const_iterator it = m_Deck.begin();
	return Deck::s_AllDecks[it->first];
}
