#pragma once

namespace Tales
{
	namespace Core
	{
		class TALES_API Object
		{
		public:
			Object();
			virtual ~Object();

			void* operator new (size_t size);
			void operator delete(void* ptr);
		};
	}
}

