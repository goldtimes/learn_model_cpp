// 寻找质数

#include <algorithm>
#include <iostream>
#include <list>
#include <cmath>
using namespace std;


bool isPrime(int value)
{
    auto number = abs(value);
    if (number == 0 || number == 1)
    {
        return false;
    }

    int divisor; 
    for (divisor = number/2; number % divisor !=0; --divisor)
    {
      // divisor = 将需判断的数/2
      // number % divisor == 0 ->不是质数
      // divisor--;
      // if divisor == 1, 则是质数
    }
    return divisor == 1;
}

int main()
{
    list<int> coll;

    for(int i = 20; i < 30; ++i)
    {
        coll.push_back(i);
    }

    auto find_it = find_if(coll.begin(), coll.end(), isPrime);
    if (find_it != coll.end())
    {
        cout << *find_it << " is first prime number found." << endl;
    }
    else 
    {
        cout << "no prime number found" << endl;
    }
    return 0;
}