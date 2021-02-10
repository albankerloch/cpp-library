#include <map>
#include "MapIterator.hpp"
#include "../Helpers/Tests.hpp"
#include "Map.hpp"

void static testConstructors() {
	ft::Map<char, int>::iterator it;
	std::map<char, int>::iterator itSTL;

	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x'] = 0;
	std['x'] = 0;

	ft::Map<char, int>::iterator it2(ft.begin());
	std::map<char, int>::iterator itSTL2(std.begin());
	assertEqual((*it2).first, (*itSTL2).first, "copy constructible");

	it = it2;
	itSTL = itSTL2;
	assertEqual((*it).first, (*itSTL).first, "copy assignable");
}

void testEquality() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x'] = 0;
	std['x'] = 0;
	ft::Map<char, int>::iterator it = ft.begin();
	std::map<char, int>::iterator itSTL = std.begin();

	assertEqual(it == ft.begin(), itSTL == std.begin(), "==");
	assertEqual(it == ft.end(), itSTL == std.end(), "==");
	assertEqual(it != ft.begin(), itSTL != std.begin(), "!=");
	assertEqual(it != ft.end(), itSTL != std.end(), "!=");
}

void testDeference() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x'] = 0;
	std['x'] = 0;
	ft::Map<char, int>::iterator it = ft.begin();
	std::map<char, int>::iterator itSTL = std.begin();

	assertEqual((*it).first, (*itSTL).first, "*a");
	assertEqual(it->first, itSTL->first, "a->m");
}

void static testLvalue() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x'] = 0;
	std['x'] = 0;
	ft::Map<char, int>::iterator it = ft.begin();
	std::map<char, int>::iterator itSTL = std.begin();

	it->second = 20;
	itSTL->second = 20;
	assertEqual(ft['x'],std['x'], "*a = t");
}

void static testIncr() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x'] = 0;
	std['x'] = 0;
	ft['a'] = 5;
	std['a'] = 5;
	ft['u'] = 10;
	std['u'] = 10;
	ft['p'] = 20;
	std['p'] = 20;
	ft::Map<char, int>::iterator it = ft.begin();
	std::map<char, int>::iterator itSTL = std.begin();

	++it;
	++itSTL;
	assertEqual(it->first, itSTL->first, "++a");
	assertEqual((*it++).first, (*itSTL++).first, "++a");
	assertEqual(it++->first, itSTL++->first, "*a++");
}

void static testReverseIncr() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x'] = 0;
	std['x'] = 0;
	ft['a'] = 5;
	std['a'] = 5;
	ft['u'] = 10;
	std['u'] = 10;
	ft['p'] = 20;
	std['p'] = 20;
	ft::Map<char, int>::reverse_iterator it = ft.rbegin();
	std::map<char, int>::reverse_iterator itSTL = std.rbegin();

	++it;
	++itSTL;
	assertEqual(it->first, itSTL->first, "reverse ++a");
	assertEqual((*it++).first, (*itSTL++).first, "reverse ++a");
	assertEqual(it++->first, itSTL++->first, "reverse *a++");
}

static void testReverseDecr() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x'] = 0;
	std['x'] = 0;
	ft['a'] = 5;
	std['a'] = 5;
	ft['u'] = 10;
	std['u'] = 10;
	ft['p'] = 20;
	std['p'] = 20;
	ft::Map<char, int>::reverse_iterator it = ft.rend();
	std::map<char, int>::reverse_iterator itSTL = std.rend();

	--it;
	--itSTL;
	assertEqual(it->first, itSTL->first, "reverse --a");
	assertEqual((*it--).first, (*itSTL--).first, "reverse --a");
	assertEqual(it--->first, itSTL--->first, "reverse *a--");
}

static void testDecr() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x'] = 0;
	std['x'] = 0;
	ft['a'] = 5;
	std['a'] = 5;
	ft['u'] = 10;
	std['u'] = 10;
	ft['p'] = 20;
	std['p'] = 20;
	ft::Map<char, int>::iterator it = ft.end();
	std::map<char, int>::iterator itSTL = std.end();

	--it;
	--itSTL;
	assertEqual(it->first, itSTL->first, "--a");
	assertEqual((*it--).first, (*itSTL--).first, "--a");
	assertEqual(it--->first, itSTL--->first, "*a--");
}

void testMapIterator() {
	std::cout << "\033[1;37m                           >> MAP ITERATORS <<                            \033[0m" << std::endl;
	testConstructors();
	testEquality();
	testDeference();
	testLvalue();
	testIncr();
	testDecr();
	testReverseIncr();
	testReverseDecr();
}