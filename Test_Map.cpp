#include <map>

#include "Map.hpp"
#include "utils.hpp"

void ft_constructor(void)
{
	std::map<std::string, int> V1_STL;
	ft::map<std::string, int> V1;
	//CompareMap(&V1, &V1_STL, "Constructor - default");

	//PrintList(&V1_STL);
/*
	ft::map<char> VCHAR2(5,'A');
	std::map<char> VCHAR2_STL(5, 'A');
	CompareList(&VCHAR2, &VCHAR2_STL, "Constructor - default with char");

	std::map<int> V2STL (3, 39);
	ft::map<int> V2 (3, 39);
	CompareList(&V2, &V2STL, "Constructor - fill");

	std::map<int> V3STL (V2STL.begin(),V2STL.end());
	ft::map<int> V3 (V2.begin(),V2.end());
	CompareList(&V3, &V3STL, "Constructor - range");

	std::map<int> V4STL (V3STL);
	ft::map<int> V4(V3);
	CompareList(&V4, &V4STL, "Constructor - copy");

	V1_STL = V4STL;
	V1 = V4;
	CompareList(&V1, &V1_STL, "Constructor - operator = ");*/
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