#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include "player.h"
#include "combination.h"
#include "setting.h"
#define GAME_TIME 10
class Engine
{
public:
    Engine(GameConfig config);
    std::vector<Player*> &getPlayers() {return players;}
    QPixmap &getCardImage(Card card) {if(card.rank == -1) return cardImages.at(card.suit).at(0); return cardImages.at(card.suit).at(card.rank);}
    Player* getCurrentPlayer() {return players.at(currentPlayerIndex);}
    Player* getWinner();
    void newRound();
    size_t getCurrentPlayerIndex() {return currentPlayerIndex;}
    int tick();
    int getCountDown() {return countDown;}
    void addPlayed(Combination* selected);
    void nextPlayer();
    void forcePlay();
    void finish();
    bool isFinished();
    Combination getLastCombination() {return lastCombination;}
private:
    std::vector<Player*> players;
    size_t currentPlayerIndex;
    int countDown;
    bool finished;
    CombinationType currentCombination;
    GameConfig _config;
    std::vector<std::vector<QPixmap>> cardImages;
    Combination lastCombination;
    QMediaPlayer mediaPlayer;
    void deal();
};

#endif // ENGINE_H
