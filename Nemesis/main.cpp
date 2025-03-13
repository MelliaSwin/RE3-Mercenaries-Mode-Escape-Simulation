/*
Name: Melissa Swinehart
 Description: RE3: Design a graph theory problem that simulates Jill escaping RPD
 Section: 1003
 Assignment: 8
 */

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <fstream>

using namespace std;

// Recursive Function: DFS type Traversal, find path from WestStairway1F to Courtyard
bool escapeRPD (
 string jillsLocation ,
 string roomNeedToReach ,
 int jillsHealth ,
 unordered_map < string , list < string > > rpdMap ,
 unordered_map < string , string > & predecessor ,
 unordered_map < string , int > & healthInRoom ,
 unordered_map < string , int > nemesisLocations )
{

 // Adjust Jill's health based on location
 if(nemesisLocations[jillsLocation]) {
  jillsHealth -= nemesisLocations[jillsLocation];
 }

 // If Jill died, return false
 if(jillsHealth <= 0) {
  return false;
 }

 // Store the health Jill had when she entered the room
 healthInRoom[jillsLocation] = jillsHealth;

 // Check if Jill reached "Courtyard"
 if(jillsLocation == roomNeedToReach) {
  return true;
 }

 // Move onto neighboring rooms
 for(auto neighbor:rpdMap[jillsLocation]) {
  if(escapeRPD(neighbor, "Courtyard", jillsHealth, rpdMap, predecessor,
   healthInRoom, nemesisLocations)) {
   // If true, add room to predecessor to construct safe path (reversed)
   predecessor[neighbor] = jillsLocation;
   return true;
  }
 }
 // No safe path found
 return false;
}


int main(int argc, char *argv[]) {
 // Open RPD.txt (rpdFile)
  ifstream rpdFile(argv[1]);
 // Open Nemesis0#.txt (nemesisFile)
  ifstream nemesisFile(argv[2]);

 // Initialize Structures Needed
 // rpdMap == Adjacency list
 unordered_map<string, list<string> > rpdMap; // Maps room name to list of neighbors (each neighbor -> another room)
 unordered_map<string, int> nemesisLocations; // Maps room name to either Nemesis or healing item (determined values)
 unordered_map<string, string> predecessor; // Used to construct a path that leads to "Courtyard"
 unordered_map<string, int> healthInRoom; // Stores the max health Jill had when she entered the room ("Visited" Array/Map)


 // Two strings used for storing the room names
 string from;
 string destination;
 // Populate the rpdMap (string:string)
 while(rpdFile >> from >> destination) {
  rpdMap[from].push_back(destination);
 }
 // Close rpd.txt
 rpdFile.close();

 // Two strings used for storing the room nemesis is in and a value
 string location;
 int value;
 // Populate nemesisLocations and its value (string:int)
 while (nemesisFile >> location >> value) {
  nemesisLocations[location] = value;
 }
 // Close nemesis0#.txt
 nemesisFile.close();

 // Call Function
 bool possibleEscape = escapeRPD("WestStairway1F", "Courtyard", 20,
  rpdMap, predecessor, healthInRoom, nemesisLocations);

 // If true, relay true all the way to the main and output the path using predecessor map
 if(possibleEscape) {
  // Predecessor is in reverse order!
  // Store values from predecessor map
  list <string> safePath;
  string room = "Courtyard";
  while(room != "WestStairway1F") {
   safePath.push_back(room);
   room = predecessor[room];
  }
  // Output safePath
  cout << "Path: WestStairway1F";
  for(auto it = safePath.end(); it != safePath.begin();) {
   --it;
   cout << " -> " << *it;

 }
  cout << endl;
  cout << endl << "Somehow...I'm still alive..." << endl;

 } else {
 cout << "STARS!!!" << endl;
 }

 return 0;
}