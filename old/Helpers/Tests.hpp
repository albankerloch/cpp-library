#ifndef FT_CONTAINERS_TESTS_HPP
#define FT_CONTAINERS_TESTS_HPP
# include <iostream>

extern int g_total;
extern int g_success;

template <typename T>
bool assertEqual(const T &t2,const T &t1, const std::string &testName){
	g_total++;
	if (t1 == t2) {
		g_success++;
		std::cout << "\033[1;32mSuccess\033[0m > " << testName << " > assertEqual" << std::endl;
		return true;
	}
	std::cout << "\033[1;31mFail\033[0m: > " << testName << " > Expecting " << t1 << " got " << t2 << std::endl;
	return false;
}

template <typename T>
bool assertPTREqual(const T &t1,const T &t2, const std::string &testName){
	g_total++;
	if (t1 == t2) {
		g_success++;
		std::cout << "\033[1;32mSuccess\033[0m > " << testName << " > ptr are the same" << std::endl;
		return true;
	}
	std::cout << "\033[1;31mFail\033[0m: > " << testName << " > Expecting " << &t1 << " got " << &t2 << std::endl;
	return false;
}

template <typename T>
bool assertPTRNotEqual(const T &t1,const T &t2, const std::string &testName){
	g_total++;
	if (t1 != t2) {
		g_success++;
		std::cout << "\033[1;32mSuccess\033[0m > " << testName << " > ptr are not the same" << std::endl;
		return true;
	}
	std::cout << "\033[1;31mFail\033[0m: > " << testName << " > Expecting " << &t1 << " got " << &t2 << std::endl;
	return false;
}

inline void incrTestSuccess() {
	g_success++;
}

inline void incrTestTotal() {
	g_total++;
}

inline void printTestsResult() {
	std::cout << g_success << "/" << g_total << " tests passed" << std::endl;
}

#endif //FT_CONTAINERS_TESTS_HPP
