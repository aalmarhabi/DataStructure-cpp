//ME - C++17 - hppe it compile
/*
 * Authors: Alhussain Almarhabi
 * */
//Reference - future review
/* Use assignment two powermod function
 * MillerRabin abstract pdf by Rajesh Pabuluru http://cs.indstate.edu/~rpavuluru/Abstract.pdf
 * MR test by Keith Conrad https://kconrad.math.uconn.edu/blurbs/ugradnumthy/millerrabin.pdf
 * Miller-Rabin primality test - youtube/Theoretically: MR test in number is not prime so if the test
 */
/*question
 * Use the Miller-Rabin algorithm together with powermod to determine weather
 * a number, passed as a command line argument, is prime or composite.
 * */
#include <iostream>
#include <cmath>
#include <algorithm>

//using namespace std; // dont use namespace for std
using std::cout;
using std::cin;
using std::endl;

///Greatest Common Denominator (GCD)
int gcd(int a,int b)
{
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

///power mod
int powermod(int a, int n, int m) //n should be unsigned int
{

    int prod = 1;
    while(n > 0)
    {
        if (n%2 !=0)
            prod = (prod*a)%m;
        a = (a*a)%m;
        n = n/2;

    }
    return prod;
}
/// Check Carmichael number which is composite
bool CKCarmichael(int n)
{
    for (int b = 2; b<n; b++)
    {
        if (gcd(b,n) == 1)
            if(powermod(b, n-1, n) != 1)
                return false; // composite
    }
    return true; // prime
}
/// find the D and S for Miller algorithm
void findDS(int n, int k, float &d, int &s )
{
    int i =1;
    while (i < k)
    {
        d = (n - 1) / (std::pow(2, i));
        if (std::abs(d - std::lround(d)) > 0) {
            d = (n - 1) / (std::pow(2, i - 1));
            s = i - 1;

            break;
        }
        else
        {
            i++;
            continue;
        }
    }
}

/// This the version 2 of Miller Rabin
bool MillerRabin2(int n, int k = 100)
{
    //pre-test for n<3 case and for even number that requited for better Miller checker
    if(n == 0 || n == 1)
    {
        cout<<"This is not prime"<<endl;
        return false;
    }
    else if(n == 2 || n == 3)
    {
        cout<<"This is prime"<<endl;
        return false;
    }
    else if(n % 2 == 0)
    {
        cout<<"This is not prime"<<endl;
        return false;
    }

    for (int i = 1; i<k; i++)
    {
        // set up a number between 1<a<n-1
        int a  = 2 + (std::rand() % (n-1+1));

        // find the split of n-1 s and d: x = a^d mod n : n-1 = 2^s * d
        int s;
        float d;
        if (i ==1) {
            findDS(n,k, d, s);
            // not requited in question
            //cout<<"found n-1 split d: "<<d<<" and s: "<<s<<endl;
        }
        int d1 = (int) d;
        int x = powermod(a, d1, n);

        if (x == 1 || x== n-1)
        {
            cout<<"This is prime"<<endl;
            return true;
        }
        for (int j=1; j<s;j++ ) {
            x = powermod(x, 2, n);
            if (x == 1) {
                cout << "This is composite" << endl;
                return false;
            }

            if (x == n - 1) {
                cout << "This is prime" << endl;
                return true;
            }
            //cout<<"this is prime 3"<<endl;
            //return false; //
            if (CKCarmichael(x)) {
                cout << "This is composite" << endl;
                return false;
            }
        }

    }
    cout<<"This is prime (probably)"<<endl;
    return true; // prime
}

int main(int argc, char* argv[])
{
    int a;
    a = std::stoi(argv[1]);
    MillerRabin2(a);
}