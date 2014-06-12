/* File: UniversalHealthCoverage.cpp
 *
 * A program that determines whether or not it is possible to provide
 * coverage to everyone using a fixed number of hospitals.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */

Set<string> loadCities();
Vector < Set<string> > loadHospitals(int numHospitals);
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);
void displayHospitals(Vector< Set<string> > result);
Vector<Vector< Set<string> > > combinationsOf(Vector< Set<string> >& s, int n); 



int main() {
	int nLocations = getInteger("Enter the number of possible locations: ");
	int numHospitals = getInteger("Enter the maximum number of hospitals: ");
	Set<string> cities = loadCities();
	Vector< Set<string> > locations = loadHospitals(nLocations);
	Vector< Set<string> > result;
	if(canOfferUniversalCoverage(cities, locations, numHospitals, result)){
		cout << "You can cover all of the cities: " << endl;
		displayHospitals(result);
	}else{
		cout << "It's not possible to cover all the cities.";
	}
	return 0;
}


/* Loads cities to provide coverage to */
Set<string> loadCities(){
	cout << "Enter cities (Press Enter 2X to finish): " << endl;
	
	Set<string> cities;
	while(true){
		string city = getLine();
		if (city == ""){
			break;
		}
		cities += city;
	}
	return cities;
}

/* Loads the hospital locations */
Vector < Set<string> > loadHospitals(int numHospitals){
	Vector< Set<string> > result;
	
	// Builds all of the locations
	for(int n = 0; n < numHospitals; n ++){
		Set<string> locations;
		cout << "Enter the cities you that hospital " << n << " can cover. (Press Enter 2X to finish)" << endl;
		// Builds the locations of that hospital n can cover
		while (true){
			string city = getLine();
			if (city == ""){
				break;
			}
			locations.add(city);
		}
		
		// Adds all the locations
		result.add(locations);
	}
	return result;
}


/* Returns whether it's possible to provide coverage to all of the cities*/
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result) {
	// If there are no cities they can always be covered
	if(cities.size() == 0){
		return true;
	// If there are cities and no hospitals can be afforded they cannot be covered
	}else if(numHospitals == 0){
		return false;
	// If there are no locations to build	
	}else if (locations.size() == 0){
		return false;
	}else{
		
		//Cities that won't be covered by hospital 0
		Set<string> citiesToCover = cities;
		foreach(string city in locations[0]){
			citiesToCover.remove(city);
		}
		
		// Remaining hospitals
		Vector< Set<string> > remainingLocations = locations;
		remainingLocations.removeAt(0);
		// If using hospital 0 is correct, add it to result
		if(canOfferUniversalCoverage(citiesToCover,remainingLocations,numHospitals - 1, result)){
			result.add(locations[0]);
			return true;
		}	
		// Don't add it if it shouldn't be used	
		//}else if(canOfferUniversalCoverage(cities,remainingLocations,numHospitals,result)){
		//	return true;
		//}
		return //canOfferUniversalCoverage(citiesToCover,remainingLocations,numHospitals - 1, result) ||
		canOfferUniversalCoverage(cities,remainingLocations,numHospitals,result);
	}	
	return false;
		
}	

/* Displays how all the cities can be covered */
void displayHospitals(Vector< Set<string> > result){
	int i = 0;
	foreach(Set<string> hospital in result){
		cout << "Build the hospital that will cover:" << endl;
		foreach(string city in hospital){
			cout << "	" << city << endl;
		}
		i++;
	}
}




