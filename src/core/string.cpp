#include "tales.h"

namespace Tales
{
	namespace Core
	{		
		String::String()
		{
			initWithString("");
		}

		String::String(const char * instr)
		{
			initWithString(instr);
		}

		String::String(const String & str)
		{
			initWithString(str.strData);
		}

		String::String(String && str)
		{
			assign(std::move(str));
		}

		String::~String()
		{		
			delete[] strData;
			strData = nullptr;
			numOfStr = 0;
		}

		void String::resize(int size)
		{
			//tales_assert(size > 0);

			delete[] strData;
			numOfStr = 0;
			int allocSize = (size + 1 + (4 - 1)) & ~(4 - 1);
			strData = new char[allocSize];
			strData[0] = 0;
		}

		int String::length() const
		{
			return numOfStr;
		}

		String& String::initWithString(const char* instr)
		{
			tales_assert(instr != nullptr);

			int size = (int)strlen(instr);
			resize(size);

			if (size > 0)
				memcpy(strData, instr, size * sizeof(char));

			strData[size] = 0;
			numOfStr = size;

			return *this;
		}

		String & String::assign(const String & str)
		{
			delete[] strData;
			strData = str.strData;
			numOfStr = str.numOfStr;
			return *this;
		}

		String & String::assign(String && str)
		{
			delete[] strData;
			strData = str.strData;
			numOfStr = str.numOfStr;
			str.strData = nullptr;
			str.numOfStr = 0;

			return *this;
		}

		String String::substr(int startIndex, int count)
		{
			int len = length();

			tales_assert(startIndex >= 0 && startIndex < len);
			tales_assert(startIndex + count < len);

			int copyCount = count == -1 ? len - startIndex : count;

			String newStr;
			newStr.resize(copyCount);
			memcpy(newStr.strData, strData + startIndex, sizeof(char) * copyCount);
			newStr.strData[copyCount] = 0;
			newStr.numOfStr = copyCount;

			return std::move(newStr);
		}

		String String::concat(const String & str)
		{
			String newStr;

			int len = length();
			int newlen = str.length();

			newStr.resize(len + newlen);
			memcpy(newStr.strData, strData, sizeof(char) * len);
			memcpy(newStr.strData + len, str.strData, sizeof(char) * newlen);
			newStr.numOfStr = len + newlen;
			newStr.strData[newStr.numOfStr] = 0;

			return std::move(newStr);
		}

		const char * String::str() const
		{
			return strData;
		}

		String String::stringWithString(const char * instr)
		{
			return std::move(String().initWithString(instr));
		}

		String String::format(const char * format, ...)
		{
			String newStr;
			newStr.resize(1024);

			va_list arg;
			va_start(arg, format);
			vsprintf(newStr.strData, format, arg);
			va_end(arg);
			newStr.numOfStr = (int)strlen(newStr.strData);

			return std::move(newStr);
		}

		bool String::compare(const String & str) const
		{
			if (numOfStr != str.numOfStr)
				return false;

			int start = 0;
			int cur = 0;
			int len = length();
			int searchLen = str.length();

			for (; start < len && cur < searchLen; ++start, ++cur)
			{
				if (str[start] != str.strData[cur])
					return false;
			}

			return start == len && cur == searchLen;
		}

		bool String::compareLowercase(const String & str) const
		{
			if (numOfStr != str.numOfStr)
				return false;

			int start = 0;
			int cur = 0;
			int len = length();
			int searchLen = str.length();

			for (; start < len && cur < searchLen; ++start, ++cur)
			{
				if (tolower(str[start]) != tolower(str.strData[cur]))
					return false;
			}

			return start == len && cur == searchLen;
		}

		String String::replace(const String & rep, const String & to) const
		{
			int count = 0;
			int pos = 0;
			int repLen = rep.length();
			int tolen = to.length();

			pos = indexOf(rep, pos);
			while (pos != String::NotFound)
			{
				count++;
				pos = indexOf(rep, pos + repLen);
			}

			if (count == 0)
				return *this;

			String newStr;
			int newSize = (tolen - repLen) * count + length();
			newStr.resize(newSize);

			pos = 0;

			pos = indexOf(rep, pos);
			int copyPos = 0;
			int toPos = 0;
			while (pos != String::NotFound)
			{
				int copyLen = pos - copyPos;
				memcpy(newStr.strData + toPos, strData + copyPos, sizeof(char) * copyLen);
				copyPos += copyLen;
				toPos += copyLen;
				memcpy(newStr.strData + toPos, to.strData, sizeof(char) * tolen);
				copyPos += repLen;
				toPos += tolen;
				pos = indexOf(rep, pos + repLen);
				if (pos == String::NotFound)
					memcpy(newStr.strData + toPos, strData + copyPos, sizeof(char) * (length() - toPos));
			}

			newStr.strData[newSize] = 0;
			newStr.numOfStr = newSize;

			return std::move(newStr);
		}

		Array<String> String::split(const String & splitStr) const
		{
			Array<String> strs;

			int pos = 0;
			int spLen = splitStr.length();			
			int copyPos = 0;

			pos = indexOf(splitStr, pos);
			while (pos != String::NotFound)
			{
				int copyLen = pos - copyPos;

				{
					String& newStr = strs.addnew();
					newStr.resize(copyLen);
					memcpy(newStr.strData, strData + copyPos, sizeof(char) * copyLen);
					newStr.strData[copyLen] = 0;
					newStr.numOfStr = copyLen;
					copyPos += copyLen + spLen;
				}

				pos = indexOf(splitStr, pos + spLen);
				if (pos == String::NotFound)
				{					
					{
						String& newStr = strs.addnew();
						int len = length() - copyPos;
						newStr.resize(len);
						memcpy(newStr.strData, strData + copyPos, sizeof(char) * len);
						newStr.strData[len] = 0;
						newStr.numOfStr = len;
					}
				}
			}

			return std::move(strs);
		}

		int String::indexOf(const String & searchValue, int startIndex) const
		{
			int len = length();
			int searchLen = searchValue.length();

			if (startIndex >= len)
				return NotFound;

			int start = startIndex;
			int cur = 0;
			int pos = start;

			for (; start < len && cur < searchLen;)
			{
				cur = 0;

				char ch = searchValue[cur];
				while (start < len && strData[start] != ch)
					start++;

				pos = start;
				while ((start < len && cur < searchLen) && strData[start] == searchValue[cur])
				{
					start++;
					cur++;
				}
			}

			if (cur == searchLen)
				return pos;

			return NotFound;
		}

		int String::lastIndexOf(const String & searchValue, int startIndex) const
		{
			int len = length();
			int searchLen = searchValue.length();

			if (startIndex >= len)
				return NotFound;

			int start = len - 1;
			int cur = 0;
			int pos = start;

			for (; start >= startIndex && start < len && cur < searchLen;)
			{
				cur = 0;

				char ch = searchValue[cur];
				while (start >= startIndex && strData[start] != ch)
					start--;

				pos = start;
				while ((start < len && cur < searchLen) && strData[start] == searchValue[cur])
				{
					start++;
					cur++;
				}
			}

			if (cur == searchLen)
				return pos;

			return NotFound;
		}

		int String::toInt() const
		{
			return atoi(str());
		}

		float String::toFloat() const
		{
			return (float)atof(str());
		}

		bool String::operator==(const char* str) const
		{
			return compare(str);
		}

		bool String::operator==(const String & str) const
		{
			return compare(str);
		}

		String & String::operator=(const String & str)
		{
			return initWithString(str.strData);
		}

		String & String::operator=(String && str)
		{
			return assign(std::move(str));
		}

		char String::operator[](int index) const
		{
			tales_assert(index >= 0 && index < length());
			return strData[index];
		}

		bool String::operator<(const String & rhs) const
		{
			return strcmp(str(), rhs.str()) < 0;
		}

		String String::operator+(const String & str)
		{
			return std::move(concat(str));
		}

		String String::operator+(const char * str)
		{
			return std::move(concat(str));
		}

		String operator+(const char * str1, const String & str2)
		{
			return std::move(String(str1).concat(str2));
		}
		std::ostream & operator<<(std::ostream & os, const String & str)
		{
			return os << str.str();
		}

	}
}

