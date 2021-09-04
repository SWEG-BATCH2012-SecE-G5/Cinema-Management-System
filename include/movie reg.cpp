#include <iostream>
#include <string.h>
#include <cctype>
#include <memory>
//#include "listofmovies.h"

using namespace std;


 struct rating{
 int age;
 float scale;

 }rate;
 struct date
 {
 int day;
 int month;
 int year;
 };
 struct movie
 {
 string name;
 string genre;
 rating rate;
 float price;
 date release;
 date outc;
 };


void movieList();
void resizer(int);


int Size=1;
//auto *lists{new movie[Size]};
auto lists{ make_unique<movie[]>(1) };
movie *addedlist{};



int main()

{
//lists[0]={"Lord of the rings","Adventure",{13,5.5},300.00,{1,1,2001},{2,2,2021}};
//lists[1]={"SpongBob","Animation",{13,5.5},300.00,{1,1,2001},{2,2,2021}};


int num;
cout<<"MOVIE REGISTRATION"<<endl;


    for(int i{0};i<Size;++i)
    {
        cout<<"\nMovie Name: ";
        getline(cin,lists[i].name);
        cout<<"\nGenre: ";
        cin>>lists[i].genre;
        cout<<"\n\t\tRating: ";

        cout<<"\nEnter the age rating (Min age allowed):";
        while(!(cin>>lists[i].rate.age))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };


        cout<<"\nEnter the rating out of 10: ";

         while(!(cin>>lists[i].rate.scale))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };
        cout<<"\nPrice: ";
          while(!(cin>>lists[i].price))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };

        cout<<"Release Date: ";
            cout<<"\nDay: ";
              while(!(cin>>lists[i].release.day))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };

            cout<<"Month: ";
              while(!(cin>>lists[i].release.month))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };

            cout<<"Year: ";
              while(!(cin>>lists[i].release.year))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };

        cout<<"Out of Cinema Date: ";
            cout<<"\nDay: ";
             while(!(cin>>lists[i].outc.day))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };

            cout<<"Month: ";
             while(!(cin>>lists[i].outc.month))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };

            cout<<"Year: ";
             while(!(cin>>lists[i].outc.year))
            {
                cout<<"\n invalid input!!! please insert numbers only :";
                cin.clear();
                cin.ignore();

            };

            system("cls");
            char choice;

    trial:
            cout<<"\nDo you want to register another Movie(Y/N): ";//temporary
                cin.ignore();
                cin>>choice;
                switch(tolower(choice))
                {
                    case 'y':
                        //goto registral;
                            resizer(++Size);
                        break;

                    case 'n': system("cls"); break;

                    default:
                        cout<<"!!Invalid input\n";goto trial;
                        break;

                }
    }

    char choice2;
    cout<<"\nDo you want to display the list of movies(Y/N): ";
    cin>>choice2;

        switch(tolower(choice2))
        {

        case 'y':movieList();
        default: return 0;

        }


}

void movieList()
{
    cout<<"\n\t############################\n";
      cout<<"\t#        MOVIES LIST       #";
    cout<<"\n\t############################";


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




}
 void resizer(int newsiz){

 movie *ptr { new movie[newsiz]};

    for(int i{};i<newsiz-1;++i)
    {
        ptr[i]=lists[i];
    }
 lists.reset(new movie[newsiz]);

    for(int i{};i<newsiz;++i)
    {
        lists[i]=ptr[i];
    }

 }
