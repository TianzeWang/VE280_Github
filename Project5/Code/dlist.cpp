//
// Created by 大泽 on 2017/7/21.
//
//#pragma once
#include "dlist.h"
#include <cstdlib>
using namespace std;

template <class T>
bool Dlist<T>::isEmpty() const{
    return this->first == NULL && this->last == NULL;
}

template <class T>
void Dlist<T>::insertFront(T *op) {
    node *newnode= new node;
    newnode->op= op;
    if (this->isEmpty()) {
        this->first=newnode;
        this->last=newnode;
        this->first->next=NULL;
        this->last->next=NULL;
        this->first->prev=NULL;
        this->last->prev=NULL;
    }
    else {
        this->first->prev = newnode;
        newnode->next = this->first;
        newnode->prev = NULL;

        this->first = newnode;

        if (this->last->prev == NULL) {
            this->last->prev = this->first;
        } else {
            this->last->prev->next = this->last;
        }
    }
}

template <class T>
void Dlist<T>::insertBack(T *op) {
    node *newnode = new node;
    newnode->op = op;
    if (this->isEmpty()){
        this->first=newnode;
        this->last=newnode;
        this->first->next=NULL;
        this->last->next=NULL;
        this->first->prev=NULL;
        this->last->prev=NULL;
    }
    else {

        this->last->next = newnode;
        newnode->prev = this->last;
        newnode->next = NULL;

        this->last = newnode;

//        if (this->first->next == NULL){
//            this->first->next = this->last;
//        }
//        else {
//            this->first->next->prev = this->first;
//        }
    }
}

template <class T>
Dlist<T>::Dlist()  {
    this->first=this->last= NULL;
}

template <class T>
Dlist<T>::Dlist(const Dlist &l) {
    this->first=NULL;
    this->last=NULL;
    //this->removeAll();
    this->copyAll(l);
}

template <class T>
Dlist<T>::~Dlist() {
    this->removeAll();
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    this->removeAll();
    this->copyAll(l);
    return *this;
}

template <class T>
void Dlist<T>::removeAll() {
    while (!this->isEmpty()){
//        node * victim = this->first;
//        node * oldlast = this->last;
//        while(victim!=oldlast){
//            delete victim->op;
//            delete victim;
//            victim = victim->next;
//        }
//        delete victim->op;
//        delete victim;
        T * victim = removeFront();
        delete victim;
    }
    delete first;
    delete last;
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l) {
//
    removeAll();
    if (l.last != NULL) {
//        node *newnode = new node (*l.first);
        node *newnode = l.first;
        while(newnode != l.last){
            this->insertBack(new T (*newnode->op));
            newnode = newnode->next;
        }
        this->insertBack(new T (*newnode->op));
    }
}



template <class T>
T *Dlist<T>::removeFront() {
    if (this->isEmpty()) {
        throw emptyList();
    }
    else{
        node * oldfront = this->first;
        T * oldop= oldfront->op;
        if (this->first==this->last&& this->last!= NULL) {
            this->first=this->last=NULL;
        }
        else {
            this->first=oldfront->next;
            this->first->prev= NULL;
            this->first->next= oldfront->next->next;
        }

        delete oldfront;
        return oldop;
    }
}

template <class T>
T *Dlist<T>::removeBack() {
    if (this->isEmpty()) {
        throw emptyList();
    }
    else {
        node * oldback=this->last;
        T * oldop= this->last->op;
        if (this->first==this->last && this->last!= NULL ) {
            this->first = this->last= NULL;
        }
        else {
            this->last=oldback->prev;
            this->last->prev= oldback->prev->prev;
            this->last->next= NULL;
        }
        delete oldback;
        return oldop;
    }
}