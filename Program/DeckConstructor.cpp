#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include "Tools.h"
#include "DeckConstructor.h"

#define TESTING_DECK_ID 107

int DeckConstructor::m_EvaluationPrecision = 1;

int GeneticDeckConstructor::m_PopulationSize = 1;
int GeneticDeckConstructor::m_GenerationsLimit = 1;
double GeneticDeckConstructor::m_MutationChance = 0.3;
double GeneticDeckConstructor::m_CrossoverChance = 0.3;

int GeneticDeckConstructor::m_MutationLength = 2;
int GeneticDeckConstructor::m_CrossoverLength = 2;

using namespace std;

bool pairCompare(const std::pair<double, DeckWithSupplement> &firstElem, const std::pair<double, DeckWithSupplement> &secondElem)
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

	if (LOOP_INFO) std::cout << "Player deck: " << std::endl << player_deck.Collection::toString(true) << std::endl;
	if (LOOP_INFO) std::cout << "Enemy deck: " << std::endl << enemy_deck.Collection::toString(true) << std::endl;

	for (int i = 0; i < m_EvaluationPrecision; ++i)
	{
		Table t = Table(player_deck, enemy_deck);

		bool result = t.PlayMatch();

		if (result)
			player_deck.m_Wins++;
		else
			player_deck.m_Looses++;

		if (LOOP_INFO) Tools::ltf(result ? "Player wins!" : "Player loose");
	}

	if (true) std::cout << player_deck.toString();

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
	Collection removed = Tools::GetRandomCollectionFromCollection(parent.m_Deck, m_MutationLength);
	Collection added = Tools::GetRandomCollectionFromCollection(parent.m_Supplement, m_MutationLength);

	parent.m_Deck.RemoveCollection(removed);
	parent.m_Supplement.RemoveCollection(added);

	parent.m_Deck.AddCollection(added);
	parent.m_Supplement.AddCollection(removed);

	parent.m_Deck.m_Wins = 0;
	parent.m_Deck.m_Looses = 0;

	return parent;
}

std::pair<DeckWithSupplement, DeckWithSupplement> GeneticDeckConstructor::Crossover(DeckWithSupplement mother, DeckWithSupplement father)
{
	Collection first_with_star = Tools::GetCommonPartOfTwoCollections(mother.m_Supplement, father.m_Deck);
	Collection second_with_star = Tools::GetCommonPartOfTwoCollections(father.m_Supplement, mother.m_Deck);

	if (DEBUG_INFO)
	{
		std::cout << "Wspolna pierwszego suplementu i drugiej talii\n" << first_with_star.toString(true);
		std::cout << "Wspolna drugiego suplementu i fierwszej talii\n" << second_with_star.toString(true);
	}

	Collection first = Tools::SubtractFromCollectionCollection(first_with_star, second_with_star);
	Collection second = Tools::SubtractFromCollectionCollection(second_with_star, first_with_star);

	if (DEBUG_INFO)
	{
		std::cout << "Pierwsza bez drugiego\n" << first.toString(true);
		std::cout << "Druga bez pierwszego\n" << second.toString(true);
	}

	first = Tools::GetRandomCollectionFromCollection(first, m_CrossoverLength);
	second = Tools::GetRandomCollectionFromCollection(second, m_CrossoverLength);

	if (DEBUG_INFO)
	{
		std::cout << "Pierwsza bez drugiego po skroceniu\n" << first.toString(true);
		std::cout << "Druga bez pierwszego po skroceniu\n" << second.toString(true);
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

	auto result = std::pair<DeckWithSupplement, DeckWithSupplement>(mother, father);

	return result;
}

Deck GeneticDeckConstructor::FindOptimalDeck()
{
	return GeneticAlghoritmForDeck();
}

Deck GeneticDeckConstructor::GeneticAlghoritmForDeck()
{
	if (DEBUG_INFO) { std::cout << "Getting random deck\n"; }

// 	for (int i = 0; i < m_PopulationSize; ++i)
// 	{
		DeckWithSupplement random_deck = DeckWithSupplement(Tools::GetRandomDeckFromCollection(m_PlayerCollection), m_PlayerCollection);
		auto p = pair<double, DeckWithSupplement>(0.0, random_deck); //EvaluationFunction(random_deck.m_Deck), random_deck);
		m_Population.push_back(p);

		cout << random_deck.toString(true) << endl;

//		sort(m_Population.begin(), m_Population.end(), pairCompare);
// 	}
// 
// 	for (int generation = 0; generation < m_GenerationsLimit; ++generation)
// 	{
// 		for (int population_member = 0; population_member < m_PopulationSize; ++population_member)
// 		{
// 			if (DEBUG_INFO) { cout << "Population member: " << population_member << endl; }
// 			if (m_CrossoverChance > Tools::GetRandomPercentage())
// 			{
// 				if (DEBUG_INFO) { cout << "Crossover!" << population_member << endl; }
// 				int crossover_with = Tools::GetRandomInteger(0, m_PopulationSize);
// 				std::pair<DeckWithSupplement, DeckWithSupplement> crossover_decks = Crossover(m_Population[population_member].second, m_Population[crossover_with].second);
// 				std::pair<double, DeckWithSupplement> deck1 = std::pair<double, DeckWithSupplement>(EvaluationFunction(crossover_decks.first.m_Deck), crossover_decks.first);
// 				m_Population.push_back(deck1);
// 
// 				std::pair<double, DeckWithSupplement> deck2 = std::pair<double, DeckWithSupplement>(EvaluationFunction(crossover_decks.second.m_Deck), crossover_decks.second);
// 				m_Population.push_back(deck2);
// 			}
// 
// 			if (m_MutationChance > Tools::GetRandomPercentage())
// 			{
// 				if (DEBUG_INFO) { cout << "Mutated!" << population_member << endl; }
// 				DeckWithSupplement mutated_deck = Mutation(m_Population[population_member].second);
// 				std::pair<double, DeckWithSupplement> mu_deck = std::pair<double, DeckWithSupplement>(EvaluationFunction(mutated_deck.m_Deck), mutated_deck);
// 				m_Population.push_back(mu_deck);
// 			}
// 		}

// 		for (std::vector<std::pair<double, DeckWithSupplement>>::iterator it = m_Population.begin(); it != m_Population.end(); ++it)
// 		{
// 			std::pair<double, DeckWithSupplement> p = *it;
// 			p.first = EvaluationFunction(p.second.m_Deck);
// 		}
//		std::sort(m_Population.begin(), m_Population.end(), pairCompare);
//
//		m_Population.resize(m_PopulationSize);
//	}
	std::cout << std::endl << "Best deck:\n" << m_Population[0].second.m_Deck.toString() << std::endl << m_Population[0].second.m_Deck.Collection::toString(true) << std::endl;
	return m_Population[0].second.m_Deck;
}
