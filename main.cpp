#include "BigNum.cpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    BigNum num1("9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"); // length = 100
    BigNum num2("99999999999999999999999999999999999999999999999999"); // length = 50
    BigNum num3("+10000000");   // length = 8
    
    BigNum num4("-50000000");   // length = 8
    BigNum num5(8000000000ll);  // length = 10   
    BigNum num6("123456789");   // length = 9
    
    BigNum num7("99999");       // length = 5
    BigNum num8("-99999");      // length = 5
    BigNum num9("100");
    
    BigNum num10 = ".123";
    BigNum num11 = 1234;
    int m = 5;
    
    cout << "------------------------------------------------------Add----------------------------------------------------\n" << endl;
    cout << "num1 + 1 = " << num1 + 1 << endl;
    cout << "num4 + (-50000000) = " << num4 + (-50000000) << endl;
    cout << "num3 + num4 = " << num3 + num4 << endl;
    cout << "num4 + num5 = " << num4 + num5 << endl;
    cout << "num6 + num6 = " << num6 + num6 << endl;    // result = 246913578
    cout << "num9 += 5 -> num9 = " << (num9 += 5) << endl;
    cout << "m += num9 -> m = " << (m += num9) << endl;
   
    cout << "\n---------------------------------------------------Subtract-------------------------------------------------\n" << endl;
    cout << "num1 - num2 = " << num1 - num2 << endl;
    cout << "num3 - num4 = " << num3 - num4 << endl;
    cout << "num4 + (-50000000) = " << num4 + (-50000000) << endl;
    cout << "num6 - 246913578 = " << num6 - 246913578 << endl;
    cout << "num9 -= 5 -> num9 = " << (num9 -= 5) << endl;    
   
    cout << "\n---------------------------------------------------Multiply--------------------------------------------------\n" << endl;
    cout << "num7 * num7 = " << num7 * num7 << endl;    // result = 9999800001
    cout << "num4 * 25 = " << num4 * 25 << endl;        // result = -1250000000
    cout << "num4 * 0 = " << num4 * 0 << endl;
    cout << "num6 * 1 = " << num6 * 1 << endl;
    cout << "num7 * num8 = " << num7 * num8 << endl;    // result = -9999800001
    cout << "num8 * num8 = " << num8 * num8 << endl;    // result = 9999800001
    cout << "num9 *= 5 -> num9 = " << (num9 *= 5) << endl;     
    
    cout << "\n-----------------------------------------------Division & Mode-----------------------------------------------\n" << endl;
    try
    {
        cout << "num7 / num7 = " << num7 / num7 << endl;    
        cout << "num8 / 9 = " << num8 / 9 << endl;          
        cout << "num6 / 1 = " << num6 / 1 << endl;
        cout << "num4 / num5 = " << num5 / num4 << endl;
        cout << "0 / num7 = " << 0 / num7 << endl;
        cout << "num9 /= 5 -> num9 = " << (num9 /= 5) << endl;    
        cout << "num7 % num7 = " << num7 % num7 << endl;     
        cout << "num6 % num8 = " << num6 % num8 << endl; // result = 58023;
        cout << "num9 %= 5 -> num9 = " << (num9 %= 5) << endl;         
        cout << "num7 / 0 = " << num7 / 0 << endl;      
    }
    catch(exception& err)
    {
        cout << err.what() << endl;
    }    
    
    cout << "\n-----------------------------------------------OtherFunctions-----------------------------------------------\n" << endl;           
    cout << "BIGNUM10 = " << num10 << endl;
    
    cout << "SubscriptOperator :" << endl;
    
    for(int i = 1; i <= 10; ++i)
    {
        try
        {
            cout << "num6["<< i << "] = " << num6[i] << endl;
        }
        catch(exception& err)
        {
            cout << err.what() << endl;
        }
    }
    
    cout << "\nPrintWithThreeDelimeters :" << endl;
    cout << num3.printWithDelimeters() << endl;
    cout << num4.printWithDelimeters() << endl;
    cout << num6.printWithDelimeters() << endl;
    cout << "\nLogicalOperators :" << endl;
    
    if(num3 > num4)
        cout << num3 << " > " << num4 << endl;
    else 
        cout << num3 << " < " << num4 << endl;
    
    if(246913578 <= num6)
        cout << 246913578 << " <= " << num6 << endl;
    else 
        cout << 246913578 << " > " << num6 << endl;    
    
    if(num7 == num8)
        cout << num7 << " == " << num8 << endl;
    else 
        cout << num7 << " != " << num8 << endl;
    
}