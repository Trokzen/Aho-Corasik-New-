#pragma once
// stdafx.h: включаемый файл для стандартных системных включаемых файлов,
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//#include "targetver.h"

// Заголовки CppUnitTest
//#include "CppUnitTest.h"
#include <string>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;
const int MAXS = 6 * 50 + 10; // Max number of states in the matching machine. // Should be equal to the sum of the length of all keywords.			 
const int MAXC = 26; // Number of characters in the alphabet.

class A_C
{
public:
	int ResultInt=0;
	string OpenFile() {
		char chBuff;
		fstream readFile("text.txt");
		if (!readFile) {
			cout << "can't open files!(openFile)";
			exit;
		}
		while (!readFile.eof()) {
			readFile.get(chBuff);
			if (chBuff != '\n')
				text += chBuff;
		}
		text.erase(text.length() - 1, 1);
		readFile.close();
		return text;
	}

	int buildMatchingMachine(const vector<string> &words, char lowestChar = 'a', char highestChar = 'z')
	{
		memset(out, 0, sizeof out);
		memset(f, -1, sizeof f);
		memset(g, -1, sizeof g);
		int states = 1; // Initially, we just have the 0 state
		for (int i = 0; i < words.size(); ++i)
		{
			const string &keyword = words[i];
			int currentState = 0;
			for (int j = 0; j < keyword.size(); ++j)
			{
				int c = keyword[j] - lowestChar;
				if (g[currentState][c] == -1)
				{ // Allocate a new node
					g[currentState][c] = states++;
				}
				currentState = g[currentState][c];
			}
			out[currentState] |= (1 << i); // There's a match of keywords[i] at node currentState.
		}
		// State 0 should have an outgoing edge for all characters.
		for (int c = 0; c < MAXC; ++c)
		{
			if (g[0][c] == -1)
			{
				g[0][c] = 0;
			}
		}

		// Now, let's build the failure function
		queue<int> q;
		for (int c = 0; c <= highestChar - lowestChar; ++c)
		{ // Iterate over every possible input
		  // All nodes s of depth 1 have f[s] = 0
			if ((g[0][c] != -1) && (g[0][c] != 0))
			{
				f[g[0][c]] = 0;
				q.push(g[0][c]);
			}
		}
		while (q.size())
		{
			int state = q.front();
			q.pop();
			for (int c = 0; c <= highestChar - lowestChar; ++c)
			{
				if (g[state][c] != -1)
				{
					int failure = f[state];
					while (g[failure][c] == -1)
					{
						failure = f[failure];
					}
					failure = g[failure][c];
					f[g[state][c]] = failure;
					out[g[state][c]] |= out[failure]; // Merge out values
					q.push(g[state][c]);
				}
			}
		}

		return states;
	}

	int findNextState(int currentState, char nextInput, char lowestChar = 'a')
	{
		int answer = currentState;
		int c = nextInput - lowestChar;
		while (g[answer][c] == -1)
			answer = f[answer];
		return g[answer][c];
	}

	void setText()
	{
		cout << "enter string for AC" << endl;
		cin >> text;
	}

	void setText(string s)
	{
		text = s;
	}

	void AddInTreeStr(string str)
	{
		keywords.push_back(str);
	}

	void AddInTreeStr()
	{
		cout << "enter string for TreeBohr" << endl;
		cin >> str;
		keywords.push_back(str);
	}

	string ACSetup()
	{
		buildMatchingMachine(keywords, 'a', 'z');
		int currentState = 0;
		for (int i = 0; i < text.size(); ++i)
		{
			currentState = findNextState(currentState, text[i], 'a');
			if (out[currentState] == 0)
				continue; // Nothing new, let's move on to the next character.
			for (int j = 0; j < keywords.size(); ++j)
			{
				if (out[currentState] & (1 << j))
				{ // Matched keywords[j]
					cout << "Keyword " << keywords[j] << " appears from " << i - keywords[j].size() + 1 << "to" << i << endl;
					ResultInt+= i;
					ResultStr += keywords[j];
				}
			}
		}
		return ResultStr;
	}

	void Menu()
	{
		int a = 0;
		bool x = true;
		do
		{
			cout << "enter 1 for input text" << endl;
			cout << "enter 2 for read text from file" << endl;
			cout << "enter 3 for add string in bohr" << endl;
			cout << "enter 4 for processing text" << endl;
			cout << "enter 5 for exit" << endl;
			cin >> a;
			switch (a)
			{
			case 1: {setText(); break; }//Ввести текст;
			case 2: {OpenFile(); break; }//Считать текст из файла;
			case 3: {AddInTreeStr(); break; }//Добавить строку в бор;
			case 4: {ACSetup(); system("pause"); break; }//Обработать текст;
			case 5: {x = false; break; }//Выход.
			default:
				break;
			}
			system("cls");
			ResultStr = "";
		} while (x);
	}

	~A_C()
	{

	}
private:
	vector<string> keywords;
	string text;
	string ResultStr = "";
	string str;
	int out[MAXS]; // Output for each state, as a bitwise mask.
	int f[MAXS]; // Failure function
	int g[MAXS][MAXC]; // Goto function, or -1 if fail.
};
