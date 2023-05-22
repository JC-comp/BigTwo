#include "play.h"
#include "button.h"
#include "cardpixmapitem.h"
#include <QTimer>

void Play::show(QGraphicsScene * scene, GameConfig config)
{
    winPlayer = nullptr;
    engine = new Engine(config);
    selecedCombination = nullptr;
    _scene = scene;
    update_screen();
    QTimer * timer = new QTimer();
    QObject::connect(timer,&QTimer::timeout,this,&Play::loop);
    timer->start(1000);
}

Play::~Play()
{
    if(winPlayer != nullptr)
        winPlayer->stop();
    delete engine;
}

void Play::newRound()
{
    engine->newRound();
    update_screen();
}

void Play::loop()
{
    if(engine->isFinished())
        return;
    int countDown = engine->tick();
    if(countDown == 0) {
        update_screen();
    }
    else {
        if(countDown <= (GAME_TIME - 2) && (engine->getCurrentPlayer()->isComputer() || engine->getCurrentPlayer()->isPassed())) {
            engine->forcePlay();
            update_screen();
        }
        else
            countDownText->setPlainText(QString::number(countDown));
    }
}

void Play::play()
{
    if(selecedCombination == nullptr)
        return;
    engine->addPlayed(selecedCombination);
    update_screen();
}

void Play::pass()
{
    if(engine->getLastCombination().getType() == START || engine->getLastCombination().getType() == EMPTY || engine->getLastCombination().getType() == SWAP)
        return;
    engine->addPlayed(&engine->getCurrentPlayer()->getCombinations().back());
    update_screen();
}


void Play::deSelectAll()
{
    for(CardPixmapItem *card : cardsToPlay)
        card->setSelected(0);
}

void Play::traverse(CombinationType type)
{
    if(engine->getLastCombination().getType() == SWAP)
        return;
    Player * player = engine->getCurrentPlayer();
    std::vector<Combination>& combinations = player->getCombinations();
    if(traverseType != type) {
        traverseCount = 0;
        traverseType = type;
    }
    int count = traverseCount++;
    deSelectAll();
    Combination* target = nullptr;
    int found = 0;
    for(Combination &combination : combinations)
        if(combination.getType() == type) {
            if(target == nullptr)
                target = &combination;
            if(count-- == 0)
            {
                target = &combination;
                found = 1;
                break;
            }
        }
    if(!found)
        traverseCount = 1;
    if(target != nullptr)
    {
        selecedCombination = target;
        for(auto card : *target->getCards())
            cardsToPlay.at(card.second)->setSelected(1);
        return;
    }
}

void Play::traversePair()
{
    traverse(PAIR);
}

void Play::traverseStraight()
{
    traverse(STRAIGHT);
}

void Play::traverseFull()
{
    traverse(HOUSE);
}

void Play::traverseFour()
{
    traverse(FOUR);
}

void Play::traverseFlush()
{
    traverse(STRAIGHTFLUSH);
}

void Play::cardClicked(CardPixmapItem * card, int clicked)
{
    selecedCombination = nullptr;
    std::vector<std::pair<Card, int>> cards;
    for (size_t i = 0; i < cardsToPlay.size(); i++)
    {
        CardPixmapItem *card = cardsToPlay.at(i);
        if(card->isSelected())
        {
            cards.push_back({card->getCard(), i});
        }
    }
    if(!engine->getCurrentPlayer()->hasCombination(cards, &selecedCombination) && clicked)
    {
        cards.clear();
        cards.push_back({card->getCard(), card->getPosition()});
        if(engine->getCurrentPlayer()->hasCombination(cards, &selecedCombination))
        {
            deSelectAll();
            card->setSelected(1);
        } else
            card->setSelected(0);
    }
}

void Play::update_screen()
{
    if(engine->isFinished()) {
        winner_screen();
        return;
    }
    int currnetPlayerIndex = engine->getCurrentPlayerIndex();
    selecedCombination = nullptr;
    _scene->clear();
    traverseCount = 0;
    countDownText= new QGraphicsTextItem(QString::number(engine->getCountDown()));
    countDownText->setFont(QFont("comic sans", 30));
    countDownText->setPos(10,850);
    countDownText->setDefaultTextColor(Qt::yellow);
    _scene->addItem(countDownText);


    if(engine->getLastCombination().getType() == SWAP)
    {
        QGraphicsTextItem* swapText = new QGraphicsTextItem("Choose 2 cards to swap");
        swapText->setFont(QFont("comic sans", 30));
        swapText->setPos(_game->width() / 2 - swapText->boundingRect().width() / 2, _game->height() / 2 - swapText->boundingRect().height() / 2);
        swapText->setDefaultTextColor(Qt::yellow);
        _scene->addItem(swapText);
    }

    std::vector<Player *> &players = engine->getPlayers();
    Player* player;

    unsigned int playerIndex = 0;
    int cardGap = 15;
    int desiredCardHeight = 100;
    int desiredIconHeight = 60;
    if(!players.at(currnetPlayerIndex)->isComputer() && !players.at(currnetPlayerIndex)->isPassed())
        playerIndex++;
    // players
    QPixmap hiddenCard(":/images/Dataset/Image/card_back.png");
    QFont cardFont("comic sans", 30);

    int rotationList[] = {0, 90, 0, 90};
    int startXList[] = {80, 80, _game->width() - 80 - 100, _game->width() - 80 - 100};
    int offsetXList[] = {100 ,100, -100, 100};
    int startYList[] = {730, 80, 80, 630};
    int offsetYList[] = {0, 150, 0, -100};
    int gapXList[] = {cardGap, 0, -cardGap, 0};
    int gapYList[] = {0, cardGap, 0, -cardGap};

    int startX, startY;
    for(; playerIndex < players.size(); playerIndex++) {
        player = players.at((currnetPlayerIndex + playerIndex) % players.size());
        startX = startXList[playerIndex];
        startY = startYList[playerIndex];

        QGraphicsTextItem* nameText = new QGraphicsTextItem(QString("%1 (%2)").arg(player->getName(), QString::number(player->getScore())));
        nameText->setPos(startX, startY - 25);
        nameText->setDefaultTextColor(Qt::yellow);
        _scene->addItem(nameText);

        QGraphicsPixmapItem* pIcon = new QGraphicsPixmapItem(QPixmap(player->getIcon()));
        qreal scaleFactor = static_cast<qreal>(desiredIconHeight) / pIcon->boundingRect().height();
        pIcon->setScale(scaleFactor);
        pIcon->setPos(startX, startY);
        _scene->addItem(pIcon);
        if (player->isPassed()){
            QGraphicsTextItem* passText = new QGraphicsTextItem("PASS");
            passText->setFont(QFont("comic sans", 15));
            passText->setPos(startX, startY + 60);
            passText->setDefaultTextColor(Qt::yellow);
            _scene->addItem(passText);
        }
        auto cards = player->getCards();
        startX += offsetXList[playerIndex];
        startY += offsetYList[playerIndex];
        for(unsigned int i = 0; i < cards.size(); i++)
        {
            QGraphicsPixmapItem* cardItem = new QGraphicsPixmapItem(hiddenCard);
            qreal scaleFactor = static_cast<qreal>(desiredCardHeight) / cardItem->boundingRect().height();
            cardItem->setScale(scaleFactor);
            cardItem->setRotation(rotationList[playerIndex]);
            cardItem->setPos(startX, startY);
            startX += gapXList[playerIndex];
            startY += gapYList[playerIndex];
            _scene->addItem(cardItem);
        }
        QGraphicsTextItem* cardLeft = new QGraphicsTextItem(QString::number(cards.size()));
        cardLeft->setFont(cardFont);
        cardLeft->setPos(startX,startY);
        cardLeft->setDefaultTextColor(Qt::yellow);
        _scene->addItem(cardLeft);
    }

    player = players.at(currnetPlayerIndex);
    cardsToPlay.clear();
    if(!players.at(currnetPlayerIndex)->isComputer() && !players.at(currnetPlayerIndex)->isPassed()) {
        std::vector<Card> &cards = player->getCards();

        int startX = 10 + (_game->width() - cardGap * cards.size() * players.size()) / 2;

        QGraphicsTextItem* nameText = new QGraphicsTextItem(QString("%1 (%2)").arg(player->getName(), QString::number(player->getScore())));
        nameText->setPos(startX - 100, 800 - 25);
        nameText->setDefaultTextColor(Qt::yellow);
        _scene->addItem(nameText);

        QGraphicsPixmapItem* pIcon = new QGraphicsPixmapItem(QPixmap(player->getIcon()));
        qreal scaleFactor = static_cast<qreal>(desiredIconHeight) / pIcon->boundingRect().height();
        pIcon->setScale(scaleFactor);
        pIcon->setPos(startX - 100, 800);

        _scene->addItem(pIcon);
        if (player->isPassed()){
            QGraphicsTextItem* passText = new QGraphicsTextItem("PASS");
            passText->setFont(QFont("comic sans", 15));
            passText->setPos(startX - 100, 80 + 600);
            passText->setDefaultTextColor(Qt::yellow);
            _scene->addItem(passText);
        }


        for(size_t i = 0; i < cards.size(); i++) {
            Card card = cards.at(i);
            CardPixmapItem* cardItem = new CardPixmapItem(engine->getCardImage(card), card, i);
            qreal scaleFactor = static_cast<qreal>(desiredCardHeight) / cardItem->boundingRect().height();
            cardItem->setScale(scaleFactor);
            cardsToPlay.push_back(cardItem);
        }
        size_t start_idx = 0;
        while (start_idx < cards.size() && cards.at(start_idx).rank < 2)
            start_idx++;

        for(size_t _i = 0; _i < cards.size(); _i++)
        {
            size_t i = (start_idx + _i) % cards.size();
            CardPixmapItem* cardItem = cardsToPlay.at(i);
            cardItem->setPos(startX, 800);
            _scene->addItem(cardItem);
            startX += cardGap * players.size();
            QObject::connect(cardItem,SIGNAL(clicked(CardPixmapItem*, int)),this,SLOT(cardClicked(CardPixmapItem*, int)));
        }


        Button* straightFlushButton = new Button(QString("Straight Flush"));
        int bxPos = 20;
        int byPos = _game->height() - 60;
        straightFlushButton->setPos(bxPos, byPos);

        Button* fourButton = new Button(QString("Four of a kind"));
        bxPos += 200;
        fourButton->setPos(bxPos, byPos);

        Button* houseButton = new Button(QString("Full house"));
        bxPos += 200;
        houseButton->setPos(bxPos, byPos);

        Button* straightButton = new Button(QString("Straight"));
        bxPos += 200;
        straightButton->setPos(bxPos, byPos);

        Button* pairButton = new Button(QString("Pair"));
        bxPos += 200;
        pairButton->setPos(bxPos, byPos);

        byPos = 730;
        bxPos = _game->width() - 500;
        Button* goButton = new Button(QString("Play"));
        goButton->setPos(bxPos, byPos);
        bxPos += 250;
        Button* passButton = new Button(QString("Pass"));
        passButton->setPos(bxPos, byPos);
        QObject::connect(passButton,SIGNAL(clicked()),this,SLOT(pass()));
        QObject::connect(goButton,SIGNAL(clicked()),this,SLOT(play()));

        QObject::connect(pairButton,SIGNAL(clicked()),this,SLOT(traversePair()));
        QObject::connect(straightButton,SIGNAL(clicked()),this,SLOT(traverseStraight()));
        QObject::connect(houseButton,SIGNAL(clicked()),this,SLOT(traverseFull()));
        QObject::connect(fourButton,SIGNAL(clicked()),this,SLOT(traverseFour()));
        QObject::connect(straightFlushButton,SIGNAL(clicked()),this,SLOT(traverseFlush()));


        _scene->addItem(straightFlushButton);
        _scene->addItem(fourButton);
        _scene->addItem(houseButton);
        _scene->addItem(straightButton);
        _scene->addItem(pairButton);
        _scene->addItem(passButton);
        _scene->addItem(goButton);

    }

    Combination combination = engine->getLastCombination();
    startX = _game->width() / 2 - 50 * combination.getCards()->size() / 2;
    for(auto card : *combination.getCards())
    {
        QGraphicsPixmapItem* cardItem = new QGraphicsPixmapItem(engine->getCardImage(card.first));
        qreal scaleFactor = static_cast<qreal>(desiredCardHeight) / cardItem->boundingRect().height();
        cardItem->setScale(scaleFactor);
        cardItem->setPos(startX, _game->height() / 2 - 50);
        _scene->addItem(cardItem);
        startX += 50;
    }
}

bool sortPlayer(Player *a, Player *b)
{
    return a->getScore() > b->getScore();
}

void Play::winner_screen()
{
    winPlayer = new QMediaPlayer;
    winPlayer->setMedia(QUrl("qrc:/music/Dataset/Sound/win.mp3"));
    winPlayer->play();
    _scene->clear();
    QGraphicsRectItem *overlay = new QGraphicsRectItem(_scene->sceneRect());
    overlay->setBrush(QBrush(QColor(0, 0, 0, 153)));
    _scene->addItem(overlay);
    QGraphicsTextItem* winnerText;
    if(engine->getWinner()->getScore() >= 50)
        winnerText = new QGraphicsTextItem("Winner is: " + engine->getWinner()->getName());
    else
        winnerText = new QGraphicsTextItem("Winner for this round: " + engine->getWinner()->getName());
    winnerText->setFont(QFont("comic sans", 30));
    winnerText->setPos(_game->width() / 2 - winnerText->boundingRect().width() / 2, 100);
    winnerText->setDefaultTextColor(Qt::white);
    _scene->addItem(winnerText);
    int byPos = 350;
    std::vector<Player*> sortedPlayers(engine->getPlayers());
    std::sort(sortedPlayers.begin(), sortedPlayers.end(), sortPlayer);

    for(Player * player : sortedPlayers)
    {
        Button* btn = new Button(player->getName() + ": " + QString::number(player->getScore()), Qt::darkBlue, Qt::blue);
        btn->setPos(_game->width() / 2 - btn->boundingRect().width() / 2, byPos);
        byPos += 70;
        _scene->addItem(btn);
    }
    byPos += 100;
    if(engine->getWinner()->getScore() >= 50) {
        Button* btn = new Button("Back to menu");
        btn->setPos(_game->width() / 2 - btn->boundingRect().width() / 2, byPos);
        QObject::connect(btn,SIGNAL(clicked()), _game,SLOT(displayMainMenu()));
        _scene->addItem(btn);
    } else{
        Button* btn = new Button("Next round");
        btn->setPos(_game->width() / 2 - btn->boundingRect().width() / 2, byPos);
        QObject::connect(btn,SIGNAL(clicked()), this,SLOT(newRound()));
        _scene->addItem(btn);
    }
}
