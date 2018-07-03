//
// Created by 大泽 on 2017/7/3.
//
#include "world_type.h"

#ifndef PROJECT3_SIMULATION_H
#define PROJECT3_SIMULATION_H
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


void getWorld(world_t &aWorld, string Dir_wrld);
//EFFECTS: Get the world information from the corresponding world file.

void species_movement(world_t &aWorld, int current_species_A);

void HOP_action(creature_t &acreature, world_t &aWorld);

void infect_action(creature_t &acreature, world_t &aWorld );

bool ifempty(creature_t &acreature,world_t &aWorld);

bool ifenemy(creature_t &acreature,world_t &aWorld);

bool ifsame(creature_t &acreature,world_t &aWorld);

bool ifwall(creature_t &acreature,world_t &aWorld);

//void go(creature_t &acreature,world_t &aWorld);

void species_movement_with_print_concise(world_t &aWorld, int current_species_A);

void ARCH_infect_helper(creature_t &acreature, world_t &aWorld );

void World_simulation(world_t &aWorld, int Round);

void species_movement_with_print(world_t &aWorld, int current_species_A);

void Verbose_Print(world_t & aWorld, int Round);

void concise_Print(world_t & aWorld, int Round);

#endif //PROJECT3_SIMULATION_H
