#ifndef COMBINATION_H
#define COMBINATION_H

#include <vector>
#include "card.h"

enum CombinationType
{
    SINGLE,
    PAIR,
    STRAIGHT,
    HOUSE,
    FOUR,
    STRAIGHTFLUSH,
    EMPTY,
    SWAP,
    START,
    PASS,
    GHOSTPAIR
};

class Combination
{
public:
    Combination(CombinationType type):_type(type){};
    Combination(std::vector<std::pair<Card, int>> card, CombinationType type);
    CombinationType getType() {return _type;}
    void setType(CombinationType type) {_type = type;}
    std::vector<std::pair<Card, int>>* getCards() {return &_card;}
    bool larger(Combination rhs);
private:
    std::vector<std::pair<Card, int>> _card;
    CombinationType _type;
};

#endif // COMBINATION_H
