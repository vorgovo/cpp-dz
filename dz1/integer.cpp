#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

class big_integer
{
private:
    vector<unsigned int> v;
    bool pos;
public:
    big_integer()
    {
        pos = true;
        v.clear();
        v.push_back(0);
    }
    big_integer(big_integer &a)
    {
        pos = a.pos;
        v = a.v;
    }
    big_integer(int a)
    {
        //cerr << "!" << a << endl;
        pos = (a >= 0);
        v.clear();
        //v.push_back(abs((long long)a));
        v.push_back(abs(a));
    }
    big_integer(string s)
    {
        int d = 0;
        if (s[0] == '-')
        {
            pos = 0;
            d = 1;
        }
        else
        {
            pos = 1;
        }
        if (s[0] == '+')
            d = 1;
        v.clear();
        int i1 = (int)s.size();
        for (; i1 > d; i1 -= 32)
        {
            unsigned int a = 0;
            for (int i = -min(i1 - d, 32); i < 0; i++)
            {
                a = 10 * a + (s[i1 + i] - '0');
            }
            cerr << a << endl;
            v.push_back(a);
        }
    }
    void print()
    {
        if (pos)
            cout << "+";
        else
            cout << "-";
        for (int i = (int)v.size() - 1; i >= 0; i--)
            cout << v[i];
        cout << endl;
    }
    int get(int t)
    {
        if (t < (int)v.size())
            return v[t];
        else
            return 0;
    }
    big_integer abs()
    {
        big_integer b = (*this);
        b.pos = 1;
        return b;
    }
};

big_integer operator +(const big_integer &a, const big_integer &b)
{
    if (a.pos == b.pos)
    {
        big_integer c = new big_integer();
        c.pos = a.pos;
        c.v.pop_back();
        unsigned int d = 0;
        int i = 0;
        while (i < (int)a.v.size() || i < (int)b.v.size() || d > 0)
        {
            unsigned int x = a.get(i);
            unsigned int y = b.get(i);
            c.v.push_back(x + y + d);
            if (x + y + d <= x)
                d = 1;
            else
                d = 0;
            i++;
        }
        return c;
    }
    else
    {
        big_integer c = new big_integer();
        c.pop_back();
        int n = max(a.v.size(), b.v.size());
        bool big = true;
        for (int i = n - 1; i >= 0; i--)
        {
            int x = a.get(i);
            int y = b.get(i);
            if (x != y)
            {
                big = x > y;
                break;
            }
        }
        unsigned int d = 0;
        for (int i = 0; i < n; i++)
        {
            int x = a.get(i);
            int y = b.get(i);
            if (big)
            {
                c.push_back(x - y - d);
                if (x > y || (x == y && d == 0))
                    d = 0;
                else
                    d = 1;
            }
            else
            {
                c.push_back(y - x - d);
                if (y > x || (y == x && d == 0))
                    d = 0;
                else
                    d = 1;
            }
        }
        while (c.v.size() > 1 && c[c.v.size() - 1] == 0)
            c.v.pop_back();
        return c;
    }
}

big_integer operator *(const big_integer &a, const big_integer &b)
{
    big_integer c = new big_integer();
    c.pos = a.pos ^ b.pos;
    c.v.pop_back();
    int n = a.v.size() + b.v.size();
    vector<unsigned int> v;
    for (int i = 0; i < n; i++)
    {
        c.v.push_back(0);
        v.push_back(0);
    }
    for (int i = 0; i < (int)a.v.size(); i++)
    {
        for (int j = 0; j < (int)b.v.size(); j++)
        {
            unsigned long long mul = (unsigned long long)a.v[i] * b.v[j];
            unsigned int x = mul / ((unsigned long long)1 << 32);
            unsigned int y = mul % ((unsigned long long)1 << 32);
            if (c.v[i + j] + y < y)
                v[i + j]++;
            if (c.v[i + j + 1] + x < x)
                v[i + j + 1]++;
            c.v[i + j] += y;
            c.v[i + j + 1] += x;
        }
    }
    for (int i = 0; i + 1 < n; i++)
    {
        if (c.v[i + 1] + v[i] < v[i])
            v[i + 1]++;
        c.v[i + 1] += v[i];
    }
    while (c.v.size() > 1 && c.v[c.v.size() - 1] == 0)
        c.v.pop_back();
    return c;
}

big_integer operator /(const big_integer &a, const big_integer &b)
{
    big_integer c = new big_integer();
    c.pos = a.pos ^ b.pos;
    c.v.pop_back();
    int n = a.v.size() - b.v.size() + 1;
    for (int i = 0; i < n; i++)
    {

    }
}

big_integer operator -(const big_integer &a)
{
    big_integer b = a;
    b.pos ^= 1;
    return b;
}

big_integer operator -(const big_integer &a, const big_integer &b)
{
    return a + (-b);
}

int main()
{
    srand(3228);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    big_integer a(-2147483648);
    big_integer b("123456789012345678901234567890123");
    a.print();
    b.print();
    return 0;
}
