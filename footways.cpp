/*footways.cpp*/

//
// A vector of footways in the Open Street Map.
//
// Yaurie Hwang
// Northwestern University
// CS 211: Winter 2023
//
#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "footway.h"
#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

// finds if there is a common node
// given node ID from building, checks
bool Footways::findIntersect(Footways &footways, long long ID, vector<long long> &intersects) {
  for (Footway i : footways.MapFootways) {
    if (footways.find(ID, i, intersects) == true) {
      if (footways.dupes(intersects, i.ID)  == false) {
        intersects.push_back(i.ID);
        }
      //cout << "i inserted " << i.ID << "!!!" << intersects.size() << endl;
  
    }
  } //for
  //reach the end of the footways 
  return false;
}

//iterates through the NodeIDs in a footway to see if there is a match
bool Footways::find(long long ID, Footway i, vector<long long> &intersects) {
  for (long long node: i.NodeIDs) {
    //cout << "node in find: " << node << endl;
    if (node == ID) { //there is a match
      return true;
    }
  }//for
  return false;
  }

// prevents duplicates in the intersects vectos
bool Footways::dupes(vector<long long> &intersects, long long nodeID) {
  for (long long i: intersects) {
    if (i == nodeID) {
      return true;
    }
  }
  return false;
}

// prints intersections of footways and buildings
void Footways::printIntersection(vector<long long> &intersects) {
  cout << "Footways that intersect: " << endl;
  if (intersects.size() != 0) {
    std::sort(intersects.begin(), intersects.end(), std::less<long long>());
    for (long long i : intersects) {
      cout << "  Footway " << i << endl;
    }
  }
  else{
    cout << "  None" << endl;
  }
}

//reads the possible footways from the doc
void Footways::readMapFootways(XMLDocument &xmldoc) {
  XMLElement *osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document way by way, looking for university buildings:
  //
  XMLElement *way = osm->FirstChildElement("way");

  while (way != nullptr) {
    const XMLAttribute *attr = way->FindAttribute("id");
    assert(attr != nullptr);

    //
    // if this is a footway, store info into vector:
    //
    if ((osmContainsKeyValue(way, "highway", "footway")) ||
        (osmContainsKeyValue(way, "area:highway", "footway"))) {
      string name = osmGetKeyValue(way, "name");

      string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " +
                          osmGetKeyValue(way, "addr:street");

      //
      // create footway object, then add the associated
      // node ids to the object:
      //
      long long id = attr->Int64Value();

      Footway F(id);

      XMLElement *nd = way->FirstChildElement("nd");

      while (nd != nullptr) {
        const XMLAttribute *ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long id = ndref->Int64Value();

        F.add(id);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      //
      // add the building to the vector:
      //
      this->MapFootways.push_back(F);
    } // if

    way = way->NextSiblingElement("way");
  } // while
}

// returns number of footways
int Footways::getNumMapFootways() { return (int)this->MapFootways.size(); }
