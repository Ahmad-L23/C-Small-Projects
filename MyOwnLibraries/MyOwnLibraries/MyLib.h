#pragma once
#include<iostream>
using namespace std;
namespace MyLib
{
	string ReadString(string message)
	{
		string input = "";
		cout << message << endl;
		cin >> input;
		return input;
	}


	float MyPowerFunc(float base, float exponent)
	{
		float result = 1;
		bool isNegative = false;
		if (exponent < 0)
		{
			exponent *= -1;
			isNegative = true;
		}

		for (int i = 1; i <= exponent; i++)
		{
			result *= base;
		}
		return isNegative ? 1 / result : result;
	}
}