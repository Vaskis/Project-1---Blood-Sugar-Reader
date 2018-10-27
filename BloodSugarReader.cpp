// BloodSugarReader.cpp
// COSCO 2030
// Jeremiah Vaskis
// 10/10/2018
// Project 1

// See Project 1 Document for Requirements

#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;			// Required to read strings & convert them to numbers

#include<iomanip>
using std::setw;

#include<stdio.h>
#include<stdlib.h>
using std::abs;

#include<array>
using std::size;

#include<algorithm>
using std::fill_n;

#include <string>			// Required to read strings & convert them to numbers
using std::getline;			// Required to read strings & convert them to numbers

#include <sstream>			// Required to read strings & convert them to numbers
using std::istringstream;	// Required to read strings & convert them to numbers



int main() {

	// Used for options selection
	string Next1 = "Next";
	string Next2 = "N";
	string Day1 = "Day";
	string Day2 = "D";
	string Week1 = "Week";
	string Week2 = "W";
	string IString = "";	// Input String
	istringstream buffer;	// Buffer used to read strings or convert them to numbers


	// Day Array - 2D
	const int DayRows = 5;
	const int DayColumns = 14;
	int Day[DayRows][DayColumns] = { {0} };		// Fill with 0's
	// Array Format:
	//
	//			Day 1		Day k		Day 14
	// Max		Day[0][0]	Day[0][k]	Day[0][13]
	// Min		Day[1][0]	Day[1][k]	Day[1][13]
	// Count	Day[2][0]	Day[2][k]	Day[2][13]
	// SumRem	Day[3][0]	Day[3][k]	Day[3][13]
	// SumOvF	Day[4][0]	Day[4][k]	Day[4][13]

	// Week Array - 2D
	const int WeekRows = 7;
	const int WeekColumns = 2;
	int Week[WeekRows][WeekColumns] = { {0} };	// Fill with 0's
	// Array Format:
	//
	//				Week 1		Week j		Week 2
	// Max			Week[0][0]	Week[0][j]	Week[0][1]
	// Min			Week[1][0]	Week[1][j]	Week[1][1]
	// Count		Week[2][0]	Week[2][j]	Week[2][1]
	// SumRem		Week[3][0]	Week[3][j]	Week[3][1]
	// SumOvF		Week[4][0]	Week[4][j]	Week[4][1]
	// Delta		Week[5][0]	Week[5][j]	Week[5][1]
	// DayOfDelta	Week[6][0]	Week[6][j]	Week[6][1]

	// Rows that Particular Data is in (Makes Reading/Manipulation easier)
	const int Max = 0;
	const int Min = 1;
	const int Count = 2;
	const int Sum = 3;
	const int SumOvF = 4;
	const int Delta = 5;
	const int DayOfDelta = 6;
	
	// Initialization of Delta Variables
	int Delta_Value = 0;
	int DayOfDelta_Value = 0;

	// Initialization of Input Variable Data
	int Data = 0;

	// Flags
	bool ValidInput = false;
	bool EndOfDays = false;

	// Indexes
	int k = 0;	// Day	Index
	int j = 0;	// Week	Index

	// Used to activate Delta Calculator
	int LowBoundDelta = 0;
	int HighBoundDelta = 7;

	// Initial Description of Program
	cout << "Integer Blood Sugar Reader" << endl;
	cout << "Records Data for 14 Days" << endl;
	cout << "Summarizes the Data into 2 Weeks" << endl;
	cout << "Ignores negative values, zeros, and values equal to or above "<< INT_MAX << endl << endl;
	cout << "Type \"N\" or \"Next\"  to go to the next Day" << endl;
	cout << "Type \"D\" or \"Day\"   to see   the Day's  Data Summary" << endl;
	cout << "Type \"W\" or \"Week\"  to see   the Week's Data Summary" << endl << endl;
	cout << "Max\t\t- The Maximum reading so far" << endl;
	cout << "Min\t\t- The Minimum reading so far" << endl;
	cout << "Count\t\t- The number of readings so far" << endl;
	cout << "SumRem\t\t- Sum's Remainder (No Overflow means true Sum)" << endl;
	cout << "SumOvF\t\t- Times Sum Overflowed with a value above " << INT_MAX << endl;
	cout << "Delta\t\t- The greatest difference in number of counts per Day" << endl;
	cout << "DayOfDelta\t- The particular Day that shows the greatest change in Delta" << endl;
	cout << endl << "Enter Integer Blood Pressure Readings:" << endl << endl;


	while (EndOfDays == false) {
		
		// Reset ValidInput (otherwise loops forever)
		ValidInput = false;

		// Will continually pester the user for correct input until it gets it
		while ((ValidInput == false) && (EndOfDays == false)) {
			
			//________________________________________________________________________________________
			//		Old Integer Input Method Below
			//________________________________________________________________________________________

			// Old Version of Data input
			// (would ignore all non-numerical inputs when tied with later else-case
			// that had cin.clear() and cin.ignore())
			
			//cout << "Day: "<< setw(2) << k + 1 << " (N, Next) (D, Day) (W, Week): ";
			//cin >> Data;

			//________________________________________________________________________________________
			//		Old Integer Input Method Above
			//		New String  Input Method Below
			//________________________________________________________________________________________
			cout << "Day: " << setw(2) << k + 1 << " (N, Next) (D, Day) (W, Week): ";
			getline(cin, IString);

			// If Valid String
			if (IString == Next1 | IString == Next2 | IString == Day1 | IString == Day2 | IString == Week1 | IString == Week2) {
				if (IString == Next1 | IString == Next2) {
					Data = -1;				// Go to Next Day
					ValidInput = false;		// Reset Flag
				}
				if (IString == Day1 | IString == Day2) {
					Data = -2;				// Go to Day Summary
					ValidInput = false;		// Reset Flag
				}
				if (IString == Week1 | IString == Week2) {
					Data = -3;				// Go to 
					ValidInput = false;		// Reset Flag
				}
			}

			// Else Convert to Number
			else {
				// Code that converts a String to it's Numerical version, ignoring tailing garbage
				buffer.str(IString);	// Converts String to Number?
				buffer >> Data;			// Inputs Value to Data
				buffer.clear();			// Clears buffer

				// If Value is NOT valid
				if (Data <= 0 | Data == INT_MAX) {
					cout << "<!!!!! Value is not Valid Input !!!!!>"<< endl << endl ;
					Data = 0;				// Data is not valid, set to 0
					ValidInput = false;		// Reset Flag
				}
				ValidInput = true;			// Set Flag
				IString = "XXX";			// Reset String
			}
			//________________________________________________________________________________________
			//		New String Input Method Above
			//________________________________________________________________________________________

			// Valid Input
			if (Data > 0) {
				ValidInput = true;
			}

			// Next Day
			else if (Data == -1) {
				k = k + 1;								// Go to next Day
				
				// Check if need to index to next Week
				if (k == HighBoundDelta) {
					j = j + 1;							// Go to next Week
					LowBoundDelta = HighBoundDelta;
					HighBoundDelta = HighBoundDelta + 7;
					if (k == DayColumns) {
						EndOfDays = true;				// May be redundent, but just to make sure
					}
				}
				
				ValidInput = false;	// Reset Flag
				Data = 0;			// Reset Data
			}

			// Display Current Day Summary
			else if (Data == -2) {
				cout << endl;
				cout << "Day " << k + 1 << " Summary" << endl;
				cout << "\tDay:\t"		<< setw(4) << k + 1 << endl;
				cout << "\tMax:\t"		<< setw(4) << Day[Max][k]		<< endl;
				cout << "\tMin:\t"		<< setw(4) << Day[Min][k]		<< endl;
				cout << "\tCount:\t"	<< setw(4) << Day[Count][k]		<< endl;
				cout << "\tSumRem:\t"	<< setw(4) << Day[Sum][k]		<< endl;
				cout << "\tSumOvF:\t"	<< setw(4) << Day[SumOvF][k]	<< endl;
				cout << endl;
				ValidInput = false;	// Reset Flag
				Data = 0;			// Reset Data
			}

			// Display Current Week Summary
			else if (Data == -3) {
				cout << endl;
				cout << "Week " << j + 1 << " Summary" << endl;
				cout << "\tWeek:\t\t"		<< setw(4) << j + 1 << endl;
				cout << "\tMax:\t\t"		<< setw(4) << Week[Max][j]		<< endl;
				cout << "\tMin:\t\t"		<< setw(4) << Week[Min][j]		<< endl;
				cout << "\tCount:\t\t"		<< setw(4) << Week[Count][j]	<< endl;
				cout << "\tSumRem:\t\t"		<< setw(4) << Week[Sum][j]		<< endl;
				cout << "\tSumOvF:\t\t"		<< setw(4) << Week[SumOvF][j]	<< endl;
				cout << "\tDelta:\t\t"		<< setw(4) << Week[Delta][j]	<< endl;
				cout << "\tDayOfDelta:\t"	<< setw(4) << Week[DayOfDelta][j] << endl;
				cout << endl;
				ValidInput = false;	// Reset Flag
				Data = 0;			// Reset Data
			}

			//________________________________________________________________________________________
			// Boxed code Below was needed when using the Old Integer Input Method
			//________________________________________________________________________________________
			//// Anything Else is Garbage
			//else {
			//	cout << endl << "Garbage Value" << endl;
			//	//cin.clear();
			//	//cin.ignore();
			//	ValidInput = false;
			//	Data = 0;	// Reset Data
			//}
			//________________________________________________________________________________________
			// Boxed code Above was needed when using the Old Integer Input Method
			//________________________________________________________________________________________


			// Reached the End of Days?
			if (k >= DayColumns) {
				EndOfDays = true;
			}
		}

		// Only Update Values if Data is worth reading
		// Should also prevent negative values from being stored
		if ((ValidInput = true) && (Data > 0)) {

			// Day Updates ________________________________________
			if ((Data > Day[Max][k]) | (Day[Max][k] == 0)) {
				Day[Max][k] = Data;					// Max Update
			}
			if ((Data < Day[Min][k]) | (Day[Min][k] == 0)) {
				Day[Min][k] = Data;					// Min Update
			}

			Day[Count][k] = Day[Count][k] + 1;		// Count Update

			// Check if OVERFLOW occurs
			if (Data > (INT_MAX - Day[Sum][k])) {
				Day[SumOvF][k]++;								// Increment Overflow Counter
				Day[Sum][k] = Data - (INT_MAX - Day[Sum][k]);	// Capture the Remainder
			}
			else {
				Day[Sum][k] = Day[Sum][k] + Data;	// Sum Update
			}

			// Week Updates ________________________________________
			if (((Day[Max][k]) > (Week[Max][j])) | (Week[Max][j] == 0)) {
				Week[Max][j] = Day[Max][k];			// Max Update
			}
			if (((Day[Min][k]) < (Week[Min][j])) | (Week[Min][j] == 0)) {
				Week[Min][j] = Day[Min][k];			// Min Update
			}

			Week[Count][j] = Week[Count][j] + 1;	// Count Update

			// Check if OVERFLOW occurs
			if (Data > (INT_MAX - Week[Sum][j])) {
				Week[SumOvF][j]++;								// Increment Overflow Counter
				Week[Sum][j] = Data - (INT_MAX - Week[Sum][j]);	// Capture the Remainder
			}
			else {
				Week[Sum][j] = Week[Sum][j] + Data;				// Sum Update
			}

			// Delta update
			if ((k >= LowBoundDelta) && (k < HighBoundDelta)) {
				Delta_Value = abs(Day[Count][k] - Day[Count][k - 1]);
				if (Delta_Value > Week[Delta][j]) {
					Week[Delta][j] = Delta_Value;				// Delta Update
					Week[DayOfDelta][j] = k + 1;				// Because of 0 indexing (Day 1, k = 0)
				}
			}

			ValidInput = false;	// Reset Flag
			Data = 0;			// Reset Data
		}

		// Reached the END OF DAYS!?
		if (k >= DayColumns) {
			EndOfDays = true;	// Set Flag
		}
	}


	// Prints all Day array information
	int WidthDay = 4;
	cout << endl << endl;
	cout << "Day Information:" << endl;
	for (int y = 0; y <= DayRows; y++) {
		if (y == 0) {
			cout << "Day: \t";
			for (int x = 0; x < DayColumns; x++) {
				cout << setw(WidthDay) << x + 1 << " ";
			}
		}
		if (y == 1) {
			cout << "Max: \t";
			for (int x = 0; x < DayColumns; x++) {
				cout << setw(WidthDay) << Day[Max][x] << " ";
			}
		}
		if (y == 2) {
			cout << "Min: \t";
			for (int x = 0; x < DayColumns; x++) {
				cout << setw(WidthDay) << Day[Min][x] << " ";
			}
		}
		if (y == 3) {
			cout << "Count: \t";
			for (int x = 0; x < DayColumns; x++) {
				cout << setw(WidthDay) << Day[Count][x] << " ";
			}
		}
		if (y == 4) {
			cout << "SumRem:\t";
			for (int x = 0; x < DayColumns; x++) {
				cout << setw(WidthDay) << Day[Sum][x] << " ";
			}
		}
		if (y == 5) {
			cout << "SumOvF:\t";
			for (int x = 0; x < DayColumns; x++) {
				cout << setw(WidthDay) << Day[SumOvF][x] << " ";
			}
		}
		cout << endl;
	}


	// Prints all Week array information
	int WidthWeek = 4;
	cout << endl << endl;
	cout << "Week Information:" << endl;
	for (int y = 0; y <= WeekRows; y++) {
		if (y == 0) {
			cout << "Week: \t\t";
			for (int x = 0; x < WeekColumns; x++) {
				cout << setw(WidthWeek) << x + 1 << " ";
			}
		}
		if (y == 1) {
			cout << "Max: \t\t";
			for (int x = 0; x < WeekColumns; x++) {
				cout << setw(WidthWeek) << Week[Max][x] << " ";
			}
		}
		if (y == 2) {
			cout << "Min: \t\t";
			for (int x = 0; x < WeekColumns; x++) {
				cout << setw(WidthWeek) << Week[Min][x] << " ";
			}
		}
		if (y == 3) {
			cout << "Count: \t\t";
			for (int x = 0; x < WeekColumns; x++) {
				cout << setw(WidthWeek) << Week[Count][x] << " ";
			}
		}
		if (y == 4) {
			cout << "SumRem: \t";
			for (int x = 0; x < WeekColumns; x++) {
				cout << setw(WidthWeek) << Week[Sum][x] << " ";
			}
		}
		if (y == 5) {
			cout << "SumOvF: \t";
			for (int x = 0; x < WeekColumns; x++) {
				cout << setw(WidthWeek) << Week[SumOvF][x] << " ";
			}
		}
		if (y == 6) {
			cout << "Delta: \t\t";
			for (int x = 0; x < WeekColumns; x++) {
				cout << setw(WidthWeek) << Week[Delta][x] << " ";
			}
		}
		if (y == 7) {
			cout << "DayOfDelta: \t";
			for (int x = 0; x < WeekColumns; x++) {
				cout << setw(WidthWeek) << Week[DayOfDelta][x] << " ";
			}
		}
		cout << endl;
	}

	// Easter Egg Output
	cout << endl << "Congratulations, you made it this far." << endl;
	cout << "You deserve a glazed, sprinkled, jelly-filled donut." << endl << endl;

	system("pause");

	return 0;
}