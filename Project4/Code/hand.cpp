//
// Created by 大泽 on 2017/7/14.
//

#include "hand.h"
Hand::Hand() {
    curValue.count=0;
    curValue.soft=0;
}

void Hand::discardAll(){
    curValue.count=0;
    curValue.soft=false;
}

void Hand::addCard(Card c) {
    int addnum=0;
//    bool isAceExisted=false;
    if (c.spot==TWO) addnum=2;
    else if (c.spot== THREE) addnum=3;
    else if (c.spot== FOUR) addnum =4;
    else if (c.spot == FIVE) addnum=5;
    else if (c.spot== SIX) addnum=6;
    else if (c.spot==SEVEN) addnum=7;
    else if (c.spot == EIGHT) addnum =8;
    else if (c.spot == NINE) addnum =9;
    else if (c.spot == TEN || c.spot == JACK || c.spot == QUEEN || c.spot == KING) addnum=10;
    else if (c.spot==ACE) {
//        isAceExisted=true;
        if (curValue.soft ){
            addnum=1;
        }
        else {
            if (curValue.count + 11 <= 21) {
                addnum = 11;
                curValue.soft = true;
            } else {
                addnum = 1;
                curValue.soft = false;
            }
        }
    }
    int newcount=curValue.count+addnum;
    if (newcount>21 && curValue.soft){
        curValue.soft=false;
        curValue.count=newcount-10;
    }
    else curValue.count=curValue.count+addnum;

}

HandValue Hand::handValue() const {
    return curValue;
}
