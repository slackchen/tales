// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tales.h>

using namespace Tales::Core;

String fooStr()
{
	return std::move(String("abc"));
}

void testString()
{
	String str = String(String("abc"));
	String str2 = "Abc";

	bool ret = str.compareLowercase(str2);

	int pos = str.indexOf("abc");
	int pos2 = str.lastIndexOf("abce");

	str = String::format("This is a %d test %s!", 8, "joke");
	str = str.substr(2);

	str = "abcd" + String("ef") + "g";

	str = str.replace("cde", "dc");

	String test = fooStr();
}

Array<String> fooArray()
{
	return std::move(Array<String>({ "abc", "def", "123" }));
}

void testArray()
{
	Array<int> list = {4, 5, 6};
	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);
	list.add(5);
	list.add(6);
	list.printAll();
	list.removeAt(1);
	list.printAll();

	list.removeAt(0);
	list.removeAt(0);
	list.removeAt(0);
	list.removeAt(0);
	list.removeAt(0);
	list.removeAt(0);
	list.printAll();

	list.removeAll();
	list.printAll();

	Array<String> strs = { "abc", "def", "123" };
	String str1 = strs[0];
	String str2 = strs[1];
	String str3 = strs[2];

	strs.removeAt(0);
	strs.removeAt(0);
	strs.removeAt(0);

	Array<String> test = fooArray();

	test = std::move(Array<String>({ "abc", "def", "123" }));
	
	String& str = strs.addnew();
	bool ret = str == "";
	str = strs.addnew();

	strs = String("abc,def,123").split(",");
	strs.printAll();
}

int main()
{
	testString();

	testArray();

	return 0;
}