#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>

#include "Movie.h"
#include "Customer.h"
#include "CinemaHall.h"
#include "CustomerManagement.h"
#include "MovieManagement.h"
#include "CinemaManagement.h"

// Container that stores all movie info
MovieList movieList;

// Container that stores all customer info
CustomerList customerList;

// Container that stores all cinema hall info, initialized
// with three slots for the day for each cinema hall
CinemaHall cinemaHall;

using namespace std;

void mainMenu()
{
    cinemaHall.init();

    START_MAIN:
    system("clear");

    cout << "##############################################" << endl << endl;
    cout << "######### CINEMA REGISTRATION SYSTEM #########" << endl << endl;
    cout << "##############################################" << endl;
    cout << "# 1. LIST OF MOVIES                          #" << endl;
    cout << "# 2. LIST OF CUSTOMERS                       #" << endl;
    cout << "# 3. CINEMA HALLS & SEAT RESERVATION         #" << endl;
    cout << "# 4. DAILY PROFIT REPORT                     #" << endl;
    cout << "# 5. QUIT                                    #" << endl;
    cout << "##############################################" << endl;

INPUT10:
    cout << "\n > "; unsigned choice; cin >> choice;

    switch (choice)
    {
    case 1:
        movieList.movie_menu();
        goto START_MAIN;
        break;

    case 2:
        customerList.customer_menu();
        goto START_MAIN;
        break;

    case 3:
        cinema_menu(cinemaHall, movieList, customerList);
        goto START_MAIN;
        break;

    case 4:
        daily_profit_report(cinemaHall, movieList);
        goto START_MAIN;
        break;

    case 5:
        cout << "\nClosing..." << endl;
        break;

    default:
        cout << "\nInvalid input, Try again." << endl;
        goto INPUT10;
    }
}

#endif