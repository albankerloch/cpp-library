#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <stack>
#include <vector>
#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"

#include <stdlib.h>
#include <ctime>

//#define MAX_RAM 429496729
#define MAX_RAM 429496
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public NAMESPACE::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename NAMESPACE::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	std::time_t tbegin = std::time(NULL);
	int ran;
	int ran2;

	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		std::time_t tend = std::time(NULL);
		std::cout << "Start time : " << tbegin << std::endl;
		std::cout << "End time   : " << tend << std::endl;
		std::cout << "Elapsed time : " << tbegin - tend << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	NAMESPACE::map<int, int> map_int;
	NAMESPACE::vector<std::string> vector_str;
	NAMESPACE::vector<int> vector_int;
	NAMESPACE::stack<int> stack_int;
	NAMESPACE::vector<Buffer> vector_buffer;
	NAMESPACE::stack<Buffer, std::deque<int> > stack_deq_buffer;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		ran = rand();
		//std::cout << ran << std::endl;
		const int idx = ran % COUNT;
		vector_buffer[idx].idx = 5;
	}

	NAMESPACE::vector<Buffer>().swap(vector_buffer);

	try
	{
	//	for (int i = 0; i < COUNT; i++)
//		{
			ran = rand();
			//std::cout << ran << std::endl;
			const int idx = ran % COUNT;
			vector_buffer.at(idx);
			//std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
	//	}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	for (int i = 0; i < COUNT; ++i)
	{
		ran = rand();
		ran2 = rand();
		//std::cout << "access " << ran << " value " << ran2 << std::endl;
		map_int.insert(NAMESPACE::make_pair(ran, ran2));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		ran = rand();
		//std::cout << ran << std::endl;
		int access = ran;
		sum += map_int[access];
		//std::cout << "access " << access << " value " << map_int[access] << std::endl;
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;
	{
		NAMESPACE::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	std::time_t tend = std::time(NULL);
	std::cout << "Start time : " << tbegin << std::endl;
	std::cout << "End time   : " << tend << std::endl;
	std::cout << "Elapsed time : " << tend - tbegin << std::endl;
	return (0);
}