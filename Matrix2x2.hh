#ifndef MATRIX_HH
#define MATRIX_HH

#include <iostream>
#include <sstream>
#include <fstream>

template<typename T>
class Matrix2x2{
    T m11;
    T m12;
    T m21;
    T m22;

public:

    Matrix2x2(){
        m11=1;
        m12=1;
        m21=1;
        m22=0;
    }

    Matrix2x2(const T& v){
        if(v!=1){
            throw std::out_of_range("value must be 1");
        }
        m11=1;
        m12=1;
        m21=1;
        m22=0;;
    }

    Matrix2x2(const Matrix2x2&) =default;
  
    Matrix2x2& operator=(const Matrix2x2&) =delete;
    
    T operator()(int i, int j) const {
        if(i==0 && j==0 ) return m11;
        else if(i==0 && j==1 ) return m12;
        else if(i==1 && j==0 ) return m21;
        else if(i==1 && j==1 ) return m22;
        else throw std::out_of_range("must be 0 or 1");
    };

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

    };
    
};

template<class T> 
Matrix2x2<T> operator*(const Matrix2x2<T>& lhs, const Matrix2x2<T>& rhs){
    auto a=lhs;
	return a*=rhs;	
};

template<class T, class charT, class traits>
inline   std::basic_ostream<charT,traits>&
    operator<< (std::basic_ostream<charT,traits>& ostr, const Matrix2x2<T>& rhs){
		std::basic_ostringstream<charT,traits>  s;
		s << "[[" << rhs.m11 << " , " << rhs.m12 << "],[" << rhs.m21 << " , " << rhs.m22 << "]]"; 
 	   return ostr << s.str();
};

#endif