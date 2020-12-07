#include<iostream>
#include<Windows.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<conio.h>
using namespace std;

class project
{
private:
	string name;
	float visEst;
	float singlePrice;
	float transRate;
	float marEst;
	float proCost;
	float collision;
	float platCost;
	float deliver;
	float labCost;
public:
	project();
	~project();
	void Set(string a, float b, float c, float d, float e, float f, float g, float h, float k, float l);
	float _visEst() { return visEst; }
	string _name() { return name; }
	float _singlePrice() { return singlePrice; }
	float _transRate() { return transRate; }
	float _marEst() { return marEst; }
	float _proCost() { return proCost; }
	float _collision() { return collision; }
	float _platCost() { return platCost; }
	float _deliver() { return deliver; }
	float _labCost() { return labCost; }
};

