#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include "Tools.h"
#include "DeckConstructor.h"

#define TESTING_DECK_ID 107

bool pairCompare(const std::pair<double, DeckWithSupplement> &firstElem, const std::pair<double, DeckWithSupplement> &secondElem)
{
	return firstElem.first > secondElem.first;
}

DeckConstructor::DeckConstructor(CardsCollection player_collection)
{
	m_PlayerCollection = player_collection;
	m_PlayerDeck = Tools::GetRandomDeckFromCollection(m_PlayerCollection);
	m_Table = Table();
}

DeckConstructor::DeckConstructor(CardsCollection player_collection, Deck player_deck)
{
	m_PlayerCollection = player_collection;
	m_PlayerDeck = player_deck;
	m_Table = Table();
}

double DeckConstructor::EvaluationFunction(Deck &player_deck)
{
	Deck enemy_deck = Deck::s_AllDecks[TESTING_DECK_ID];

	if (LOOP_INFO) std::cout << "Player deck: " << std::endl << player_deck.CardsCollection::toString(true) << std::endl;
	if (LOOP_INFO) std::cout << "Enemy deck: " << std::endl << enemy_deck.CardsCollection::toString(true) << std::endl;

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

	if (LOOP_INFO) std::cout << player_deck.toString();

	return player_deck.GetWinRatio();
}

GeneticDeckConstructor::GeneticDeckConstructor()
{
	m_PopulationSize = 10;
	m_GenerationsLimit = 10;
	m_MutationChance = 0.3;
	m_CrossoverChance = 0.3;
}

GeneticDeckConstructor::GeneticDeckConstructor(DeckConstructor dc)
{
	m_PopulationSize = 10;
	m_GenerationsLimit = 10;
	m_MutationChance = 0.3;
	m_CrossoverChance = 0.3;

	m_PlayerCollection = dc.m_PlayerCollection;
	m_PlayerDeck = dc.m_PlayerDeck;
}

DeckWithSupplement GeneticDeckConstructor::Mutation(DeckWithSupplement parent)
{
	auto a = Tools::ReplaceCardsBetweenCollections(&parent, &parent.m_Supplement);
	std::cout << "Card from deck: " << a.first << " Card from collection: " << a.second << std::endl << parent.toString() << std::endl << parent.m_Supplement.toString();


	return parent;
}

std::pair<DeckWithSupplement, DeckWithSupplement> GeneticDeckConstructor::Crossover(DeckWithSupplement mother, DeckWithSupplement father)
{
	CardsCollection first_with_star = Tools::GetCommonPartOfTwoCollections(mother.m_Supplement, father);
	CardsCollection second_with_star = Tools::GetCommonPartOfTwoCollections(father.m_Supplement, mother);
	CardsCollection first = Tools::SubtractFromCollectionCollection(first_with_star, second_with_star);
	CardsCollection second = Tools::SubtractFromCollectionCollection(second_with_star, first_with_star);

	mother.RemoveCollection(second);
	mother.AddCollection(first);
	
	father.RemoveCollection(first);
	father.AddCollection(second);
	
	std::pair<DeckWithSupplement, DeckWithSupplement> result = std::pair<DeckWithSupplement, DeckWithSupplement>(mother, father);

	return result;
}

Deck GeneticDeckConstructor::FindOptimalDeck()
{
	return GeneticAlghoritmForDeck();
}

Deck GeneticDeckConstructor::GeneticAlghoritmForDeck()
{
	if (DEBUG_INFO) { std::cout << "Getting random deck\n"; }

	for (int i = 0; i < m_PopulationSize; ++i)
	{
		DeckWithSupplement random_deck = DeckWithSupplement(Tools::GetRandomDeckFromCollection(m_PlayerCollection), m_PlayerCollection);
		std::pair<double, DeckWithSupplement> p = std::pair<double, DeckWithSupplement>(EvaluationFunction(random_deck), random_deck);
		m_Population.push_back(p);

		std::sort(m_Population.begin(), m_Population.end(), pairCompare);
	}

	for (int generation = 0; generation < m_GenerationsLimit; ++generation)
	{
		for (int population_member = 0; population_member < m_PopulationSize; ++population_member)
		{
			if (m_CrossoverChance > Tools::GetRandomPercentage())
			{
				int crossover_with = Tools::GetRandomInteger(0, m_PopulationSize);
				std::pair<DeckWithSupplement, DeckWithSupplement> crossover_decks = Crossover(m_Population[population_member].second, m_Population[crossover_with].second);
				std::pair<double, DeckWithSupplement> deck1 = std::pair<double, DeckWithSupplement>(EvaluationFunction(crossover_decks.first), crossover_decks.first);
				m_Population.push_back(deck1);

				std::pair<double, DeckWithSupplement> deck2 = std::pair<double, DeckWithSupplement>(EvaluationFunction(crossover_decks.second), crossover_decks.second);
				m_Population.push_back(deck2);
			}

			if (m_MutationChance > Tools::GetRandomPercentage())
			{
				DeckWithSupplement mutated_deck = Mutation(m_Population[population_member].second);
				std::pair<double, DeckWithSupplement> mu_deck = std::pair<double, DeckWithSupplement>(EvaluationFunction(mutated_deck), mutated_deck);
				m_Population.push_back(mu_deck);
			}
		}

		for (std::vector<std::pair<double, DeckWithSupplement>>::iterator it = m_Population.begin(); it != m_Population.end(); ++it)
		{
			std::pair<double, DeckWithSupplement> p = *it;
			p.first = EvaluationFunction(p.second);
		}
		std::sort(m_Population.begin(), m_Population.end(), pairCompare);

		m_Population.resize(m_PopulationSize);
	}
	std::cout << std::endl << "Best deck:\n" << m_Population[0].second.toString() << std::endl << m_Population[0].second.CardsCollection::toString(true) << std::endl;
	return m_Population[0].second;
}
