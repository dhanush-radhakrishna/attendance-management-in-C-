#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<math.h>
using namespace std;
ofstream pt;
class subject
{
   int hrs,hra,hrb=0,req=0,i;
   string name;
   float curr,fa,minim;
   public:
       subject()
       {
       }
       int skip(int,int);
       void fine();
       void printtofile();

       void subject1(int x1,float x2,string str1)
       {
            hrs=x1;
            minim=x2;
            name=str1;
       }
       void display()
       {
           cout<<"         SUBJECT DETAILS       "<<endl;
           cout<<"Subject name = "<<name<<endl;
           cout<<"Minimum percentage = "<<minim<<endl;
           cout<<"Number of hours in a week = "<<hrs<<endl<<endl;
           cout<<"         ANALYSIS              "<<endl;
           cout<<"Current percentage = "<<curr<<endl;
           if(curr<minim)
                fine();
           else
                cout<<"You are eligible :) "<<endl;
       }
       void getpercent()
       {
             int attend=0,ta=0,j=0;
             i=0;
             string check[1000];
            char reply;
            cout<<"Number of hours of "<<name<<" in one week = "<<hrs<<endl;
            /*ifstream rt;
            rt.open("result.txt");
            if(rt.eof()==0)
            {
                cout<<"entered result"<<endl;
                while(!rt.eof())
                {
                    rt >> check[j];
                    if(check[j]==name)
                    {
                        rt >> i;
                        break;
                    }
                    else
                    {
                        j++;
                        continue;
                    }
                }

            }
            cout<<"from check, name="<<check[j]<<"i="<<i;*/
            do
            {
                i++;
                cout<<"Enter the number of classes attended in week "<<i<<endl;
                cin>>attend;
                ta=ta+attend;
                curr=((float)ta/(hrs*i))*100;
                cout<<"your current attendance percentage is = "<<curr<<"%"<<endl;
                if(curr<minim && i>=3)
                {
                    req=((float)minim/100)*(hrs*(i+1))-ta;
                    cout<<"You need to attend "<<req<<" hours  in the next week to cover up your attendance "<<endl;
                }
                if(curr>minim && i>=3)
                {
                    cout<<"you can miss out "<<skip(ta,i)<<" hours in the next week"<<endl;
                }
                cout<<"Do you want to enter next week ? (Y/N)"<<endl;
                cin>>reply;
                cout<<"--------------------------------------------------"<<endl;
            }while(reply!='n');
            if(curr<minim)
                fine();
            cout<<"--------------------------------------------------"<<endl;
       }
};
 void subject :: fine()
{
    switch(((int)curr/10)*10)
    {
    case 70:
        cout<<"your fine amount ="<<((minim-curr)*200)<<endl;
        fa=(minim-curr)*200;
        break;
    case 60:
        cout<<"your fine amount ="<<((minim-curr)*300)<<endl;
        fa=(minim-curr)*300;
        break;
    case 50:
        cout<<"your fine amount ="<<((minim-curr)*400)<<endl;
        fa=(minim-curr)*400;
        break;
    case 40:
        cout<<"your fine amount ="<<((minim-curr)*500)<<endl;
        fa=(minim-curr)*500;
        break;
    default: cout<<"SORRY YOUR IN FASTRACK !! "<<endl;
    }
}
int subject :: skip(int y1,int y2)
{
    hrb= ((hrs*(y2+1))*(float)minim/100)-y1;
    hrb=hrb+1;
    return hrb;
}
void subject :: printtofile()
{
    pt<<name<<"\t"<<i<<"\t week completed"<<endl;
    pt<<"Number of hours in a week = "<<hrs<<endl;
    pt<<"Your current attendance percentage = "<<curr<<endl;
    if(req)
     {
         pt<<"Number of classes required to attend = "<<req<<endl;
         pt<<"Your fine amount is = "<<fa<<endl;
         pt<<"----------------------------------------------"<<endl;
     }
    else if(hrb)
        {
            pt<<"Number of classes you can miss out ="<<hrb<<endl;
            pt<<"----------------------------------------------"<<endl;
        }
    else
        pt<<"----------------------------------------------"<<endl;

}
int main()
{
    cout<<"__________________YOUR TIME TABLE______________________"<<endl;
    string subname[7][7],temp[5]={"maths","oops","m.prc","c.org","hss_"};
    int i,j,k,cnt[5]={0},n=0;
    float minperc;
    char reply0;
    subject s[5];
    ifstream tt("tt.txt");
    //reading the time table
        while(!tt.eof())
        {
            for(i=0;i<7;i++)
            {
                for(j=0;j<7;j++)
                {
                        tt >> subname[i][j];
                        //cout<<subname[i][j]<<"  ";
                }
            }
        }
    //printing the time table
    for(i=0;i<7;i++)
    {
        for(j=0;j<7;j++)
        {
            cout<<subname[i][j]<<"   ";

        }
        cout<<endl;
    }
    //calculating number of hours in a week for one subject
    for(k=0;k<5;k++)
    {
        n=0;
        for(i=1;i<7;i++)
        {
            for(j=1;j<7;j++)
            {
                if((temp[k].compare(subname[i][j]))==0)
                {
                    n++;
                }
            }
        }
        cnt[k]=n;
    }
    cout<<endl<<"Enter the minimum percentage for all the subjects"<<endl;
    cin>>minperc;
    //sending values to all the objects
    for(i=0;i<5;i++)
    {
        s[i].subject1(cnt[i],minperc,temp[i]);
    }
    string inp[5];
    j=0;
    pt.open("result.txt");
    //inputing the user's subjects choice , and sending the respective subject to the member function
    do{
        cout<<"Which subject's attendance do you want to enter ?"<<endl;
           cin>>inp[j];
        for(i=0;i<5;i++)
        {
          if((inp[j].compare(temp[i]))==0)
           {
             s[i].getpercent();
             s[i].printtofile();
           }
        }
        j++;
        cout<<"Do you want to enter other subject ? (y/n)"<<endl;
            cin>>reply0;
     }while(reply0!='n');
     /*for(int l=0;l<=j;l++)
     {
         s[l].printtofile();
     }*/
    tt.close();
    cin.get();
    return 0;
}
