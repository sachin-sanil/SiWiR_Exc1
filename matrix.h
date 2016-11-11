#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <assert.h>

using namespace std;

class matrix
{

    private:
	int pad=80;

    public:
    std::vector<double> data;
    int rows, cols;
    
    double& operator() (const int &i, const int &j)
    {
        assert((i > 0) && (i <= rows) && (j > 0) && (j <= rows));
        return data[(i-1)*(cols+pad)+j-1];
    }
    friend void read(std::string file_name, matrix &M);
    friend void multiply(matrix& A, matrix& B, matrix& C);
    friend void write(string file_name, matrix &M);
    int get_rows(){return rows;}
    int get_cols(){return cols;}
    matrix() = default;
    matrix(int i, int j):rows(i), cols(j){data.resize(rows*(cols+pad));}
    void reset(){fill(data.begin(), data.end(), 0);};


};
//void matrix::reset(){this->data(0);}

 void read(std::string file_name, matrix &M)
{
	//read the file and get the data in a temporary variable
	ifstream file(file_name);
	file >> M.rows; file >> M.cols;
     M.data.resize((M.rows)*(M.cols+M.pad));
    int i = 0;
    while (!file.eof())
    {
	
	for (auto j=0; j != M.rows; ++j){
        file >> M.data[i];
        ++i;
	}
	i+=M.pad;
    }

    file.close();
}

void write(std::string file_name, matrix &M)
{
	//read the file and get the data in a temporary variable
	ofstream file(file_name);
	file << M.rows << " "; file << M.cols << "\n";
    for (auto i = M.data.begin(); i!= M.data.end(); ++i)
    {
        file << *i << "\n";

    }

    file.close();
}




 //std::vector<double> write();

 //std::Vector<double>

#endif


