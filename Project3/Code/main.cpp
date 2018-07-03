#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cassert>
#include "world_type.h"

using namespace std;

void getinstruct(species_t &a, string s, int &kk, int &istoinstruction);
//EFFECTS: give s as enum to a, and add kk
//Modifies: a, kk

void instruct_to(species_t &a, unsigned int b, const int kk);
//EFFECTS: Give to the movement for kk so that it could define
//

direction_t leftFrom(direction_t dir);

direction_t rightFrom(direction_t dir);

point_t adjacentPoint(point_t pt, direction_t dir);

void World_print(const world_t &aWorld);

instruction_t getInstruction(const creature_t &creature);

creature_t *getCreature(const grid_t &grid,point_t location);

direction_t leftFrom(direction_t dir) {
    if (dir == EAST) return NORTH;
    if (dir == NORTH) return WEST;
    if (dir == WEST) return SOUTH;
    if (dir == SOUTH) return EAST;
}

direction_t rightFrom(direction_t dir) {
    if (dir == EAST) return SOUTH;
    if (dir == SOUTH) return WEST;
    if (dir == WEST) return NORTH;
    if (dir == NORTH) return EAST;
}

point_t adjacentPoint(point_t pt, direction_t dir) {
    if (dir == NORTH) {
        pt.r--;
    } else if (dir == SOUTH) pt.r++;
    else if (dir == WEST) pt.c--;
    else if (dir == EAST) pt.c++;
    return pt;
}

instruction_t getInstruction(const creature_t &creature) {
    return creature.species->program[creature.programID-1];
}

void getWorld(world_t &aWorld, string Dir_wrld);
//EFFECTS: Get the world information from the corresponding world file.

void species_movement(world_t &aWorld, int current_species_A);

void HOP_action(creature_t &acreature, world_t &aWorld);

void infect_action(creature_t &acreature, world_t &aWorld );

bool ifempty(creature_t &acreature,world_t &aWorld);

bool ifenemy(creature_t &acreature,world_t &aWorld);

bool ifsame(creature_t &acreature,world_t &aWorld);

bool ifwall(creature_t &acreature,world_t &aWorld);

void go(creature_t &acreature,world_t &aWorld);

void species_movement_with_print_concise(world_t &aWorld, int current_species_A);

void ARCH_infect_helper(creature_t &acreature, world_t &aWorld );

void World_simulation(world_t &aWorld, int Round);

void species_movement_with_print(world_t &aWorld, int current_species_A);

void Verbose_Print(world_t & aWorld, int Round);

//void species_movement_excution(creature_t &aCreatr);

void getinstruct(species_t &a, string s, int &kk, int &istoinstruction) {
    if (s == "hop") {
        kk++;
        a.program[kk].op = HOP;
    } else if (s == "left") {
        kk++;
        a.program[kk].op = LEFT;
    } else if (s == "right") {
        kk++;
        a.program[kk].op = RIGHT;
    }
    else if (s == "infect")  {
        kk++;
        a.program[kk].op = INFECT;
    }
    else if (s == "ifempty") {
        kk++;
        a.program[kk].op = IFEMPTY;
    } else if (s == "ifenemy") {
        kk++;
        a.program[kk].op = IFENEMY;
    } else if (s == "ifsame") {
        kk++;
        a.program[kk].op = IFSAME;
    } else if (s == "ifwall") {
        kk++;
        a.program[kk].op = IFWALL;
    } else if (s == "go") {
        kk++;
        a.program[kk].op = GO;
    } else {
        cout << "Error: Instruction " << s << " is not recognized!" << endl;
        exit(0);
    }
    a.program[kk].address=0; // to initialize the address, we note it as 0
}

void instruct_to(species_t &a, unsigned int b, const int kk) {
    a.program[kk].address = b;
}

void getWorld(world_t &aWorld, string Dir_wrld) {
    ifstream iFile2;
    stringstream iString2;
    string line2;
    iFile2.open(Dir_wrld);
    if (!iFile2){
        cout << "Error: Cannot open file "<< Dir_wrld << "!" << endl;
        exit(0);
    }
    int heighT, widTh;
    int row, column;// used in loop
    char TerrType;
// To read height and width
    getline(iFile2, line2);
//    iString2 << line2;
    iString2.str(line2);
    iString2 >> heighT;
    iString2.clear();
    getline(iFile2, line2);
//    iString2 << line2;
    iString2.str(line2);
    iString2 >> widTh;
    iString2.clear();
    if (widTh > MAXWIDTH || widTh <1) {
        cout << "Error: The grid width is illegal!" << endl;
        exit(0);
    }
    if (heighT > MAXHEIGHT || heighT < 1) {
        cout << "Error: The grid height is illegal!" << endl;
        exit(0);
    }
    aWorld.grid.height=heighT;
    aWorld.grid.width = widTh;
// Loop to read terrain type
    for (row=0;row<widTh;row++){
        getline(iFile2,line2);
//        iString2 << line2;
        iString2.str(line2);
        for (column=0;column<heighT;column++) {
            iString2.get(TerrType);
            if (TerrType=='P') aWorld.grid.terrain[row][column]= PLAIN;
            else if (TerrType == 'L') aWorld.grid.terrain[row][column] = LAKE;
            else if (TerrType == 'F') aWorld.grid.terrain[row][column] = FOREST;
            else if (TerrType == 'H') aWorld.grid.terrain[row][column] = HILL;
            else {
                cout << "Error: Terrain square (" <<TerrType << " " << row << " " << column << ") is invalid!";
                exit(0);
            }
            aWorld.grid.squares[row][column] = NULL; //initialize the pointer to creature
        }
        iString2.clear();
    }
//Loop to load creatures in the world
    int creature_num=0;
    int ii;
    while (!iFile2.eof()) {
        string CretType, CreatDir;
        char superpower, blk; // used to judge the kongge, a and f
        int isToEnd=0;
        getline(iFile2,line2);
//        iString2 << line2;
        iString2.str(line2);
        if(line2=="") break;
        iString2 >> CretType;
// Loop for getting the creature name;
        for (ii=0;ii< aWorld.numSpecies;ii++) {
            if (CretType == aWorld.species[ii].name) {
                aWorld.creatures[creature_num].species = &aWorld.species[ii];
                isToEnd = 1;
            }
            if (ii == aWorld.numSpecies - 1 && isToEnd == 0) {
                cout << "Error: Species " << CretType << " not found!" << endl;
                exit(0);
            }
        }
// To get direction
        string DirecTion;
        iString2 >> DirecTion;
        if (DirecTion == "east") aWorld.creatures[creature_num].direction = EAST;
        else if (DirecTion == "west") aWorld.creatures[creature_num].direction = WEST;
        else if (DirecTion == "south") aWorld.creatures[creature_num].direction = SOUTH;
        else if (DirecTion == "north") aWorld.creatures[creature_num].direction = NORTH;
        else {
            cout << "Error: Direction " << DirecTion << " is not recognized!" << endl;
            exit(0);
        }
// To get position
        int Creature_Height, Creature_Width;
        iString2 >> Creature_Height>> Creature_Width;
        if (Creature_Height >= aWorld.grid.height || Creature_Width >= aWorld.grid.width ) {
            cout << "Error: Creature (" << aWorld.creatures->species->name << " "
                 << directName[aWorld.creatures->direction] << " " <<
                 Creature_Height << " " << Creature_Width << ") is out of bound!" << endl;
            cout << "The grid size is " << aWorld.grid.height << "-by-"<< aWorld.grid.width << "." << endl;
            exit(0);
        }
        aWorld.creatures[creature_num].location.r=Creature_Height;
        aWorld.creatures[creature_num].location.c=Creature_Width;

        if (aWorld.grid.squares[Creature_Height][Creature_Width]!= NULL){
            creature_t *CrExisted= aWorld.grid.squares[Creature_Height][Creature_Width];
            const creature_t CrNew= aWorld.creatures[creature_num];

            cout << "Error: Creature (" <<CrNew.species->name <<" " << directName[CrNew.direction] << " " << CrNew.location.r << " " << CrNew.location.c
                 << ") overlaps with creature (" <<CrExisted->species->name << " " << directName[CrExisted->direction] << " " << CrExisted->location.r << " " << CrExisted->location.c<< ")!" << endl;
            exit(0);
        }



        aWorld.grid.squares[Creature_Height][Creature_Width]=&aWorld.creatures[creature_num];
        aWorld.creatures[creature_num].ability[FLY] = false;// initializaion
        aWorld.creatures[creature_num].ability[ARCH] = false;//initialization
        aWorld.creatures[creature_num].programID=1;//initialization
        aWorld.creatures[creature_num].hillActive=false;//initialization
        while(!iString2.eof()){
            iString2 >> superpower;
            if (superpower== 'f') {
                aWorld.creatures[creature_num].ability[FLY]=true;
            }
            else if (superpower == 'a') {
                aWorld.creatures[creature_num].ability[ARCH]=true;
            }
            else {
                cout << "Error: Creature (" << aWorld.creatures[creature_num].species->name << " " <<directName[aWorld.creatures[creature_num].direction]<<
                     " "<< aWorld.creatures[creature_num].location.r << " " << aWorld.creatures[creature_num].location.c << ") has an invalid ability " <<
                     superpower <<  "!"<<endl;
                exit(0);
            }
        }

        if (aWorld.grid.terrain[Creature_Height][Creature_Width]==LAKE){
            if (aWorld.creatures[creature_num].ability[FLY]==false) {
                const creature_t CrNew= aWorld.creatures[creature_num];
                cout << "Error: Creature (" <<CrNew.species->name <<" " << directName[CrNew.direction] << " " << CrNew.location.r << " " << CrNew.location.c <<
                     ") is in a lake square " << endl;
                cout << "The creature cannot fly!" << endl;
                exit(0);
            }
        }
        iString2.clear();
        creature_num++;
        if (creature_num > MAXCREATURES) {
            cout << "Error: Too many creatures!" << endl;
            cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
            exit(0);
        }
    }
    aWorld.numCreatures=creature_num;
    iFile2.clear();
    iFile2.close();
}

void World_simulation(world_t &aWorld, int Round){

    int current_Round=0;
    while (current_Round<Round) {//simulate big round
        int current_creature_activated;
        for (current_creature_activated=0;current_creature_activated<aWorld.numCreatures;current_creature_activated++) //simulate steps for each creature
        {
            if (aWorld.grid.terrain[aWorld.creatures[current_creature_activated].location.r][aWorld.creatures[current_creature_activated].location.c]==HILL) {
                if(!aWorld.creatures[current_creature_activated].hillActive){
                    species_movement(aWorld,current_creature_activated);
                    aWorld.creatures[current_creature_activated].hillActive=true;
                }
                else {
                    aWorld.creatures[current_creature_activated].hillActive=false;
                }
            }
            else{
                species_movement(aWorld,current_creature_activated); // For the individual round the simulation result for each of the creature
            }
        }
        current_Round++;
    }
}

void World_print(const world_t &aWorld){
    int r,c; // i indicates columns(width), j indicates rows(height)
    for (r=0;r<aWorld.grid.height;r++){
        for (c=0;c<aWorld.grid.width;c++){
            if (aWorld.grid.squares[r][c] == NULL) {
                cout << "____ " ;
            }
            else {
                cout << aWorld.grid.squares[r][c]->species->name.substr(0,2) << "_" << directShortName[aWorld.grid.squares[r][c]->direction]<< " ";
            }
            if (c == aWorld.grid.width-1) cout << endl;
        }
    }
}

void Verbose_Print(world_t & aWorld, int Round) {
    cout << "Initial state" << endl;
    int current_Round=0;
    World_print(aWorld);
    while (current_Round<Round) {//simulate big round
        cout << "Round " << current_Round+1 << endl;
        int current_creature_activated;
        for (current_creature_activated=0;current_creature_activated<aWorld.numCreatures;current_creature_activated++) //simulate steps for each creature
        {
            creature_t &CurCrt=aWorld.creatures[current_creature_activated];
            cout << "Creature (" << aWorld.creatures[current_creature_activated].species->name << " " << directName[aWorld.creatures[current_creature_activated].direction] << " " << CurCrt.location.r << " " << CurCrt.location.c << ") takes action:" << endl  ;
            if (aWorld.grid.terrain[aWorld.creatures[current_creature_activated].location.r][aWorld.creatures[current_creature_activated].location.c]==HILL) {
                if(!aWorld.creatures[current_creature_activated].hillActive){
                    species_movement_with_print(aWorld,current_creature_activated);
                    aWorld.creatures[current_creature_activated].hillActive=true;
                }
                else {
                    aWorld.creatures[current_creature_activated].hillActive=false;
                }
            }
            else{
                species_movement_with_print(aWorld,current_creature_activated); // For the individual round the simulation result for each of the creature
            }
//            World_print(aWorld);
        }
        current_Round++;
    }
}

void concise_Print(world_t & aWorld, int Round) { //In a short print
    cout << "Initial state" << endl;
    int current_Round=0;
    World_print(aWorld);
    while (current_Round<Round) {//simulate big round
        cout << "Round " << current_Round+1 <<endl;
        int current_creature_activated;
        for (current_creature_activated=0;current_creature_activated<aWorld.numCreatures;current_creature_activated++) //simulate steps for each creature
        {
            creature_t &CurCrt=aWorld.creatures[current_creature_activated];
            cout << "Creature (" << aWorld.creatures[current_creature_activated].species->name << " " << directName[aWorld.creatures[current_creature_activated].direction] << " " << CurCrt.location.r << " " << CurCrt.location.c << ") takes action: "  ;
            if (aWorld.grid.terrain[aWorld.creatures[current_creature_activated].location.r][aWorld.creatures[current_creature_activated].location.c]==HILL) {
                if(!aWorld.creatures[current_creature_activated].hillActive){
                    species_movement_with_print_concise(aWorld,current_creature_activated);
                    aWorld.creatures[current_creature_activated].hillActive=true;
                }
                else {
                    aWorld.creatures[current_creature_activated].hillActive=false;
                }
            }
            else{
                species_movement_with_print_concise(aWorld,current_creature_activated); // For the individual round the simulation result for each of the creature
            }
        }
        World_print(aWorld);
        current_Round++;
    }
}

void species_movement_with_print(world_t &aWorld, int current_species_A){
    creature_t & CurrentCreature= aWorld.creatures[current_species_A];
    instruction_t CurrentProgram = aWorld.creatures[current_species_A].species->program[CurrentCreature.programID-1];
    while(CurrentProgram.op!=HOP && CurrentProgram.op!= LEFT && CurrentProgram.op!= RIGHT && CurrentProgram.op!=INFECT){
        cout << "Instruction " << CurrentCreature.programID << ": " << opName[CurrentProgram.op] << " "<< CurrentProgram.address << endl;
        if (CurrentProgram.op == IFEMPTY) {
            if(ifempty(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFENEMY) {
            if(ifenemy(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFSAME) {
            if(ifsame(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFWALL) {
            if(ifwall(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == GO) {
            CurrentCreature.programID=CurrentProgram.address;
        }
        CurrentProgram=CurrentCreature.species->program[CurrentCreature.programID-1];
    }
    //Please Remeber to judge boundary points later
    cout << "Instruction " << CurrentCreature.programID << ": " << opName[CurrentProgram.op] << endl;
    if (CurrentProgram.op == HOP) {
        HOP_action(CurrentCreature,aWorld);
        World_print(aWorld);
        CurrentCreature.programID++;
    }
    else if (CurrentProgram.op == LEFT ) {
        CurrentCreature.direction=leftFrom(CurrentCreature.direction);
        World_print(aWorld);
        CurrentCreature.programID++;
    }
    else if(CurrentProgram.op == RIGHT) {
        CurrentCreature.direction=rightFrom(CurrentCreature.direction);
        World_print(aWorld);
        CurrentCreature.programID++;
    }
    else if(CurrentProgram.op == INFECT) {
        infect_action(CurrentCreature,aWorld);
        World_print(aWorld);
        CurrentCreature.programID++;
    }

}

void species_movement_with_print_concise(world_t &aWorld, int current_species_A) {
    int i;
//    for (i = 0; i < aWorld.creatures[current_species_A].species->programSize; i++) {
//
//        int CURR_row = aWorld.creatures[current_species_A].location.r;
//        int CURR_column = aWorld.creatures[current_species_A].location.c;
//    }
    creature_t & CurrentCreature= aWorld.creatures[current_species_A];
    instruction_t CurrentProgram = aWorld.creatures[current_species_A].species->program[CurrentCreature.programID-1];
    while(CurrentProgram.op!=HOP && CurrentProgram.op!= LEFT && CurrentProgram.op!= RIGHT && CurrentProgram.op!=INFECT){
        //cout << "Instruction " << CurrentCreature.programID << ": " << opName[CurrentProgram.op] << endl;
        if (CurrentProgram.op == IFEMPTY) {
            if(ifempty(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFENEMY) {
            if(ifenemy(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFSAME) {
            if(ifsame(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFWALL) {
            if(ifwall(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == GO) {
            CurrentCreature.programID=CurrentProgram.address;
        }
        CurrentProgram=CurrentCreature.species->program[CurrentCreature.programID-1];
    }
    //Please Remeber to judge boundary points later
    cout << opName[CurrentProgram.op] << endl;
    if (CurrentProgram.op == HOP) {
        HOP_action(CurrentCreature,aWorld);
        CurrentCreature.programID++;
    }
    else if (CurrentProgram.op == LEFT ) {
        CurrentCreature.direction=leftFrom(CurrentCreature.direction);
        CurrentCreature.programID++;
    }
    else if(CurrentProgram.op == RIGHT) {
        CurrentCreature.direction=rightFrom(CurrentCreature.direction);
        CurrentCreature.programID++;
    }
    else if(CurrentProgram.op == INFECT) {
        infect_action(CurrentCreature,aWorld);
        CurrentCreature.programID++;
    }
    // World_print(aWorld);
}

void species_movement(world_t &aWorld, int current_species_A) {
    int i;
//    for (i = 0; i < aWorld.creatures[current_species_A].species->programSize; i++) {
//
//        int CURR_row = aWorld.creatures[current_species_A].location.r;
//        int CURR_column = aWorld.creatures[current_species_A].location.c;
//    }
    creature_t & CurrentCreature= aWorld.creatures[current_species_A];
    instruction_t CurrentProgram = aWorld.creatures[current_species_A].species->program[CurrentCreature.programID-1];
    while(CurrentProgram.op!=HOP && CurrentProgram.op!= LEFT && CurrentProgram.op!= RIGHT && CurrentProgram.op!=INFECT){
        if (CurrentProgram.op == IFEMPTY) {
            if(ifempty(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFENEMY) {
            if(ifenemy(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFSAME) {
            if(ifsame(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == IFWALL) {
            if(ifwall(CurrentCreature,aWorld)) {
                CurrentCreature.programID=CurrentProgram.address;
            }
            else CurrentCreature.programID++;
        }
        else if (CurrentProgram.op == GO) {
            CurrentCreature.programID=CurrentProgram.address;
        }
        CurrentProgram=CurrentCreature.species->program[CurrentCreature.programID-1];
    }
    //Please Remeber to judge boundary points later
    if (CurrentProgram.op == HOP) {
        HOP_action(CurrentCreature,aWorld);
        CurrentCreature.programID++;
    }
    else if (CurrentProgram.op == LEFT ) {
        CurrentCreature.direction=leftFrom(CurrentCreature.direction);
        CurrentCreature.programID++;
    }
    else if(CurrentProgram.op == RIGHT) {
        CurrentCreature.direction=rightFrom(CurrentCreature.direction);
        CurrentCreature.programID++;
    }
    else if(CurrentProgram.op == INFECT) {
        infect_action(CurrentCreature,aWorld);
        CurrentCreature.programID++;
    }
}



void HOP_action(creature_t &acreature, world_t &aWorld){
    point_t adj_point=adjacentPoint(acreature.location,acreature.direction);
    if (aWorld.grid.squares[adj_point.r][adj_point.c] == NULL) {
        if (0 <= adj_point.c && adj_point.c < aWorld.grid.width && 0 <= adj_point.r &&
            adj_point.r < aWorld.grid.height) {
            if (aWorld.grid.terrain[adj_point.r][adj_point.c] == LAKE) {
                if (acreature.ability[FLY] == 1) {
                    aWorld.grid.squares[acreature.location.r][acreature.location.c] = NULL;
                    acreature.location = adj_point;
                    aWorld.grid.squares[adj_point.r][adj_point.c] = &acreature;
                }
            } else {
                aWorld.grid.squares[acreature.location.r][acreature.location.c] = NULL;
                acreature.location = adj_point;
                aWorld.grid.squares[adj_point.r][adj_point.c] = &acreature;
            }
        }
    }
}

void infect_action(creature_t &acreature, world_t &aWorld ){
    point_t adj_point=adjacentPoint(acreature.location,acreature.direction);
    if (aWorld.grid.squares[adj_point.r][adj_point.c]!= NULL && 0<=adj_point.c && adj_point.c<aWorld.grid.width && 0 <= adj_point.r && adj_point.r < aWorld.grid.height && aWorld.grid.squares[adj_point.r][adj_point.c]->species!=acreature.species) {
        if (!acreature.ability[ARCH]) {
            if (aWorld.grid.squares[adj_point.r][adj_point.c] != NULL) {
                if (aWorld.grid.terrain[adj_point.r][adj_point.c] != FOREST) {
                    if (aWorld.grid.squares[adj_point.r][adj_point.c]->species->name != acreature.species->name) {
                        aWorld.grid.squares[adj_point.r][adj_point.c]->species = acreature.species;
                        aWorld.grid.squares[adj_point.r][adj_point.c]->programID = 1;
                    }
                }
            }
        } else if (acreature.ability[ARCH]) {
            ARCH_infect_helper(acreature, aWorld);
        }
    }
}

void ARCH_infect_helper(creature_t &acreature, world_t &aWorld ){
    int i;
    bool is_already_infected= false;
    if (acreature.direction==EAST) {
        for(i=acreature.location.c;i<aWorld.grid.width;i++){
            if (aWorld.grid.squares[acreature.location.r][i] != NULL){
                if (is_already_infected)  break;
                else {
                    if (aWorld.grid.squares[acreature.location.r][i]->species!=acreature.species){
                        is_already_infected=true;
                        aWorld.grid.squares[acreature.location.r][i]->species = acreature.species;
                        aWorld.grid.squares[acreature.location.r][i]->programID=1;
                    }
                }}
        }
    }
    else if (acreature.direction == WEST) {
        for(i=acreature.location.c;i>=0;i--){
            if (aWorld.grid.squares[acreature.location.r][i] != NULL){
                if (is_already_infected)  break;
                else {
                    if (aWorld.grid.squares[acreature.location.r][i]->species!=acreature.species){
                        is_already_infected=true;
                        aWorld.grid.squares[acreature.location.r][i]->species = acreature.species;
                        aWorld.grid.squares[acreature.location.r][i]->programID=1;
                    }
                }}
        }
    }
    else if(acreature.direction == SOUTH) {
        for(i=acreature.location.r;i< aWorld.grid.height;i++){
            if (aWorld.grid.squares[i][acreature.location.c] != NULL){
                if (is_already_infected)  break;
                else {
                    if (aWorld.grid.squares[i][acreature.location.c]->species!=acreature.species){
                        is_already_infected=true;
                        aWorld.grid.squares[i][acreature.location.c]->species = acreature.species;
                        aWorld.grid.squares[i][acreature.location.c]->programID=1;
                    }
                }
            }}
    }
    else if(acreature.direction == NORTH) {
        for (i=acreature.location.r ; i>=0;i--) {
            if (aWorld.grid.squares[i][acreature.location.c]!= NULL){
                if (is_already_infected) break;
                else {
                    if (aWorld.grid.squares[i][acreature.location.c]->species!=acreature.species){
                        is_already_infected=true;
                        aWorld.grid.squares[i][acreature.location.c]->species = acreature.species;
                        aWorld.grid.squares[i][acreature.location.c]->programID=1;
                    }
                }
            }}
    }
}

bool ifempty(creature_t &acreature,world_t &aWorld){
    point_t pt=adjacentPoint(acreature.location,acreature.direction);
    if (!(pt.r<0||pt.r>=aWorld.grid.height||pt.c<0||pt.c>=aWorld.grid.width)){
        if (aWorld.grid.squares[pt.r][pt.c]==NULL) {
            return true;
        }
        else return false;
    }
    else return false;
}

bool ifenemy(creature_t &acreature,world_t &aWorld){
    point_t pt=adjacentPoint(acreature.location,acreature.direction);
    if (!(pt.r<0||pt.r>=aWorld.grid.height||pt.c<0||pt.c>=aWorld.grid.width)){
    if (aWorld.grid.terrain[pt.r][pt.c]!=FOREST && aWorld.grid.squares[pt.r][pt.c] != NULL && aWorld.grid.squares[pt.r][pt.c]->species!=acreature.species){
        return true;
    }
    else return false;}
    else return false;
}

bool ifsame(creature_t &acreature,world_t &aWorld) {
    point_t pt = adjacentPoint(acreature.location, acreature.direction);
    if (!(pt.r < 0 || pt.r >= aWorld.grid.height || pt.c < 0 || pt.c >= aWorld.grid.width)) {
        if (aWorld.grid.terrain[pt.r][pt.c] != FOREST && aWorld.grid.squares[pt.r][pt.c] != NULL &&
            aWorld.grid.squares[pt.r][pt.c]->species == acreature.species) {
            return true;
        } else return false;
    }
    else return false;
}
bool ifwall(creature_t &acreature,world_t &aWorld){
    point_t pt=adjacentPoint(acreature.location,acreature.direction);
    if ((aWorld.grid.terrain[pt.r][pt.c]==FOREST && !acreature.ability[FLY]) || pt.r<0||pt.r>=aWorld.grid.height||pt.c<0||pt.c>=aWorld.grid.width){
        return true;
    }
    else return false;
}

//void go(creature_t &acreature,world_t &aWorld){
//    acreature.programID=acreature.species->program[acreature.programID-1].address;
//}


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
                cout << Species_name[i] << endl;                // This line is only used for debug to
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
    cout << argv[3] << endl;
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