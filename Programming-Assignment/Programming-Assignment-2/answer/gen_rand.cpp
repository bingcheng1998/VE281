#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;
int main(int argc, char *argv[]) {
	// cout << "argc = " << argc <<endl;
	// for (int i = 0; i < argc; ++i)
	// {
	// 	cout << "argv ["<< i <<"] = "<<argv[i]<<endl;
	// }

	assert(argc == 3);

	cout<<argv[1]<<endl;
	int rand_num = atoi(argv[2]);
	cout<<rand_num<<endl;

	for (int i = 0; i < rand_num; ++i)
	{
		int k = mrand48();
		cout << k <<endl;
	}
}