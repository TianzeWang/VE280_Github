//
// Created by 大泽 on 2017/7/24.
//
//#pragma once
#include "dlist.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct ComplexNum {
    int real;
    int imag;
};

class ErrorAns {
//    string a="error answer";
};

class NotEnough {
//    string b="not enough argument";
};

void PrintAll(Dlist<ComplexNum> &dlist);

void RemoveAll(Dlist<ComplexNum> &dlist);

void Print(Dlist<ComplexNum> &dlist);

void Reverse(Dlist<ComplexNum> &dlist);

void Duplicate(Dlist<ComplexNum> &dlist);

void Negate(Dlist<ComplexNum> &dlist);

void Multiply(Dlist<ComplexNum> &dlist);

void Substract(Dlist<ComplexNum> &dlist);

void Plus(Dlist<ComplexNum> &dlist);

void AddtoList(const string &str, Dlist<ComplexNum> &dlist);

void PrintAll(Dlist<ComplexNum> &dlist) {

    Dlist<ComplexNum> dlist_b;
    dlist_b = dlist;
    while (!dlist_b.isEmpty()) {
//        Print(*dlist_b);
        ComplexNum *a = dlist_b.removeFront();
        if (a->imag >= 0) cout << a->real << "+" << a->imag << "i" << " ";
        else cout << a->real << a->imag << "i" << " ";
        delete a;
    }
    cout << endl;
}
//    if (!dlist_b->isEmpty()) {

//        ComplexNum *Original_Last = dlist.removeBack();
//        ComplexNum *temp;
//        if (dlist.isEmpty()) {
//            dlist.insertBack(Original_Last);
//            Print(dlist);
//        }
//        else {
//            dlist.insertBack(Original_Last);
//            temp=dlist.removeFront();
//            dlist.insertFront(temp);
//            while(temp != Original_Last){
//                Print(dlist);
//                temp=dlist.removeFront();
//                dlist.insertBack(temp);
//            }
//        }
//    }


void RemoveAll(Dlist<ComplexNum> &dlist) {
    while (!dlist.isEmpty()) {
        delete dlist.removeFront();
    }
}

void Print(Dlist<ComplexNum> &dlist) {
    NotEnough ne;
    if (dlist.isEmpty()) throw ne;
    ComplexNum *a = dlist.removeFront();
    if (a->imag >= 0) cout << a->real << "+" << a->imag << "i" ;
    else cout << a->real << a->imag << "i" ;
//    ComplexNum *b = new ComplexNum;
//    b->imag = a->imag;
//    b->real = a->real;
//    ComplexNum *b = new ComplexNum(*a);
    dlist.insertFront(a);
//    delete a;
}

void Reverse(Dlist<ComplexNum> &dlist) {
    NotEnough ne;
    if (dlist.isEmpty()) throw ne;
    ComplexNum *a = dlist.removeFront();// Need to check the number of elements here
    if (dlist.isEmpty()) {
        dlist.insertFront(a);
        throw ne;
    }

    ComplexNum *b = dlist.removeFront();
    ComplexNum *c = new ComplexNum;
    ComplexNum *d = new ComplexNum;
    c->real = a->real;
    c->imag = a->imag;
    d->real = b->real;
    d->imag = b->imag;
    dlist.insertFront(c);
    dlist.insertFront(d);
    delete a;
    delete b;
}

void Duplicate(Dlist<ComplexNum> &dlist) {
    NotEnough ne;
    if (dlist.isEmpty()) throw ne;
    ComplexNum *a = dlist.removeFront();
    ComplexNum *b = new ComplexNum;
    ComplexNum *c = new ComplexNum;
    b->real = a->real;
    b->imag = a->imag;
    c->real = a->real;
    c->imag = a->imag;
    dlist.insertFront(c);
    dlist.insertFront(b);
    delete a;
}

void Negate(Dlist<ComplexNum> &dlist) {
    NotEnough ne;
    if (dlist.isEmpty()) throw ne;
    ComplexNum *a = dlist.removeFront();
    ComplexNum *result = new ComplexNum;
    result->real = -a->real;
    result->imag = -a->imag;
    dlist.insertFront(result);
    delete a;
}

void Multiply(Dlist<ComplexNum> &dlist) {
    NotEnough ne;
    if (dlist.isEmpty()) throw ne;
    ComplexNum *a = dlist.removeFront();// Need to check the number of elements here
    if (dlist.isEmpty()) {
        dlist.insertFront(a);
        throw ne;
    }
    ComplexNum *b = dlist.removeFront();
    ComplexNum *result = new ComplexNum;
    result->real = b->real * a->real - b->imag * a->imag;
    result->imag = a->imag * b->real + a->real * b->imag;
    dlist.insertFront(result);
    delete a;
    delete b;
}

void Substract(Dlist<ComplexNum> &dlist) {
    NotEnough ne;
    if (dlist.isEmpty()) throw ne;
    ComplexNum *a = dlist.removeFront();// Need to check the number of elements here
    if (dlist.isEmpty()) {
        dlist.insertFront(a);
        throw ne;
    }
    ComplexNum *b = dlist.removeFront();
    ComplexNum *result = new ComplexNum;
    result->real = b->real - a->real;
    result->imag = b->imag - a->imag;
    dlist.insertFront(result);
    delete a;
    delete b;
}

void Plus(Dlist<ComplexNum> &dlist) {
    NotEnough ne;
    if (dlist.isEmpty()) throw ne;
    ComplexNum *a = dlist.removeFront();
    if (dlist.isEmpty()) {
        dlist.insertFront(a);
        throw ne;
    }
    ComplexNum *b = dlist.removeFront();
    ComplexNum *result = new ComplexNum;
    result->imag = a->imag + b->imag;
    result->real = a->real + b->real;
    dlist.insertFront(result);
    delete a;
    delete b;
}

void AddtoList(const string &str, Dlist<ComplexNum> &dlist) {
    ErrorAns Erroranswer;
    if (str.find('i') != str.length() - 1) throw Erroranswer;
    ComplexNum *newComplexnum = new ComplexNum;
    if ((str.find('+') == str.npos && str.find('-') == str.npos) || str.find('i') == str.npos) {
        delete newComplexnum;
        throw Erroranswer;
    }
    if (str.find('-') == 0) {
        if (str.find('+', 1) == str.npos && str.find('-', 1) == str.npos) {
            delete newComplexnum;
            throw Erroranswer;
        }
        if (str.find('+', 1) == str.npos) {
            int minus_pos = str.find('-', 1);
            int i;
            if (minus_pos<= 1){
                delete newComplexnum;
                throw Erroranswer;
            }
            if (str.length()-2 < minus_pos+1) {
                delete newComplexnum;
                throw Erroranswer;
            }
            for (i = 1; i < minus_pos; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    delete newComplexnum;
                    throw Erroranswer;
                }
            }
            for (i = minus_pos + 1; i < str.length() - 1; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    delete newComplexnum;
                    throw Erroranswer;
                }
            }
//                    if (strtol(str.substr(1,minus_pos-1))==ERANGE || strtol(str.substr(minus_pos+1))== ERANGE){
//                        throw Erroranswer;
//                    }
//            char *apple = const_cast<char *>(str.substr(1, minus_pos - 1).c_str());
//            char *pear = const_cast<char *>(str.substr(minus_pos + 1, str.length() - minus_pos - 2).c_str());
            newComplexnum->real = -atoi(str.substr(1, minus_pos - 1).c_str());
            newComplexnum->imag = -atoi(str.substr(minus_pos + 1, str.length() - minus_pos - 2).c_str());
        } else if (str.find('-', 1) == str.npos) {
            int plus_pos = str.find('+', 1);
            int i;
            if (plus_pos <= 1) {
                delete newComplexnum;
                throw Erroranswer;
            }
            if (str.length()-2 < plus_pos+1){
                delete newComplexnum;
                throw Erroranswer;
            }
            for (i = 1; i < plus_pos; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    delete newComplexnum;
                    throw Erroranswer;
                }
            }
            for (i = plus_pos + 1; i < str.length() - 1; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    delete newComplexnum;
                    throw Erroranswer;
                }
            }
//                    if (strtol(str.substr(1,plus_pos-1))==ERANGE || strtol(str.substr(plus_pos+1))== ERANGE){
//                        throw Erroranswer;
//                    }
//            char *apple = const_cast<char *>(str.substr(1, plus_pos - 1).c_str());
//            char *pear = const_cast<char *>(str.substr(plus_pos + 1, str.length() - plus_pos - 2).c_str());
            newComplexnum->real = -atoi(str.substr(1, plus_pos - 1).c_str());
            newComplexnum->imag = atoi(str.substr(plus_pos + 1, str.length() - plus_pos - 2).c_str());
        } else {
            delete newComplexnum;
            throw Erroranswer;
        }

    } else {
        if (str.find('+') == str.npos && str.find('-') == str.npos) {
            delete newComplexnum;
            throw Erroranswer;
        }

        if (str.find('+') == str.npos) {
            int minus_pos = str.find('-');
            int i;
            if (minus_pos<=0) {
                delete newComplexnum;
                throw Erroranswer;
            }
            if (str.length() -2 < minus_pos +1){
                delete newComplexnum;
                throw Erroranswer;
            }
            for (i = 0; i < minus_pos; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    delete newComplexnum;
                    throw Erroranswer;
                }
            }
            for (i = minus_pos + 1; i < str.length() - 1; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    delete newComplexnum;
                    throw Erroranswer;
                }
            }
//                    if (strtol(str.substr(1, minus_pos - 1)) == ERANGE || strtol(str.substr(minus_pos + 1)) == ERANGE) {
//                        throw Erroranswer;
//                    }
//            char *apple = const_cast<char *>(str.substr(0, minus_pos).c_str());
//            char *pear = const_cast<char *>(str.substr(minus_pos + 1, str.length() - minus_pos - 2).c_str());
            newComplexnum->real = atoi(str.substr(0, minus_pos).c_str());
            newComplexnum->imag = -atoi(str.substr(minus_pos + 1, str.length() - minus_pos - 2).c_str());
        } else if (str.find('-') == str.npos) {
            int plus_pos = str.find('+');
            int i;
            if (plus_pos==0){
                delete newComplexnum;
                throw Erroranswer;
            }
            for (i = 0; i < plus_pos; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    delete newComplexnum;
                    throw Erroranswer;
                }
            }
            if (str.length() -2 < plus_pos+1){
                delete newComplexnum;
                throw Erroranswer;
            }
            for (i = plus_pos + 1; i < str.length() - 1; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    delete newComplexnum;
                    throw Erroranswer;
                }
            }

//                    if (strtol(str.substr(1, plus_pos - 1)) == ERANGE || strtol(str.substr(plus_pos + 1)) == ERANGE) {
//                        throw Erroranswer;
//                    }
//            char *apple = const_cast<char *>(str.substr(0, plus_pos).c_str());
//            char *pear = const_cast<char *>(str.substr(plus_pos + 1, str.length() - plus_pos - 2).c_str());
            newComplexnum->real = atoi(str.substr(0, plus_pos).c_str());
            newComplexnum->imag = atoi(str.substr(plus_pos + 1, str.length() - plus_pos - 2).c_str());
        } else {
            delete newComplexnum;
            throw Erroranswer;
        }

    }

    dlist.insertFront(newComplexnum);
}

int main() {
    string str;
    Dlist<ComplexNum> All;
    while (1) {
        cin >> str;
        if (str == "q") {
            while (!All.isEmpty()) {
                delete All.removeFront();
            }
            break;
        }
        if (str == "a") {
            try {
                PrintAll(All);
            }
            catch (NotEnough) {
                cout << "Not enough operands\n";
            }
        } else if (str == "c") {
            try {
                RemoveAll(All);
            }
            catch (NotEnough) {
                cout << "Not enough operands\n";
            }
        } else if (str == "p") {
            try {
                Print(All);
                cout << endl;
            }
            catch (NotEnough) {
                cout << "Not enough operands\n";
            }

        } else if (str == "r") {
            try {
                Reverse(All);
            }
            catch (NotEnough) {
                cout << "Not enough operands\n";
            }
        } else if (str == "d") {
            try {
                Duplicate(All);
            }
            catch (NotEnough) {
                cout << "Not enough operands\n";
            }
        } else if (str == "n") {
            try {
                Negate(All);
            }
            catch (NotEnough) {
                cout << "Not enough operands\n";
            }
        } else if (str == "*") {
            try {
                Multiply(All);
            }
            catch (NotEnough) {
                cout << "Not enough operands\n";
            }
        } else if (str == "-") try{
                Substract(All);
            }
            catch (NotEnough){
                cout << "Not enough operands\n";
            }
        else if (str == "+") {
            try {
                Plus(All);
            }
            catch (NotEnough) {
                cout << "Not enough operands\n";
            }
        } else {
            try {
                AddtoList(str, All);
//                Print(All);
            }
            catch (ErrorAns) {
                cout << "Bad input\n";
            }
        }
    }
    return 0;
}