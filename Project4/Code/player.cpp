#include "player.h"

class SimplePlayer : public Player {
    virtual int bet(unsigned int bankroll, unsigned int minimum);

    bool draw(Card dealer, const Hand &player);

    virtual void expose(Card c){ }
    virtual void shuffled(){ }
//    ~Player() {}
};

class CountingPlayer : public SimplePlayer {
private:
    int count;
//    int bet(unsigned int bankroll,unsigned int minimum);
//    bool draw(Card dealer, const Hand &player);
public:
    int bet(unsigned int bankroll, unsigned int minimum);

    void expose(Card c);

    void shuffled();

//    ~Player() {}
};

int SimplePlayer::bet(unsigned int bankroll, unsigned int minimum) {
    if (bankroll >= minimum) {
        //finish here with minimum wager later
        return minimum;
    } else return 0;
}

bool SimplePlayer::draw(Card dealer, const Hand &player) {
    if (!player.handValue().soft) {
        if (player.handValue().count <= 11) return true;
        else if (player.handValue().count == 12) {
            if (dealer.spot != FOUR && dealer.spot != FIVE && dealer.spot != SIX) return true;
        } else if (player.handValue().count >= 13 && player.handValue().count <= 16) {
            if (dealer.spot != TWO && dealer.spot != THREE && dealer.spot != FOUR && dealer.spot != FIVE &&
                dealer.spot != SIX) {
                return true;
            }
            else return false;
        }
        else return false;
    } else {
        if (player.handValue().count <= 17) return true;
        else if (player.handValue().count == 18) {
            if (dealer.spot != TWO && dealer.spot != SEVEN && dealer.spot != EIGHT) return true;
        }
        else return false;
    }
    return false;
}

void CountingPlayer::expose(Card c) {
    if (c.spot == TEN || c.spot == JACK || c.spot == QUEEN || c.spot == KING || c.spot == ACE) {
        count=count-1;
    } else if (c.spot == TWO || c.spot == THREE || c.spot == FOUR || c.spot == FIVE || c.spot == SIX) {
        count=count+1;
    }
}

void CountingPlayer::shuffled() {
    count = 0;
}

int CountingPlayer::bet(unsigned int bankroll, unsigned int minimum) {
    if (bankroll >= minimum) {
        if (count >= 2) {
            if (bankroll >= 2 * minimum) return 2 * minimum;
        }
        else return minimum;
    }
    else return 0;
    return 0;
}// Already considered the case that not enough bankroll

extern Player *get_Simple() {
    return (Player *) new SimplePlayer;
}

extern Player *get_Counting() {
    return (Player *) new CountingPlayer;
}
