# Big Two Game

## Introduction
Welcome to the Big Two Game! This project is a graphical user interface (GUI) implementation of the popular card game Big Two, also known as Deuces or Pusoy Dos using Qt and C++. The objective of the game is to be the first player to get rid of all your cards that requires you to place increasingly higher-ranked cards, and always of whatever number combination the round began with.

## How to Play
1. **Controls:** The game is played using the graphical user interface. You will interact with the game by clicking on buttons and cards using the mouse.

2. **Number of Players:** The game can be played with 2 to 4 players. Each player will be dealt a hand of cards.

3. **Special Game Mode:**
    - **Swap Card Mode:** Before the game starts, players have the opportunity to swap 2 cards from their initial hand. The card could be shuffled and randomly dealt to each player, or directly passes to the player on the right.
    - **Joker Cards:** In this game mode, joker cards are introduced. Joker cards can be used to represent any rank and suit of the player's choice except big two. They can be used to complete card combinations or as standalone cards. Joker pair is the biggest combination that can be played at any time.

4. **Gameplay:** The game follows the traditional rules of Big Two. The player with the 3 of Diamonds starts the first round, and the subsequent players must play a higher-ranked card or combination or pass their turn. The ranking of cards from highest to lowest is 2 > Joker > A > K > Q > J > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3.

5. **Card Combinations:** Players can play single cards, pairs, four-of-a-kind, straights, or flushes. Only higher-ranked combinations of the same type can be played on top of the previous player's move.

6. **Passing and Ending:** If a player cannot or chooses not to play a higher combination, they can pass their turn. If all players pass consecutively, a new round starts with the last player who made a valid move. The game ends when one player runs out of cards or when the deck is empty and no more valid moves can be made.

7. **Scoring:** At the end of each round, the winner of the round gets score equals to the sum of the number of the losers’ remaining cards. If a loser has at least one big two in the remaining hand, the winner can get double score from this loser.

8. **Winning the Game:** The first player to get 50 scores is winner.

## How to Compile
To compile the code using qmake, follow these steps:
1. Ensure that you have Qt installed and properly configured on your system, including the setup of qmake.
2. Open a terminal or command prompt.
3. Navigate to the directory containing the source code files.
4. Create a new folder named `build` and navigate to it.\
```mkdir build && cd build```
5. The folder structure will look like this:
    ```
    bigtwo
    ├── README.md
    ├── report.pdf
    ├── build
    ├── BigTwo
    │   ├── card.cpp
    │   ├── card.h
    │   ├── BigTwo.pro
    ...
    ```
6. Run the following command to generate the makefile:\
    ```qmake -o Makefile ../BigTwo/```
7. Run `make` to compile the code: \
    ```make``` \
This will create an executable file named `BigTwo`.

## Running the Executable
Once the code is compiled, you can run the game by executing the generated executable file, which is named `BigTwo`.

## Project Summary
In this project, we have implemented a graphical user interface (GUI) version of the Big Two card game using Qt framework. We have implemented **all basic** requirements and **all bonus** features, including:
- **Basic Requirements:**
    - GUI
        - Setting stage
            - Player number
            - Mode
            - Start game
            - Exit
        - Playing stage 
            - Play big two
            - Card that played last round
            - Show PASS
            - Sorted cards of yours
        - Scoring stage
            - List score of each player
            - Player getting 50 first is winner
        - Award stage
            - Display winner
        - Screen size
            - Width : 1080 
            - Height : 960
    - Poker cards
        - A total of 52 cards
        - 4 suits: Spades, Hearts, Diamonds, Clubs
        - 13 numbers: A, 2 to 10, J, Q, K
    - Game Rules 
        - Each player is dealt an equal number of cards, face down.
        - Begin the game by playing combination include the three of club.
        - Card are played in a counterclockwise direction.
        - The next player can either pass or follow the previous combination with higher-ranked.
        - If choosing to pass in this turn, you can’t play any card until this turn end. 
        - When the other three players all pass, the turn ends.
        - Once everyone besides you have passed, you can play new combination and start a new turn.
        - The first player who runs out of cards can get scores and a new round begin. 
        - Player who get 50 scores first is winner
    - Game Logic
        - The suits are ranked: Spades > Hearts > Diamonds > Clubs
        - The card numbers are ranked: 2 > A > K > Q > J > 10 > … > 3 
        - The priority of comparison: Numbers > Suits, E.g. Club 4 > Spade 3 
    - Card combinations
        - Single card
        - Pair
        - Straight
        - Full house
        - Four of a kind
        - Straight flush
    - Scoring method
        - Score equals to summation of the number of the losers’ remaining cards
        - If a loser has at least one big two in the remaining hand, the winner can get double score from this loser. 
- **Bonus Features:**
    - Sound effect
        - Backgound music
        - Button clicks
        - Playing cards
        - Winner effect
    - Player vs. Computer
    - The computer must play cards according to the rules mentioned earlier.
    - The total number of players(include computers) in the game can be set as 2~4.
    - Setting total number of players in setting stage.
    - Show hints for combinations that can be played from the hand.
    - If player doesn’t play any card within 10 seconds, then the system will automatically play a card.
        - Must play cards according to the rules mentioned earlier
    - Add joker cards (2 cards) into the game.
        - Joker card can be seen as any card except big two.
        - Joker pair is the biggest combination that can be played at any time.
        - Setting this mode in setting stage.
    - Swap card mode (choose mode in the setting stage)
        - In the begining of each round, each player chooses two cards and passes to the player on the right.
        - In the begining of each round, collect two cards from each player, shuffle those cards and deal to each player.
