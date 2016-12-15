#include "array.h"
namespace Tales
{
	namespace Core
	{
		template <class T>
		inline Array<T>::Array()
		{
			
		}

		template<class T>
		inline Array<T>::Array(const Array & rhs)
		{
			assign(rhs);
		}

		template<class T>
		inline Array<T>::Array(Array && rhs)
		{
			assign(std::move(rhs));
		}

		template <class T>
		inline Array<T>::Array(const std::initializer_list<T>& list)
		{
			resize(list.size());
			int i = 0;
			for (const T& elem : list)
			{
				elements[i] = elem;
				i++;
			}
		}


		template <class T>
		inline Array<T>::~Array()
		{
			removeAll();
		}

		template<class T>
		inline int Array<T>::num() const
		{
			return numOfElem;
		}

		template<class T>
		inline Array<T> & Array<T>::assign(const Array & rhs)
		{
			int num = rhs.num();
			resize(num);

			for (int i = 0; i < num; ++i)
				elements[i] = rhs.elements[rhs.i];

			return *this;
		}

		template<class T>
		inline Array<T> & Array<T>::assign(Array && rhs)
		{
			delete[] (elements - begin);
			elements = rhs.elements;
			numOfElem = rhs.numOfElem;
			capSize = rhs.capSize;
			begin = rhs.begin;

			rhs.elements = nullptr;
			rhs.numOfElem = 0;
			rhs.capSize = 0;
			rhs.begin = 0;

			return *this;
		}

		template<class T>
		inline void Array<T>::add(const T & elem)
		{
			resize(num() + 1);
			new(&elements[num() - 1])T;
			elements[num() - 1] = elem;
		}

		template<class T>
		inline T & Array<T>::addnew()
		{
			resize(num() + 1);
			new(&elements[num() - 1])T;
			return elements[num() - 1];
		}

		template<class T>
		inline void Array<T>::removeAt(int index)
		{
			tales_assert(index >= 0 && index < num());

			T* copyElems = nullptr;
			if (num() - 1 > 0 && num() - 1 < capSize / 4)
			{
				capSize /= 4;
				int allocSize = capSize * sizeof(T) + (16 - 1) & ~(16 - 1);
				copyElems = (T*)new char[allocSize];

				if (std::is_pod<T>::value)
				{
					memcpy(copyElems, elements, sizeof(T) * index);
				}
				else
				{
					for (int i = 0; i < index; ++i)
					{
						new(&copyElems[i])T;
						copyElems[i] = elements[i];
					}
				}
				
				int copyCount = num() - index - 1;
				if (copyCount > 0)
				{
					if (std::is_pod<T>::value)
					{
						memcpy(copyElems + index, elements + index + 1, sizeof(T) * copyCount);
					}
					else
					{
						for (int i = index; i < index + copyCount; ++i)
						{
							new(&copyElems[i])T;
							copyElems[i] = elements[i + 1];
						}
					}
				}

				delete[] (elements - begin);
				elements = copyElems;
				begin = 0;
			}
			else
			{
				if (index == 0)
				{
					begin++;
					capSize--;
					elements++;
				}
				else
				{
					copyElems = elements;
					int copyCount = num() - index - 1;
					if (copyCount > 0)
					{
						if (std::is_pod<T>::value)
						{
							memcpy(copyElems + index, elements + index + 1, sizeof(T) * copyCount);
						}
						else
						{
							for (int i = index; i < index + copyCount; ++i)
							{
								new(&copyElems[i])T;
								copyElems[i] = elements[i + 1];
							}
						}
					}
				}
			}

			numOfElem--;
		}

		template<class T>
		inline void Array<T>::removeAll()
		{
			delete[] (elements - begin);
			elements = nullptr;
			numOfElem = 0;
			capSize = 0;
			begin = 0;
		}

		template<class T>
		inline void Array<T>::resize(int size)
		{
			if (size > capSize)
			{
				capSize = size * 2;

				int allocSize = capSize * sizeof(T) + (16 - 1) & ~(16 - 1);
				T* newElems = (T*)new char[allocSize];

				if (std::is_pod<T>::value)
				{					
					memcpy(newElems, elements, sizeof(T) * num());
				}
				else
				{
					for (int i = 0; i < size; ++i)
					{
						new(&newElems[i])T;

						if (i < num())
							newElems[i] = elements[i];
					}
				}

				delete[] (elements - begin);
				elements = newElems;
				begin = 0;
			}

			numOfElem = size;
		}

		template<class T>
		inline const T & Array<T>::operator[](int index) const
		{
			tales_assert(index >= 0 && index < num());
			return elements[index];
		}

		template<class T>
		inline Array<T> & Array<T>::operator=(const Array & rhs)
		{
			return assign(rhs);
		}

		template<class T>
		inline Array<T> & Array<T>::operator=(Array && rhs)
		{
			return assign(std::move(rhs));
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
