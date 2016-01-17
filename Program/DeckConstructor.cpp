#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include "Tools.h"
#include "DeckConstructor.h"

#define TESTING_DECK_ID 107

int DeckConstructor::s_EvaluationPrecision = 10000; // Must be >= 1

int GeneticDeckConstructor::s_PopulationSize = 10; // Must be >= 1
int GeneticDeckConstructor::s_GenerationsLimit = 10;
double GeneticDeckConstructor::s_MutationChance = 0.3; // in a range (never) 0.0-1.0 (always)
double GeneticDeckConstructor::s_CrossoverChance = 0.3;  // in a range (never) 0.0-1.0 (always)
int GeneticDeckConstructor::s_MutationLength = 2;
int GeneticDeckConstructor::s_CrossoverLength = 2;

using namespace std;

bool pairCompare(const pair<double, DeckWithSupplement> &firstElem, const pair<double, DeckWithSupplement> &secondElem)
{
	return firstElem.first > secondElem.first;
}

DeckConstructor::DeckConstructor(Collection player_collection)
{
	m_PlayerCollection = player_collection;
	m_PlayerDeck = Tools::GetRandomDeckFromCollection(m_PlayerCollection);
	m_Table = Table();
}

DeckConstructor::DeckConstructor(Collection player_collection, Deck player_deck)
{
	m_PlayerCollection = player_collection;
	m_PlayerDeck = player_deck;
	m_Table = Table();
}

double DeckConstructor::EvaluationFunction(Deck &player_deck)
{
	Deck enemy_deck = Deck::s_AllDecks[TESTING_DECK_ID];

	if (LOOP_INFO) cout << "Player deck: " << endl << player_deck.Collection::toString(true) << endl;
	if (LOOP_INFO) cout << "Enemy deck: " << endl << enemy_deck.Collection::toString(true) << endl;

	for (int i = 0; i < s_EvaluationPrecision; ++i)
	{
		Table t = Table(player_deck, enemy_deck);

		bool result = t.PlayMatch();

		if (result)
			player_deck.m_Wins++;
		else
			player_deck.m_Looses++;

		if (LOOP_INFO) Tools::ltf(result ? "Player wins!" : "Player loose");
	}

	if (true) cout << player_deck.toString();

	return player_deck.GetWinRatio();
}

GeneticDeckConstructor::GeneticDeckConstructor()
{
}

GeneticDeckConstructor::GeneticDeckConstructor(DeckConstructor dc)
{
	m_PlayerCollection = dc.m_PlayerCollection;
	m_PlayerDeck = dc.m_PlayerDeck;
}

DeckWithSupplement GeneticDeckConstructor::Mutation(DeckWithSupplement parent)
{
	Collection removed = Tools::GetRandomCollectionFromCollection(parent.m_Deck, s_MutationLength);
	Collection added = Tools::GetRandomCollectionFromCollection(parent.m_Supplement, s_MutationLength);

	parent.m_Deck.RemoveCollection(removed);
	parent.m_Supplement.RemoveCollection(added);

	parent.m_Deck.AddCollection(added);
	parent.m_Supplement.AddCollection(removed);

	parent.m_Deck.m_Wins = 0;
	parent.m_Deck.m_Looses = 0;

	return parent;
}

pair<DeckWithSupplement, DeckWithSupplement> GeneticDeckConstructor::Crossover(DeckWithSupplement mother, DeckWithSupplement father)
{
	Collection first_with_star = Tools::GetCommonPartOfTwoCollections(mother.m_Supplement, father.m_Deck);
	Collection second_with_star = Tools::GetCommonPartOfTwoCollections(father.m_Supplement, mother.m_Deck);

	if (DEBUG_INFO)
	{
		cout << "Wspolna pierwszego suplementu i drugiej talii\n" << first_with_star.toString(true);
		cout << "Wspolna drugiego suplementu i fierwszej talii\n" << second_with_star.toString(true);
	}

	Collection first = Tools::SubtractFromCollectionCollection(first_with_star, second_with_star);
	Collection second = Tools::SubtractFromCollectionCollection(second_with_star, first_with_star);

	if (DEBUG_INFO)
	{
		cout << "Pierwsza bez drugiego\n" << first.toString(true);
		cout << "Druga bez pierwszego\n" << second.toString(true);
	}

	first = Tools::GetRandomCollectionFromCollection(first, s_CrossoverLength);
	second = Tools::GetRandomCollectionFromCollection(second, s_CrossoverLength);

	if (DEBUG_INFO)
	{
		cout << "Pierwsza bez drugiego po skroceniu\n" << first.toString(true);
		cout << "Druga bez pierwszego po skroceniu\n" << second.toString(true);
	}
	
	mother.m_Deck.RemoveCollection(second);
	mother.m_Supplement.AddCollection(second);
	mother.m_Supplement.RemoveCollection(first);
	mother.m_Deck.AddCollection(first);
	
	father.m_Deck.RemoveCollection(first);
	father.m_Supplement.AddCollection(first);
	father.m_Supplement.RemoveCollection(second);
	father.m_Deck.AddCollection(second);
	
	mother.m_Deck.m_Looses = 0;
	mother.m_Deck.m_Wins = 0;
	father.m_Deck.m_Looses = 0;
	father.m_Deck.m_Wins = 0;

	auto result = pair<DeckWithSupplement, DeckWithSupplement>(mother, father);

	return result;
}

Deck GeneticDeckConstructor::FindOptimalDeck()
{
	return GeneticAlghoritmForDeck();
}

Deck GeneticDeckConstructor::GeneticAlghoritmForDeck()
{
	if (DEBUG_INFO) { cout << "Getting random deck\n"; }

	DeckWithSupplement player_deck = DeckWithSupplement(m_PlayerDeck, m_PlayerCollection);
	auto p = pair<double, DeckWithSupplement>(EvaluationFunction(player_deck.m_Deck), player_deck);
	m_Population.push_back(p);

	for (int i = 0; i < s_PopulationSize - 1; ++i)
	{
		DeckWithSupplement random_deck = DeckWithSupplement(Tools::GetRandomDeckFromCollection(m_PlayerCollection), m_PlayerCollection);
		random_deck.SortCollection();
		auto p = pair<double, DeckWithSupplement>(EvaluationFunction(random_deck.m_Deck), random_deck);
		m_Population.push_back(p);

		sort(begin(m_Population), end(m_Population), pairCompare);
	}

	for (int generation = 0; generation < s_GenerationsLimit; ++generation)
	{
		for (int population_member = 0; population_member < s_PopulationSize; ++population_member)
		{
			if (DEBUG_INFO) { cout << "Population member: " << population_member << endl; }
			if (s_CrossoverChance > Tools::GetRandomPercentage())
			{
				if (DEBUG_INFO) { cout << "Crossover!" << population_member << endl; }
				int crossover_with = Tools::GetRandomInteger(s_PopulationSize);
				auto crossover_decks = Crossover(m_Population[population_member].second, m_Population[crossover_with].second);
				
				auto deck1 = pair<double, DeckWithSupplement>(EvaluationFunction(crossover_decks.first.m_Deck), crossover_decks.first);
				m_Population.push_back(deck1);

				auto deck2 = pair<double, DeckWithSupplement>(EvaluationFunction(crossover_decks.second.m_Deck), crossover_decks.second);
				m_Population.push_back(deck2);
			}

			if (s_MutationChance > Tools::GetRandomPercentage())
			{
				if (DEBUG_INFO) { cout << "Mutated!" << population_member << endl; }
				DeckWithSupplement mutated_deck = Mutation(m_Population[population_member].second);
				auto mu_deck = pair<double, DeckWithSupplement>(EvaluationFunction(mutated_deck.m_Deck), mutated_deck);
				m_Population.push_back(mu_deck);
			}
		}

// 		for (auto it = begin(m_Population); it != end(m_Population); ++it)
// 		{
// 			auto p = *it;
// 			p.first = EvaluationFunction(p.second.m_Deck);
// 		}

 		sort(begin(m_Population), end(m_Population), pairCompare);

		m_Population.resize(s_PopulationSize);
	}
	cout << endl << "Best deck:\n" << m_Population[0].second.m_Deck.toString(true) << endl;
	return m_Population[0].second.m_Deck;
}
