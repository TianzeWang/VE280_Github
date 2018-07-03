#include "deck.h"
#include "card.h"
#include <iostream>
#include <cstdlib>

Deck::Deck() {
    int i;
    int j = 13;
    int n;
    next=0;
    for (n = 0; n < 4; n++) {
        for (i = n * j; i < n * j + 13; i++) {
            deck[i].spot = Spot(i-13*n);
            deck[i].suit = Suit(n);
        }
    }
}

void Deck::reset() {
    Deck();
}

void Deck::shuffle(int n) {
    next=0;
    Card newdeck[DeckSize];

    int i; //used in loop
    for (i=0;i<DeckSize;i++){
        newdeck[i]=deck[i];
    }
    if (n <= 26) {
        for (i = 0; i < n; i++) {
            deck[2*i] = newdeck[n + i];
            deck[2*i + 1] = newdeck[i];
        }
    } else {
        for (i = 0; i < 52 - n; i++) {
            deck[2*i] = newdeck[ n + i];
            deck[2*i + 1] = newdeck[i];
        }
        for (i = 0; i < 2*n-52; i++) {
            deck[(52-n)*2+i] = newdeck[i+52-n];
        }
    }
}

// Warning: Deal does not change the variable next here, should it change?
// May be could answer later
// Ans: Should change. And already changed.(next++)
Card Deck::deal() {
    DeckEmpty a;
    Card Currdeck=deck[next];
    next++;
    if (next <0 || next >=52) throw (a);
    else return Currdeck;
}

int Deck::cardsLeft() {
    return 52-next;
}



