void ft_test_vector(void);
void ft_test_map(void);
void ft_test_stack(void);
#include <ctime>
#include <iostream>

int main(void)
{
    clock_t t;

    t = clock();
    ft_test_vector();
    std::cout << "=====================================================> Vector time " << clock() - t << std::endl;

    t = clock();
    //ft_test_stack();
    std::cout << "=====================================================> Stack  time " << clock() - t << std::endl;
    
    t = clock();
    ft_test_map();
    std::cout << "=====================================================> Map    time " << clock() - t << std::endl;
}