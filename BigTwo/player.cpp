#include "player.h"
#include <QDebug>
Player::Player(QString icon, QString name): _icon(icon), _name(name), score(0), _passed(0)
{

}

bool compareCard(Card i1, Card i2)
{
    if(i1.rank == i2.rank)
        return (i1.suit < i2.suit);
    return (i1.rank < i2.rank);
}

void Player::addCard(Card card)
{
    cards.push_back(card);
    sort(cards.begin(), cards.end(), compareCard);
}

void Player::removeCard(int indexToRemove)
{
    cards.erase(cards.begin() + indexToRemove);
}

int isSingle(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() == 1)
        return true;
    return false;
}

int couldBeSingle(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() == 0)
        return true;
    return false;
}

int isPair(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() == 2) {
        if( test.at(0).first.rank == test.at(1).first.rank ) {
            if(test.at(0).first.suit == 4)
                return false;
            else
                return true;
        }
        else if(test.at(0).first.suit == 4 || test.at(1).first.suit == 4) {
            if(test.at(0).first.rank == 1 || test.at(1).first.rank == 1)
                return false;
            else
                return true;
        }
    }

    return false;
}

int couldBePair(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() == 1)
        return true;
    return false;
}

int isStraight(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() != 5)
        return 0;
    int spare = 0;
    for(size_t i = 0; i < test.size(); i++)
        if(test.at(i).first.suit == 4)
            spare++;
    for(size_t i = 0; i < test.size(); i++)
    {
        int spareLeft = spare;
        if(test.at(i).first.suit == 4)
            continue;
        int match = 10;
        bool valid = test.at(i).first.rank < match;
        while(spareLeft && !valid)
        {
            match++;
            valid = test.at(i).first.rank < match;
            spareLeft--;
        }
        int lastPos = i;
        size_t currentPos = (lastPos + 1) % test.size();
        while(currentPos != i && valid) {
            if(test.at(currentPos).first.suit == 4) {
                currentPos = (currentPos + 1) % test.size();
                continue;
            }
            match = 1;
            while(spareLeft && (test.at(currentPos).first.rank != ((test.at(lastPos).first.rank + match) % 13))) {
                if(((test.at(lastPos).first.rank + match) % 13) == 1)
                    break;
                spareLeft--;
                match++;
            }
            if(test.at(currentPos).first.rank != ((test.at(lastPos).first.rank + match) % 13))
                valid = 0;
            lastPos = currentPos;
            currentPos = (lastPos + 1) % test.size();
        }
        if (valid) {
            return 1;
        }
    }
    return 0;
}

int couldBeStraight(std::vector<std::pair<Card, int>>& test)
{
    int spare = 5 - test.size();
    for(size_t i = 0; i < test.size(); i++)
        if(test.at(i).first.suit == 4)
            spare++;
    for(size_t i = 0; i < test.size(); i++)
    {
        int spareLeft = spare;
        if(test.at(i).first.suit == 4)
            continue;
        int match = 11;
        bool valid = test.at(i).first.rank < match;
        while(spareLeft && !valid)
        {
            match++;
            valid = test.at(i).first.rank < match;
            spareLeft--;
        }
        int lastPos = i;
        size_t currentPos = (lastPos + 1) % test.size();
        while(currentPos != i && valid) {
            if(test.at(currentPos).first.suit == 4) {
                currentPos = (currentPos + 1) % test.size();
                continue;
            }
            int match = 1;
            while(spareLeft && (test.at(currentPos).first.rank != ((test.at(lastPos).first.rank + match) % 13))) {
                spareLeft--;
                match++;
            }
            if(test.at(currentPos).first.rank != ((test.at(lastPos).first.rank + match) % 13))
                valid = 0;
            lastPos = currentPos;
            currentPos = (lastPos + 1) % test.size();
        }
        if (valid)
            return 1;
    }
    return 0;
}

int isFullHouse(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() != 5)
        return 0;
    if(test.at(0).first.rank == test.at(1).first.rank && test.at(3).first.rank == test.at(4).first.rank)
        if(test.at(2).first.rank == test.at(1).first.rank || test.at(2).first.rank == test.at(3).first.rank)
            return 1;
    if(test.at(0).first.suit == 4 && test.at(1).first.suit != 4) {
        if(test.at(1).first.rank != test.at(4).first.rank) {
            if(test.at(2).first.rank == test.at(3).first.rank) {
                if(test.at(1).first.rank == test.at(2).first.rank && test.at(4).first.rank != 1)
                    return 1;
                if(test.at(3).first.rank == test.at(4).first.rank && test.at(1).first.rank != 1)
                    return 1;
            }
            if(test.at(1).first.rank == test.at(2).first.rank && test.at(3).first.rank == test.at(4).first.rank)
                return 1;
        }
    }
    if(test.at(1).first.suit == 4) {
        if(test.at(2).first.rank == test.at(4).first.rank && test.at(2).first.rank == test.at(3).first.rank)
            return 1;
        if(test.at(2).first.rank == test.at(3).first.rank || test.at(3).first.rank == test.at(4).first.rank)
            return 1;
    }

    return 0;
}

int couldBeFullHouse(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() < 3)
        return 1;
    int a = -5, b = -5;
    int countA = 0, countB = 0;
    for(size_t i = 0; i < test.size(); i++) {
        if(test.at(i).first.suit == 4)
            continue;
        if(a == -5) {
            a = test.at(i).first.rank;
            countA = 1;
        } else if (a == test.at(i).first.rank)
            countA++;
        else if(b == -5) {
            b = test.at(i).first.rank;
            countB = 1;
        } else if (b == test.at(i).first.rank)
            countB++;
        else
            return 0;
    }
    if(countA > 3 || countB > 3)
        return 0;
    return 1;
}

int couldBeFour(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() < 3)
        return 1;
    int a = -5, b = -5;
    int countA = 0, countB = 0;
    int ghostCount = 0;
    for(size_t i = 0; i < test.size(); i++) {
        if(test.at(i).first.suit == 4) {
            ghostCount++;
            continue;
        }
        if(a == -5) {
            a = test.at(i).first.rank;
            countA = 1;
        } else if (a == test.at(i).first.rank)
            countA++;
        else if(b == -5) {
            b = test.at(i).first.rank;
            countB = 1;
        } else if (b == test.at(i).first.rank)
            countB++;
        else
            return 0;
    }
    if(test.size() == 5 && ghostCount)
    {
        if(countA > 1 && a == 1) {
            if(countB > 0)
                return 0;
            else if(ghostCount > 1)
                return 0;
        }
        if(countB > 1 && b == 1) {
            if(countA > 0)
                return 0;
            else if(ghostCount > 1)
                return 0;
        }
    }
    return countA <= 1 || countB <= 1;
}

int isFour(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() != 5)
        return 0;
    return couldBeFour(test);
}

int isFlush(std::vector<std::pair<Card, int>>& test)
{
    if(isStraight(test))
    {
        int cmpIndex;
        for(size_t i = 0; i < test.size(); i++)
            if(test.at(i).first.suit != 4)
                cmpIndex = i;
        for(size_t i = 0; i < test.size(); i++)
            if((test.at(i).first.suit != test.at(cmpIndex).first.suit) && (test.at(i).first.suit != 4))
                return 0;
        return 1;
    }
    return 0;
}

int isGhostPair(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() == 2)
        return test.at(0).first.suit == test.at(1).first.suit && test.at(1).first.suit == 4;
    return false;
}

int couldBeGhostPair(std::vector<std::pair<Card, int>>& test)
{
    if(test.size() == 1 && test.at(0).first.rank == 4)
        return true;
    return false;
}

void checkAdd(CombinationType type, std::vector<std::pair<Card, int>>& test, std::vector<Combination>& combinations, Combination table)
{
    if(table.getType() == START) {
        for(std::pair<Card, int> &c: test)
            if(c.first.suit == 0 && c.first.rank == 2)
                combinations.push_back(Combination(test, type));
    } else
        if (Combination(test, type).larger(table))
            combinations.push_back(Combination(test, type));

}

void combination(size_t pos, std::vector<Card>& cards, std::vector<std::pair<Card, int>>& test, std::vector<Combination>& combinations, Combination table)
{
    if(test.size() > 5 || pos > cards.size())
        return;

    if(isSingle(test))
        checkAdd(SINGLE, test, combinations, table);
    if(isPair(test))
        checkAdd(PAIR, test, combinations, table);
    if(isStraight(test)) {
        if(isFlush(test))
            checkAdd(STRAIGHTFLUSH, test, combinations, table);
        else
            checkAdd(STRAIGHT, test, combinations, table);
    }
    if(isFullHouse(test))
        checkAdd(HOUSE, test, combinations, table);
    if(isFour(test))
        checkAdd(FOUR, test, combinations, table);
    if(isGhostPair(test))
        checkAdd(GHOSTPAIR, test, combinations, table);

    if(!couldBeSingle(test) && !couldBePair(test) && !couldBeStraight(test) && !couldBeFullHouse(test) && !couldBeFour(test))
        return;
    for(size_t i = pos; i < cards.size(); i++)
    {
        test.push_back({cards.at(i), i});
        combination(i + 1, cards, test, combinations, table);
        test.pop_back();
    }
}

void Player::updateCombination(Combination table)
{
    combinations.clear();
    if(table.getType() == SWAP) {
        combinations.push_back(Combination({std::pair(Card(), 0), std::pair(Card(), 0)}, SWAP));
        return;
    }
    if(isPassed()) {
        combinations.push_back(Combination({}, PASS));
        return;
    }
    std::vector<std::pair<Card, int>> test;
    combination(0, cards, test, combinations, table);
    if(table.getType() != START)
        combinations.push_back(Combination({}, PASS));
}

bool Player::hasCombination(std::vector<std::pair<Card, int>> &cards, Combination ** selecedCombination)
{
    bool found = false;
    bool matched = false;
    for(Combination &combination : combinations)
    {
        if(combination.getType() == SWAP) {
            if(cards.size() < combination.getCards()->size())
                return true;
            if(cards.size() == combination.getCards()->size()) {
                combination.getCards()->clear();
                combination.getCards()->insert(combination.getCards()->begin(), cards.begin(), cards.end());
                *selecedCombination = &combination;
                return true;
            }
        }

        std::vector<std::pair<Card, int>>* target = combination.getCards();
        size_t position = 0;
        for(size_t i = 0; i < target->size() && position < cards.size(); i++)
        {
            if(target->at(i).second == cards.at(position).second)
                position++;
            if(position == cards.size())
            {
                if(position == target->size()) {
                    if(!matched || *selecedCombination == nullptr || combination.larger(**selecedCombination)) {
                        *selecedCombination = &combination;
                        matched = true;
                    }
                }
                found = true;
            }
        }
    }
    return found;
}

void Player::newGame()
{
    setPassed(false);
    getCards().clear();
    getSwapCards().clear();
    getCombinations().clear();
}


