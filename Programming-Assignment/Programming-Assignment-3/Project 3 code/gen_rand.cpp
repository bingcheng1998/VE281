#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;
int main(int argc, char *argv[]) {

	int w = 100;

	cout<<w<<" "<<w<<endl;
	cout<<0<<" "<<0<<endl;
	cout<<99<<" "<<99<<endl;
	int k;
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			k = mrand48()%5 + 4;
			cout << k <<" ";
		}
	}
}