//#include<iostream>
//using namespace std;
//
//void E();
//void E_dash();
//void T();
//void T_dash();
//void F();
//void getNextToken();
//void errorHandler();
//string input = ")v+*n$";
//int f = 0;
//char C_T = input[0];
//
//int main()
//{
//	E();
//	if (C_T == '$')
//		cout << "Successfully Executed\n";
//	else
//		cout << "Syntax Error found\n";
//	return 0;
//}
//
//void E()
//{
//	switch (C_T)
//	{
//	case '(':
//	case 'v':
//	case 'n':
//		T();
//		E_dash();
//		break;
//	default:
//		errorHandler();
//		break;
//	}
//}
//
//void E_dash()
//{
//	switch (C_T)
//	{
//	case '+':
//	case '-':
//		getNextToken();
//		T();
//		E_dash();
//		break;
//	case ')':
//	case '$':
//		break;
//	default:
//		errorHandler();
//		break;
//	}
//}
//
//void T()
//{
//	switch (C_T)
//	{
//	case '(':
//	case 'v':
//	case 'n':
//		F();
//		T_dash();
//		break;
//	default:
//		errorHandler();
//		break;
//	}
//}
//
//void T_dash()
//{
//	switch (C_T)
//	{
//	case '*':
//	case '/':
//		getNextToken();
//		F();
//		T_dash();
//		break;
//	case '+':
//	case '-':
//	case ')':
//	case '$':
//		break;
//	default:
//		errorHandler();
//		break;
//	}
//}
//
//void F()
//{
//	switch (C_T)
//	{
//	case '(':
//		getNextToken();
//		E();
//		if (C_T == ')')
//			getNextToken();
//		else
//			errorHandler();
//		break;
//	case 'v':
//		getNextToken();
//		break;
//	case 'n':
//		getNextToken();
//		break;
//	default:
//		errorHandler();
//		break;
//	}
//}
//
//void getNextToken()
//{
//	f = f + 1;
//	C_T = input[f];
//}
//
//void errorHandler()
//{
//	cout << "Syntax Error found\n";
//	exit(0);
//}