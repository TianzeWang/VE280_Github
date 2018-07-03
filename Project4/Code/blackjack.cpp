#include "hand.h"
#include "player.h"
#include "card.h"
#include "deck.h"
#include "rand.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cassert>
using namespace std;
//void CountingPlayerFunction(int bankRoll, int minBet, int playHands);
//void SimplePlayerFunction(int bankRoll, int minBet, int playHands);
//void CountingPlayerwithShuffle(int bankRoll, int minBet, int playHands);
//void SimplePlayerwithShuffle(int bankRoll, int minBet, int playHands);
int main(int argc, char* argv[]){
    int bankroll=atoi(argv[1]);
    int minbet=atoi(argv[2]);
    int playhands=atoi(argv[3]);
    string playertype=argv[4];
    Deck adeck;
    Hand Dealerhand, Playerhand;
    Player *player;
    if (playertype == "simple"){
        player=get_Simple();
    }
    else player = get_Counting();
    //shuffle the deck
    if (argc==5) {
        int j;
        //shuffle the deck
        cout << "# Shuffling the deck\n";
        for (j = 0; j < 7; j++) {
            int cut=get_cut();
            adeck.shuffle(cut);
            cout << "cut at " << cut << endl;
        }
    }
    else{
        ifstream iFile;
        iFile.open(argv[5]);
        string line;
        stringstream iString;
        getline(iFile,line);
        iString << line;
        int current_Cut;
        cout << "# Shuffling the deck\n";
        while(!iString.eof()){
            iString >> current_Cut;
            adeck.shuffle(current_Cut);
            cout << "cut at " << current_Cut << endl;
        }
//        iString.clear();
//        iFile.close();
    }

    int thishand = 1;
    player->shuffled();
        while (playhands >= thishand&&minbet <= bankroll) {
            int i;
            cout << "# Hand " << thishand << " bankroll " << bankroll << endl;
            if (adeck.cardsLeft() < 20) {
                player->shuffled();
                adeck.reset();
                cout << "# Shuffling the deck\n";
                for (i = 0; i < 7; i++) {
                    int cut = get_cut();
                    adeck.shuffle(cut);
                    cout << "cut at " << cut << endl;
                }
            }
            Playerhand.discardAll();
            Dealerhand.discardAll();
            //Bet Operation
            int wager = player->bet(bankroll, minbet);
            cout << "# Player bets " << player->bet(bankroll, minbet) << endl;
            bankroll = bankroll - player->bet(bankroll, minbet);
            //Deal Four Cards
            Card a = adeck.deal();
            Card b = adeck.deal();
            Card c = adeck.deal();
            Card d = adeck.deal();
            cout << "Player dealt " << SpotNames[a.spot] << " of " << SuitNames[a.suit] << endl;
            cout << "Dealer dealt " << SpotNames[b.spot] << " of " << SuitNames[b.suit] << endl;
            cout << "Player dealt " << SpotNames[c.spot] << " of " << SuitNames[c.suit] << endl;
            player->expose(a);
            player->expose(b);
            player->expose(c);
            Playerhand.addCard(a);
            Playerhand.addCard(c);
            Dealerhand.addCard(b);
            Dealerhand.addCard(d);
            if (Playerhand.handValue().count == 21) {
                bankroll = (unsigned int) (bankroll + 2.5 * wager);
                cout << "# Player dealt natural 21\n";
//            continue;
            } else {
                while (player->draw(b, Playerhand) && Playerhand.handValue().count <= 21) {
                    Card newDraw = adeck.deal();
                    cout << "Player dealt " << SpotNames[newDraw.spot] << " of " << SuitNames[newDraw.suit] << endl;
                    Playerhand.addCard(newDraw);
                    player->expose(newDraw);
                }
                cout << "Player's total is " << Playerhand.handValue().count << endl;
                if (Playerhand.handValue().count > 21) {
                    cout << "# Player busts\n";
//                continue;
                } else {
                    player->expose(d);
                    cout << "Dealer's hole card is " << SpotNames[d.spot] << " of " << SuitNames[d.suit] << endl;
                    while (Dealerhand.handValue().count < 17) {
                        Card DealerDraw = adeck.deal();
                        player->expose(DealerDraw);
                        cout << "Dealer dealt " << SpotNames[DealerDraw.spot] << " of " << SuitNames[DealerDraw.suit] << endl;
                        Dealerhand.addCard(DealerDraw);
                    }
                    cout << "Dealer's total is " << Dealerhand.handValue().count << endl;
                    if (Dealerhand.handValue().count > 21) {
                        cout << "# Dealer busts\n";
                        bankroll = (unsigned int) (bankroll + 2 * wager);
//                    continue;
                    } else {//corresponding to the situation that neither bust
                        if (Dealerhand.handValue().count > Playerhand.handValue().count) {
                            cout << "# Dealer wins\n";
//                        continue;
                        } else if (Dealerhand.handValue().count < Playerhand.handValue().count) {
                            cout << "# Player wins\n";
                            bankroll = (unsigned int) (bankroll + 2 * wager);
//                        continue;
                        } else {
                            cout << "# Push\n";
                            bankroll = bankroll + wager;
                        }
                    }
                }
            }
            thishand++;
        }
    cout << "# Player has " << bankroll << " after " << thishand-1 << " hands\n";
//    delete *player;
}
//
//void CountingPlayerFunction(int bankRoll, int minBet, int playHands){
//    Deck adeck;
//    Hand Dealerhand, Playerhand;
//    CountingPlayer player;
//    int i;
//    for (i=0;i<7;i++){
//
//    }
//}
