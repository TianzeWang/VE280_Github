//
// Created by Peter on 2017/7/3.
//

#include "simulation.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>


int main(int argc, char *argv[]) {
    ifstream iFile;
    stringstream iString;

    if (argc <= 3) {
        cout << "Error: Missing arguments!" << endl;
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
        exit(0);
    }

    if (atoi(argv[3]) <0) {
        cout << "Error: Number of simulation rounds is negative!" << endl;
        exit(0);
    }


    string line, Spc_Proty, Spc_Dir;
    string Species_name[MAXSPECIES];
    species_t BigSpecie[MAXSPECIES];
    creature_t BigCreature[MAXCREATURES];
    world_t BigWorld;
//    string blank = "";
    int i = 0;          // for counting
    int j = 0;          // for noting the number of species

//The Program for get the Directory of species

    iFile.open(argv[1]);
    if (!iFile){
        cout << "Error: Cannot open file "<< argv[1] << "!" << endl;
        exit(0);
    }
//    iFile.open("species");
    getline(iFile, line);
    iString << line;
    iString >> Spc_Dir;// to get the name of directory
    iString.clear();
//The function for get the name of species
    while (!iFile.eof()) {
        getline(iFile, line);               //Here may occur bugs, note that later.
        if (line != "") {
            iString << line;
            iString >> Species_name[i];
            i++;
                          // This line is only used for debug to
            // check whether it can get the correct output.
            iString.clear();

//            }
        }
        if (i >MAXSPECIES){
            cout << "Error: Too many species!" << endl;
            cout << "Maximal number of species is " << MAXSPECIES<< "." << endl;
        }
    }//Here is the code to gain the species data and put the name of species into
    //an array called Species_name[MAXSPECIES].

    iFile.close();

    j = i - 1;
    int k;                  // used for counting in the next loop. Remember to compare the size of k with the program
    //size later.
    int steP;

//The function for get the instruction for each creatures
    for (i = 0; i <= j; i++) {
        k = -1;
        iFile.open(Spc_Dir + "/" + Species_name[i]);        //Here may occur bugs, note that later.

        if (!iFile){
            cout << "Error: Cannot open file "<< Spc_Dir << "/" << Species_name[i] << "!" << endl;
            exit(0);
        }

        BigSpecie[i].name = Species_name[i];
        int is_changed_to_instruction = 0;                //This indicates whether we have read the instruction
        while (!iFile.eof()) {                       //inside this loop i could never be modified
            getline(iFile, line);
            if (line == "") break;
            iString.str(line);
            iString >> Spc_Proty;                    // Should test errors here
            getinstruct(BigSpecie[i], Spc_Proty, k, is_changed_to_instruction); // modifies: BigSpecie[i], k
            steP = 0; //to check whether it follows a go to
            iString >> steP;
            if (steP != 0) {
                if (steP < 0) {

                    cout << "Error: The step that jump to must be a positive integer!" << endl;
                    exit(0);
                }
                instruct_to(BigSpecie[i], steP, k);
            }
            if (k > MAXPROGRAM) {
                cout << "Error: Too many instructions for species " << BigSpecie[i].name << "!" << endl;
                cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
                exit(0);

            }
            iString.clear();
        }
        iFile.close();
        BigSpecie[i].programSize = k+1;
    }

    for (i=0;i<=j ;i++) {
        BigWorld.species[i]=BigSpecie[i];
    }

    //Pass the species read to the world type
    BigWorld.numSpecies = j+1;
    getWorld(BigWorld, argv[2]);
//    getWorld(BigWorld,"world2");

    //This is a void big program to read all the world information


    //Next start simulation part
//    Verbose_Print( BigWorld, 8);
    //The following determines the concise output or the verbal output
//    cout << argv[4]<<endl;
//    cout << argv[3] << endl;
    if (argc==5) {
        string v = argv[4];
        string verbose = argv[4];
        if ((v == "v" || verbose == "verbose")) {      //Need Debug!
            Verbose_Print(BigWorld, atoi(argv[3]));
//        Verbose_Print(BigWorld, 8);
        }
    }
    else {
        concise_Print(BigWorld, atoi(argv[3]));
//        concise_Print(BigWorld, 8);
    }
}
