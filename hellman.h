#include<iostream>
#include<vector>
#include<unordered_set>
#include<math.h>
using namespace std;
bool Prime(int n)
{
    for(int i=2; i<=sqrt(n); i++)
        if(n%i==0)
            return true;
    return false;
}
int binPow( int a,int b, int c)
{
    a%=c;
    int res=1;
    while(b>0)
    {
        if(b&1)
            res=(res*a)%c;
        a=(a*a)%c;
        b>>=1;
    }
    return res;
}
void findPrimefactors(unordered_set<int> &s, int n)
{
    while (n%2 == 0)
    {
        s.insert(2);
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        while (n%i == 0)
        {
            s.insert(i);
            n = n/i;
        }
    }
    if (n > 2)
        s.insert(n);
}
class Deffie_Hellman
{
    static int n,alpha;
    int x,y;
    static void genPrime()
    {
        n=rand()%256+256;
        if(n%2==0)
            ++n;
        while(Prime(n))
            n+=2;
    }
    static void findPrimitive()
    {
        unordered_set<int> s;
        int phi = n-1;
        findPrimefactors(s, phi);
        for (int r=2; r<=phi; r++)
        {
            bool flag = false;
            for (auto it = s.begin(); it != s.end(); it++)
            {
                if (binPow(r, phi/(*it), n) == 1)
                {
                    flag = true;
                    break;
                }
            }
            if (flag == false)
            {
                alpha= r;
                break;
            }
        }
    }
    void gen_Key()
    {
        x=(rand()%256)+1;
        y=binPow(alpha,x,n);
    }
    int sec_Key(int k)
    {
        return binPow(k,x,n);
    }
public:
    Deffie_Hellman()
    {
        gen_Key();
    }
    static void Init_n_alpha()
    {
        genPrime();
        findPrimitive();
    }
    vector<int> en_Key(int k,vector<int> v)
    {
        int j=sec_Key(k);
        for(int i=0; i<v.size(); i++)
            v[i]+=j;
        return v;
    }
    vector<int> de_Key(int k,vector<int> v)
    {
        int j=sec_Key(k);
        for(int i=0; i<v.size(); i++)
            v[i]-=j;
        return v;
    }
    int get_PK()
    {
        return y;
    }
};
int Deffie_Hellman::alpha;
int Deffie_Hellman::n;
