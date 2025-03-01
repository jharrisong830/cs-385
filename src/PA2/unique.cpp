/*******************************************************************************
 * Name        : unique.cpp
 * Author      : John Graham
 * Date        : 9/22/22
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

/**returns true if all characters in a string are lowercase letters, and false if any other characters are detected*/
bool is_all_lowercase(const string &s) {
    int counter=0;
    char curr_char=s[counter];

    while(curr_char!='\0') { //while not at the null-terminator (end of string)
        if(!islower(curr_char)) { //not a lowercase letter
            return false;
        }
        counter++;
        curr_char=s[counter];
    }
    return true;
}

/**returns true if all letters in a string are unique, and false otherwise*/
bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.
    unsigned int vector=0; //used for storage
    unsigned int setter;

    int counter=0;
    char curr_char=s[counter];

    while(curr_char!='\0') { //while not at the null-terminator (end of string)
        setter=1<<(curr_char-'a');
        if((setter&vector)!=0) { //if the letter has already been encountered before
            return false;
        }
        else { //not encountered, record the variable in the vector
            vector=vector|setter;
            counter++;
            curr_char=s[counter];
        }
    }
    return true;
}

/**reads a string from the command line, and determines if all of the letters are unique. Only accepts one argument,
 * with only lowercase letters*/
int main(int argc, char * const argv[]) {
    if(argc!=2) { //none or too many arguments
        cerr<<"Usage: ./unique <string>"<<endl;
        return 1;
    }
    else if(!is_all_lowercase(argv[1])) { //argument includes non-lowercase letters
        cerr<<"Error: String must contain only lowercase letters."<<endl;
        return 1;
    }
    else if(all_unique_letters(argv[1])) { //yay! (in Meunier's voice), all letters are unique
        cout<<"All letters are unique."<<endl;
        return 0;
    }
    else { //duplicate letters
        cout<<"Duplicate letters found."<<endl;
        return 0;
    }
}
