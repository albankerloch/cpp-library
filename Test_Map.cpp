#include <map>

#include "map.hpp"

template <typename Key, typename T>
void PrintMap(NAMESPACE::map<Key, T> *stl, std::string str = "test") 
{
	typename NAMESPACE::map<Key, T>::iterator it_stl;
	size_t i;


	std::cout << "------------------------------------ " << str << std::endl;
	std::cout << " SIZES : STL = "<< stl->size() << std::endl;
	it_stl = stl->begin();
	i = 0;
	while(i < stl->size())
	{
		std::cout << " Value : STL = " << it_stl->first << " and " << it_stl->second << " at position " << i++ << std::endl;
		it_stl++;
	}
}

void ft_constructor(void)
{

	NAMESPACE::map<std::string, int> V1_STL;
	PrintMap(&V1_STL);
 
	NAMESPACE::map<int, char> VCHAR2;
	VCHAR2[1]='B';
	PrintMap(&VCHAR2);

	NAMESPACE::map<int, int> V2;
	V2[1]=3;
	PrintMap(&V2);

	V2[2]=4;
	NAMESPACE::map<int, int> V3 (V2.begin(),V2.end());
	PrintMap(&V2, "Constructor - range");
/*
	map<int, int>V4STL (V3STL);
	NAMESPACE::map<int, int>V4(V3);
	CompareMap(&V4, &V4STL, "Constructor - copy");

	V2STL = V4STL;
	V2 = V4;
	CompareMap(&V1, &V1_STL, "Constructor - operator = ");

	PrintMap(&V2);
	STLPrintMap(&V2STL);*/
}


void ft_test_map(void)
{
   ft_constructor();
   /*
   ft_insert_erase();
   ft_swap();
   ft_clear();
   ft_access();
   ft_begin_end();*/
}