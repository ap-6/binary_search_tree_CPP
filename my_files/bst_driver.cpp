/********************************************************************************************
Name: Anthony Polese		                                 Z#: Z23582157
Course: Date Structures and Algorithm Analysis (COP3530) Professor: Dr. Lofton Bullard
Due Date: 04/16/2021 	                                 Due Time: 11:59pm
Total Points: 25                                         Assignment 11: Binary Search Trees

Description: This assignment involves implementing a binary search tree class.
			 Each node stores a county's name and its population count (taken
			 from the given "county_data.txt" file. The class has insert, delete,
			 and search functions as well as a function to print all counties and their
			 populations in alphabetical order, a function to print all counties
			 and their populations within a given alphabet range, and a function
			 to print all county names and populations in alphabetical order to
			 a file named �county_info.txt�.
*********************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
using namespace std;

int main( )
{
	cout << "**************************************************************" << endl;
	cout << "Test1: default constructor" << endl;

	bst  myTree;

	cout << "Print contents of bst in order to the screen" << endl << endl;
	myTree.print_tree();
	cout << "*************End Test1*****************************************" << endl;
	cout << endl << endl;

	cout << "**************************************************************" << endl;
	cout << "Test2: insert" << endl;

	myTree.insert("New County", 234658);
	cout << endl << "Print contents of bst in order to the screen" << endl << endl;;
	myTree.print_tree();
	cout << "*************End Test2*****************************************" << endl;
	cout << endl << endl;

	cout << "**************************************************************" << endl;
	cout << "Test3: county_ranges" << endl;
	cout << "Print contents of bst range between B and K in order to the screen" << endl << endl;;
	myTree.county_ranges("B", "K");
	cout << "*************End Test3*****************************************" << endl;
	cout << endl << endl;

	cout << "**************************************************************" << endl;
	cout << "Test4: del_name" << endl;
	myTree.del_name("Miami Dade");
	cout << endl << "Print contents of bst in order, with Miami Dade removed, to the screen" << endl << endl;;
	myTree.print_tree();
	cout << "*************End Test4*****************************************" << endl;
	cout << endl << endl;

	cout << "**************************************************************" << endl;
	cout << "Test5: sorted_info" << endl << endl;
	cout << "Print contents of bst in order to the output file, county_info.txt, with name and associated population size shown" << endl << endl;
	myTree.sorted_info();
	cout << "*************End Test5*****************************************" << endl;
	cout << endl << endl;

	cout << "**************************************************************" << endl;
	cout << "Test6: empty_tree" << endl << endl;
	myTree.empty_tree();
	cout << endl << "Print contents of an empty bst to the screen" << endl << endl;;
	myTree.print_tree();
	cout << "*************End Test6*****************************************" << endl;
	cout << endl << endl;

	return 0;
}


