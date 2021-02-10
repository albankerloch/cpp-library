#include "../Helpers/Tests.hpp"
#include "Vector.hpp"
#include <vector>

template <typename T>
void printVectors(const ft::Vector<T> *ft, const std::vector<T> *std) {
	std::cout << "FT: ";
	for (typename ft::Vector<T>::iterator it = ft->begin(); it != ft->end(); it++) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl << "STD: ";
	for (typename std::vector<T>::const_iterator it = std->begin(); it != std->end(); it++) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
}

template <typename T>
bool assertVectorEquals(ft::Vector<T> *ft, std::vector<T> *std, const std::string &testName) {
	incrTestTotal();
	if (ft->size() != std->size()){
		std::cout << "\033[1;31mFail\033[0m: > "<< testName << " > Expecting size to be equal: STL " << std->size() << " got FT " << ft->size() << std::endl;
		return false;
	}

	typename std::vector<T>::iterator itSTL = std->begin();
	size_t i(0);
	for (typename ft::Vector<T>::iterator it = ft->begin(); it != ft->end(); it++) {

		if (*it != *itSTL){
			std::cout << "\033[1;31mFail\033[0m: > "<< testName << " > Expecting " << *itSTL << " at pos "<< i++ << " got " << *it << std::endl;
			return false;
		}
		itSTL++;
	}
	std::cout << "\033[1;32mSuccess\033[0m > " << testName << " > AssertVectorEquals" << std::endl;
	incrTestSuccess();
	return true;
}

static void testConstructors() {
	ft::Vector<int> first;
	std::vector<int> firstSTL;
	assertVectorEquals(&first, &firstSTL, "constructors first");

	ft::Vector<int> second (static_cast<ft::Vector<int>::size_type>(4),100);
	std::vector<int> secondSTL (4,100);
	assertVectorEquals(&second, &secondSTL, "constructors second");

	ft::Vector<int> third (second.begin(),second.end());
	std::vector<int> thirdSTL (secondSTL.begin(),secondSTL.end());
	assertVectorEquals(&third, &thirdSTL, "constructors third");

	ft::Vector<int> fourth (third);
	std::vector<int> fourthSTL (thirdSTL);
	assertVectorEquals(&fourth, &fourthSTL, "constructors fourth");
}

static void testOperators() {
	ft::Vector<int> first;
	std::vector<int> firstSTL;
	ft::Vector<int> second (static_cast<ft::Vector<int>::size_type>(4),100);
	std::vector<int> secondSTL (4,100);
	first = second;
	firstSTL = secondSTL;
	assertVectorEquals(&first, &firstSTL, "operator= first");
}

static void testBeginEnd() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;
	assertPTREqual(order.begin(), order.end(), ".begin() empty");

	for (int i=1; i<=5; i++) order.push_back(i);
	for (int i=1; i<=5; i++) orderSTL.push_back(i);
	ft::Vector<int>::iterator it = order.begin();
	std::vector<int>::iterator itSTL = orderSTL.begin();
	assertEqual(*it, *itSTL, ".begin()");
	it = --order.end();
	itSTL = --orderSTL.end();
	assertEqual(*it, *itSTL, ".end()");

	const ft::Vector<int> const_order(order.begin(), order.end());
	const std::vector<int> const_orderSTL(orderSTL.begin(), orderSTL.end());
	ft::Vector<int>::const_iterator const_it = const_order.begin();
	std::vector<int>::const_iterator const_itSTL = const_orderSTL.begin();
	assertEqual(*const_it, *const_itSTL, ".begin()");
	const_it = --const_order.end();
	const_itSTL = --const_orderSTL.end();
	assertEqual(*it, *itSTL, ".end()");
}

static void testRbeginRend() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;
	assertPTREqual(order.rbegin(), order.rend(), ".begin() empty");

	for (int i=1; i<=5; i++) order.push_back(i);
	for (int i=1; i<=5; i++) orderSTL.push_back(i);
	ft::Vector<int>::reverse_iterator it = order.rbegin();
	std::vector<int>::reverse_iterator itSTL = orderSTL.rbegin();
	assertEqual(*it, *itSTL, ".rbegin()");
	it = --order.rend();
	itSTL = --orderSTL.rend();
	assertEqual(*it, *itSTL, ".rend()");
}

static void testSize() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;
	assertEqual(order.size(), orderSTL.size(), ".size() empty");
	assertEqual(order.capacity(), orderSTL.capacity(), ".capacity() empty");
	assertEqual(order.max_size(), orderSTL.max_size(), ".max_size() empty");

	for (int i=1; i<=5; i++) order.push_back(i);
	for (int i=1; i<=5; i++) orderSTL.push_back(i);
	assertEqual(order.size(), orderSTL.size(), ".size() 5");
	assertEqual(order.capacity(), orderSTL.capacity(), ".capacity() 5");
	assertEqual(order.max_size(), orderSTL.max_size(), ".max_size() 5");
}

static void testResize() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;
	for (int i=1; i<=10; i++) order.push_back(i);
	for (int i=1; i<=10; i++) orderSTL.push_back(i);

	order.resize(5);
	orderSTL.resize(5);
	assertVectorEquals(&order, &orderSTL, ".resize() 10 > 5");
	order.resize(25);
	orderSTL.resize(25);
	assertVectorEquals(&order, &orderSTL, ".resize() 5 > 25");

}
static void testEmpty() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;
	assertEqual(order.empty(), orderSTL.empty(), ".empty()");
	for (int i=1; i<=5; i++) order.push_back(i);
	for (int i=1; i<=5; i++) orderSTL.push_back(i);
	assertEqual(order.empty(), orderSTL.empty(), ".empty() not empty");
}

static void testReserve() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;

	order.reserve(10);
	orderSTL.reserve(10);
	assertEqual(order.capacity(), orderSTL.capacity(), ".reserve()");
	for (int i=1; i<=5; i++) order.push_back(i);
	for (int i=1; i<=5; i++) orderSTL.push_back(i);
	assertEqual(order.capacity(), orderSTL.capacity(), ".reserve() nothing changed");
}

static void testBrackets() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;
	for (int i=1; i<=5; i++) order.push_back(i);
	for (int i=1; i<=5; i++) orderSTL.push_back(i);

	assertEqual(order[0], orderSTL[0], "operator[] 0");
	assertEqual(order[4], orderSTL[4], "operator[] 4");
}

static void testAt() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;
	for (int i=1; i<=5; i++) order.push_back(i);
	for (int i=1; i<=5; i++) orderSTL.push_back(i);

	assertEqual(order.at(0), orderSTL.at(0), ".at() 0");
	assertEqual(order.at(4), orderSTL.at(4), ".at() 4");
	incrTestTotal();
	try {
		order.at(5);
		std::cout << "\033[1;31mFail\033[0m: > Expecting an exception for at() out_of_range" << std::endl;
	} catch (std::out_of_range &oor) {
		incrTestSuccess();
		std::cout << "\033[1;32mSuccess\033[0m > Got an exception as expected "<< std::endl;
	}
}

static void testFrontBack() {
	ft::Vector<int> order;
	std::vector<int> orderSTL;
	order.push_back(4);
	orderSTL.push_back(4);
	assertEqual(order.front(), orderSTL.front(), ".front() single");
	assertEqual(order.back(), orderSTL.back(), ".back() single");

	for (int i=1; i<=5; i++) order.push_back(i);
	for (int i=1; i<=5; i++) orderSTL.push_back(i);
	assertEqual(order.front(), orderSTL.front(), ".front()");
	assertEqual(order.back(), orderSTL.back(), ".back()");
}

static void testAssign() {
	std::vector<int> firstSTL;
	ft::Vector<int> first;
	std::vector<int> secondSTL;
	ft::Vector<int> second;
	std::vector<int> thirdSTL;
	ft::Vector<int> third;

	first.assign(static_cast<ft::Vector<int>::size_type>(7), 100);
	firstSTL.assign(7, 100);
	assertVectorEquals(&first, &firstSTL, ".assign() size_type n, const value_type& val");

	ft::Vector<int>::iterator it;
	std::vector<int>::iterator itSTL;
	it = first.begin() + 1;
	itSTL = firstSTL.begin() + 1;
	second.assign(it, first.end() - 1);
	secondSTL.assign(itSTL, firstSTL.end() - 1);
	assertVectorEquals(&second, &secondSTL, ".assign() InputIterator first, InputIterator last");

	int myints[] = {1776,7,4};
	third.assign(myints, myints+3);
	thirdSTL.assign(myints, myints+3);
	assertVectorEquals(&third, &thirdSTL, ".assign() myints");
	third.assign(myints, myints+3);
	thirdSTL.assign(myints, myints+3);
	assertVectorEquals(&third, &thirdSTL, ".assign() myints twice");
}

void static testPushPop() {
	std::vector<int> firstSTL;
	ft::Vector<int> first;

	first.push_back(42);
	first.push_back(21);
	firstSTL.push_back(42);
	firstSTL.push_back(21);
	assertVectorEquals(&first, &firstSTL, ".push_back()");
	first.pop_back();
	firstSTL.pop_back();
	assertVectorEquals(&first, &firstSTL, ".pop_back()");
	first.pop_back();
	firstSTL.pop_back();
	assertVectorEquals(&first, &firstSTL, ".pop_back() again");
}

static void testInsert() {
	ft::Vector<int> myvector;
	ft::Vector<int>::iterator it;
	std::vector<int> myvectorSTL;
	std::vector<int>::iterator itSTL;
	for (int i=1; i<=5; i++) myvector.push_back(i);
	for (int i=1; i<=5; i++) myvectorSTL.push_back(i);
	it = myvector.begin();
	it = myvector.insert(it, 200);
	itSTL = myvectorSTL.begin();
	itSTL = myvectorSTL.insert(itSTL, 200);
	assertEqual(*it, *itSTL, ".insert() iterator position, const value_type& val");
	assertVectorEquals(&myvector, &myvectorSTL, ".insert() iterator position, const value_type& val");

	it = myvector.begin();
	itSTL = myvectorSTL.begin();
	ft::Vector<int> anothervector (static_cast<ft::Vector<int>::size_type >(2), 400);
	std::vector<int> anothervectorSTL (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());
	myvectorSTL.insert (itSTL +2,anothervectorSTL.begin(),anothervectorSTL.end());
	assertVectorEquals(&myvector, &myvectorSTL, ".insert() InputIterator first, InputIterator last");

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);
	myvectorSTL.insert (myvectorSTL.begin(), myarray, myarray+3);
	assertVectorEquals(&myvector, &myvectorSTL, ".insert() at the beginning");
	myvector.insert (myvector.begin() + 3, myarray, myarray+3);
	myvectorSTL.insert (myvectorSTL.begin() + 3, myarray, myarray+3);
	assertVectorEquals(&myvector, &myvectorSTL, ".insert() middle");
	myvector.insert (myvector.end(), myarray, myarray+3);
	myvectorSTL.insert (myvectorSTL.end(), myarray, myarray+3);
	assertVectorEquals(&myvector, &myvectorSTL, ".insert() at the end");

	myvector.insert(myvector.begin(), static_cast<ft::Vector<int>::size_type>(20), 5);
	myvectorSTL.insert(myvectorSTL.begin(), 20, 5);
	assertVectorEquals(&myvector, &myvectorSTL, ".insert() iterator position, size_type n, const value_type& val");

	myvector.clear();
	myvectorSTL.clear();
	myvector.insert(myvector.begin(), static_cast<ft::Vector<int>::size_type>(20), 5);
	myvectorSTL.insert(myvectorSTL.begin(), 20, 5);
	assertVectorEquals(&myvector, &myvectorSTL, ".insert() after clear");
}

static void testErase() {
	std::vector<int> myvectorSTL;
	ft::Vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);
	for (int i=1; i<=5; i++) myvectorSTL.push_back(i);


	ft::Vector<int>::iterator it;
	std::vector<int>::iterator itSTL;

	it = myvector.erase(myvector.begin());
	itSTL = myvectorSTL.erase(myvectorSTL.begin());
	assertEqual(*it, *itSTL, ".erase() iterator");
	assertVectorEquals(&myvector, &myvectorSTL, ".erase() begin");

	it = myvector.erase(myvector.begin() + 2);
	itSTL = myvectorSTL.erase(myvectorSTL.begin() + 2);
	assertEqual(*it, *itSTL , ".erase() iterator");
	assertVectorEquals(&myvector, &myvectorSTL, ".erase() middle");

	it = myvector.erase(myvector.end() - 1);
	itSTL = myvectorSTL.erase(myvectorSTL.end() - 1);
	assertEqual(*it, *itSTL , ".erase() iterator");
	assertVectorEquals(&myvector, &myvectorSTL, ".erase() end2");

	/*	myvector.erase(myvector.end() - 1);
	myvectorSTL.erase(myvectorSTL.end() - 1);
	assertVectorEquals(&myvector, &myvectorSTL, ".erase() end");
	*/
	for (int i=1; i<=50; i++) myvector.push_back(i);
	for (int i=1; i<=50; i++) myvectorSTL.push_back(i);
	it = myvector.erase(myvector.begin() + 5, myvector.end() - 3);
	itSTL = myvectorSTL.erase(myvectorSTL.begin() + 5, myvectorSTL.end() - 3);
	assertEqual(*it, *itSTL , ".erase() iterator");
	assertVectorEquals(&myvector, &myvectorSTL, ".erase() iterator first, iterator last");
}

static void testSwap() {
	ft::Vector<int> second (static_cast<ft::Vector<int>::size_type>(4),100);
	std::vector<int> secondSTL (4,100);

	ft::Vector<int> first (static_cast<ft::Vector<int>::size_type>(5),40);
	std::vector<int> firstSTL (5,40);

	first.swap(second);
	firstSTL.swap(secondSTL);
	assertVectorEquals(&first, &firstSTL, ".swap() first");
	assertVectorEquals(&second, &secondSTL, ".swap() second");
	swap(first, second);
	swap(firstSTL, secondSTL);
	assertVectorEquals(&first, &firstSTL, "swap() first");
	assertVectorEquals(&second, &secondSTL, "swap() second");
}

static void testClear() {
	ft::Vector<int> first (static_cast<ft::Vector<int>::size_type>(5),40);
	std::vector<int> firstSTL (5,40);

	first.clear();
	firstSTL.clear();
	assertVectorEquals(&first, &firstSTL, ".clear() first");
	first.push_back(40);
	firstSTL.push_back(40);
	assertVectorEquals(&first, &firstSTL, ".clear() add values again");
}

static void testRelationalOperator(){
	int myints[] = {2,77,177,277,377, 20,57,77,100,200};
	int myints2[] = {2,77,177,277,377, 20,57,77};

	ft::Vector<int> order(myints, myints + sizeof(myints) / sizeof(int));
	ft::Vector<int> order2(myints2, myints2 + sizeof(myints2) / sizeof(int));
	ft::Vector<int> order3(myints, myints + sizeof(myints2) / sizeof(int));
	std::vector<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));
	std::vector<int> order2STL(myints2, myints2 + sizeof(myints2) / sizeof(int));
	std::vector<int> order3STL(myints2, myints2 + sizeof(myints2) / sizeof(int));

	assertEqual((order == order2), (orderSTL == order2STL), "operator==");
	assertEqual((order == order3), (orderSTL == order3STL), "operator==");
	assertEqual((order != order2), (orderSTL != order2STL), "operator!=");
	assertEqual((order != order3), (orderSTL != order3STL), "operator!=");
	assertEqual((order < order2), (orderSTL < order2STL), "operator<");
	assertEqual((order < order3), (orderSTL < order3STL), "operator<");
	assertEqual((order <= order2), (orderSTL <= order2STL), "operator<=");
	assertEqual((order <= order3), (orderSTL <= order3STL), "operator<=");
	assertEqual((order > order2), (orderSTL > order2STL), "operator>");
	assertEqual((order > order3), (orderSTL > order3STL), "operator>");
	assertEqual((order >= order2), (orderSTL >= order2STL), "operator<=");
	assertEqual((order >= order3), (orderSTL >= order3STL), "operator<=");
}

void testVector() {
	std::cout << "\033[1;37m                           >> VECTOR <<                            \033[0m" << std::endl;
	testConstructors();
	testOperators();
	testBeginEnd();
	testRbeginRend();
	testSize();
	testResize();
	testEmpty();
	testReserve();
	testBrackets();
	testAt();
	testFrontBack();
	testAssign();
	testPushPop();
	testInsert();
	testErase();
	testSwap();
	testClear();
	testRelationalOperator();
}
