#include <iostream>
using namespace std;

static void swap(int array[], const int a, const int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void bubble_sort_opt(int array[], const int length) {
    cout<<"START: ";
    for(int i = 0; i <= length - 2;) {
        cout<<"[";
        for(int x=0; x<length; x++) {
            cout<<array[x]<<", ";
        }
        int s = 0;
        for(int j = 0; j <= length - 2 - i; j++) {
            if(array[j + 1] < array[j]) {
                swap(array, j, j + 1);
                s = j;
            }
        }
        i = length - s - 1;
        cout<<endl;
    }
    cout<<"LAST: [";
    for(int x=0; x<length; x++) {
            cout<<array[x]<<", ";
        }
    cout<<endl;
}


void selection_sort(int array[], const int length) {
    cout<<"START: ";
    for(int i = 0; i < length - 1; i++) {
        cout<<"[";
        for(int x=0; x<length; x++) {
            cout<<array[x]<<", ";
        }
        int min_j = i;
        for(int j = i + 1; j < length; j++) {
            if(array[j] < array[min_j]) {
                min_j = j;
            }
        }
        if(min_j != i) {
            swap(array, i, min_j);
        }
        cout<<endl;
    }
    cout<<"LAST: [";
    for(int x=0; x<length; x++) {
            cout<<array[x]<<", ";
        }
    cout<<endl;
}

void insertion_sort(int array[], const int length) {
    cout<<"START: ";
    for(int i = 1; i < length; i++) {
        cout<<"[";
        for(int x=0; x<length; x++) {
            cout<<array[x]<<", ";
        }
        int j, current = array[i];
        for(j = i - 1; j >= 0 && array[j] > current; j--) {
            array[j + 1] = array[j];
        }
        array[j + 1] = current;
        cout<<endl;
    }
    cout<<"LAST: [";
    for(int x=0; x<length; x++) {
            cout<<array[x]<<", ";
        }
    cout<<endl;
}



int main() {
    int array[]={78,15,23,2,97,85};
    insertion_sort(array,6);
    return 0;
}