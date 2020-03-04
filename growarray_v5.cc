//ME - C++17 - hope it compile
/*
 * Authors: Alhussain Almarhabi
 * */
//Reference - future review
/* Use assignment four, how to read files of .dat
 *Use Kruger old examples and videos for growarray
 */
#include <iostream>
#include <fstream>
#include<string>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

template<class T>
class GrowArray {
private:
    uint32_t len;
    uint32_t capacity;
    T* data;

    void grow() //O(1)
    { // doubles the size
        capacity = 2*capacity;
    }

    void checkGrow() { //O(1)
        if (len == capacity)
            grow();
    }

public:

    GrowArray() : capacity(1) ,len(0), data(nullptr) {	} //O(1)
    ~GrowArray() {delete [] data;} //O(1)

    void addEnd(T v)
    { //O(n)
        T* old = data; //O(1)
        checkGrow();
        data = new T[len+1]; //O(1)
        for (int i = 0; i < len; i++) // O(len)
            data[i] = old[i];
        delete [] old; // O(1)
        data[len] = v;
        len++;
    }

    void addStart(T v)
    { //O(len) O(n)
        T* old = data; //O(1)
        data = new T[len++]; //O(1)
        data[0] = v;
        for (int i = 1; i <= len; i++) //O(len)
            data[i] = old[i-1];
        //len++;
        delete [] old;
    }

    void removeEnd()
    { //O(l)
        len--;
    }

    void removeStart()
    {//O(n)
        T* old = data; //O(1)
        data = new T[--len]; //O(!)
        for (int i = 0; i < len; i++) //O(len)
            data[i] = old[i+1];
        delete [] old; //O(1)
    }

    void insert(int i, T v)
    { //O(n/2)
        T* old = data;
        data = new T[len++];
        for (int j = 0; j < i; j++) //O(n/2)
            data[j] = old[j];
        data[i] = v;
        for (int j = i+1; j < len; j++) //O(n/2)
            data[j] = old[j-1];
        delete [] old; //O(1)
    }
    void showArray()
    {//O(n)
        if (this->len == 0){
            cout << "empty" << endl;

        }
        else {
            for (int i = 0; i < len; i++) {
                cout << data[i] << " ";
                if (i == len - 1)
                    cout << endl;
            }
        }
    }

    uint32_t size() const {
        return len;
    }

    T get(int i) { //O(1)
        return data[i];
    }


};

/// CLASS Point
class Point2d {
public:
    float x,y;
    /// two defult constructor with input and without
    Point2d(): x(0.0f), y(0.0f) {}
    Point2d(float x, float y) : x(x), y(y) {}
    /// use to set x and y of object point
    void setPoint(float x1, float y1){ //O(1)
        x = x1;
        y = y1;
    }
    void setPx(float x1){ //O(1)
        x = x1;
    }
    void setPy(float y1){ //O(1)
        y = y1;
    }
    /// Print x and y as tuple (x,y)
    void printpoint() { //O(1)
        cout << "( " << x << ", " << y << " )" << endl;
    }
     float getx(){ //O(1)
        return x;
    }
    float gety(){ //O(1)
        return y;
    }

};

std::ostream & operator<<(std::ostream & os, const Point2d & pt)
{
    os << "( " << pt.x << ", " << pt.y << " )" << " ";
    return os;
}
template<class T>
void detail(int n, T cell){

    cout<< endl;
    cout << "All 8 cells in upper perimeter cells " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "cell[0][" << i<< "]"<<endl;
        cout << "Number of Points: "<< cell[0][i].size() << endl;
    }
    cout<< endl;
    cout << "All 8 cells in right perimeter cells " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "cell["<< i << "][7]"<<endl;
        cout << "Number of Points: "<< cell[i][7].size() << endl;
    }
    cout<< endl;
    cout << "All 8 cells in lower perimeter cells " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "cell[7]["<< i<< "]"<<endl;
        cout << "Number of Points: "<< cell[7][i].size() << endl;
    }
    cout<< endl;
    cout << "All 8 cells in left perimeter cells " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "cell["<< i << "][0]" <<endl;
        cout << "Number of Points: "<<cell[i][0].size() << endl;
    }

}

int main() {
    std::string filename;
    filename = "./convexhullpoints.dat";

    std::ifstream dfile;
    dfile.open(filename);

    if (!dfile.is_open()){
        cout << "Error: file did not open" << endl;
        return 0;
    }
    std::string line;
    std::getline(dfile,line);
    std::stringstream ss(line);
    int len =1;
    for (int i =0; i < line.size();i++){
        if (line[i] == ' '){ len++;}
    }
    GrowArray<Point2d> vdata;
    Point2d pp(0,0);
    const int n = 8;

    int count = 0;
    float x;
    while (!ss.eof()){
        ss >> x;

        if (count % 2 == 0){pp.setPx(x);}
        else {pp.setPy(x); vdata.addEnd(pp);}
         count++;
    }

    cout << "Total no. of inserted point: " << count/2 << endl;


    std::vector<float> xes;
    std::vector<float> yes;
    float xmin,xmax,ymin,ymax;
    uint32_t size = vdata.size();

    for (uint32_t i = 0; i< size; i++){
        xes.push_back(vdata.get(i).x);
        yes.push_back(vdata.get(i).y);
    }

    xmin = *std::min_element(xes.begin(),xes.end());
    xmax =  *std::max_element(xes.begin(),xes.end());

    ymin =  *std::min_element(yes.begin(),yes.end());
    ymax =  *std::max_element(yes.begin(),yes.end());

    cout << "\nMin x's point = " <<  xmin << endl;
    cout << "\nMax x's point = " <<  xmax << endl;
    cout << "\nMin y's point = "  << ymin << endl;
    cout << "\nMax y's point = " << ymax << endl;
    cout << endl;

    GrowArray<Point2d> cell[n][n];
    Point2d pp2(0.0,0.0);

    int X_interval, Y_interval;
    X_interval = (n - 1)/(xmax - xmin);
    Y_interval = (n - 1)/(ymax -ymin);
    int i_int, j_int;
    for (int i = 0; i < vdata.size(); i++) {
        i_int = std::round((vdata.get(i).y - ymin) * Y_interval);
        j_int = std::round((vdata.get(i).x - xmin) * X_interval);
        pp2.setPoint(vdata.get(i).x, vdata.get(i).y);
        cell[j_int][i_int].addEnd(pp2);
    }
    detail(n, cell);
    dfile.close();
    return 0;
}
