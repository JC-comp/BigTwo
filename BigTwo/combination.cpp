#include "combination.h"

Combination::Combination(std::vector<std::pair<Card, int>> card, CombinationType type)
    :_card(card), _type(type)
{

}

bool cmp(Card a, Card b)
{
    int rankA = a.rank;
    int rankB = b.rank;
    if(rankA == -1)
        a.rank = 0;
    if(rankB == -1)
        b.rank = 0;
    bool result;
    if((a.rank + 11) % 13 == (b.rank + 11) % 13 )
        result = a.suit > b.suit;
    else
        result = (a.rank + 11) % 13 > (b.rank + 11) % 13;
    a.rank = rankA;
    b.rank = rankB;
    return result;
}

Card getStraightCmp(std::vector<std::pair<Card, int>>* test)
{
    Card c;
    int spare = 0;
    for(size_t i = 0; i < test->size(); i++)
        if(test->at(i).first.suit == 4)
            spare++;
    for(size_t i = 0; i < test->size(); i++)
    {
        int spareLeft = spare;
        if(test->at(i).first.suit == 4)
            continue;
        int match = 10;
        bool valid = test->at(i).first.rank < match;
        while(spareLeft && !valid)
        {
            match++;
            valid = test->at(i).first.rank < match;
            spareLeft--;
        }
        c = test->at(i).first;
        size_t lastPos = i;
        size_t currentPos = (lastPos + 1) % test->size();
        while(currentPos != i && valid) {
            if(test->at(currentPos).first.suit == 4) {
                currentPos = (currentPos + 1) % test->size();
                c.suit = 4;
                c.rank = (c.rank + 1) % 13;
                continue;
            }
            match = 1;
            while(spareLeft && (test->at(currentPos).first.rank != ((test->at(lastPos).first.rank + match) % 13))) {
                if(((test->at(lastPos).first.rank + match) % 13) == 1)
                    break;
                spareLeft--;
                match++;
            }
            if(test->at(currentPos).first.rank != ((test->at(lastPos).first.rank + match) % 13))
                valid = 0;
            c = test->at(currentPos).first;
            lastPos = currentPos;
            currentPos = (lastPos + 1) % test->size();
        }
        if (valid) {
            return c;
        }
    }
    return c;
}

Card getFourCmp(std::vector<std::pair<Card, int>>* test)
{
    int a = -5, b = -5;
    int countA = 0, countB = 0;
    for(size_t i = 0; i < test->size(); i++) {
        if(test->at(i).first.suit == 4)
            continue;
        if(a == -5) {
            a = test->at(i).first.rank;
            countA = 1;
        } else if (a == test->at(i).first.rank)
            countA++;
        else if(b == -5) {
            b = test->at(i).first.rank;
            countB = 1;
        } else if (b == test->at(i).first.rank)
            countB++;
    }
    if(countA > countB)
        return {0, a};
    else if(countA == countB) {
        if(a > b)
            return {0, a};
        else
            return {0, b};
    } else
        return {0, b};
}

bool Combination::larger(Combination rhs)
{
    if(rhs.getType() == EMPTY)
        return true;
    if(_type == SINGLE) {
        if(rhs.getType() == SINGLE)
            return cmp(getCards()->at(0).first, rhs.getCards()->at(0).first);
        else
            return false;
    } else if(_type == PAIR) {
        if(rhs.getType() == PAIR) {
            for(size_t i = 0; i < getCards()->size(); i++) {
                bool isLarger = true;
                for(size_t j = 0; j < rhs.getCards()->size();j++)
                    if(!cmp(getCards()->at(i).first, rhs.getCards()->at(j).first))
                        isLarger = false;
                if(isLarger)
                    return true;
            }
            return false;
        }
        else
            return false;
    } else if(_type == STRAIGHT) {
        if(rhs.getType() == STRAIGHT)
            return cmp(getStraightCmp(getCards()), getStraightCmp(rhs.getCards()));
        else
            return false;
    } else if(_type == HOUSE) {
        if(rhs.getType() == HOUSE)
            return cmp(getFourCmp(getCards()), getFourCmp(rhs.getCards()));
        else
            return false;
    } else if(_type == FOUR) {
        if(rhs.getType() == STRAIGHTFLUSH || rhs.getType() == GHOSTPAIR)
            return false;
        if(rhs.getType() == FOUR)
            return cmp(getFourCmp(getCards()), getFourCmp(rhs.getCards()));
        else
            return true;
    }  else if(_type == STRAIGHTFLUSH) {
        if(rhs.getType() == STRAIGHTFLUSH)
            return cmp(getStraightCmp(getCards()), getStraightCmp(rhs.getCards()));
        else if (rhs.getType() == GHOSTPAIR)
            return false;
        else
            return true;
    } else if(_type == GHOSTPAIR)
        return true;

    return false;
}
