//
// Created by 王天泽 on 2017/7/26.
//

#include "dlist.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;
enum Status {regular,silver,gold,platinum};
const string Status_name[] = {"regular","silver","gold","platinum"};


struct Event{
    int timestamp;
    string name;
    Status status;
    int waiting;
    int duration;
    int answered_at_tick=-1;
    bool is_calling = false;
    bool is_answered = false;
};

int main(){
    int N;
    cin >> N;
    int i=1;
    int j;
    Dlist<Event> Platinum_Usr;
    Dlist<Event> Gold_Usr;
    Dlist<Event> Silver_Usr;
    Dlist<Event> Regular_Usr;
    Dlist<Event> All_Usr;
//Reading from cin
    while (i <= N){
        Event *a=new Event;
        string stt;
        cin >> a->timestamp >> a->name >> stt >> a->waiting >> a->duration;
        for (j=0;j<4;j++){
            if (Status_name[j] == stt ){
                a->status=Status(j);
            }
        }
        Event *b = new Event(*a);
        All_Usr.insertBack(b);
        if(a->status==regular){
            Regular_Usr.insertBack(a);
        }
        else if (a->status == silver) {
            Silver_Usr.insertBack(a);
        }
        else if (a->status == gold) {
            Gold_Usr.insertBack(a);
        }
        else {
            Platinum_Usr.insertBack(a);
        }
        i++;
    }

    int tick = 0;

    bool is_answering=false ;
    Dlist<Event> Platinum_Usr_temp;
    Dlist<Event> Gold_Usr_temp;
    Dlist<Event> Silver_Usr_temp;
    Dlist<Event> Regular_Usr_temp;
    Dlist<Event> All_Usr_temp;
    int Platinum_calling_count=0;
    int Gold_calling_count=0;
    int Silver_calling_count=0;
    int Regular_calling_count=0;


    while(!Platinum_Usr.isEmpty()|| !Gold_Usr.isEmpty()|| !Silver_Usr.isEmpty()|| !Regular_Usr.isEmpty()){

        cout << "Starting tick #" << tick << endl;
//Implementation of 被接电话的人Hang Up
        if (is_answering){
            while (!Platinum_Usr.isEmpty()) {
                Event *Platinum_temp = Platinum_Usr.removeFront();
                if (Platinum_temp->is_answered && Platinum_temp->duration + Platinum_temp->answered_at_tick == tick) {
                    is_answering = false;
                    delete Platinum_temp;
                    Platinum_calling_count--;
                } else {
                    Platinum_Usr_temp.insertBack(Platinum_temp);
                }
            }

            while (!Gold_Usr.isEmpty()) {
                Event *Gold_temp = Gold_Usr.removeFront();
                if (Gold_temp->is_answered && Gold_temp->duration + Gold_temp->answered_at_tick== tick) {
                    is_answering = false;
                    delete Gold_temp;
                    Gold_calling_count--;
                } else {
                    Gold_Usr_temp.insertBack(Gold_temp);
                }
            }

            while (!Silver_Usr.isEmpty()) {
                Event *Silver_temp = Silver_Usr.removeFront();
                if (Silver_temp->is_answered && Silver_temp->duration + Silver_temp->answered_at_tick == tick) {
                    is_answering = false;
                    delete Silver_temp;
                    Silver_calling_count--;
                } else {
                    Silver_Usr_temp.insertBack(Silver_temp);
                }
            }

            while (!Regular_Usr.isEmpty()) {
                Event *Regular_temp = Regular_Usr.removeFront();
                if (Regular_temp->is_answered && Regular_temp->duration + Regular_temp->answered_at_tick== tick) {
                    is_answering = false;
                    delete Regular_temp;
                    Regular_calling_count--;
                } else {
                    Regular_Usr_temp.insertBack(Regular_temp);
                }
            }
            Platinum_Usr=Platinum_Usr_temp;
            Gold_Usr=Gold_Usr_temp;
            Silver_Usr=Silver_Usr_temp;
            Regular_Usr=Regular_Usr_temp;
        }
//Reinitialize Usr_temp
        while(!Platinum_Usr_temp.isEmpty()){
            delete Platinum_Usr_temp.removeFront();
        }
        while(!Gold_Usr_temp.isEmpty()){
            delete Gold_Usr_temp.removeFront();
        }
        while(!Silver_Usr_temp.isEmpty()){
            delete Silver_Usr_temp.removeFront();
        }
        while(!Regular_Usr_temp.isEmpty()){
            delete Regular_Usr_temp.removeFront();
        }
//Implementation of 没有被接电话的人hang up

            while (!Platinum_Usr.isEmpty()){
                Event *Platinum_temp=Platinum_Usr.removeFront();
                if (!Platinum_temp->is_answered && Platinum_temp->is_calling && Platinum_temp->waiting+Platinum_temp->timestamp == tick) {
                    cout << Platinum_temp->name<< " hangs up" << endl;
                    Platinum_temp->is_calling=false;
                    delete Platinum_temp;
                    Platinum_calling_count--;
                }
                else {
                    Platinum_Usr_temp.insertBack(Platinum_temp);
                }
            }
            Platinum_Usr=Platinum_Usr_temp;

            while (!Gold_Usr.isEmpty()){
                Event *Gold_temp=Gold_Usr.removeFront();
                if (!Gold_temp->is_answered&& Gold_temp->is_calling && Gold_temp->waiting+Gold_temp->timestamp == tick) {
                    cout << Gold_temp->name<< " hangs up" << endl;
                    Gold_temp->is_calling=false;
                    delete Gold_temp;
                    Gold_calling_count--;
                }
                else {
                    Gold_Usr_temp.insertBack(Gold_temp);
                }
            }
            Gold_Usr=Gold_Usr_temp;

            while (!Silver_Usr.isEmpty()){
                Event *Silver_temp=Silver_Usr.removeFront();
                if (!Silver_temp->is_answered&& Silver_temp->is_calling && Silver_temp->waiting+Silver_temp->timestamp == tick) {
                    cout << Silver_temp->name<< " hangs up" << endl;
                    Silver_temp->is_calling=false;
                    delete Silver_temp;
                    Silver_calling_count--;
                }
                else {
                    Silver_Usr_temp.insertBack(Silver_temp);
                }
            }
            Silver_Usr=Silver_Usr_temp;

            while (!Regular_Usr.isEmpty()){
                Event *Regular_temp=Regular_Usr.removeFront();
                if (!Regular_temp->is_answered && Regular_temp->is_calling && Regular_temp->waiting+Regular_temp->timestamp == tick) {
                    cout << Regular_temp->name<< " hangs up" << endl;
                    Regular_temp->is_calling=false;
                    delete Regular_temp;
                    Regular_calling_count--;
                }
                else {
                    Regular_Usr_temp.insertBack(Regular_temp);
                }
            }
            Regular_Usr=Regular_Usr_temp;

//Reinitialize Usr_temp
        while(!Platinum_Usr_temp.isEmpty()){
            delete Platinum_Usr_temp.removeFront();
        }
        while(!Gold_Usr_temp.isEmpty()){
            delete Gold_Usr_temp.removeFront();
        }
        while(!Silver_Usr_temp.isEmpty()){
            delete Silver_Usr_temp.removeFront();
        }
        while(!Regular_Usr_temp.isEmpty()){
            delete Regular_Usr_temp.removeFront();
        }

//Implementation of Call from

        while (!All_Usr.isEmpty()){
            Event *All_temp= All_Usr.removeFront();
            if (All_temp->timestamp == tick){
                cout << "Call from " << All_temp->name<< " a "
                     << Status_name[All_temp->status] <<" member" << endl;
                delete All_temp;
            }
            else{
                All_Usr_temp.insertBack(All_temp);
            }
        }


        while (!Platinum_Usr.isEmpty()) {
            Event *Platinum_temp = Platinum_Usr.removeFront();
            if (Platinum_temp->timestamp == tick) {
                Platinum_temp->is_calling = true;
                Platinum_calling_count++;
                //                cout << "Call from " << Platinum_temp->name<< " a "
                //                     << Status_name[Platinum_temp->status] <<" member" << endl;
            }
            Platinum_Usr_temp.insertBack(Platinum_temp);
        }


        while (!Gold_Usr.isEmpty()){
            Event *Gold_temp=Gold_Usr.removeFront();
            if (Gold_temp->timestamp == tick) {
                Gold_temp->is_calling=true;
                Gold_calling_count++;
//                cout << "Call from " << Gold_temp->name<< " a " << Status_name[Gold_temp->status] <<" member" << endl;
            }
            Gold_Usr_temp.insertBack(Gold_temp);
        }

        while (!Silver_Usr.isEmpty()){
            Event *Silver_temp=Silver_Usr.removeFront();
            if (Silver_temp->timestamp == tick) {
                Silver_temp->is_calling=true;
                Silver_calling_count++;
//                cout << "Call from " << Silver_temp->name<< " a "
//                     << Status_name[Silver_temp->status] <<" member" << endl;
            }
            Silver_Usr_temp.insertBack(Silver_temp);
        }

        while (!Regular_Usr.isEmpty()){
            Event *Regular_temp=Regular_Usr.removeFront();
            if (Regular_temp->timestamp == tick) {
                Regular_temp->is_calling=true;
                Regular_calling_count++;
//                cout << "Call from " << Regular_temp->name<< " a "
//                     << Status_name[Regular_temp->status] <<" member" << endl;
            }
            Regular_Usr_temp.insertBack(Regular_temp);
        }
        Platinum_Usr=Platinum_Usr_temp;
        Gold_Usr=Gold_Usr_temp;
        Silver_Usr=Silver_Usr_temp;
        Regular_Usr=Regular_Usr_temp;
        All_Usr=All_Usr_temp;
//Reinitialize Usr_temp
        while(!Platinum_Usr_temp.isEmpty()){
            delete Platinum_Usr_temp.removeFront();
        }
        while(!Gold_Usr_temp.isEmpty()){
            delete Gold_Usr_temp.removeFront();
        }
        while(!Silver_Usr_temp.isEmpty()){
            delete Silver_Usr_temp.removeFront();
        }
        while(!Regular_Usr_temp.isEmpty()){
            delete Regular_Usr_temp.removeFront();
        }
        while(!All_Usr_temp.isEmpty()){
            delete All_Usr_temp.removeFront();
        }
//Implementation of Answering

        if (!is_answering) {
            if (Regular_calling_count == 0 && Silver_calling_count == 0 &&
                Gold_calling_count == 0 && Platinum_calling_count == 0) {
                is_answering = false;
            } else {
                if (Platinum_calling_count > 0) {
                    while (!Platinum_Usr.isEmpty()) {
                        Event *Platinum_temp = Platinum_Usr.removeFront();
                        if (Platinum_temp->is_calling && !is_answering) {
                            is_answering = true;
                            Platinum_temp->is_calling = false;
                            Platinum_temp->is_answered = true;
                            Platinum_temp->answered_at_tick = tick;
                            cout << "Answering call from " << Platinum_temp->name << endl;
//                            Platinum_calling_count--;
                        }
                        Platinum_Usr_temp.insertBack(Platinum_temp);
                    }
                    Platinum_Usr = Platinum_Usr_temp;
                } else if (Gold_calling_count > 0 && !is_answering) {
                    while (!Gold_Usr.isEmpty()) {
                        Event *Gold_temp = Gold_Usr.removeFront();
                        if (Gold_temp->is_calling && !is_answering) {
                            is_answering = true;
                            Gold_temp->is_calling = false;
                            Gold_temp->is_answered = true;
                            Gold_temp->answered_at_tick=tick;
                            cout << "Answering call from " << Gold_temp->name << endl;
//                            Gold_calling_count--;
                        }
                        Gold_Usr_temp.insertBack(Gold_temp);
                    }
                    Gold_Usr = Gold_Usr_temp;
                } else if (Silver_calling_count > 0 && !is_answering) {
                    while (!Silver_Usr.isEmpty()) {
                        Event *Silver_temp = Silver_Usr.removeFront();
                        if (Silver_temp->is_calling && !is_answering) {
                            is_answering = true;
                            Silver_temp->is_answered = true;
                            Silver_temp->is_calling = false;
                            Silver_temp->answered_at_tick = tick;
                            cout << "Answering call from " << Silver_temp->name << endl;
//                            Silver_calling_count--;
                        }
                        Silver_Usr_temp.insertBack(Silver_temp);
                    }
                    Silver_Usr = Silver_Usr_temp;
                } else if (Regular_calling_count > 0 && !is_answering) {
                    while (!Regular_Usr.isEmpty()) {
                        Event *Regular_temp = Regular_Usr.removeFront();
                        if (Regular_temp->is_calling && !is_answering) {
                            is_answering = true;
                            Regular_temp->is_answered = true;
                            Regular_temp->is_calling = false;
                            Regular_temp->answered_at_tick=tick;
                            cout << "Answering call from " << Regular_temp->name << endl;
//                            Regular_calling_count--;
                        }
                        Regular_Usr_temp.insertBack(Regular_temp);
                    }
                    Regular_Usr = Regular_Usr_temp;
                }
            }
        }

//Reinitialize Usr_temp
        while(!Platinum_Usr_temp.isEmpty()){
           delete Platinum_Usr_temp.removeFront();
        }
        while(!Gold_Usr_temp.isEmpty()){
            delete Gold_Usr_temp.removeFront();
        }
        while(!Silver_Usr_temp.isEmpty()){
            delete Silver_Usr_temp.removeFront();
        }
        while(!Regular_Usr_temp.isEmpty()){
            delete Regular_Usr_temp.removeFront();
        }


        tick++;
    }
}