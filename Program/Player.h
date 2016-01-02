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
	CardsCollection m_Collection;
	CardsCollection m_Deck;
	CardsCollection m_ResultDeck;

public:
	Player();
	Player(int pid, std::string pname);
	Player(int pid, std::string pname, CardsCollection pcollection, CardsCollection pdeck);
	~Player();

	std::string toString(bool with_collection = false) const;

	CardsCollection GetCollection() { return m_Collection; }
	CardsCollection GetDeck() { return m_Deck; }
	void SetResultDeck(CardsCollection result) { m_ResultDeck = result; }
};

