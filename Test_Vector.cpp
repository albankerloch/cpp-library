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
	std::cout << " SIZES : STL = "<< ft->size() << " ; FT =  " << stl->size() << std::endl;

	it_stl = stl->begin();
	it = ft->begin();
	i = 0;
	while(it != ft->end())
	{
		std::cout << " SHOW : at pos "<< i++ << " got " << *it << std::endl;
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
}

void ft_test_vector(void)
{
   ft_constructor();
   ft_assign();
   ft_push_pop_back();
   ft_insert_erase();
}