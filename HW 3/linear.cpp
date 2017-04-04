//
//  linear.cpp
//  HomeWork 3
//
//  Created by Ishan Sharma on 2/12/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include <cassert>
using namespace std;

//Declarations
bool somePredicate(double x);

//Implementations
bool somePredicate(double x)
{
    return x < 0;
}


bool allTrue(const double a[], int n)
{
    if (n<=0){
        return true;
    }
    
    if (!somePredicate(a[n-1]))
        return false;
    
    return allTrue(a, n-1);
}


int countFalse(const double a[], int n)
{
    if (n<=0)
        return 0;
    
    return (!somePredicate(a[n-1]) + countFalse(a, n-1));
   
}

int firstFalse(const double a[], int n)
{
    if (n <=0)
        return -1;
    if (!somePredicate(a[0])) // first one is false return 0
        return 0;
    int i=firstFalse(a+1, n-1);
    if (i==-1)      //none are false return -1
        return -1;
    
    return i+1; // i will check the position of the first false in arr+1 so 1 must be added in order to have correct pos
    
}
// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.

int indexOfMin(const double a[], int n)
{
   if (n<=0)
       return -1;
    
    int index= 1 + indexOfMin(a+1, n-1);
    if (a[0]<=a[index])
        return 0;
    else
        return index;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20

bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return true;
    if (n1<=0)
        return false;
    
    if (a1[0]==a2[0])
        return includes(a1+1, n1-1, a2+1, n2-1);
    else
        return includes(a1+1, n1-1, a2, n2);
}
 
/*
int main(){
    double a[4]= {-1,-2,-3,-4};
    double b[4]= {1,-2,3,-4};
    double c[4]= {1,-2,-3,-4};
    
    double t[7]= {10,50,40,20,50,40,30};
    double x[3] = {50, 40, 40};
 
    assert(allTrue(a, 4));
    assert(!allTrue(b, 4));
    assert(!allTrue(c, 4));
    
    assert(countFalse(a, 4)==0);
    assert(countFalse(b, 4)==2);
    assert(countFalse(c, 4)==1);
    assert(countFalse(t, 7)==7);
    assert(countFalse(x, 3)==3);
    
    assert(!includes(a,4,x,3));
    assert(includes(t,7,x,3));
    
    
    cout<<"Passed"<<endl;
}
*/
