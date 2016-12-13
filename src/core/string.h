#pragma once

namespace Tales
{
	namespace Core
	{
		class TALES_API String : public Object
		{
		public:
			static const int NotFound = -1;

			String();
			String(const char* instr);
			String(const String& str);
			String(String&& str);
			~String();

			void resize(int size);
			int length() const;

			String& initWithString(const char* instr);
			String& assign(const String& str);
			String& assign(String&& str);
			String substr(int startIndex, int count = -1);
			String concat(const String& str);
			const char* str() const;

			static String stringWithString(const char* instr);
			static String format(const char* format, ...);

			bool compare(const String& str);
			bool compareLowercase(const String& str);
			String replace(const String& rep, const String& to);
			//String[] split(const String& splitStr);

			int indexOf(const String& searchValue, int startIndex = 0);
			int lastIndexOf(const String& searchValue, int startIndex = 0);

			bool operator==(const String& str);
			String& operator=(const String& str);
			String& operator=(String&& str);
			char operator[] (int index) const;

			String operator+(const String& str);
			String operator+(const char* str);
			friend String operator+(const char* str1, const String& str2);

		private:
			char* strData = nullptr;
			int numOfStr = 0;
		};
	}
}

