#include "../Helpers/Tests.hpp"
#include "Map.hpp"
#include <map>


template<class Key, class T, class Compare>
static void printBST(const ft::Map<Key, T, Compare> *ft, const std::map<Key, T, Compare> *std){
	typename ft::Map<Key, T, Compare>::const_iterator it = ft->begin();
	typename std::map<Key, T, Compare>::const_iterator itSTL = std->begin();

	std::cout << "FT:" << std::endl;
	while (it != ft->end()) {
		std::cout << it->first << " : " << it->second << std::endl;
		++it;
	}
	std::cout << "STL:" << std::endl;
	while (itSTL != std->end()) {
		std::cout << itSTL->first << " : " << itSTL->second << std::endl;
		itSTL++;
	}
}

template<class Key, class T, class Compare>
static bool assertBSTEqual(const ft::Map<Key, T, Compare> *ft, std::map<Key, T, Compare> *std, const std::string &testName) {
	incrTestTotal();
	if (ft->size() != std->size()){
		std::cout << "\033[1;31mFail\033[0m: > "<< testName << " > Expecting size to be equal " << std->size() << " got " << ft->size() << std::endl;
		printBST(ft, std);
		return false;
	}
	typename ft::Map<Key, T, Compare>::size_type s = ft->size();
	typename ft::Map<Key, T, Compare>::const_iterator it = ft->begin();
	typename std::map<Key, T, Compare>::const_iterator itSTL = std->begin();
	while (it != ft->end()){
		--s;
		if ((*it).first != (*itSTL).first || (*it).second != (*itSTL).second){
			std::cout << "\033[1;31mFail\033[0m: > "<< testName << " > Expecting [" << (*itSTL).first << "]" << (*itSTL).second << " got [" << (*it).first << "]" << (*it).second << std::endl;
			return false;
		}
		++it;
		++itSTL;
	}
	if (s != 0) {
		std::cout << "\033[1;31mFail\033[0m: > " << testName << " > Only " << ft->size() - s << " elements were iterate expecting " << ft->size() << std::endl;
		printBST(ft, std);
		return false;
	}
	std::cout << "\033[1;32mSuccess\033[0m > " << testName << " > Map content are equal" << std::endl;
	incrTestSuccess();
	return true;

}

static void testInsert() {
	std::pair<ft::Map<char, int>::iterator, bool> ret;
	std::pair<std::map<char, int>::iterator, bool> retSTL;

	ft::Map<char, int> ft;
	ft.insert ( std::pair<char,int>('a',100));
	ret = ft.insert ( std::pair<char,int>('w',100));
	ft.insert ( std::pair<char,int>('p',200));
	ft.insert ( std::pair<char,int>('z',200));
	std::map<char, int> std;
	std.insert ( std::pair<char,int>('a',100));
	retSTL = std.insert ( std::pair<char,int>('w',100));
	std.insert ( std::pair<char,int>('p',200));
	std.insert ( std::pair<char,int>('z',200));
	assertEqual(ret.second, retSTL.second, ".insert() new key -> bool");
	assertEqual(ret.first->first, retSTL.first->first, ".insert() new key -> iterator");
	assertBSTEqual(&ft, &std, ".insert() const value_type& val");

	ret = ft.insert(std::pair<char, int>('p', 100));
	retSTL = std.insert(std::pair<char, int>('p', 100));
	assertEqual(ret.second, retSTL.second, ".insert() duplicate key -> bool");
	assertEqual(ret.first->first, retSTL.first->first, ".insert() duplicate key -> iterator");

	ft::Map<char, int>::iterator it;
	std::map<char, int>::iterator itSTL;
	it = ft.insert(ret.first, std::pair<char, int>('y', 400));
	itSTL = std.insert(retSTL.first, std::pair<char, int>('y', 400));
	assertEqual((*it).first, (*itSTL).first, ".insert() iterator");
	assertBSTEqual(&ft, &std, ".insert() iterator position, const value_type& val");
	it = ft.insert(ret.first, std::pair<char, int>('z', 400));
	itSTL = std.insert(retSTL.first, std::pair<char, int>('z', 400));
	assertEqual((*it).first, (*itSTL).first, ".insert() iterator failed insert");
	assertBSTEqual(&ft, &std, ".insert() iterator position, const value_type& val");

	std.insert (std::pair<char,int>('m',200));
	std.insert (std::pair<char,int>('u',200));
	ft.insert(std.begin(), std.end());
	std.insert(ft.begin(), ft.end());
	assertBSTEqual(&ft, &std, ".insert() InputIterator first, InputIterator last");
}
static void testEmpty() {
	std::map<char, int> std;
	ft::Map<char, int> ft;
	assertEqual(ft.empty(), std.empty(), ".empty() empty");
	ft.insert ( std::pair<char,int>('z',200));
	std.insert ( std::pair<char,int>('z',200));
	assertEqual(ft.empty(), std.empty(), ".empty() not empty");
}

static void testSize() {
	std::map<char, int> std;
	ft::Map<char, int> ft;
	assertEqual(ft.size(), std.size(), ".size() empty");
	ft.insert ( std::pair<char,int>('z',200));
	std.insert ( std::pair<char,int>('z',200));
	assertEqual(ft.size(), std.size(), ".size() not empty");
}

static void testMaxSize() {
	std::map<char, int> std;
	ft::Map<char, int> ft;

	assertEqual(ft.max_size(), std.max_size(), ".max_size()");
}

static void testOperatorBrackets() {
	std::map<char, int> std;
	ft::Map<char, int> ft;
	assertEqual(ft['u'], std['u'], "operator[] creating");
	assertBSTEqual(&ft, &std, "operator[] asserting u was created");
	ft.insert ( std::pair<char,int>('w',200));
	std.insert ( std::pair<char,int>('w',200));
	ft.insert ( std::pair<char,int>('z',300));
	std.insert ( std::pair<char,int>('z',300));
	ft.insert ( std::pair<char,int>('a',400));
	std.insert ( std::pair<char,int>('a',400));
	ft.insert ( std::pair<char,int>('p',500));
	std.insert ( std::pair<char,int>('p',500));
	ft.insert ( std::pair<char,int>('i',600));
	std.insert ( std::pair<char,int>('i',600));

	assertEqual(ft['i'], std['i'], "operator[] existing");
	assertEqual(ft['z'], std['z'], "operator[] another existing");
	assertEqual(ft['t'], std['t'], "operator[] creating t");
	assertBSTEqual(&ft, &std, "operator[] asserting t was created");
}

static void testErase() {
	ft::Map<char, int> ft;
	ft::Map<char, int>::iterator it;
	ft['a']=10;
	ft['b']=20;
	ft['c']=30;
	ft['d']=40;
	ft['e']=50;
	ft['f']=60;
	ft['g']=70;
	ft['z']=260;
	std::map<char, int> std;
	std::map<char, int>::iterator itSTL;
	std['a']=10;
	std['b']=20;
	std['c']=30;
	std['d']=40;
	std['e']=50;
	std['f']=60;
	std['g']=70;
	std['z']=260;

	it=ft.find('b');
	ft.erase(it);
	itSTL=std.find('b');
	std.erase(itSTL);
	assertBSTEqual(&ft, &std, ".erase() iterator position middle");

	ft.erase('a');
	std.erase('a');
	assertBSTEqual(&ft, &std, ".erase() first");
	ft.erase('f');
	std.erase('f');
	assertBSTEqual(&ft, &std, ".erase() last");
	ft.erase(ft.begin(), ft.end());
	std.erase(std.begin(), std.end());
	assertBSTEqual(&ft, &std, ".erase() iterator first, iterator last");
}

static void testSwap() {
	ft::Map<char, int> ft, ft2;
	ft['x']=100;
	ft['y']=200;
	ft2['a']=11;
	ft2['b']=22;
	ft2['c']=33;
	std::map<char, int> std, std2;
	std['x']=100;
	std['y']=200;
	std2['a']=11;
	std2['b']=22;
	std2['c']=33;
	ft.swap(ft2);
	std.swap(std2);
	assertBSTEqual(&ft, &std, ".swap() left");
	assertBSTEqual(&ft2, &std2, ".swap() right");
}
static void testClear() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x']=100;
	ft['y']=200;
	ft['a']=11;
	ft['b']=22;
	ft['c']=33;
	std['x']=100;
	std['y']=200;
	std['a']=11;
	std['b']=22;
	std['c']=33;
	ft.clear();
	std.clear();
	assertBSTEqual(&ft, &std, ".clear()");
	ft.clear();
	std.clear();
	assertBSTEqual(&ft, &std, ".clear() empty");
	ft['u']=100;
	ft['w']=200;
	ft['t']=11;
	std['u']=100;
	std['w']=200;
	std['t']=11;
	assertBSTEqual(&ft, &std, ".clear() add data after");
}

static void testBeginEnd() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	assertEqual((ft.begin() == ft.end()), (std.begin() == std.end()), "begin() & end() equal if empty");
}

static void testRbeginRend() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	assertEqual((ft.rbegin() == ft.rend()), (std.rbegin() == std.rend()), "rbegin() & rend() equal if empty");
	ft['x'] = 0;
	std['x'] = 0;
	assertEqual(ft.rbegin()->first, std.rbegin()->first, ".rbegin() val ");
	assertEqual((ft.rbegin() == ft.rend()), (std.rbegin() == std.rend()), "rbegin() & rend() not equal if not empty");
}
static void testKeyComp() {
	ft::Map<char,int> mymap;
	ft::Map<char,int>::key_compare mycomp = mymap.key_comp();
	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;
	mymap['m']=400;
	mymap['z']=500;

	ft::Map<char,int>::iterator it = mymap.begin();
	int i = 0;
	while ( mycomp((*it++).first, 'm')){
		i++;
	}
	assertEqual(i, 3, ".key_comp()");
}

static void testValueComp() {
	ft::Map<char,int> mymap;
	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	std::pair<char, int> highest = std::make_pair('z', 3003);
	ft::Map<char,int>::iterator it = mymap.begin();
	int i = 0;
	while ( mymap.value_comp()(*it++, highest)){
		i++;
	}
	assertEqual(i, 2, ".value_comp()");
}

static void testFind(){
	ft::Map<char, int> ft;
	std::map<char, int> std;
	assertEqual((ft.find('e') == ft.end()), (std.find('e') == std.end()),".find() empty");
	ft['x']=100;
	ft['y']=200;
	ft['a']=11;
	ft['b']=22;
	ft['c']=33;
	std['x']=100;
	std['y']=200;
	std['a']=11;
	std['b']=22;
	std['c']=33;
	assertEqual((*ft.find('x')).second,(*std.find('x')).second, ".find() existing");
	assertEqual((ft.find('e') == ft.end()), (std.find('e') == std.end()),".find() missing");
}

static void testCount() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	ft['x']=100;
	ft['y']=200;
	ft['a']=11;
	ft['b']=22;
	ft['c']=33;
	std['x']=100;
	std['y']=200;
	std['a']=11;
	std['b']=22;
	std['c']=33;
	assertEqual(ft.count('c'), std.count('c'), ".count() existing");
	assertEqual(ft.count('X'), std.count('X'), ".count() missing");
}

static void testLowerBound() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	assertEqual((ft.lower_bound('e') == ft.end()), (std.lower_bound('e') == std.end()), ".lower_bound() empty");
	ft['x']=100;
	ft['y']=200;
	ft['a']=11;
	ft['b']=22;
	ft['c']=33;
	std['x']=100;
	std['y']=200;
	std['a']=11;
	std['b']=22;
	std['c']=33;
	assertEqual((*ft.lower_bound('e')).first, (*std.lower_bound('e')).first, ".lower_bound() existing");
	assertEqual((*ft.lower_bound('x')).first, (*std.lower_bound('x')).first, ".lower_bound() existing equal");
	assertEqual((ft.lower_bound('z') == ft.end()), (std.lower_bound('z') == std.end()), ".lower_bound() out of bound");
}

static void testUpperBound() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	assertEqual((ft.upper_bound('e') == ft.end()), (std.upper_bound('e') == std.end()), ".upper_bound() empty");
	ft['x']=100;
	ft['y']=200;
	ft['a']=11;
	ft['b']=22;
	ft['c']=33;
	std['x']=100;
	std['y']=200;
	std['a']=11;
	std['b']=22;
	std['c']=33;
	assertEqual((*ft.upper_bound('e')).first, (*std.upper_bound('e')).first, ".upper_bound() existing");
	assertEqual((*ft.upper_bound('c')).first, (*std.upper_bound('c')).first, ".upper_bound() existing equal");
}

static void testEqualBound() {
	ft::Map<char, int> ft;
	std::map<char, int> std;
	std::pair<ft::Map<char, int>::iterator , ft::Map<char ,int>::iterator> it = ft.equal_range('e');
	std::pair<std::map<char, int>::iterator , std::map<char ,int>::iterator> itSTL = std.equal_range('e');
	assertEqual((it.first == ft.end()), (itSTL.first == std.end()), ".equal_range() empty begin");
	assertEqual((it.second == ft.end()), (itSTL.second == std.end()), ".equal_range() empty end");
	ft['x'] = 100;
	ft['y'] = 200;
	ft['a'] = 11;
	ft['b'] = 22;
	ft['c'] = 33;
	std['x'] = 100;
	std['y'] = 200;
	std['a'] = 11;
	std['b'] = 22;
	std['c'] = 33;
	it = ft.equal_range('e');
	itSTL = std.equal_range('e');
	assertEqual((*(it.first)).first, (*(itSTL.first)).first, ".equal_range() existing");
	assertEqual((it.second == ft.end()), (itSTL.second == std.end()), ".equal_range() existing end");
	it = ft.equal_range('b');
	itSTL = std.equal_range('b');
	assertEqual((*(it.first)).first, (*(itSTL.first)).first, ".equal_range() equal");
	assertEqual((it.second == ft.end()), (itSTL.second == std.end()), ".equal_range() equal end");
}

bool fncomp (char lhs, char rhs) {return lhs>rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs>rhs;}
};


static void testConstructors() {
	ft::Map<char,int> first;
	std::map<char,int> firstSTL;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	firstSTL['a']=10;
	firstSTL['b']=30;
	firstSTL['c']=50;
	firstSTL['d']=70;
	assertBSTEqual(&first, &firstSTL, "empty constructor");
	ft::Map<char,int> second (first.begin(),first.end());
	std::map<char,int> secondSTL (firstSTL.begin(),firstSTL.end());
	assertBSTEqual(&second, &secondSTL, "range constructor");

	ft::Map<char,int> third(second);
	std::map<char,int> thirdSTL(secondSTL);
	assertBSTEqual(&third, &thirdSTL, "copy constructor");

	ft::Map<char,int,classcomp> fourth;
	std::map<char,int,classcomp> fourthSTL;
	fourth['a']=10;
	fourth['b']=30;
	fourth['c']=50;
	fourth['d']=70;
	fourthSTL['a']=10;
	fourthSTL['b']=30;
	fourthSTL['c']=50;
	fourthSTL['d']=70;
	assertBSTEqual(&fourth, &fourthSTL, "constructor comp class");
	bool(*fn_pt)(char,char) = fncomp;
	ft::Map<char,int,bool(*)(char,char)> fifth (fn_pt);
	std::map<char,int,bool(*)(char,char)> fifthSTL (fn_pt);
	fifth['a']=10;
	fifth['b']=30;
	fifth['c']=50;
	fifth['d']=70;
	fifthSTL['a']=10;
	fifthSTL['b']=30;
	fifthSTL['c']=50;
	fifthSTL['d']=70;
	assertBSTEqual(&fifth, &fifthSTL, "constructor fn");
}

void testCopy() {
	ft::Map<char,int> first;
	ft::Map<char,int> second;
	std::map<char,int> firstSTL;
	std::map<char,int> secondSTL;

	first['x']=8;
	first['y']=16;
	first['z']=32;
	firstSTL['x']=8;
	firstSTL['y']=16;
	firstSTL['z']=32;

	second=first;
	secondSTL=firstSTL;
	first=ft::Map<char,int>();
	firstSTL=std::map<char, int>();

	//assertBSTEqual(&second, &secondSTL, "operator= copy");
	assertBSTEqual(&first, &firstSTL, "operator= original emptied");
}

void testMap(){
	std::cout << "\033[1;37m                           >> MAP <<                            \033[0m" << std::endl;
	testConstructors();
	testCopy();
	testBeginEnd();
	testRbeginRend();
	testInsert();
	testEmpty();
	testSize();
	testMaxSize();
	testOperatorBrackets();
	testErase();
	testSwap();
	testClear();
	testKeyComp();
	testValueComp();
	testFind();
	testCount();
	testLowerBound();
	testUpperBound();
	testEqualBound();
}