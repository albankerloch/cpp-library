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

void ft_clear(void)
{
	std::map<int, int> V1STL;
	ft::map<int, int>  V1;

	V1STL.insert(V1STL.begin(), std::make_pair(1,5));
	V1.insert(V1.begin(),std::make_pair(1,5));

	V1STL.clear();
	V1.clear();
	CompareMap(&V1, &V1STL, "Clear - default");
}

void ft_swap(void)
{
	std::map<int, int> V1STL;
	ft::map<int, int>  V1;

	V1STL.insert(V1STL.begin(), std::make_pair(1,5));
	V1.insert(V1.begin(),std::make_pair(1,5));

	std::map<int, int> V2STL;
	ft::map<int, int>  V2;

	V1STL.swap(V2STL);
	V1.swap(V2);
	CompareMap(&V1, &V1STL, "Swap - first element");
	CompareMap(&V2, &V2STL, "Swap - second element");
}

void ft_insert_erase(void)
{
	std::map<int, int> V1STL;
	ft::map<int, int>  V1;

	V1STL.insert(V1STL.begin(), std::make_pair(1,5));
	V1.insert(V1.begin(),std::make_pair(1,5));
	CompareMap(&V1, &V1STL, "Insert - one element");

	V1STL.insert(V1STL.end(), std::make_pair(2,3));
	V1.insert(V1.end(), std::make_pair(2,3));
	CompareMap(&V1, &V1STL, "Insert again - one element");

	V1STL.erase(V1STL.begin());
	V1.erase(V1.begin());
	CompareMap(&V1, &V1STL, "Erase - one element");

	V1STL.erase(V1STL.begin(), (V1STL.begin()++));
	V1.erase(V1.begin(), (V1.begin()++));
	CompareMap(&V1, &V1STL, "Erase - one range");
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

	V2STL[2]=4;
	V2[2]=4;
	std::map<int, int>  V3STL (V2STL.begin(),V2STL.end());
	ft::map<int, int> V3 (V2.begin(),V2.end());
	CompareMap(&V3, &V3STL, "Constructor - range");

	std::map<int, int>V4STL (V3STL);
	ft::map<int, int>V4(V3);
	CompareMap(&V4, &V4STL, "Constructor - copy");

	V2STL = V4STL;
	V2 = V4;
	CompareMap(&V1, &V1_STL, "Constructor - operator = ");

	PrintMap(&V2);
	STLPrintMap(&V2STL);
}

void ft_access(void)
{
	std::map<int, int> V1STL;
	ft::map<int, int>  V1;

	V1STL.insert(V1STL.begin(), std::make_pair(1,5));
	V1.insert(V1.begin(),std::make_pair(1,5));
	//STLPrintList(&V1STL);
	//PrintList(&V1);
	
 	if (V1.max_size() == V1STL.max_size())
		std::cout << " Success - max_Size " <<  V1.max_size() << " vs " << V1STL.max_size() << std::endl;
	else
		std::cout << " Fail - max_Size " <<  V1.max_size() << " vs " << V1STL.max_size() <<  std::endl;

	if (V1.empty() == V1STL.empty())
		std::cout << " Success - Empty " <<  V1.empty() << " vs " << V1STL.empty()<< std::endl;
	else
		std::cout << " Fail - Empty " <<  V1.empty()<< " vs " << V1STL.empty()<<  std::endl;

	std::map<int, int> V2STL;
	ft::map<int, int> V2;

	if (V2.empty() == V2STL.empty())
		std::cout << " Success - Empty " <<  V2.empty() << " vs " << V2STL.empty()<< std::endl;
	else
		std::cout << " Fail - Empty " <<  V2.empty()<< " vs " << V2STL.empty()<<  std::endl;
}


void ft_begin_end()
{
	std::map<int, int> V1STL;
	ft::map<int, int>  V1;

	V1STL.insert(V1STL.begin(), std::make_pair(1,5));
	V1.insert(V1.begin(),std::make_pair(1,5));

	//STLPrintList(&V1STL);
	//PrintList(&V1);

	if (V1.begin()->first == V1STL.begin()->first)
		std::cout << " Success - Begin " << std::endl;
	else
		std::cout << " Fail - Begin " <<  std::endl;

	if (V1.rbegin()->first == V1STL.rbegin()->first)
		std::cout << " Success - rBegin "  << std::endl;
	else
		std::cout << " Fail - rBegin " <<  std::endl;
}

void ft_test_map(void)
{
   ft_constructor();
   ft_insert_erase();
   ft_swap();
   ft_clear();
   ft_access();
   ft_begin_end();
}