#pragma once

namespace Tales
{
	namespace Core
	{
		template <class Key, class T>
		class Map;

		template <class Key, class T>
		class MapIterator
		{
		public:
			MapIterator(Map<Key, T>& map);
			bool hasNext() const;
			T& next();
			T& value();

		private:
			Map<Key, T>& map;
			typename std::map<Key, T>::iterator it;
		};

		template <class Key, class T>
		class Map : public Object
		{
		public:
			Map();
			Map(const std::initializer_list<T>& list);
			Map(const Map& rhs);
			~Map();

			Map& assign(const Map& rhs);
			Map& assign(Map&& rhs);

			void add(const Key& key, const T& value);
			void remove(const Key& key);
			void removeAll();

			T* objectForKey(const Key& key);
			MapIterator<Key, T> getIterator();

			T& operator[](const Key& key);

			friend class MapIterator<Key, T>;

		private:
			std::map<Key, T>* map = nullptr;
		};

	}
}


#include "map.inl"
