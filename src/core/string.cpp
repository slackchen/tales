#include "tales.h"

namespace Tales
{
	namespace Core
	{
		
		String::String()
		{
		}

		String::String(const char * instr)
		{
			initWithString(instr);
		}

		String::String(const String & str)
		{
			initWithString(str.str);
		}

		String::String(String && str)
		{
			this->str = str.str;
			str.str = nullptr;
		}


		String::~String()
		{		
			delete str;
		}

		void String::initWithString(const char* instr)
		{
			tales_assert(instr != nullptr);

			int size = strlen(instr);
			int allocSize = (size + 1) + (4 - 1) & ~(4 - 1);
			str = new char[allocSize];

			if (size > 0)
				memcpy(str, instr, size * sizeof(char));

			str[size] = 0;
		}

		String & String::operator=(const String & str)
		{
			initWithString(str.str);
			return *this;
		}

		String & String::operator=(String && str)
		{
			this->str = str.str;
			str.str = nullptr;
			return *this;
		}

		int String::Length() const
		{
			int len;
			for (len = 0; str[len] != 0; ++len)
				;

			return len;
		}

		char String::operator[](int index) const
		{
			tales_assert(index >= 0 && index < Length());
			return str[index];
		}

		int String::indexOf(const String & searchValue, int startIndex)
		{
			int len = Length();
			int searchLen = searchValue.Length();

			if (startIndex >= len)
				return NotFound;

			int start = startIndex;
			int cur = 0;
			int pos = start;

			for (; start < len || cur < searchLen;)
			{
				cur = 0;

				while (str[start] != searchValue[cur])
					start++;

				pos = start;
				while ((start < len || cur < searchLen) && str[start] == searchValue[cur])
				{
					start++;
					cur++;
				}
			}

			if (cur == searchLen)
				return pos - startIndex;

			return NotFound;
		}
	}
}

