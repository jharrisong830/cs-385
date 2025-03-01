/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : John Graham
 * Date        : 9/27/22
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

/**Calculates and specifies the number of ways that num_stairs can be climbed.*/
vector< vector<int> > get_ways(int num_stairs) {
    vector<vector<int>> ways;
    if(num_stairs<=0) { //base case
        return ways;
    }
    for(int i=1; i<4; i++) { //1, 2, or 3 stairs at a time
        if(num_stairs>=i) {
            vector<vector<int>> result=get_ways(num_stairs-i); //what we're prepending to (since each way in get_ways(num_stairs-i) prepended with i will make up the full get_ways(num_stairs))
            vector<int> prepend; //used for inserting to the final vector of ways
            int size=result.size();
            if(size==0) { //prepending to get_ways(0) (can just push_back(i), since our previous result is empty)
                prepend.push_back(i);
                ways.insert(ways.cend(),prepend); //adds the prepended way to the final vector of ways
            }
            else {
                for(int j=0; j<size; j++) { //for each way in the result, prepend i
                    prepend=result.at(j); //take the way at the jth position
                    prepend.insert(prepend.cbegin(),i); //insert i at the beginning
                    ways.insert(ways.cend(),prepend); //add the prepended vector to the final vector of ways
                }
            }
        }
    }
    return ways;
}

/**Displays the number of ways that a staircaise can be climbed.*/
void display_ways(const vector< vector<int> > &ways) {
    int num_stairs;
    int num_ways=0;
    for(const auto &way:ways) { //counts the number of stairs to be climbed
        num_stairs=0;
        for(const auto &num:way) {
            num_stairs+=num;
        }
        num_ways++;
    }
    if(num_stairs==1) { //for grammar, no plurals
        cout<<"1 way to climb 1 stair."<<endl;
    }
    else { //plurals
        cout<<num_ways<<" ways to climb "<<num_stairs<<" stairs."<<endl;
    }

    int num_digits=0; //for setw(num_digits), alignment
    while(num_ways>=1) {
        num_ways/=10;
        num_digits++;
    }

    int counter=1; //for printing out which way we are on
    int counter_way; //keeps track of which int we are on in each way
    int size_way; //the number of ints in each way

    for(const auto &way:ways) {
        cout<<setw(num_digits)<<counter; //sets width to the number of digits, so that all numbers are aligned
        cout<<". [";
        size_way=way.size(); //sets the size of the current way, used to keep track of if we're at the end of a cartain way
        counter_way=1;
        for(const auto &num:way) {
            if(counter_way==size_way) { //if at the end of the current way
                cout<<num; //print only the number, no comma (last number)
            }
            else {
                cout<<num<<", ";
            }
            counter_way++;
        }
        cout<<"]"<<endl; //end of a way
        counter++;
    }
}

int main(int argc, char * const argv[]) {
    istringstream iss;
    int num;

    if(argc!=2) { //if 0 or more than 1 arguments are given (not valid)
        cerr<<"Usage: ./stairclimber <number of stairs>"<<endl;
        return 1;
    }

    iss.str(argv[1]);
    if(!(iss>>num) || num<=0) { //if the given argument is not an integer, or it it is <= 0
        cerr<<"Error: Number of stairs must be a positive integer."<<endl;
        return 1;
    }

    vector<vector<int>> ways=get_ways(num); //gets the ways to climb a staircase with <num> stairs
    display_ways(ways); //outputs the results!
}
