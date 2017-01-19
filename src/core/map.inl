#include "map.h"

namespace Tales
{
	namespace Core
	{
		template<class Key, class T>
		inline MapIterator<Key, T>::MapIterator(Map<Key, T> & map)
			: map(map)
		{
			it = map.map.begin();
		}

		template<class Key, class T>
		inline bool MapIterator<Key, T>::hasNext() const
		{
			return it != map.map.end();
		}

		template<class Key, class T>
		inline T& MapIterator<Key, T>::next()
		{
			T& t = it->second;
			it++;
			return t;
		}

		template<class Key, class T>
		inline T & MapIterator<Key, T>::value()
		{
			return it->second;
		}

		template<class Key, class T>
		inline Map<Key, T>::Map()
		{

		}

		template <class Key, class T>
		Map<Key, T>::Map(const std::initializer_list<T>& list)
		{
			for (const T& elem : list)
			{
				map[elem] = elem;
			}
		}
		template<class Key, class T>
		inline Map<Key, T>::Map(const Map & rhs)
		{
			assign(rhs);
		}
		template<class Key, class T>
		inline Map<Key, T>::~Map()
		{
		}

		template<class Key, class T>
		inline Map<Key, T>& Map<Key, T>::assign(const Map & rhs)
		{
			map.clear();
			map.insert(rhs.begin, rhs.end());
			return *this;
		}

		template<class Key, class T>
		inline Map<Key, T>& Map<Key, T>::assign(Map && rhs)
		{
			std::swap(map, rhs.map);
			map = rhs.map;
			rhs.map = nullptr;
			return *this;
		}

		template<class Key, class T>
		inline void Map<Key, T>::add(const Key & key, const T & value)
		{
			map[key] = value;
		}

		template<class Key, class T>
		inline void Map<Key, T>::remove(const Key & key)
		{
			map.erase(key);
		}

		template<class Key, class T>
		inline void Map<Key, T>::removeAll()
		{
			map.clear();
		}

		template<class Key, class T>
		inline T * Map<Key, T>::objectForKey(const Key & key)
		{
			auto it = map.find(key);
			if (it == map.end())
				return nullptr;

			return &it->second;
		}

		template<class Key, class T>
		inline MapIterator<Key, T> Map<Key, T>::getIterator()
		{
			return std::move(MapIterator<Key, T>(*this));
		}

		template<class Key, class T>
		inline T & Map<Key, T>::operator[](const Key& key)
		{
			return map[key];
		}
	}
}


