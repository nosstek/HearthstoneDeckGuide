#pragma once

#include <map>
#include <vector>
#include <random>

class CardsCollection
{
public:
	std::map<int, int> m_Collection;
public:
	CardsCollection() { m_Collection.clear(); }
	virtual ~CardsCollection() {}

	virtual bool AddCard(int id, int quantity = 1);
	virtual bool RemoveCard(int id, int quantity = 1);
	int GetRandomCard();

	int GetCardsCount();

	bool AddCollection(CardsCollection ccolection);
	bool RemoveCollection(CardsCollection ccolection);
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

public:
	int m_Id;
	std::string m_Name;
	DeckClass m_Class;

	int m_Wins;
	int m_Looses;

public:

	Deck() { m_Collection.clear(); }
	Deck(int deck_id, std::string name, DeckClass dclass, int wins = 0, int looses = 0);
	Deck(CardsCollection cc) { m_Collection = cc.m_Collection; }
	~Deck() {}

	double GetWinRatio() const;

	std::string toString() const;
};

class DeckWithSupplement : public Deck
{
public:
	CardsCollection m_Supplement;
public:
	DeckWithSupplement() {};
	DeckWithSupplement(CardsCollection player_deck, CardsCollection player_collection);
	DeckWithSupplement(Deck player_deck, CardsCollection deck_supplement);
	~DeckWithSupplement() {};

	bool AddCard(int id, int quantity = 1) override;
	bool RemoveCard(int id, int quantity = 1) override;
};