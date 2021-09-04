#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>

#include "Movie.h"
#include "Customer.h"

// MOVIE INITIALIZATION
int movieCount = 1;
bool movieRegistered = false;
Movie *movies = new Movie[movieCount];

// CUSTOMER INITIALIZATION
int customerCount = 1;
bool customerRegistered = false;
Customer *customers = new Customer[customerCount];

#include "MovieRegistration.h"
#include "CustomerRegistration.h"
#include "CustomerList.h"

using namespace std;

void mainMenu()
{
    system("clear");

    cout << "##############################################" << endl << endl;
    cout << "######### CINEMA REGISTRATION SYSTEM #########" << endl << endl;
    cout << "##############################################" << endl;
    cout << "# 1. MOVIE REGISTRATION                      #" << endl;
    cout << "# 2. CUSTOMER REGISTRATION                   #" << endl;
    cout << "# 3. MOVIES LIST                             #" << endl;
    cout << "# 4. CUSTOMER LIST                           #" << endl;
    cout << "# 5. SEAT REGISTRATION                       #" << endl;
    cout << "# 6. DAILY PROFIT REPORT                     #" << endl;
    cout << "# 7. QUIT                                    #" << endl;
    cout << "##############################################" << endl;

INPUT0:
    cout << "\n > "; unsigned choice; cin >> choice;

    switch (choice)
    {
    case 1:
        movie_registration(movies, movieRegistered);
        mainMenu();
        break;
    case 2:
        customer_registration(customers, customerRegistered);
        mainMenu();
        break;
    case 3:
        // movie_list(movies, movieCount);
        break;
    case 4:
        customer_list(customers, customerCount, customerRegistered);
        mainMenu();
        break;
    case 5:
        // seat_reservation();
        break;
    case 6:
        // profit_report();
        break;
    case 7:
        cout << "Closing..." << endl;
        return;
    default:
        cout << "\nInvalid Input. Try again." << endl;
        goto INPUT0;
    }
}

#endif