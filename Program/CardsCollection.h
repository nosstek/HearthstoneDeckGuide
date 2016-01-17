#pragma once

#include <map>
#include <random>
#include <list>

using namespace std;

class Collection
{
public:
	list<int> m_Collection;

public:
	Collection() { m_Collection.clear(); }
	~Collection() {}

	bool AddCard(int card_id);
	bool RemoveCard(int card_id);
	int GetRandomCard(bool remove_card = false);

	int GetCardQuantity(int card_id);
	int GetCardsCount() { return (int)m_Collection.size(); }

	bool AddCollection(Collection col, int number_of_elements = -1);
	bool RemoveCollection(Collection col, int number_of_elements = -1);
	
	void SortCollection() { m_Collection.sort(); }

	virtual string toString(bool with_cards_details = false) const;

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

class Deck : public Collection
{
public:
	static map<int, Deck> s_AllDecks;

public:
	int m_Id;
	string m_Name;
	DeckClass m_Class;
	int m_Wins;
	int m_Looses;

	Deck();
	Deck(const Collection collection);
	Deck(int deck_id, std::string name, DeckClass dclass, int wins = 0, int looses = 0);
	~Deck() {}

	double GetWinRatio() const;

	string toString(bool with_cards_details = false) const override;

};

class DeckWithSupplement
{
public:
	Deck m_Deck;
	Collection m_Supplement;
public:
	DeckWithSupplement() {};
	DeckWithSupplement(Collection player_deck, Collection player_collection, bool deck_already_substracted_from_collection = false);
	DeckWithSupplement(Deck player_deck, Collection player_collection, bool deck_already_substracted_from_collection = false);
	~DeckWithSupplement() {};

	bool AddCard(int id);
	bool RemoveCard(int id);

	void SortCollection() { m_Deck.SortCollection(); m_Supplement.SortCollection(); }

	string toString(bool with_cards_details = false) const;
};