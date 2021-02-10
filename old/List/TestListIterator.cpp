#include <iostream>
#include "List.hpp"
#include "../Helpers/Tests.hpp"
#include <list>

static void testConstructors() {
	int myints[] = {2,77,177,277};
	ft::List<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int>::iterator it;
	ft::List<int>::iterator it2(ft.begin());
	ft::List<int>::iterator it3 = it2;


	it = it2;
	assertEqual(*it, *it2, "constructor(copy)");
	assertEqual(*it3, *it2, "constructor=");
}

void testEmpty() {
	ft::List<int> init;

	ft::List<int>::iterator begin = init.begin();
	ft::List<int>::iterator end = init.end();

	assertPTREqual(begin, end, "empty");
}
static void testDeference() {
	int myints[] = {2,77,177,277};
	ft::List<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> std(myints, myints + sizeof(myints) / sizeof(int));

	ft::List<int>::iterator it = ft.begin();
	std::list<int>::iterator itSTL = std.begin();

	*it = 4;
	*itSTL = 4;

	assertEqual(*it, *itSTL, "deferencement");
}

static void testComp() {
	int myints[] = {2,77,177,277};
	ft::List<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int> ft2(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> std(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> std2(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int>::iterator it = ft.begin();
	ft::List<int>::iterator it2 = ft.begin();
	std::list<int>::iterator itSTL = std.begin();
	std::list<int>::iterator itSTL2 = std.begin();

	assertEqual((it == it2), (itSTL == itSTL2), "operator==");
	assertEqual((it == ++it2), (itSTL == ++itSTL2), "operator== diff");
	assertEqual((it != --it2), (itSTL != --itSTL2), "operator!=");
	assertEqual((it != ++it2), (itSTL != ++itSTL2), "operator!= diff");
}

static void testIncrDecr() {
	int myints[] = {2,77,177,277};
	ft::List<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> std(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int>::iterator it = ft.begin();
	std::list<int>::iterator itSTL = std.begin();

	assertEqual(*it, *itSTL, ".first()");
	assertEqual(*it++, *itSTL++, "operator++");
	assertEqual(*++it, *++itSTL, "++operator");

	assertEqual(*it--, *itSTL--, "--operator");
	assertEqual(*--it, *--itSTL, "operator--");
	it = ft.end();
	itSTL = std.end();
	assertEqual(*--it, *--itSTL, ".end()");
}

static void testReverseIncrDecr() {
	int myints[] = {2,77,177,277};
	ft::List<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> std(myints, myints + sizeof(myints) / sizeof(int));

	ft::List<int>::reverse_iterator it = ft.rbegin();
	std::list<int>::reverse_iterator itSTL = std.rbegin();

	assertEqual(*it, *itSTL, "reverse .first()");
	assertEqual(*it++, *itSTL++, "reverse operator++");
	assertEqual(*++it, *++itSTL, "reverse ++operator");

	assertEqual(*it--, *itSTL--, "reverse --operator");
	assertEqual(*--it, *--itSTL, "reverse operator--");
	it = ft.rend();
	itSTL = std.rend();
	assertEqual(*--it, *--itSTL, "reverse .end()");

}

void testListIterator() {
	std::cout << "\033[1;37m                           >> LIST ITERATORS <<                            \033[0m" << std::endl;
	testEmpty();
	testConstructors();
	testDeference();
	testIncrDecr();
	testReverseIncrDecr();
	testComp();
}