#include "tales.h"

namespace Tales
{
	namespace Core
	{
		Object::Object()
		{

		}

		Object::~Object()
		{}

		void * Object::operator new(size_t size)
		{
			int allocSize = (size + (16 - 1)) & ~(16 - 1);
			return malloc(allocSize);
		}
		void * Object::operator new(size_t size, void * addr)
		{
			return addr;
		}

		void Object::operator delete(void * ptr)
		{
			free(ptr);
		}

		void Object::operator delete(void * ptr, void* addr)
		{

		}

	}
}