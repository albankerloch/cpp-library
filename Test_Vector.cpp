#include "Vector.hpp"
#include <vector>
#include <cstring>

template <typename T>
bool Comparevector(ft::vector<T> *ft, std::vector<T> *stl, const std::string &testName) 
{
	typename std::vector<T>::iterator it_stl;
	typename ft::vector<T>::iterator it;
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

void ft_capacity()
{
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);
	std::vector<int> V2STL;
	ft::vector<int> V2;
	/*
	size
max_size
resize
capacity
empty
reserve*/

	if (V1.size() == V1STL.size())
		std::cout << " Success - Size " <<  V1.size() << " vs " << V1STL.size() << std::endl;
	else
		std::cout << " Fail - Size " <<  V1.size() << " vs " << V1STL.size() <<  std::endl;

	if (V1.max_size() == V1STL.max_size())
		std::cout << " Success - max_Size " <<  V1.max_size() << " vs " << V1STL.max_size() << std::endl;
	else
		std::cout << " Fail - max_Size " <<  V1.max_size() << " vs " << V1STL.max_size() <<  std::endl;

	if (V1.capacity() == V1STL.capacity())
		std::cout << " Success - Capacity " <<  V1.capacity() << " vs " << V1STL.capacity() << std::endl;
	else
		std::cout << " Fail - Capacity " <<  V1.capacity() << " vs " << V1STL.capacity() <<  std::endl;
	
	if (V1.empty() == V1STL.empty())
		std::cout << " Success - Empty " <<  V1.empty() << " vs " << V1STL.empty()<< std::endl;
	else
		std::cout << " Fail - Empty " <<  V1.empty()<< " vs " << V1STL.empty()<<  std::endl;

	if (V2.empty() == V2STL.empty())
		std::cout << " Success - Empty " <<  V2.empty() << " vs " << V2STL.empty()<< std::endl;
	else
		std::cout << " Fail - Empty " <<  V2.empty()<< " vs " << V2STL.empty()<<  std::endl;

	V1.reserve(50);
	V1STL.reserve(50);
	if (V1.capacity() == V1STL.capacity())
		std::cout << " Success - Reserve " <<  V1.capacity() << " vs " << V1STL.capacity() << std::endl;
	else
		std::cout << " Fail - Reserve " <<  V1.capacity() << " vs " << V1STL.capacity() <<  std::endl;

	V1.reserve(5);
	V1STL.reserve(5);
	if (V1.capacity() == V1STL.capacity())
		std::cout << " Success - Reserve " <<  V1.capacity() << " vs " << V1STL.capacity() << std::endl;
	else
		std::cout << " Fail - Reserve " <<  V1.capacity() << " vs " << V1STL.capacity() <<  std::endl;

	V1.resize(100);
	V1STL.resize(100);
	if (V1.capacity() == V1STL.capacity())
		std::cout << " Success - Resize " <<  V1.capacity() << " vs " << V1STL.capacity() << std::endl;
	else
		std::cout << " Fail - Resize " <<  V1.capacity() << " vs " << V1STL.capacity() <<  std::endl;
	
	V1.resize(2);
	V1STL.resize(2);
	if (V1.capacity() == V1STL.capacity())
		std::cout << " Success - Resize " <<  V1.capacity() << " vs " << V1STL.capacity() << std::endl;
	else
		std::cout << " Fail - Resize " <<  V1.capacity() << " vs " << V1STL.capacity() <<  std::endl;
	Comparevector(&V1, &V1STL, "Resize - 2");

	V1.resize(11);
	V1STL.resize(11);
	if (V1.capacity() == V1STL.capacity())
		std::cout << " Success - Resize " <<  V1.capacity() << " vs " << V1STL.capacity() << std::endl;
	else
		std::cout << " Fail - Resize " <<  V1.capacity() << " vs " << V1STL.capacity() <<  std::endl;
	Comparevector(&V1, &V1STL, "Resize - 11");

	V1.resize(15, 666);
	V1STL.resize(15, 666);
	if (V1.capacity() == V1STL.capacity())
		std::cout << " Success - Resize " <<  V1.capacity() << " vs " << V1STL.capacity() << std::endl;
	else
		std::cout << " Fail - Resize " <<  V1.capacity() << " vs " << V1STL.capacity() <<  std::endl;
	Comparevector(&V1, &V1STL, "Resize - 11");
}

void ft_begin_end()
{
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);
	V1.push_back(3);
	V1STL.push_back(3);

	if (*V1.begin() == *V1STL.begin())
		std::cout << " Success - Begin " <<  *V1.begin() << " vs " << *V1STL.begin() << std::endl;
	else
		std::cout << " Fail - Begin " <<  *V1.begin() << " vs " << *V1STL.begin() <<  std::endl;

	if (*V1.rbegin() == *V1STL.rbegin())
		std::cout << " Success - rBegin " <<  *V1.rbegin() << " vs " << *V1STL.rbegin() << std::endl;
	else
		std::cout << " Fail - rBegin " <<  *V1.rbegin() << " vs " << *V1STL.rbegin() <<  std::endl;

	if (*(V1.end() - 1) == *(V1STL.end() - 1))
		std::cout << " Success - End " <<  *(V1.end() - 1)<< " vs " << *(V1STL.end() - 1) << std::endl;
	else
		std::cout << " Fail - End " <<  *(V1.end() - 1)<< " vs " << *(V1STL.end() - 1) << std::endl;

	if (*V1.rend() == *V1STL.rend())
		std::cout << " Success - rEnd " <<  *V1.rend() << " vs " << *V1STL.rend() << std::endl;
	else
		std::cout << " Fail - rEnd " <<  *V1.rend() << " vs " << *V1STL.rend() <<  std::endl;
}

void ft_relationnal_operator(void)
{
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);
	std::vector<int> V2STL (3, 39);
	ft::vector<int> V2 (3, 39);
	std::vector<int> V3STL (4, 39);
	ft::vector<int> V3 (4, 39);

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
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);

	V1.push_back(5);
	V1STL.push_back(5);

	Comparevector(&V1, &V1STL, "Operator - default");

	if (V1[3] != V1STL[3])
		std::cout << " FAIL - Operator [] error : STL " << V1STL[3] << " vs FT " << V1[3]  << std::endl;
	else
		std::cout << " Success - Operator [] : " << V1STL[3] << " at 3"  << std::endl;

	if (V1[0] != V1STL[0])
		std::cout << " FAIL - Operator [] error : STL " << V1STL[0] << " vs FT " << V1[0]  << std::endl;
	else
		std::cout << " Success - Operator [] : " << V1STL[0] << " at 0"  << std::endl;

	if (V1.at(0) != V1STL.at(0))
		std::cout << " FAIL - Operator at error : STL " << V1STL.at(0) << " vs FT " << V1.at(0)  << std::endl;
	else
		std::cout << " Success - Operator at : " <<  V1STL.at(0) << " at 0"  << std::endl;

	if (V1.at(3) != V1STL.at(3))
		std::cout << " FAIL - Operator at error : STL " << V1STL.at(3) << " vs FT " << V1.at(3)  << std::endl;
	else
		std::cout << " Success - Operator at : " << V1STL[3] << " at 3"  << std::endl;

	if (V1.front() != V1STL.front())
		std::cout << " FAIL - Operator front error : STL " << V1STL.front() << " vs FT " << V1.front()  << std::endl;
	else
		std::cout << " Success - Operator front : " <<  V1STL.front() << " at 0"  << std::endl;

	if (V1.back() != V1STL.back())
		std::cout << " FAIL - Operator back error : STL " << V1STL.back() << " vs FT " << V1.back()  << std::endl;
	else
		std::cout << " Success - Operator back : " <<  V1STL.back() << " at 0"  << std::endl;
 
}

void ft_clear(void)
{
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);

	V1STL.clear();
	V1.clear();
	Comparevector(&V1, &V1STL, "Clear - default");
}

void ft_swap(void)
{
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);
	std::vector<int> V2STL (2,50);
	ft::vector<int> V2 (2,50);

	V1STL.swap(V2STL);
	V1.swap(V2);
	Comparevector(&V1, &V1STL, "Swap - first element");
	Comparevector(&V2, &V2STL, "Swap - second element");
}

void ft_insert_erase(void)
{
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);

	V1STL.insert(V1STL.begin() + 1, 5);
	V1.insert(V1.begin() + 1, 5);
	Comparevector(&V1, &V1STL, "Insert - one element");

	V1STL.insert(V1STL.end(), 6);
	V1.insert(V1.end(), 6);
	Comparevector(&V1, &V1STL, "Insert again - one element");

	std::vector<int> V2STL (2, 14);
	ft::vector<int> V2 (2, 14);
	V1STL.insert(V1STL.begin(), V2STL.begin(), V2STL.end());
	V1.insert(V1.begin(), V2.begin(), V2.end());
	Comparevector(&V1, &V1STL, "Insert again - one range");

	V1STL.erase(V1STL.begin());
	V1.erase(V1.begin());
	Comparevector(&V1, &V1STL, "Erase - one element");

	V1STL.erase(V1STL.begin(), V1STL.begin() + 2);
	V1.erase(V1.begin(), V1.begin() + 2);
	Comparevector(&V1, &V1STL, "Erase - one range");
}

void ft_push_pop_back(void)
{
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);

	V1STL.push_back(55);
	V1.push_back(55);
	Comparevector(&V1, &V1STL, "Push_back - default");

	V1STL.push_back(51);
	V1.push_back(51);
	Comparevector(&V1, &V1STL, "Push_back again - default");

	V1STL.pop_back();
	V1.pop_back();
	Comparevector(&V1, &V1STL, "Pop_back - default");

	V1STL.pop_back();
	V1.pop_back();
	V1STL.pop_back();
	V1.pop_back();
	Comparevector(&V1, &V1STL, "Pop_back again - default");
}

void ft_assign(void)
{
	std::vector<int> V1STL (3, 39);
	ft::vector<int> V1 (3, 39);
	std::vector<int> V2STL (3,50);
	ft::vector<int> V2 (3,50);

	V1STL.assign(++V2STL.begin(), V2STL.end());
	V1.assign(++V2.begin(), V2.end());
	Comparevector(&V1, &V1STL, "Assign - with iterator");

	V1STL.assign(7, 21);
	V1.assign(7, 21);
	Comparevector(&V1, &V1STL, "Assign - with value");

	ft::vector<std::string> VCHAR2(1,"Test");
	std::vector<std::string> VCHAR2_STL(1, "Test");
	Comparevector(&VCHAR2, &VCHAR2_STL, "Assign - with string value");

	ft::vector<std::string> VCHAR3(0,"Test");
	std::vector<std::string> VCHAR3_STL(0, "Test");
	Comparevector(&VCHAR3, &VCHAR3_STL, "Assign - with size at 0");
}

void ft_constructor(void)
{
	std::vector<int> V1_STL;
	ft::vector<int> V1;
	Comparevector(&V1, &V1_STL, "Constructor - default");

	ft::vector<char> VCHAR2(5,'A');
	std::vector<char> VCHAR2_STL(5, 'A');
	Comparevector(&VCHAR2, &VCHAR2_STL, "Constructor - default with char");

	std::vector<int> V2STL (3, 39);
	ft::vector<int> V2 (3, 39);
	Comparevector(&V2, &V2STL, "Constructor - fill");

	std::vector<int> V3STL (V2STL.begin(),V2STL.end());
	ft::vector<int> V3 (V2.begin(),V2.end());
	Comparevector(&V3, &V3STL, "Constructor - range");

	std::vector<int> V4STL (V3STL);
	ft::vector<int> V4(V3);
	Comparevector(&V4, &V4STL, "Constructor - copy");

	V1_STL = V4STL;
	V1 = V4;
	Comparevector(&V1, &V1_STL, "Constructor - operator = ");
}

void ft_test_vector(void)
{
   ft_constructor();
   ft_assign();
   ft_push_pop_back();
   ft_insert_erase();
   ft_swap();
   ft_clear();
   ft_access();
   ft_relationnal_operator();
   ft_begin_end();
   ft_capacity();
}