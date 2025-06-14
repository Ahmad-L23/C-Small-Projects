
#include <iostream>
#include"MyLib.h";

using namespace std;

int main()
{
    cout << "Weclome " << MyLib::ReadString("Enter Your Name") << endl;
    cout << MyLib::MyPowerFunc(7,5);
}

