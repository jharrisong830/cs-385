/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : John Graham
 * Date        : 11/10/22
 * Description : Karatsuba algorithm in C++
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
using namespace std;

//pads str with 0's at the front until it is of length n
string normalize_length(long unsigned int n, string str) {
    if(n%2!=0) {
        n++;
    }
    return str.insert(0, n-str.length(), '0');
}

//finds the lowest power of 2 that is greater than the string length
int pad(int n) {
    int mult_2=1;
    while(mult_2<n) { 
        mult_2=mult_2<<1;
    }
    return mult_2;
}

//removes any extra padded 0's from the front of str (unless str is a single character string of "0")
string remove_padding(string str) {
    long unsigned int n=0;
    while(str.at(n)=='0' && str.length()-1!=n) {
        n++;
    }
    return str.substr(n, str.length()-n); //str[n:];
}

string add(const string& a, const string& b) {
    char char_a, char_b, curr_sum;
    bool carry=false;
    string result="";
    string str_a=a;
    string str_b=b;
    while(str_a.length()!=0 && str_b.length()!=0) { //iterating right to left through a and b
        if(carry) { //if we are carrying in a value from the previous iteration...
            carry=false; //...now set carry as false (for now)...
            curr_sum='1'; //...and set the current sum to be 1 (since we are carrying a 1 from the addition in the previous digit place)
        }
        else {
            curr_sum='0'; //else, reset the current sum for this digit place to be 0
        }
        char_a=str_a.back(); //character at the B^(length-(i+1)) place of a
        char_b=str_b.back(); //character at the B^(length-(i+1)) place of b
        str_a.pop_back();
        str_b.pop_back();
        /*while(char_a!='0') { //while char_a still has a value...
            curr_sum++; //...increment the sum...
            char_a--; //...and decrement char_a (taking value from char_a and adding it to a running sum for this decimal place)
            if(curr_sum>'9') { //if the value of the current sum is greater than the character '9', then we must carry out for our next addition
                curr_sum='0'; //reset the sum
                carry=true; //set carry as true (this will start us with a carry in value later)
            }
        }
        while(char_b!='0') { //same as above, but now we are adding the value of char_b to our current sum
            curr_sum++;
            char_b--;
            if(curr_sum>'9') {
                curr_sum='0';
                carry=true;
            }
        }*/
        curr_sum+=char_a-48;
        curr_sum+=char_b-48;
        if(curr_sum>'9') {
            curr_sum-=10;
            carry=true;
        }
        result.insert(0, 1, curr_sum); //puts the current sum for this digit place at the start of the result string)
    }
    while(str_a.length()!=0) {
        if(carry) { //if we are carrying in a value from the previous iteration...
            carry=false; //...now set carry as false (for now)...
            curr_sum='1'; //...and set the current sum to be 1 (since we are carrying a 1 from the addition in the previous digit place)
        }
        else {
            curr_sum='0'; //else, reset the current sum for this digit place to be 0
        }
        char_a=str_a.back(); //character at the B^(length-(i+1)) place of a
        str_a.pop_back();
        curr_sum+=char_a-48;
        if(curr_sum>'9') {
            curr_sum-=10;
            carry=true;
        }
        result.insert(0, 1, curr_sum); //puts the current sum for this digit place at the start of the result string)
    }
    while(str_b.length()!=0) {
        if(carry) { //if we are carrying in a value from the previous iteration...
            carry=false; //...now set carry as false (for now)...
            curr_sum='1'; //...and set the current sum to be 1 (since we are carrying a 1 from the addition in the previous digit place)
        }
        else {
            curr_sum='0'; //else, reset the current sum for this digit place to be 0
        }
        char_b=str_b.back(); //character at the B^(length-(i+1)) place of b
        str_b.pop_back();
        curr_sum+=char_b-48;
        if(curr_sum>'9') {
            curr_sum-=10;
            carry=true;
        }
        result.insert(0, 1, curr_sum); //puts the current sum for this digit place at the start of the result string)
    }
    if(carry) { //if we have a carry out after the last digit place, put '1' at the start of the result string
        result.insert(0, 1, '1');
    }

    return result;
}
string subtract(const string& a, const string& b) {
    string str_a=a;
    string str_b=b;
    char char_a, char_b, curr_diff;
    bool carry=false;
    string result="";
    while(str_b.length()!=0) { //iterating right to left through a and b
        char_a=str_a.back(); //character at the B^(length-(i+1)) place of a
        char_b=str_b.back(); //character at the B^(length-(i+1)) place of b
        str_a.pop_back(); 
        str_b.pop_back(); 
        if(carry) { //if we had to borrow a 10 from the previous iteration...
            if(char_a=='0') { //if we needed to carry again...
                char_a='9'; //...add 9 to the value of char_a (adding ascii values), like double-borrowing from subtraction (='9' because we have already borrowed from this digit place)
            } //we keep carry=true, because we have already carried from the next digit place 
            else { //else, we are able to properly modify after borrowing... 
                carry=false; //...set carry to be false...
                char_a--; //...and decrement the current char_a by 1 (like you would when borrowing from the next place over when subtracting)
            }
        }
        if(char_b=='0') { //if char_b has no value, then curr_diff = char_a (no need to compute, so we can skip everything below)
            result.insert(0, 1, char_a);
            continue;
        }
        curr_diff=char_a; //set the current difference to be char_a
        /*while(char_b!='0') { //while char_b still has value...
            if(curr_diff<char_b) { //if the current difference is less than char_b (i.e. if we have a-b and a<b), then we must borrow
                curr_diff+=10; //add 10 to the value of curr_diff (adding ascii values), like borrowing a 10 in subtraction
                carry=true; //set carry to be true
            }
            curr_diff--; //decrement the current difference...
            char_b--; //...and decrement char_b (we have subtracted 1 from char_a, and keep doing this until all of char_b has been subtracted from char_a)
        }*/
        curr_diff=char_a-char_b+48;
        if(curr_diff<'0') {
            carry=true;
            curr_diff+=10;
        }
        result.insert(0, 1, curr_diff); //put the new curr_diff at the start of the result
    }
    while(str_a.length()!=0) {
        char_a=str_a.back();
        str_a.pop_back();
        if(carry) {
            if(char_a=='0') { //if we needed to carry again...
                char_a='9'; //...add 9 to the value of char_a (adding ascii values), like double-borrowing from subtraction (='9' because we have already borrowed from this digit place)
            } //we keep carry=true, because we have already carried from the next digit place 
            else { //else, we are able to properly modify after borrowing... 
                carry=false; //...set carry to be false...
                char_a--; //...and decrement the current char_a by 1 (like you would when borrowing from the next place over when subtracting)
            }
        }
        result.insert(0, 1, char_a);
    }


    return result;
}

//multiplies a and b using the Karatsuba algorithm
string multiply(const string& a, const string& b, int n) { //NOTE: at this point, a and b are properly padded to be of equal length AND to have a length that is a power of 2
    //int n=a.length();
    //int mult_2;
    string result;
    if(n==1) { //base case: 1-digit multiplication
        int a_int=stoi(a);
        int b_int=stoi(b);
        result=to_string(a_int*b_int);
        return result; //returns a*b (in string form)
    }
    string a0, a1, a_sum, b0, b1, b_sum, c0, c1, c2, c_diff;

    a1=a.substr(0, n/2); //a1 = leftmost digits of a
    a0=a.substr(n/2, n-(n/2)); //a0 = rightmost digits of a
    b1=b.substr(0, n/2); //b1 = leftmost digits of b
    b0=b.substr(n/2, n-(n/2)); //b0 = rightmost digits of b

    c0=multiply(a0, b0, n/2); //c0 = a0 * b0 (no normalizing needed, since a and b are already powers of 2)
    c0=remove_padding(c0);

    a_sum=add(a0, a1);
    int a_sum_length=pad(a_sum.length()); //finds the minimum length of a string so that a_sum has even number of digits
    b_sum=add(b0, b1);
    int b_sum_length=pad(b_sum.length()); //finds the minimum length of a string so that b_sum has even number of digits
    int mult_2=max(a_sum_length, b_sum_length);
    a_sum=normalize_length(mult_2, a_sum);
    b_sum=normalize_length(mult_2, b_sum);

    c1=multiply(a_sum, b_sum, max(a_sum_length, b_sum_length)); //c1 = (a0 + a1) * (b0 + b1)
    c1=remove_padding(c1);

    c2=multiply(a1, b1, n/2); //c2 = a1 * b1 
    c2=remove_padding(c2);

    //c1=normalize_length(max(c1.length(), c2.length()), c1); //normalize so that the arguments to be subtracted have equal length
    //c2=normalize_length(max(c1.length(), c2.length()), c2);
    c_diff=subtract(c1, c2);
    //c_diff=normalize_length(max(c_diff.length(), c0.length()), c_diff); //normalize so that the arguments to be subtracted have equal length
    //c0=normalize_length(max(c_diff.length(), c0.length()), c0);
    c_diff=subtract(c_diff, c0); //c_diff = c1 -c2 - c0
    for(int i=0; i<n/2; i++) {
        c_diff.append("0"); //c_diff = (c1 -c2 - c0) * B^(n/2), where B=base10
    }

    for(int i=0; i<n; i++) { //c2 * B^n, where B=base10
        c2.append("0"); //NOTE: appending '0' is the same as multiplying by 10
    }

    //c_diff=normalize_length(max(c_diff.length(), c2.length()), c_diff); //normalize so that the arguments to be added have equal length
    //c2=normalize_length(max(c_diff.length(), c2.length()), c2);
    result=add(c_diff, c2);
    //c0=normalize_length(max(c0.length(), result.length()), c0); //normalize so that the arguments to be added have equal length
    //result=normalize_length(max(c0.length(), result.length()), result);
    result=add(result, c0);
    return result; //result = a*b = c2 * B^n + (c1 -c2 - c0) * B^(n/2) + c0
}

int main(int argc, char* argv[]) {
    string a=argv[1];
    string b=argv[2];

    a=remove_padding(a);
    b=remove_padding(b);
    int mult_2=pad(max(a.length(), b.length())); //normalizing lengths to nearest multiple of 2, to make multiplying easier
    a=normalize_length(mult_2, a);
    b=normalize_length(mult_2, b);

    string result=multiply(a, b, mult_2);
    result=remove_padding(result);
    result.append("\n");
    cout<<result;
}