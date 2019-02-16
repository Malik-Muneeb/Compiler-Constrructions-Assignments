//#include<iostream>
//#include<stack>
//#include<string>
//using namespace std;
//
////e stands for empty, s stands for syn, ^ stands for null
////I replace E` and T` with D and S respectively for stack handling
//
//string table[5][9] = { {"TD", "TD", "e", "e", "e", "e", "TD","s","s"},
//						{ "e", "e", "+TD", "e", "-TD", "e", "e", "^", "^"},
//						{ "FS", "FS", "s", "e", "s", "e", "FS", "s", "s" },
//						{ "e", "e", "^", "*FS", "^", "/FS", "e", "^", "^" },
//						{ "v", "n", "s", "s", "s", "s", "(E)", "s", "s" }	};
//
//char row[5] = { 'E', 'D', 'T', 'S','F' };
//char col[9] = { 'v','n','+','*','-','/','(',')','$' };
//void getInput();
//string input;	char c_t;	int f = 0;
//stack<char> stk;
//bool parsing();
//string error = "";
//int getRowNum(char);
//int getColNum(char);
//void getNextToken();
//void errorRecord();
//void replaceInverse(string);
//void displayError();
//
//int main()
//{
//	getInput();
//	if (parsing())
//		displayError();
//	else
//		cout << "\nSyntax is correct\n\n";
//	return 0;
//}
//
//void getInput()
//{
//	cout << "Enter Your Input: ";
//	getline(cin, input);
//	input = input + "$";
//	c_t = input[f];
//	stk.push('$');
//	if (c_t != '$')
//		stk.push('E');
//}
//
//bool parsing()
//{
//	bool isError = false;
//	while (c_t != '$' || stk.top() != '$')
//	{
//		char top = stk.top();
//		int rowNum = getRowNum(top);
//		if (rowNum >= 0)
//		{
//			int colNum = getColNum(c_t);
//			string tableVal = table[rowNum][colNum];
//			if (tableVal == "^")
//				stk.pop();
//			else if (tableVal == "e" || tableVal == "s")
//			{
//				isError = true;
//				errorRecord();
//			}
//			else
//				replaceInverse(tableVal);
//		}
//		else if (top == c_t)
//		{
//			stk.pop();
//			getNextToken();
//		}
//		else
//		{
//			isError = true;
//			errorRecord();
//		}
//	}
//	return isError;
//}
//
//int getRowNum(char ch)
//{
//	for (int i = 0; i < 5; i++)
//	{
//		if (row[i] == ch)
//			return i;
//	}
//	return -1;
//}
//
//int getColNum(char ch)
//{
//	for (int i = 0; i < 9; i++)
//	{
//		if (col[i] == ch)
//			return i;
//	}
//	return -1;
//}
//
//void getNextToken()
//{
//	f = f + 1;
//	c_t = input[f];
//}
//
//void replaceInverse(string tableVal)
//{
//	int strLen = tableVal.length();
//	char charArr[4];
//	strcpy_s(charArr, tableVal.c_str());
//	stk.pop();
//	stack<char> stk1;
//	for (int i = 0; i < strLen; i++)
//		stk1.push(charArr[i]);
//	for (int i = 0; i < strLen; i++)
//	{
//		stk.push(stk1.top());
//		stk1.pop();
//	}
//}
//
//void errorRecord()
//{
//	error = error + c_t;
//	getNextToken();
//}
//
//void displayError()
//{
//	cout << "\nSyntax is INCORRECT\n\nError Found at these characters\n\n";
//	cout << " ------------------------------- \n";
//	for (int i = 0; i < error.length(); i++)
//		cout<<"| Error # "<< i+1 << "\t|\t" << error[i] << "\t|\n";
//	cout << " ------------------------------- \n";
//}