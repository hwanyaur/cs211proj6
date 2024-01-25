/*building.cpp*/

//
// A building in the Open Street Map.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#include "building.h"
#include "footways.h"

using namespace std;

//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
    : ID(id), Name(name), StreetAddress(streetAddr) {
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  // this->ID = id;
  // this->Name = name;
  // this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid) { this->NodeIDs.push_back(nodeid); }


//
// prints all info related to building
//
void Building::printInfo(Building B, Nodes nodes, Footways &footways, vector<long long> intersects) {
  cout << B.Name << endl;
  cout << "Address: " << B.StreetAddress << endl;
  cout << "Building ID: " << B.ID << endl;

  cout << "Nodes:" << endl;
  B.print(nodes, footways, intersects);

} // if


//
// prints all nodes associated with building
//
void Building::print(Nodes &nodes, Footways &footways,
                     vector<long long> intersects) {
  for (long long nodeid : this->NodeIDs) {
    cout << "  " << nodeid << ": ";

    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      cout << "(" << lat << ", " << lon << ")";

      if (entrance)
        cout << ", is entrance";

      cout << endl;

      // finds intersection
      
      bool intersect = footways.findIntersect(footways, nodeid, intersects);

    } else {
      cout << "**NOT FOUND**" << endl;
    }
    
  }
  //cout << "Footways that intersect" << endl;
  footways.printIntersection(intersects);
  
}

