void ft_test_vector(void);
void ft_test_map(void);
void ft_test_stack(void);
#include <ctime>
#include <iostream>

int main(void)
{
	std::time_t vtbegin;
	std::time_t vtend;
	std::time_t stbegin;
	std::time_t stend;
	std::time_t mtbegin;
	std::time_t mtend;
    
    vtbegin = std::time(NULL);
    //ft_test_vector();
    vtend = std::time(NULL);
    std::cout << "=====================================================> Vector time : " << vtbegin - vtend << std::endl;
    stbegin = std::time(NULL);
    //ft_test_stack();
    stend = std::time(NULL);
    std::cout << "=====================================================> Stack  time : " << stbegin - stend << std::endl;
    mtbegin = std::time(NULL);
    ft_test_map();
    mtend = std::time(NULL);
    std::cout << "=====================================================> Vector time : " << vtbegin - vtend << std::endl;
    std::cout << "=====================================================> Stack  time : " << stbegin - stend << std::endl;
    std::cout << "=====================================================> Map    time : " << stbegin - stend << std::endl << std::endl;
}