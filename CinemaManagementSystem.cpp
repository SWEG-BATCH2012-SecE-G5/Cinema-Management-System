/* This program gives the user the ability to manage their own cinema
   More specifically, it is able to do the following:
    - Store into, modify and delete movies in the database
    - Add, modify, and delete customers into and from the database
    - Manage the cinema cinema viewing slots, reserve and cancel seats
    - And finally give the daily profit report to the manager in a tabular format
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
#include <vector>
#include <ctime>
#include <memory>

using namespace std;

struct Rating {
    int movieRating;
    int viewerAge;
};

struct Date {
    int day, month, year;
};

struct Movie {
    char name[30];
    char genre[20];

    int price;

    // Dates for when the movie goes in or out of cinema
    Date entryDate;
    Date exitDate;

    // Preview rating out of 10 and PG rating
    Rating ratingPg;
};

struct Customer {
    char name[30];
    int age, id;
};

struct Cinema {
    // The maximum amount of slots that are to be allowed for the day
    int movieCount = 3;

    vector<shared_ptr<Movie>> movieSlots;

    unsigned seatReservations[3][8][8];

    void displayArrangement(int slot)
    {
        // An 8 by 8 layout is used
        // id of the customer who reserved the seat is used as a place-holder of the seat
        // otherwise is left with blank
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << "[" << setw(4) 
                            << (seatReservations[slot - 1][i][j] == 0 ? "    " : to_string(seatReservations[slot - 1][i][j])) 
                            << "]" << ' ';
            }
            cout << endl;
        }

        cout << endl;
    }

    void displaySlots()
    {
        for (int i = 0; i < movieSlots.size(); i++)
        {
            cout << "Slot " << i + 1 << endl;
            cout << "\tName: " << movieSlots[i]->name << endl;
            cout << "\tGenre: " << movieSlots[i]->genre << endl;

            cout << endl;
        }
    }

    bool exists(unsigned slotNum)
    {
        return movieSlots.size() >= slotNum;
    }
};

// We need containers that can hold all the movies and customers
vector<Movie> movieList;
vector<Customer> customerList;

Cinema cinema;

// int main will be the one that holds the main menu, housing the sub-menus
// All 5 sub-menus are to be classified by four functions
void movieMenu();
void customerMenu();
void cinemaMenu();
void profitReport();
void developersInfo();

// Helper functions
unsigned getChoice();

void registerMovie();
void modifyMovie(unsigned); // Edit a movie from the database with a given index
void sortMoviesBy(); // Sort movies with their given identifier
unsigned getMovieChoice();

void registerCustomer();
void modifyCustomer(unsigned); // Edit a customer's info with a given index
unsigned getCustomerIndex();

void addSlot();
bool dateChecksOut(Movie&, Date&);

void dailyProfitReport();

template <typename T> void swapped(T& one, T& other);

// Get todays date first
time_t t = time(0);
tm *now = localtime(&t); // The local time (based on the time zone)

int year = now->tm_year + 1900;
int month = now->tm_mon + 1;
int day = now->tm_mday;

Date today_date {day, month, year};

bool isEmpty(fstream& pFile)
{
    return pFile.peek() == fstream::traits_type::eof();
}

void loadMovies();
void dumpMovies();

void loadCustomers();
void dumpCustomers();

void loadCinema();
void dumpCinema();

int main()
{
    loadMovies();
    loadCustomers();
    loadCinema();
    START_MAIN:
    system ("cls");

    cout << "##############################################" << endl << endl;
    cout << "######### CINEMA REGISTRATION SYSTEM #########" << endl << endl;
    cout << "##############################################" << endl;
    cout << "# 1. LIST OF MOVIES                          #" << endl;
    cout << "# 2. LIST OF CUSTOMERS                       #" << endl;
    cout << "# 3. CINEMA & SEAT RESERVATION               #" << endl;
    cout << "# 4. DAILY PROFIT REPORT                     #" << endl;
    cout << "# 5. SAVE AND QUIT                           #" << endl;
    cout << "##############################################" << endl;

    INPUT01:
    switch (getChoice())
    {
    case 1: movieMenu(); goto START_MAIN; break;
    case 2: customerMenu(); goto START_MAIN; break;
    case 3: cinemaMenu(); goto START_MAIN; break;
    case 4: dailyProfitReport(); goto START_MAIN; break;           
    case 5: 
        cout << "\nClosing..." << endl; 
        dumpMovies();
        dumpCustomers();
        dumpCinema();
        break;
    default: cout << "\nInvalid input, Try again." << endl; goto INPUT01;
    }
}

// MOVIE MENU BEGINS
void movieMenu()
{
    START_MOVIE:
    system ("cls");

    if (!movieList.empty()) // If movies exist already...
    {
        cout << "#################################################################################" << endl;
        cout << '|' << setw(30) << "Name" << '|'
                    << setw(10) << "Genre" << '|'
                    << setw(4) << "Price" << '|'
                    << setw(10) << "Rel. Date" << '|'
                    << setw(10) << "Exp. Date" << '|'
                    << setw(6) << "Rating" << '|'
                    << setw(2) << "PG" << '|' << endl;
        cout << "#################################################################################" << endl; 

        for (int i = 0; i < movieList.size(); i++)
        {
            cout << '|' << setw(30) << movieList[i].name << '|'
                    << setw(10) << movieList[i].genre << '|'
                    << setw(5) << movieList[i].price << '|' 
                    << setw(10) << to_string(movieList[i].entryDate.day) + '/'
                                        + to_string(movieList[i].entryDate.month) + '/'
                                        + to_string(movieList[i].entryDate.year) << '|'
                    << setw(10) << to_string(movieList[i].exitDate.day) + '/'
                                        + to_string(movieList[i].exitDate.month) + '/'
                                        + to_string(movieList[i].exitDate.year) << '|'
                    << setw(6) << movieList[i].ratingPg.movieRating << '|'
                    << setw(2) << movieList[i].ratingPg.viewerAge << '|' << endl; 
        }

        cout << "#################################################################################" << endl << endl;

        cout << "1. Register a new movie" << endl;
        cout << "2. Modify an existing movie" << endl;
        cout << "3. Delete a movie from stock" << endl;
        cout << "4. Sort by..." << endl;
        cout << "5. Return to main menu" << endl;

        INPUT02:
        switch (getChoice())
        {
        case 1: registerMovie(); goto START_MOVIE; break;
        case 2:
            cout << "Enter the name of the movie: "; cin.ignore(); 
            char name[30]; cin.getline(name, 30);
            for (int i = 0; i < movieList.size(); i++)
                if (strcmp(movieList[i].name, name) == 0)
                    modifyMovie(i);
            goto START_MOVIE;
            break;

        case 3:
            cout << "Enter the name of the movie: "; cin.ignore(); 
            cin.getline(name, 30);
            for (int i = 0; i < movieList.size(); i++)
                if (strcmp(movieList[i].name, name) == 0)
                    movieList.erase(movieList.begin() + i);
            goto START_MOVIE;
            break;

        case 4: sortMoviesBy(); goto START_MOVIE; break;
        case 5: break;
        default: cout << "Invalid input, try again." << endl; goto INPUT02; break;
        }
    }
    else // no movies yet
    {
        system ("cls");

        cout << "Seems like you haven't added any movies yet. Care to add one?" << endl << endl;
        cout << "1. Register movie" << endl;
        cout << "2. Return to Main Menu" << endl;

        INPUT03:
        switch(getChoice())
        {
        case 1: registerMovie(); goto START_MOVIE;break;
        case 2: dumpMovies(); break;
        default: cout << "Invalid input, try again." << endl; goto INPUT03;
        }
    }
}

void registerMovie()
{
    system ("cls");

    Movie movie;

    cin.ignore();
    cout << "Enter movie name: "; cin.getline(movie.name, 30);
    cout << "Enter movie genre: "; cin >> movie.genre;
    cout << "Enter movie price: "; cin >> movie.price;

    cout << "Enter movie release date, separated by spaces (DD/MM/YYYY): ";
    cin >> movie.entryDate.day >> movie.entryDate.month >> movie.entryDate.year;

    cout << "Enter the date this movie goes out of cinema, separated by spaces (DD/MM/YYYY): ";
    cin >> movie.exitDate.day >> movie.exitDate.month >> movie.exitDate.year;
    
    cout << "Enter viewer rating out of 10: "; cin >> movie.ratingPg.movieRating;
    cout << "Enter the movie's PG rating: "; cin >> movie.ratingPg.viewerAge;

    movieList.push_back(movie);
}

void modifyMovie(unsigned index)
{
    system ("cls");

    Movie *current = &movieList[index];

    cout << "What do you want to modify?" << endl << endl;
    cout << "1. Name" << endl;
    cout << "2. Genre" << endl;
    cout << "3. Price" << endl;
    cout << "4. Release Date" << endl;
    cout << "5. Expiry Date" << endl;
    cout << "6. Rating (viewer reviews and PG)" << endl;
    cout << "7. Return to main menu" << endl;

    INPUT04:
    switch(getChoice())
    {
    case 1: cout << "New name: "; cin.ignore(); cin.getline(current->name, 30); break;
    case 2: cout << "New genre: "; cin >> current->genre; break;
    case 3: cout << "New price: "; cin >> current->price; break;
    case 4:
        cout << "Release day, month, year: ";
        cin >> current->entryDate.day >> current->entryDate.month >> current->entryDate.year;
        break;
    case 5:
        cout << "Expiry day, month, year: ";
        cin >> current->exitDate.day >> current->exitDate.month >> current->exitDate.year;
        break;
    case 6:
        cout << "Viewer rating and PG: "; cin >> current->ratingPg.movieRating >> current->ratingPg.viewerAge;
        break;
    case 7: break;
    default: cout << "Invalid input, try again." << endl; goto INPUT04;
    }

    // Make the current pointer invalid, since it deletes what it points to
    // when deleted itself
    current = nullptr;
}

void sortMoviesBy()
{
    system ("cls");

    cout << "1. Name" << endl;
    cout << "2. Genre" << endl;
    cout << "3. Price" << endl;
    cout << "4. Return to previous menu" << endl;

    INPUT05:
    switch (getChoice())
    {
    case 1:
        for (int i = 0; i < movieList.size(); i++)
            for (int j = 0; j < i; j++)
                if (strcmp((movieList[i].name), movieList[j].name) < 0)
                    swapped(movieList[i], movieList[j]);
        break;
    
    case 2:
        for (int i = 0; i < movieList.size(); i++)
            for (int j = 0; j < i; j++)
                if (strcmp(movieList[i].genre, movieList[j].genre) < 0)
                    swapped(movieList[i], movieList[j]);
        break;

    case 3: 
        for (int i = 0; i < movieList.size(); i++)
            for (int j = 0; j < i; j++)
                if (movieList[i].price < movieList[j].price)
                    swapped(movieList[i], movieList[j]);
        break;

    case 4: break;
    default: cout << "Invalid input, try again." << endl; goto INPUT05; break;
    }
}
// MOVIE MENU ENDS

// CUSTOMER MENU BEGINS
void customerMenu()
{
    START_CUSTOMER:
    system ("cls");

    if (!customerList.empty()) // If customer(s) exist already...
    {
        cout << "#####################################" << endl;
        cout << '|' << setw(5) << "ID"
                    << '|' << setw(25) << "Name"
                    << '|' << setw(3) << "Age" << '|' << endl;
        cout << "#####################################" << endl;
        for (int i = 0; i < customerList.size(); i++)
        {
            cout << '|' << setw(5) << customerList[i].id
                        << '|' << setw(25) << customerList[i].name
                        << '|' << setw(3) << customerList[i].age << '|' << endl;
        }
        cout << "#####################################" << endl << endl;

        cout << "1. Register a new customer" << endl;
        cout << "2. Modify an existing customer" << endl;
        cout << "3. Remove a customer from the database" << endl;
        cout << "4. Return to main menu" << endl;

        INPUT06:
        switch (getChoice())
        {
        case 1: registerCustomer(); goto START_CUSTOMER; break;
        case 2: modifyCustomer(getCustomerIndex()); goto START_CUSTOMER; break;
        case 3: customerList.erase(customerList.begin() + getCustomerIndex()); goto START_CUSTOMER; break;
        case 4: break;
        default: cout << "Invalid input, try again." << endl; goto INPUT06;
        }
    }
    else // no customers yet
    {
        system ("cls");

        cout << "Seems like you haven't added any customers yet. Care to add one?" << endl << endl;
        cout << "1. Register customer" << endl;
        cout << "2. Return to Main Menu" << endl;

        INPUT07:
        switch(getChoice())
        {
        case 1: registerCustomer(); goto START_CUSTOMER; break;
        case 2: break;
        default: cout << "Invalid input, try again." << endl; goto INPUT07;
        }
    }
}

void registerCustomer()
{
    system ("cls");

    Customer customer;

    cout << "Enter customer name: "; 
    cin.ignore(); cin.getline(customer.name, 30);
    cout << "Enter customer age: "; cin >> customer.age;
    customer.id = customerList.size() + 1000;

    // To avoid ID duplication in case of customer deletion
    if (customerList.size())
        while (customer.id == customerList[customerList.size() - 1].id)
            customer.id++;

    customerList.push_back(customer);
}

void modifyCustomer(unsigned index)
{
    system ("cls");

    Customer *current = &customerList[index];

    cout << "What do you want to modify?" << endl << endl;
    cout << "1. Name" << endl;
    cout << "2. Age" << endl;
    cout << "3. Return to main menu" << endl;

    INPUT08:
    cout << "\n > "; unsigned choice; cin >> choice;

    switch(choice)
    {
    case 1: cout << "New name: "; cin >> current->name; break;
    case 2: cout << "New age: "; cin >> current->age; break;
    case 3: break;
    default: cout << "Invalid input, try again." << endl; goto INPUT08;
    }
    // Make the current pointer invalid, lest it modifies
    // the actual data
    current = nullptr;
}

unsigned getCustomerIndex()
{
    cout << "Enter the name of the customer: "; char name[30]; 
    cin.ignore(); cin.getline(name, 30);
    for (int i = 0; i < customerList.size(); i++)
        if (strcmp(customerList[i].name, name) == 0)
            return i;
}
// CUSTOMER MENU ENDS

// CINEMA MENU BEGINS
void cinemaMenu()
{
    START_CINEMA:
    system ("cls");

    cout << "1. Slots for the day" << endl;
    cout << "2. Seat Reservations" << endl;
    cout << "3. Return to main menu" << endl;

    INPUT09:
    cout << "\n > "; int choice; cin >> choice;
    switch (choice)
    {
    case 1: 
        if (cinema.movieSlots.empty())
        {
            system ("cls");

            cout << "Seems like you don't have any movies in the slot yet. Care to add one?" << endl;
            cout << "1. Add a movie to the slot" << endl;
            cout << "2. Return to main menu" << endl;

            cout << "\n > "; cin >> choice;
            switch (choice)
            {
            case 1: addSlot(); break;
            default: break;
            }
        }

        else
        {
            system ("cls");

            cinema.displaySlots();

            cout << "1. Add a movie to the slots" << endl;
            cout << "2. Delete a movie from the slots" << endl;
            cout << "3. Return to main menu" << endl;
            INPUT10:
            cout << "\n > "; cin >> choice;

            switch(choice)
            {
            case 1: addSlot(); break;
            case 2: {
                cout << "Enter the name of the movie: ";
                cin.ignore(); char name[30]; cin.getline(name, 30);
                int del_slot;
                for (int i = 0; i < movieList.size(); i++)
                    if (strcmp(cinema.movieSlots[i]->name, name) == 0)
                    {
                        cinema.movieSlots.erase(cinema.movieSlots.begin() + i);
                        del_slot = i;
                        break;
                    }
                for (int i = 0; i < 8; i++)
                    for (int j = 0; j < 8; j++)
                        cinema.seatReservations[del_slot][i][j] = 0;
                break;
            }
            case 3: break;
            default: cout << "Invalid input, try again." << endl; goto INPUT10;
            }

        }
        break; // SLOTS FOR THE DAY
    
    case 2:
        system ("cls");

        cout << "Enter the slot number: "; int slotNum; cin >> slotNum;
        if (cinema.exists(slotNum))
        {
            cout << cinema.movieSlots[slotNum-1]->name << endl;
        }
        else
        {
            cout << "Slot doesn't exist yet." << endl;
            cout << "1. Return to previous menu" << endl;
            getChoice();
            goto START_CINEMA;
        }

        INPUT11:
        system ("cls");
        cinema.displayArrangement(slotNum);

        cout << "1. Reserve a seat" << endl;
        cout << "2. Cancel a reservation" << endl;
        cout << "3. Return to main menu" << endl;

        cout << "\n > "; cin >> choice;
        switch(choice)
        {
        case 1:
            if (customerList.empty())
            {
                system ("cls");

                cout << "There are no customers registered yet." << endl;
                cout << "1. Return to previous menu" << endl;
                cout << "\n > "; cin >> choice;
                goto START_CINEMA;
            }
            
            cout << "\nEnter customer ID: "; cin >> choice;
            while (choice < 1000 || choice > customerList[customerList.size() - 1].id)
            {
                cout << "Invalid input, try again." << endl;
                cout << "\nEnter customer ID: " ; cin >> choice; 
            }

            Customer *current;
            for (int i = 0; i < customerList.size(); i++)
                if (customerList[i].id == choice)
                    current = &customerList[i];

            if (cinema.movieSlots[slotNum-1]->ratingPg.viewerAge > current->age)
            {
                system ("cls");

                cout << "The customer is too young for this movie." << endl;
                cout << "1. Return to previous menu" << endl;
                cout << "\n > "; cin >> choice;
                goto INPUT11;
            }
            else
            {   
                INPUT12:
                cout << "Row and column: "; int row, col; cin >> row >> col;
                while (row > 8 || col > 8)
                {
                    cout << "\nInvalid input, try again.\n" << endl;
                    cout << "Row and column: "; cin >> row >> col; 
                }

                if (cinema.seatReservations[slotNum - 1][row-1][col-1] == 0)
                {
                    cinema.seatReservations[slotNum - 1][row-1][col-1] = current->id;
                    goto START_CINEMA;
                }
                else
                {
                    cout << "\nSeat already taken." << endl;
                    cout << "\n1. Try again" << endl;
                    cout << "2. Return to main menu" << endl;
                    cout << "\n > "; cin >> choice;
                    switch (choice)
                    {
                    case 1: goto INPUT12; break;
                    default: break;
                    }
                }
            }

        case 2:
            cout << "Enter row and column: "; int row, col; cin >> row >> col;
            while (row > 8 || col > 8)
            {
                cout << "\nInvalid input, try again.\n" << endl;
                cout << "Row and column: "; cin >> row >> col; 
            }
            
            if (cinema.seatReservations[slotNum - 1][row-1][col-1] != 0)
            {
                cinema.seatReservations[slotNum - 1][row-1][col-1] = 0;
                goto START_CINEMA;
            }
        }
        break; // SEAT RESERVATIONS
    
    case 3: break;
    default: cout << "Invalid input, try again." << endl; goto INPUT09;
    }
}

bool dateChecksOut(Movie &movie, Date &date)
{
    // First check if the release date of the movie is or equal to or less than today's date
    if ((movie.entryDate.year <= date.year && movie.entryDate.month <= date.month && movie.entryDate.day <= date.day)
        || (movie.entryDate.year <= date.year && movie.entryDate.month < date.month)
        || (movie.entryDate.year < date.year))
    {
        // If it passes, it checks if the expiry date of the movie is equal or greater than that of today's date
        if ((movie.exitDate.year >= date.year && movie.exitDate.month >= date.month && movie.exitDate.day >= date.day)
            || (movie.exitDate.year >= date.year && movie.exitDate.month > date.month)
            || (movie.exitDate.year > date.year))
        {
            return true;
        }
    }

    // If it didn't pass...
    return false;
}
// CINEMA MENU ENDS

void dailyProfitReport()
{
    system ("cls");

    if (cinema.movieSlots.empty())
    {
        cout << "There are zero movies added to the slots for today." << endl;
        cout << "\n1. Return to main menu" << endl;
        cout << "\n > "; int choice; cin >> choice;
        return;
    }
    cout << "########################################################################################" << endl;
    cout << '|' << setw(8) << "Slot No." << '|'
                << setw(19) << "Movie to be watched" << '|'
                << setw(25) << "Price for a single ticket" << '|'
                << setw(17) << "Number of Viewers" << '|' 
                << setw(13) << "Total Revenue" << '|' << endl;
    cout << "########################################################################################" << endl; 
    int total_revenue = 0;
    for (int i = 0; i < cinema.movieSlots.size(); i++)
    {
        float total_viewers = 0;
        for (int j = 0; j < 8; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                if (cinema.seatReservations[i][j][k] != 0) total_viewers++;
            }
        }
        float slot_revenue = total_viewers * cinema.movieSlots[i]->price;

        cout << '|' << setw(8) << i+1 << '|'
                    << setw(19) << cinema.movieSlots[i]->name << '|'
                    << setw(25) << cinema.movieSlots[i]->price << '|'
                    << setw(17) << total_viewers << '|'
                    << setw(13) << slot_revenue << '|' << endl;
        
        total_revenue += slot_revenue;
    }
    cout << "########################################################################################" << endl;
    cout << setw(87) << "Total revenue for the day: " + to_string(total_revenue)<< endl; 

    cout << "\n1. Return to main menu" << endl;
    cout << "\n > "; int choice; cin >> choice;
    return;
}

void addSlot()
{
    unsigned choice;
    if (cinema.movieSlots.size() + 1 > cinema.movieCount) // If slots are full
    {
        cout << "Slots are full." << endl;
        cout << "\n1. Return to main menu" << endl;
        cout << "\n > "; cin >> choice;
        return;
    }
    cout << "Enter the name of the movie: ";
    cin.ignore(); char m_name[30]; cin.getline(m_name, 30);
    for (int i = 0; i < movieList.size(); i++)
    {
        if (strcmp(movieList[i].name, m_name) == 0)
        {
            if (dateChecksOut(movieList[i], today_date))
            {
                cinema.movieSlots.push_back(make_shared<Movie>(movieList[i]));
            }
            else // if it's out of date, either early or expired
            {
                system ("cls");

                cout << "Movie is out of date." << endl;
                cout << "\n1. Return to main menu" << endl;
                cout << "\n > "; cin >> choice;
                return;
            }
            break;
        }
    }
}

unsigned getChoice()
{
    cout << "\n > "; unsigned choice; cin >> choice;
    return choice;
}

template <typename T> void swapped(T& one, T& other)
{
    T temp = one;
    one = other;
    other = temp;
}

// MOVIE MANAGEMENT BEGINS
void loadMovies()
{
   fstream movieLoad("movies.txt", ios::in);
    
    if (!isEmpty(movieLoad))
    {
        while (!movieLoad.eof())
        {
            // Holds info on a single movie
            vector<string> movieInfo;
            string line, word;

            getline(movieLoad, line);

            // The last line is always empty, so...
            if (!line.empty())
            {
                // We are going to have to manually change each
                // value to its respective data type if needed
                string separator = ",,";
                size_t start = line.find_first_not_of(separator);   // First word start index
                while (start != string::npos)                     // Find the words
                {
                    size_t end = line.find_first_of(separator, start + 1);  // Find end of word
                    if (end == string::npos)                        // Found a separator?
                    end = line.length();                               // No, so set to end of text
                    movieInfo.push_back(line.substr(start, end - start));    // Store the word
                    start = line.find_first_not_of(separator, end + 1);  // Find first character of next word
                }
                Movie movie;

                strcpy(movie.name, movieInfo[0].c_str());
                strcpy(movie.genre, movieInfo[1].c_str());
                movie.price = stoi(movieInfo[2]);
                movie.entryDate = Date{stoi(movieInfo[3]), stoi(movieInfo[4]), stoi(movieInfo[5])};
                movie.exitDate = Date{stoi(movieInfo[6]), stoi(movieInfo[7]), stoi(movieInfo[8])};
                movie.ratingPg = Rating{stoi(movieInfo[9]), stoi(movieInfo[10])};

                movieList.push_back(movie);
            }
        }
    }
    movieLoad.close(); 
}

void dumpMovies()
{
    ofstream movieDump("movies.txt", ios::out | ios::trunc);

    for (auto movie : movieList)
    {
        movieDump << movie.name << ",,"
                    << movie.genre << ",,"
                    << movie.price << ",,"
                    << movie.entryDate.day << ",,"
                    << movie.entryDate.month << ",,"
                    << movie.entryDate.year << ",,"
                    << movie.exitDate.day << ",,"
                    << movie.exitDate.month << ",,"
                    << movie.exitDate.year << ",,"
                    << movie.ratingPg.movieRating << ",,"
                    << movie.ratingPg.viewerAge << '\n';
    }
    movieDump.close();
}
// MOVIE MANAGEMENT ENDS

// CUSTOMER MANAGEMENT BEGINS
void loadCustomers()
{
    fstream customerLoad("customers.txt", ios::in);

    // This is done in a similar fasion to that of movies
    if (!isEmpty(customerLoad))
    {
        while (!customerLoad.eof())
        {
            vector<string> customerInfo;
            string line, word;

            getline(customerLoad, line);

            // The last line is always empty, so...
            if (!line.empty())
            {
                // We are going to have to manually change each
                // value to its respective data type if needed
                string separator = ",,";
                size_t start = line.find_first_not_of(separator);   // First word start index
                while (start != string::npos)                     // Find the words
                {
                    size_t end = line.find_first_of(separator, start + 1);  // Find end of word
                    if (end == string::npos)                        // Found a separator?
                    end = line.length();                               // No, so set to end of text
                    customerInfo.push_back(line.substr(start, end - start));    // Store the word
                    start = line.find_first_not_of(separator, end + 1);  // Find first character of next word
                }
                Customer customer;

                strcpy(customer.name, customerInfo[0].c_str());
                customer.age = stoi(customerInfo[1]);
                customer.id = stoi(customerInfo[2]);

                customerList.push_back(customer);
            }
        }
    }

    customerLoad.close();
}

void dumpCustomers()
{
    ofstream customerDump("customers.txt", ios::out | ios::trunc);

    for (auto customer : customerList)
    {
        customerDump << customer.name << ",,"
                        << customer.age << ",,"
                        << customer.id << '\n';
    }

    customerDump.close();
}
// CUSTOMER MANAGEMENT ENDS

// CINEMA MANAGEMENT BEGINS
void loadCinema()
{
    fstream cinemaLoad("slots.txt", ios::in);
    
    if (!isEmpty(cinemaLoad))
    {
        while (!cinemaLoad.eof())
        {
            // Holds info on a single movie
            vector<string> movieInfo;
            string line, word;

            getline(cinemaLoad, line);

            // The last line is always empty, so...
            if (!line.empty())
            {
                // We are going to have to manually change each
                // value to its respective data type if needed
                string separator = ",,";
                size_t start = line.find_first_not_of(separator);   // First word start index
                while (start != string::npos)                     // Find the words
                {
                    size_t end = line.find_first_of(separator, start + 1);  // Find end of word
                    if (end == string::npos)                        // Found a separator?
                    end = line.length();                               // No, so set to end of text
                    movieInfo.push_back(line.substr(start, end - start));    // Store the word
                    start = line.find_first_not_of(separator, end + 1);  // Find first character of next word
                }
                Movie movie;

                strcpy(movie.name, movieInfo[0].c_str());
                strcpy(movie.genre, movieInfo[1].c_str());
                movie.price = stoi(movieInfo[2]);
                movie.entryDate = Date{stoi(movieInfo[3]), stoi(movieInfo[4]), stoi(movieInfo[5])};
                movie.exitDate = Date{stoi(movieInfo[6]), stoi(movieInfo[7]), stoi(movieInfo[8])};
                movie.ratingPg = Rating{stoi(movieInfo[9]), stoi(movieInfo[10])};

                cinema.movieSlots.push_back(make_shared<Movie>(movie));
            }
        }
    }
    cinemaLoad.close();

    cinemaLoad.open("reservations.txt");
    if (!isEmpty(cinemaLoad))
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 8; j++)
                for (int k = 0; k < 8; k++)
                {
                    string value;
                    cinemaLoad >> value;
                    cinema.seatReservations[i][j][k] = stoi(value);
                }
    }
    cinemaLoad.close();
}

void dumpCinema()
{
    ofstream cinemaDump("slots.txt", ios::out);

    for (auto moviep : cinema.movieSlots)
    {
        cinemaDump << moviep->name << ",,"
                    << moviep->genre << ",,"
                    << moviep->price << ",,"
                    << moviep->entryDate.day << ",,"
                    << moviep->entryDate.month << ",,"
                    << moviep->entryDate.year << ",,"
                    << moviep->exitDate.day << ",,"
                    << moviep->exitDate.month << ",,"
                    << moviep->exitDate.year << ",,"
                    << moviep->ratingPg.movieRating << ",,"
                    << moviep->ratingPg.viewerAge << '\n';
    }
    cinemaDump.close();

    cinemaDump.open("reservations.txt");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                cinemaDump << cinema.seatReservations[i][j][k] << '\n';
    cinemaDump.close();
}
// CINEMA MANAGEMENT ENDS