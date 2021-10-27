#include "stack.hpp"
# include <stack>
#include <cstring>

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
/*
void ft_stack_capacity()
{
	NAMESPACE::stack<int> V1 (3, 39);
	NAMESPACE::stack<int> V2;
	Printstack(&V1, "Capacity");

	std::cout << "Size " <<  V1.size() << std::endl;
	std::cout << "max_Size " <<  V1.max_size() << std::endl;
	std::cout << "Capacity " <<  V1.capacity() << std::endl;
	std::cout << "Empty " <<  V1.empty() << std::endl;
	std::cout << "Empty " <<  V2.empty() << std::endl;

	V1.reserve(50);
	std::cout << "Reserve " <<  V1.capacity() << std::endl;

	V1.reserve(5);
	std::cout << "Reserve " <<  V1.capacity() << std::endl;

	V1.resize(100);
	std::cout << "Resize " <<  V1.capacity() << std::endl;
	
	V1.resize(2);
	std::cout << "Resize " <<  V1.capacity()  << std::endl;
	Printstack(&V1, "Resize - 2");

	V1.resize(11);
	std::cout << "Resize " <<  V1.capacity() << std::endl;
	Printstack(&V1, "Resize - 11");

	V1.resize(15, 666);
	std::cout << "Resize " <<  V1.capacity()  << std::endl;
	Printstack(&V1,  "Resize - 11");
}

void ft_stack_begin_end()
{
	NAMESPACE::stack<int> V1 (3, 39);

	V1.push_back(3);
	Printstack(&V1, "Begin / End");

	std::cout << "Begin " <<  *V1.begin() << std::endl;
	std::cout << "rBegin " <<  *V1.rbegin() << std::endl;
	std::cout << "End " <<  *(V1.end() - 1) << std::endl;
	std::cout << "rEnd " <<  *V1.rend() << std::endl;
}

void ft_stack_relationnal_operator(void)
{
	std::cout << "------------------------------------ " << "Relationnal operator" << std::endl;
	NAMESPACE::stack<int> V1 (3, 39);
	NAMESPACE::stack<int> V2 (3, 39);
	NAMESPACE::stack<int> V3 (4, 39);

	std::cout << "Operator == " <<  (V1 == V2) << std::endl;
	std::cout << "Operator != " << (V1 != V2) << std::endl;
	std::cout << "Operator == " <<  (V1 == V3) <<  std::endl;
	std::cout << "Operator != " << (V1 != V3) << std::endl;

	V1.push_back(3);
	V2.push_back(4);
	
	std::cout << "Operator == " <<  (V1 == V2) << std::endl;
	std::cout << "Operator != " << (V1 != V2) << std::endl;
	std::cout << "Operator == " <<  (V1 == V3) <<  std::endl;
	std::cout << "Operator != " << (V1 != V3) << std::endl;
}

void ft_stack_access(void)
{
	NAMESPACE::stack<int> V1 (3, 39);

	V1.push_back(5);
	Printstack(&V1, "Operator - default");

	std::cout << "Operator [] : " << V1[3] << " at 3"  << std::endl;
	std::cout << "Operator [] : " << V1[0] << " at 0"  << std::endl;
	std::cout << "Operator at : " << V1.at(3) << " at 3"  << std::endl;
	std::cout << "Operator at : " << V1.at(0) << " at 0"  << std::endl;
	std::cout << "Front : " << V1.front() << " at 3"  << std::endl;
	std::cout << "Back : " << V1.back()  << " at 0"  << std::endl; 
}

void ft_stack_clear(void)
{
	NAMESPACE::stack<int> V1 (3, 39);

	V1.clear();
	Printstack(&V1,  "Clear - default");
}

void ft_stack_swap(void)
{
	NAMESPACE::stack<int> V1 (3, 39);
	NAMESPACE::stack<int> V2 (2,50);

	V1.swap(V2);
	Printstack(&V1, "Swap - first element");
	Printstack(&V2, "Swap - second element");
}

void ft_stack_insert_erase(void)
{
	NAMESPACE::stack<int> V1 (3, 39);

	V1.insert(V1.begin() + 1, 5);
	Printstack(&V1, "Insert - one element");

	V1.insert(V1.end(), 6);
	Printstack(&V1, "Insert again - one element");

	NAMESPACE::stack<int> V2 (2, 14);
	V1.insert(V1.begin(), V2.begin(), V2.end());
	Printstack(&V1, "Insert again - one range");

	V1.erase(V1.begin());
	Printstack(&V1, "Erase - one element");

	V1.erase(V1.begin(), V1.begin() + 2);
	Printstack(&V1, "Erase - one range");
}

void ft_stack_push_pop_back(void)
{
	NAMESPACE::stack<int> V1 (3, 39);

	V1.push_back(55);
	Printstack(&V1, "Push_back - default");

	V1.push_back(51);
	Printstack(&V1, "Push_back again - default");

	V1.pop_back();
	Printstack(&V1, "Pop_back - default");

	V1.pop_back();
	V1.pop_back();
	Printstack(&V1, "Pop_back again - default");
}

void ft_stack_assign(void)
{
	NAMESPACE::stack<int> V1 (3, 39);
	NAMESPACE::stack<int> V2 (3,50);

	V1.assign(++V2.begin(), V2.end());
	Printstack(&V1, "Assign - with iterator");

	V1.assign(7, 21);
	Printstack(&V1, "Assign - with value");

	NAMESPACE::stack<std::string> VCHAR2(1,"Test");
	Printstack(&VCHAR2, "Assign - with string value");

	NAMESPACE::stack<std::string> VCHAR3(0,"Test");
	Printstack(&VCHAR3, "Assign - with size at 0");
}
*/
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
 /*  ft_stack_assign();
   ft_stack_push_pop_back();
   ft_stack_insert_erase();
   ft_stack_swap();
   ft_stack_clear();
   ft_stack_access();
   ft_stack_relationnal_operator();
   ft_stack_begin_end();
   ft_stack_capacity();*/
}