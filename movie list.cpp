#include <iostream>

using namespace std;

void moviesearch();

int main()
{

        cout<<"LIST BY: ";
        cout<<"\n\t\t1. Default";
        cout<<"\n\t\t2. Genre";
        cout<<"\n\t\t3. Year of release";
int sortchoice;
cin>>sortchoice;

    switch(sortchoice)
    {

    case 1:
         for(int i{};i<Size;++i)
    {
        cout<<"\n------------------------------------------------";
        cout<<"\n------------------------------------------------";
        cout<<"\nMovie Name: "<<lists[i].name;
        cout<<"\nGenre: "<<lists[i].genre;
        cout<<"\nRating: "<<"Rated <"<<lists[i].rate.age;
        cout<<"\n\t\t("<<lists[i].rate.scale<<"/10)";
        cout<<"\n------------------------------------------------";
        cout<<"\n------------------------------------------------";
        cout<<"\n++++++++++++++++++++++++++++++++++++++++++++++++\n";
    }
    case 2:
         for(int i{};i<Size&&lists[i].genre=="action";++i)
    {
        cout<<"\n------------------------------------------------";
        cout<<"\n------------------------------------------------";
        cout<<"\nMovie Name: "<<lists[i].name;
        cout<<"\nGenre: "<<lists[i].genre;
        cout<<"\nRating: "<<"Rated <"<<lists[i].rate.age;
        cout<<"\n\t\t("<<lists[i].rate.scale<<"/10)";
        cout<<"\n------------------------------------------------";
        cout<<"\n------------------------------------------------";
        cout<<"\n++++++++++++++++++++++++++++++++++++++++++++++++\n";

    }










    }





}
