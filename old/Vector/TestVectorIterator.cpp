#include <iostream>
#include "Vector.hpp"
#include "../Helpers/Tests.hpp"
#include <vector>

static void testReverseComparaisonOperator() {
	int myints[] = {2,77,177,68, 42, 277};
	ft::Vector<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::vector<int> std(myints, myints + sizeof(myints) / sizeof(int));

	ft::Vector<int>::reverse_iterator it = ft.rbegin();
	std::vector<int>::reverse_iterator itSTL = std.rbegin();

	it += 2;
	itSTL += 2;
	assertEqual((ft.rbegin() > it), (std.rbegin() > itSTL), "operator>");
	assertEqual((ft.rend() > it), (std.rend() > itSTL), "operator>");
	assertEqual((ft.rbegin() >= it), (std.rbegin() >= itSTL), "operator>=");
	assertEqual((ft.rend() >= it), (std.rend() >= itSTL), "operator>=");
	assertEqual((ft.rbegin() < it), (std.rbegin() < itSTL), "operator<");
	assertEqual((ft.rend() < it), (std.rend() < itSTL), "operator<");
	assertEqual((ft.rbegin() <= it), (std.rbegin() <= itSTL), "operator<=");
	assertEqual((ft.rend() <= it), (std.rend() <= itSTL), "operator<");
}

static void testComparaisonOperator() {
	int myints[] = {2,77,177,68, 42, 277};
	ft::Vector<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::vector<int> std(myints, myints + sizeof(myints) / sizeof(int));

	ft::Vector<int>::iterator it = ft.begin();
	std::vector<int>::iterator itSTL = std.begin();

	it += 2;
	itSTL += 2;
	assertEqual((ft.begin() > it), (std.begin() > itSTL), "operator>");
	assertEqual((ft.end() > it), (std.end() > itSTL), "operator>");
	assertEqual((ft.begin() >= it), (std.begin() >= itSTL), "operator>=");
	assertEqual((ft.end() >= it), (std.end() >= itSTL), "operator>=");
	assertEqual((ft.begin() < it), (std.begin() < itSTL), "operator<");
	assertEqual((ft.end() < it), (std.end() < itSTL), "operator<");
	assertEqual((ft.begin() <= it), (std.begin() <= itSTL), "operator<=");
	assertEqual((ft.end() <= it), (std.end() <= itSTL), "operator<");
}

static void testIncrDecr() {
	int myints[] = {2,77,177,68, 42, 277, 402};
	ft::Vector<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::vector<int> std(myints, myints + sizeof(myints) / sizeof(int));

	ft::Vector<int>::iterator it = ft.begin();
	std::vector<int>::iterator itSTL = std.begin();

	assertEqual(*it, *itSTL, ".begin()");
	it += 1;
	itSTL += 1;
	assertEqual(*it, *itSTL, "operator +=");
	it -= 1;
	itSTL -= 1;
	assertEqual(*it, *itSTL, " operator -=");
	assertEqual(*it++, *itSTL++, " operator++");
	assertEqual(*++it, *++itSTL, " ++operator");
	assertEqual(*it--, *itSTL--, " --operator");
	assertEqual(*--it, *--itSTL, " operator--");
	it++;
	itSTL++;
	assertEqual(*(it - 1), *(itSTL - 1), " operator-");
	assertEqual(*(it + 1), *(itSTL + 1), " operator+");
	it = ft.end();
	itSTL = std.end();
	assertEqual(*--it, *--itSTL, ".end()");
}

static void testOperator() {
	int myints[] = {2,77,177,68, 42, 277};
	ft::Vector<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::vector<int> std(myints, myints + sizeof(myints) / sizeof(int));

	ft::Vector<int>::iterator it = ft.begin();
	std::vector<int>::iterator itSTL = std.begin();
	assertEqual(it[0], itSTL[0], "reverse operator[] 0");
	assertEqual(it[2], itSTL[2], "reverse operator[] 2");
}

static void testReverseIncrDecr() {
	int myints[] = {2,77,177,68, 42, 277};
	ft::Vector<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::vector<int> std(myints, myints + sizeof(myints) / sizeof(int));

	ft::Vector<int>::reverse_iterator it = ft.rbegin() + 1;
	std::vector<int>::reverse_iterator itSTL = std.rbegin() + 1;

	assertEqual(*it, *itSTL, "reverse .first()");
	it += 1;
	itSTL += 1;
	assertEqual(*it, *itSTL, "reverse operator +=");
	it -= 1;
	itSTL -= 1;
	assertEqual(*it, *itSTL, "reverse operator -=");
	assertEqual(*it++, *itSTL++, "reverse operator++");
	assertEqual(*++it, *++itSTL, "reverse ++operator");
	assertEqual(*it--, *itSTL--, "reverse --operator");
	assertEqual(*--it, *--itSTL, "reverse operator--");
	assertEqual(*(it - 1), *(itSTL - 1), "reverse operator-");
	assertEqual(*(it + 1), *(itSTL + 1), "reverse operator+");
	it = ft.rend();
	itSTL = std.rend();
	assertEqual(*--it, *--itSTL, "reverse .end()");
}

static void testReverseOperator() {
	int myints[] = {2,77,177,68, 42, 277};
	ft::Vector<int> ft(myints, myints + sizeof(myints) / sizeof(int));
	std::vector<int> std(myints, myints + sizeof(myints) / sizeof(int));

	ft::Vector<int>::reverse_iterator it = ft.rbegin();
	std::vector<int>::reverse_iterator itSTL = std.rbegin();
	assertEqual(it[0], itSTL[0], "reverse operator[] 0");
	assertEqual(it[2], itSTL[2], "reverse operator[] 2");
}

void testVectorIterator() {
	std::cout << "\033[1;37m                           >> VECTOR ITERATORS <<                            \033[0m" << std::endl;
	testIncrDecr();
	testOperator();
	testReverseIncrDecr();
	testReverseOperator();
	testComparaisonOperator();
	testReverseComparaisonOperator();
}
