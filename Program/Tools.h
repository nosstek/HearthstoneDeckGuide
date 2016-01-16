#pragma once

#include "CardsCollection.h"

class Tools
{
public:
	static void initialize();

	static void ltf(const std::string &text);
	static void ClearLogFile();

	static int MoveCardFromCollectionToCollection(CardsCollection* from_collection, CardsCollection* to_collection, int card_id = -1);

	static std::pair<int, int> ReplaceCardsBetweenCollections(CardsCollection* collection_first, CardsCollection* collection_second, int card_id_first = -1, int card_id_second = -1);

	static CardsCollection GetCommonPartOfTwoCollections(CardsCollection collection_first, CardsCollection collection_second);

	static CardsCollection SubtractFromCollectionCollection(CardsCollection collection_first, CardsCollection collection_second);

	CardsCollection SumCollectionWithCollection(CardsCollection collection_first, CardsCollection collection_second);

	static Deck GetRandomDeckFromCollection(CardsCollection collection, DeckClass dclass = druid);

	static CardsCollection GetRandomCollectionFromCollection(CardsCollection collection, int collection_elements);

	static bool FlipTheCoin();
	static double GetRandomPercentage();
	static int GetRandomInteger(int from, int to);
	static int GetRandomInteger(int to) { return GetRandomInteger(0, to); }
	static void AddCoinToCollection(CardsCollection* to_collection);

	static std::mt19937_64 m_RandomMachine;

	Tools();
	~Tools();
};

