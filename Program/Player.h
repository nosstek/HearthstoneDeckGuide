#pragma once

#include <string>
#include <map>

#include "CardsCollection.h"


class Player
{
public:
	static std::map<int,Player> s_AllPlayers;

	int m_Id;
	std::string m_Name;
	Collection m_Collection;
	std::map<int, std::string> m_Deck;
	Deck m_ResultDeck;

public:
	Player();
	Player(int pid, std::string pname);
	Player(int pid, std::string pname, Collection collection);
	~Player();

	std::string toString(bool with_collection = false) const;

	Collection GetCollection() { return m_Collection; }
	Deck GetDeck();
	void SetResultDeck(Deck result) { m_ResultDeck = result; }
};

