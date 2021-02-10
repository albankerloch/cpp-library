#include "../Helpers/Tests.hpp"
#include "Queue.hpp"
#include <queue>
#include "../Vector/Vector.hpp"
#include "../List/List.hpp"

static void testEmpty() {
	ft::List<int> list;

	ft::Queue<int, ft::List<int> > ft (list);
	std::queue<int,ft::List<int> > STL (list);

	assertEqual(ft.empty(), STL.empty(), ".empty()");
}

static void testPop() {
	ft::List<int> list;
	ft::List<int> list2;
	list.push_back(2);
	list2.push_back(2);
	list.push_back(1);
	list2.push_back(1);
	ft::Queue<int, ft::List<int> > ft (list);
	std::queue<int,ft::List<int> > STL (list2);
	ft.pop();
	STL.pop();

	assertEqual(ft.front(), STL.front(), ".pop()");
}

static void testPush() {
	ft::List<int> list;
	ft::List<int> list2;

	list.push_back(2);
	list2.push_back(2);
	ft::Queue<int, ft::List<int> > ft (list);
	std::queue<int,ft::List<int> > STL (list2);
	ft.push(1);
	STL.push(1);

	assertEqual(ft.front(), STL.front(), ".push()");
}

static void testFrontBack() {
	ft::Vector<int> vector;
	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);

	ft::Queue<int, ft::Vector<int> > ft (vector);
	std::queue<int,ft::Vector<int> > STL (vector);

	assertEqual(ft.front(), STL.front(), ".front()");
	assertEqual(ft.back(), STL.back(), ".back()");
}

static void testSize() {
	ft::Vector<int> vector(static_cast<ft::Vector<int>::size_type>(3), 100);

	ft::Queue<int, ft::Vector<int> > ft (vector);
	std::queue<int,ft::Vector<int> > STL (vector);
	assertEqual(ft.size(), STL.size(), ".size() vector");
}

static void testConstructors() {
	ft::Vector<int> vector(static_cast<size_t>(3), 100);

	std::queue<int,ft::Vector<int> > thirdSTL;
	ft::Queue<int,ft::Vector<int> > third;

	ft::Queue<int, ft::Vector<int> > fourth (vector);
	std::queue<int,ft::Vector<int> > fourthSTL (vector);

	assertEqual(third.size(), thirdSTL.size(), ".constructors() empty size 0");
	assertEqual(fourth.size(), fourthSTL.size(), ".constructors() vector size > 0");
}

static void testOperators() {
	ft::Vector<int> vector(static_cast<size_t>(3), 100);
	ft::Vector<int> vector2(static_cast<size_t>(5), 100);

	ft::Queue<int, ft::Vector<int> > ft (vector);
	std::queue<int,ft::Vector<int> > STL (vector);

	ft::Queue<int, ft::Vector<int> > ft2 (vector2);
	std::queue<int,ft::Vector<int> > STL2 (vector2);

	assertEqual((ft == ft2), (STL == STL2), "operator==");
	assertEqual((ft != ft2), (STL != STL2), "operator!=");
	assertEqual((ft < ft2), (STL < STL2), "operator<");
	assertEqual((ft <= ft2), (STL <= STL2), "operator<=");
	assertEqual((ft > ft2), (STL > STL2), "operator>");
	assertEqual((ft >= ft2), (STL >= STL2), "operator>=");

}

void testQueue() {
	std::cout << "\033[1;37m                           >> QUEUE <<                            \033[0m" << std::endl;
	testEmpty();
	testConstructors();
	testSize();
	testFrontBack();
	testPush();
	testPop();
	testOperators();
}