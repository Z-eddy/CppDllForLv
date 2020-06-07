#include"vector1D.h"
#include<vector>
#include<algorithm>
using std::vector;
using std::max;
using std::min;
using std::abs;
using std::advance;

 vector<double>  addArr(const vector<double>&ve0, const vector<double>&ve1)
{
	vector<double>ve;
	auto size0{ ve0.size() };
	auto size1{ ve1.size() };
	auto size{ min(size0,size1) };
	for (int i{ 0 }; i != size; ++i) {
		ve.push_back(ve0.at(i) + ve1.at(i));
	}
	const vector<double>& tempV{ size0 > size1 ? ve0 : ve1 };
	const auto endSize{ max(size0,size1) };
	for (; size != endSize; ++size) {
		ve.push_back(tempV.at(size));
	}
	return ve;
}

 void lvAddArr(double *arrIn0, long size0, double *arrIn1, long size1)
 {

	vector<double>vIn0, vIn1;
	for (int i{ 0 }; i != size0; ++i) {
		vIn0.push_back(arrIn0[i]);
	}
	for (int i{ 0 }; i != size1; ++i) {
		vIn1.push_back(arrIn1[i]);
	}
	auto vOut = addArr(vIn0, vIn1);

	auto arr{ size0 > size1 ? arrIn0 : arrIn1 };
	auto size{ max(size0,size1) };
	for (int i{ 0 }; i != size; ++i) {
		arr[i] = vOut.at(i);
	}
 }
