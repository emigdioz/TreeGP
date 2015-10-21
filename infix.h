#ifndef INFIX
#define INFIX
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>

const int MAX = 1000;

class infix
{
	private :
		char target[MAX], stack[MAX] ;
		char *s, *t ;
		int top, l ;
		void reverse(std::string& str);
		void swap(std::string& str, int index1, int index2);
	public :
		infix( ) ;
		void setexpr ( char *str ) ;
		void push ( char c ) ;
		char pop( ) ;
		void convert( ) ;
		int priority ( char c ) ;
		void show( ) ;
} ;

#endif // INFIX

