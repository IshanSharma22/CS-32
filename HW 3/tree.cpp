//
//  tree.cpp
//  HomeWork 3
//
//  Created by Ishan Sharma on 2/13/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include <cassert>
#include <iostream>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3


int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2<=0)
        return 1;
    if (n1<=0)
        return 0;
    
    if (a1[n1-1]==a2[n2-1])
        return (countIncludes(a1, n1-1, a2, n2-1) + countIncludes(a1, n1-1, a2, n2));
    
    else
        return (countIncludes(a1, n1-1, a2, n2));
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
              int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > separator
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < separator
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.

void order(double a[], int n)
{
    if (n <=1)
        return;

    int fLess;
    int fngreat;
    
    separate(a, n, a[n/2], fngreat, fLess);
    
    order(a,fngreat);
    order(a+fLess, n-fLess);
}


/*
int main(){
    double t[7]= {10,20,10,20,50,40,30};
    double s[7] ={10,50,40,20,50,40,30};
    
    double x[3] = {10,20,30};
    
    double a[3] = {10,20,40};
    double b[3] = {10,40,30};
    
    double c[3] = {20,10,40};
    double d[3] = {50,40,30};
    
    assert(countIncludes(t, 4, x, 2)==3);
    
    assert(countIncludes(s, 7, a, 3)==1);
    assert(countIncludes(s, 7, b, 3)==2);
    assert(countIncludes(s, 7, c, 3)==0);
    assert(countIncludes(s, 7, d, 3)==3);
    
    order(t,7);
    order(s,7);
    order(x,3);
    order(a,3);
    order(b,3);
    order(c,3);
    order(d,3);
    
    for (int i =0; i<7; i++){
        cout<<s[i]<< " ";
    }
    cout << endl;

    for (int i =0; i<7; i++){
        cout<<t[i]<< " ";
    }
    cout << endl;
    
    for (int i =0; i<3; i++){
        cout<<a[i]<< " ";
    }
    cout << endl;
    
    for (int i =0; i<3; i++){
        cout<<b[i]<< " ";
    }
    cout << endl;
    
    for (int i =0; i<3; i++){
        cout<<c[i]<< " ";
    }
    cout << endl;
    
    for (int i =0; i<3; i++){
        cout<<d[i]<< " ";
    }
    cout << endl;

    cout<< "WORKS" <<endl;
}
*/
