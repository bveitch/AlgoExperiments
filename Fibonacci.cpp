#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
using namespace std::chrono; 

template<typename T>
class Matrix2x2{
    T m11;
    T m12;
    T m21;
    T m22;

public:

    T operator()(int i, int j) const {
        if(i==0 && j==0 ) return m11;
        else if(i==0 && j==1 ) return m12;
        else if(i==1 && j==0 ) return m21;
        else if(i==1 && j==1 ) return m22;
        else throw std::out_of_range("must be 0 or 1");
    }

    Matrix2x2(){
        m11=1;
        m12=1;
        m21=1;
        m22=0;
    }

    Matrix2x2(const T& n){
        m11=n;
        m12=n;
        m21=n;
        m22=0;
    }

    Matrix2x2& operator*= (const Matrix2x2<T>& rhs){
        auto l11=m11;
        auto l12=m12;
        auto l21=m21;
        auto l22=m22;
        m11=l11*rhs.m11+l12*rhs.m21;
        m12=l11*rhs.m12+l12*rhs.m22;
        m21=l21*rhs.m11+l22*rhs.m21;
        m22=l21*rhs.m12+l22*rhs.m22;
		
		return *this;
    }
    
};

template<class T> 
Matrix2x2<T> operator*(const Matrix2x2<T>& lhs, const Matrix2x2<T>& rhs){
    auto a=lhs;
	return a*=rhs;	
};

template<typename T> 
T fast_exp(T v, unsigned long n){
	//if(n < 0 ) return fast_exp( T(1)/v, -n);
	if(n == 0 ) return 1;
	else if(n == 1 ) return v;
	else if(n % 2 ==1) return v*fast_exp(v*v,(n-1)/2);
	else return fast_exp(v*v,n/2 );	
}

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

    double golden = (sqrt(5)+1)/2;
    double fn;
    if(use_cpp){
        fn  = pow(golden,n);
        return round(fn/sqrt(5)); 
    }
    else{
        fn = fast_exp(golden,n);
    }
    return round(fn/sqrt(5)); 
}

uint64_t fib3(const uint64_t& n){

    typedef Matrix2x2<int64_t> M2x2;
    M2x2 matrix;
    auto fn_mat  = fast_exp(matrix,n-1);
    std::cerr << fn_mat(0,0) << std::endl;
    return fn_mat(0,0); 

}
int main (int argc, char *argv[]) { 
    
    uint64_t N=atoi(argv[1]);
    
    auto start = high_resolution_clock::now();

    auto fn = fib1(N);
    
    auto stop = high_resolution_clock::now(); 
    
    std::chrono::duration<double, std::micro> duration = stop - start;

    cerr << "Dynamic programming loop (should be O(n) time, O(1) mem) ..." <<   std::endl; 
    
    cerr << "   Fibonacci("<<  N  << ") = " << fn << std::endl;  
    cerr << "   Runtime was " << duration.count() << " microseconds\n" ;

    auto start2 = high_resolution_clock::now();

    auto fn2 = fib2(N);
    
    auto stop2 = high_resolution_clock::now(); 
    
    std::chrono::duration<double, std::micro> duration2 = stop2 - start2;
    
    cerr << "Powering of golden ration (should be O(log2(n)) time, O(1) mem) ..." <<   std::endl;
    
    cerr << "   Fibonacci2("<<  N  << ") = " << fn2 << std::endl;  
    
    cerr << "   Runtime was " << duration2.count() << " microseconds\n" ;

    auto start2_1 = high_resolution_clock::now();

    auto fn2_1 = fib2(N,false);
    
    auto stop2_1 = high_resolution_clock::now(); 
    
    std::chrono::duration<double, std::micro> duration2_1 = stop2_1 - start2_1;
    
    cerr << "Faster Powering of golden ration (should be O(log2(n)) time, O(1) mem) ..." <<   std::endl;
    
    cerr << "   Fibonacci2("<<  N  << ") = " << fn2_1 << std::endl;  
    
    cerr << "   Runtime was " << duration2_1.count() << " microseconds\n" ;
    
    auto start3 = high_resolution_clock::now();

    auto fn3 = fib3(N);
    
    auto stop3 = high_resolution_clock::now(); 
    
    std::chrono::duration<double, std::micro> duration3 = stop3 - start3;
     
    cerr << "Fast powering matrix operator (should be O(log2(n)) time, O(1) mem + a bit) ..." <<   std::endl;
    
    cerr << "   Fibonacci3("<<  N  << ") = " << fn3 << std::endl;  
    
    cerr << "   Runtime was " << duration3.count() << " microseconds\n" ;
    
	return 0;
}