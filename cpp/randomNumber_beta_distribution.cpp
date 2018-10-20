#include <cstdio>
#include <boost/math/distributions/beta.hpp>

#include <iostream>
#include <string>
#include <map>
#include <random>

using namespace boost::math;
using namespace std;

int main() {
	srand(time(0));
	double alpha = 0.5, beta = 0.5;
	beta_distribution<> dist(alpha, beta);

	for (int i = 0 ; i < 1000 ; i++) {
		double rngfloat = (double)(rand() % 101) / 100;
		cout<<" "<<quantile(dist, rngfloat)<<endl;
	}
}
