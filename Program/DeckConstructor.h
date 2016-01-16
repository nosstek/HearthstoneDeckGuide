#pragma once

#include "CardsCollection.h"
#include "Curve.h"
#include "Table.h"

#include <vector>

class DeckConstructor
{
public:
	CardsCollection m_PlayerCollection;
	Deck m_PlayerDeck;

	Curve m_OptimalCurve;

	Table m_Table;

	int m_EvaluationPrecision;
public:
	DeckConstructor() {}
	DeckConstructor(CardsCollection player_collection);
	DeckConstructor(CardsCollection player_collection, Deck player_deck);
	
	virtual ~DeckConstructor() {}

	virtual Deck FindOptimalDeck() { return m_PlayerDeck; };
	
	double EvaluationFunction(Deck &player_deck);
};

class GeneticDeckConstructor : public DeckConstructor
{
public:
	int m_PopulationSize;
	int m_GenerationsLimit;
	double m_MutationChance;
	double m_CrossoverChance;

	std::vector<std::pair<double,DeckWithSupplement>> m_Population;

	GeneticDeckConstructor();
	GeneticDeckConstructor(const DeckConstructor dc);

	static DeckWithSupplement Mutation(DeckWithSupplement parent);
	static std::pair<DeckWithSupplement, DeckWithSupplement> Crossover(DeckWithSupplement mother, DeckWithSupplement father);

	Deck FindOptimalDeck() override;
	Deck GeneticAlghoritmForDeck();
};