//ME - C++17 - hope it compile
/*
 * Authors: Alhussain Almarhabi
 * */
//Reference - future review
/* Use assignment four, how to read files of .dat
 *Use prof. Kruger matrix class and modify it
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Matrix {
private:
    int rows,cols;
    double* m;
    Matrix(int r, int c) : rows(r), cols(c), m(new double[r*c]) {}

public:
    Matrix(int r, int c, double val) : rows(r), cols(c), m(new double[r*c]) {
        for (int i = 0; i < r*c; i++)
            m[i] = val;
    }
    ~Matrix() {
        delete [] m; //O(1)
    }
    Matrix(const Matrix& orig) : rows(orig.rows), cols(orig.cols), m(new double[rows*cols]) {
        for (int i = 0; i < rows*cols; i++)
            m[i] = orig.m[i]; //O(r*c)
    }
    //copy and swap
    Matrix& operator =(const Matrix& orig) {
        Matrix copy(orig); //O(rows*cols)
        swap(m, copy.m);//O(1)
        rows = copy.rows;//O(1)
        cols = copy.cols;//O(1)
        return *this;
    }
#if 1
    double operator[](int i) const {
        return m[i] ;
    }
    double& operator[](int i) {
        return m[i];
    }
#endif
    // move constructor
    Matrix(Matrix& orig) : rows(orig.rows),  cols(orig.cols) {
        m = orig.m;
        orig.m = nullptr;
    }
    void display() {
        for (int i = 0 ; i<rows*rows; i++){
            cout << this->m[i]<< "  ";
            if (i % this->rows == (this->rows - 1)){cout << endl;}
        }
    }
    //O(rows*cols) if they are the same O(n^2)
    friend Matrix operator +(const Matrix& a, const Matrix& b) {
        if (a.rows != b.rows || a.cols != b.cols)
            throw "Bad matrix size";
        Matrix ans(a.rows,a.cols); //O(1)
        for (int i = 0; i < a.rows*a.cols; ++i)
            ans.m[i] = a.m[i] + b.m[i];
        return ans; //O(1)
    }

    double  operator()(int i, int j) const {
        return m[i*cols+j];
    }
    double&  operator()(int i, int j) {
        return m[i*cols+j];
    }
    friend Matrix operator *(const Matrix& a, const Matrix& b) {
        if (a.cols != b.rows) {
            throw "Bad matrix size";
        }
        Matrix ans(a.rows, b.cols);
        for (int i = 0; i < a.rows; ++i){
            for (int j = 0; j < b.cols; ++j) {
                double dot = 0;
                for (int k = 0; k < a.cols; k++){
                    dot += a(i, k) * b(k, j);
                }
                ans(i,j) = dot;
            }
        }
        return ans;
    }
    static Matrix read(istream& s) {
        int n;
        s >> n;
        cout<< "Number of rows: " << n<< endl;
        Matrix m(n,n);
        for (int i = 0; i < n*n; i++) {
            s >> m.m[i];
            cout << m.m[i] ;
            cout << "    ";
            if ( (i % n) == n-1)
                cout << endl;
        }
        return m;
    }

    void partialPivot(int i, vector<double>& B) {
        int biggestPos = i;
        double biggest = (*this)(i,i);

        // partial pivoting
        for (int j = i; j < rows; j++) {
            if (std::abs((*this)(j,i)) > std::abs(biggest)) {
                biggest = (*this)(j,i);
                biggestPos = j;
            }
        }
        double temp;
        for (int j = 0; j < rows; j++) {
            temp = (*this)(i,j);
            (*this)(i,j) = (*this)(biggestPos,j);
            (*this)(biggestPos,j) = temp;
        }
        temp = B[i];
        B[i] = B[biggestPos];
        B[biggestPos] = temp;
    }

    friend void backSubstitute(Matrix& m, vector<double>& x, vector<double>& B) {
        for (int n = m.rows  ; n > 0; n--) {
            x[n - 1] = B[n - 1] / m(n - 1, n - 1);
            for (int j = n - 2; j >= 0; j--) {
                B[j] -= m(j, n) * x[n - 1];
            }
        }
    }
    friend vector<double> solve(Matrix &m, vector<double> &B) {
        vector<double> x;
        // rows = cols or we are DEAD
        x.reserve(m.rows);
        for (int i = 0; i < m.rows; i++) {
            m.partialPivot(i, B);
            for (int k = i + 1; k < m.rows; k++) {
                double s = -m(k, i) / m(i, i);
                m(k, i) = 0; // make sure this is exactly zero! // i+1 was j
                for (int j = i + 1; j < m.cols; j++) {
                    m(k, j) += s * m(i, j); // modify remaining part of row
                }
                B[k] += s * B[i];
            }
            backSubstitute(m, x, B);
        }
        return x;
    }


};

vector<double> read(int n, istream& s) {
    vector<double> B;
    B.reserve(n);
    double tmp;
    for (int i = 0; i < n; ++i) {
        s >> tmp;
        B.push_back(tmp);
    }
    return B;
}

int main() {
    ifstream f("./mat.dat");
    cout << "Read Matrix A: "<<endl;
    Matrix A = Matrix::read(f);
    cout << endl;
    cout << "Read Vector B: " << endl;
    vector<double> B = read(10, f);
    for (int i=0; i < 10; i++){
        cout << B[i]<<endl;
    }

    cout << endl;
    vector<double> x = solve(A, B);
    cout << "The solution for x in Ax=b is: " << endl;
    for (int i = 0; i< 10; i++){
        cout << x[i] << endl;
    }
    // you must print out the vector x
    cout << endl;
    cout << "modified A after backward subtituion"<<endl;
    A.display();
    cout<<endl;
    cout << "modified B after backward subtitution" << endl;
    for (int i = 0; i<10; i++){ cout<< B[i]<<endl;}


}