#ifndef MOVIE_H
#define MOVIE_H

#include <string>

struct Rating {
    float movieRating;
    int viewerAge;
};

struct Date {
    int day, month, year;
};

struct Movie {
    std::string name, genre;

    float price;

    // Dates for when the movie goes in or out of cinema
    Date entryDate;
    Date exitDate;

    Rating ratingPg;
};

#endif // MOVIE_H
