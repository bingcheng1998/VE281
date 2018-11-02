#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include <fstream>
#include "sort.h"

using namespace std;

#define SORT_WAY_SIZE 6
#define file_num 100
#define SORT_DEBUG
// #define STANDARD_OUTPUT

// enum sort_way
// {
// 	bubble_sort, insertion_sort, selection_sort,
// 	merge_sort, quick_sort_array, quick_sort_in_place,
// 	SORT_WAY_SIZE
// };

void debug_print(char TAG, string deb_string){
	if(TAG == 'r') cout<< deb_string;
	#ifdef DEBUG_SIM
	#ifdef LOG_E
	if(TAG == 'e') cerr<< deb_string;
	#endif
	#ifdef LOG_D
	if(TAG == 'd') cerr<< deb_string;
	#endif
	#ifdef LOG_V
	if(TAG == 'v') cerr<< deb_string;
	#endif
	#ifdef LOG_K
	if(TAG == 'k') cerr<< deb_string;
	#endif
	#endif
}

const string sortName[] = {
	"bubble_sort", "insertion_sort", "selection_sort",
	"merge_sort", "quick_sort_array", "quick_sort_in_place",
	"ERROR_SORT_NAME"
};

// int sort_helper(void (*fn)(int*, int), int arr[], int n) {
// 	fn(arr, n);
// }
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
	10, 11, 13, 15, 17, 19, 22, 26, 30, 34, 39, 45, 52, 60, 69, 79, 91, 104, 120, 138, 158, 181, 208, 239, 275, 316, 363, 416, 478, 549, 630, 724, 831, 954, 1096, 1258, 1445, 1659, 1905, 2187, 2511, 2884, 3311, 3801, 4365, 5011, 5754, 6606, 7585, 8709, 10000, 11481, 13182, 15135, 17378, 19952, 22908, 26302, 30199, 34673, 39810, 45708, 52480, 60255, 69183, 79432, 91201, 104712, 120226, 138038, 158489, 181970, 208929, 239883, 275422, 316227, 363078, 416869, 478630, 549540, 630957, 724435, 831763, 954992, 1096478, 1258925, 1445439, 1659586, 1905460, 2187761, 2511886, 2884031, 3311311, 3801893, 4365158, 5011872, 5754399, 6606934, 7585775, 8709635};
int main(int argc, char *argv[]) {
    void (*const fn[SORT_WAY_SIZE])(int*, const int) = {
        bubble_sort,
        insertion_sort,
        selection_sort,
        merge_sort,
        quick_sort_array,
        quick_sort_in_place
    };

	clock_t start, end;
	// start = clock();
	ofstream outFile;
	outFile.open("data.csv", ios::out);
	outFile << "size"<<","<<"bubble_sort"<<","
		<<"insertion_sort"<<","<<"selection_sort"<<
		","<<"merge_sort"<<","<<"quick_sort_array"<<
		"," <<"quick_sort_in_place"<<","<<endl;
	for (int j = 0; j < file_num; ++j)
	{
		ifstream iFile;
		
		
		ostringstream path_stream;
		path_stream<<j<<".txt";
		safe_open_file(iFile, path_stream.str());
		int lines;
		iFile >> lines;
		iFile >> lines;
		
		int *arr = new int[lines];
		int baz;
		for (int i = 0; i < lines; ++i)
		 {
		 	iFile >> baz;
		 	arr[i] = baz;
		 } 
		// cerr<<"All "<<lines<<" lines, they are:"<<endl;
		// for (int i = 0; i < lines; ++i)
		// {
		// 	cerr<<arr[i]<<endl;
		// }
		// cerr<<"end of lines"<<endl;
		outFile << int_size[j]<<",";
		for (int i = 0; i < SORT_WAY_SIZE; ++i)
		{
			start = clock();
			fn[i](arr, lines);
			end = clock();
			cout<<"Sort algorithm is ["<<sortName[i]<<"],";
			double time_run =  (double)(end - start) / CLOCKS_PER_SEC;
			cout << " 总共运行时间：" <<time_run<< endl;
			outFile << time_run<<",";
		}
		outFile <<endl;


		iFile.close();
		delete[] arr;
	}
	outFile.close();


	// fn[sort_algorithm](arr, n);
	// end = clock();

	return 0;
}




