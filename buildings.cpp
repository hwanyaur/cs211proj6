/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "building.h"
#include "buildings.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "footways.h"

using namespace std;
using namespace tinyxml2;

//
// readMapBuildings
//
// Given an XML document, reads through the document and
// stores all the buildings into the given vector.
//
void Buildings::readMapBuildings(XMLDocument &xmldoc) {
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
    // if this is a building, store info into vector:
    //
    if (osmContainsKeyValue(way, "building", "university")) {
      string name = osmGetKeyValue(way, "name");

      string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " +
                          osmGetKeyValue(way, "addr:street");

      //
      // create building object, then add the associated
      // node ids to the object:
      //
      long long id = attr->Int64Value();

      Building B(id, name, streetAddr);

      XMLElement *nd = way->FirstChildElement("nd");

      while (nd != nullptr) {
        const XMLAttribute *ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long id = ndref->Int64Value();

        B.add(id);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      //
      // add the building to the vector:
      //
      this->MapBuildings.push_back(B);
    } // if

    way = way->NextSiblingElement("way");
  } // while

  //
  // done:
  //
}

//
// accessors / getters
//
int Buildings::getNumMapBuildings() { return (int)this->MapBuildings.size(); }

//
// prints all buildings with name
//
void Buildings::print(Building B, Nodes nodes, Footways &footways, vector<long long> intersects) {
  cout << B.Name << endl;
  cout << "Address: " << B.StreetAddress << endl;
  cout << "Building ID: " << B.ID << endl;

  cout << "Nodes:" << endl;
  B.print(nodes, footways, intersects);

} // if

//
// finds all buildings and prints them
//
void Buildings::findAndPrint(string name, Nodes nodes, Footways &footways,
                     vector<long long> intersects) {
  for (Building &B : this->MapBuildings) {
    if (B.Name.find(name) != string::npos) { // contains name:
      //cout << "hi" << endl;
      B.printInfo(B, nodes, footways, intersects);
    }
  } // for
}
