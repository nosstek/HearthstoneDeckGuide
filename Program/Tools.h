#pragma once

#include "CardsCollection.h"

class Tools
{
public:

	static std::mt19937_64 m_RandomMachine;

	Tools() {}
	~Tools() {}

	static void initialize();

	static void ltf(const std::string &text);
	static void ClearLogFile();

	static int MoveCardFromCollectionToCollection(Collection* from_collection, Collection* to_collection, int card_id = -1);

	static std::pair<int, int> ReplaceCardsBetweenCollections(Collection* collection_first, Collection* collection_second, int card_id_first = -1, int card_id_second = -1);

	static Collection GetCommonPartOfTwoCollections(Collection collection_first, Collection collection_second);

	static Collection SubtractFromCollectionCollection(Collection collection_first, Collection collection_second);

	Collection SumCollectionWithCollection(Collection collection_first, Collection collection_second);

	static Deck GetRandomDeckFromCollection(Collection collection, DeckClass dclass = druid);

	static Collection GetRandomCollectionFromCollection(Collection collection, int collection_elements);

	static bool FlipTheCoin();
	static double GetRandomPercentage();
	static int GetRandomInteger(int from, int to);
	static int GetRandomInteger(int to) { return GetRandomInteger(0, to); }
	static void AddCoinToCollection(Collection* to_collection);


};

