#include "infix.h"

infix :: infix( )
{
	top = -1 ;
	strcpy ( target, "" ) ;
	strcpy ( stack, "" ) ;
	l = 0 ;
}
void infix :: setexpr ( char *str )
{
	std::string s2(str);
	reverse ( s2 ) ;
	strcpy(s, s2.c_str());
	l = strlen ( s ) ;
	* ( target + l ) = '\0' ;
	t = target + ( l - 1 ) ;
}
void infix :: push ( char c )
{
	if ( top == MAX - 1 )
		std::cout << "\nStack is full\n" ;
	else
	{
		top++ ;
		stack[top] = c ;
	}
}
char infix :: pop( )
{
	if ( top == -1 )
	{
		std::cout << "Stack is empty\n" ;
		return -1 ;
	}
	else
	{
		char item = stack[top] ;
		top-- ;
		return item ;
	}
}
void infix :: convert( )
{
	char opr ;

	while ( *s )
	{
		if ( *s == ' ' || *s == '\t' )
		{
			s++ ;
			continue ;
		}

		if ( isdigit ( *s ) || isalpha ( *s ) )
		{
			while ( isdigit ( *s ) || isalpha ( *s ) )
			{
				*t = *s ;
				s++ ;
				t-- ;
			}
		}

		if ( *s == ')' )
		{
			push ( *s ) ;
			s++ ;
		}

		if ( *s == '*' || *s == '+' || *s == '/' ||
				*s == '%' || *s == '-' || *s == '$' )
		{
			if ( top != -1 )
			{
				opr = pop( ) ;

				while ( priority ( opr ) > priority ( *s ) )
				{
					*t = opr ;
					t-- ;
					opr = pop( ) ;
				}
				push ( opr ) ;
				push ( *s ) ;
			}
			else
				push ( *s ) ;
			s++ ;
		}

		if ( *s == '(' )
		{
			opr = pop( ) ;
			while ( ( opr ) != ')' )
			{
				*t = opr ;
				t-- ;
				opr =  pop ( ) ;
			}
			s++ ;
		}
	}

	while ( top != -1 )
	{
		opr = pop( ) ;
		*t = opr ;
		t-- ;
	}
	t++ ;
}
int infix :: priority ( char c )
{
	if ( c == '$' )
		return 3 ;
	if ( c == '*' || c == '/' || c == '%' )
		return 2 ;
	else
	{
		if ( c == '+' || c == '-' )
			return 1 ;
		else
			return 0 ;
	}
}
void infix :: show( )
{
	while ( *t )
	{
		std::cout << " " << *t ;
		t++ ;
	}
}

void infix::swap(std::string& str, int index1, int index2) {

    char temp = str[index1];
    str[index1] = str[index2];
    str[index2] = temp;

}

void infix::reverse(std::string& str) {

    for (int i = 0; i < str.size() / 2; i++)
        swap(str, i, str.size() - i - 1);

}
