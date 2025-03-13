/*
Name: Melissa Swinehart
 Description: Create mercenary mode from Resident Evil 3 using input/simulation files
 Section: 1003
 Assignment: 7
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "priorityQ.h"

using namespace std;

struct mercType
{
// Tracks how many of each monster is defeated and civilian saved for a mercenary
int zombies;
int spiders;
int drainDeimos;
int zombieDogs;
int hunters;
int nemesis;
int civilians;

 // Default Constructor: Initialize all to 0 for clean slate
mercType() {
 zombies = 0;
 spiders = 0;
 drainDeimos = 0;
 zombieDogs = 0;
 hunters = 0;
 nemesis = 0;
 civilians = 0;
}

 // Parameterized Constructor (Helper Function)
 mercType(string & subject, int quantity): mercType() {
 if(subject == "zombies") {
  zombies = quantity;
 }else if(subject == "spiders"){
  spiders = quantity;
 }else if(subject == "drainDeimos"){
  drainDeimos = quantity;
 }else if(subject == "zombieDogs") {
  zombieDogs = quantity;
 }else if(subject == "hunters") {
  hunters = quantity;
 }else if(subject == "nemesis") {
  nemesis = quantity;
 }else if(subject == "civilians") {
  civilians = quantity;
 }

}

 // Create a function (rather than overload <<) to compute the scores of mercenaries (Helper Function)
 double getScore() const{
 return (zombies * 1.0) + (spiders * 1.1) +
  (drainDeimos * 1.2) + (zombieDogs * 1.3) + (hunters * 1.4) +
   (nemesis * 1.5) + (civilians * 2.0);
}

// Operator Overload: ">" Compare two mercType objects and determine which mercenary has a higher score
// Used in bubbleUp & bubbleDown
 bool operator > ( const mercType & rhs ) const {
 // Call getScore to compare the scores of both objects *this (current object) and rhs (object passed in to compare)
 double currentMerc = this->getScore(); // Pointer to object
 double otherMerc = rhs.getScore();  // Reference to mercType object

 // If the current object has a higher score than the rhs object, return true, else false
 if (currentMerc > otherMerc) {
  return true;
 } else {
  return false;
 }
}

 // Operator Overload: "+=": Increments/Updates each score of the current mercenary by adding onto from rhs object
 // Used in increaseKey
 mercType & operator += ( const mercType & rhs ) {
 zombies += rhs.zombies;
 spiders += rhs.spiders;
 drainDeimos += rhs.drainDeimos;
 zombieDogs += rhs.zombieDogs;
 hunters += rhs.hunters;
 nemesis += rhs.nemesis;
 civilians += rhs.civilians;
 return *this; // Return the current updated object
}


};


int main() {
 // Declare priorityQ "mercenaries"
 priorityQ < string , mercType > mercenaries;

 // Prompt user to open mercenaries file
 cout << "Enter mercenaries file: ";
 string fileName;
 cin >> fileName;
 ifstream inFile;
 inFile.open(fileName);

 // Read each mercenary (one name/line terminated by end of line character
 string mercenaryName;
 while(inFile >> mercenaryName) {
   mercenaries.push_back(mercenaryName, mercType()); // Insert into priorityQ using name as first arg and default object as second arg
 }
 // Close File
 inFile.close();
 cout << endl;

 // Open simulation file
 cout << "Enter simulation file: ";
 string simFile;
 cin >> simFile;
 ifstream inFile2;
 inFile2.open(simFile);
 cout << endl;

 // Variables for simulation
 string subject;
 int quantity;
 string inLead = " ";

 // Read each line and update mercenary's monster/civilian amount passing into increaseKey
 while(inFile2 >> mercenaryName >> subject >> quantity) {

  // Create temporary object
  mercType temp(subject, quantity);
  // Call increaseKey to update priority
  mercenaries.increaseKey(mercenaryName, temp);
  string newLead = mercenaries.get_front_key();

  // Output the new leader if there is one
  if(newLead != inLead) {
   cout << endl;
   cout << "We have a new leader: " <<  mercenaries.get_front_key() << " Score: "
   << fixed << setprecision(1) << mercenaries.get_front_priority().getScore() << endl;
   // Update inLead to the new leader
   inLead = newLead;
  }
 }
 // Close file
inFile2.close();
 cout << endl;

 // Output the ranks from 1 to the amount of mercenaries along with mercenary's name and their score
 int ranks = 1;
 while(!mercenaries.isEmpty()) {
  cout << "Rank " << ranks << endl;
  cout << "Name: " << mercenaries.get_front_key()  << " Score: " << fixed
  << setprecision(1) << mercenaries.get_front_priority().getScore() << endl;
  cout << endl;
  mercenaries.pop_front();
  ranks++;
 }

 return 0;
}
