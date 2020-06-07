#include <iostream>
#include<vector>
#include "vector1D.h"
using std::cout;
using std::endl;
using std::ends;
using std::vector;

int main()
{
	vector<double>v0{ 1,2,3,4,5 };
	vector<double>v1{ 2,3,4 };
	auto ve{ addArr(v0, v1) };
	for (auto item : ve) {
		cout << item << endl;
	}
}