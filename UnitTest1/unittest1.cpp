#include "stdafx.h"
#include "CppUnitTest.h"

#include <tales.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Tales::Core;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestString)
		{
			// TODO: Your test code here
			String str = String(String("abc"));
			String str2 = "Abc";

			bool ret = str.compareLowercase(str2);
			Assert::IsTrue(ret);

			int pos = str.indexOf("abc");
			Assert::IsTrue(pos == 0);
			
			int pos2 = str.lastIndexOf("abce");
			Assert::IsTrue(pos2 == String::NotFound);

			str = String::format("This is a %d test %s!", 8, "joke");
			Assert::AreEqual(str.str(), "This is a 8 test joke!");
			str = str.substr(2);
			Assert::AreEqual(str.str(), "is is a 8 test joke!");

			str = "abcd" + String("ef") + "g";
			Assert::AreEqual(str.str(), "abcdefg");

			str = str.replace("cde", "dc");
			Assert::AreEqual(str.str(), "abdcfg");

			String test = foo();
			Assert::AreEqual(test.str(), "abc");
		}

		TEST_METHOD(TestArray)
		{
			Array<int> list = { 4, 5, 6 };
			Assert::IsTrue(list[0] == 4 && list[1] == 5 && list[2] == 6);

			list.add(1);
			list.add(2);
			list.add(3);
			Assert::IsTrue(list[3] == 1 && list[4] == 2 && list[5] == 3);

			list.printAll();
			
			list.removeAt(1);
			Assert::IsTrue(list[0] == 4 && list[1] == 6 && list[2] == 1);

			list.printAll();

			list.removeAll();
			list.printAll();
		}

		String foo()
		{
			return std::move(String("abc"));
		}

	};
}