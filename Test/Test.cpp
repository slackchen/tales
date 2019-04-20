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
    TALES_UNUSED(ret);

	int pos = str.indexOf("abc");
    TALES_UNUSED(pos);
	int pos2 = str.lastIndexOf("abce");
    TALES_UNUSED(pos2);

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
    TALES_UNUSED(ret);
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
	bool stop = false;
	std::thread tServer([&stop] {
		Tales::Net::Socket socket;
		socket.create(Tales::Net::Socket::Protocol::Udp);
		socket.setBlocking(true);
		socket.bind("0.0.0.0:9999");
		//socket.connect("localhost:9999");

		//Tales::Net::Socket client = socket.accept();
		//client.setBlocking(true);

        //Tales::Net::Socket& client = socket;

		int i = 0;
		while (true)
		{
			String str = String("[recv]") + socket.recvString(14);
			std::cout << str << i + 1 << std::endl;
			++i;

			if (i >= 130000)
                break;
		}

		stop = true;
	});

	std::this_thread::sleep_for(std::chrono::seconds(1));

		//std::thread tClient([] {
			Tales::Net::Socket socketClient;
			socketClient.create(Tales::Net::Socket::Protocol::Udp);
			socketClient.setBlocking(true);
			socketClient.bind("0.0.0.0:9999");
			socketClient.connect("localhost:9999");

			for (int i = 0; /*i < 130000*/; ++i)
			{
				socketClient.send("This is test!");
				//String str = client.recvString();
				//std::cout << str << std::endl;
				if (stop)
					break;
			}
		//});

			std::cout << "send finished" << std::endl;

    tServer.join();

}

int main()
{
	testString();

	testArray();

	testMap();

	testSocket();

	return 0;
}
