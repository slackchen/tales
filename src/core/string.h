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

			bool compare(const String& str) const;
			bool compareLowercase(const String& str) const;
			String replace(const String& rep, const String& to) const;
			Array<String> split(const String& splitStr) const;

			int indexOf(const String& searchValue, int startIndex = 0) const;
			int lastIndexOf(const String& searchValue, int startIndex = 0) const;

			int toInt() const;
			float toFloat() const;

			bool operator==(const char* str) const;
			bool operator==(const String& str) const;
			String& operator=(const String& str);
			String& operator=(String&& str);
			char operator[] (int index) const;

			bool operator<(const String& rhs) const;

			String operator+(const String& str);
			String operator+(const char* str);
			friend String operator+(const char* str1, const String& str2);
			friend std::ostream& operator<<(std::ostream& os, const String& str);

		private:
			char* strData = nullptr;
			int numOfStr = 0;
		};
	}
}

