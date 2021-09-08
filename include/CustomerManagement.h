#ifndef CUSTOMERMANAGEMENT_H
#define CUSTOMERMANAGEMENT_H

#include "Customer.h"

#include <iostream>
#include <cctype>
#include <string>
#include <iomanip>

// We are going to use a struct that manages everything
// the manager might need to interact with their customer database, 
// like dynamically adding new customers to the list, modifying them, 
// deleting them, sorting them, etc...

struct CustomerList {
    // This is where the customers will be kept
    Customer *customer_list;

    // The current amount of movies in stock
    unsigned customer_count = 0;

    // The first-issued customer id
    unsigned customer_id = 1000;

    // Function that registers customer and passes
    // said customer to add_customer
    void register_customer();

    // A function that adds a customer into the database
    void add_customer(Customer &);

    // A function that modifies info about selected customer
    void modify_customer(unsigned &);

    // A function that deletes a customer from the database
    void delete_customer(unsigned &);

    // A function that sorts the list by age
    void sort_by();

    // Returns customer for a given id value
    Customer *find_customer(int);

    // Menu for accessing the functions above
    void customer_menu();

    unsigned& get_count() { return customer_count; }
};

// Function Definitions

Customer *CustomerList::find_customer(int id)
{
    for (int i = 0; i < customer_count; i++)
    {
        if (customer_list[i].id == id)
        {
            return customer_list + i;
        }
    }
    return nullptr;
}
void CustomerList::register_customer()
{
    system ("cls");

    Customer customer;

    std::cin.ignore();
    std::cout << "Enter customer name : "; std::getline(std::cin, customer.name);
    std::cout << "Enter customer age: "; std::cin >> customer.age;

    add_customer(customer);

    if (customer_count == 1) customer_menu(); // Initializer, automatically
    // redirects to the main menu after first customer is registered
}

void CustomerList::add_customer(Customer &customer)
{
    if (!customer_count) // if a movie doesn't exist yet...
    {
        customer_count++;
        customer_list = new Customer[customer_count];
        customer.id = customer_id++;

        *customer_list = customer;
    }
    else
    {
        // Make a copy that can handle the current amount of customers
        Customer *copy = new Customer[customer_count + 1]; 
        for (int i = 0; i < customer_count; i++)
        {
            *(copy + i) = *(customer_list + i);
        }
        customer.id = customer_id++;
        *(copy + customer_count) = customer;

        // free currently used memory
        delete[] customer_list;
        customer_list = nullptr; 

        // Make the customer_list point to an array that can hold
        // the required amount of customer data
        customer_count++;
        customer_list = new Customer[customer_count];
        for (int i = 0; i < customer_count; i++)
        {
            *(customer_list + i) = *(copy + i);
        }

        // release memory held by the copy
        delete[] copy;
        copy = nullptr;
    }   
}

void CustomerList::modify_customer(unsigned &index)
{
    system ("cls");

    Customer *current = customer_list + index;

    std::cout << "What do you want to modify?" << std::endl << std::endl;
    std::cout << "1. Name" << std::endl;
    std::cout << "2. Age" << std::endl;
    std::cout << "3. Return to main menu" << std::endl;

    INPUT6:
    std::cout << "\n > "; unsigned choice; std::cin >> choice;

    switch(choice)
    {
    case 1:
        std::cin.ignore();
        std::cout << "New name: "; std::getline(std::cin, current->name);
        break;
    
    case 2:
        std::cout << "New age: "; std::cin >> current->age;
        break;
    
    case 3:
        return;
        break;
    
    default:
        std::cout << "Invalid input, try again." << std::endl;
        goto INPUT6;
    }

    // Make the current pointer invalid, lest it modifies
    // the actual data
    current = nullptr;
}

void CustomerList::delete_customer(unsigned &index)
{
    // Make two arrays to take in the values before and
    // after the deleted value respectively

    unsigned l_size = index;
    unsigned r_size = customer_count - index - 1;

    if (r_size == 0) // if we are asked to delete the last movie...
    {
        customer_count--; // ...just deny access to it
        return;
    }

    Customer *copy_left = new Customer[l_size];
    Customer *copy_right = new Customer[r_size];

    for (int i = 0; i < l_size; i++)
    {
        *(copy_left + i) = *(customer_list + i);
    }

    for (int i = 0; i < r_size; i++)
    {
        *(copy_right + i) = *(customer_list + i + l_size + 1);
    }

    delete[] customer_list;
    customer_list = nullptr;

    customer_count--;

    customer_list = new Customer[customer_count];

    // All that's left is to stich it back
    // and return the resultant data 
    // to the main container
    for (int i = 0; i < l_size; i++)
    {
        *(customer_list + i) = *(copy_left + i);
    }

    for (int i = l_size; i < customer_count; i++)
    {
        *(customer_list + i) = *(copy_right + i - l_size);
    }

    // Make the temporary pointers invalid
    copy_left = nullptr;
    copy_right = nullptr;
}

void CustomerList::sort_by()
{
    system ("cls");

    std::cout << "1. Age" << std::endl;
    std::cout << "2. Return to previous menu" << std::endl;

    INPUT7:
    std::cout << "\n > "; unsigned choice; std::cin >> choice;
    
    switch (choice)
    {
    case 1: 
        std::cout << "Enter the minimum age: "; unsigned m_age; std::cin >> m_age;

        system ("cls");

        std::cout << "#####################################" << std::endl;
        std::cout << '|' << std::setw(5) << "ID"
                    << '|' << std::setw(25) << "Name"
                    << '|' << std::setw(3) << "Age" << '|' << std::endl;
        std::cout << "#####################################" << std::endl;
        for (int i = 0; i < customer_count; i++)
        {
            if (customer_list[i].age >= m_age)
            {
                std::cout << '|' << std::setw(5) << customer_list[i].id
                            << '|' << std::setw(25) << customer_list[i].name
                            << '|' << std::setw(3) << customer_list[i].age << '|' << std::endl;
            }
        }
        std::cout << "######################################" << std::endl << std::endl;

        std::cout << "1. Return to previous menu" << std::endl;
        
        INPUT1:
        std::cout << "\n > "; unsigned choice; std::cin >> choice;
        
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

    case 2: 
        break;

    default:
        std::cout << "Invalid input, try again." << std::endl;
        goto INPUT7;
    }
}

void CustomerList::customer_menu()
{
    START_CUSTOMER:
    system ("cls");

    if (customer_count) // If customer(s) exist already...
    {
        std::cout << "#####################################" << std::endl;
        std::cout << '|' << std::setw(5) << "ID"
                    << '|' << std::setw(25) << "Name"
                    << '|' << std::setw(3) << "Age" << '|' << std::endl;
        std::cout << "#####################################" << std::endl;
        for (int i = 0; i < customer_count; i++)
        {
            std::cout << '|' << std::setw(5) << customer_list[i].id
                        << '|' << std::setw(25) << customer_list[i].name
                        << '|' << std::setw(3) << customer_list[i].age << '|' << std::endl;
        }
        std::cout << "#####################################" << std::endl << std::endl;

        std::cout << "1. Register a new customer" << std::endl;
        std::cout << "2. Modify an existing customer" << std::endl;
        std::cout << "3. Remove a customer from the database" << std::endl;
        std::cout << "4. Sort by..." << std::endl;
        std::cout << "5. Return to main menu" << std::endl;

        INPUT8:
        std::cout << "\n > "; unsigned choice; std::cin >> choice;
        switch (choice)
        {
        case 1:
            register_customer();
            goto START_CUSTOMER;
            break;
        
        case 2:
            std::cout << "Enter the ID of the customer: "; std::cin >> choice;
            while (choice > customer_id || choice < 1000)
            {
                std::cout << "\nInvalid input, try again." << std::endl;
                std::cout << "\n > "; std::cin >> choice;
            }
            choice -= 1000;
            modify_customer(choice);
            goto START_CUSTOMER;
            break;
        
        case 3:
            std::cout << "Enter the ID of the customer: "; std::cin >> choice;
            while (choice > customer_id || choice < 1000)
            {
                std::cout << "\nInvalid input, try again." << std::endl;
                std::cout << "\n > "; std::cin >> choice;
            }
            choice -= 1000;
            delete_customer(choice);
            goto START_CUSTOMER;
            break;
        
        case 4:
            sort_by();
            goto START_CUSTOMER;
            break;

        case 5:
            return;
            break;

        default:
            std::cout << "Invalid input, try again." << std::endl;
            goto INPUT8;
            break;
        }
    }
    else // no customers yet
    {
        system ("cls");

        std::cout << "Seems like you haven't added any customers yet. Care to add one?" << std::endl << std::endl;
        std::cout << "1. Register customer" << std::endl;
        std::cout << "2. Return to Main Menu" << std::endl;

        INPUT9:
        std::cout << "\n > "; unsigned choice; std::cin >> choice;
        switch(choice)
        {
        case 1:
            register_customer();
            break;
        
        case 2:
            break;
        
        default:
            std::cout << "Invalid input, try again." << std::endl;
            goto INPUT9;
        }
    }  
}

#endif // CUSTOMERMANAGEMENT_H