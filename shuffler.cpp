#include"shuffler.h"

Shuffler::Shuffler() {
    rng.seed(time(0)); // 初始化随机数生成器
}

void Shuffler::shuffle(std::vector<int> x) {
    hand.clear();
    discard.clear();

    // 初始化牌堆（编号从1到x）
    deck = x;

    // Fisher-Yates 洗牌算法
    for (int i = deck.size() - 1; i > 0; --i) {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(rng);
        std::swap(deck[i], deck[j]);
    }
}

std::vector<int> Shuffler::draw(int y) {
    //发牌
    if (y > deck.size()) {
        throw std::runtime_error("Not enough cards left to draw.");
    }
    std::vector<int> drawn(deck.begin(), deck.begin() + y);
    hand.insert(hand.end(), deck.begin(), deck.begin() + y);
    deck.erase(deck.begin(), deck.begin() + y);
    return drawn;
}

void Shuffler::dis(int selectedCard) {
    //出牌
    auto it = find(hand.begin(), hand.end(), selectedCard);
    discard.push_back(selectedCard);
    hand.erase(it);
    return;
}

std::vector<int> Shuffler::disAll(std::vector<int>& selectedCards) {
    //弃牌
    std::vector<int> discardedCards;
    for (int card : selectedCards) {
        auto it = find(hand.begin(), hand.end(), card);
        if (it != hand.end()) {
            discard.push_back(card);
            hand.erase(it);
            discardedCards.push_back(card);
        } else {
            std::cout << "Card " << card << " not found in hand!" << std::endl;
        }
    }
    return discardedCards;
}

bool Shuffler::InHand(int card) {
    return find(hand.begin(), hand.end(), card) != hand.end();
}

void Shuffler::PrintDeck() {
    std::cout << "The cards in the deck:" << std::endl;
    for (int card : deck) {
        std::cout << card << " ";
    }
    return;
}

void Shuffler::PrintHand() {
    std::cout << "The cards in your hand:" << std::endl;
    for(int card : hand) {
        std::cout << card << " ";
    }
    return;
}

void Shuffler::PrintDiscard() {
    std::cout << "The cards in the discard:" << std::endl;
    for(int card : discard) {
        std::cout << card << " ";
    }
    return;
}

bool Shuffler::DeckEmpty() {
    return deck.empty();
}

bool Shuffler::HandEmpty() {
    return hand.empty();
}

bool Shuffler::DiscardEmpty() {
    return discard.empty();
}

int Shuffler::DeckRemaining() {
    return deck.size();
}

int Shuffler::HandRemaining() {
    return hand.size();
}

int Shuffler::DiscardRemaining() {
    return discard.size();
}

std::vector<int> Shuffler::ReturnDeck() {
    return deck;
}

std::vector<int> Shuffler::ReturnHand() {
    return hand;
}

std::vector<int> Shuffler::ReturnDiscard() {
    return discard;
}