#pragma once

#include <map>
#include <vector>

struct SimpleCard
{
	int m_BaseCost;
	int m_Quantity;
	int m_Overload;
	int m_DrawCard;
	SimpleCard(int base_cost, int quantity, int overload, int draw_card) { m_BaseCost = base_cost; m_Quantity = quantity; m_Overload = overload; m_DrawCard = draw_card; }
};

class CardsCollection
{
public:
	std::map<int, int> m_Collection;
public:
	CardsCollection();
	virtual ~CardsCollection();

	bool AddCard(int id, int quantity = 1);
	bool RemoveCard(int id, int quantity = 1);

	std::map<int, int> GetCollection() { return m_Collection; }
	std::vector<SimpleCard> GetSimpleCollection();

	std::string toString() const;
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