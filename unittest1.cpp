#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Fun.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	//public:
		
		TEST_METHOD(TestMethod1)//Проверим на вхождение 1 строку
		{
			string ResultStr = "";
			int ResultInt[20];
			vector<string> keywords;
			keywords.push_back("a");
			string text = "ahisahersa";
			buildMatchingMachine(keywords, 'a', 'z');
			int currentState = 0;
			for (int i = 0; i < text.size(); ++i)
			{
				currentState = findNextState(currentState, text[i], 'a');
				if (out[currentState] == 0)
					continue;
				for (int j = 0; j < keywords.size(); ++j)
				{
					if (out[currentState] & (1 << j))
					{ 
						ResultInt[j] = i - keywords[j].size() + 1;
						ResultStr += keywords[j];
					}
				}
			}
			string str = "aaa";
			Assert::AreEqual(str, ResultStr);
		}

		TEST_METHOD(TestMethod2)//Проверим на вхождение несколько строк
		{
			string ResultStr = "";
			int ResultInt[20];
			vector<string> keywords;
			keywords.push_back("a");
			keywords.push_back("i");
			string text = "ahisahersa";
			buildMatchingMachine(keywords, 'a', 'z');
			int currentState = 0;
			for (int i = 0; i < text.size(); ++i)
			{
				currentState = findNextState(currentState, text[i], 'a');
				if (out[currentState] == 0)
					continue;
				for (int j = 0; j < keywords.size(); ++j)
				{
					if (out[currentState] & (1 << j))
					{
						ResultInt[j] = i - keywords[j].size() + 1;
						ResultStr += keywords[j];
					}
				}
			}
			string str = "aiaa";
			Assert::AreEqual(str, ResultStr);
		}

		TEST_METHOD(TestMethod3)//Инъекция ошибки
		{
			string ResultStr = "";
			int ResultInt[20];
			vector<string> keywords;
			keywords.push_back("a");
			string text = "ahisahersa";
			buildMatchingMachine(keywords, 'a', 'z');
			int currentState = 0;
			for (int i = 0; i < text.size(); ++i)
			{
				currentState = findNextState(currentState, text[i], 'a');
				if (out[currentState] == 0)
					continue;
				for (int j = 0; j < keywords.size(); ++j)
				{
					if (out[currentState] & (1 << j))
					{
						ResultInt[j] = i - keywords[j].size() + 1;
						ResultStr += keywords[j];
					}
				}
			}
			string str = "aiaa";
			Assert::AreNotEqual(str, ResultStr);
		}

	};

}