#include <iostream>
#include <list>
#include "List.hpp"
#include "../Helpers/Tests.hpp"

template <typename T>
void printList(const ft::List<T> *ft, const std::list<T> *std) {
	std::cout << "FT: ";
	for (typename ft::List<T>::const_iterator it = ft->begin(); it != ft->end(); it++) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl << "STD: ";
	for (typename std::list<T>::const_iterator it = std->begin(); it != std->end(); it++) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
}

template <typename T>
bool assertListEquals(ft::List<T> *ft, std::list<T> *std, const std::string &testName) {
	incrTestTotal();
	if (ft->size() != std->size()){
		std::cout << "\033[1;31mFail\033[0m: > "<< testName << " > Expecting size to be equal " << std->size() << " got " << ft->size() << std::endl;
		printList(ft, std);
		return false;
	}
	typename std::list<T>::iterator itSTL = std->begin();
	size_t i(0);
	for (typename ft::List<T>::iterator it = ft->begin(); it != ft->end(); it++) {

		if (*it != *itSTL){
			std::cout << "\033[1;31mFail\033[0m: > "<< testName << " > Expecting " << *itSTL << " at pos "<< i << " got " << *it << std::endl;
			return false;
		}
		++i;
		++itSTL;
	}
	std::cout << "\033[1;32mSuccess\033[0m > " << testName << " > Lists content are equal" << std::endl;
	incrTestSuccess();
	return true;
}

template <typename T>
bool assertSizeIsNot0(ft::List<T> *ft, const std::string &testName){
	g_total++;
	if (ft->size() == 0 ){
		std::cout << "\033[1;31mFail\033[0m: > "<< testName << " > Expecting more than 0 got "<< ft->size() << std::endl;
		return false;
	}
	g_success++;
	return true;
}

void testConstructors() {
	ft::List<int> first;
	ft::List<int> second (static_cast<ft::List<int>::size_type>(200), 40);
	std::list<int> secondSTL (static_cast<ft::List<int>::size_type>(200), 40);
	assertListEquals(&second, &secondSTL, "second constructor");

	ft::List<int> third (second.begin(),second.end());
	std::list<int> thirdSTL (secondSTL.begin(), secondSTL.end());
	assertListEquals(&third, &thirdSTL, "third constructor");

	ft::List<int> fourth (third);
  	std::list<int> fourthSTL (thirdSTL);
	assertListEquals(&third, &thirdSTL, "fourth constructor");

  	int myints[] = {16,2,77,29};
  	ft::List<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
  	std::list<int> fifthSTL (myints, myints + sizeof(myints) / sizeof(int) );
	assertListEquals(&fifth, &fifthSTL, "fifth constructor");
}

void testOperators() {
	int myints[] = {16,2,77,29};

	ft::List<int> empty;
	ft::List<int> full(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> emptySTL;
	std::list<int> fullSTL(myints, myints + sizeof(myints) / sizeof(int));

	empty = full;
	emptySTL = fullSTL;
	assertSizeIsNot0(&empty, "operator=");
	assertListEquals(&empty, &emptySTL, "operator=");
}

void testSize() {
	int myints[] = {16,2,77,29};
	ft::List<int> second (static_cast<ft::List<int>::size_type>(200), 40);
	std::list<int> secondSTL (static_cast<ft::List<int>::size_type>(200), 40);

	ft::List<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
	std::list<int> fifthSTL (myints, myints + sizeof(myints) / sizeof(int) );

	assertEqual(second.empty(), secondSTL.empty(), ".empty() not empty");
	assertEqual(second.size(), secondSTL.size(), ".size() second");
	assertEqual(second.max_size(), secondSTL.max_size(), ".max_size() second");
	assertEqual(second.size(), secondSTL.size(), ".size() fifth");
	assertEqual(fifth.max_size(), fifthSTL.max_size(), ".max_size() second");
	second.clear();
	secondSTL.clear();
	assertEqual(second.empty(), secondSTL.empty(), ".empty() empty");
}

void testFrontBack() {
	int myints[] = {16,2,77,29};
	ft::List<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
	std::list<int> fifthSTL (myints, myints + sizeof(myints) / sizeof(int) );

	assertEqual(fifth.front(), fifthSTL.front(), ".front()");
	assertEqual(fifth.back(), fifthSTL.back(), ".back()");
}

void testAssign() {
	ft::List<int> first;
	std::list<int>  firstSTL;
	int myints[] = {16,2,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int> second;
	std::list<int>  secondSTL;

	firstSTL.assign (7,100);
	first.assign (static_cast<ft::List<int>::size_type>(7),static_cast<int>(100));
	assertListEquals(&first, &firstSTL, ".assign() first");
	second.assign (order.begin(),order.end());
	secondSTL.assign (orderSTL.begin(), orderSTL.end());
	assertListEquals(&second, &secondSTL, ".assign() order");
}

void testPush() {
	std::list<int> mylistSTL (2,100);
	ft::List<int> mylist (static_cast<ft::List<int>::size_type>(2),100);

	mylist.push_front (200);
	mylist.push_front (300);
	mylistSTL.push_front (200);
	mylistSTL.push_front (300);
	assertListEquals(&mylist, &mylistSTL, ".push_front()");

	mylist.push_back (200);
	mylist.push_back (300);
	mylistSTL.push_back (200);
	mylistSTL.push_back (300);
	assertListEquals(&mylist, &mylistSTL, ".push_back()");
}

void testPop() {
	int myints[] = {16,2,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));

	order.pop_front();
	orderSTL.pop_front();
	assertListEquals(&order, &orderSTL, ".pop_front()");

	order.pop_back();
	orderSTL.pop_back();
	assertListEquals(&order, &orderSTL, ".pop_back()");
}

void testInsert() {
	int myints[] = {16,2,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> rangeSTL(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int> range(myints, myints + sizeof(myints) / sizeof(int));

	std::list<int>::iterator itSTL;
	ft::List<int>::iterator it;

	it = order.begin();
	itSTL = orderSTL.begin();
	order.insert(it, 5);
	orderSTL.insert(itSTL, 5);
	assertListEquals(&order, &orderSTL, ".insert() &val push_front");

	itSTL++;
	it++;
	it = order.insert(it, 10);
	itSTL = orderSTL.insert(itSTL, 10);
	assertListEquals(&order, &orderSTL, ".insert() &val pos 2");

	order.insert(order.end(), 42);
	orderSTL.insert(orderSTL.end(), 42);
	assertListEquals(&order, &orderSTL, ".insert() &val push_back");

	order.insert(it,static_cast<ft::List<int>::size_type>(2),20);
	orderSTL.insert(itSTL,2,20);
	assertListEquals(&order, &orderSTL, ".insert() size_type n, &val ");

	order.insert(it, range.begin(), range.end());
	orderSTL.insert(itSTL, rangeSTL.begin(), rangeSTL.end());
	assertListEquals(&order, &orderSTL, ".insert() InputIterator");
}

void testErase() {
	int myints[] = {16,2,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int>::iterator itSTL;
	ft::List<int>::iterator it;

	it = order.begin();
	itSTL = orderSTL.begin();

	it = order.erase(it);
	itSTL = orderSTL.erase(itSTL);
	assertListEquals(&order, &orderSTL, ".erase() iterator pop_front");

	it++;
	itSTL++;
	order.erase(it);
	orderSTL.erase(itSTL);
	assertListEquals(&order, &orderSTL, ".erase() iterator pos 2");

	it = order.erase(--order.end());
	itSTL = orderSTL.erase(--orderSTL.end());
	assertListEquals(&order, &orderSTL, ".erase() iterator pop_back");

	order.erase(order.begin(), it);
	orderSTL.erase(orderSTL.begin(), itSTL);
	assertListEquals(&order, &orderSTL, ".erase() iterator range");
}

void testSwap() {
	ft::List<int> first (static_cast<ft::List<int>::size_type>(3),100);
	ft::List<int> second (static_cast<ft::List<int>::size_type>(5),200);
	std::list<int> firstSTL (3,100);
	std::list<int> secondSTL (5,200);

	first.swap(second);
	firstSTL.swap(secondSTL);
	assertListEquals(&first, &firstSTL, ".swap() first");
	assertListEquals(&second, &secondSTL, ".swap() second");
}

void testResize() {
	int myints[] = {16,2,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));

	order.resize(4);
	orderSTL.resize(4);
	assertListEquals(&order, &orderSTL, ".resize() 4 == 4");

	order.resize(5);
	orderSTL.resize(5);
	assertListEquals(&order, &orderSTL, ".resize() 4 < 5");

	order.resize(2);
	orderSTL.resize(2);
	assertListEquals(&order, &orderSTL, ".resize() 5 > 2");

	order.resize(8, 100);
	orderSTL.resize(8, 100);
	assertListEquals(&order, &orderSTL, ".resize() size n, &val");
}

void testClear() {
	int myints[] = {16,2,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));

	order.clear();
	orderSTL.clear();
	assertListEquals(&order, &orderSTL, ".clear()");
}

void testSplice() {
	int myints[] = {16,2,77,29};
	int myints2[] = {10,32,54,42};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int> splice(myints2, myints2 + sizeof(myints) / sizeof(int));
	std::list<int> spliceSTL(myints2, myints2 + sizeof(myints) / sizeof(int));
	std::list<int>::iterator itSTL;
	ft::List<int>::iterator it;

	it = ++order.begin();
	itSTL = ++orderSTL.begin();

	order.splice(it, splice, ++splice.begin());
	orderSTL.splice(itSTL, spliceSTL, ++spliceSTL.begin());
	assertListEquals(&order, &orderSTL, ".splice() iterator position, list& x, iterator i");
	assertListEquals(&splice, &spliceSTL, ".splice() single removal");

	order.splice(++it, splice);
	orderSTL.splice(++itSTL, spliceSTL);
	assertListEquals(&order, &orderSTL, ".splice() iterator position, list& x");
	assertListEquals(&splice, &spliceSTL, ".splice() removal");
}

void testRemove() {
	int myints[] = {16,2,77,77,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));

	order.remove(77);
	orderSTL.remove(77);
	assertListEquals(&order, &orderSTL, ".remove() existing value");
	order.remove(77);
	orderSTL.remove(77);
	assertListEquals(&order, &orderSTL, ".remove() non existing value");
	order.remove(16);
	orderSTL.remove(16);
	order.remove(2);
	orderSTL.remove(2);
	order.remove(29);
	orderSTL.remove(29);
	assertListEquals(&order, &orderSTL, ".remove() everything else");
}

struct is_odd {
	bool operator() (const int& value) { return (value%2)==1; }
};

void testRemoveIf() {
	int myints[] = {16,2,77,77,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));

	order.remove_if(is_odd());
	orderSTL.remove_if(is_odd());
	assertListEquals(&order, &orderSTL, ".remove_if() is_odd");
}

void testUnique() {
	int myints[] = {16,2,77,77,77,29};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));

	order.unique();
	orderSTL.unique();
	assertListEquals(&order, &orderSTL, ".unique()");
}

void testMerge() {
	int myints[] = {2,77,177,277,377};
	int myints2[] = {20,57,77,100,200};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int> merge(myints2, myints2 + sizeof(myints2) / sizeof(int));
	std::list<int> mergeSTL(myints2, myints2 + sizeof(myints2) / sizeof(int));

	order.merge(merge);
	orderSTL.merge(mergeSTL);
	assertListEquals(&order, &orderSTL, ".merge()");
	assertListEquals(&merge, &mergeSTL, ".merge() empty");
}

void testSort() {
	int myints[] = {2,77,77,177,277,377, 20,57,77,100,200};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));

	order.sort();
	orderSTL.sort();
	assertListEquals(&order, &orderSTL, ".sort()");
}

void testReverse() {
	int myints[] = {2,77,177,277,377, 20,57,77,100,200};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));

	order.reverse();
	orderSTL.reverse();
	assertListEquals(&order, &orderSTL, ".reverse()");
}

void testRelationalOperator(){
	int myints[] = {2,77,177,277,377, 20,57,77,100,200};
	int myints2[] = {2,77,177,277,377, 20,57,77};

	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int> order2(myints2, myints2 + sizeof(myints2) / sizeof(int));
	ft::List<int> order3(myints, myints + sizeof(myints2) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> order2STL(myints2, myints2 + sizeof(myints2) / sizeof(int));
	std::list<int> order3STL(myints2, myints2 + sizeof(myints2) / sizeof(int));

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

void testSwapList() {
	int myints[] = {2,7,177,277,87,20,57,77,100};
	int myints2[] = {12,77,177,27,377,20,57,77};
	ft::List<int> order(myints, myints + sizeof(myints) / sizeof(int));
	ft::List<int> order2(myints2, myints2 + sizeof(myints2) / sizeof(int));
	std::list<int> orderSTL(myints, myints + sizeof(myints) / sizeof(int));
	std::list<int> order2STL(myints2, myints2 + sizeof(myints2) / sizeof(int));

	swap(order, order2);
	swap(orderSTL, order2STL);

	assertListEquals(&order, &orderSTL, "swap(List<T,Alloc>& x, list<T,Alloc>& y)");
	assertListEquals(&order2, &order2STL, "swap(List<T,Alloc>& x, list<T,Alloc>& y)");
}

void testList() {
	std::cout << "\033[1;37m                           >> LIST <<                            \033[0m" << std::endl;
	testConstructors();
	testOperators();
	testFrontBack();
	testAssign();
	testSize();
	testPush();
	testPop();
	testInsert();
	testErase();
	testSwap();
	testResize();
	testClear();
	testSplice();
	testRemove();
	testRemoveIf();
	testUnique();
	testMerge();
	testSort();
	testReverse();
	testRelationalOperator();
	testSwapList();
}
