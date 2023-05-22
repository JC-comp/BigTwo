#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "card.h"
#include "combination.h"

class Player
{
public:
    Player(QString icon, QString name);
    void addCard(Card card);
    std::vector<Card>& getCards() {return cards;}
    std::vector<Card>& getSwapCards() {return toSwap;}
    std::vector<Combination>& getCombinations() {return combinations;}
    void removeCard(int idx);
    QString getIcon() {return _icon;}
    QString getName() {return _name;}
    virtual int isComputer(){return false;}
    void updateCombination(Combination table);
    bool hasCombination(std::vector<std::pair<Card, int>> &cards, Combination ** selecedCombination);
    bool isPassed() {return _passed;}
    void setPassed(bool passed) {_passed = passed;}
    int getScore() {return score;}
    void addScore(int point) {score += point;}
    void newGame();
private:
    std::vector<Card> cards;
    std::vector<Card> toSwap;
    std::vector<Combination> combinations;
    QString _icon, _name;
    int score;
    bool _passed;
};


class Computer: public Player
{
    using Player::Player;
public:
    virtual int isComputer(){return true;}
};


#endif // PLAYER_H
