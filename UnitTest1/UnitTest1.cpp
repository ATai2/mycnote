#include "pch.h"
#include "CppUnitTest.h"
//#include "../cppnode/learn.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual<int>(1, newAaaryTest());
		}
	};
}
