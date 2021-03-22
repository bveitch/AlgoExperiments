#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include "Utilities.hh"
#include "Matrix2x2.hh"

using namespace std;
using namespace std::chrono; 

uint64_t fib1(const uint64_t& n){

    auto f0=0UL;
    auto f1=1UL;
    if(n<=0) return f0;
    if(n==1) return f1; 
    for(auto i=1; i< n;i++){
        auto f2=f0+f1;
        f0=f1;
        f1=f2;
    } 
    return f1;
}

uint64_t fib2(const uint64_t& n, bool use_cpp = true){

    double golden = (sqrt(5.0)+1)/2;
    double fn;
    if(use_cpp){
        fn  = pow(golden,n);
    }
    else{
        fn = Utilities::fast_exp(golden,n);
    }
    return round(fn/sqrt(5)); 
}

uint64_t fib3(const uint64_t& n){

    typedef Matrix2x2<int64_t> M2x2;
    M2x2 matrix;
    auto fn_mat  = Utilities::fast_exp(matrix,n-1);
    return fn_mat(0,0); 

}
int main (int argc, char *argv[]) { 
    
    uint64_t N=atoi(argv[1]);

    typedef std::chrono::duration<double> microseconds;
    
    auto start = high_resolution_clock::now();

    auto fn = fib1(N);
    
    auto stop = high_resolution_clock::now(); 
    
    microseconds duration = stop - start;
 
    cout << std::fixed << std::setprecision(12) << std::left;
    
    cerr << "Dynamic programming loop (should be O(n) time, O(1) mem) ..." <<   std::endl; 
    
    cerr << "   Fibonacci("<<  N  << ")  = " << fn << std::endl;  
    
    cerr << "   Runtime was "  << std::setw(9) << duration.count() << " seconds\n" ;

    auto start2 = std::chrono::system_clock::now();

    auto fn2 = fib2(N);
    
    auto stop2 = std::chrono::system_clock::now(); 
    
    microseconds duration2 = stop2 - start2;
    
    cerr << "Powering of golden ration (should be O(log2(n)) time, O(1) mem) ..." <<   std::endl;
    
    cerr << "   Fibonacci2("<<  N  << ") = " << fn2 << std::endl;  
    
    cerr << "   Runtime was " << std::setw(9) << duration2.count() << " seconds\n" ;

    auto start2_1 = std::chrono::system_clock::now();

    auto fn2_1 = fib2(N,false);
    
    auto stop2_1 = std::chrono::system_clock::now(); 
    
    microseconds duration2_1 = stop2_1 - start2_1;
    
    cerr << "Faster Powering of golden ration (should be O(log2(n)) time, O(1) mem) ..." <<   std::endl;
    
    cerr << "   Fibonacci2("<<  N  << ") = " << fn2_1 << std::endl;  
    
    cerr << "   Runtime was " << duration2_1.count() << " seconds\n" ;
    
    auto start3 = std::chrono::system_clock::now();

    auto fn3 = fib3(N);
    
    auto stop3 = std::chrono::system_clock::now(); 
    
    microseconds duration3 = stop3 - start3;
     
    cerr << "Fast powering matrix operator (should be O(log2(n)) time, O(1) mem + a bit) ..." <<   std::endl;
    
    cerr << "   Fibonacci3("<<  N  << ") = " << fn3 << std::endl;  
    
    cerr << "   Runtime was " << duration3.count() << " seconds\n" ;
    
	return 0;
}