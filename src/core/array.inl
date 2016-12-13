#include "array.h"
#include "array.h"
#include "tales.h"
#include "array.h"

namespace Tales
{
	namespace Core
	{
		template <class T>
		Array<T>::Array()
		{
		}

		template <class T>
		Array<T>::Array(const std::initializer_list<T>& list)
		{
			for (auto elem : list)
			{
				add(elem);
			}
		}


		template <class T>
		Array<T>::~Array()
		{
		}

		template<class T>
		int Array<T>::num() const
		{
			return numOfElem;
		}

		template<class T>
		void Array<T>::add(const T & elem)
		{
			resize(numOfElem + 1);
			elements[numOfElem] = elem;
			numOfElem++;
		}

		template<class T>
		void Array<T>::removeAt(int index)
		{
			tales_assert(index >= 0 && index < numOfElem);

			T* copyElems = nullptr;
			if (numOfElem - 1 < capSize / 4)
			{
				capSize /= 4;
				int allocSize = capSize * sizeof(T) + (16 - 1) & ~(16 - 1);
				copyElems = (T*)new char[allocSize];

				memcpy(copyElems, elements, sizeof(T) * index);
				int copyCount = numOfElem - index - 1;
				if (copyCount > 0)
					memcpy(copyElems + index, elements + index + 1, sizeof(T) * copyCount);
				delete[] elements;
				elements = copyElems;
			}
			else
			{
				copyElems = elements;
				int copyCount = numOfElem - index - 1;
				if (copyCount > 0)
					memcpy(copyElems + index, elements + index + 1, sizeof(T) * copyCount);
			}

			numOfElem--;
		}

		template<class T>
		inline void Array<T>::removeAll()
		{
			delete[] elements;
			numOfElem = 0;
			capSize = 0;
		}

		template<class T>
		void Array<T>::resize(int size)
		{
			if (size > capSize)
			{
				capSize = size * 2;
				int allocSize = capSize * sizeof(T) + (16 - 1) & ~(16 - 1);
				T* newElems = (T*)new char[allocSize];
				memcpy(newElems, elements, sizeof(T) * numOfElem);
				delete[] elements;
				elements = newElems;
			}
		}

		template<class T>
		inline const T & Array<T>::operator[](int index) const
		{
			tales_assert(index >= 0 && index < numOfElem);
			return elements[index];
		}

		template<class T>
		inline void Array<T>::printAll()
		{
			for (int i = 0; i < num(); ++i)
				std::cout << elements[i] << " ";
			std::cout << std::endl;

		}
	}
}
