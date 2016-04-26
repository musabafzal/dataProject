#include <iostream>
#include <string.h>
#include <iomanip>
#define MAXCITY 30    
using namespace std;
struct FlightType {
    int FlightNo;            	/* flight number */
    char *startCity;          	/* departure city */
    int timeDepart;          	/* departure time hhmm, e.g. 830, 1220, etc. */
    char *endCity;          	/* arrival city */
    int timeArrival;           	/* arrival time hhmm, e.g. 950, 1240, etc. */
    int noOfPassengers;       	/* number of passengers on the flight */
    FlightType *nextDeparture; 	/* next departure node from this city */
    FlightType *nextArrival; 	/* next arrival node to this city */
};


struct CityListType {
    char *cityName;           	   /* name of the city */
    FlightType *nextDeparture;    /* first departure from this city */
    FlightType *nextArrival;      /* first arrival to this city */
};

struct RouteType {
    int Day;                  /* day of travel: mmdd */
    int nHops;                /* Number of hops (1 or 2) */
    int FlightNo1;            /* Flight number of first hop */
    int FlightNo2;            /* Flight number of second hop (if needed) */
};

#define ROUNDTRIP 0
#define ONEWAY 1
struct ReservationType {
    char *firstName;              /* first name of passenger */
    char *lastName;               /* last name of passenger */
    int tripType;                 /* ROUNDTRIP or ONEWAY */
    RouteType route1;             /* first route */
    RouteType route2;             /* second route (only if ROUNDTRIP) */
    ReservationType *nextReserve; /* next reservation in linked list */
};

ReservationType *reserveHead,*reserveTail; /* head and tail of the reservation list */
#define MAXFLIGHT 200             /* maximum number of flights to maintain */
struct FlightNumberListType {
    int FlightNo;             /* flight number */
    FlightType *flight;        /* flight node for this type */
};

FlightNumberListType flightList[MAXFLIGHT];  /* array of flights */
CityListType cityList[MAXCITY];  /* array of cities */
void init()
{
	for(int i=0; i<MAXCITY; i++)
	{
		cityList[i].cityName=NULL;
	}
}
FlightType *nextDp(FlightType *newPtr)
{
	int i=0;
	for(i=0; i<MAXCITY; i++)
	{
		if(!(strcmp(cityList[i].cityName,newPtr->startCity)))
		break;
	}
	
	FlightType *tmp=cityList[i].nextDeparture;
	if(tmp==NULL)
	{
		cityList[i].nextDeparture=newPtr;
		return 0;
	}
	else
	{
	for(; tmp->nextDeparture!=NULL; tmp=tmp->nextDeparture)
	{
		if(newPtr->timeDepart<tmp->nextDeparture->timeDepart)
		{
		newPtr->nextDeparture=tmp->nextDeparture;
	    tmp->nextDeparture=newPtr;
		return newPtr->nextDeparture;
		}
	}
	if(newPtr->timeDepart>tmp->timeDepart)
	{
	newPtr->nextDeparture=NULL;
	tmp->nextDeparture=newPtr;
    return NULL;
    }
    else
    {
    	newPtr->nextDeparture=tmp;
    	tmp=newPtr;
    	return newPtr->nextDeparture;
	}
  }
}
FlightType *nextAr(FlightType *newPtr)
{
	
	int i=0;
	for( i=0; i<MAXCITY; i++)
	{
		
		if(!(strcmp(cityList[i].cityName,newPtr->endCity)))
		break;
	}
	
	FlightType *tmp=cityList[i].nextArrival;
	if(tmp==NULL)
	{
		
		cityList[i].nextArrival=newPtr;
		return NULL;
	}
	else
	{
	for(; tmp->nextArrival!=NULL; tmp=tmp->nextArrival)
	{
		if(newPtr->timeArrival<tmp->nextArrival->timeArrival)
		{
		
		newPtr->nextArrival=tmp->nextArrival;
	    tmp->nextArrival=newPtr;
	    return newPtr->nextArrival;
		
	   }
	}
	if(newPtr->timeArrival>tmp->timeArrival)
	{
			newPtr->nextArrival=NULL;
	    tmp->nextArrival=newPtr;
	    return NULL;
	}
	else
	{
		newPtr->nextArrival=tmp;
		tmp=newPtr;
		return newPtr->nextArrival;
	}
    }
}
int top=-1;
void map(char *s)
{
	cityList[++top].cityName=new char[strlen(s)+1];
	cityList[top].cityName=s;
}
FlightType *MakeFlightNode(int FlightNo, char *startCity, int timeDepart, char *endCity, int timeArrival){
	
	FlightType *newPtr =new FlightType;
	newPtr->FlightNo=FlightNo;
	newPtr->startCity=new char[strlen(startCity)+1];
	newPtr->startCity=startCity;
	newPtr->timeDepart=timeDepart;
	newPtr->endCity=new char[strlen(endCity)+1];
	newPtr->endCity=endCity;
	newPtr->timeArrival=timeArrival;
	newPtr->nextDeparture=nextDp(newPtr);
	newPtr->nextArrival=nextAr(newPtr);
	return newPtr;
}

void ReadFlightData(){
	flightList[0].FlightNo = 111;
	flightList[1].FlightNo = 222;
	flightList[2].FlightNo = 333;
	flightList[3].FlightNo = 321;
	flightList[4].FlightNo = 444;
	flightList[5].FlightNo = 555;
	flightList[6].FlightNo = 666;
	flightList[7].FlightNo = 699;
	flightList[8].FlightNo = 777;
	flightList[9].FlightNo = 888;
	flightList[10].FlightNo = 999;
	flightList[11].FlightNo = 101;
	flightList[12].FlightNo = 102;
	flightList[13].FlightNo = 103;
	flightList[14].FlightNo = 123;
	flightList[15].FlightNo = 456;
	flightList[16].FlightNo = 789;
	flightList[17].FlightNo = 987;
	flightList[18].FlightNo = 654;
	flightList[19].FlightNo = 201;
	flightList[20].FlightNo = 301;
	map("Islamabad");
	map("Lahore");
	map("Karachi");
	map("Bahawalpur");
	map("Quetta");
	map("UAE");
	map("Peshawar");
	flightList[0].flight=MakeFlightNode(111,"Lahore", 1500, "Karachi", 1630);
	flightList[1].flight=MakeFlightNode(222,"Lahore", 800, "Peshawar",845);
	flightList[2].flight=MakeFlightNode(333,"Lahore", 900, "Quetta", 1030);
	flightList[3].flight=MakeFlightNode(321,"Lahore", 1900, "Bahawalpur", 1930);
	flightList[4].flight=MakeFlightNode(444,"Karachi", 1500, "Quetta", 1600);
	flightList[5].flight=MakeFlightNode(555,"Karachi", 1520, "Peshawar", 1700);
	flightList[6].flight=MakeFlightNode(666,"Karachi", 1100, "Lahore", 1230);
	flightList[7].flight=MakeFlightNode(699,"Karachi", 2100, "UAE", 2230);
	flightList[8].flight=MakeFlightNode(777,"Quetta", 1700, "Lahore", 1830);
	flightList[9].flight=MakeFlightNode(888,"Quetta", 1800, "Karachi", 1900);
	flightList[10].flight=MakeFlightNode(999,"Quetta", 830, "Islamabad", 1100);
	flightList[11].flight=MakeFlightNode(101,"Peshawar", 1200, "Lahore", 1245);
	flightList[12].flight=MakeFlightNode(102,"Peshawar", 1300, "Karachi", 1440);
	flightList[13].flight=MakeFlightNode(103,"Peshawar", 1800, "Islamabad", 1830);
	flightList[14].flight=MakeFlightNode(123,"Islamabad", 700, "Karachi", 840);
//	cout<<cityList[0].nextDeparture->timeDepart<<endl;
	flightList[15].flight=MakeFlightNode(456,"Islamabad", 1100, "Peshawar", 1125);
	flightList[16].flight=MakeFlightNode(789,"Islamabad", 1130, "Quetta", 1200);
	flightList[17].flight=MakeFlightNode(987,"Islamabad", 1930, "Bahawalpur", 2030);
	//cout<<flightList[14].flight->nextDeparture->timeDepart<<endl;
	flightList[18].flight=MakeFlightNode(654,"Bahawalpur", 1230, "Islamabad", 1330);
	flightList[19].flight=MakeFlightNode(201,"Bahawalpur", 1300, "Lahore", 1330);
	flightList[20].flight=MakeFlightNode(301,"UAE", 1250, "Karachi", 1420);
//	cout<<"Flag2\n";
	
}
FlightType *CityDepartureList(char *cityName){
	int i=0;   FlightType *tmp;
	for(i=0; i<MAXCITY; i++)
	{
		if(!(strcmp(cityList[i].cityName,cityName)))
		break;
	}
	return cityList[i].nextDeparture;
	
}
void DisplayDepartureList(char *cityName){
	FlightType *tmp=CityDepartureList(cityName);
	cout<<endl<<cityName<<endl<<"Departure List :\n";
	for(; tmp!=NULL; tmp=tmp->nextDeparture)
	{
		cout<<"To  "<<tmp->endCity<<"   at  "<<tmp->timeDepart<<endl;
	}
	cout<<endl<<endl;

}
FlightType * CityArrivalList(char *cityName){
	int i=0;   FlightType *tmp;
	for(i=0; i<MAXCITY; i++)
	{
		if(!(strcmp(cityList[i].cityName,cityName)))
		break;
	}
	return cityList[i].nextArrival;
}
void DisplayArrivalList(char *cityName){
	FlightType *tmp=CityArrivalList(cityName);
	cout<<endl<<cityName<<endl<<"Arrival List :\n";
	for(; tmp!=NULL; tmp=tmp->nextArrival)
	{
		cout<<"From  "<<tmp->startCity<<"   at  "<<tmp->timeArrival<<endl;
	}
	cout<<endl<<endl;

}
void DisplayFlightInfo(FlightType *flight){
	cout<<endl;
	cout<<left<<setw(8)<<flight->FlightNo;
	cout<<left<<setw(15)<<flight->startCity;
	cout<<left<<setw(8)<<flight->timeDepart;
	cout<<left<<setw(15)<<flight->endCity;
	cout<<left<<setw(8)<<flight->timeArrival;
}
void DisplayAllFlightsData(){
	for(int i=0; i<MAXFLIGHT ; i++){
		if(flightList[i].flight==NULL)
		return;
		DisplayFlightInfo(flightList[i].flight);
	}
}

int main(){


    init();
	ReadFlightData();
	DisplayAllFlightsData();
	DisplayDepartureList("Islamabad");
	DisplayDepartureList("Bahawalpur");
	DisplayDepartureList("UAE");
	
}
