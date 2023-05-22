#include "engine.h"
#include <algorithm>
#include <random>

Engine::Engine(GameConfig config) : _config(config), lastCombination(START)
{
    // init players
    for(unsigned int i = 0; i < config.player_count; i++) {
        Player* player;
        QString icon = QString(":/images/Dataset/Image/p%1.png").arg(i+1);
        if(i < config.computer_count) {
            player = new Computer(icon, "Computer " + QString::number(i));
        } else {
            player = new Player(icon, "Player " + QString::number(i));
        }
        players.push_back(player);
    }
    finished = true;
    newRound();
}


void Engine::newRound()
{
    currentCombination = SINGLE;
    if(_config.swap_mode)
        lastCombination.setType(SWAP);
    else
        lastCombination.setType(START);
    lastCombination.getCards()->clear();
    deal();
    countDown = GAME_TIME;
    for(Player*player:players)
        player->setPassed(false);
    finished = false;
}

Player* Engine::getWinner()
{
    for(Player* player: players)
        if(player->getCards().empty())
            return player;
    return nullptr;
}


int Engine::tick()
{
    countDown--;
    if(countDown == 0) {
        forcePlay();
        return 0;
    }
    return countDown;
}

bool Engine::isFinished()
{
    for(Player * player:players)
        if(player->getCards().empty()) {
            finished = true;
            return true;
        }
    return finished;
}

void Engine::finish()
{
    int score = 0;
    for(Player *player:players)
    {
        int count = 0;
        int scale = 1;
        for(Card &card : player->getCards())
        {
            count += 1;
            if(card.suit == 3)
                scale = 2;
        }
        count *= scale;
        score += count;
    }
    getWinner()->addScore(score);
}

void Engine::nextPlayer()
{
    if(isFinished()) {
        finish();
        return;
    }
    countDown = GAME_TIME;
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    size_t passedCount = 1;
    for(size_t i = 0; i < players.size(); i++)
        if(i != currentPlayerIndex && players.at(i)->isPassed())
            passedCount ++;
    if(passedCount == players.size()) {
        for(size_t i = 0; i < players.size(); i++)
            players.at(i)->setPassed(0);
        lastCombination.setType(EMPTY);
    }

    if(lastCombination.getType() == SWAP)
    {
        bool done = true;
        for(Player * player : players)
            if(player->getSwapCards().empty())
                done = false;
        if(done)
        {
            if(_config.swap_mode == 1) {
                for(size_t i = 0; i < players.size(); i++)
                    for(Card &c :  players.at(i)->getSwapCards())
                        players.at((i + players.size() - 1) % players.size())->addCard(c);
            } else {
                std::vector<Card> cards;
                for(size_t i = 0; i < players.size(); i++)
                    for(Card &c :  players.at(i)->getSwapCards())
                        cards.push_back(c);
                std::random_device rd;
                std::mt19937 rng(rd());
                std::shuffle(cards.begin(), cards.end(), rng);
                size_t i = 0;
                int currentPlayer = 0;
                while(i < cards.size())
                {
                    players.at(currentPlayer++)->addCard(cards.at(i++));
                    currentPlayer %= _config.player_count;
                }
            }
            lastCombination.setType(START);
            for(size_t i = 0; i < players.size(); i++)
                for(Card &c :  players.at(i)->getCards())
                    if(c.suit == 0 && c.rank == 2)
                        currentPlayerIndex = i;
        }
    }



    getCurrentPlayer()->updateCombination(lastCombination);
}

void Engine::forcePlay()
{
    std::vector<Combination> &playerCombination= getCurrentPlayer()->getCombinations();
    if(playerCombination.at(0).getType() == SWAP)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(getCurrentPlayer()->getCards().begin(), getCurrentPlayer()->getCards().end(), rng);

        size_t size = playerCombination.at(0).getCards()->size();
        playerCombination.at(0).getCards()->clear();
        for(size_t i = 0; i < size; i++)
            playerCombination.at(0).getCards()->push_back({getCurrentPlayer()->getCards().at(i), 0});

    }
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, playerCombination.size() - 1);
    int randomIndex = dist(rng);
    addPlayed(&playerCombination.at(randomIndex));
}

QString getSoundEffect(Combination* selected)
{
    if(selected->getType() == PAIR)
        return "422";
    if(selected->getType() == STRAIGHT)
        return "424";
    if(selected->getType() == HOUSE)
        return "425";
    if(selected->getType() == FOUR)
        return "426";
    if(selected->getType() == STRAIGHTFLUSH)
        return "427";
    if(selected->getType() == PASS)
        return "43";
    if(selected->getType() == SWAP)
        return "";

    return "41" + QString::number(selected->getCards()->at(0).first.suit) + QString::number(selected->getCards()->at(0).first.rank + 1).rightJustified(2, '0');
}

void Engine::addPlayed(Combination* selected)
{
    std::vector<Card> &playerCards= getCurrentPlayer()->getCards();
    for(std::pair<Card, int> c : *selected->getCards()) {
        bool found = false;
        playerCards.erase(std::remove_if(playerCards.begin(), playerCards.end(), [&](const Card& card) {
                              if (found)
                                  return false;
                              bool result = card.rank == c.first.rank && card.suit == c.first.suit;
                              if(result)
                                found = true;
                              return result;
                   }), playerCards.end());
    }
    if(selected->getType() == PASS)
        getCurrentPlayer()->setPassed(1);
    else if(selected->getType() == SWAP) {
        for(auto &c : *selected->getCards())
            getCurrentPlayer()->getSwapCards().push_back(c.first);
    } else
        lastCombination = *selected;
    QString filename = "qrc:/music/Dataset/Sound/r" + QString::number(getCurrentPlayerIndex() + 1) + "_" + getSoundEffect(selected) + ".mp3";
    mediaPlayer.setMedia(QUrl(filename));
    mediaPlayer.play();
    nextPlayer();
}

QString getCardFileName(Card card)
{
    QString file = ":/images/Dataset/Image/";
    file += RANK_MAP[card.rank];
    file += "_of_";
    file += SUIT_MAP[card.suit];
    file += ".png";

    return file;
}


void Engine::deal() {
    std::vector<Card> deck;
    for(int i = 0; i < 4; i++) {
        cardImages.push_back(std::vector<QPixmap>());
        for (int j = 0; j < 13; j++) {
            Card card;
            card.suit = i;
            card.rank = j;
            deck.push_back(card);
            QPixmap cardImage(getCardFileName(card));  // Load the card image
            cardImages.at(i).push_back(cardImage);
        }
    }
    if (_config.joker_mode) {
        Card card;
        card.suit = 4;
        card.rank = -1;
        deck.push_back(card);
        deck.push_back(card);
        QPixmap cardImage(":/images/Dataset/Image/red_joker");  // Load the card image
        cardImages.push_back(std::vector<QPixmap>());
        cardImages.at(cardImages.size() - 1).push_back(cardImage);
        cardImages.at(cardImages.size() - 1).push_back(cardImage);
    }
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(deck.begin(), deck.end(), rng);
    for(Player * player: players)
        player->newGame();
    size_t i = 0;
    int currentPlayer = 0;
    while(i < deck.size())
    {
        if(deck.at(i).suit == 0 && deck.at(i).rank == 2)
            currentPlayerIndex = currentPlayer;
        players.at(currentPlayer++)->addCard(deck.at(i++));
        currentPlayer %= _config.player_count;
    }
    players.at(currentPlayerIndex)->updateCombination(lastCombination);
}

