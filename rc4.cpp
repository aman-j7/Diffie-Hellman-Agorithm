#include"hellman.h"
class RC4
{
    vector<int> s,t,key;
    int len;
      void Key_Stream_Generation()
    {
        int i,j=0,c=0,t;
        while(c<len)
        {
            i=(i+1)%256;
            j=(j+s[i])%256;
            swap(s[i],s[j]);
            t=(s[i]+s[j])%256;
            key.push_back(s[t]);
            c++;
        }
    }
    void Key_Scheduling()
    {
        int i,j;
        j=0;
        for(i=0; i<256; i++)
        {
            j=(j+s[i]+t[i])%256;
            swap(s[i],s[j]);
        }
        Key_Stream_Generation();
    }
    void Permutation(string msg)
    {
        len=msg.length();
        int m[len],i,j;
        for(i=0; i<len; i++)
            m[i]=msg.at(i);
        for(i=0; i<256; i++)
            s.push_back(i);
        j=0;
        for(i=0; i<256; i++)
        {
            if(j==len)
                j=0;
            t.push_back(m[j]);
            j++;
        }
        Key_Scheduling();
    }
public:
    vector<int> Encryption(string msg)
    {
        Permutation(msg);
        vector<int> cipher(len);
        for(int i=0; i<len; i++)
            cipher[i]=msg.at(i)^key[i];
        return cipher;
    }
    string Decryption(vector<int> cipher,vector<int> k)
    {
        string s;
        int i;
        for( i=0; i<k.size(); i++)
            s+=cipher[i]^k[i];
        return s;
    }
    vector<int> get_Key()
    {
        return key;
    }
};
int main()
{
    Deffie_Hellman::Init_n_alpha();
    Deffie_Hellman u1,u2;
    RC4 obj1,obj2;
    vector<int>Cipher,ac_Key,en_key,de_Key;
    string ac_data,de_data;
    int i;
    cout<<"\nEnter the Data : ";
    getline(cin,ac_data);

    cout<<"\n--------------RC4 Data Encryption-----------------\n"<<endl;
    cout<<"Plain Data     : "<<ac_data<<endl;
    Cipher=obj1.Encryption(ac_data);
    ac_Key=obj1.get_Key();
    cout<<"Cipher Text    : ";
    for(i=0; i<Cipher.size(); i++)
        cout<<Cipher[i]<<" ";
    cout<<endl;
    cout<<"Actual Key     : ";
    for(i=0; i<ac_Key.size(); i++)
        cout<<ac_Key[i]<<" ";
    cout<<endl;

    cout<<"\n-----------Deffie Hellman Key Encryption-----------\n"<<endl;
    en_key=u1.en_Key(u2.get_PK(),ac_Key);
    cout<<"Encrypted Key  : ";
    for(i=0; i<en_key.size(); i++)
        cout<<en_key[i]<<" ";
    cout<<endl;

    cout<<"\n-----------Deffie Hellman Key Decryption-----------\n"<<endl;
    de_Key=u2.de_Key(u1.get_PK(),en_key);
    cout<<"Decrypted Key  : ";
    for(i=0; i<de_Key.size(); i++)
        cout<<de_Key[i]<<" ";
    cout<<endl;

    cout<<"\n--------------RC4 Data Decryption-----------------\n"<<endl;
    de_data=obj2.Decryption(Cipher,de_Key);
    cout<<"Retrieved Data : "<<de_data<<endl;
    return 0;
}




