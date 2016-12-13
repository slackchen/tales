// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tales.h>

using namespace Tales::Core;

String foo()
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

	String test = foo();
}

int main()
{
	testString();

	return 0;
}