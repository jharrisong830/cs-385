/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : John Graham
 * Version     : 1.0
 * Date        : 10/25/22
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long num=0;
    for(int i=0; i<length; i++) {
        for(int j=i+1; j<length; j++) {
            if(array[i] > array[j]) {
                num++;
            }
        }
    }
    return num;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch=new int[length]; //create scratch array so we can call mergesort on the given array
    for(int i=0; i<length; i++) {
        scratch[i]=0;
    }
    long result=mergesort(array, scratch, 0, length-1); //counts the total number of inversions in the array, returns it to result
    delete [] scratch; //delete (for memeory management)
    return result;
}

/*Merge function for mergesort (returns the number of inversions fixed with every merge)*/
static long merge(int array[], int scratch[], int low, int mid, int high) {
    long num=0;
    int i1=low;
    int i2=mid+1;
    int i=low;
    while(i1<=mid && i2<=high) {
        if(array[i1]<=array[i2]) { //if value in the lower half of the array is less...
            scratch[i]=array[i1]; //...then copy that value to scratch first, and increment apppropriate counters
            i++;
            i1++;
        }
        else { //else if value in the upper half of the array is less..
            scratch[i]=array[i2]; //then copy that value to scratch first, and increment the appropriate counters
            i++;
            i2++;
            num+=(mid-i1+1); //we are fixing this many inversions when copying back to array from the upper half 
        }
    }
    while(i1<=mid) { //fill in any leftover values from lower half
        scratch[i]=array[i1];
        i++;
        i1++;
    }
    while(i2<=high) { //fill in any leftover values from upper half
        scratch[i]=array[i2];
        i++;
        i2++;
    }
    for(int k=low; k<=high; k++) { //copy scratch back to original array from low to high
        array[k]=scratch[k];
    }
    return num;
}

/*Performs mergesort on an array, while counting the number of inversions in the array*/
static long mergesort(int array[], int scratch[], int low, int high) {
    long num=0;
    int mid;
    if(low<high) {
        mid=low + (high-low)/2;
        num+=mergesort(array, scratch, low, mid); //at each recurisve level...
        num+=mergesort(array, scratch, mid+1, high); //..add the number of inversions fixed...
        num+=merge(array, scratch, low, mid, high); //...and merge!
    }
    return num; //return the result
}

int main(int argc, char *argv[]) {
    string strrr="slow";
    if(argc==2) { //if there are 2 arguments
        if(argv[1]!=strrr) { //2nd argument is not "slow"
            cerr<<"Error: Unrecognized option '"<<argv[1]<<"'."<<endl;
            return 1;
        }
    }
    else if(argc!=1) { //else if there are more than 2 arguments (i.e. not 1 and not 2)
        cerr<<"Usage: ./inversioncounter [slow]"<<endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    
    long inversions;
    if(values.empty()) { //if no array is given, then we can't count
        cerr<<"Error: Sequence of integers not received."<<endl;
        return 1;
    }
    if(argc==2) { //slow!
        inversions=count_inversions_slow(&values[0], values.size());
    }
    else { //normal!
        inversions=count_inversions_fast(&values[0], values.size());
    }

    cout<<"Number of inversions: "<<inversions<<endl;

    return 0;
}
