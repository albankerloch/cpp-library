void ft_test_vector(void);
void ft_test_map(void);
void ft_test_stack(void);
#include <ctime>
#include <iostream>

int main(void)
{
	std::time_t tbegin;
	std::time_t tend;
    
    tbegin = std::time(NULL);
    //ft_test_vector();
    tend = std::time(NULL);
    std::cout << "Vector time : " << tbegin - tend << std::endl;
    tbegin = std::time(NULL);
    //ft_test_stack();
    tend = std::time(NULL);
    std::cout << "Stack time : " << tbegin - tend << std::endl;
    tbegin = std::time(NULL);
    ft_test_map();
    tend = std::time(NULL);
    std::cout << "Map time : " << tbegin - tend << std::endl;
}