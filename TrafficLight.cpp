#include <iostream>
#include <iomanip>
#include "TrafficLight.h"

using namespace std;

/*
* TrafficLight - constructor that takes in yellow timer, and green timer.
* Also decides which light is green first
* 
* @param gIn - length of green light
* @param start - 0 is start NS green, anything else is EW green first
*/
TrafficLight::TrafficLight( int gIn, int start)
{
	ytimer = 6;	// yellow is 6 b/c that is min time to clear intersection given by lab doc
	gtimer = gIn;
	rtimer = gIn + ytimer;

	if (start == 0)
	{
		NS_Light = 0;
		EW_Light = 2;
		counter = rtimer;
	}
	else
	{
		NS_Light = 2;
		EW_Light = 0;
		counter = rtimer * 2;
	}
}

// get_NS returns NS light state, 0-green, 1-yellow, 2-red
int TrafficLight::get_NS()
{
	return NS_Light;
}

// get_EW returns NS light state, 0-green, 1-yellow, 2-red
int TrafficLight::get_EW()
{
	return EW_Light;
}

/*
*	update - increment counter and reset when reaches 0, changes light
*	when the timer indicate to
*
*/
void TrafficLight::update()
{
	counter -= 1;

	if (counter == 0)
	{
		counter = rtimer * 2;
	}

	if (counter == rtimer * 2)
	{
		NS_Light = 2;
		EW_Light = 0;
	}
	else if (counter == (rtimer * 2) - gtimer)
	{
		EW_Light = 1;
	}
	else if (counter == rtimer)
	{
		NS_Light = 0;
		EW_Light = 2;
	}
	else if (counter == rtimer - gtimer)
	{
		NS_Light = 1;
	}

	return;
}

/*
*	print - prints the current light status
* 
*	@param w - used to decide the setw() for formatting
*/
void TrafficLight::print(int w)
{
	if (NS_Light == 0)
	{
		cout << setw(w) << "NS: Green  " << endl;
	}
	else if (NS_Light == 1)
	{
		cout << setw(w) << "NS: Yellow" << endl;
	}
	else
	{
		cout << setw(w) << "NS: Red   " << endl;
	}

	if (EW_Light == 0)
	{
		cout << setw(w) << "EW: Green  " << endl;
	}
	else if (EW_Light == 1)
	{
		cout << setw(w) << "EW: Yellow" << endl;
	}
	else
	{
		cout << setw(w) << "EW: Red   " << endl;
	}
}
