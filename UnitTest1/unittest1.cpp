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
		
		String fooStr()
		{
			return std::move(String("abc"));
		}

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

			String test = fooStr();
			Assert::AreEqual(test.str(), "abc");
		}

		Array<String> fooArray()
		{
			return std::move(Array<String>({ "abc", "def", "123" }));
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

			Array<String> strs = { "abc", "def", "123" };
			Assert::IsTrue(strs[0] == "abc");
			Assert::IsTrue(strs[1] == "def");
			Assert::IsTrue(strs[2] == "123");

			Array<String> movedStrs = Array<String>({ "abc", "def", "123" });
			Assert::IsTrue(movedStrs[0] == "abc");
			Assert::IsTrue(movedStrs[1] == "def");
			Assert::IsTrue(movedStrs[2] == "123");

			Array<String> test = std::move(Array<String>({ "abc", "def", "123" }));
			Assert::IsTrue(test[0] == "abc");
			Assert::IsTrue(test[1] == "def");
			Assert::IsTrue(test[2] == "123");

			test = fooArray();

			String& str = strs.addnew();
			Assert::IsTrue(str == "");
			str = strs.addnew();
			Assert::IsTrue(str == "");

			strs = String("abc,def,123").split(",");
			Assert::IsTrue(strs[0] == "abc");
			Assert::IsTrue(strs[1] == "def");
			Assert::IsTrue(strs[2] == "123");
		}
	};
}