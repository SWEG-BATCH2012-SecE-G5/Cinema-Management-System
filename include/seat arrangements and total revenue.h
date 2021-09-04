#include<iostream>
using namespace std;
int custrow = 0;   //number of the row the customer enters
int custcol = 0;  //number of the row the customer enters
int nrows =r ; //number of rows of the cinema 
int ncols = c; //number of columns of the cinema
int answer,total,cost;
int ticketsold=0;
int total number of seats = seats
char TAKEN = '#'; //seats taken
char seating[r][c]; //array that holds seating arrangements

void displayseats(int ncols int nrows int seating[][]){

for (int count = 0; count < c; count++)
		{
			cout << endl << "Column " << (count + 1);
			
		}

for (int countt = 0; countt < r; countt++)
		{
			cout << endl << "Row " << (countt + 1);
			for (int count2 = 0; count2 < c; count2++)
			{
				cout << " " <<  seating[countt] [countt2];
			}
		}
			cout << endl;


}

void reserveseats(int& seats int& ticketsold int seating[][] int& total int cost){
cout>>"There are ">>seats>>"available">>endl;
for(int i=0; i<r;i++){
for(int j=0; j<c;j++)
if(seating[r][c] !== '#'){
cout>>" ">>seating[r][c];
}
}
cout << "Please select the row you would like to sit in: ";
cin >> custrow;
cout << "Please select the seat you would like to sit in: ";
cin >> custcol;
	if (seating[custrow] [custcol] == '#')
			{
				cout << "Sorry that seat is sold-out, Please select a new seat.";
				cout << endl;
						}
	else 
			{
				
				total = total + cost;
				cout << "That ticket costs: " << cost << endl;
				cout << "Confirm Purchase? Enter (1 = YES / 2 = NO)";
				cin >> answer;
				
						
						if (answer == 1)
						{ 
							cout << "Your ticket purchase has been confirmed." << endl;
							seating[custrow][custcol] = TAKEN;
                                                        ticketsold++;
                                                        seats = seats - 1;
						}

                                                else if (answer == 2)
						{
							cout << "Thank you for visting our website";
							cout << endl;
							
						}


}
 void revenue(int ticketsold int cost){
 cout<<"Total revenue in ticket sales : "<<ticketsold*cost<<"$"<<endl;}