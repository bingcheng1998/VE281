#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <assert.h>
#include <fstream>
// #include <direct.h>
#include <math.h>
using namespace std;
int main(int argc, char *argv[]) {
	ofstream oFile;

	for (int i = 0; i < 100; ++i)
	{
		ostringstream path_stream;
		path_stream<<"./data_file/"<<i<<".data";
		oFile.open(path_stream.str());
		double k = 1.0 + 2.0/100*(i);
		int ek = pow(10, k);
		cerr<<ek<<", ";

		oFile<<0<<endl;
		oFile<<ek<<endl;
		oFile<<0<<endl;
		for (int i = 0; i < ek; ++i)
		{
			int k = mrand48();
			oFile << k <<endl;
		}
		oFile.close();
	}
}