// Test.cpp : Defines the entry point for the console application.
//

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

Array<String>&& fooArray()
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

	Array<int> intlist;
	for (int i = 0; i < 10000; ++i)
		intlist.add(i);
	for (int i = 0; i < 10000; ++i)
		intlist.removeAt(0);
}

void testMap()
{
	Map<String, String> map = { "abc", "bcd", "def" };
	auto iter = map.getIterator();

	while (iter.hasNext())
	{
		std::cout << iter.next() << std::endl;
	}

	*map.objectForKey("abc") == "abc";
}

void testSocket()
{
	std::thread* tServer = new std::thread([] {
		Tales::Net::Socket socket;
		socket.create();
		socket.setBlocking(true);
		socket.bind("0.0.0.0:9999");

		Tales::Net::Socket client = socket.accept();
		client.setBlocking(true);

		int i = 0;
		while (true)
		{
			String str = client.recvString();
			std::cout << str << i << std::endl;
			++i;

			if (i >= 130000)
                break;
		}
	});

	std::this_thread::sleep_for(std::chrono::seconds(2));

		//std::thread tClient([] {
			Tales::Net::Socket socketClient;
			socketClient.create();
			socketClient.setBlocking(true);
			socketClient.connect("127.0.0.1:9999");

			for (int i = 0; i < 130000; ++i)
			{
				socketClient.send("This is test!");
				//String str = client.recvString();
				//std::cout << str << std::endl;
			}
		//});

    tServer->join();

}

int main()
{
	testString();

	testArray();

	testMap();

	testSocket();

	return 0;
}
