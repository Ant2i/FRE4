#include <NativePlatformStack.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#undef CaptureStackBackTrace
#endif

class Test
{
public:
	Test();
};

Test::Test()
{
	int zero = 0;
	int res = 2 / (int)sin(0);
}

int TestFunction3()
{
	Test();
	return 0;
}

int TestFunction2()
{
	return TestFunction3();
}

int TestFunction1()
{
	return TestFunction2();
}

LONG ExpFilter(EXCEPTION_POINTERS* pExp, DWORD dwExpCode)
{
	std::vector<Platform::PlatformStack::SymbolInfo> stack;
	Platform::PlatformStack::GetStack(Platform::ArraySymbolInfoGet(stack), 0, 1024, (void *)pExp->ContextRecord);

	for (const Platform::PlatformStack::SymbolInfo& info : stack)
	{
		std::cout << info.FileName << "(" << info.LineNumber << ") " << info.FunctionName << std::endl;
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char* argv[])
{

#ifdef _WIN32

	__try
	{
		TestFunction1();
	}
	__except(ExpFilter(GetExceptionInformation(), GetExceptionCode()))
	{
		
	}

#endif

}