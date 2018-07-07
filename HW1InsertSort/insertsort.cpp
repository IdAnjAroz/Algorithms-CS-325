#include <iostream>
#include <ostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;
void insertsort(vector <int>& unsorted_vector){
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

    fstream outputFile; //Initializes output file
    outputFile.open("insert.out", fstream::app); //Opens the output file in append mode
    //Writes the contents of the sorted vector to the file insert.out
    for ( int i = 0; i < unsorted_vector.size(); i++ ){
        outputFile << unsorted_vector[i] << " ";
    }//End For
    outputFile << endl; //add line break between sorted vectors
    outputFile.close(); //Closes the file insert.out
}//end insertionSort Function




int main() {

    //Create a vector to hold the values
    vector<int> numbers;
    //Create a vector to hold the unsroted values
    vector<int> unsorted;

    //Create an input file stream
    ifstream in("data.txt",ios::in);

    //As long as we haven't reached the end of the file, keep reading entries.

    int number;  //Variable to hold each number as it is read

    //Read number using the extraction (>>) operator
    while (in >> number) {
        //Add the number to the end of the array
        numbers.push_back(number);
    }// End while

    //Close the file stream
    in.close();


    //Now, the vector<int> object "numbers" contains both the array of numbers,
    //and its length (the number count from the file).

    //Copy the input data into a vector to be sorted
    while(!numbers.empty()){
        for(int i=1;i<=numbers[0];i++){
            unsorted.push_back(numbers[i]);
        }//End For

        insertsort(unsorted); //Call insertion sort algorithm
        unsorted.clear();   /*Erase unsorted lsit now that it has been sorted
                            and move on to next unsorted data*/

        //Resize is used as a parameter to update the new data in numbers
        int resize = numbers[0] + 1;
        //Erase that data that was just sorted and update with unused data
        numbers.erase (numbers.begin(),numbers.begin()+resize);

    }//End while

    return 0;
}
