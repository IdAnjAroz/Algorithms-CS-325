#include <iostream>
#include <ostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

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
        if(numbers.size() == 1){
            unsorted.push_back(numbers[0]);
        }
        for(int i=1;i<=numbers[0];i++){
            unsorted.push_back(numbers[i]);
        }//End For

        vector<int> sorted = mergesort(unsorted); //Call merge sort algorithm
        unsorted.clear();   /*Erase unsorted lsit now that it has been sorted
                            and move on to next unsorted data*/

        fstream outputFile; //Initializes output file
        outputFile.open("merge.out", fstream::app); //Opens the output file in append mode
        //Writes the contents of the sorted vector to the file merge.out
        for ( int i = 0; i < sorted.size(); i++ ){
            outputFile << sorted[i] << " ";
        }//End For
        outputFile << endl; //add line break between sorted vectors
        outputFile.close(); //Closes the file merge.out

        //Resize is used as a parameter to update the new data in numbers
        int resize = numbers[0] + 1;
        //Erase that data that was just sorted and update with unused data
        numbers.erase (numbers.begin(),numbers.begin()+resize);

    }//End while

    return 0;
}
