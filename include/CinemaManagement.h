#ifndef CINEMAMANAGEMENT_H
#define CINEMAMANAGEMENT_H

#include "MovieManagement.h"
#include "CustomerManagement.h"
#include "CinemaHall.h"

#include <iostream>
#include <iomanip>
#include <ctime> // To get today's date

bool date_checks_out(Movie&, Date&);

void cinema_menu(CinemaHall& hall, MovieList& movies, CustomerList& customers)
{
    START_CINEMA:
    system ("cls");

    std::cout << "1. Slots for the day" << std::endl;
    std::cout << "2. Seat Reservations" << std::endl;
    std::cout << "3. Return to main menu" << std::endl;

    INPUT14:
    std::cout << "\n > "; int choice; std::cin >> choice;
    switch (choice)
    {
    case 1: 
        if (hall.current_count == 0)
        {
            system ("cls");

            std::cout << "Seems like you don't have any movies in the slot yet. Care to add one?" << std::endl;
            std::cout << "1. Add a movie to the slot" << std::endl;
            std::cout << "2. Return to main menu" << std::endl;

            std::cout << "\n > "; std::cin >> choice;
            switch (choice)
            {
            case 1: {
                std::cout << "Enter the name of the movie: "; std::string m_name; std::cin >> m_name;
                for (int i = 0; i < movies.get_count(); i++)
                {
                    if (movies.movie_list[i].name == m_name)
                    {
                        hall.add_slot(movies.movie_list[i]);
                        break;
                    }
                }
                break;
            }
            default:
                break;
            }
        }

        else
        {
            system ("cls");

            hall.display_slots();

            std::cout << "1. Add a movie to the slots" << std::endl;
            std::cout << "2. Delete a movie from the slots" << std::endl;
            std::cout << "3. Return to main menu" << std::endl;
            INPUT13:
            std::cout << "\n > "; std::cin >> choice;

            switch(choice)
            {
            case 1: {
                // Get todays date first
                std::time_t t = std::time(0);
                std::tm *now = std::localtime(&t); // The local time (based on the time zone)

                int year = now->tm_year + 1900;
                int month = now->tm_mon + 1;
                int day = now->tm_mday;

                Date today_date {day, month, year};

                std::cout << "Enter the name of the movie: "; std::string m_name; std::cin >> m_name;
                for (int i = 0; i < movies.get_count(); i++)
                {
                    if (movies.movie_list[i].name == m_name)
                    {
                        if (date_checks_out(movies.movie_list[i], today_date))
                        {
                            hall.add_slot(movies.movie_list[i]);
                        }
                        else // if it's out of date, either early or expired
                        {
                            system ("cls");

                            std::cout << "Movie is out of date." << std::endl;
                            std::cout << "\n1. Return to main menu" << std::endl;
                            std::cout << "\n > "; std::cin >> choice;
                            return;
                        }
                        break;
                    }
                }
                break;
            }
            case 2: {
                std::cout << "Enter the name of the movie: "; std::string name; std::cin >> name;
                int del_slot;
                for (int i = 0; i < movies.get_count(); i++)
                {
                    if (hall.movie_slots[i].name == name)
                    {
                        hall.remove_slot(i+1);
                        del_slot = i;
                        break;
                    }
                }
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        hall.seat_arrangements[del_slot][i][j] = 0;
                    }
                }
                break;
            }
            case 3: 
                break;
            
            case 4:
                std::cout << "Invalid input, try again." << std::endl;
                goto INPUT13;
            }

        }
        break; // SLOTS FOR THE DAY
    
    case 2:
        system ("cls");

        std::cout << "Enter the slot number: "; int slot_num; std::cin >> slot_num;
        if (hall.exists(slot_num-1))
        {
            std::cout << hall.movie_slots[slot_num-1].name << std::endl;
        }
        else
        {
            std::cout << "Slot doesn't exist yet." << std::endl;
            std::cout << "1. Return to previous menu" << std::endl;
            std::cout << "\n > "; std::cin >> choice;
            goto START_CINEMA;
        }

        INPUT11:
        system ("cls");
        hall.display_arrangement(slot_num);

        std::cout << "1. Reserve a seat" << std::endl;
        std::cout << "2. Cancel a reservation" << std::endl;
        std::cout << "3. Return to main menu" << std::endl;

        std::cout << "\n > "; std::cin >> choice;
        switch(choice)
        {
        case 1:
            if (customers.get_count() == 0)
            {
                system ("cls");

                std::cout << "There are no customers registered yet." << std::endl;
                std::cout << "1. Return to previous menu" << std::endl;
                std::cout << "\n > "; std::cin >> choice;
                goto START_CINEMA;
            }
            std::cout << "\nEnter customer ID: "; std::cin >> choice;
            while (choice < 1000 || choice > customers.customer_id)
            {
                std::cout << "Invalid input, try again." << std::endl;
                std::cout << "\nEnter customer ID: " ; std::cin >> choice; 
            }

            Customer *current;
            for (int i = 0; i < customers.get_count(); i++)
            {
                if (customers.customer_list[i].id == choice)
                {
                    current = (customers.customer_list) + i;
                }
            }
            if (hall.movie_slots[slot_num-1].ratingPg.viewerAge > current->age)
            {
                system ("cls");

                std::cout << "The customer is too young for this movie." << std::endl;
                std::cout << "1. Return to previous menu" << std::endl;
                std::cout << "\n > "; std::cin >> choice;
                goto INPUT11;
            }
            else
            {   
                INPUT12:
                std::cout << "Row and column: "; int row, col; std::cin >> row >> col;
                while (row > 8 || col > 8)
                {
                    std::cout << "\nInvalid input, try again.\n" << std::endl;
                    std::cout << "Row and column: "; std::cin >> row >> col; 
                }

                if (hall.seat_arrangements[slot_num - 1][row-1][col-1] == 0)
                {
                    hall.seat_arrangements[slot_num - 1][row-1][col-1] = current->id;
                    goto START_CINEMA;
                }
                else
                {
                    std::cout << "\nSeat already taken." << std::endl;
                    std::cout << "\n1. Try again" << std::endl;
                    std::cout << "2. Return to main menu" << std::endl;
                    std::cout << "\n > "; std::cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        goto INPUT12;
                        break;
                    
                    default:
                        break;
                    }
                }
            }

        case 2:
            std::cout << "Enter row and column: "; int row, col; std::cin >> row >> col;
            while (row > 8 || col > 8)
            {
                    std::cout << "\nInvalid input, try again.\n" << std::endl;
                    std::cout << "Row and column: "; std::cin >> row >> col; 
            }
            
            if (hall.seat_arrangements[slot_num - 1][row-1][col-1] != 0)
            {
                hall.seat_arrangements[slot_num - 1][row-1][col-1] = 0;
                goto START_CINEMA;
            }
        }
        break; // SEAT RESERVATIONS
    
    case 3:
        break;

    default:
        std::cout << "Invalid input, try again." << std::endl;
        goto INPUT14;
    }
}

void daily_profit_report(CinemaHall &hall, MovieList &movies)
{
    system ("cls");

    if (hall.current_count == 0)
    {
        std::cout << "There are zero movies added to the slots for today." << std::endl;
        std::cout << "\n1. Return to main menu" << std::endl;
        std::cout << "\n > "; int choice; std::cin >> choice;
        return;
    }
    std::cout << "########################################################################################" << std::endl;
    std::cout << '|' << std::setw(8) << "Slot No." << '|'
                << std::setw(19) << "Movie to be watched" << '|'
                << std::setw(25) << "Price for a single ticket" << '|'
                << std::setw(17) << "Number of Viewers" << '|' 
                << std::setw(13) << "Total Revenue" << '|' << std::endl;
    std::cout << "########################################################################################" << std::endl; 
    int total_revenue = 0;
    for (int i = 0; i < hall.current_count; i++)
    {
        float total_viewers = 0;
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                if (hall.seat_arrangements[i][j][k] != 0) total_viewers++;
            }
        }
        float slot_revenue = total_viewers * hall.movie_slots[i].price;

        std::cout << '|' << std::setw(8) << i+1 << '|'
                    << std::setw(19) << hall.movie_slots[i].name << '|'
                    << std::setw(25) << hall.movie_slots[i].price << '|'
                    << std::setw(17) << total_viewers << '|'
                    << std::setw(13) << slot_revenue << '|' << std::endl;
        
        total_revenue += slot_revenue;
    }
    std::cout << "########################################################################################" << std::endl;
    std::cout << std::setw(87) << "Total revenue for the day: " + std::to_string(total_revenue) + '.' + std::to_string(total_revenue - std::stof(std::to_string(total_revenue)))<< std::endl; 

    std::cout << "\n1. Return to main menu" << std::endl;
    std::cout << "\n > "; int choice; std::cin >> choice;
    return;
}

bool date_checks_out(Movie &movie, Date &date)
{
    // First check if the release date of the movie is or equal to or less than today's date
    if ((movie.entryDate.year <= date.year && movie.entryDate.month <= date.month && movie.entryDate.day <= date.day)
        || (movie.entryDate.year <= date.year && movie.entryDate.month < date.month && movie.entryDate.day > date.day)
        || (movie.entryDate.year < date.year && movie.entryDate.month > date.month && movie.entryDate.day > date.day))
    {
        // If it passes, it checks if the expiry date of the movie is equal or greater than that of today's date
        if ((movie.exitDate.year >= date.year && movie.exitDate.month >= date.month && movie.exitDate.day >= date.day)
            || (movie.exitDate.year >= date.year && movie.exitDate.month > date.month && movie.exitDate.day < date.day)
            || (movie.exitDate.year > date.year && movie.exitDate.month < date.month && movie.exitDate.day > date.day))
        {
            return true;
        }
    }

    // If it didn't pass...
    return false;
}
#endif // CINEMAMANAGEMENT_H