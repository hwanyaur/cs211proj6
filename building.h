/*building.h*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "node.h"
#include "nodes.h"
#include "footways.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  //
  // prints the nodes related to the building
  //
  void print(Nodes& nodes, Footways& footways, vector<long long> intersects);

// prints the intersecting node IDs
  void printIntersection(vector<long long> intersects);

//prints all info related to building
void printInfo(Building B, Nodes nodes, Footways &footways, vector<long long> intersects);
};
