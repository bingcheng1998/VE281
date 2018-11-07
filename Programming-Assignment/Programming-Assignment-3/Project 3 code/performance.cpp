#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include <fstream>
#include "selection.h"

using namespace std;

#define HEAP_WAY_SIZE 3
#define file_num 100
#define LOOP_TIME 40
// #define SORT_DEBUG

void debug_print(char TAG, string deb_string){
	if(TAG == 'v') cerr<< deb_string;
}

void   Delay(int   time){ 
	clock_t   now   =   clock(); 
	while(   clock()   -   now   <   time   ); 
} 

const string selectionName[] = {
	"unsorted_heap","binary_heap","fib_heap", "ERROR_HEAP"
};

bool safe_open_file(ifstream& i_file, string file_name){
	ostringstream debug_stream;
	i_file.open(file_name.c_str());
	if (i_file.fail()) {
		cout<<"Error: Cannot open file "<< file_name<<"!"<<endl; 
		exit(0);
	}
	debug_stream<<"file opened success!"<<endl;
	debug_print('v', debug_stream.str());
	debug_stream.clear();
	return true;
}

static int int_size[] = {
	// 10, 10, 10, 11, 12, 12, 13, 13, 14, 15, 15, 16, 17, 18, 19, 19, 20, 21, 22, 23, 25, 26, 27, 28, 30, 31, 33, 34, 36, 38, 39, 41, 43, 45, 47, 50, 52, 54, 57, 60, 63, 66, 69, 72, 75, 79, 83, 87, 91, 95, 100, 104, 109, 114, 120, 125, 131, 138, 144, 151, 158, 165, 173, 181, 190, 199, 208, 218, 229, 239, 251, 263, 275, 288, 301, 316, 331, 346, 363, 380, 398, 416, 436, 457, 478, 501, 524, 549, 575, 602, 630, 660, 691, 724, 758, 794, 831, 870, 912, 954 };

// 100, 112, 125, 141, 158, 177, 199, 223, 251, 281, 316, 354, 398, 446, 501, 562, 630, 707, 794, 891, 1000, 1122, 1258, 1412, 1584, 1778, 1995, 2238, 2511, 2818, 3162, 3548, 3981, 4466, 5011, 5623, 6309, 7079, 7943, 8912, 10000, 11220, 12589, 14125, 15848, 17782, 19952, 22387, 25118, 28183, 31622, 35481, 39810, 44668, 50118, 56234, 63095, 70794, 79432, 89125, 100000, 112201, 125892, 141253, 158489, 177827, 199526, 223872, 251188, 281838, 316227, 354813, 398107, 446683, 501187, 562341, 630957, 707945, 794328, 891250, 1000000, 1122018, 1258925, 1412537, 1584893, 1778279, 1995262, 2238721, 2511886, 2818382, 3162277, 3548133, 3981071, 4466835, 5011872, 5623413, 6309573, 7079457, 7943282, 8912509};
1000, 1047, 1096, 1148, 1202, 1258, 1318, 1380, 1445, 1513, 1584, 1659, 1737, 1819, 1905, 1995, 2089, 2187, 2290, 2398, 2511, 2630, 2754, 2884, 3019, 3162, 3311, 3467, 3630, 3801, 3981, 4168, 4365, 4570, 4786, 5011, 5248, 5495, 5754, 6025, 6309, 6606, 6918, 7244, 7585, 7943, 8317, 8709, 9120, 9549, 10000, 10471, 10964, 11481, 12022, 12589, 13182, 13803, 14454, 15135, 15848, 16595, 17378, 18197, 19054, 19952, 20892, 21877, 22908, 23988, 25118, 26302, 27542, 28840, 30199, 31622, 33113, 34673, 36307, 38018, 39810, 41686, 43651, 45708, 47863, 50118, 52480, 54954, 57543, 60255, 63095, 66069, 69183, 72443, 75857, 79432, 83176, 87096, 91201, 95499};
bool jump_j[] = {false, false,false,false,false,false};

struct compare_t {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

int main(int argc, char *argv[]) {
	int (*const fn[HEAP_WAY_SIZE])(int*, const int, const int) = {
        unsorted_heap,
        binary_heap,
        fib_heap
    };

	clock_t start, end;
	ofstream outFile;
	outFile.open("data.csv", ios::out);
	outFile << "size"<<","<<selectionName[0]<<","<<selectionName[1]<<","<<endl;
	for (int j = 0; j < file_num; ++j)
	{
		ifstream iFile;
		
		
		ostringstream path_stream;
		path_stream<<"./data_file/"<<j<<".data";
		safe_open_file(iFile, path_stream.str());
		int lines;
		iFile >> lines;
		iFile >> lines;
		int meanning_less;
		iFile >> meanning_less;

		
		int *arr = new int[lines];
		int baz;
		for (int i = 0; i < lines; ++i)
		 {
		 	iFile >> baz;
		 	arr[i] = baz;
		 } 
		outFile << int_size[j]<<",";
		for (int i = 0; i < SELECTION_WAY_SIZE; ++i)
		{
			if(jump_j[i] == true){
				outFile << ""<<",";
				cerr<<"jump "<<selectionName[i]<<" with "<<int_size[j]<<" size!"<<endl;
				continue;
			}
			if(int_size[j] < 1000){
				cerr<<"delay at "<<int_size[j]<<" size"<<endl;
			 	Delay(1000);
			} else Delay(500);


			// int arr_copy[lines];
			// //use deep copy to make arr_copy evry turn
			// memset(arr_copy,0, lines*sizeof(int));
			// memcpy(arr_copy,arr, lines*sizeof(int));
			// start = clock();
			// fn[i](arr_copy, lines, 0);
			// end = clock();

			long time_all = 0;
 
            for (int io = 0; io < 100; ++io)
            {
            	int i_th_num = lines*(io/(100));
            	int arr_copy[lines];
                //use deep copy to make arr_copy evry turn
                memset(arr_copy,0, lines*sizeof(int));
                memcpy(arr_copy,arr, lines*sizeof(int));
                start = clock();
            	fn[i](arr_copy, lines, i_th_num);
            	end = clock();
            	time_all += (end - start);
            }
                



			cout<<"Sort algorithm is ["<<selectionName[i]<<"],";
			double time_run =  (double)time_all / CLOCKS_PER_SEC / LOOP_TIME;
			cout << "Running time: " <<time_run<< endl;
			if (time_run >= 24.0)
			{
				jump_j[i] = true;
			}
			outFile << time_run<<",";
		}
		outFile <<endl;


		iFile.close();
		delete[] arr;
	}
	outFile.close();
	return 0;
}



