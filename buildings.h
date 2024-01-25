/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include "building.h"
#include "tinyxml2.h"
#include <iostream>
#include <vector>
#include <string>
#include "nodes.h"
#include "node.h"

using namespace std;
using namespace tinyxml2;

//
// Keeps track of all the buildings in the map.
//
class Buildings {
public:
  vector<Building> MapBuildings;

  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and
  // stores all the buildings into the given vector.
  //
  void readMapBuildings(XMLDocument &xmldoc);

  //
  // accessors / getters
  //
  int getNumMapBuildings();

  //
  // prints all buildings with name
  //
  void print(Building B, Nodes nodes, Footways &footways, vector<long long> intersects);
  
  //
  // finds all buildings and prints them
  // 
  void findAndPrint(string name, Nodes nodes, Footways &footways, vector<long long> intersects);
};


