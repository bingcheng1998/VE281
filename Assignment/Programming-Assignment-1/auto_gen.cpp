#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <assert.h>
#include <fstream>
#include <math.h>
using namespace std;
int main(int argc, char *argv[]) {
	ofstream oFile;

	for (int i = 0; i < 100; ++i)
	{
		ostringstream path_stream;
		path_stream<<i<<".txt";
		oFile.open(path_stream.str());
		double k = 1.0 + 6.0/100*(i);
		int ek = pow(10, k);
		cerr<<ek<<", ";

		oFile<<ek<<endl;
		oFile<<ek<<endl;
		for (int i = 0; i < ek; ++i)
		{
			int k = mrand48();
			oFile << k <<endl;
		}
		oFile.close();
	}
}