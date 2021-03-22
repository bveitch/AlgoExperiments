#ifndef UTILITIES_HH
#define UTILITIES_HH

#include <iostream>
#include <fstream>
#include <cmath>

namespace Utilities {

    template<typename T> 
    T fast_exp(const T& v, const unsigned long& n){
	    //if(n < 0 ) return fast_exp( T(1)/v, -n);
	    if(n == 0 ) return static_cast<T>(1);
	    else if(n == 1 ) return v;
	    else if(n % 2 ==1) return v*fast_exp(v*v,(n-1)/2);
	    else return fast_exp(v*v,n/2 );	
    }

}

#endif