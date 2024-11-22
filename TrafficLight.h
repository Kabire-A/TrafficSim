#pragma once

#ifndef TRAFFICLIGHT_H

#include <iostream>

using namespace std;

#define TRAFFICLIGHT_H

class TrafficLight
{
private:
	// for lights
	// 0 - green, 1 - yellow, 2 - red
	int NS_Light;
	int EW_Light;
	int gtimer;
	int ytimer;
	int rtimer;
	int counter;
public:
	TrafficLight(int gIn, int start);
	int get_NS();
	int get_EW();
	void update();
	void print(int w);
};

#endif // !TRAFFICLIGHT_H

