#include "BigNum.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

BigNum::BigNum(string number)
{
    if(number[0] == '.' || (number[0] == '-' && number[1] == '.'))
        number = "0";
    else
    {
        for(int i = 0; number[i]; ++i)
        if(number[i] == '.')
        {    
            number = number.substr(0, i);
            break;
        }
    }        
    setNum(number);
}

BigNum::BigNum(const long long number)
{
    string temp = to_string(number);
    setNum(temp);
}

BigNum::BigNum(const long number)
{
    string temp = to_string(number);
    setNum(temp);
}

BigNum::BigNum(const int number)
{
    string temp = to_string(number);
    setNum(temp);
}

BigNum::BigNum(const char* number)
{
    string temp = "";  
    
    if(number[0] == '.' || (number[0] == '-' && number[1] == '.'))
        temp = "0";    
    else
    {
        for(int i = 0; number[i] && number[i] != '.'; ++i)
        {
            temp += number[i];
            if(number[i - 1] == '.')
                break;
        }        
    }    
    setNum(temp);    
}

BigNum::~BigNum() { }


void BigNum::setNum(string thing)
{
    if(thing[0] == '+')
        thing = thing.substr(1);
    bigNum = thing;
}

const string& BigNum::getNum() const { return bigNum ;}


BigNum BigNum::add(const BigNum& num1, const BigNum& num2) const
{
    int carry = 0, sum;
    BigNum newNum;
    string temp1, temp2;

    int length1 = num1.bigNum.length() >= num2.bigNum.length() ? num1.bigNum.length() : num2.bigNum.length();
    int length2 = num1.bigNum.length() < num2.bigNum.length() ? num1.bigNum.length() : num2.bigNum.length(); 
    
    if(num1.bigNum.length() >= num2.bigNum.length())
    {
        temp1 = string(num1.bigNum.rbegin(), num1.bigNum.rend());
        temp2 = string(num2.bigNum.rbegin(), num2.bigNum.rend());
    }
    else
    {
        temp1 = string(num2.bigNum.rbegin(), num2.bigNum.rend());
        temp2 = string(num1.bigNum.rbegin(), num1.bigNum.rend());
    } 

    for(int i = 0; i < length2; ++i)
    {
        sum = (temp1[i] - '0') + (temp2[i] - '0');
        if(carry)
            sum += carry;           
        newNum.bigNum += (sum % 10) + '0';
        carry = sum / 10;
    }
    if(length1 == length2 && carry != 0)
    {
        newNum.bigNum += carry + '0';
    }
    else
    {
        for(int i = length2; i < length1; ++i)
        {
            sum = (temp1[i] - '0');
            if(carry)
                sum += carry;  
            newNum.bigNum += (sum % 10) + '0';  
            carry = sum / 10;               
        }
        if(carry)
            newNum.bigNum += carry + '0';
    }

    newNum.bigNum = string(newNum.bigNum.rbegin(), newNum.bigNum.rend());    
    return newNum;
}

BigNum BigNum::subtract(const BigNum& num1, const BigNum& num2) const
{
    int change, sum, carrier, is_negative = 0;
    string temp1, temp2;
    BigNum newNum;

    int length1 = num1.bigNum.length() >= num2.bigNum.length() ? num1.bigNum.length() : num2.bigNum.length();
    int length2 = num1.bigNum.length() < num2.bigNum.length() ? num1.bigNum.length() : num2.bigNum.length();
    
    if(num1.bigNum.length() >= num2.bigNum.length())
    {
        temp1 = string(num1.bigNum.rbegin(), num1.bigNum.rend());
        temp2 = string(num2.bigNum.rbegin(), num2.bigNum.rend());
    }
    else
    {
        temp1 = string(num2.bigNum.rbegin(), num2.bigNum.rend());
        temp2 = string(num1.bigNum.rbegin(), num1.bigNum.rend());
        is_negative = 1;
    }    

    if(num2.bigNum > num1.bigNum && length1 == length2)
    {
        string temp(temp1);
        temp1 = temp2;
        temp2 = temp;
        is_negative = 1;
    }


    for(int i = 0; i < length2; ++i)
    {
        change = (temp1[i] - '0') - (temp2[i] - '0');
        if(change < 0)
        {
            change += 10;
            carrier = i + 1;
            while(temp1[carrier] == '0')
            {
                ++carrier;
            }
            --temp1[carrier];
            --carrier;
            while(carrier != i)
            {
                temp1[carrier] += 9;
                --carrier;
            }
        }
        newNum.bigNum += (change + '0');
    }
    if(length1 != length2)
    {    
        for(int i = length2; i < length1; ++i)
                newNum.bigNum += temp1[i];
    } 
        newNum.bigNum = string(newNum.bigNum.rbegin(), newNum.bigNum.rend());
        if(newNum.bigNum[0] == '0')
        {
            int count = 1;
            while(newNum.bigNum[count] == '0')
                ++count;
            if(count != newNum.bigNum.length())    
                newNum.bigNum = newNum.bigNum.substr(count);
            else    
                newNum.bigNum = '0';    
        }
        if(is_negative)
        {
            newNum.bigNum = string(newNum.bigNum.rbegin(), newNum.bigNum.rend());
            newNum.bigNum += "-";
            newNum.bigNum = string(newNum.bigNum.rbegin(), newNum.bigNum.rend());
        }
        return newNum; 
}

bool BigNum::negativeOrPositive(const BigNum& left, const BigNum& right, BigNum& t1, BigNum& t2)
{
    bool is_negative = false;
    if(left.bigNum[0] == '-' && right.bigNum[0] != '-')
    {       
        is_negative = true;
        t1.bigNum = left.bigNum.substr(1);
        t2.bigNum = right.bigNum;
    }
    else if(left.bigNum[0] != '-' && right.bigNum[0] == '-')
    {       
        is_negative = 1;
        t1.bigNum = left.bigNum;
        t2.bigNum = right.bigNum.substr(1);
    }
    else if(left.bigNum[0] == '-' && right.bigNum[0] == '-')
    {       
        t1.bigNum = left.bigNum.substr(1);
        t2.bigNum = right.bigNum.substr(1);
    }    
    else
    {
        t1.bigNum = left.bigNum;
        t2.bigNum = right.bigNum;       
    }
    return is_negative;
}


BigNum& BigNum::operator+=(const BigNum& other)
{
    (*this) = (*this) + other;
    return (*this);
}

BigNum& BigNum::operator-=(const BigNum& other)
{
    (*this) = (*this) - other;
    return (*this);
}

BigNum& BigNum::operator*=(const BigNum& other)
{
    (*this) = (*this) * other;
    return (*this);
}

BigNum& BigNum::operator/=(const BigNum& other)
{
    (*this) = (*this) / other;
    return (*this);
}

BigNum& BigNum::operator%=(const BigNum& other)
{
    (*this) = (*this) % other;
    return (*this);
}


char& BigNum::operator[](int idx)
{
    int length = this->bigNum.length();
    if(idx >= 1 && idx <= length && this->bigNum[length - idx] != '-')
        return this->bigNum[length - idx];
    else
        throw(out_of_range("index out of range!"));    
}

const char& BigNum::operator[](int idx) const
{
    int length = this->bigNum.length();
    if(idx >= 1 && idx <= length && this->bigNum[length - idx] != '-')
        return this->bigNum[length - idx];
    else
        throw(out_of_range("index out of range!"));    
}


string BigNum::printWithDelimeters() const
{
    string final = "";
    BigNum temp = (*this);
    
    if(temp.bigNum[0] == '-')
        temp.bigNum = temp.bigNum.substr(1);
    
    int length = temp.bigNum.length();
    for(int i = length - 1; i >= 0; --i)
    {
        final += temp.bigNum[i];  
        if(length > 3 && (length - i) >= 3 && (length - i) % 3 == 0 && 
           (i != 0) && (this->bigNum[i] != '-' && this->bigNum[i] != '+'))
            final += ",";  
    }
    if(this->bigNum[0] == '-')
        final += "-";
    return string(final.rbegin(), final.rend());
}


ostream& operator<<(ostream& output, const BigNum& b)
{
    output << b.getNum();
    return output;
}

istream& operator>>(istream& input, BigNum& b)
{
    input >> b.bigNum;
    return input;
}


BigNum operator-(const BigNum& left, const BigNum& right)
{
    if(right.bigNum[0] == '-' && left.bigNum[0] == '-')
    {
        BigNum temp1, temp2;
        temp1.bigNum = right.bigNum.substr(1);
        temp2.bigNum = left.bigNum.substr(1);
        return temp1.subtract(temp1, temp2);
    }
    else if(right.bigNum[0] == '-')
    {
        BigNum temp1;
        temp1.bigNum = right.bigNum.substr(1);
        return left.add(left, temp1);
    }
    else if(left.bigNum[0] == '-')
    {
        BigNum temp2, temp;
        temp2.bigNum = left.bigNum.substr(1);
        temp = temp.add(right, temp2);
        temp.bigNum = string(temp.bigNum.rbegin(), temp.bigNum.rend());
        temp.bigNum += '-';
        temp.bigNum = string(temp.bigNum.rbegin(), temp.bigNum.rend());
        return temp;        
    }
    else
        return left.subtract(left, right);
}

BigNum operator+(const BigNum& left, const BigNum& right)
{
    if(left.bigNum[0] == '-'  && right.bigNum[0] == '-')
    {
        BigNum temp1, temp2, temp3;
        temp1.bigNum = right.bigNum.substr(1);
        temp2.bigNum = left.bigNum.substr(1);
        temp3 = temp3.add(temp1, temp2);
        temp3.bigNum = string(temp3.bigNum.rbegin(), temp3.bigNum.rend());
        temp3.bigNum += '-';
        temp3.bigNum = string(temp3.bigNum.rbegin(), temp3.bigNum.rend());
        return temp3;        
    }
    else if(left.bigNum[0] == '-')
    {
        BigNum temp2;
        temp2.bigNum = left.bigNum.substr(1);        
        return left.subtract(right, temp2);
    }

    else if(right.bigNum[0] == '-')
    {
        BigNum temp1;
        temp1.bigNum = right.bigNum.substr(1);
        return left.subtract(left, temp1);
    }
    else
        return left.add(left, right);
}

BigNum operator*(const BigNum& left, const BigNum& right)
{
    BigNum result("0"), temp;
    int is_negative = 0, carry = 0, multiply;
    string s_left, s_right;
    
    if(left.bigNum[0] == '-' && right.bigNum[0] != '-')
    {       
        is_negative = 1;
        s_left = left.bigNum.substr(1);
        s_right = right.bigNum;
    }
    else if(left.bigNum[0] != '-' && right.bigNum[0] == '-')
    {       
        is_negative = 1;
        s_left = left.bigNum;
        s_right = right.bigNum.substr(1);
    }
    else if(left.bigNum[0] == '-' && right.bigNum[0] == '-')
    {       
        s_left = left.bigNum.substr(1);
        s_right = right.bigNum.substr(1);
    }    
    else
    {
        s_left = left.bigNum;
        s_right = right.bigNum;       
    }   

    for(int i = s_left.length() - 1; i >= 0; --i)
    {
        temp.bigNum = "";
        carry = 0;
        for(int k = i; k < s_left.length() - 1; ++k)
            temp.bigNum += '0';
        
        for(int j = s_right.length() - 1; j >= 0; --j)
        {
            multiply = ((s_left[i] - '0') * (s_right[j] - '0')) + carry;
            temp.bigNum += (multiply % 10) + '0';
            carry = multiply / 10;
        }
        if(carry)
            temp.bigNum += carry + '0';
        temp.bigNum = string(temp.bigNum.rbegin(), temp.bigNum.rend());   
        result = result.add(result, temp);    
    }
    if(result.bigNum[0] == '0')
    {
        result.bigNum = '0';
        return result;
    }
    if(is_negative)
    {    
        result.bigNum = string(result.bigNum.rbegin(), result.bigNum.rend());
        result.bigNum += "-";
        result.bigNum = string(result.bigNum.rbegin(), result.bigNum.rend()); 
    }
    return result;           
}

BigNum operator/(const BigNum& left, const BigNum& right)
{
    if(right.bigNum[0] == '0')
        throw(invalid_argument("(invalid) 0 can not be a divisor.")); 
    BigNum result, temp;
    static BigNum dividend, divisor;
    int idx = 0, remainder;
    bool is_negative;

    is_negative = BigNum::negativeOrPositive(left, right, dividend, divisor);
    
    temp.bigNum = dividend.bigNum[idx];
    while(dividend.bigNum.length() > idx)
    {      
        while(temp < divisor && dividend.bigNum.length() - 1 > idx)
        { 
            if(temp.bigNum[0] == '0')
            {    
                if(dividend.bigNum[idx + 1] != '0')
                {
                    temp.bigNum = "";
                    temp.bigNum += dividend.bigNum[++idx];
                }
                else
                    ++idx; 
            }        
            else      
                temp.bigNum += dividend.bigNum[++idx];
            
            if(result.bigNum != "" && dividend.bigNum.length() > idx)
                result.bigNum += '0';        
        }
        for(remainder = 0; temp >= divisor; ++remainder)
        {
            temp = temp.subtract(temp, divisor);
        }
        if(remainder)
            result.bigNum += remainder + '0';
        if(idx < (dividend.bigNum.length() - 1))
        {
            if(temp.bigNum[0] != '0')    
                temp.bigNum += dividend.bigNum[++idx];
            else
            {
                temp.bigNum[0] = dividend.bigNum[++idx];
                if(result.bigNum != "" && dividend.bigNum.length() > idx && temp < divisor)
                    result.bigNum += '0';                    
            }                             
        }
        else
            break;    
    }
    if(is_negative)
    {    
        result.bigNum = string(result.bigNum.rbegin(), result.bigNum.rend());
        result.bigNum += "-";
        result.bigNum = string(result.bigNum.rbegin(), result.bigNum.rend()); 
    }
    if(result.bigNum == "")
        result.bigNum = '0';
    return result;            
}

BigNum operator%(const BigNum& left, const BigNum& right)
{
    if(right.bigNum[0] == '0')
        throw(invalid_argument("(invalid) 0 can not be a divisor."));    
    BigNum temp = (left / right) * right;
    return left - temp;
}


bool operator<(const BigNum& left, const BigNum& right)
{
    if((right.bigNum[0] != '-' && left.bigNum[0] == '-') ||
       (right.bigNum[0] == '-' && left.bigNum[0] != '-'))
    {
        return left.bigNum[0] == '-';
    }   
    
    else if(right.bigNum[0] == '-' && left.bigNum[0] == '-')
    {
       if(right.bigNum.length() == left.bigNum.length()) 
            return left.bigNum > right.bigNum;
        else
            return right.bigNum.length() < left.bigNum.length();    
    }
    
    else 
    {
        if(right.bigNum.length() == left.bigNum.length())
            return left.bigNum < right.bigNum;
        else
            return right.bigNum.length() > left.bigNum.length();
    }                
}

bool operator<=(const BigNum& left, const BigNum& right)
{
    if((right.bigNum[0] != '-' && left.bigNum[0] == '-') ||
       (right.bigNum[0] == '-' && left.bigNum[0] != '-'))
    {
        return left.bigNum[0] == '-';
    }   
    
    else if(right.bigNum[0] == '-' && left.bigNum[0] == '-')
    {
       if(right.bigNum.length() == left.bigNum.length()) 
            return left.bigNum >= right.bigNum;
        else
            return right.bigNum.length() <= left.bigNum.length();    
    }
    
    else 
    {
        if(right.bigNum.length() == left.bigNum.length())
            return left.bigNum <= right.bigNum;
        else
            return right.bigNum.length() >= left.bigNum.length();
    }    
}

bool operator>(const BigNum& left, const BigNum& right)
{
    return !(left <= right);
}

bool operator>=(const BigNum& left, const BigNum& right)
{
    return !(left < right);
}

bool operator==(const BigNum& left, const BigNum& right)
{
    return left.bigNum == right.bigNum;
}

bool operator!=(const BigNum& left, const BigNum& right)
{
    return left.bigNum != right.bigNum;
}


long long operator+=(long long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft += right;
        if(newLeft >= 9223372036854775807ll || newLeft <= -9223372036854775807ll) 
            throw(out_of_range("the number is out of Long Long range!")); 
        left = stoll(newLeft.bigNum); 
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }           
}

long long operator-=(long long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft -= right;
        if(newLeft >= 9223372036854775807ll || newLeft <= -9223372036854775807ll) 
            throw(out_of_range("the number is out of Long Long range!"));    
        left = stoll(newLeft.bigNum); 
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }             
}

long long operator*=(long long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft *= right;
        if(newLeft >= 9223372036854775807ll || newLeft <= -9223372036854775807ll) 
            throw(out_of_range("the number is out of Long Long range!"));    
        left = stoll(newLeft.bigNum); 
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }           
}

long long operator/=(long long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft /= right;
        if(newLeft >= 9223372036854775807ll || newLeft <= -9223372036854775807ll) 
            throw(out_of_range("the number is out of Long Long range!"));    
        left = stoll(newLeft.bigNum); 
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }          
}

long long operator%=(long long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft %= right;
        if(newLeft >= 9223372036854775807ll || newLeft <= -9223372036854775807ll) 
            throw(out_of_range("the number is out of Long Long range!"));    
        left = stoll(newLeft.bigNum); 
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }          
} 


long operator+=(long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft += right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));
        else
        {    
            left = stoi(newLeft.bigNum); 
            return left;
        }
    }    
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }           
}

long operator-=(long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft -= right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));
        else
        {    
            left = stoi(newLeft.bigNum); 
            return left;
        }
    }    
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }             
}

long operator*=(long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft *= right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));
        else
        {    
            left = stoi(newLeft.bigNum); 
            return left;
        }
    }    
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }           
}

long operator/=(long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft /= right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));
        else
        {    
            left = stoi(newLeft.bigNum); 
            return left;
        }
    }    
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }          
}

long operator%=(long& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft %= right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));
        else
        {    
            left = stoi(newLeft.bigNum); 
            return left;
        }
    }    
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }           
} 
  

int operator+=(int& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft += right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));
        else
        {    
            left = stoi(newLeft.bigNum); 
            return left;
        }
    }    
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }          
}

int operator-=(int& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft -= right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));    
        left = stoi(newLeft.bigNum); 
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }             
}

int operator*=(int& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft *= right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));    
        left = stoi(newLeft.bigNum); 
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }           
}

int operator/=(int& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft /= right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));    
        left = stoi(newLeft.bigNum);
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }          
}

int operator%=(int& left, const BigNum& right)
{
    try
    {
        BigNum newLeft(left);
        newLeft %= right;
        if(newLeft > 2147483647 || newLeft < -2147483647) 
            throw(out_of_range("the number is out of Int range!"));    
        left = stoi(newLeft.bigNum); 
        return left;
    }
    catch(const out_of_range& err)
    {
        cout << err.what() << endl;
    }          
} 
  