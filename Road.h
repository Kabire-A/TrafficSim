#pragma once

#ifndef ROAD_H

#include <iostream>
#include <vector>
#include "Place.h"
#include "Constants.h"

using namespace std;

#define ROAD_H

class Road
{
private:
	vector<Place*> lane;
	char direction;
	// 0 - north boud; 1 - south bound; 2 - east bound; 3 - west
public:
	Road();
	Road(pair<int, int> locations[], int nplaces, int dir);
	vector<Place*> getlane();
	void setlane(vector<Place*> loc, int nplaces, int dir);
	//void setintersection(Road&, Road&);
	char getdirection() const;
	void setdirection(char c);
	int getfreeplace(int dir);
};


#endif