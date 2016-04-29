#define NOTVISITED 1
#define VISITED 2
#define PROCESSED 3
int top=-1;
const int N = 5;
int stack[N];
void Push(CityListType newData){
	if(top == N-1);
	else{
	      top=top+1;
	      stack[top] = newData;
	}
}
int Pop(){
	int topData;
	if(top == -1){
	     return -1;
	     }
	else {
	     topData = stack[top];
	     top = top-1;
	     return topData;
	 }
}


