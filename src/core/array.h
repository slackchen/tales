#pragma once

namespace Tales
{
	namespace Core
	{
		template <class T>
		class Array : public Object
		{
		public:
			Array();
			Array(const Array& rhs);
			Array(Array&& rhs);
			Array(const std::initializer_list<T>& list);
			~Array();

			int num() const;

			Array& assign(const Array& rhs);
			Array& assign(Array&& rhs);

			void add(const T& elem);
			T& addnew();			
			void removeAt(int index);
			void removeAll();

			void resize(int size);

			const T& operator[](int index) const;
			Array& operator=(const Array& rhs);
			Array& operator=(Array&& rhs);

			void printAll();

		private:
			T* elements = nullptr;
			int numOfElem = 0;
			int capSize = 0;
			int begin = 0;
		};
	}
}

#include "array.inl"

