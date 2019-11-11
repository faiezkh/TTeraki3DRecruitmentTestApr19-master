#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include<vector>
#include <list>
#include <iterator>
#include <math.h>

using namespace std;

struct point{
    double x,y,z,reflectivity;
    int index;
};

int ReadNumbers( const string & s, vector <double> & v );
void import_matrix_from_txt_file(const char* filename_X, vector <double>& v, int& rows, int& cols);
void file_PLY_to_file_txt(const char* filename_X);
void matrix_to_point_matrix(vector <double>& v, int& rows, int& cols, vector <struct point>& matrix_point);
double cartesian_distance(struct point p1,struct point p2);
void cartesian_distance_point_table(struct point p,vector <struct  point> tab,vector <double>& v);
void re_arrange_point_table(vector <struct point> v1, vector <struct point> v2,vector <struct point>& v3);
double min_table(vector <double>& v);
void output_file(vector <struct point> v1,vector <struct point> v2,const char* output_file_name);

void output(const char* file1, const char* file2,vector <double>& v,int& rows,int & cols,vector <struct point>& matrix_point, vector <double>& va,int& rowsA,int & colsA,vector <struct point>& matrix_pointA){

    //uncompressed file

    file_PLY_to_file_txt("Car_XYZI_uncompressed_ASCII.ply");
    import_matrix_from_txt_file("file2.txt",v,rows,cols);
    matrix_to_point_matrix( v,rows, cols, matrix_point);

    const int rem = remove("file2.txt");

    //decompressed file

    file_PLY_to_file_txt(file1);
    import_matrix_from_txt_file("file2.txt",va,rowsA,colsA);
    matrix_to_point_matrix( va,rowsA, colsA, matrix_pointA);
    vector <struct point> v2_2;
    re_arrange_point_table(matrix_point,matrix_pointA,v2_2);
    output_file(matrix_point,v2_2,file2);

}

int main() {

    /*vector<double> v;
    vector<struct point> matrix_point;
    int rows = 0;
    int cols = 0;

    //decompressed file

    vector<double> va;
    vector<struct point> matrix_pointA;
    int rowsA = 0;
    int colsA = 0;

    output("Exemple_Decomp.ply", "output_Exemple", v, rows, cols, matrix_point, va, rowsA, colsA,
           matrix_pointA);*/

    char c;

    cout << "which .PLY file you would see ?" << endl;
    cout << "if A write a, if B write b and if C write c" << endl;
    cin >> c;

    switch (c) {
        case 'a': {
            //uncompressed file

            vector<double> v;
            vector<struct point> matrix_point;
            int rows = 0;
            int cols = 0;

            //decompressed file

            vector<double> va;
            vector<struct point> matrix_pointA;
            vector<struct point> matrixa;
            int rowsA = 0;
            int colsA = 0;

            const int rem = remove("file2.txt");

            output("Car_XYZI_decompressed_ASCII_A.ply", "output_A", v, rows, cols, matrix_point, va, rowsA, colsA,
                   matrix_pointA);
        }
        break;
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 'b': {
            //uncompressed file

            vector<double> v2;
            vector<struct point> matrix_point2;
            int rows2 = 0;
            int cols2 = 0;

            //decompressed file

            vector<double> vb;
            vector<struct point> matrix_pointB;
            vector<struct point> matrixb;
            int rowsB = 0;
            int colsB = 0;

            const int rem1 = remove("file2.txt");

            output("Car_XYZI_decompressed_ASCII_B.ply", "output_B", v2, rows2, cols2, matrix_point2, vb, rowsB, colsB,
                   matrix_pointB);
        }
        break;
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 'c': {
            //uncompressed file

            vector<double> v3;
            vector<struct point> matrix_point3;
            int rows3 = 0;
            int cols3 = 0;

            //decompressed file

            vector<double> vc;
            vector<struct point> matrix_pointC;
            vector<struct point> matrixc;
            int rowsC = 0;
            int colsC = 0;

            const int rem2 = remove("file2.txt");

            output("Car_XYZI_decompressed_ASCII_C.ply", "output_C", v3, rows3, cols3, matrix_point3, vc, rowsC, colsC,
                   matrix_pointC);
        }
        break;
        default:
            cout << "choice not configured";
            break;
    }

    return 0;
}

int ReadNumbers( const string & s, vector <double> & v ) {
    istringstream is( s );
    double n;
    while( is >> n ) {
        v.push_back( n );
    }
    return v.size();
}

void import_matrix_from_txt_file(const char* filename_X, vector <double>& v, int& rows, int& cols){

    ifstream file_X;
    string line;

    file_X.open(filename_X);
    if (file_X.is_open())
    {
        int i=0;
        getline(file_X, line);

        cols =ReadNumbers( line, v );
        //cout << "cols:" << cols << endl;

        //for ( i=1;i<32767;i++){
        // if(getline(file_X, line)) break;
        //  ReadNumbers( line, v );
        //}

        while(getline(file_X,line))
        {
            ReadNumbers(line,v);
            i++;i<32767;
        }
        rows=i;
        //cout << "rows :" << rows << endl;
        if(rows >32766) cout<< "N must be smaller than MAX_INT";

        file_X.close();
    }
    else{
        cout << "file open failed";
    }

    /*cout << "v:" << endl;
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            std::cout << std::setprecision(9);
            cout << v[i*cols+j] << "\t" ;
        }
        std::cout << std::setprecision(9);
        cout << endl;
    }*/
}

void file_PLY_to_file_txt(const char* filename_X)
{
    string mystring,chaine;

    ifstream myfile;
    ofstream myfile2;
    myfile.open(filename_X, ios::in);
    myfile2.open("file2.txt", ios::out);
    if (!myfile.is_open()) {
        printf("Error we can't open the file");
        exit(1);
    }
    int j = 0;
    while(mystring != "end_header")
    {
        getline(myfile,mystring);
        j++;
    }

    while (getline(myfile, chaine)) {
        if (!myfile2.is_open()) {
            printf("Error we can't open the file");
            exit(2);
        }
        if(chaine.find("0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 0 0 2109 1 0 0")) {
            myfile2 << chaine << "\n";
        }

    }
    myfile2.close();
    myfile.close();
}

void matrix_to_point_matrix(vector <double>& v, int& rows, int& cols, vector <struct point>& matrix_point)
{
    double tab[4];
    struct point Point;
    for (int i = 0; i <rows ; ++i) {
        for (int j = 0; j <4 ; ++j) {
            std::setprecision(9);
            tab[j] = v[i*cols+j];
        }
        Point.x =tab[0];
        Point.y=tab[1];
        Point.z=tab[2];
        Point.reflectivity=tab[3];
        std::setprecision(9);
        matrix_point.push_back(Point);
    }

    /*for (int i = 0; i <rows ; ++i) {
        std::cout << std::setprecision(9);
        cout<<"point "<<i<<" : x = "<< matrix_point[i].x<<"| y = "<< matrix_point[i].y<<"| z  = "<<matrix_point[i].z<<"| reflectivity = "<<matrix_point[i].reflectivity<<endl;
    }*/
}

double cartesian_distance(struct point p1,struct point p2)
{
    double distance = 0;
    distance = sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2) + pow(p1.z - p2.z,2));
    return distance;
}

void cartesian_distance_point_table(struct point p,vector <struct point> tab,vector <double>& v)
{
    int rows = tab.size();
    //cout<<p.x<<" "<<p.y<<" "<<p.z<<" "<<p.reflectivity<<" "<<endl;
    for (int i = 0; i < rows-1; i++) {
        v.push_back(cartesian_distance(p,tab[i]));
        //cout<<tab[i].x<<" "<<tab[i].y<<" "<<tab[i].z<<" "<<tab[i].reflectivity<<" ";
        //cout<<cartesian_distance(p,tab[i])<<endl;
    }
}

double min_table(vector <double>& v)
{
    int rows = v.size();
    double min,max;
    max = v[0];
    for (int i = 0; i < rows; i++) {
        if(max < v[i]){
            max = v[i];
        }
    }

    min = v[0];
    for (int j = 0; j < rows; j++) {
        if(min > v[j]){
            min = v[j];
        }
    }
    return min;
}

void re_arrange_point_table(vector <struct point> v1, vector <struct point> v2,vector <struct point>& v3)
{
    int rows = v1.size();
    double min_distance;
    vector <int> point_min_distance;
    for (int i = 0; i < rows-1 ; i++) {
        vector <double> tab;
        cartesian_distance_point_table(v1[i],v2,tab);
        min_distance = min_table(tab);

        for (int j = 0; j < rows-1; j++) {
            int index =j;
            if(min_distance == tab[index]){
                point_min_distance.push_back(index);
            }
        }
    }

    for (int k = 0; k < rows-1 ; k++) {
        v3.push_back(v2[point_min_distance[k]]);
    }
}

void output_file(vector <struct point> v1,vector <struct point> v2, const char* output_file_name)
{
    int rows = v1.size();
    ofstream myfile;
    myfile.open(output_file_name, ios::out);
    if (!myfile.is_open()) {
        printf("Error we can't open the file");
        exit(1);
    }

    struct {
        int width;
        string header;
    } columns[] ={{15,"X_Uncomp"},{15,"Y_Uncomp"},{15,"Z_Uncomp"},{15,"ref_Uncomp"},
                  {15,"X_Decomp"},{15,"Y_Decomp"},{15,"Z_Decomp"},{15,"ref_Decomp"},
                  {15,"distance"}};

    for (auto& col : columns) myfile << std::setw(col.width) << col.header << " | ";
    myfile << "\n" << std::setfill('-');
    for (auto& col : columns) myfile << std::setw(col.width) << "" << "-+-";
    myfile << "\n" << std::setfill(' ');

    for (int j = 0; j < rows-1 ; j++) {
        myfile << std::setw(columns[0].width) << v1[j].x <<std::setprecision(12)<< " | "
            << std::setw(columns[1].width) << v1[j].y <<std::setprecision(12)<< " | "
            << std::setw(columns[2].width) << v1[j].z <<std::setprecision(12)<< " | "
            << std::setw(columns[3].width) << v1[j].reflectivity <<std::setprecision(12)<< " | "
            << std::setw(columns[4].width) << v2[j].x <<std::setprecision(12)<< " | "
            << std::setw(columns[5].width) << v2[j].y <<std::setprecision(12)<< " | "
            << std::setw(columns[6].width) << v2[j].z <<std::setprecision(12)<< " | "
            << std::setw(columns[7].width) << v2[j].reflectivity <<std::setprecision(11)<< " | "
            << std::setw(columns[8].width) << cartesian_distance(v1[j],v2[j])<< " |" << "\n";
    }

    for (auto& col : columns) myfile << std::setw(col.width) << std::setfill('-') << "" << "-+-";
    myfile << "\n";

    myfile.close();
}

