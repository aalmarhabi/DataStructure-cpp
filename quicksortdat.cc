// ME - C++17 - I hope it compile
/*
 * Author: Alhussain Almarhabi
*/
/*Reference and future review
 * Youtube Michael Sambol Quick sort in 4 minutes: https://www.youtube.com/watch?v=Hoixgm4-P4M
 * geeks for geeks guick sort: https://www.geeksforgeeks.org/quick-sort/
 * */
/* Question
 * Quicksort
input file format:
number of test cases
number of elements to sort in test 1
data for test1
number of elements to sort in test 2
data for test2
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

/// Swap function using pointer
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
/// Partition function to find the pivot
int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // i is index for small element

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
/// Quircksort algorithm
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int partIndex = partition(arr, low, high);

        quickSort(arr, low, partIndex - 1);
        quickSort(arr, partIndex + 1, high);
    }
}

int main(int argc, char* argv[]) {
    /// ERROR MESSAGE in case more than two argv was entered
    try{// start of try
        if (argc !=2){// start of if
            throw 1;
        } // end of it
    }// end of try
    catch (int x){
        std::cout<<"Error Message: "<< x << " . Please only include one argument in command line"<<std::endl;
        return 0;
    }

    /// Reading .data file
    std::ifstream dfile;
    dfile.open(argv[1]);

    /// Check if file open
    if (!dfile.is_open())
    {
        std::cout << "Error Message: 2 . File did not open"<< std::endl;
        return 0;
    }

    std::string line;
    int cases, noarray;
    std::getline(dfile, line);
    cases = std::stoi(line);

    /// cases Index
    int caIndex = 0;

    while (caIndex != cases)
    {
        /// get array length
        std::getline(dfile, line);
        noarray = std::stoi(line);

        /// get array and some information
        std::getline(dfile, line);
        int n = line.length();
        int array[noarray];
        int ii = 0;

        /// array2 to use sstream to rmove spaces and make element easy to read
        std::vector<int> array2;
        std::stringstream ss(line);
        int temp;
        while (ss >> temp)
        {
            array2.push_back(temp);
        }

        /// Prepare array for quicksort
        for (int i=0; i <= array2.size()-1; i++)
        {
            array[ii] = array2[i];
            ii++;
        }

        /// now run quicksort on our array
        quickSort(array, 0, noarray -1 );

        /// print array before going to next one
        for (int i=0; i <=noarray-1; i++)
        {
            std::cout<<array[i]<<' ';
        }
        std::cout<<std::endl;
        caIndex++; // increment index cases

    }
    return 0;
}
