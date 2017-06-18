#include "gtest/gtest.h"
#include "Containers/FreMemory.h"

#include <map>
#include <unordered_map>
#include <random>

using namespace FRE;

TEST(Test_PoolChunk, Allocate)
{
	const unsigned PoolSize = 1000000;
	Utils::FPoolChunk<unsigned> poolChunk(sizeof(float), PoolSize);

	float ** p = new float*[PoolSize];
	for (int i = 0; i < PoolSize; ++i)
	{
		p[i] = (float *)poolChunk.Allocate();
		*p[i] = (float)i;
	}
	ASSERT_EQ(poolChunk.IsFull(), true);
	ASSERT_EQ(poolChunk.Allocate(), nullptr);

	for (int i = 0; i < PoolSize; ++i)
		 poolChunk.Deallocate(p[i]);
	ASSERT_EQ(poolChunk.IsEmpty(), true);

	for (int i = 0; i < PoolSize; ++i)
	{
		p[i] = (float *)poolChunk.Allocate();
		*p[i] = (float)i;
	}

	poolChunk.Deallocate(p[PoolSize/2]);
	ASSERT_EQ(poolChunk.IsFull(), false);
	ASSERT_EQ(poolChunk.IsEmpty(), false);

	void * newP = poolChunk.Allocate();
	ASSERT_EQ(p[PoolSize/2], newP);
}

class Test_PoolMemory : public ::testing::Test
{
public:
	enum 
	{
		Size = 10000,
		ChunkSize = Size/4
	};

	struct Foo
	{
		Foo(unsigned long long v)
		{
			_val = v;
		}

		~Foo()
		{
			_val = 0;
		}

		void * operator new(std::size_t size) 
		{
			return _poolMemory.Allocate();
		}

		void operator delete(void * pointer)
		{
			_poolMemory.Deallocate(pointer);
		}

		unsigned long long _val;
	};

	virtual void SetUp() override
	{
	}

protected:
	static Utils::FPoolMemory<Foo, ChunkSize> _poolMemory;
};

Utils::FPoolMemory<Test_PoolMemory::Foo, Test_PoolMemory::ChunkSize> Test_PoolMemory::_poolMemory;

TEST_F(Test_PoolMemory, Allocate)
{
	Foo ** pointers = new Foo*[Size];

	for (unsigned i = 0; i < Size; ++i)
	{
		pointers[i] = new Foo(i);
	}

	for (unsigned i = 0; i < Size; ++i)
	{
		ASSERT_EQ(pointers[i]->_val, i);
	}

	for (unsigned i = 0; i < Size; ++i)
	{
		delete pointers[i];
	}
}

TEST_F(Test_PoolMemory, AllocateDealloc)
{
	for (unsigned i = 0; i < Size; ++i)
	{
		Foo * p = new Foo(i);
        ASSERT_EQ(p->_val, i);
		delete p;
	}
}

struct HeapFoo
{
	HeapFoo(unsigned long long v)
	{
		_val = v;
	}

	unsigned long long _val;
};

TEST(Test_Heap, Allocate)
{
	HeapFoo ** pointers = new HeapFoo*[Test_PoolMemory::Size];

	for (unsigned i = 0; i < Test_PoolMemory::Size; ++i)
	{
		pointers[i] = new HeapFoo(i);
	}

	for (unsigned i = 0; i < Test_PoolMemory::Size; ++i)
	{
		ASSERT_EQ(pointers[i]->_val, i);
	}

	for (unsigned i = 0; i < Test_PoolMemory::Size; ++i)
	{
		delete pointers[i];
	}
}

TEST(Test_Heap, AllocateDealloc)
{
	for (unsigned i = 0; i < Test_PoolMemory::Size; ++i)
	{
		HeapFoo * p = new HeapFoo(i);
        ASSERT_EQ(p->_val, i);
		delete p;
	}
}
