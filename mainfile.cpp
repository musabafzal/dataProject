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

int Noflights=21;
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

ReservationType *reserveHead=NULL,*reserveTail=NULL; /* head and tail of the reservation list */
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
int hash(char *s)
{
	for(int i=0; i<MAXCITY; i++)
	{
		if(strcmp(cityList[i].cityName,s)==0)
		return i;
	}
	return -1;
}
FlightType *nextDp(FlightType *newPtr)
{
	int i=0;
	/*for(i=0; i<MAXCITY; i++)
	{
		if(!(strcmp(cityList[i].cityName,newPtr->startCity)))
		break;
	}*/
	i=hash(newPtr->startCity);
	
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
    	cityList[i].nextDeparture=newPtr;
    	return newPtr->nextDeparture;
	}
  }
}
FlightType *nextAr(FlightType *newPtr)
{
	
	int i=0;
	/*for( i=0; i<MAXCITY; i++)
	{
		
		if(!(strcmp(cityList[i].cityName,newPtr->endCity)))
		break;
	}*/
	i=hash(newPtr->endCity);
	
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
		cityList[i].nextArrival=newPtr;
		return newPtr->nextArrival;
	}
    }
}
int top1=-1;
void map(char *s)
{
	cityList[++top1].cityName=new char[strlen(s)+1];
	cityList[top1].cityName=s;
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
	newPtr->noOfPassengers=0;
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
	cout<<endl;
	for(i=0; i<MAXCITY; i++)
	{
		
		tmp=cityList[i].nextDeparture;
		if(!(strcmp(cityList[i].cityName,cityName)))
		break;
	}
	;
	return tmp;
	
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
	if(flight!=NULL){
	cout<<endl;
	cout<<left<<setw(8)<<flight->FlightNo;
	cout<<left<<setw(15)<<flight->startCity;
	cout<<left<<setw(8)<<flight->timeDepart;
	cout<<left<<setw(15)<<flight->endCity;
	cout<<left<<setw(8)<<flight->timeArrival;
	}
}
void DisplayAllFlightsData(){
	for(int i=0; i<MAXFLIGHT ; i++){
		if(flightList[i].flight==NULL)
		return;
		DisplayFlightInfo(flightList[i].flight);
	}
}
FlightType *FlightByNumber(int FlightNo){
	int i;
	for(i=0; i<MAXFLIGHT ; i++){
	if(flightList[i].flight==NULL)
		return NULL;
	if(flightList[i].FlightNo==FlightNo)
	break;
	}
	return flightList[i].flight;
}
void DisplayAllCities(){
	for(int i=0;i<MAXCITY;i++)
	{
		if(cityList[i].cityName==NULL)
		return;
		cout<<endl<<cityList[i].cityName;
	}
}
int timeweight(int timeDepart, int timeArrival)
{
	int min1; int min2;   int hour1,hour2;   int time;
	min1=timeDepart%100;      
	min2=timeArrival%100;
	hour1=timeDepart/100;
	hour2=timeArrival/100;
	if(min2-min1<0)
	{
		min2=min2+60;
		min2=min2-min1;
		hour2=hour2-1;
	}
	else
	min2=min2-min1;
	
	hour2=hour2-hour1;
	time=(hour2*100)+min2;
	return time;
}
int find(int k, int a[], int j)
{
	for(int i=0; i<=j; i++)
	{
		if(a[i]==k)
		return 0;
	}
	return 1;
}
int min(int a,int b,int c=4800,int d=4800, int e=4800, int f=4800)
{
	int min;
	int N[6]={a,b,c,d,e,f};
	min=N[0];
	for(int i=0; i<6; i++)
	{
		if(N[i]<min)
		min=N[i];
	}
	return min;
}
int timeadd(int x, int y)
{ int time;
   int min1,min2,hour1,hour2;
   min1=x%100;    hour1=x/100;
   hour2=y/100;
   min2=y%100;
   if(min1+min2>=60)
   {
   	    min2=(min2+min1)-60;
   	    hour2=hour2+1+hour1;
   }
   else
   {
     min2=min2+min1;
     hour2=hour2+hour1;
  }
     time=(hour2*100)+min2;
     return time;
}
void DisplayShortestPath(char *startCity,char *endCity)
{
	int a[30]={0};     int i;     FlightType *p,*t;  int w[top1];   int min=4800;   int j=0; int c=-1; int weight; int s,e; int cc; int parent,path[30],par[30];
	
	i=hash(startCity);
	s=i;
	
	w[s]=0;
	e=hash(endCity);
	a[j]=i;
	
	while(j!=top1)
	   {   //cout<<"Flag 3\n";
	      min=4800;
	       for(int z=j; z>=0  ;z--)
	       {    
	           for(p=cityList[a[z]].nextDeparture;  p!=NULL;  p=p->nextDeparture)
	          {
                    weight=timeadd(w[a[z]],timeweight(p->timeDepart,p->timeArrival));
                    cc=hash(p->endCity);
		            if(weight<min && find(cc,a,j))
		            {
		              parent=a[z];
			          min=weight;
			          t=p;	
		            }
	          }
           }
            
            i=hash(t->endCity);
            path[i]=parent;
            
             w[i]=min;
             
             a[++j]=i;
             //cout<<"Flag 1\n";
         for(int k=0; k<=top1; k++)
          {
          	//cout<<"Flag 2\n";
             if(k!=s && find(k,a,j))
              {
        	     min=4800;
        		for(int z=j; z>=0  ;z--)
	            {
	               for(p=cityList[a[z]].nextDeparture;  p!=NULL;  p=p->nextDeparture)
	               {
		              if(strcmp(p->endCity,cityList[k].cityName)==0)
		              {
		              	weight=timeadd(timeweight(p->timeDepart,p->timeArrival),w[a[z]]);
		                 if(weight<min)
		                 {
		                    min=weight;	
						 }
		              }   
	               }
	               
                }  
				w[k]=min; 
		      }
          }
         //cout<<w[e]<<endl;
     }
     int q=0;
     for(parent=e; q<=30 && par[c]!=s; q++)
     {
     	par[++c]=path[parent];
		parent=par[c];	
	 }
	 for(;c!=-1;)
	 {
	 	cout<<cityList[par[c--]].cityName<<"->";
	 }
	 cout<<cityList[e].cityName;
	 cout<<endl;
     cout<<"Shortest Path weight: \n"<<w[e]/100<<": "<<w[e]%100<<endl;
}
#define NOTVISITED 1
#define VISITED 2
#define PROCESSED 3
int top=-1;
const int N = 10;
CityListType stack[N];
void Push(CityListType newData){
	if(top == N-1);
	else{
	      top=top+1;
	      stack[top] = newData;
	}
}
CityListType Pop(){
	CityListType topData;
	if(top == -1){
	     }
	else {
	     topData = stack[top];
	     top = top-1;
	     return topData;
	 }
}

void DisplayCitiesFrom(char *startCity){
	int i,j,k,l,count=0;   FlightType *tmp;
	for(i=0; i<MAXCITY; i++)
	{
		if(!(strcmp(cityList[i].cityName,startCity)))
		break;
	}
	for(k=0;k<MAXCITY;k++){
		if(cityList[k].cityName==NULL)
		break;
		count++;
	}
	int *status = new int[count];
	for(j=0;j<count; j++){
		status[j]=NOTVISITED;
	}
	Push(cityList[i]);
	status[i]=VISITED;
	CityListType citytmp;
	while(top!=-1){
		citytmp=Pop();
	cout<<citytmp.cityName<<"->";
	
	int z=0;
	for(z=0;z<count;z++){
		if(!(strcmp(cityList[z].cityName,citytmp.cityName)))
		break;
	}
	int m;
	for(tmp= citytmp.nextDeparture;tmp!=NULL;tmp=tmp->nextDeparture){
		
		for(m=0;m<count;m++){
			if(!(strcmp(cityList[m].cityName,tmp->endCity)))
			break;
		}
		if(status[m]==NOTVISITED){
		Push(cityList[m]);
		status[m]=VISITED;
		}
	}
	status[z]=PROCESSED;

	}
}
int timediff(int time1,int time2,int &tripdate)
{
	int min1,min2,hour1,hour2,time; int dd,mm;    dd=tripdate%100;   mm=tripdate/100;
	if(time1>time2)
	{
		min1=time1%100;
		min2=time2%100;
		hour1=time1/100;
		hour2=time2/100;
		if(min1>0)
		{
			hour1=23-hour1;
			min1=60-min1;
		}
		else
		hour1=24-hour1;
		hour2=hour1+hour2;
		min2=min2+min1;
		if(min2>60)
		{
			min2=min2-60;
			hour2++;
		}
		dd++;
		if(dd>30)
		{
			dd=dd-30;
			mm++;
		}
		tripdate=(mm*100)+dd;
	}
	else
	{
		min1=time1%100;
		min2=time2%100;
		hour1=time1/100;
		hour2=time2/100;
		if(min2<min1)
		{
			hour2--;
		   min2=min2+60-min1;
		   hour2=hour2-hour1;
	    }
	    else
	    {
	    	min2=min2-min1;
	    	hour2=hour2-hour1;
		}
	}
	time=(hour2*100)+min2;
	return time;
}
int FindRoute(char *startCity, char *endCity, RouteType &route){
	FlightType *tmp = CityDepartureList(startCity); 
	int count=0,count1=0;
	
	for(;tmp!=NULL;tmp=tmp->nextDeparture){
		
		if(!strcmp(tmp->endCity,endCity)){
			count++;
			break;
		}
	}
	if(count!=0){
		
		route.FlightNo1=tmp->FlightNo;   int i=0;
		route.FlightNo2=0;
		for(i=0; i<Noflights ; i++)
		{
			 
			if(flightList[i].FlightNo==route.FlightNo1)
			break;
		}
		flightList[i].flight->noOfPassengers++;
		route.nHops=1;
		return 1;
	}
	else{
	FlightType *tmp1 = CityDepartureList(startCity);
	FlightType *tmp2=CityArrivalList(endCity);
	
	for(;tmp1!=NULL;tmp1=tmp1->nextDeparture){
		
		for(tmp2=CityArrivalList(endCity);tmp2!=NULL;tmp2=tmp2->nextArrival){
			if(!strcmp(tmp1->endCity,tmp2->startCity))
			break;
		}
		if(tmp2!=NULL){
		if(!strcmp(tmp1->endCity,tmp2->startCity)){
		count1++;
		break;
		}
		}
	}
	if(count1!=0&&timediff(tmp1->timeArrival,tmp2->timeDepart,route.Day)>30){
		    int i=0;
		route.FlightNo1=tmp1->FlightNo;
		route.FlightNo2=tmp2->FlightNo;
		for(i=0; i<Noflights ; i++)
		{
			if(flightList[i].FlightNo==route.FlightNo1)
			break;
		}
		flightList[i].flight->noOfPassengers++;
		for(i=0; i<Noflights ; i++)
		{
			if(flightList[i].FlightNo==route.FlightNo2)
			break;
		}
		flightList[i].flight->noOfPassengers++;
		
		route.nHops=2;
	}
	else 
		return 0;
	}
}

ReservationType *MakeReserveNode(char *firstName, char *lastName, int tripType, RouteType route1, RouteType route2){
	ReservationType *node = new ReservationType;
	
	node->firstName=firstName;
	node->lastName=lastName;
	node->tripType=tripType;
	node->route1=route1;
	node->route2=route2;
	node->nextReserve=NULL;
	return node;	
}
void MakeReservation()
{
	ReservationType *R;   RouteType rt1,rt2;   
	string firstName; string lastName;  string startCity,endCity;  int tripType,tripdate,tripdate2;    int reserved,reserved2=1; char *s,*e,*f,*l;
	cout<<"Enter first Name :\n";
	cin>>firstName;
	cout<<"Enter last Name : \n";
	cin>>lastName;
	cout<<"Enter Departure City : \n";
	cin>>startCity;
	cout<<"Enter Destination City : \n";
	cin>>endCity;
	cout<<"Enter 1 for round trip or 0 for one way :\n";
	cin>>tripType;
	s=new char[startCity.length()+1];
	startCity.copy(s,startCity.length(),0);
	e=new char[endCity.length()+1];
	endCity.copy(e,endCity.length(),0);
	f=new char[firstName.length()+1];
	firstName.copy(f,firstName.length(),0);
	l=new char[lastName.length()+1];
	lastName.copy(l,lastName.length(),0);
	s[startCity.length()]='\0';
	e[endCity.length()]='\0';
	f[firstName.length()]='\0';
	l[lastName.length()]='\0';
	if(tripType==0)
	{
	cout<<"Enter Date of Travel (mm/dd): \n";
	cin>>tripdate;
	rt1.Day=tripdate;
	reserved=FindRoute(s,e,rt1);
    }
    else
    {
     	cout<<"Enter Date of Travel (mm/dd): \n";
	    cin>>tripdate;
     	cout<<"Enter Date of Return (mm/dd): \n";
	   cin>>tripdate2;
	    rt1.Day=tripdate;
	     reserved=FindRoute(s,e,rt1);
	     
	    rt2.Day=tripdate2;
	 	reserved2=FindRoute(e,s,rt2);
	}
	 if(reserved!=0 && reserved2!=0)
	 {
	 	
	    R=MakeReserveNode(f,l,tripType,rt1,rt2);
	    
	    if(reserveHead==NULL)
	    {
	    	reserveHead=R;
	    	reserveTail=reserveHead;
		}
		else
		{
			
	    reserveTail->nextReserve=R;
	     reserveTail=reserveTail->nextReserve;
	     
	    }
	     
     }
     else
     {
     	cout<<"Cannot Book Flight\n";
	 }
}
void PrintReservation(ReservationType *P)
{
	if(P==NULL)
	{
		cout<<"No Reservation\n";
		return;
	}
	cout<<"First Name : "<<setw(5)<<P->firstName<<endl;
	cout<<"Last Name : "<<setw(5)<<P->lastName<<endl;
	
	if(P->tripType==1)
	{
	cout<<"Round Trip \n\n";
	cout<<"Journey\n";
	cout<<"Flight No 1 : "<<P->route1.FlightNo1<<"\t"<<"Flight No 2 : "<<P->route1.FlightNo2<<endl;
	cout<<"\nReturn Journey\n";
	cout<<"Flight No 1 : "<<P->route2.FlightNo1<<"\t"<<"Flight No 2 : "<<P->route2.FlightNo2<<endl;
    }
	else if(P->tripType==0)
	{
	cout<<"One way \n";
	cout<<"Flight No 1 : "<<P->route1.FlightNo1<<setw(5)<<"Flight No 2 : "<<P->route1.FlightNo2<<endl;
     }
}
void printRoute(int ifExists, RouteType route){
	if(ifExists==1){
	cout<<"Flight No 1 : "<<route.FlightNo1<<setw(5)<<"Flight No 2 : "<<route.FlightNo2<<endl;
	}
	else{
		cout<<"No Route Exists"<<endl;
	}
}
void PrintAllReservation()
{
	ReservationType *p=reserveHead;
	for(; p!=NULL; p=p->nextReserve)
	{
		  cout<<endl;
	      PrintReservation(p);
    }
}
void PrintPassengers(int FlightNo){
	ReservationType *p=reserveHead;
	

	
	cout<<endl;
	for(; p!=NULL; p=p->nextReserve){
		if(FlightNo==p->route1.FlightNo1||FlightNo==p->route1.FlightNo2||FlightNo==p->route2.FlightNo1||FlightNo==p->route2.FlightNo2){
			cout<<"First Name: "<<p->firstName<<endl;
			cout<<"Last Name: "<<p->lastName<<endl;
		}
	}	
}
void PrintSchedule(){
	ReservationType *p=reserveHead;
	string firstName, lastName; char *f,*l;
	
	cout<<"Enter first Name :\n";
	cin>>firstName;
	cout<<"Enter last Name : \n";
	cin>>lastName;
	
	f=new char[firstName.length()+1];
	firstName.copy(f,firstName.length(),0);
	l=new char[lastName.length()+1];
	lastName.copy(l,lastName.length(),0);

	cout<<endl;
	for(;p!=NULL;p=p->nextReserve){
		if(!strcmp(f,p->firstName)&&!strcmp(l,p->lastName)){
			break;
		}
	}
	if(p!=NULL)
	PrintReservation(p);
	else 
		cout<<"No Record Found"<<endl;
}
void DeleteReserve(){
	ReservationType *p=reserveHead;
	string firstName, lastName; char *f,*l;
	
	cout<<"Enter first Name :\n";
	cin>>firstName;
	cout<<"Enter last Name : \n";
	cin>>lastName;
	
	f=new char[firstName.length()+1];
	firstName.copy(f,firstName.length(),0);
	l=new char[lastName.length()+1];
	lastName.copy(l,lastName.length(),0);

	cout<<endl;
	for(;p!=NULL;p=p->nextReserve){
		if(!strcmp(f,p->firstName)&&!strcmp(l,p->lastName)){
			break;
		}
	}
	if(p!=NULL){
		int i=0;
		for(i=0; i<Noflights ;i++)
		{ 
		if(flightList[i].FlightNo==p->route1.FlightNo1)
		break;
		}
		if(p->route1.FlightNo1!=0)
		flightList[i].flight->noOfPassengers--;
		for(i=0; i<Noflights ;i++)
		{ 
		if(flightList[i].FlightNo==p->route1.FlightNo2)
		break;
		}
		if(p->route1.FlightNo2!=0)
		flightList[i].flight->noOfPassengers--;
		for(i=0; i<Noflights ;i++)
		{ 
		if(flightList[i].FlightNo==p->route2.FlightNo1)
		break;
		}
		if(p->route2.FlightNo1!=0)
		flightList[i].flight->noOfPassengers--;
		for(i=0; i<Noflights ;i++)
		{ 
		if(flightList[i].FlightNo==p->route2.FlightNo2)
		break;
		}
		if(p->route2.FlightNo2!=0)
		flightList[i].flight->noOfPassengers--;
		
		if(p==reserveHead){
			reserveHead=reserveHead->nextReserve;
		}
		else{
			ReservationType *prev=reserveHead,*p1=reserveHead->nextReserve;
			for(;p1!=NULL;p1=p1->nextReserve){
				if(p==p1){
					break;
				}
				prev=prev->nextReserve;
			}
			prev->nextReserve=p1->nextReserve;
		}
	
	}
	else 
		cout<<"No Record Found"<<endl;
}
int main(){
    init();
	ReadFlightData();
	cout<<"\n\n\t--------------------AIRLINE RESERVATION---------------------------\n\n\n\tENTER\n\t1. Add City\n\t2. Add Flight\n\t3. Display All Cities\n\t4. Display City Departure List\n\t5. Display City Arrival List\n\t6. Display Cities From\n\t7. Display Shortest path between cities\n\t8. Make Reservation\n\t9. Delete Reservation\n\t10. Print Passengers Reservation Schedule\n\n";
//	DisplayFlightInfo(FlightByNumber(654));
//	DisplayDepartureList("Quetta");
/*	DisplayAllCities();
	DisplayDepartureList("Islamabad");
	DisplayDepartureList("Bahawalpur");
	DisplayDepartureList("UAE");
	DisplayDepartureList("Lahore");
	DisplayShortestPath("UAE","Bahawalpur");*/
	MakeReservation();
	MakeReservation();
	PrintAllReservation();
	DeleteReserve();
	PrintAllReservation();
}
