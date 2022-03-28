#include <bits/stdc++.h>
using namespace std;

#define pdd pair<double, double>

pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D)
{
	// Line AB -> a1x + b1y = c1
	double a1 = B.second - A.second;
	double b1 = A.first - B.first;
	double c1 = a1*(A.first) + b1*(A.second);

	// Line CD -> a2x + b2y = c2
	double a2 = D.second - C.second;
	double b2 = C.first - D.first;
	double c2 = a2*(C.first)+ b2*(C.second);

	double determinant = a1*b2 - a2*b1;

	if (determinant != 0) {
        double x = (b2*c1 - b1*c2)/determinant;
		double y = (a1*c2 - a2*c1)/determinant;
		return {x, y};
	}
	else
        return {FLT_MAX, FLT_MAX};
}

// int main()
// {
// 	pdd A = {1, 1};
// 	pdd B = {2, 2};
// 	pdd C = {3, 7};
// 	pdd D = {2, 1};

// 	pdd intersection = lineLineIntersection(A, B, C, D);

// 	if (intersection.first == FLT_MAX && intersection.second==FLT_MAX) {
// 		cout << "Lines are parallel\n";
// 	}

// 	else {
// 		cout << "(" << intersection.first << ", " << intersection.second << ")" << endl;
// 	}

// 	return 0;
// }
