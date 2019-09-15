//ME - C++17 - hope it compile
/*
 * Author: Alhussain Almarhabi
 */
//REFERENCE and future review
/* "Longest Common Subsequence|DP-4" by GeeksforGeeks
 * "Remove spaces from std::string in c++" by stackoverlfow - Matt Price
 * "c++ strlen()" by Programiz website
 */

#include <iostream>
#include <fstream>
#include <ostream>
//#include <string>
//#include <unistd.h>
//#include <stdio.h>
#include <algorithm> // for erase function
#include <cstring> // for strlen
using namespace std;

// implement LCS with 2d memoization, matrix to look for common characters
const int maximum = 1000;
int lcs(string X, string Y, int m, int n, int dp[][maximum])
{
    // return nothing after we exhaust the complete length of one file
    if (m == 0 || n == 0)
        return 0;

    // Use memoization if lcs already calculated
    if (dp[m - 1][n - 1] != -1)
        return dp[m - 1][n - 1];

    // store the value of same computation
    if (X[m - 1] == Y[n - 1]) {
        dp[m - 1][n - 1] = 1 + lcs(X, Y, m - 1, n - 1, dp);
        return dp[m - 1][n - 1];
    }
    else {
        dp[m - 1][n - 1] = max(lcs(X, Y, m, n - 1, dp),
                               lcs(X, Y, m - 1, n, dp));

        return dp[m - 1][n - 1];
    }
}

int main() {
    // Initialize files to compare
    string file1, file2,line1, line2, cline1, cline2;
    // Initialize Read the pointed files
    ifstream text1r, text2r; // text one read, text two read

    // Request user to enter the name of the files
    cout<<"Please enter file one name: "<<endl;
    cin>>file1;
    cout<<"Please enter the name of the second file"<<endl;
    cin>>file2;

    //open the pointed file
    text1r.open(file1); // (file1.c_str(), ios::binary);
    text2r.open(file2); //(file2.c_str(), ios::binary);

    //combine all the file in one string line and then perform LCM
    if(text1r.is_open())
    {
        while(!text1r.eof())
        {
            getline(text1r, line1);
            cline1 += line1;
        }
    }else
        cout<<"file is not open"<<endl;

    if(text2r.is_open())
    {
        while(!text2r.eof())
        {
            getline(text2r, line2);
            cline2 += line2;
        }
    }else
        cout<<"file is not open"<<endl;

    // Remove spaces from the combined line cline
    cline1.erase(std::remove(cline1.begin(), cline1.end(), ' '), cline1.end());
    cline2.erase(std::remove(cline2.begin(), cline2.end(), ' '), cline2.end());

    int dp[strlen(cline1.c_str())][maximum];
    memset(dp, -1, sizeof(dp));

    //now perform the large common sub-sequence LCS
    //printf("the length of common bytes: %d", lcs(cline1, cline2, strlen(cline1.c_str()), strlen(cline2.c_str())));
    printf("the length of common bytes: %d", lcs(cline1, cline2, strlen(cline1.c_str()), strlen(cline2.c_str()), dp));
    //cout<< "the length of common bytes: "<<lcs(cline1, cline2, strlen(cline1.c_str()), strlen(cline2.c_str()));


    /*
    //go through lines
    if(text1r.is_open() & text2r.is_open())
    {
        while(!text1r.eof() & !text2r.eof())
        {
            getline(text1r, line1);
            getline(text2r, line2);
            if(line1==line2)
            {
                continue;
            }

        }
    }*/

    /*string line;
    ifstream text1r;
    text1r.open(file1);
    if(text1r.is_open())
    {
        while(getline(text1r, line))
        {
            cout<<line<<endl;
        }
        text1r.close();
    } else
        cout<<"file is not open"<<endl;
    */

    return 0;
}