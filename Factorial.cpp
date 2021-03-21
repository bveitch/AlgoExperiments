#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <gmpxx.h>

using namespace std;
using namespace std::chrono; 
using namespace std::placeholders; 

/**
Created on Fri Sep 04 2020
description : Faster way of computing factorial
author      : bveitch
version     : 1.0
project     : AlgoExperiemnts

Definition (recursive): 

factorial(n)=n*factorial(n-1)

Program should be linked with the libgmpxx and libgmp libraries. For example,
>g++ mycxxprog.cc -std=c++14 -lgmpxx -lgmp

*/


uint64_t factorial(const uint64_t& n){

    if(n==1) return 1;
    else return n*factorial(n-1);
    
}

vector<uint64_t> prime_sieve(size_t n)
{
    vector<bool> flags(n,true);
    flags[0]=false;
    auto i = 1UL;
    vector<uint64_t> primes;
    for(auto pflag=flags.begin(); pflag != flags.end(); pflag++)
    {
        if(*pflag == true)
        {
            primes.push_back(i);
            for(auto j = i*i - 1; j < flags.size(); j+=i){
                flags[j]=false;
            }
        }
        i++;
    }
    return primes;
}

template<typename T> 
T fast_exp(T v, unsigned long n){
	if(n == 0 ) return 1;
	else if(n == 1 ) return v;
	else if(n % 2 ==1) return v*fast_exp(v*v,(n-1)/2);
	else return fast_exp(v*v,n/2 );	
}

uint64_t faster_factorial(const uint64_t& n , const vector<uint64_t> & primes){
    
    auto fac = 1UL;
    for(const auto& p :primes)
    {
        auto p_exp = p;
        auto count = 0UL;
        while( p_exp <= n )
        {
            count+=n/p_exp;
            p_exp*=p;
        }
        fac*=fast_exp(p,count);
    }
    return fac;
}

int main (int argc, char *argv[]) { 
    
    uint64_t N=atoi(argv[1]);
    
    auto start = high_resolution_clock::now();

    auto v = factorial(N);
    
    auto stop = high_resolution_clock::now(); 
  
    //auto duration = duration_cast<double,std::micro>(stop - start);
    
    std::chrono::duration<double, std::micro> duration = stop - start;
    
    cerr << "factorial(recursive) = " << v << std::endl;  

    auto list_of_primes = prime_sieve(N);

    auto start2 = high_resolution_clock::now();
    
    auto vf = faster_factorial(N , list_of_primes );
    
    if(vf!=v){
        cerr << "factorial (recursive) : " << v << std::endl;
        cerr << "factorial ('faster') : " << vf << std::endl;
    }

    auto stop2 = high_resolution_clock::now(); 
  
    std::chrono::duration<double, std::micro> duration2 = stop2 - start2;
    if(duration2.count() < duration.count()){
        std::cerr << "'Faster' method was faster" << std::endl;
    }
    else{
         std::cerr <<  "'Faster' method was actually  slower" << std::endl;
    }

    cerr << "Runtime (recursion) was " << duration.count() << " seconds\n" ;
    cerr << "Runtime ('faster' method) was " << duration2.count() << " seconds\n" ;
  
	return 0;
}