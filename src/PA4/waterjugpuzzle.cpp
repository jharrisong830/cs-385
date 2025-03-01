/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : John Graham & Emma Hodor
 * Date        : 10/7/22
 * Description : Solves the water jug puzzle using breadth-first search
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/


#include <iostream>
#include <sstream>
#include <queue>
#include <stack>
using namespace std;


/**Struct to represent state of water in the jugs. (default code from Canvas)*/
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    State() : a{0}, b{0}, c{0}, directions{""}, parent{nullptr} {} //default constructor
    
    /**String representation of state in tuple form*/
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

    /**Returns whether or not two states are equal (not including directions and their parents)*/
    bool equals(State compare) {
        if(a==compare.a && b==compare.b && c==compare.c) {
            return true;
        }
        return false;
    }
};


/**Checks if a transfer can be made from jug C to jug A*/
bool c_to_a(State current, int cA) {
    if(current.a==cA || current.c==0) { //if source is empty, or if destination is full, then return false
        return false;
    }
    return true;
}


/**Checks if a transfer can be made from jug B to jug A*/
bool b_to_a(State current, int cA) {
    if(current.a==cA || current.b==0) { //if source is empty, or if destination is full, then return false
        return false;
    }
    return true;
}


/**Checks if a transfer can be made from jug C to jug B*/
bool c_to_b(State current, int cB) {
    if(current.b==cB || current.c==0) { //if source is empty, or if destination is full, then return false
        return false;
    }
    return true;
}


/**Checks if a transfer can be made from jug A to jug B*/
bool a_to_b(State current, int cB) {
    if(current.b==cB || current.a==0) { //if source is empty, or if destination is full, then return false
        return false;
    }
    return true;
}


/**Checks if a transfer can be made from jug B to jug C*/
bool b_to_c(State current, int cC) {
    if(current.c==cC || current.b==0) { //if source is empty, or if destination is full, then return false
        return false;
    }
    return true;
}


/**Checks if a transfer can be made from jug A to jug C*/
bool a_to_c(State current, int cC) {
    if(current.c==cC || current.a==0) { //if source is empty, or if destination is full, then return false
        return false;
    }
    return true;
}


/**Prints the result of the BFS in reverse order (starting from the root state to the current state, based on parent pointers)*/
void print_state(State *state) {
    stack<State*> s;
    while((*state).parent!=nullptr) {
        s.push(state);
        state=(*state).parent;
    }
    s.push(state);
    while(!s.empty()) {
        state=s.top();
        cout<<(*state).directions<<" "<<(*state).to_string()<<endl;
        s.pop();
    }
}


/**Only exists bc the test cases check for grammar smh*/
string one_gallon(int amount_to_empty) {
    if(amount_to_empty==1) {
        return "gallon";
    }
    return "gallons";
}


/**Performs a breadth-first search to solve the water jug puzzle.*/
void water_jug_main(int cA, int cB, int cC, int gA, int gB, int gC) {
    State **array = new State*[cA+1]; //creates a 2D array with cA+1 rows..., which tracks whether a given state has been visited before
    for(int i=0; i<(cA+1); i++) { //...and cB+1 columns
        array[i] = new State[cB+1];
    }
    bool solved=false; //for if we should print if there are no solutions
    queue<State*> q, m; //q is queue for BFS, m is queue for memory management (stores pointers for all created states so they can be deleted later)
    State *initial=new State(0, 0, cC, "Initial state.");
    q.push(initial);
    m.push(initial);
    int amount_to_empty; //used to store the maximum possible water that a jug can receive, given its current contents

    while(!q.empty()) {
        State *current=q.front();
        q.pop();
        if((*current).a==gA && (*current).b==gB && (*current).c==gC) { //if goal state found, this is the solution
            solved=true;
            print_state(current); //prints out from this state all the way to the parent state, in reverse order (root first)
            break; //ends the BFS (we're at the goal!)
        }
        else if((array[(*current).a][(*current).b]).equals(*current)) { //if the current state has already been visited
            continue; //go to next iteration of loop
        }
        array[(*current).a][(*current).b]=*current; //set the current state as visited
        if(c_to_a(*(current), cA)) {
            amount_to_empty=cA-(*current).a; //max amount that can be received by the destination jug
            if(amount_to_empty>(*current).c) { //if max amount is greater than what is in the source jug
                amount_to_empty=(*current).c; //set max amount to what is in the source jug
            }
            State *new_current=new State((*current).a+amount_to_empty, (*current).b, (*current).c-amount_to_empty, "Pour "+to_string(amount_to_empty)+" "+one_gallon(amount_to_empty)+" from C to A."); //adds a new state to the heap
            (*new_current).parent=current; //set parent
            q.push(new_current); //push new state
            m.push(new_current); //to keep track of memory
        }
        if(b_to_a(*(current), cA)) {
            amount_to_empty=cA-(*current).a; //max amount that can be received by the destination jug
            if(amount_to_empty>(*current).b) { //if max amount is greater than what is in the source jug
                amount_to_empty=(*current).b; //set max amount to what is in the source jug
            }
            State *new_current=new State((*current).a+amount_to_empty, (*current).b-amount_to_empty, (*current).c, "Pour "+to_string(amount_to_empty)+" "+one_gallon(amount_to_empty)+" from B to A."); //adds a new state to the heap
            (*new_current).parent=current; //set parent
            q.push(new_current); //push new state
            m.push(new_current); //to keep track of memory
        }
        if(c_to_b(*(current), cB)) {
            amount_to_empty=cB-(*current).b; //max amount that can be received by the destination jug
            if(amount_to_empty>(*current).c) { //if max amount is greater than what is in the source jug
                amount_to_empty=(*current).c; //set max amount to what is in the source jug
            }
            State *new_current=new State((*current).a, (*current).b+amount_to_empty, (*current).c-amount_to_empty, "Pour "+to_string(amount_to_empty)+" "+one_gallon(amount_to_empty)+" from C to B."); //adds a new state to the heap
            (*new_current).parent=current; //set parent
            q.push(new_current); //push new state
            m.push(new_current); //to keep track of memory
        }
        if(a_to_b(*(current), cB)) {
            amount_to_empty=cB-(*current).b; //max amount that can be received by the destination jug
            if(amount_to_empty>(*current).a) { //if max amount is greater than what is in the source jug
                amount_to_empty=(*current).a; //set max amount to what is in the source jug
            }
            State *new_current=new State((*current).a-amount_to_empty, (*current).b+amount_to_empty, (*current).c, "Pour "+to_string(amount_to_empty)+" "+one_gallon(amount_to_empty)+" from A to B."); //adds a new state to the heap
            (*new_current).parent=current; //set parent
            q.push(new_current); //push new state
            m.push(new_current); //to keep track of memory
        }
        if(b_to_c(*(current), cC)) {
            amount_to_empty=cC-(*current).c; //max amount that can be received by the destination jug
            if(amount_to_empty>(*current).b) { //if max amount is greater than what is in the source jug
                amount_to_empty=(*current).b; //set max amount to what is in the source jug
            }
            State *new_current=new State((*current).a, (*current).b-amount_to_empty, (*current).c+amount_to_empty, "Pour "+to_string(amount_to_empty)+" "+one_gallon(amount_to_empty)+" from B to C."); //adds a new state to the heap
            (*new_current).parent=current; //set parent
            q.push(new_current); //push new state
            m.push(new_current); //to keep track of memory
        }
        if(a_to_c(*(current), cC)) {
            amount_to_empty=cC-(*current).c; //max amount that can be received by the destination jug
            if(amount_to_empty>(*current).a) { //if max amount is greater than what is in the source jug
                amount_to_empty=(*current).a; //set max amount to what is in the source jug
            }
            State *new_current=new State((*current).a-amount_to_empty, (*current).b, (*current).c+amount_to_empty, "Pour "+to_string(amount_to_empty)+" "+one_gallon(amount_to_empty)+" from A to C."); //adds a new state to the heap
            (*new_current).parent=current; //set parent
            q.push(new_current); //push new state
            m.push(new_current); //to keep track of memory
        }
    }

    while(!m.empty()) { //for every state created, delete it from the heap
        initial=m.front();
        m.pop();
        delete initial;
    }
    for(int i = 0; i < (cA+1); i++) {
        delete [] array[i]; //delete each row of the 2d array from the heap
    }
    delete [] array; //delete the original array from the heap

    if(!solved) { //printed only when puzzle isn't able to be solved :(
        cout<<"No solution."<<endl;
    }
}


/**Handles all errors for invalid input and syntax. Calls water_jug_main to try and solve water jug problem with given arguments*/
int main(int argc, char * const argv[]) {
    istringstream iss;
    int args[6]; //array for all command line arguments (capacities and goals)
    int curr_int; //current command line argument being processed
    char curr_jug; //character of the current jug (used for printing errors)

    if(argc!=7) { //if the wrong amount of arguments are given
        cerr<<"Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<<endl;
        return 1;
    }
    for(int i=1; i<=6; i++) { //iterates through all arguments and checks for invalid argument types (capacity > 0, goal >= 0)
        iss.str(argv[i]);
        if(i<=3) { //processing capacities...
            if(!(iss>>curr_int) || curr_int<=0) { //if the argument is not an int, or if it is less than or equal to 0 (invalid capacity)
                curr_jug='A'+(i-1);
                cerr<<"Error: Invalid capacity '"<<argv[i]<<"' for jug "<<curr_jug<<"."<<endl;
                return 1;
            }
        }
        else { //processing goals...
            if(!(iss>>curr_int) || curr_int<0) { //if the argument is not an int, or if it is less than 0 (invalid goal)
                curr_jug='A'+(i-4);
                cerr<<"Error: Invalid goal '"<<argv[i]<<"' for jug "<<curr_jug<<"."<<endl;
                return 1;
            }
        }
        args[i-1]=curr_int;
        iss.clear();
    }

    for(int i=3; i<=5; i++) { //iterates through each goal to see if it is greater than its respective capacity
        if(args[i]>args[i-3]) { //if the goal of the jug is greater than its capacity
            curr_jug='A'+(i-3);
            cerr<<"Error: Goal cannot exceed capacity of jug "<<curr_jug<<"."<<endl;
            return 1;
        }
    }
    if(args[2] != (args[3]+args[4]+args[5])) { //if the total gallons in the goal state is less than capacity of jug c
        cerr<<"Error: Total gallons in goal state must be equal to the capacity of jug C."<<endl;
        return 1;
    }

    water_jug_main(args[0], args[1], args[2], args[3], args[4], args[5]); //starts the puzzle!

    return 0;
}