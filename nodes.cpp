/*nodes.cpp*/

//
// A collection of nodes in the Open Street Map.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//
// References:
//
// TinyXML:
//   files: https://github.com/leethomason/tinyxml2
//   docs:  http://leethomason.github.io/tinyxml2/
//
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include <utility>

using namespace std;
using namespace tinyxml2;

//
// readMapNodes
//
// Given an XML document, reads through the document and
// stores all the nodes into the given vector. Each node
// is a point on the map, with a unique id along with
// (lat, lon) position. Some nodes are entrances to buildings,
// which we capture as well.
//
void Nodes::readMapNodes(XMLDocument &xmldoc) {
  XMLElement *osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document node by node:
  //
  XMLElement *node = osm->FirstChildElement("node");

  while (node != nullptr) {
    const XMLAttribute *attrId = node->FindAttribute("id");
    const XMLAttribute *attrLat = node->FindAttribute("lat");
    const XMLAttribute *attrLon = node->FindAttribute("lon");

    assert(attrId != nullptr);
    assert(attrLat != nullptr);
    assert(attrLon != nullptr);

    // assign id, lat, lon
    long long id = attrId->Int64Value();
    double latitude = attrLat->DoubleValue();
    double longitude = attrLon->DoubleValue();

    bool entrance = false;

    if (osmContainsKeyValue(node, "entrance", "yes") ||
        osmContainsKeyValue(node, "entrance", "main") ||
        osmContainsKeyValue(node, "entrance", "entrance")) {
      entrance = true;
    }

    //
    // Add node to vector:
    //
    // This creates an object then pushes copy into vector:
    //
    //   Node N(id, latitude, longitude, entrance);
    //   this->MapNodes.push_back(N);
    //
    // This creates just one object "emplace", avoiding
    // an extra Node copy each time:
    //
    // this->MapNodes.emplace_back(id, latitude, longitude, entrance);
    Node N(id, latitude, longitude, entrance);
    this->MapNodes.emplace(id, Node(id, latitude, longitude, entrance));

    //
    // next node element in the XML doc:
    //
    node = node->NextSiblingElement("node");
  }
}

//
// sortByID
//
// sorts the nodes into ascending order by ID.
//
void Nodes::sortByID() {
  // sort(this->MapNodes.begin(), this->MapNodes.end(),
  //      [](Node a, Node b) { // sort from class
  //        if (a.getID() < b.getID()) {
  //          return true;
  //        } else {
  //          return false;
  //        }

  //      });
}

//
// find
//
// Searches the nodes for the one with the matching ID, returning
// true if found and false if not. If found, a copy of the node
// is returned via the node parameter, which is passed by reference.
//
bool Nodes::find(long long id, double &lat, double &lon, bool &isEntrance) {
  auto ptr = this->MapNodes.find(id);
  if (ptr == this->MapNodes.end()) {
    // not found
    return false;
  } else {
    if (id == ptr->second.getID()) {
    lat = ptr->second.getLat();
    lon = ptr->second.getLon();
    isEntrance = ptr->second.getIsEntrance();

      }

    
    return true;
      }
    // found: ???

    //   //
    //   // linear search:
    //   //
    //   for (Node& N : this->MapNodes)
    //   {
    //     if (N.getID() == id) {
    //       lat = N.getLat();
    //       lon = N.getLon();
    //       isEntrance = N.getIsEntrance();

    //       return true;
    //     }
    //   }

    //
    // binary search:
    //
    // int low = 0;
    // int high = (int)this->MapNodes.size() - 1;

    // while (low <= high) {
    //   int mid = low + ((high - low) / 2);
    //   long long nodeid = this->MapNodes[mid].getID();

    //   if (id == nodeid) {
    //     lat = this->MapNodes[mid].getLat();
    //     lon = this->MapNodes[mid].getLon();
    //     isEntrance = this->MapNodes[mid].getIsEntrance();

    //     return true;
    //   } else if (id < nodeid) {
    //     high = mid - 1;
    //   } else {
    //     low = mid + 1;
    //   }
    // }
    // //
    // // if get here, not found:
    // //
    // return false;
  }


//
// accessors / getters
//
int Nodes::getNumMapNodes() { return (int)this->MapNodes.size(); }
