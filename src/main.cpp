
#include "tales.h"

using namespace Tales::Core;

String foo()
{
	return std::move(String("abc"));
}

int main()
{
	String* str = new String(String("abce"));

	int pos = str->indexOf(*str);

	String test = foo();

    return 0;
}

