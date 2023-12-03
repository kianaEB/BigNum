#ifndef BIGNUM_H
#define BIGNUM_H
#include <string>

#pragma once

class BigNum
{
    friend std::ostream& operator<<(std::ostream&, const BigNum&);
    friend std::istream& operator>>(std::istream&, BigNum&);
    
    friend BigNum operator+(const BigNum&, const BigNum&);
    friend BigNum operator-(const BigNum&, const BigNum&);
    friend BigNum operator*(const BigNum&, const BigNum&);
    friend BigNum operator/(const BigNum&, const BigNum&);
    friend BigNum operator%(const BigNum&, const BigNum&);
    
    friend bool operator<(const BigNum&, const BigNum&);
    friend bool operator<=(const BigNum&, const BigNum&);
    friend bool operator>(const BigNum&, const BigNum&);
    friend bool operator>=(const BigNum&, const BigNum&);            
    friend bool operator==(const BigNum&, const BigNum&);
    friend bool operator!=(const BigNum&, const BigNum&); 
    
    friend long long operator+=(long long&, const BigNum&);
    friend long long operator-=(long long&, const BigNum&);
    friend long long operator*=(long long&, const BigNum&);
    friend long long operator/=(long long&, const BigNum&);
    friend long long operator%=(long long&, const BigNum&); 

    friend long int operator+=(long int&, const BigNum&);
    friend long int operator-=(long int&, const BigNum&);
    friend long int operator*=(long int&, const BigNum&);
    friend long int operator/=(long int&, const BigNum&);
    friend long int operator%=(long int&, const BigNum&);           

    friend int operator+=(int&, const BigNum&);
    friend int operator-=(int&, const BigNum&);
    friend int operator*=(int&, const BigNum&);
    friend int operator/=(int&, const BigNum&);
    friend int operator%=(int&, const BigNum&);           

public:
    explicit BigNum(std::string = "");
    BigNum(const long long);
    BigNum(const long int);
    BigNum(const int);
    BigNum(const char*);
    ~BigNum();

    void setNum(std::string);
    const std::string& getNum() const;
   
    BigNum& operator+=(const BigNum&);
    BigNum& operator-=(const BigNum&);
    BigNum& operator*=(const BigNum&);
    BigNum& operator/=(const BigNum&);
    BigNum& operator%=(const BigNum&);
    
    char& operator[](const int);
    const char& operator[](const int) const;

    std::string printWithDelimeters() const;

private:
    std::string bigNum;
    BigNum add(const BigNum&, const BigNum&) const;
    BigNum subtract(const BigNum&, const BigNum&) const;
    static bool negativeOrPositive(const BigNum&, const BigNum&, BigNum&, BigNum&);
};

#endif