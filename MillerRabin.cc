//ME - C++17 - hppe it compiles
/*
 * Authors: Alhussain Almarhabi
 * */
//Reference - future review
/* Use assignment two powermod function
 * MillerRabin abstract pdf by Rajesh Pabuluru http://cs.indstate.edu/~rpavuluru/Abstract.pdf
 * MR test by Keith Conrad https://kconrad.math.uconn.edu/blurbs/ugradnumthy/millerrabin.pdf
 * Miller-Rabin primality test - youtube/Theoretically: MR test in number is not prime so if the test
 * say it's not prime that mean 100%. However if it say it's prime that not for sure prime
 *      1. Find n-1 = 2^k*m repeat w/ different k 'till we find k (n-1/2^k)
 *      2. Pick up a value a from 1<a<n-1 - for simplicity just choose a =2
 *      3. compute b_0 = a^m mod n
 *          if b_0 = 1/-1/n-1 then it's probably prime
 *          if not the compute b_1 ==> b_i = b_i-1^2
 *              if -1 mean it's probably prime
 *              if 1  mean it's composite (not prime)
 *          if b_1 is nether 1 or -1 then compute b_2 and so on
 * */
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
/// delete this in final version
bool MillerRabin(int n, int k = 1000)
{
    // set up a number between 1<a<n-1
    int a  = 2 + (std::rand() % (n-1+1));

    // fine m by going through k iteration or trails
    int i = 1;
    int ki;
    float m;
    if (n == 0 || n == 1)
    {
        cout<<"The entered number is composite (not prime)"<<endl;
        return false;
    }
    while (i < k)
    {

        m = (n-1)/(std::pow(2, i));
        //cout<<m<<endl;
        //cout<<std::abs(m - std::lround(m))<<endl;
        if (std::abs(m - std::lround(m))>0)
        {
            cout<<"found suitable m and k for Miller-Rabin"<<endl;
            m = (n-1)/(std::pow(2, i-1));
            ki = i-1;
            break;
        }
        else
        {
            i++;
            continue;
        }
    }

    //we have k and m
    //we use the first line value a that generated randomly
    //now compute b_0 using powermodd given a, m and n
    int b0, btemp;
    int m_m = m;
    b0 = powermod(a, m_m ,n);

    printf("m = %d and k = %d",m_m,ki);
    cout<<endl;

    // when ever find m and k, where ki =1 then n it composite
    /*if (ki == 1)
    {
        cout<<"The entered number is composite (not prime)dfafd"<<endl;
        return false;
    }*/

    for (int ii = 0; ii <= k; ii++) //ki-1
    {
        if (ii == 0)
        {
          if ((std::abs(b0)) == 1)
          {
              cout<<"1 the entered number is prime (probably)"<<endl;
              return true;
          }
          else
          {
              //powermod(std::pow(b0,2),m_m,n);

              //cout<<b0<<endl;
              continue;
          }

        }

        else
        {
            b0 = powermod(b0,2,n);
            btemp = b0 ;
            if (btemp == 1)
            {
                if (CKCarmichael(b0))
                {
                    cout<<"2 The enterd number is prime (probably) Carmichael test"<<endl;
                }
                cout<<"The entered number is composite (not prime)"<<endl;
                return false;
            }
            else if (btemp == n-1)
            {
                //cout<<"The entered number is prime (probably)"<<endl;
                continue;
            }
            else
            {
                //b0 = powermod(b0,2,n);
                //cout<<b0<<endl;

                continue;
            }
        }
    }
    cout<<"3 The entered number is prime (probably)"<<endl;
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
            cout<<"found n-1 split d: "<<d<<" and s: "<<s<<endl;
        }
        int d1 = (int) d;
        int x = powermod(a, d1, n);

        if (x == 1 || x== n-1)
        {
            cout<<"This is prime 0"<<endl;
            return true;
        }
        for (int j=1; j<s;j++ ) {
            x = powermod(x, 2, n);
            if (x == 1) {
                cout << "This is composit 2" << endl;
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
int main()
{
    int a;
    bool checkprime;
    cout<<"Please enter a number to check if prime or composite: "<<endl;
    cin>>a;
    checkprime = MillerRabin2(a);
    cout<<"#############"<<endl;
}