#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <stack>
#include <vector>
#include <ctime>
#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
void ft_test_vector(void);
void ft_test_map(void);
void ft_test_stack(void);
void main_sujet(void);

#define MAX_RAM 429496729
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

int main(int argc, char** argv) 
{
	clock_t tv;
	clock_t tv2;
	clock_t ts;
	clock_t ts2;
	clock_t tm;
	clock_t tm2;

    std::cout << "<====================================< Vector test >====================================>" << std::endl << std::endl;
    tv = clock();
    ft_test_vector();
	tv2 = clock();

    std::cout << "<====================================< Stack test >====================================>" << std::endl << std::endl;
    ts = clock();
    ft_test_stack();
	ts2 = clock();

    std::cout << "<====================================< Map test >====================================>" << std::endl << std::endl;  
    tm = clock();
    ft_test_map();
	tm2 = clock();

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
		const int idx = ran % COUNT;
		vector_buffer[idx].idx = 5;
	}

	NAMESPACE::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			ran = rand();
			const int idx = ran % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	for (int i = 0; i < COUNT; ++i)
	{
		ran = rand();
		ran2 = rand();
		map_int.insert(NAMESPACE::make_pair(ran, ran2));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		ran = rand();
		int access = ran;
		sum += map_int[access];
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
	std::cout << "Elapsed time : " << tend - tbegin << std::endl << std::endl;

    std::cout << "=====================================================> Vector time " << tv2 - tv << std::endl << std::endl;
    std::cout << "=====================================================> Stack  time " << ts2 - ts2 << std::endl << std::endl;
    std::cout << "=====================================================> Map    time " << tm2 - tm << std::endl << std::endl;

	return (0);
}