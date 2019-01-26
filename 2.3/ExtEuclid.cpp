#include<iostream>
using namespace std;

struct ExtEuc{
	int d;
	int s;
	int t;
};

ExtEuc ExtEulcid(int,int);
int main(){
	ExtEuc eu;
	int a,b;
	cout<<"Please input two integers:";
	cin>>a>>b;
	eu=ExtEulcid(a,b);
	cout<<"d="<<eu.d<<" s="<<eu.s<<" t="<<eu.t<<endl;

	return 0;
}

ExtEuc ExtEulcid(int a,int b){
	ExtEuc eu,eu1;
	if(b==0){
		eu1.d=a;
		eu1.s=1;
		eu1.t=0;
		return eu1;
	}
	eu1=ExtEulcid(b,a%b);
	eu.d=eu1.d;
	eu.s=eu1.t;
	eu.t=eu1.s-(a/b)*eu1.t;
	return eu;
}
