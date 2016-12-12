#pragma once

namespace Tales
{
	namespace Core
	{
		class String : public Object
		{
		public:
			const int NotFound = -1;

			String();
			String(const char* str);
			String(const String& str);
			String(String&& str);
			~String();

			void initWithString(const char* instr);
			String& operator=(const String& str);
			String& operator=(String&& str);

			int Length() const;

			char operator[] (int index) const;

			int indexOf(const String& searchValue, int startIndex = 0);

		private:
			char* str;
		};
	}
}

