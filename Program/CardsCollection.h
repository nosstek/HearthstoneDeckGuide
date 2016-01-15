#pragma once

#include <map>
#include <vector>
#include <random>

class CardsCollection
{
public:
	std::map<int, int> m_Collection;

	std::mt19937_64 m_RandomMachine;

public:
	CardsCollection();
	virtual ~CardsCollection();

	bool AddCard(int id, int quantity = 1);
	bool RemoveCard(int id, int quantity = 1);
	int GetRandomCard();

	int GetCardsCount();

	std::map<int, int> GetCollection() { return m_Collection; }

	std::string toString(bool with_cards_details = false) const;
};

enum DeckClass
{
	druid = 1,
	hunter,
	mage,
	paladin,
	priest,
	rogue,
	shaman,
	warlock,
	warrior,
};

class Deck : public CardsCollection
{
public:
	static std::map<int, Deck> s_AllDecks;

	int m_Id;
	std::string m_Name;
	float m_WinRate;
	DeckClass m_Class;
public:

	Deck() { m_Collection.clear(); }
	Deck(int deck_id, std::string name, float win_rate, DeckClass dclass);
	Deck(CardsCollection cc) { m_Collection = cc.m_Collection; }
	~Deck() {}

	std::string toString() const;
};