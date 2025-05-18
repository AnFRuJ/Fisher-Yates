#ifndef SHUFFLER_H
#define SHUFFLER_H

#include<vector>
#include<random>
#include <ctime>
#include <algorithm>
#include <iostream>

class Shuffler {
    private:
        std::vector<int> deck;
        std::vector<int> hand;
        std::vector<int> discard;
        std::mt19937 rng;
    
    public:
        Shuffler();
        void shuffle(std::vector<int> x);
        std::vector<int> draw(int y);
        void dis(int selectedCard);
        std::vector<int> disAll(std::vector<int>& selectedCards);
        bool InHand(int card);
        void PrintDeck();
        void PrintHand();
        void PrintDiscard();
        bool DeckEmpty();
        bool HandEmpty();
        bool DiscardEmpty();
        int DeckRemaining();
        int HandRemaining();
        int DiscardRemaining();
        std::vector<int> ReturnDeck();
        std::vector<int> ReturnHand();
        std::vector<int> ReturnDiscard();
    };

#endif