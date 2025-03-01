/******************************************************************************* 
 * Filename: sqrt.cpp 
 * Author  : John Graham 
 * Version : 1.0 
 * Date    : 9/6/22 
 * Description: A program that computes square roots using Newton's method.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
using namespace std;

double sqrt(double num, double epsilon) {
    if(num<0) {
        return numeric_limits<double>::quiet_NaN();
    }
    else if(num==0 or num==1) {
        return num;
    }
    else {
        double next_guess=1;
        double last_guess=1;
        do {
            last_guess=next_guess;
            next_guess = (last_guess + num/last_guess) / 2;
        } while(!(abs(last_guess - next_guess) <= epsilon));
        return next_guess;
    }
}

int main(int argc, char* argv[]) {
    double num, epsilon;
    istringstream iss; // input string stream variable
    if(argc!=3) {
        if(argc!=2) {
            cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
            return 1;
        }
    }
    iss.str(argv[1]);
    if(!(iss >> num)) {
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }
    iss.clear(); // Remember to clear iss before using it with another string!
    if(argc==2) {
        epsilon=1e-7;
    }
    else {
        iss.str(argv[2]);
        if(!(iss >> epsilon) || epsilon<=0) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    }
    cout<<fixed;
    cout << setprecision(8) << sqrt(num, epsilon) << '\n';
    return 0;
}