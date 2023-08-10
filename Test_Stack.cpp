/**
 * @file Test_Stack.cpp
 * @author alban kerloc'h
 * @date 11/04/2021
 * @version 1.0
 */

#include "Stack.hpp"
# include <stack>
# include <cstring>
# include <list>
# include <deque>

template <typename T>
bool Printstack(NAMESPACE::stack<T> *stl, std::string str = "test") 
{
	NAMESPACE::stack<T> tmp(*stl);
	size_t i;

	std::cout << "------------------------------------ " << str << std::endl;
	std::cout << " SIZE : = "<< tmp.size() << std::endl;

	i = 0;
	while(i < stl->size())
	{
		std::cout << " SHOW : at pos "<< i++ << " got " << tmp.top() << std::endl;
		tmp.pop();
	}
	return true;
}

void ft_stack_capacity()
{
	std::cout << "------------------------------------ " << "Size and Empty" << std::endl;
	NAMESPACE::stack<int, std::list<int> > V1;
	NAMESPACE::stack<char, std::deque<int> > V2;

	V1.push(3);

	std::cout << "Size " <<  V1.size() << std::endl;
	std::cout << "Empty " <<  V1.empty() << std::endl;

	std::cout << "Size " <<  V2.size() << std::endl;
	std::cout << "Empty " <<  V2.empty() << std::endl;
}

void ft_stack_relationnal_operator(void)
{
	std::cout << "------------------------------------ " << "Relationnal operator" << std::endl;
	NAMESPACE::stack<int> V1;
	NAMESPACE::stack<int> V2;
	NAMESPACE::stack<int> V3;

	V1.push(39);
	V1.push(39);
	V1.push(39);

	V2.push(39);
	V2.push(39);
	V2.push(39);

	V3.push(39);
	V3.push(39);
	V3.push(39);
	V3.push(39);

	std::cout << "Operator == " <<  (V1 == V2) << std::endl;
	std::cout << "Operator != " << (V1 != V2) << std::endl;
	std::cout << "Operator == " <<  (V1 == V3) <<  std::endl;
	std::cout << "Operator != " << (V1 != V3) << std::endl;

	V1.push(3);
	V2.push(4);
	
	std::cout << "Operator == " <<  (V1 == V2) << std::endl;
	std::cout << "Operator != " << (V1 != V2) << std::endl;
	std::cout << "Operator == " <<  (V1 == V3) <<  std::endl;
	std::cout << "Operator != " << (V1 != V3) << std::endl;
}


void ft_stack_push_pop_back(void)
{
	NAMESPACE::stack<int> V1;

	V1.push(5);
	V1.push(55);
	Printstack(&V1, "Push_back - default");

	V1.push(51);
	V1.push(51);
	Printstack(&V1, "Push_back again - default");

	V1.pop();
	Printstack(&V1, "Pop_back - default");

	V1.pop();
	V1.pop();
	Printstack(&V1, "Pop_back again - default");
}

void ft_stack_constructor(void)
{
	NAMESPACE::stack<int> V1;
	Printstack(&V1, "Constructor - default");

	NAMESPACE::stack<char> VCHAR2;
	Printstack(&VCHAR2, "Constructor - default with char");

	V1.push(1);
	NAMESPACE::stack<int> V3(V1);
	Printstack(&V3, "Constructor - copy");

	NAMESPACE::stack<int> V4 = V1;
	Printstack(&V4, "Constructor - operator = ");
}

void ft_test_stack(void)
{
   ft_stack_constructor();
   ft_stack_push_pop_back();
   ft_stack_relationnal_operator();
   ft_stack_capacity();
}