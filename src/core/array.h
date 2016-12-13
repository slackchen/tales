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
			Array(const std::initializer_list<T>& list);
			~Array();

			int num() const;

			Array& assign(const Array& rhs);

			void add(const T& elem);
			void removeAt(int index);
			void removeAll();

			void resize(int size);

			const T& operator[](int index) const;
			Array& operator=(const Array& rhs);

			void printAll();

		private:
			T* elements = nullptr;
			int numOfElem = 0;
			int capSize = 0;
		};
	}
}

#include "array.inl"

