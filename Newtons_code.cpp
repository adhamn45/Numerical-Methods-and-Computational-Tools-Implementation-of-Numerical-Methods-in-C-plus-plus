#include<iostream>
#include<math.h>
using namespace std;

float f(float x){
	float k;
	k=x*x*x-x*x-x+1;
	return k;
}
float df(float x){
	float k;
	k=3*x*x-2*x-1;
	return k;
}
int main(){
	float x,x1;
	cout<<"enter a:"<<endl;
	cin>>x;
	  if(f(x)!=0){
	while(f(x1)>0.000001){
		x1=x-f(x)/df(x);
		x=x1;
		
		
	}
	cout<<"Value of root: "<<x;
}
  else
	{
		cout<<"Real root: "<<x;
	}
return 0;
}