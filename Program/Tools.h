#pragma once

#include "CardsCollection.h"

class Tools
{
public:

	static int MoveCardFromCollectionToCollection(CardsCollection* from_collection, CardsCollection* to_collection, int card_id = -1);
	static Deck GetRandomDeckFromCollection(CardsCollection collection, DeckClass dclass = druid);

	Tools();
	~Tools();
};

