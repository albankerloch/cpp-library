#include <map>
#include "map.hpp"

template <typename Key, typename T>
void PrintMap(NAMESPACE::map<Key, T> *stl, std::string str = "test") 
{
	typename NAMESPACE::map<Key, T>::iterator it_stl;
	size_t i;

	std::cout << "------------------------------------ " << str << std::endl;
	std::cout << " SIZES : = "<< stl->size() << std::endl;
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
	PrintMap(&V1_STL, "Constructor - default");
 
	NAMESPACE::map<int, char> VCHAR2;
	VCHAR2[1]='B';
	PrintMap(&VCHAR2, "Constructor - default with char");

	NAMESPACE::map<int, int> V2;
	V2[2]=3;
	PrintMap(&V2, "Constructor - fill");

	V2[-2]=4;
	V2[0]=4;
	V2[-1]=4;
	V2[4]=4;
	PrintMap(&V2, "Constructor - fill");
	NAMESPACE::map<int, int> V3 (V2.begin(),V2.end());
	PrintMap(&V2, "Constructor - range");

	NAMESPACE::map<int, int>V4(V3);
	PrintMap(&V4,  "Constructor - copy");

	V2 = V4;
	PrintMap(&V2, "Constructor - operator = ");
}

void ft_insert_erase(void)
{
	NAMESPACE::map<int, int>  V1;
	NAMESPACE::map<int, int> ::iterator it;
	NAMESPACE::map<int, int> ::iterator it2;


	V1.insert(V1.begin(),NAMESPACE::make_pair(1,5));
	PrintMap(&V1, "Insert - one element");

	V1.insert(V1.end(), NAMESPACE::make_pair(4,3));
	PrintMap(&V1, "Insert again - one element");
	V1.insert(V1.end(), NAMESPACE::make_pair(5,3));
	PrintMap(&V1, "Insert again - one element");

	it = V1.begin();
	it2 = V1.end();
	it2--;
	std::cout << "it = " << it->first << " " << it->second << std::endl;
	std::cout << "it2 = " << it2->first << " " << it2->second << std::endl;

	V1.insert(V1.end(), NAMESPACE::make_pair(2,3));
	PrintMap(&V1, "Insert again - one element");
	
	std::cout << "it = " << it->first << " " << it->second << std::endl;
	std::cout << "it2 = " << it2->first << " " << it2->second << std::endl;
	V1.erase(++V1.begin());
	PrintMap(&V1, "Erase - one element");
	std::cout << "it = " << it->first << " " << it->second << std::endl;
	std::cout << "it2 = " << it2->first << " " << it2->second << std::endl;

	V1.insert(V1.end(), NAMESPACE::make_pair(6,3));
	PrintMap(&V1, "Insert again - one element");

	it2++;
	V1.erase(++V1.begin(), --V1.end());
	PrintMap(&V1, "Erase - one range");
	std::cout << "it = " << it->first << " " << it->second << std::endl;
	std::cout << "it2 = " << it2->first << " " << it2->second << std::endl;
}

void ft_clear(void)
{
	NAMESPACE::map<int, int>  V1;

	V1.insert(V1.begin(),NAMESPACE::make_pair(1,5));

	V1.clear();
	PrintMap(&V1, "Clear - default");
}

void ft_swap(void)
{
	NAMESPACE::map<int, int>  V1;
	NAMESPACE::map<int, int> ::iterator it;
	NAMESPACE::map<int, int> ::iterator it2;
	NAMESPACE::map<int, int> ::iterator it3;
	NAMESPACE::map<int, int> ::iterator it4;
	NAMESPACE::map<int, int> ::iterator it5;
	NAMESPACE::map<int, int>  V2;

	V1.insert(V1.begin(),NAMESPACE::make_pair(1,5));
	V1.insert(V1.begin(),NAMESPACE::make_pair(2,7));
	V1.insert(V1.begin(),NAMESPACE::make_pair(-1,8));
	V2.insert(V2.begin(),NAMESPACE::make_pair(-2,7));
	V2.insert(V2.begin(),NAMESPACE::make_pair(51,8));

	it = V1.begin();
	it2 = V1.begin();
	it2++;
	it3 = V1.end();
	it3--;
	it4 = V2.begin();
	it5 = V2.end();
	it5--;
	
	std::cout << "it = " << it->first << " " << it->second << std::endl;
	std::cout << "it2 = " << it2->first << " " << it2->second << std::endl;
	std::cout << "it3 = " << it3->first << " " << it3->second << std::endl;
	std::cout << "it4 = " << it4->first << " " << it4->second << std::endl;
	std::cout << "it5 = " << it5->first << " " << it5->second << std::endl;

	V1.swap(V2);
	PrintMap(&V1, "Swap - first element");
	PrintMap(&V2, "Swap - second element");

	std::cout << "it = " << it->first << " " << it->second << std::endl;
	std::cout << "it2 = " << it2->first << " " << it2->second << std::endl;
	std::cout << "it3 = " << it3->first << " " << it3->second << std::endl;
	std::cout << "it4 = " << it4->first << " " << it4->second << std::endl;
	std::cout << "it5 = " << it5->first << " " << it5->second << std::endl;

	it++;
	it2++;
	it3--;
	it4++;
	it5--;

	std::cout << "it = " << it->first << " " << it->second << std::endl;
	std::cout << "it2 = " << it2->first << " " << it2->second << std::endl;
	std::cout << "it3 = " << it3->first << " " << it3->second << std::endl;
	std::cout << "it4 = " << it4->first << " " << it4->second << std::endl;
	std::cout << "it5 = " << it5->first << " " << it5->second << std::endl;
}

void ft_access(void)
{
	std::cout << "------------------------------------ " << "Size of plenty" << std::endl;
	NAMESPACE::map<int, int>  V1;

	V1.insert(V1.begin(),NAMESPACE::make_pair(1,5));
	
	std::cout << "Max_Size " <<  V1.max_size() << std::endl;
	std::cout << "Empty " <<  V1.empty() << std::endl;

	NAMESPACE::map<int, int> V2;

	std::cout << "Empty " <<  V2.empty() << std::endl;
}

void ft_begin_end()
{
	std::cout << "------------------------------------ " << "A begin and an end" << std::endl;
	NAMESPACE::map<int, int>  V1;

	V1.insert(V1.begin(),NAMESPACE::make_pair(1,5));
	V1.insert(V1.begin(),NAMESPACE::make_pair(2,6));

	std::cout << "Begin (" << V1.begin()->first << " | " << V1.begin()->second << ")" << std::endl;
	std::cout << "Rbegin (" << V1.rbegin()->first << " | " <<  V1.rbegin()->second << ")" << std::endl;
	std::cout << "End (" << (--V1.end())->first << " | " <<  (--V1.end())->second << ")" << std::endl;
	std::cout << "Rend (" << (--V1.rend())->first << " | " <<  (--V1.rend())->second << ")" << std::endl;
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
