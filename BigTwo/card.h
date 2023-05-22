#ifndef CARD_H
#define CARD_H
#include <QString>

extern const QString SUIT_MAP[];
extern const QString RANK_MAP[];

struct Card {
    int suit;
    int rank;
};

#endif // CARD_H
