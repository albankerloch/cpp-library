#include "Helpers/Tests.hpp"

extern void testList();
extern void testListIterator();
extern void testVector();
extern void testMap();
extern void testMapIterator();
extern void testVectorIterator();
extern void testStack();
extern void testQueue();

int g_success = 0;
int g_total = 0;

int main() {
	testList();
	testListIterator();
	testVector();
	testVectorIterator();
	testMap();
	testMapIterator();
	testStack();
	testQueue();
	printTestsResult();
	return 0;
}

