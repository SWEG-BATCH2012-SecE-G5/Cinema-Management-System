#ifndef CINEMAHALL_H
#define CINEMAHALL_H

#include "Movie.h"
#include "Customer.h"

#include <iomanip>
#include <iostream>

struct CinemaHall {
    int id;

    // The maximum amount of slots that are to be allowed for the day
    int movie_count = 3;

    // amount of movies currently in slots
    int current_count = 0;

    Movie *movie_slots;
    unsigned ***seat_arrangements = new unsigned**[3];
    
    // displays the seating arrangement for a given slot number
    void display_arrangement(int);

    void add_slot(Movie&);
    void remove_slot(int);
    
    void display_slots();

    bool exists(int);

    // INITIALIZER
    void init();
};

bool CinemaHall::exists(int index)
{
    if (index + 1 <= current_count) return true;
    return false;
}

void CinemaHall::init()
{
    for (int i = 0; i < 3; i++)
    {
        seat_arrangements[i] = new unsigned*[8]; 
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            seat_arrangements[i][j] = new unsigned[8];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                seat_arrangements[i][j][k] = 0;
            }
        }
    }


    
}

void CinemaHall::add_slot(Movie& movie)
{
    if (current_count == 0)
    {
        movie_slots = new Movie[1];
        movie_slots[0] = movie;
        current_count++;
    }
    else
    {
        if (current_count < movie_count)
        {
            Movie *copy = new Movie[current_count + 1];
            for (int i = 0; i < current_count; i++)
            {
                *(copy + i) = *(movie_slots + i);
            }
            *(copy + current_count) = movie;
            
            delete[] movie_slots;
            movie_slots = nullptr;

            current_count++;

            movie_slots = new Movie[current_count];
            for (int i = 0; i < current_count; i++)
            {
                *(movie_slots + i) = *(copy + i);
            }
            copy = nullptr;
        }
        else
        {
            std::cout << "Slots are full!" << std::endl;
        }
    }
} 

void CinemaHall::remove_slot(int slot_num)
{
    int l_size = slot_num - 1;
    int r_size = current_count - slot_num;

    Movie *copy_left = new Movie[l_size];
    Movie *copy_right = new Movie[r_size];

    for (int i = 0; i < l_size; i++)
    {
        copy_left[i] = movie_slots[i];
    }

    for (int i = 0; i < r_size; i++)
    {
        copy_right[i] = movie_slots[i + l_size + 1];
    }

    delete[] movie_slots;
    movie_slots = nullptr;

    current_count--;
    movie_slots = new Movie[current_count];

    for (int i = 0; i < l_size; i++)
    {
        movie_slots[i] = copy_left[i];
    }

    for (int i = l_size; i < current_count; i++)
    {
        movie_slots[i] = copy_right[i - l_size];
    }

    copy_left = nullptr;
    copy_right = nullptr;
}

void CinemaHall::display_arrangement(int slot_num)
{
    // An 8 by 8 layout is used
    // id of the customer who reserved the seat is used as a place-holder of the seat
    // otherwise is left with blank
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            std::cout << "[" << std::setw(4) 
                        << (seat_arrangements[slot_num - 1][i][j] == 0 ? "    " : std::to_string(seat_arrangements[slot_num - 1][i][j])) 
                        << "]" << ' ';
        }
        std::cout << std::endl;
    }
}

void CinemaHall::display_slots()
{
    if (current_count == 0) return;
    else
    {
        for (int i = 0; i < current_count; i++)
        {
            std::cout << "Slot " << i + 1 << std::endl;
            std::cout << "\tName: " << movie_slots[i].name << std::endl;
            std::cout << "\tGenre: " << movie_slots[i].genre << std::endl;

            std::cout << std::endl;
        }
    }
}
#endif // CINEMAHALL_H