#pragma once

#include "CardsCollection.h"

class Tools
{
public:
	static void initialize();

	static void log(const std::string &text);
	static void ClearLogFile();

	static int MoveCardFromCollectionToCollection(CardsCollection* from_collection, CardsCollection* to_collection, int card_id = -1);
	static Deck GetRandomDeckFromCollection(CardsCollection collection, DeckClass dclass = druid);

	static bool FlipTheCoin();
	static void AddCoinToCollection(CardsCollection* to_collection);

	static std::mt19937_64 m_RandomMachine;

	Tools();
	~Tools();
};

