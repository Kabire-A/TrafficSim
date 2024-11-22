
#include <iostream>
#include <time.h>
#include <iomanip>
#include <string>
#include <queue>
#include <list>
#include "Road.h"
#include "Vehicle.h"
#include "Car.h"
#include "Truck.h"
#include "Bus.h"
#include "Motorcycle.h"
#include "Place.h"
#include "Constants.h"
#include "TrafficLight.h"

void generate(list<Vehicle*> &v, Road r);
void simN(list<Vehicle*> &V, TrafficLight TLin);
void simS(list<Vehicle*> &V, TrafficLight TLin);
void simE(list<Vehicle*> &V, TrafficLight TLin);
void simW(list<Vehicle*>& V, TrafficLight TLin);

using namespace std;


int main()
{
	list<Vehicle*> N, S, E, W;

	// Set the random seed
	srand(time(0));

	// build a road North bound
	pair<int, int> nslocs[YMAX];

	for (int i = 0; i < YMAX; i++)
	{
		nslocs[i].first = XMAX / 2 + 1;
		nslocs[i].second = i;
	}

	Road north_bound(nslocs, YMAX, 0);  // 0 = north bound


	// build a road South bound

	for (int i = 0 ; i < YMAX; i++)
	{
		nslocs[i].first = XMAX / 2;
		nslocs[i].second = YMAX - i - 1;
	}

	Road south_bound(nslocs, YMAX, 1);  // 1 = south bound


	// build a road East bound
	pair<int, int> ewlocs[XMAX];

	for (int i = 0; i < XMAX; i++)
	{
		ewlocs[i].first = i;
		ewlocs[i].second = YMAX / 2;
	}

	Road east_bound(ewlocs, XMAX, 2);  // 2 = east bound
	
	// reset east bound so that it uses pre-existing intersection places
	vector<Place*> temp;
	for (int i = 0; i < XMAX; i++)
	{
		if (i == XMAX / 2)
		{
			temp.push_back(south_bound.getlane()[(YMAX / 2) - 1]);
			delete east_bound.getlane()[XMAX / 2];
		}
		else if (i == (XMAX / 2) + 1)
		{
			temp.push_back(north_bound.getlane()[YMAX / 2]);
			delete east_bound.getlane()[(XMAX / 2) + 1];
		}
		else
		{
			temp.push_back(east_bound.getlane()[i]);
		}
	}
	east_bound.getlane().clear();
	east_bound.setlane(temp, XMAX, 2);	// set road with reused intersections

	temp.clear();

	// generate pairs for west bound road
	for (int i = 0; i < XMAX; i++)
	{
		ewlocs[i].first = XMAX - i - 1;
		ewlocs[i].second = YMAX / 2 + 1;
	}

	Road west_bound(ewlocs, XMAX, 3);  // 3 = west bound

	// reset west bound so that it uses pre-existing intersection places
	for (int i = 0; i < XMAX; i++)
	{
		if (i == (XMAX / 2) - 2)
		{
			temp.push_back(north_bound.getlane()[(YMAX / 2) + 1]);
			delete west_bound.getlane()[(XMAX / 2) - 2];
		}
		else if (i == (XMAX / 2) - 1)
		{
			temp.push_back(south_bound.getlane()[(YMAX/2) - 2]);
			delete west_bound.getlane()[(XMAX / 2) - 1];
		}
		else
		{
			temp.push_back(west_bound.getlane()[i]);
		}
	}
	west_bound.getlane().clear();
	west_bound.setlane(temp, XMAX, 3);	// set road with reused intersection

	temp.clear();

	int inputgreen;
	cout << "How long would you like the green light time to be?: ";
	cin >> inputgreen;

	TrafficLight TL = TrafficLight(inputgreen, 0);

	int simtime = 0;
	cout << "For how long would you like to run the sim?: ";
	cin >> simtime;
	// let start putting vehicle into the lane
	// lane should be from YMAX/2 - 1 to 0

	for (int tm = 0; tm < simtime; tm++)
	{
		// check for new vehicle and place on road if generated
		generate(N, north_bound);
		generate(S, south_bound);
		generate(E, east_bound);
		generate(W, west_bound);

		{
			// no vehicle arrives
			// move the vehicles already in the queue forward if
			// the light is green
			int w = 60;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			cout << setw(w / 2) << "Time: " << tm << endl;
			TL.print((w / 2) + 4);

			// generate header and simulate northbound road
			cout << setw((w / 2) + 8) << "Northbound Vehicles" << endl;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			cout << setw(12) << "Vehicle  " << setw(9) << " X     Y " << setw(12) <<
				"Distance" << setw(7) << "Idle" << setw(9) << "Time" << endl;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			simN(N, TL);
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;

			// generate header and simulate southbound road
			cout << setw((w / 2) + 8) << "Southbound Vehicles" << endl;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			cout << setw(12) << "Vehicle  " << setw(9) << " X     Y " << setw(12) <<
				"Distance" << setw(7) << "Idle" << setw(9) << "Time" << endl;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			simS(S, TL);
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;

			// generate header and simulate eastbound road
			cout << setw((w / 2) + 8) << "Eastbound Vehicles" << endl;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			cout << setw(12) << "Vehicle  " << setw(9) << " X     Y " << setw(12) <<
				"Distance" << setw(7) << "Idle" << setw(9) << "Time" << endl;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			simE(E, TL);
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;

			// generate header and simulate westbound road
			cout << setw((w / 2) + 8) << "Westbound Vehicles" << endl;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			cout << setw(12) << "Vehicle  " << setw(9) << " X     Y " << setw(12) <<
				"Distance" << setw(7) << "Idle" << setw(9) << "Time" << endl;
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;
			simW(W, TL);
			cout << setfill('-') << setw(w) << "" << setfill(' ') << endl;

			TL.update();
			cout << endl;

		}
	}
	return 0;
}


/*
*	generate - takes a road and vehicle list and generates a vehicle
*	if the random roll is satisfied, then places it on the appropriate
*	space on the provided road
* 
*	@param v - the vehicle list that will be updated
*	@param r - the road the vehicle will be placed on
*/
void generate(list<Vehicle*> &v, Road r)
{
	int ncar = CAR_PROB * 1000;
	int ntruck = TRUCK_PROB * 1000;
	int nbus = BUS_PROB * 1000;
	int nmoto = MOTORCYCLE_PROB * 1000;

	int nrand = rand() % 1000;

	if (nrand < ncar)
	{
		// car arrives
		int index = 0;

		// insert car into road
		pair<int, int> temp;
		if (r.getdirection() == 'N')
		{
			index = r.getfreeplace(0);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = pair<int, int>(XMAX / 2 + 1, index);	
		}
		else if (r.getdirection() == 'S')
		{
			index = r.getfreeplace(1);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
		}
		else if (r.getdirection() == 'E')
		{
			index = r.getfreeplace(2);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
		}
		else
		{
			index = r.getfreeplace(3);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
		}
		Car* ncar = new Car(temp, 100, 50, r.getdirection());

		// point the place vehicle pointers to the car
		vector<Place*> temp_place = r.getlane();
		temp_place[index]->setvehicle(ncar);
		temp_place[index - 1]->setvehicle(ncar);


		// point each plaecptr in the car to the temp_place
		Place** temp_placeptr = ncar->getplace();
		temp_placeptr[0] = temp_place[index];  // front of car
		temp_placeptr[1] = temp_place[index - 1]; // back of car


		v.push_back(ncar);
	}
	else if (nrand >= ncar && nrand < (ntruck + ncar))
	{
		// truck arrives
		int index = 0;

		// insert truck into road
		pair<int, int> temp;
		pair<int, int> temp_dest;
		if (r.getdirection() == 'N')
		{
			index = r.getfreeplace(0);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = pair<int, int>(XMAX / 2 + 1, index);
			temp_dest = pair<int, int>(XMAX / 2 + 1, 999);
		}
		else if (r.getdirection() == 'S')
		{
			index = r.getfreeplace(1);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
			temp_dest = pair<int, int>(XMAX / 2, 0);
		}
		else if (r.getdirection() == 'E')
		{
			index = r.getfreeplace(2);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
			temp_dest = pair<int, int>(XMAX - 1, YMAX / 2 + 1);
		}
		else
		{
			index = r.getfreeplace(3);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
			temp_dest = pair<int, int>(XMAX - 1, YMAX / 2 + 1);
		}
		
		Truck* ntruck = new Truck(temp, 100, 50, r.getdirection(), 2000, temp_dest);

		// point the place vehicle pointers to the truck
		vector<Place*> temp_place = r.getlane();

		for (int i = 0; i < 5; i++)
		{
			temp_place[index - i]->setvehicle(ntruck);
		}

		// point each plaecptr in the truck to the temp_place
		Place** temp_placeptr = ntruck->getplace();

		for (int i = 0; i < 5; i++)
		{
			temp_placeptr[i] = temp_place[index - i];  // truck
		}

		v.push_back(ntruck);
	}
	else if (nrand >= (ntruck + ncar) && nrand < (ntruck + ncar + nbus))
	{
		// bus arrives
		int index = 0;

		// insert bus into road
		pair<int, int> temp;
		if (r.getdirection() == 'N')
		{
			index = r.getfreeplace(0);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = pair<int, int>(XMAX / 2 + 1, index);
		}
		else if (r.getdirection() == 'S')
		{
			index = r.getfreeplace(1);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
		}
		else if (r.getdirection() == 'E')
		{
			index = r.getfreeplace(2);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
		}
		else
		{
			index = r.getfreeplace(3);
			temp = r.getlane()[index]->getlocation();
		}

		Bus* nbus = new Bus(temp, 100, 50, r.getdirection(), "MBTA", 30);

		// point the place vehicle pointers to the bus
		vector<Place*> temp_place = r.getlane();

		for (int i = 0; i < 4; i++)
		{
			temp_place[index - i]->setvehicle(nbus);
		}

		// point each plaecptr in the truck to the temp_place
		Place** temp_placeptr = nbus->getplace();

		for (int i = 0; i < 4; i++)
		{
			temp_placeptr[i] = temp_place[index - i];  // bus
		}

		v.push_back(nbus);
	}
	else if (nrand >= (ntruck + ncar + nbus) &&
		nrand < (ntruck + ncar + nbus + nmoto))
	{
		// motorcycle arrives
		int index = 0;

		// insert motorcycle into road
		pair<int, int> temp;
		if (r.getdirection() == 'N')
		{
			index = r.getfreeplace(0);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = pair<int, int>(XMAX / 2 + 1, index);
		}
		else if (r.getdirection() == 'S')
		{
			index = r.getfreeplace(1);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
		}
		else if (r.getdirection() == 'E')
		{
			index = r.getfreeplace(2);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
		}
		else
		{
			index = r.getfreeplace(3);
			if (index == -1)
			{
				cout << "No more room on road!" << endl;
				return;
			}
			temp = r.getlane()[index]->getlocation();
		}

		Motorcycle* nmotor = new Motorcycle(temp, 100, 50, r.getdirection(), "Harley");

		// point the place vehicle pointers to the bus
		vector<Place*> temp_place = r.getlane();

		temp_place[index]->setvehicle(nmotor);

		// point each plaecptr in the motorcycle to the temp_place
		Place* temp_placeptr = nmotor->getplace();

		temp_placeptr = temp_place[index];
		nmotor->setplace(temp_placeptr);

		v.push_back(nmotor);
	}
}


/*
*	simN - iterates through the vehicle list and moves if the space ahead is clear,
*	and is not the intersection on a red light. It then outputs all related data
*	about the vehicle. If the end of the road is reached then the destrutor is 
*	called and the spaces it was attached to are freed
* 
*	@param V - the vehicle list to be iterated through
*	@param TLin - the traffic light of the intersection
*/
void simN(list<Vehicle*> &V, TrafficLight TLin)
{
	
	for (auto it = V.begin(); it != V.end(); it++)
	{
		if (dynamic_cast<Car*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Car*>(*it)->getplace()[0]->getnorth() == NULL)
			{
				dynamic_cast<Car*>(*it)->~Car();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Car*>(*it)->getplace()[0]->getnorth()->isoccupied())
			{
				if (!(dynamic_cast<Car*>(*it)->getplace()[0]->getnorth()->getlocation().second == YMAX / 2) || TLin.get_NS() == 0)
				{
					dynamic_cast<Car*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Car: ";
		}
		else if (dynamic_cast<Truck*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Truck*>(*it)->getplace()[0]->getnorth() == NULL)
			{
				dynamic_cast<Truck*>(*it)->~Truck();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Truck*>(*it)->getplace()[0]->getnorth()->isoccupied())
			{
				if (!(dynamic_cast<Truck*>(*it)->getplace()[0]->getnorth()->getlocation().second == YMAX / 2) || TLin.get_NS() == 0)
				{
					dynamic_cast<Truck*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Truck: ";
		}
		else if (dynamic_cast<Bus*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Bus*>(*it)->getplace()[0]->getnorth() == NULL)
			{
				dynamic_cast<Bus*>(*it)->~Bus();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Bus*>(*it)->getplace()[0]->getnorth()->isoccupied())
			{
				if (!(dynamic_cast<Bus*>(*it)->getplace()[0]->getnorth()->getlocation().second == YMAX / 2) || TLin.get_NS() == 0)
				{
					dynamic_cast<Bus*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Bus: ";
		}
		else if (dynamic_cast<Motorcycle*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Motorcycle*>(*it)->getplace()->getnorth() == NULL)
			{
				dynamic_cast<Motorcycle*>(*it)->~Motorcycle();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Motorcycle*>(*it)->getplace()->getnorth()->isoccupied())
			{
				if (!(dynamic_cast<Motorcycle*>(*it)->getplace()->getnorth()->getlocation().second == YMAX / 2) || TLin.get_NS() == 0)
				{
					dynamic_cast<Motorcycle*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Motorcycle: ";
		}
		(*it)->incrementExist();
		cout << setw(3) << (*it)->getlocation().first << setw(6) << (*it)->getlocation().second << setw(9) << (*it)->getdistance() << setw(9) <<
			(*it)->getidle() << setw(9) << (*it)->getexisttime() << endl;
	}
	
}


/*
*	simS - iterates through the vehicle list and moves if the space ahead is clear,
*	and is not the intersection on a red light. It then outputs all related data
*	about the vehicle. If the end of the road is reached then the destrutor is
*	called and the spaces it was attached to are freed
*
*	@param V - the vehicle list to be iterated through
*	@param TLin - the traffic light of the intersection
*/
void simS(list<Vehicle*> &V, TrafficLight TLin)
{

	for (auto it = V.begin(); it != V.end(); it++)
	{
		if (dynamic_cast<Car*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Car*>(*it)->getplace()[0]->getsouth() == NULL)
			{
				dynamic_cast<Car*>(*it)->~Car();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Car*>(*it)->getplace()[0]->getsouth()->isoccupied())
			{
				if (!(dynamic_cast<Car*>(*it)->getplace()[0]->getsouth()->getlocation().second == ((YMAX / 2) + 1)) || TLin.get_NS() == 0)
				{
					dynamic_cast<Car*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Car: ";
		}
		else if (dynamic_cast<Truck*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Truck*>(*it)->getplace()[0]->getsouth() == NULL)
			{
				dynamic_cast<Truck*>(*it)->~Truck();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Truck*>(*it)->getplace()[0]->getsouth()->isoccupied())
			{
				if (!(dynamic_cast<Truck*>(*it)->getplace()[0]->getsouth()->getlocation().second == ((YMAX / 2) + 1)) || TLin.get_NS() == 0)
				{
					dynamic_cast<Truck*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Truck: ";
		}
		else if (dynamic_cast<Bus*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Bus*>(*it)->getplace()[0]->getsouth() == NULL)
			{
				dynamic_cast<Bus*>(*it)->~Bus();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Bus*>(*it)->getplace()[0]->getsouth()->isoccupied())
			{
				if (!(dynamic_cast<Bus*>(*it)->getplace()[0]->getsouth()->getlocation().second == ((YMAX / 2) + 1)) || TLin.get_NS() == 0)
				{
					dynamic_cast<Bus*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Bus: ";
		}
		else if (dynamic_cast<Motorcycle*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Motorcycle*>(*it)->getplace()->getsouth() == NULL)
			{
				dynamic_cast<Motorcycle*>(*it)->~Motorcycle();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Motorcycle*>(*it)->getplace()->getsouth()->isoccupied())
			{
				if (!(dynamic_cast<Motorcycle*>(*it)->getplace()->getsouth()->getlocation().second == ((YMAX / 2) + 1)) || TLin.get_NS() == 0)
				{
					dynamic_cast<Motorcycle*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Motorcycle: ";
		}
		(*it)->incrementExist();
		cout << setw(3) << (*it)->getlocation().first << setw(6) << (*it)->getlocation().second << setw(9) << (*it)->getdistance() << setw(9) <<
			(*it)->getidle() << setw(9) << (*it)->getexisttime() << endl;
	}

}

/*
*	simE - iterates through the vehicle list and moves if the space ahead is clear,
*	and is not the intersection on a red light. It then outputs all related data
*	about the vehicle. If the end of the road is reached then the destrutor is
*	called and the spaces it was attached to are freed
*
*	@param V - the vehicle list to be iterated through
*	@param TLin - the traffic light of the intersection
*/
void simE(list<Vehicle*> &V, TrafficLight TLin)
{

	for (auto it = V.begin(); it != V.end(); it++)
	{
		if (dynamic_cast<Car*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Car*>(*it)->getplace()[0]->geteast() == NULL)
			{
				dynamic_cast<Car*>(*it)->~Car();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Car*>(*it)->getplace()[0]->geteast()->isoccupied())
			{
				if (!(dynamic_cast<Car*>(*it)->getplace()[0]->geteast()->getlocation().first == (XMAX / 2)) || TLin.get_EW() == 0)
				{
					dynamic_cast<Car*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Car: ";
		}
		else if (dynamic_cast<Truck*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Truck*>(*it)->getplace()[0]->geteast() == NULL)
			{
				dynamic_cast<Truck*>(*it)->~Truck();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Truck*>(*it)->getplace()[0]->geteast()->isoccupied())
			{
				if (!(dynamic_cast<Truck*>(*it)->getplace()[0]->geteast()->getlocation().first == (XMAX / 2)) || TLin.get_EW() == 0)
				{
					dynamic_cast<Truck*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Truck: ";
		}
		else if (dynamic_cast<Bus*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Bus*>(*it)->getplace()[0]->geteast() == NULL)
			{
				dynamic_cast<Bus*>(*it)->~Bus();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Bus*>(*it)->getplace()[0]->geteast()->isoccupied())
			{
				if (!(dynamic_cast<Bus*>(*it)->getplace()[0]->geteast()->getlocation().first == (XMAX / 2)) || TLin.get_EW() == 0)
				{
					dynamic_cast<Bus*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Bus: ";
		}
		else if (dynamic_cast<Motorcycle*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Motorcycle*>(*it)->getplace()->geteast() == NULL)
			{
				dynamic_cast<Motorcycle*>(*it)->~Motorcycle();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Motorcycle*>(*it)->getplace()->geteast()->isoccupied())
			{
				if (!(dynamic_cast<Motorcycle*>(*it)->getplace()->geteast()->getlocation().first == (XMAX / 2)) || TLin.get_EW() == 0)
				{
					dynamic_cast<Motorcycle*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			
			cout << setw(12);
			cout << "Motorcycle: ";
		}
		(*it)->incrementExist();
		cout << setw(3) << (*it)->getlocation().first << setw(6) << (*it)->getlocation().second << setw(9) << (*it)->getdistance() << setw(9) <<
			(*it)->getidle() << setw(9) << (*it)->getexisttime() << endl;
	}

}

/*
*	simW - iterates through the vehicle list and moves if the space ahead is clear,
*	and is not the intersection on a red light. It then outputs all related data
*	about the vehicle. If the end of the road is reached then the destrutor is
*	called and the spaces it was attached to are freed
*
*	@param V - the vehicle list to be iterated through
*	@param TLin - the traffic light of the intersection
*/
void simW(list<Vehicle*>& V, TrafficLight TLin)
{
	// iterate through list till it is empty
	for (auto it = V.begin(); it != V.end(); it++)
	{
		// check the vehicle type
		if (dynamic_cast<Car*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Car*>(*it)->getplace()[0]->getwest() == NULL)
			{
				dynamic_cast<Car*>(*it)->~Car();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Car*>(*it)->getplace()[0]->getwest()->isoccupied())
			{
				if (!(dynamic_cast<Car*>(*it)->getplace()[0]->getwest()->getlocation().first == (XMAX / 2) + 1) || TLin.get_EW() == 0)
				{
					dynamic_cast<Car*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Car: ";
		}
		else if (dynamic_cast<Truck*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Truck*>(*it)->getplace()[0]->getwest() == NULL)
			{
				dynamic_cast<Truck*>(*it)->~Truck();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Truck*>(*it)->getplace()[0]->getwest()->isoccupied())
			{
				if (!(dynamic_cast<Truck*>(*it)->getplace()[0]->getwest()->getlocation().first == (XMAX / 2) + 1) || TLin.get_EW() == 0)
				{
					dynamic_cast<Truck*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Truck: ";
		}
		else if (dynamic_cast<Bus*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Bus*>(*it)->getplace()[0]->getwest() == NULL)
			{
				dynamic_cast<Bus*>(*it)->~Bus();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Bus*>(*it)->getplace()[0]->getwest()->isoccupied())
			{
				if (!(dynamic_cast<Bus*>(*it)->getplace()[0]->getwest()->getlocation().first == (XMAX / 2) + 1) || TLin.get_EW() == 0)
				{
					dynamic_cast<Bus*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			cout << setw(12);
			cout << "Bus: ";
		}
		else if (dynamic_cast<Motorcycle*>(*it) != nullptr)
		{
			// check if the vehicle has reached end of road, call destructor if true
			if (dynamic_cast<Motorcycle*>(*it)->getplace()->getwest() == NULL)
			{
				dynamic_cast<Motorcycle*>(*it)->~Motorcycle();
				it = V.erase(it);
				cout << "Vehicle Leaving the road" << endl;
				continue;
			}
			// check if next space is occupied then check if red light at intersection, if both false then move
			else if (!dynamic_cast<Motorcycle*>(*it)->getplace()->getwest()->isoccupied())
			{
				if (!(dynamic_cast<Motorcycle*>(*it)->getplace()->getwest()->getlocation().first == (XMAX / 2) + 1) || TLin.get_EW() == 0)
				{
					dynamic_cast<Motorcycle*>(*it)->move();
				}
				else
				{
					(*it)->incrementIdle();	// if not moving then increment idle time
				}
			}
			else
			{
				(*it)->incrementIdle();	// if not moving then increment idle time
			}
			
			cout << setw(12);
			cout << "Motorcycle: ";
		}
		(*it)->incrementExist();
		cout << setw(3) << (*it)->getlocation().first << setw(6) << (*it)->getlocation().second << setw(9) << (*it)->getdistance() << setw(9) <<
			(*it)->getidle() << setw(9) << (*it)->getexisttime() << endl;
	}

}