#pragma once

#include "CardsCollection.h"
#include "Curve.h"
#include "Table.h"

#include <vector>

class DeckConstructor
{
public:
	static int s_EvaluationPrecision;
public:
	Collection m_PlayerCollection;
	Deck m_PlayerDeck;

	Curve m_OptimalCurve;

	Table m_Table;	
public:
	DeckConstructor() {}
	DeckConstructor(Collection player_collection);
	DeckConstructor(Collection player_collection, Deck player_deck);
	
	virtual ~DeckConstructor() {}

	virtual Deck FindOptimalDeck() { return m_PlayerDeck; };
	
	double EvaluationFunction(Deck &player_deck);
};

class GeneticDeckConstructor : public DeckConstructor
{
public:
	static int s_PopulationSize;
	static int s_GenerationsLimit;
	static double s_MutationChance;
	static double s_CrossoverChance;

	static int s_MutationLength;
	static int s_CrossoverLength;
public:
	std::vector<std::pair<double,DeckWithSupplement>> m_Population;

	GeneticDeckConstructor();
	GeneticDeckConstructor(const DeckConstructor dc);

	static DeckWithSupplement Mutation(DeckWithSupplement parent);
	static std::pair<DeckWithSupplement, DeckWithSupplement> Crossover(DeckWithSupplement mother, DeckWithSupplement father);

	Deck FindOptimalDeck() override;
	Deck GeneticAlghoritmForDeck();
};