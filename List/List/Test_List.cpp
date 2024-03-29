#include "List.hpp"
#include <list>
#include <cstring>
#include <iostream>
#include <fstream>

template <typename T>
void STLPrintList(std::list<T> *stl) 
{
	typename std::list<T>::iterator it_stl;
	size_t i;

	std::cout << " SIZES : STL = "<< stl->size() << std::endl;
	it_stl = stl->begin();
	i = 0;
	while(it_stl != stl->end())
	{
		std::cout << " Value : STL = " << *it_stl << " at position " << i << std::endl;
		it_stl++;
		i++;
	}
	std::cout << " STL BEGIN : "<< *stl->begin() << std::endl;
	//std::cout << " STL BEGIN : "<< *stl->begin() << " STL END : "<< *stl->end() << std::endl;
	std::cout << " STL FRONT : "<< stl->front() << " STL BACK : "<< stl->back() << std::endl;
}

template <typename T>
void PrintList(ft::list<T> *stl) 
{
	typename ft::list<T>::iterator it_stl;
	size_t i;

	std::cout << " SIZES : FT = "<< stl->size() << std::endl;
	it_stl = stl->begin();
	i = 0;
	while(i < stl->size())
	{
		std::cout << " Value : FT = " << *it_stl << " at position " << i++ << std::endl;
		it_stl++;
	}
	std::cout << " STL BEGIN : "<< *stl->begin() << std::endl;
	//std::cout << " STL BEGIN : "<< *stl->begin() << " STL END : "<< *stl->end() << std::endl;
	std::cout << " STL FRONT : "<< stl->front() << " STL BACK : "<< stl->back() << std::endl;
}

template <typename T>
bool CompareList(ft::list<T> *ft, std::list<T> *stl, const std::string &testName) 
{
	typename std::list<T>::iterator it_stl;
	typename ft::list<T>::iterator it;
	size_t i;

	if (ft->size() != stl->size())
	{
		std::cout <<  testName << " FAIL - Size error :  STL " << stl->size() << " vs FT " << ft->size() << std::endl;
		return false;
	}
//	std::cout << " SIZES : STL = "<< ft->size() << " ; FT =  " << stl->size() << std::endl;
	it_stl = stl->begin();
	it = ft->begin();
	i = 0;
	while(it != ft->end())
	{
//		std::cout << " SHOW : at pos "<< i++ << " got " << *it << std::endl;
		if (*it != *it_stl)
		{
			std::cout << testName << " FAIL - Value error : STL " << *it_stl << " vs FT " << *it << " at position "<< i++ << std::endl;
			return false;
		}
		it_stl++;
		it++;
	}
	std::cout << testName << " => \033[1;32mOK\033[0m" << std::endl;
	return true;
}


void ft_resize()
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);
	
	V1.resize(100);
	V1STL.resize(100);
	if (V1.size() == V1STL.size())
		std::cout << " Success - Resize " <<  V1.size() << " vs " << V1STL.size() << std::endl;
	else
		std::cout << " Fail - Resize " <<  V1.size() << " vs " << V1STL.size() <<  std::endl;
	CompareList(&V1, &V1STL, "Resize - 1");
	
	V1.resize(2);
	V1STL.resize(2);
	if (V1.size() == V1STL.size())
		std::cout << " Success - Resize " <<  V1.size() << " vs " << V1STL.size() << std::endl;
	else
		std::cout << " Fail - Resize " <<  V1.size() << " vs " << V1STL.size() <<  std::endl;

	CompareList(&V1, &V1STL, "Resize - 2");

	V1.resize(11);
	V1STL.resize(11);
	if (V1.size() == V1STL.size())
		std::cout << " Success - Resize " <<  V1.size() << " vs " << V1STL.size() << std::endl;
	else
		std::cout << " Fail - Resize " <<  V1.size() << " vs " << V1STL.size() <<  std::endl;

	CompareList(&V1, &V1STL, "Resize - 11");

	V1.resize(15, 666);
	V1STL.resize(15, 666);
	if (V1.size() == V1STL.size())
		std::cout << " Success - Resize " <<  V1.size() << " vs " << V1STL.size() << std::endl;
	else
		std::cout << " Fail - Resize " <<  V1.size() << " vs " << V1STL.size() <<  std::endl;
	CompareList(&V1, &V1STL, "Resize - 11");
}

void ft_begin_end()
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);
	V1.push_back(3);
	V1STL.push_back(3);
	V1.push_front(12);
	V1STL.push_front(12);
	V1.push_front(11);
	V1STL.push_front(11);
	V1.push_front(13);
	V1STL.push_front(13);
	V1.pop_front();
	V1STL.pop_front();

	//STLPrintList(&V1STL);
	//PrintList(&V1);

	if (*V1.begin() == *V1STL.begin())
		std::cout << " Success - Begin " <<  *V1.begin() << " vs " << *V1STL.begin() << std::endl;
	else
		std::cout << " Fail - Begin " <<  *V1.begin() << " vs " << *V1STL.begin() <<  std::endl;

	if (*V1.rbegin() == *V1STL.rbegin())
		std::cout << " Success - rBegin " <<  *V1.rbegin() << " vs " << *V1STL.rbegin() << std::endl;
	else
		std::cout << " Fail - rBegin " <<  *V1.rbegin() << " vs " << *V1STL.rbegin() <<  std::endl;

	/*if (*(V1.end()--) == *(V1STL.end()--))
		std::cout << " Success - End " <<  *(V1.end()--)<< " vs " << *(V1STL.end()--) << std::endl;
	else
		std::cout << " Fail - End " <<  *(V1.end()--)<< " vs " << *(V1STL.end()--) << std::endl;

	if (*V1.rend() == *V1STL.rend())
		std::cout << " Success - rEnd " <<  *V1.rend() << " vs " << *V1STL.rend() << std::endl;
	else
		std::cout << " Fail - rEnd " <<  *V1.rend() << " vs " << *V1STL.rend() <<  std::endl;*/
}

void ft_relationnal_operator(void)
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);
	std::list<int> V2STL (3, 39);
	ft::list<int> V2 (3, 39);
	std::list<int> V3STL (4, 39);
	ft::list<int> V3 (4, 39);

	if (V1 == V2)
		std::cout << " Success - Operator == " <<  (V1 == V2) << " vs " << (V1STL == V2STL) << std::endl;
	else
		std::cout << " Fail - Operator == " <<  (V1 == V2) << " vs " << (V1STL == V2STL) <<  std::endl;
	
	if (V1 != V2)
		std::cout << " Fail - Operator != " << (V1 != V2) << " vs " << (V1STL != V2STL) << std::endl;
	else
		std::cout << " Success - Operator != " << (V1 != V2) << " vs " << (V1STL != V2STL) << std::endl;

	if (V1 == V3)
		std::cout << " Fail - Operator == " <<  (V1 == V3) << " vs " << (V1STL == V3STL) << std::endl;
	else
		std::cout << " Success - Operator == " <<  (V1 == V3) << " vs " << (V1STL == V3STL) <<  std::endl;
	
	if (V1 != V3)
		std::cout << " Success - Operator != " << (V1 != V3) << " vs " << (V1STL != V3STL) << std::endl;
	else
		std::cout << " Fail - Operator != " << (V1 != V3) << " vs " << (V1STL != V3STL) << std::endl;

	V1.push_back(3);
	V2.push_back(4);
	V1STL.push_back(3);
	V2STL.push_back(4);
	if (V1 < V2)
		std::cout << " Success- Operator < " <<  (V1 < V2) << " vs " << (V1STL < V2STL) << std::endl;
	else
		std::cout << " Fail - Operator < " <<  (V1 < V2) << " vs " << (V1STL < V2STL) <<  std::endl;
	if (V1 > V2)
		std::cout << " Fail- Operator > " <<  (V1 > V2) << " vs " << (V1STL > V2STL) << std::endl;
	else
		std::cout << " Success - Operator > " <<  (V1 > V2) << " vs " << (V1STL > V2STL) <<  std::endl;
	if (V1 <= V2)
		std::cout << " Success- Operator <= " <<  (V1 <= V2) << " vs " << (V1STL <= V2STL) << std::endl;
	else
		std::cout << " Fail - Operator <= " <<  (V1 <= V2) << " vs " << (V1STL <= V2STL) <<  std::endl;
	if (V1 >= V2)
		std::cout << " Fail- Operator >= " <<  (V1 >= V2) << " vs " << (V1STL >= V2STL) << std::endl;
	else
		std::cout << " Success - Operator >= " <<  (V1 >= V2) << " vs " << (V1STL >= V2STL) <<  std::endl;
}

void ft_access(void)
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);
	V1.push_back(5);
	V1STL.push_back(5);

	//STLPrintList(&V1STL);
	//PrintList(&V1);

	if (V1.front() != V1STL.front())
		std::cout << " FAIL - Front : STL " << V1.front() << " vs FT " << V1STL.front()  << std::endl;
	else
		std::cout << " Success - Front : " << V1.front() << " vs FT " << V1STL.front()  << std::endl;

	if (V1.back() != V1STL.back())
		std::cout << " FAIL - back error : STL " << V1STL.back() << " vs FT " << V1.back()  << std::endl;
	else
		std::cout << " Success - back : STL " << V1STL.back() << " vs FT " << V1.back()  << std::endl;
 
 	if (V1.max_size() == V1STL.max_size())
		std::cout << " Success - max_Size " <<  V1.max_size() << " vs " << V1STL.max_size() << std::endl;
	else
		std::cout << " Fail - max_Size " <<  V1.max_size() << " vs " << V1STL.max_size() <<  std::endl;

	if (V1.empty() == V1STL.empty())
		std::cout << " Success - Empty " <<  V1.empty() << " vs " << V1STL.empty()<< std::endl;
	else
		std::cout << " Fail - Empty " <<  V1.empty()<< " vs " << V1STL.empty()<<  std::endl;

	std::list<int> V2STL;
	ft::list<int> V2;

	if (V2.empty() == V2STL.empty())
		std::cout << " Success - Empty " <<  V2.empty() << " vs " << V2STL.empty()<< std::endl;
	else
		std::cout << " Fail - Empty " <<  V2.empty()<< " vs " << V2STL.empty()<<  std::endl;
}

void ft_clear(void)
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);

	V1STL.clear();
	V1.clear();
	CompareList(&V1, &V1STL, "Clear - default");
}

void ft_swap(void)
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);
	std::list<int> V2STL (2,50);
	ft::list<int> V2 (2,50);

	V1STL.swap(V2STL);
	V1.swap(V2);
	CompareList(&V1, &V1STL, "Swap - first element");
	CompareList(&V2, &V2STL, "Swap - second element");
}

void ft_insert_erase(void)
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);

	V1STL.insert(V1STL.begin()++, 5);
	V1.insert(V1.begin()++, 5);
	CompareList(&V1, &V1STL, "Insert - one element");

	V1STL.insert(V1STL.end(), 6);
	V1.insert(V1.end(), 6);
	CompareList(&V1, &V1STL, "Insert again - one element");

	std::list<int> V2STL (2, 14);
	ft::list<int> V2 (2, 14);
	V1STL.insert(V1STL.begin(), V2STL.begin(), V2STL.end());
	V1.insert(V1.begin(), V2.begin(), V2.end());
	CompareList(&V1, &V1STL, "Insert again - one range");

	V1STL.erase(V1STL.begin());
	V1.erase(V1.begin());
	CompareList(&V1, &V1STL, "Erase - one element");

	V1STL.erase(V1STL.begin(), (V1STL.begin()++)++);
	V1.erase(V1.begin(), (V1.begin()++)++);
	CompareList(&V1, &V1STL, "Erase - one range");
}

void ft_push_pop_back(void)
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);

	V1STL.push_back(55);
	V1.push_back(55);
	CompareList(&V1, &V1STL, "Push_back - default");

	V1STL.push_back(51);
	V1.push_back(51);
	CompareList(&V1, &V1STL, "Push_back again - default");

	V1STL.pop_back();
	V1.pop_back();
	CompareList(&V1, &V1STL, "Pop_back - default");

	V1STL.pop_back();
	V1.pop_back();
	V1STL.pop_back();
	V1.pop_back();
	CompareList(&V1, &V1STL, "Pop_back again - default");
}

void ft_assign(void)
{
	std::list<int> V1STL (3, 39);
	ft::list<int> V1 (3, 39);
	std::list<int> V2STL (3,50);
	ft::list<int> V2 (3,50);

	V1STL.assign(++V2STL.begin(), V2STL.end());
	V1.assign(++V2.begin(), V2.end());
	CompareList(&V1, &V1STL, "Assign - with iterator");

	V1STL.assign(7, 21);
	V1.assign(7, 21);
	CompareList(&V1, &V1STL, "Assign - with value");

	std::list<std::string> VCHAR2_STL(3, "At");
	//STLPrintList(&VCHAR2_STL);
	ft::list<std::string> VCHAR2(3, "At");
	//PrintList(&VCHAR2);
	CompareList(&VCHAR2, &VCHAR2_STL, "Assign - with string value");

	ft::list<std::string> VCHAR3(0,"Test");
	std::list<std::string> VCHAR3_STL(0, "Test");
	CompareList(&VCHAR3, &VCHAR3_STL, "Assign - with size at 0");
}

void ft_constructor(void)
{
	std::list<int> V1_STL;
	ft::list<int> V1;
	CompareList(&V1, &V1_STL, "Constructor - default");

	//PrintList(&V1_STL);

	ft::list<char> VCHAR2(5,'A');
	std::list<char> VCHAR2_STL(5, 'A');
	CompareList(&VCHAR2, &VCHAR2_STL, "Constructor - default with char");

	std::list<int> V2STL (3, 39);
	ft::list<int> V2 (3, 39);
	CompareList(&V2, &V2STL, "Constructor - fill");

	std::list<int> V3STL (V2STL.begin(),V2STL.end());
	ft::list<int> V3 (V2.begin(),V2.end());
	CompareList(&V3, &V3STL, "Constructor - range");

	std::list<int> V4STL (V3STL);
	ft::list<int> V4(V3);
	CompareList(&V4, &V4STL, "Constructor - copy");

	V1_STL = V4STL;
	V1 = V4;
	CompareList(&V1, &V1_STL, "Constructor - operator = ");
}

void ft_test_list(void)
{
   ft_constructor();
   ft_assign();
   ft_push_pop_back();
   ft_insert_erase();
   ft_resize();
   ft_swap();
   ft_clear();
   ft_access();
   ft_relationnal_operator();
   ft_begin_end();
}