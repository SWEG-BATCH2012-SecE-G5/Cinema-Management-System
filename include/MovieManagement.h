#ifndef MOVIEMANAGEMENT_H
#define MOVIEMANAGEMENT_H

#include "Movie.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

// We are going to use a struct that manages everything
// the manager might need to interact with their movie database,
// including dynamically add new movies to the list, modifying them,
// deleting them, etc...
  //A function for checking interger entries(not character)
    inline void integer_Input(auto *);
struct MovieList {
    // This is where the movies will be kept
    Movie *movie_list;

    // The current amount of movies in stock
    unsigned movie_count = 0;

    // Function that registers movie and passes
    // said movie to add_movie
    void register_movie();

    // A function that adds a movie into stock
    void add_movie(Movie &);

    // A function that modifies info about selected movie
    void modify_movie(unsigned &);

    // A function that deletes a movie from stock
    void delete_movie(unsigned &);

    // A function that sorts the list by genre, price range, rating
    void sort_by();

    // Menu for accessing the functions above
    void movie_menu();



    unsigned &get_count() { return movie_count; }
};

void MovieList::register_movie()
{
    system ("cls");

    Movie movie;

    std::cin.ignore();
    std::cout << "Enter movie name: "; std::getline(std::cin,movie.name);
    std::cout << "Enter movie genre: "; std::cin >> movie.genre;
    std::cout << "Enter movie price: ";
    //for taking values with a datatype that was declared at the time of declaration
    integer_Input(&(movie.price));

    std::cout << "Enter movie release date, separated by spaces (DD/MM/YYYY): ";
        integer_Input(&(movie.entryDate.day));
        integer_Input(&(movie.entryDate.month));
        integer_Input(&(movie.entryDate.year));

    std::cout << "Enter the date this movie goes out of cinema, separated by spaces (DD/MM/YYYY): ";
        integer_Input(&(movie.exitDate.day));
        integer_Input(&(movie.exitDate.month));
        integer_Input(&(movie.exitDate.year));

    std::cout << "Enter viewer rating out of 10: ";
        integer_Input(&(movie.ratingPg.movieRating));
    std::cout << "Enter the movie's PG rating: ";
        integer_Input(&(movie.ratingPg.viewerAge));

    add_movie(movie);

    if (movie_count == 1) movie_menu(); // Initializer
}

void MovieList::add_movie(Movie &movie)
{
    if (!movie_count) // if a movie doesn't exist yet...
    {
        movie_count++;
        movie_list = new Movie[movie_count];

        *movie_list = movie;
    }
    else
    {
        // Make a copy that can handle the current amount of movies
        Movie *copy = new Movie[movie_count + 1];
        for (int i = 0; i < movie_count; i++)
        {
            *(copy + i) = *(movie_list + i);
        }
        *(copy + movie_count) = movie;

        // free currently used memory
        delete[] movie_list;
        movie_list = nullptr;

        // Make the movie_list point to an array that can hold
        // the required amount of movie data
        movie_count++;
        movie_list = new Movie[movie_count];
        for (int i = 0; i < movie_count; i++)
        {
            *(movie_list + i) = *(copy + i);
        }

        // release memory held by the copy
        delete[] copy;
        copy = nullptr;
    }
}

void MovieList::modify_movie(unsigned &index)
{
    system ("cls");

    Movie *current = movie_list + index;

    std::cout << "What do you want to modify?" << std::endl << std::endl;
    std::cout << "1. Name" << std::endl;
    std::cout << "2. Genre" << std::endl;
    std::cout << "3. Price" << std::endl;
    std::cout << "4. Release Date" << std::endl;
    std::cout << "5. Expiry Date" << std::endl;
    std::cout << "6. Rating (viewer reviews and PG)" << std::endl;
    std::cout << "7. Return to main menu" << std::endl;

    INPUT0:
    std::cout << "\n > "; unsigned choice; std::cin >> choice;

    switch(choice)
    {
    case 1:
        std::cin.ignore();
        std::cout << "New name: "; std::getline(std::cin, current->name);
        break;

    case 2:
        std::cout << "New genre: "; std::cin >> current->genre;
        break;

    case 3:
        std::cout << "New price: "; integer_Input(&(current->price));
        break;

    case 4:
        std::cout << "Release day: ";
            integer_Input(&(current->entryDate.day));
        std::cout<< "Release month: ";
            integer_Input(&(current->entryDate.month));
        std::cout<< "Release year: ";
            integer_Input(&(current->entryDate.year));
        break;

    case 5:
        std::cout << "Expiry day: ";
            integer_Input(&(current->exitDate.day));
        std::cout << "Expiry month: ";
            integer_Input(&(current->exitDate.month));
        std::cout << "Expiry year: ";
            integer_Input(&(current->exitDate.year));
        break;

    case 6:
        std::cout << "Viewer rating: ";
            integer_Input(&(current->ratingPg.movieRating));
        std::cout << "PG: ";
            integer_Input(&(current->ratingPg.viewerAge));
        break;

    case 7:
        return;
        break;

    default:
        std::cout << "Invalid input, try again." << std::endl;
        goto INPUT0;
    }

    // Make the current pointer invalid, lest it modifies
    // the actual data
    current = nullptr;
}

void MovieList::delete_movie(unsigned &index)
{
    // Make two arrays to take in values before and
    // after the deleted value respectively
    unsigned l_size = index;
    unsigned r_size = movie_count - index - 1;

    if (r_size == 0) // if we are asked to delete the last movie...
    {
        movie_count--; // ...just deny access to it
        return;
    }

    Movie *copy_left = new Movie[l_size];
    Movie *copy_right = new Movie[r_size];

    for (int i = 0; i < l_size; i++)
    {
        *(copy_left + i) = *(movie_list + i);
    }

    for (int i = 0; i < r_size; i++)
    {
        *(copy_right + i) = *(movie_list + i + l_size + 1);
    }

    delete[] movie_list;
    movie_list = nullptr;

    movie_count--;

    movie_list = new Movie[movie_count];

    // All that's left is to stich it back
    // and return the resultant data
    // to the main container
    for (int i = 0; i < l_size; i++)
    {
        *(movie_list + i) = *(copy_left + i);
    }

    for (int i = l_size; i < movie_count; i++)
    {
        *(movie_list + i) = *(copy_right + i - l_size);
    }

    // Make the temporary pointers invalid
    copy_left = nullptr;
    copy_right = nullptr;
}

void MovieList::sort_by()
{
    system ("cls");

    std::cout << "1. Genre" << std::endl;
    std::cout << "2. Price" << std::endl;
    std::cout << "3. Viewer Rating" << std::endl;
    std::cout << "4. Return to previous menu" << std::endl;

    std::cout << "\n > "; unsigned choice; std::cin >> choice;

    // Filters out the stock based on the different attributes
    switch (choice)
    {
    case 1: {
        system ("cls");

        std::cout << "Enter the preferred genre: "; std::string p_genre; std::cin >> p_genre;

        int id_num = 1;

        std::cout << "###########################################################################" << std::endl;
        std::cout << '|' << std::setw(3) << "ID" << '|'
                    << std::setw(20) << "Name" << '|'
                    << std::setw(10) << "Genre" << '|'
                    << std::setw(4) << "Price" << '|'
                    << std::setw(10) << "Rel. Date" << '|'
                    << std::setw(10) << "Exp. Date" << '|'
                    << std::setw(6) << "Rating" << '|'
                    << std::setw(2) << "PG" << '|' << std::endl;
        std::cout << "###########################################################################" << std::endl;

        for (int i = 0; i < movie_count; i++)
        {
            if (movie_list[i].genre == p_genre)
            {
               std::cout << '|' << std::setw(3) << id_num++ << '|'
                    << std::setw(20) << movie_list[i].name << '|'
                    << std::setw(10) << movie_list[i].genre << '|'
                    << std::setw(4) << movie_list[i].price << '|'
                    << std::setw(10) << std::to_string(movie_list[i].entryDate.day) + '/'
                                      + std::to_string(movie_list[i].entryDate.month) + '/'
                                      + std::to_string(movie_list[i].entryDate.year) << '|'
                    << std::setw(10) << std::to_string(movie_list[i].exitDate.day) + '/'
                                      + std::to_string(movie_list[i].exitDate.month) + '/'
                                      + std::to_string(movie_list[i].exitDate.year) << '|'
                    << std::setw(6) << movie_list[i].ratingPg.movieRating << '|'
                    << std::setw(2) << movie_list[i].ratingPg.viewerAge << '|' << std::endl;
            }
        }
        std::cout << "###########################################################################" << std::endl << std::endl;

        std::cout << "1. Return to previous menu" << std::endl;

        INPUT1:
        std::cout << "\n > "; std::cin >> choice;

        switch (choice)
        {
        case 1:
            break;

        default:
            std::cout << "Invalid input, try again." << std::endl;
            goto INPUT1;
            break;
        }
        break;
    }
    case 2: {
        system ("cls");

        std::cout << "Enter the price cap: "; float p_cap; std::cin >> p_cap;

        int id_num = 1;

        std::cout << "###########################################################################" << std::endl;
        std::cout << '|' << std::setw(3) << "ID" << '|'
                    << std::setw(20) << "Name" << '|'
                    << std::setw(10) << "Genre" << '|'
                    << std::setw(4) << "Price" << '|'
                    << std::setw(10) << "Rel. Date" << '|'
                    << std::setw(10) << "Exp. Date" << '|'
                    << std::setw(6) << "Rating" << '|'
                    << std::setw(2) << "PG" << '|' << std::endl;
        std::cout << "###########################################################################" << std::endl;

        for (int i = 0; i < movie_count; i++)
        {
            if (movie_list[i].price <= p_cap)
            {
               std::cout << '|' << std::setw(3) << id_num++ << '|'
                    << std::setw(20) << movie_list[i].name << '|'
                    << std::setw(10) << movie_list[i].genre << '|'
                    << std::setw(4) << movie_list[i].price << '|'
                    << std::setw(10) << std::to_string(movie_list[i].entryDate.day) + '/'
                                      + std::to_string(movie_list[i].entryDate.month) + '/'
                                      + std::to_string(movie_list[i].entryDate.year) << '|'
                    << std::setw(10) << std::to_string(movie_list[i].exitDate.day) + '/'
                                      + std::to_string(movie_list[i].exitDate.month) + '/'
                                      + std::to_string(movie_list[i].exitDate.year) << '|'
                    << std::setw(6) << movie_list[i].ratingPg.movieRating << '|'
                    << std::setw(2) << movie_list[i].ratingPg.viewerAge << '|' << std::endl;
            }
        }
        std::cout << "###########################################################################" << std::endl << std::endl;

        std::cout << "1. Return to previous menu" << std::endl;

        INPUT2:
        std::cout << "\n > "; std::cin >> choice;

        switch (choice)
        {
        case 1:
            return;
            break;

        default:
            std::cout << "Invalid input, try again." << std::endl;
            goto INPUT2;
            break;
        }
        break;
    }
    case 3: {
        system ("cls");
        std::cout << "Enter the minimum age requirement: "; float m_age; std::cin >> m_age;

        int id_num = 1;

        std::cout << "###########################################################################" << std::endl;
        std::cout << '|' << std::setw(3) << "ID" << '|'
                    << std::setw(20) << "Name" << '|'
                    << std::setw(10) << "Genre" << '|'
                    << std::setw(4) << "Price" << '|'
                    << std::setw(10) << "Rel. Date" << '|'
                    << std::setw(10) << "Exp. Date" << '|'
                    << std::setw(6) << "Rating" << '|'
                    << std::setw(2) << "PG" << '|' << std::endl;
        std::cout << "###########################################################################" << std::endl;

        for (int i = 0; i < movie_count; i++)
        {
            if (movie_list[i].ratingPg.viewerAge >= m_age)
            {
               std::cout << '|' << std::setw(3) << id_num++ << '|'
                    << std::setw(20) << movie_list[i].name << '|'
                    << std::setw(10) << movie_list[i].genre << '|'
                    << std::setw(4) << movie_list[i].price << '|'
                    << std::setw(10) << std::to_string(movie_list[i].entryDate.day) + '/'
                                      +  std::to_string(movie_list[i].entryDate.month) + '/'
                                      +  std::to_string(movie_list[i].entryDate.year) << '|'
                    << std::setw(10) << std::to_string(movie_list[i].exitDate.day) + '/'
                                      +  std::to_string(movie_list[i].exitDate.month) + '/'
                                      +  std::to_string(movie_list[i].exitDate.year) << '|'
                    << std::setw(6) << movie_list[i].ratingPg.movieRating << '|'
                    << std::setw(2) << movie_list[i].ratingPg.viewerAge << '|' << std::endl;
            }
        }
        std::cout << "###########################################################################" << std::endl << std::endl;

        std::cout << "1. Return to previous menu" << std::endl;

        INPUT3:
        std::cout << "\n > "; std::cin >> choice;

        switch (choice)
        {
        case 1:
            break;

        default:
            std::cout << "Invalid input, try again." << std::endl;
            goto INPUT3;
            break;
        }
        break;
    }

    default:
        break;
    }
}

void MovieList::movie_menu()
{
    START_MOVIE:
    system ("cls");

    if (movie_count) // If movies exist already...
    {
        int id_num = 1;
        std::cout << "###########################################################################" << std::endl;
        std::cout << '|' << std::setw(3) << "ID" << '|'
                    << std::setw(20) << "Name" << '|'
                    << std::setw(10) << "Genre" << '|'
                    << std::setw(4) << "Price" << '|'
                    << std::setw(10) << "Rel. Date" << '|'
                    << std::setw(10) << "Exp. Date" << '|'
                    << std::setw(6) << "Rating" << '|'
                    << std::setw(2) << "PG" << '|' << std::endl;
        std::cout << "###########################################################################" << std::endl;

        for (int i = 0; i < movie_count; i++)
        {
            std::cout << '|' << std::setw(3) << id_num++ << '|'
                    << std::setw(20) << movie_list[i].name << '|'
                    << std::setw(10) << movie_list[i].genre << '|'
                    << std::setw(4) << movie_list[i].price << '|'
                    << std::setw(10) << std::to_string(movie_list[i].entryDate.day) + '/'
                                        + std::to_string(movie_list[i].entryDate.month) + '/'
                                        + std::to_string(movie_list[i].entryDate.year) << '|'
                    << std::setw(10) << std::to_string(movie_list[i].exitDate.day) + '/'
                                        + std::to_string(movie_list[i].exitDate.month) + '/'
                                        + std::to_string(movie_list[i].exitDate.year) << '|'
                    << std::setw(6) << movie_list[i].ratingPg.movieRating << '|'
                    << std::setw(2) << movie_list[i].ratingPg.viewerAge << '|' << std::endl;
        }

        std::cout << "###########################################################################" << std::endl << std::endl;

        std::cout << "1. Register a new movie" << std::endl;
        std::cout << "2. Modify an existing movie" << std::endl;
        std::cout << "3. Delete a movie from stock" << std::endl;
        std::cout << "4. Sort by..." << std::endl;
        std::cout << "5. Return to main menu" << std::endl;

        INPUT4:
        std::cout << "\n > "; unsigned choice; std::cin >> choice;
        switch (choice)
        {
        case 1:
            register_movie();
            goto START_MOVIE;
            break;

        case 2:
            std::cout << "Enter the ID of the movie: "; std::cin >> choice;
            while (choice > id_num || choice < 1)
            {
                std::cout << "\nInvalid input, try again." << std::endl;
                std::cout << "\n > "; std::cin >> choice;
            }
            choice--;
            modify_movie(choice);
            goto START_MOVIE;
            break;

        case 3:
            std::cout << "Enter the ID of the movie: "; std::cin >> choice;
            while (choice > id_num || choice < 1)
            {
                std::cout << "\nInvalid input, try again." << std::endl;
                std::cout << "\n > "; std::cin >> choice;
            }
            choice--;
            delete_movie(choice);
            goto START_MOVIE;
            break;

        case 4:
            sort_by();
            goto START_MOVIE;
            break;

        case 5:
            return;
            break;

        default:
            std::cout << "Invalid input, try again." << std::endl;
            goto INPUT4;
            break;
        }
    }
    else // no movies yet
    {
        system ("cls");

        std::cout << "Seems like you haven't added any movies yet. Care to add one?" << std::endl << std::endl;
        std::cout << "1. Register movie" << std::endl;
        std::cout << "2. Return to Main Menu" << std::endl;

        INPUT5:
        std::cout << "\n > "; unsigned choice; std::cin >> choice;
        switch(choice)
        {
        case 1:
            register_movie();
            break;

        case 2:
            break;

        default:
            std::cout << "Invalid input, try again." << std::endl;
            goto INPUT5;
        }
    }
}

inline void integer_Input(auto *ToBeChecked)
{
    //int invalidCounter=0;
    while(!(std::cin>>*ToBeChecked))
    {
        //invalidCounter++;
      //  if(invalidCounter==1)
        //{
            std::cout<<"\nInvalid input!!! please insert Numbers only: ";
            std::cin.clear();
            std::cin.ignore();
       // }
    }
}

#endif // MOVIEMANAGEMENT_H
