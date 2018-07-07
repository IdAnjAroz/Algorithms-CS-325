#include <iostream>
#include <ostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector <int> insertsort(vector <int>& unsorted_vector){

    //Pass the input vector reference so you can modify data

    int j, temp; // Initialize step and temp variables

    //Iterate through entire list
    for(int i = 1; i < unsorted_vector.size(); i++){
        temp = unsorted_vector[i]; //Temp marks the start of the unsorted cards
        j = i - 1;                 //j is location of current card

        //Swap current card left until it finds a home
        while(j >= 0 && unsorted_vector[j] > temp){
            unsorted_vector[j + 1] = unsorted_vector[j]; //Swap card to the left
            j = j - 1;
        }//End while

        unsorted_vector[j + 1] = temp; //Update value of max card
    }//End for
    return unsorted_vector;
}
//Initialize constants that bound random number generation
constexpr auto low_bound = 0;
constexpr auto up_bound = 10000;

int main() {
    //Random number parameter configuration
    auto seed = chrono::system_clock::now().time_since_epoch().count();//seed
    default_random_engine dre(seed);//engine
    uniform_int_distribution<int> di(low_bound,up_bound);//distribution
    //For loop creates arrays  where n is a multiple of 5k to 70k of random numbers
    //insertion sort is called within loop
    for(int i =5000; i<=70000; i = i + 5000){
        vector<int> unsorted(i);
        generate(unsorted.begin(), unsorted.end(), [&]{ return di(dre);});
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        insertsort(unsorted); //Call insertion sort algorithm
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<seconds>( t2 - t1 ).count();
        cout << "Array Size: n = "<< i <<"  \n";
        cout << "Running time: " << duration <<" seconds" <<endl;
        cout << endl;

        unsorted.clear();   /*Erase unsorted lsit now that it has been sorted
                                and move on to next unsorted data*/
    }

    return 0;
}
