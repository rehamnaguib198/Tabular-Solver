#include<iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <string.h>
using namespace std;
vector <vector<string> > minterms;
vector<string>temp;
vector<string>neglected;
vector<string>prime;
int countSetBits( int num)
{
    int count = 0;
    while (num)
    {
        // bitwise AND operation to check if the
        // leftmost bit is set or not
        // if set, increment the count
        count += num & 1;
        // left shift the nm by one position
        num >>= 1;
    }
    return count;
}
long long convertDecimalToBinary(int n)
{
    long long binaryNumber = 0;
    int remainder, i = 1, step = 1;

    while (n!=0)
    {
        remainder = n%2;
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}
int compare(string first,string second)
{
    int i=0,c=0;
    while (first[i]!='\0')
    {
        if (first[i] != second[i])
            c++;
        i++;
    }
    return c;
}
int diffindex(string first,string second)
{
    int i=0,index;
    while (first[i]!='\0')
    {
        if (first[i] != second[i])
        {
            index=i;
            return index;
        }
        else
        {
            i++;
        }
    }
}
int findx(string x)
{
    int flag=0;
    for(int i=0; i<neglected.size(); i++)
    {
        if(x==neglected[i])
        {
            flag=1;
            return 1;
        }
    }
    return flag;
}
int repInMin1(string x)
{
    int flag=0;
    for(int i=0; i<temp.size(); i++)
    {

        if(x==temp[i])
        {
            flag=1;
            return 1;
        }

    }
    return flag;
}
string toAlphabet(string y,int variable)
{
    string ans;
    for(int i=0; i<variable; i++)
    {
        if(y[i]=='1')
        {
            ans.push_back(65+i);
        }
        else if(y[i]=='0')
        {
            ans.push_back(65+i);
            ans.push_back('\'');
        }
    }
    return ans;
}
int main()
{
    unsigned int n,element,d;
    int numOfones;
    long long binElement;
    //-------------------------------minterms--------------------------------//
    cout<<"please enter number of variables";
    int variable;
    cin>>variable;
    while(variable ==0)
    {
        cout<<"please enter number of variables";
        cin>>variable;
    }
    cout<<"please enter number of minterms"<<endl;
    cin>>n;

    minterms.resize(variable+1);
    if(n != 0)
    {
        cout<<"please enter minterms"<<endl;
        for(int k=0; k<n; k++)
        {
            cin>>element;
            numOfones=countSetBits(element);
            binElement=convertDecimalToBinary(element);
            string strBinary;
            ostringstream convert;

            convert << binElement;

            strBinary = convert.str();
            int fr2=variable-strBinary.length();
            while(fr2>0)
            {
                strBinary = "0" + strBinary;
                fr2--;
            }
            minterms[numOfones].push_back(strBinary);
        }
    }
    //----------------------------------don't cares-------------------------------------//
    cout<<"please enter number of don't cares"<<endl;
    cin>>d;

    if(d!=0)
    {
        cout<<"please enter don't cares"<<endl;
        for(int k=0; k<d; k++)
        {
            cin>>element;
            numOfones=countSetBits(element);
            binElement=convertDecimalToBinary(element);
            string strBinarydc;
            ostringstream convert;

            convert << binElement;

            strBinarydc = convert.str();
            int fr2=variable-strBinarydc.length();
            while(fr2>0)
            {
                strBinarydc = "0" + strBinarydc;
                fr2--;
            }
            minterms[numOfones].push_back(strBinarydc);
        }
    }
    cout<<endl;
    int counter;
    int index;
    int check=0;
    while(check!=minterms.size())
    {
        for (int i = 0; i <minterms.size(); ++i)
        {
            cout<<"\n";
            cout<<"group";
            cout<<i<<"\t"; ;
            for(int j=0; j<minterms[i].size(); j++)
            {
                cout << minterms[i][j];
                cout<<" ";
            }
            cout<<"\n";
            cout<< "-------------------------------------";
        }
        check=0;
        for (int i = 0; i <minterms.size()-1; i++)
        {
            int next=i+1;
            for(int j=0; j<minterms[i].size(); j++)
            {
                for(int k=0; k<minterms[next].size(); k++)
                {
                    if(!minterms[next].empty()&&!minterms[i].empty()&& next<minterms.size())
                    {
                        int flag = findx(minterms[i][j]);
                        counter = compare(minterms[i][j],minterms[next][k]);

                        if(counter==1)
                        {
                            index =diffindex(minterms[i][j],minterms[next][k]);
                            string dup=minterms[i][j];
                            dup[index]='_';
                            int flag1=repInMin1(dup);
                            if(flag1==0)
                            {
                                temp.push_back(dup);
                            }
                            neglected.push_back(minterms[i][j]);
                            neglected.push_back(minterms[next][k]);
                        }
                    }
                }
                int flag = findx(minterms[i][j]);
                if(flag == 0)
                {
                    prime.push_back(minterms[i][j]);
                }
            }
            minterms[i].erase(minterms[i].begin(),minterms[i].end());
            if(i==minterms.size()-2)
            {
                for(int x=0; x<minterms[next].size(); x++)
                {
                    int flag = findx(minterms[next][x]);
                    if(flag == 0)
                    {
                        prime.push_back(minterms[next][x]);
                    }
                }
                minterms[minterms.size()-1].erase(minterms[minterms.size()-1].begin(),minterms[minterms.size()-1].end());
            }
            if(!temp.empty())
            {
                for(int z=0; z<temp.size(); z++)
                {
                    minterms[i].push_back(temp[z]);
                }
                temp.erase(temp.begin(),temp.end());
            }
        }
        cout<<endl<<"---------------------------------------------------------"<<endl;
        for(int a=0; a<minterms.size(); a++)
        {
            if(minterms[a].empty())
            {
                check++;
            }
        }
    }
//-------------------------------------------Final answer---------------------------------------//
    cout<<endl<<"---------------------------Finally-----------------------"<<endl;
    cout<<"---------------------PRIME IMPLICANTS ARE:------------------"<<endl;
    for (int i = 0; i <prime.size(); ++i)
    {
        cout << toAlphabet(prime[i],variable);
        cout<<"\n";
    }
    return 0;
}
