#include "../Helpers/Tests.hpp"
#include "Stack.hpp"
#include <stack>
#include "../Vector/Vector.hpp"
#include "../List/List.hpp"

static void testPop() {
	ft::List<int> list;
	ft::List<int> list2;
	list.push_back(2);
	list2.push_back(2);
	list.push_back(1);
	list2.push_back(1);
	ft::Stack<int, ft::List<int> > ft (list);
	std::stack<int,ft::List<int> > STL (list2);
	ft.pop();
	STL.pop();

	assertEqual(ft.top(), STL.top(), ".pop()");
}

static void testPush() {
	ft::List<int> list;
	ft::List<int> list2;

	list.push_back(2);
	list2.push_back(2);
	ft::Stack<int, ft::List<int> > ft (list);
	std::stack<int,ft::List<int> > STL (list2);
	ft.push(1);
	STL.push(1);

	assertEqual(ft.top(), STL.top(), ".push()");
}

static void testTop() {
	ft::Vector<int> vector;
	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);

	ft::Stack<int, ft::Vector<int> > ft (vector);
	std::stack<int,ft::Vector<int> > STL (vector);

	assertEqual(ft.top(), STL.top(), ".top()");
}

static void testSize() {
	ft::Vector<int> vector(static_cast<ft::Vector<int>::size_type>(3), 100);

	ft::Stack<int, ft::Vector<int> > ft (vector);
	std::stack<int,ft::Vector<int> > STL (vector);
	assertEqual(ft.size(), STL.size(), ".size() vector");
}

static void testConstructors() {
	ft::Vector<int> vector(static_cast<size_t>(3), 100);

	std::stack<int,ft::Vector<int> > thirdSTL;
	ft::Stack<int,ft::Vector<int> > third;

	ft::Stack<int, ft::Vector<int> > fourth (vector);
	std::stack<int,ft::Vector<int> > fourthSTL (vector);

	assertEqual(third.size(), thirdSTL.size(), ".constructors() empty size 0");
}

static void testOperators() {
	ft::Vector<int> vector(static_cast<size_t>(3), 100);
	ft::Vector<int> vector2(static_cast<size_t>(5), 100);

	ft::Stack<int, ft::Vector<int> > ft (vector);
	std::stack<int,ft::Vector<int> > STL (vector);

	ft::Stack<int, ft::Vector<int> > ft2 (vector2);
	std::stack<int,ft::Vector<int> > STL2 (vector2);

	assertEqual((ft == ft2), (STL == STL2), "operator==");
	assertEqual((ft != ft2), (STL != STL2), "operator!=");
	assertEqual((ft < ft2), (STL < STL2), "operator<");
	assertEqual((ft <= ft2), (STL <= STL2), "operator<=");
	assertEqual((ft > ft2), (STL > STL2), "operator>");
	assertEqual((ft >= ft2), (STL >= STL2), "operator>=");

}

static void testEmpty() {
	ft::List<int> list;

	ft::Stack<int, ft::List<int> > ft (list);
	std::stack<int,ft::List<int> > STL (list);

	assertEqual(ft.empty(), STL.empty(), ".empty()");
}

void testStack() {
	std::cout << "\033[1;37m                           >> STACK <<                            \033[0m" << std::endl;
	testEmpty();
	testConstructors();
	testSize();
	testTop();
	testPush();
	testPop();
	testOperators();
}