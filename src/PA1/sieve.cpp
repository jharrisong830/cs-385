/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : John Graham
 * Date        : 09/12/22
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() { //must be included to delete the array in memory after we are done with this object (needed when we make a **new** object, like the pointer array)
        delete [] is_prime_; //this is called a destructor
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables, COMPUTE THESE PROPERLY IN THE CONSTRUCTOR
    bool * const is_prime_; //pointer to array of booleans. you
    const int limit_; //upper limit for search (n)
    int num_primes_, max_prime_; //number of primes, and the largest prime number

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {  //NOTE:this is an initializer list, see Classes notes
    sieve();
}

/**displays all of the prime numbers up to the limit (in a very organized way!)*/
void PrimesSieve::display_primes() const {
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);

    cout<<endl<<"Number of primes found: "<<num_primes_<<endl;
    cout<<"Primes up to "<<limit_<<":"<<endl;

    int counter=0;
    for(int i=2; i<=limit_; i++) {
        if(is_prime_[i]) {
            if(num_primes_<primes_per_row) { //if there is only one row, no need to right-align
                if(counter==0) {
                    //do nothing
                }
                else {
                    cout<<setw(num_digits(i)+1); //single space between every prime
                }
            }
            else if(counter==0) { //if at the start of a new row, set the width to that of the max prime
                cout<<setw(max_prime_width);
            }
            else { //else, set the width to that of the max prime +1 (right-aligns every number)
                cout<<setw(max_prime_width+1);
            }

            cout<<i;
            counter++;

            if(counter==primes_per_row) { //starting new row
                counter=0;
                cout<<endl;
            }
        }
    }
    cout<<endl;
}

/**counts the total number of primes found up to (and including) the limit*/
int PrimesSieve::count_num_primes() const { //FINISHED
    int counter=0;
    for(int i=2; i<=limit_; i++) {
        if(is_prime_[i]) {
            counter++;
        }
    }
    return counter;
}

/**performs the sieve algorithm to find all primes up to and including the limit*/
void PrimesSieve::sieve() {
    for(int i=0; i<=limit_; i++) { //initialize array
        if(i==0 || i==1) {
            is_prime_[i]=false;
        }
        else {
            is_prime_[i]=true;
        }
    }


    for(int i=2; i<=sqrt(limit_); i++) { //sieve algorithm
        if(is_prime_[i]) {
            for(int j=i*i; j<=limit_; j+=i) {
                is_prime_[j]=false;
            }
        }
    }

    for(int i=limit_; i>=0; i--) { //finding the max prime
        if(is_prime_[i]) {
            max_prime_=i;
            break;
        }
    }

    num_primes_=count_num_primes(); //sets total number of primes
    
    display_primes(); //displays everything!
}

/**calculates the number of digits that a number has*/
int PrimesSieve::num_digits(int num) { //FINISHED
    double number=num;
    int counter=0;
    while(number>=1) {
        counter++;
        number=number/10;
    }
    return counter;
}

/**main function for running the sieve program*/
int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve s1=PrimesSieve(limit);

    return 0;
}
