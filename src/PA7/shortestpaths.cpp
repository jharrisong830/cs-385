/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : John Graham & Emma Hodor
 * Version     : 1.0
 * Date        : 12/07/22
 * Description : shortest path with floyd's algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <vector>
using namespace std;

int number_length(int number) {
    if(number==0) {
        return 1;
    }
    int counter=0;
    while(number>=1) {
        counter++;
        number=number/10;
    }
    return counter;
}


string path_string(string p, char curr, char dst, int row, int col, long **distance, long ** intermediate, long vertices) {
    string dst_ = "";
    dst_.insert(0, " -> ");
    long c = intermediate[row][col];
    
    p.append(dst_);
    if (c == 999999999999999999) {
        return p;
    }
    else {
        
        long curr_min=999999999999999999;
        long curr_char=c;
        for(int i=0; i<vertices; i++) {
            if(row!=i) {
                if(distance[row][i]<curr_min && intermediate[row][i]!=999999999999999999 && curr_char!=intermediate[row][i]) {
                    curr_min=distance[row][i];
                    curr_char=intermediate[row][i];
                }
            }
        }
        p.push_back(char(curr_char + 'A'));
        
        row = curr_char;
        return path_string(p, curr, dst, row, col, distance, intermediate, vertices);
    }} 
/**
 * Displays the matrix on the screen formatted as a table.
 */
void display_table(long **const matrix, const string &label, int num_vertices, const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix[i][j];
            if (cell !=999999999999999999 && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? number_length(max_val) : number_length(max(static_cast<long>(num_vertices), max_val));
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == 999999999999999999) {
                cout << "-";
            }
            else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            }
            else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./shortestpaths <filename>" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    input_file.exceptions(ifstream::badbit);
    string line;
    istringstream iss;
    int vertices;
    int check;
    vector<char> first_char;
    vector<char> second_char;
    vector<int> edges;
    try {
        unsigned int line_number = 1;
        while (getline(input_file, line)) {
            iss.str(line);
            if(line_number==1 && (!(iss>>vertices) || vertices<1 || vertices >26)) {
                cerr<<"Error: Invalid number of vertices '"<<line<<"' on line "<<line_number<<".";
                return 1;
            }
            else if(line_number==1) {
                line_number++;
                continue;
            }
            else if(line_number!=1 && line.length()<5) {
                cerr<<"Error: Invalid edge data '"<<line<<"' on line "<<line_number<<".";
                return 1;
            }
            else if(line_number!=1 && (line.at(0) > (64+vertices) || line.at(0) < 65 || line.at(1)!=32)) {
                cerr<<"Error: Starting vertex '"<<line.substr(0, line.rfind(" ", line.rfind(" ")-1))<<"' on line "<<line_number<<" is not among valid values "<<(char)(65)<<"-"<<(char)(64+vertices)<<".";
                return 1;
            }
            else if(line_number!=1 && (line.at(2) > (64+vertices) || line.at(2) < 65 || line.at(3)!=32)) {
                cerr<<"Error: Ending vertex '"<<line.substr(2, line.rfind(" ")-2)<<"' on line "<<line_number<<" is not among valid values "<<(char)(65)<<"-"<<(char)(64+vertices)<<".";
                return 1;
            }
            iss.clear();
            iss.str(line.substr(4));
            if(line_number!=1 && (!(iss>>check) || (stoi(line.substr(4)))<=0)) {
                cerr<<"Error: Invalid edge weight '"<<line.substr(4)<<"' on line "<<line_number<<".";
                return 1;
            }
            first_char.push_back(line.at(0));
            second_char.push_back(line.at(2));
            edges.push_back(stoi(line.substr(4)));
            line_number++;
            iss.clear();
        }
        input_file.close();
        
        long **distance = new long*[vertices];
        long **intermediate_vertices=new long*[vertices];
        for(int i=0; i<vertices; i++) {
            distance[i] = new long[vertices];
            intermediate_vertices[i]=new long[vertices];
            for(int j=0; j<vertices; j++) {
                if(i!=j) {
                    distance[i][j]=999999999999999999;
                    intermediate_vertices[i][j]=999999999999999999;
                }
                else {
                    distance[i][j]=0;
                }
            }
        }

        while(!edges.empty()) {
            distance[first_char.back()-65][second_char.back()-65]=edges.back();
            first_char.pop_back();
            second_char.pop_back();
            edges.pop_back();
        }


        string s="Distance matrix:";
        display_table(distance, s, vertices);

        for(int k=0; k<vertices; k++) {
            for(int i=0; i<vertices; i++) {
                for(int j=0; j<vertices; j++) {
                    if(distance[i][k]==999999999999999999 || distance[k][j]==999999999999999999) {
                        continue;
                    }
                    else if(i==j || j==k || i==k) {
                        continue;
                    }
                    else if(distance[i][j] > distance[i][k]+distance[k][j]) {
                        distance[i][j]=distance[i][k]+distance[k][j];
                        intermediate_vertices[i][j]=k;
                    }
                }
            }
        }

        for(int i=0; i<vertices; i++) {
            for(int j=0; j<vertices; j++) {
                if(i==j) {
                    distance[i][j]=0;
                    intermediate_vertices[i][j]=999999999999999999;
                }
            }
        }

        s="Path lengths:";
        display_table(distance, s, vertices);
        s="Intermediate vertices:";
        display_table(intermediate_vertices, s, vertices, true);

        //vector<char> path;
        string path = "";
        for(int i=0; i<vertices; i++) {
            for(int j=0; j<vertices; j++) {
                if(i==j) {
                    char curr_char=i+'A';
                    char dst_char=j+'A';
                    cout<<curr_char<<" -> "<<dst_char<<", distance: "<<distance[i][j]<<", path: "<<curr_char<<endl;
                }
                else if(distance[i][j]!=999999999999999999) {
                    char curr_char=i+'A';
                    char dst_char=j+'A';
                    cout<<curr_char<<" -> "<<dst_char<<", distance: "<<distance[i][j]<<", path: "<<curr_char;
                    //determining path goes here
                    long row = i;
                    long col = j;
                    //char d;
                    //long c;
                    //path.clear();
                    /*while (intermediate_vertices[row][col] < 999999999999999999) {
                        c = intermediate_vertices[row][col];
                        path.push_back((char(c+'A')));
                        col=c;
                    }
                    cout<<" -> ";
                    while(!path.empty()) {
                        curr_char=path.back();
                        path.pop_back();
                        cout<<curr_char<<" -> ";
                    } */
                    string p;
                    string path=path_string(p, curr_char, dst_char, row, col, distance, intermediate_vertices, vertices);
                    cout<<path;
                    
                    cout<<dst_char<<endl;
                }
                else {
                    cout<<(char)(i+'A')<<" -> "<<(char)(j+'A')<<", distance: infinity, path: none"<<endl;
                }
            }
        }
        for(int i = 0; i < vertices; i++) {
            delete [] distance[i];
        }
        delete [] distance;
        for(int i = 0; i < vertices; i++) {
            delete [] intermediate_vertices[i];
        }
        delete [] intermediate_vertices;
    }
    catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}