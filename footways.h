/*footways.h*/

//
// A vector of footways in the Open Street Map
// 
// Yaurie Hwang
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include <vector>

#include "footway.h"
#include "footways.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// Keeps track of all the nodes in the map.
//
class Footways
{
public:
  vector<Footway> MapFootways;

// finds if there is a common ID
  bool findIntersect(Footways &footways, long long ID, vector<long long> &intersects);

//inputs footways
  void readMapFootways(XMLDocument &xmldoc);

  // gets number of footways
  int getNumMapFootways(); 

  // finds if there is a common ID given a footway
  bool find(long long ID, Footway i, vector<long long> &intersects); 

// prevents duplicates in the intersects vector
  bool dupes(vector<long long> &intersects, long long nodeID);


// prints intersections for each building
  void printIntersection(vector<long long> &intersects);
};
