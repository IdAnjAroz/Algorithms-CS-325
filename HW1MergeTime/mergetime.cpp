#include <iostream>
#include <ostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<int> mergesort(const vector<int>& input)
{
    if(input.size()<=1){ //Check if the vector has only 1 element
        return input;    //If so,return the value
    }

    vector<int> output(input.size()); //Initialize the vector to operate on

    //Split Vector//
    int midpoint=0.5*input.size(); //Value which is used to find the middle element of the left vector
    vector<int> input_left(input.begin(),input.begin()+midpoint); //Split vector into left and right vectors
    vector<int> input_right(input.begin()+midpoint,input.end());

    input_left=mergesort(input_left);       // Recursively sort the left and right vectors
    input_right=mergesort(input_right);
    //Combine sorted left and right vectors into the final vector
    merge(input_left.begin(),input_left.end(),input_right.begin(),input_right.end(),output.begin());

    return output; // return sorted vector
}
constexpr auto low_bound = 0;
constexpr auto up_bound = 10000;

int main() {    //Random number parameter configuration
    auto seed = chrono::system_clock::now().time_since_epoch().count();//seed
    default_random_engine dre(seed);//engine
    uniform_int_distribution<int> di(low_bound,up_bound);//distribution
    //For loop creates arrays  where n is a multiple of 5k to 70k of random numbers
    //insertion sort is called within loop
    for(int i =100000; i<=10000000; i = i + 500000){
        vector<int> unsorted(i);
        generate(unsorted.begin(), unsorted.end(), [&]{ return di(dre);});
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        unsorted = mergesort(unsorted); //Call merge sort algorithm
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        double duration = duration_cast<seconds>( t2 - t1 ).count();
        cout << "Array Size: n = "<< i <<"  \n";
        cout << "Running time: " << duration <<" seconds" <<endl;
        cout << endl;

        unsorted.clear();   /*Erase unsorted lsit now that it has been sorted
                                and move on to next unsorted data*/
    }

    return 0;
}
