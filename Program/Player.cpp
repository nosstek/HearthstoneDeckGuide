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

Player::Player(int pid, std::string pname, Collection collection)
{
	m_Id = pid;
	m_Name = pname;
	m_Collection = collection;
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

Deck Player::GetDeck()
{
	auto it = m_Deck.begin();
	return Deck::s_AllDecks[it->first];
}
