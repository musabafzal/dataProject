# dataproject

/*  MakeFlightNode  create a flight node from the given info */
FlightType *MakeFlightNode(int FlightNo, char *startCity, 
 			 int timeDepart, char *endCity, int timeArrival);
#done
/*  ReadFlightData  make a flight database from scratch. Some examples are shown */
void ReadFlightData(){
}
#done
/* DisplayFlightInfo   display a particular flight info in tabular form  */
void DisplayFlightInfo(FlightType * flight){
/* For example following data is displayed
       111	 Lahore	700	Karachi	830
*/
}
#done

/* DisplayFlightInfo   display all flights info in tabular form */
void DisplayAllFlightsData(){
/*  makes use of the function named DisplayFlightInfo().
*/
}
#done

/*  FlightByNumber  return info about a flight given its flight number  */
FlightType * FlightByNumber(int FlightNo)
#done
/*  DisplayAllCities  Show a list of all the cities serviced by airline in a tabular form   */
void DisplayAllCities();
#done
/* DisplayCitiesFrom  Show a list of cities which can be reached from a particular city. */
void DisplayCitiesFrom(char *startCity){
/* This function will make use of depth first search (DFS) graph traversal algorithm.*/
}
#done
/* DisplayShortestPath  Show the list of cities in the shorted path between any two cities. */
void DisplayShortestPath(char *startCity, char *endCity){
/* This function will make use of a shortest path algorithm like Dijkstra’s shortest path algorithm or Floyd -Warshal Algorithm. The shortest path means the route taking shortest time from source to destination. */
 }

/*CityDepartureList  return a sorted list of departures for a city    */
FlightType *CityDepartureList(char *cityName);
#done
/*  CityArrivalList  return a sorted list of arrivals for a city  */
FlightType * CityArrivalList(char *cityName);
#done
/* DisplayDepartureList  Show flight departures for a city listed in order of time. */
void DisplayDepartureList(char *cityName){
    /* This function makes use of the function CityDepartureList(cityName) */
}
#done
/*DisplayArrivalList  Show flight arrivals for a city listed in order of time. */
void DisplayArrivalList(char *cityName){
   /* This function makes use of the function CityArrivalList(cityName) */
}
#done
/ * MakeReserveNode  create a reservation node from the given info */
ReservationType MakeReserveNode(char *firstName, char *lastName,
		 int tripType, RouteType route1, RouteType route2);

/* FindRoute  find a route from city1 to city2 and put it in the route structure, which is passed by 
		 reference here.
                                      Return 0 if a route is found and 
                                      Return -1 if no route could be found */
									  
int findRoute(char *startCity, char *endCity, RouteType &route){

/* The algorithm for FindRoute() will be as follows:
 
1.	Get the list of departures for startCity and if there exist any direct flights to endCity then pick one of the flights and return it.

2.	If no direct flights exist then compare the departure list for startCity with the arrival list for endCity. Try to find a city in common to both lists to use for connections. As a constraint, the second flight must leave at least MINLAYOVER minutes (default of 30) after the first flight arrives. Return any valid connection.

3.	If no flight combinations exist then report that reservation system will not be able to handle the passenger's travel needs and do not make the reservation. 
*/
 }

/* MakeReservation  make a reservation for a passenger by reading info from the user. */

void MakeReservation(Flights &flightdb){

/* In the function, you will need to gather the name of the passenger and the departure city along with the type of travel (round trip or one-way) and the day(s) of travel. For each trip you will need to see if a flight can be booked based on the flight database. Passengers prefer direct flights between cities, but will accept a trip with one connecting flight. By default passengers will accept any trip you give them on the day of travel (no preferences for the time of day). 

The function makes use of the functions FindRoute()and MakeReserveNode(). */
}

/* printRoute  prints the route stored in variable route  */
void printRoute(int ifExists, RouteType route);


/* PrintReservation  prints the reservation schedule, as pointed by  pReserve */
PrintReservation(ReservationType *pReserve)

/* PrintAllReservations  prints all the reservations in the database */
PrintAllReservations()

/* PrintPassengers  print the list of all passengers on a particular flight  */
void PrintPassengers(int FlightNo);

/* PrintSchedule  prompt the user for a passenger’s (first and second) name and print that passenger's schedule. */
void PrintSchedule(){
   /* This function makes use of the function PrintReservation() */
}

/* DeleteReserve  delete a reservation for a passenger by prompting for name  */
void DeleteReserve()
