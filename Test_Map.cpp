#include <map>

#include "Map.hpp"
#include "utils.hpp"

template <typename Key, typename T>
void STLPrintMap(std::map<Key, T> *stl) 
{
	typename std::map<Key, T>::iterator it_stl;
	size_t i;

	std::cout << " SIZES : STL = "<< stl->size() << std::endl;
	it_stl = stl->begin();
	i = 0;
	while(i < stl->size())
	{
		std::cout << " Value : STL = " << it_stl->first << " and " << it_stl->second << " at position " << i++ << std::endl;
		it_stl++;
	}
	//std::cout << " STL BEGIN : "<< *stl->begin() << std::endl;
	//std::cout << " STL BEGIN : "<< *stl->begin() << " STL END : "<< *stl->end() << std::endl;
	//std::cout << " STL FRONT : "<< stl->front() << " STL BACK : "<< stl->back() << std::endl;
}

template <typename Key, typename T>
void PrintMap(ft::map<Key, T> *stl) 
{
	typename ft::map<Key, T>::iterator it_stl;
	size_t i;

	std::cout << " SIZES : FT = "<< stl->size() << std::endl;
	it_stl = stl->begin();
	i = 0;
	while(i < stl->size())
	{
		std::cout << " Value : FT = " << it_stl->first << " and " << it_stl->second << " at position " << i++ << std::endl;
		it_stl++;
	}
	//std::cout << " STL BEGIN : "<< *stl->begin() << std::endl;
	//std::cout << " STL BEGIN : "<< *stl->begin() << " STL END : "<< *stl->end() << std::endl;
	//std::cout << " STL FRONT : "<< stl->front() << " STL BACK : "<< stl->back() << std::endl;
}

template <typename Key, typename T>
bool CompareMap(ft::map<Key, T> *ft, std::map<Key, T> *stl, const std::string &testName)
{
	typename std::map<Key, T>::iterator it_stl;
	typename ft::map<Key, T>::iterator it;
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
		if (it->first != it_stl->first || it->second != it_stl->second)
		{
			std::cout << testName << " FAIL - Value error : STL " << it_stl->first << " and " << it_stl->second << " vs FT " << it->first << " and " << it->second  << " at position "<< i++ << std::endl;
			return false;
		}
		it_stl++;
		it++;
	}
	std::cout << testName << " => \033[1;32mOK\033[0m" << std::endl;
	return true;
}

void ft_constructor(void)
{
	std::map<std::string, int> V1_STL;
	ft::map<std::string, int> V1;
	CompareMap(&V1, &V1_STL, "Constructor - default");

	PrintMap(&V1);
	STLPrintMap(&V1_STL);
 
	ft::map<int, char> VCHAR2;
	std::map<int, char> VCHAR2_STL;
	VCHAR2[1]='B';
	VCHAR2_STL[1]='B';
	//PrintMap(&VCHAR2);
	//STLPrintMap(&VCHAR2_STL);
	CompareMap(&VCHAR2, &VCHAR2_STL, "Constructor - default with char");

	ft::map<int, int> V2;
	std::map<int, int> V2STL;
	V2STL[1]=3;
	V2[1]=3;
	CompareMap(&V2, &V2STL, "Constructor - fill");

	std::map<int, int>  V3STL (V2STL.begin(),V2STL.end());
	ft::map<int, int> V3 (V2.begin(),V2.end());
	CompareMap(&V3, &V3STL, "Constructor - range");

	std::map<int, int>V4STL (V3STL);
	ft::map<int, int>V4(V3);
	//CompareMap(&V4, &V4STL, "Constructor - copy");
/*
	V1_STL = V4STL;
	V1 = V4;
	CompareMap(&V1, &V1_STL, "Constructor - operator = ");*/
}

void ft_test_map(void)
{
   ft_constructor();
   /*ft_assign();
   ft_push_pop_back();
   ft_insert_erase();
   ft_resize();
   ft_swap();
   ft_clear();
   ft_access();
   ft_relationnal_operator();
   ft_begin_end();*/
}