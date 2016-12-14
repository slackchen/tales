namespace Tales
{
	namespace Core
	{
		template <class T>
		Array<T>::Array()
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
		Array<T>::Array(const std::initializer_list<T>& list)
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
		Array<T>::~Array()
		{
			delete[] elements;
			elements = nullptr;
			numOfElem = 0;
			capSize = 0;
		}

		template<class T>
		int Array<T>::num() const
		{
			return numOfElem;
		}

		template<class T>
		inline Array<T> & Array<T>::assign(const Array & rhs)
		{
			int num = rhs.num();
			resize(num);

			for (int i = 0; i < num; ++i)
				elements[i] = rhs.elements[i];

			return *this;
		}

		template<class T>
		inline Array<T> & Array<T>::assign(Array && rhs)
		{
			delete[] elements;
			elements = rhs.elements;
			numOfElem = rhs.numOfElem;
			capSize = rhs.capSize;

			rhs.elements = nullptr;
			rhs.numOfElem = 0;
			rhs.capSize = 0;

			return *this;
		}

		template<class T>
		void Array<T>::add(const T & elem)
		{
			resize(numOfElem + 1);
			new(&elements[numOfElem - 1])T;
			elements[numOfElem - 1] = elem;
		}

		template<class T>
		inline T & Array<T>::addnew()
		{
			resize(numOfElem + 1);
			new(&elements[numOfElem - 1])T;
			return elements[numOfElem - 1];
		}

		template<class T>
		void Array<T>::removeAt(int index)
		{
			tales_assert(index >= 0 && index < numOfElem);

			T* copyElems = nullptr;
			if (numOfElem - 1 > 0 && numOfElem - 1 < capSize / 4)
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
				
				int copyCount = numOfElem - index - 1;
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

				delete[] elements;
				elements = copyElems;
			}
			else
			{
				copyElems = elements;
				int copyCount = numOfElem - index - 1;
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

			numOfElem--;
		}

		template<class T>
		inline void Array<T>::removeAll()
		{
			delete[] elements;
			elements = nullptr;
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

				if (std::is_pod<T>::value)
				{
					memcpy(newElems, elements, sizeof(T) * numOfElem);
				}
				else
				{
					for (int i = 0; i < size; ++i)
					{
						new(&newElems[i])T;

						if (i < numOfElem)
							newElems[i] = elements[i];
					}
				}

				delete[] elements;
				elements = newElems;
			}

			numOfElem = size;
		}

		template<class T>
		inline const T & Array<T>::operator[](int index) const
		{
			tales_assert(index >= 0 && index < numOfElem);
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
