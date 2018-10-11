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
// #define SORT_DEBUG

void debug_print(char TAG, string deb_string){
	if(TAG == 'v') cerr<< deb_string;
}

void   Delay(int   time){ 
	clock_t   now   =   clock(); 
	while(   clock()   -   now   <   time   ); 
} 

const string sortName[] = {
	"bubble_sort", "insertion_sort", "selection_sort",
	"merge_sort", "quick_sort_array", "quick_sort_in_place",
	"ERROR_SORT_NAME"
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
	10, 10, 10, 11, 12, 12, 13, 13, 14, 15, 15, 16, 17, 18, 19, 19, 20, 21, 22, 23, 25, 26, 27, 28, 30, 31, 33, 34, 36, 38, 39, 41, 43, 45, 47, 50, 52, 54, 57, 60, 63, 66, 69, 72, 75, 79, 83, 87, 91, 95, 100, 104, 109, 114, 120, 125, 131, 138, 144, 151, 158, 165, 173, 181, 190, 199, 208, 218, 229, 239, 251, 263, 275, 288, 301, 316, 331, 346, 363, 380, 398, 416, 436, 457, 478, 501, 524, 549, 575, 602, 630, 660, 691, 724, 758, 794, 831, 870, 912, 954};

bool jump_j[] = {false, false,false,false,false,false};

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
		outFile << int_size[j]<<",";
		for (int i = 0; i < SORT_WAY_SIZE; ++i)
		{
			if(jump_j[i] == true){
				outFile << ""<<",";
				cerr<<"jump "<<sortName[i]<<" with "<<int_size[j]<<" size!"<<endl;
				continue;
			}
			if(int_size[j] < 1000){
				cerr<<"delay at "<<int_size[j]<<" size"<<endl;
			 	Delay(1000);
			} else Delay(500);
			int arr_copy[lines];
			//use deep copy to make arr_copy evry turn
			memset(arr_copy,0, lines*sizeof(int));
			memcpy(arr_copy,arr, lines*sizeof(int));
			start = clock();
			fn[i](arr_copy, lines);
			end = clock();
			cout<<"Sort algorithm is ["<<sortName[i]<<"],";
			double time_run =  (double)(end - start) / CLOCKS_PER_SEC;
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




