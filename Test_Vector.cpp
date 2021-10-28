#include "Vector.hpp"
#include <vector>
#include <cstring>

template <typename T>
bool Printvector(NAMESPACE::vector<T> *stl, std::string str = "test") 
{
	typename NAMESPACE::vector<T>::iterator it;
	size_t i;

	std::cout << "------------------------------------ " << str << std::endl;
	std::cout << " SIZES : = "<< stl->size() << std::endl;

	it = stl->begin();
	i = 0;
	while(it != stl->end())
	{
		std::cout << " SHOW : at pos "<< i++ << " got " << *it << std::endl;
		it++;
	}
	return true;
}

void ft_vector_capacity()
{
	NAMESPACE::vector<int> V1 (3, 39);
	NAMESPACE::vector<int> V2;
	Printvector(&V1, "Capacity");

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
	Printvector(&V1, "Resize - 2");

	V1.resize(11);
	std::cout << "Resize " <<  V1.capacity() << std::endl;
	Printvector(&V1, "Resize - 11");

	V1.resize(15, 666);
	std::cout << "Resize " <<  V1.capacity()  << std::endl;
	Printvector(&V1,  "Resize - 11");
}

void ft_vector_begin_end()
{
	NAMESPACE::vector<int> V1 (3, 39);

	V1.push_back(3);
	Printvector(&V1, "Begin / End");

	std::cout << "Begin " <<  *V1.begin() << std::endl;
	std::cout << "rBegin " <<  *V1.rbegin() << std::endl;
	std::cout << "End " <<  *(V1.end() - 1) << std::endl;
	std::cout << "rEnd " <<  *V1.rend() << std::endl;
}

void ft_vector_relationnal_operator(void)
{
	std::cout << "------------------------------------ " << "Relationnal operator" << std::endl;
	NAMESPACE::vector<int> V1 (3, 39);
	NAMESPACE::vector<int> V2 (3, 39);
	NAMESPACE::vector<int> V3 (4, 39);

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

void ft_vector_access(void)
{
	NAMESPACE::vector<int> V1 (3, 39);

	V1.push_back(5);
	Printvector(&V1, "Operator - default");

	std::cout << "Operator [] : " << V1[3] << " at 3"  << std::endl;
	std::cout << "Operator [] : " << V1[0] << " at 0"  << std::endl;
	std::cout << "Operator at : " << V1.at(3) << " at 3"  << std::endl;
	std::cout << "Operator at : " << V1.at(0) << " at 0"  << std::endl;
	std::cout << "Front : " << V1.front() << " at 3"  << std::endl;
	std::cout << "Back : " << V1.back()  << " at 0"  << std::endl; 
}

void ft_vector_clear(void)
{
	NAMESPACE::vector<int> V1 (3, 39);

	V1.clear();
	Printvector(&V1,  "Clear - default");
}

void ft_vector_swap(void)
{
	NAMESPACE::vector<int> V1 (3, 39);
	NAMESPACE::vector<int> V2 (2,50);

	V1.swap(V2);
	Printvector(&V1, "Swap - first element");
	Printvector(&V2, "Swap - second element");
}

void ft_vector_insert_erase(void)
{
	NAMESPACE::vector<int> V1 (3, 39);

	V1.insert(V1.begin() + 1, 5);
	Printvector(&V1, "Insert - one element");

	V1.insert(V1.end(), 6);
	Printvector(&V1, "Insert again - one element");

	NAMESPACE::vector<int> V2 (2, 14);
	V1.insert(V1.begin(), V2.begin(), V2.end());
	Printvector(&V1, "Insert again - one range");

	V1.erase(V1.begin());
	Printvector(&V1, "Erase - one element");

	V1.erase(V1.begin(), V1.begin() + 2);
	Printvector(&V1, "Erase - one range");
}

void ft_vector_push_pop_back(void)
{
	NAMESPACE::vector<int> V1 (3, 39);

	V1.push_back(55);
	Printvector(&V1, "Push_back - default");

	V1.push_back(51);
	Printvector(&V1, "Push_back again - default");

	V1.pop_back();
	Printvector(&V1, "Pop_back - default");

	V1.pop_back();
	V1.pop_back();
	Printvector(&V1, "Pop_back again - default");
}

void ft_vector_assign(void)
{
	NAMESPACE::vector<int> V1 (3, 39);
	NAMESPACE::vector<int> V2 (3,50);

	V1.assign(++V2.begin(), V2.end());
	Printvector(&V1, "Assign - with iterator");

	V1.assign(7, 21);
	Printvector(&V1, "Assign - with value");

	NAMESPACE::vector<std::string> VCHAR2(1,"Test");
	Printvector(&VCHAR2, "Assign - with string value");

	NAMESPACE::vector<std::string> VCHAR3(0,"Test");
	Printvector(&VCHAR3, "Assign - with size at 0");
}

void ft_vector_constructor(void)
{
	NAMESPACE::vector<int> V1;
	Printvector(&V1, "Constructor - default");

	NAMESPACE::vector<char> VCHAR2(5, 'A');
	Printvector(&VCHAR2, "Constructor - default with char");

	NAMESPACE::vector<int> V2 (3, 39);
	Printvector(&V2, "Constructor - fill");

	NAMESPACE::vector<int> V3 (V2.begin(),V2.end());
	Printvector(&V3, "Constructor - range");

	NAMESPACE::vector<int> V4(V3);
	Printvector(&V4, "Constructor - copy");

	V1 = V4;
	Printvector(&V1, "Constructor - operator = ");
}


void ft_test_vector(void)
{
   ft_vector_constructor();
   ft_vector_assign();
   ft_vector_push_pop_back();
   ft_vector_insert_erase();
   ft_vector_swap();
   ft_vector_clear();
   ft_vector_access();
   ft_vector_relationnal_operator();
   ft_vector_begin_end();
   ft_vector_capacity();
}
