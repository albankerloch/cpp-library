#include "Vector.hpp"
#include <vector>

template <typename T>
bool assertVectorEquals(ft::Vector<T> *ft, std::vector<T> *std, const std::string &testName) 
{
	if (ft->size() != std->size())
	{
		std::cout <<  testName << " FAIL : Expecting size to be equal: STL " << std->size() << " got FT " << ft->size() << std::endl;
		return false;
	}
	
	typename std::vector<T>::iterator itSTL = std->begin();
	size_t i(0);
	for (typename ft::Vector<T>::iterator it = ft->begin(); it != ft->end(); it++)
	{

		if (*it != *itSTL)
		{
			std::cout << testName << " FAIL : Expecting " << *itSTL << " at pos "<< i++ << " got " << *it << std::endl;
			return false;
		}
		itSTL++;
	}

	std::cout << testName << " => \033[1;32mOK\033[0m" << std::endl;
	return true;
}

void ft_constructor(void)
{
	ft::Vector<int> first;
	std::vector<int> firstSTL;
	assertVectorEquals(&first, &firstSTL, "Constructor - default");

	ft::Vector<int> second (4,100);
	std::vector<int> secondSTL (4,100);
	assertVectorEquals(&second, &secondSTL, "Constructor - fill");
/*
	ft::Vector<int> third (second.begin(),second.end());
	std::vector<int> thirdSTL (secondSTL.begin(),secondSTL.end());
	assertVectorEquals(&third, &thirdSTL, "Constructor - Range");

	ft::Vector<int> fourth (third);
	std::vector<int> fourthSTL (thirdSTL);
	assertVectorEquals(&fourth, &fourthSTL, "constructors fourth");
*/

}

void ft_test_vector(void)
{
   ft_constructor();
}