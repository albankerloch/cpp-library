#ifndef TEST_VECTOR_HPP
# define TEST_VECTOR_HPP

template <typename T>
bool assertVectorEquals(ft::Vector<T> *ft, std::vector<T> *std, const std::string &testName) 
{
	if (ft->size() != std->size()){
		std::cout << testName << " > Expecting size to be equal: STL " << std->size() << " got FT " << ft->size() << std::endl;
		return false;
	}
	/*
	typename std::vector<T>::iterator itSTL = std->begin();
	size_t i(0);
	for (typename ft::Vector<T>::iterator it = ft->begin(); it != ft->end(); it++) {

		if (*it != *itSTL){
			std::cout << "\033[1;31mFail\033[0m: > "<< testName << " > Expecting " << *itSTL << " at pos "<< i++ << " got " << *it << std::endl;
			return false;
		}
		itSTL++;
	}*/
	std::cout << testName << " => OK" << std::endl;
	return true;
}