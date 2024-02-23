
#include <iostream>
#include <string>
#include <fstream> //for file streams
#include <cstdlib> //for exit(1)
#include <cctype>  //for isdigit()
#include "bst.h"

using namespace std;

/**************************************************************************************************
Name:			Default constructor
Pre-Conditon:	Current object does not exist.
Post-Condition: Current object has been initialized with "county_data.txt"'s county infortmation
Description:    This default constructor uses "county_data.txt"'s county and population data
				to create a binary search tree, with each treenode object containing 
				a "county_name" string data, a "population_size" double data, and left and right
				child pointers ("lchild" and "rchild"). Nodes are arranged such that
				inorder traversal will output nodes in alphabetical order.
**************************************************************************************************/
bst::bst()
{
	root = 0;
	cout.setf(ios::fixed);	//turns off scientific notation for output stream
	cout.precision(0);		//removes trailing 0s from output

	//opening county_data.txt
	ifstream in_stream;
	in_stream.open("county_data.txt");
	if (in_stream.fail())
	{
		cout << "Input file unable to be opened. Program will now end." << endl;
		exit(1);
	}

	//transferring county_data.txt data to bst
	string next;									//stores each line of county_data.txt as the file is traversed
	string county_name;
	string pop_string;
	double pop_double;
	int pop_start,			//position of first number in "next" string
		pop_end,				//position of last number in "next" string
		pop_length;			//length of population in "next" string
	while ( getline(in_stream, next) )
	{
		//getting population from "next"
		pop_end = next.length() - 1; //position before '\0'

		int i = pop_end;             /*initalizing counter at last digit of
									   population in getline() string*/

		while (isdigit(next[i]))     /*decrements i until next[i] = the space before the
									   population starts*/
		{
			i--;
		}

		pop_start = i + 1;								 
		pop_length = pop_end - pop_start + 1;

		pop_string = next.substr(pop_start, pop_length); //stores population from "next"
		pop_double = stod(pop_string);					 //converts string to double
		
		//getting county name from "next"
		county_name = next.substr(0, i);					 //stores county name from "next"

		insert(county_name, pop_double);
	}
}

/**************************************************************************************************
Name:			Destructor
Pre-Conditon:	Current object may have nodes in its binary search tree or may not
Post-Condition: Current object is an empty binary search tree
Description:		Destructor deallocates all nodes in binary search tree by calling del_name()
				until no more nodes are remain.
**************************************************************************************************/
bst::~bst()
{
	while (root != 0)
	{
		del_name(root->county_name);
	}
}

/**************************************************************************************************
Name:			empty()
Pre-Conditon:	It is not known whether the current object's bst is empty or not
Post-Condition: It is known whether the current object's bst is empty or not
Description:		empty() returns true if the current object's bst is an empty bst, or
				false if the current object's bst is not an empty bst.
**************************************************************************************************/
bool bst::empty()
{
	return (root == 0);
}

/**************************************************************************************************
Name:			insert() (auxiliary function)
Pre-Conditon:	Current object's bst has n nodes
Post-Condition: The primary insert() function is called with the same "item" and "population"
				parameters
Description:		This insert() is an auxilary function to allow the user to insert a new
				county + population into the bst without having to be involved with using the
				root pointer, which is a private member. This function calls the primary 
				insert() function with the same given data but now with the root pointer 
				included.
**************************************************************************************************/
void bst::insert(const string& item, const double& population)
{
	insert(root, item, population);
}

/**************************************************************************************************
Name:			insert()
Pre-Conditon:	Current object's bst has n nodes
Post-Condition: Current object's bst has n + 1 nodes
Description:		insert() function inserts a new node with the given county name and population
				data into the bst in its correct position (the position that allows an
				inorder traversal to output the node data in alphabetical order). If the county
				is already in the bst, a message saying so will be outputted.
**************************************************************************************************/
void bst::insert(treenode*& loc_ptr, const string& item, const double& population)
{
	if (loc_ptr == 0)										//base case (item not already in tree)
	{
		loc_ptr = new treenode;								//new node
		loc_ptr->lchild = 0;									//set pointers
		loc_ptr->rchild = 0;
		loc_ptr->county_name = item;							//set county name
		loc_ptr->population_size = population;				//set county population
	}
	else if (loc_ptr->county_name > item)					//recursive left branch 
		insert(loc_ptr->lchild, item, population);
	else if (loc_ptr->county_name < item)					//recursive right branch 
		insert(loc_ptr->rchild, item, population);
	else														//base case (item is found in tree, no insert necessary)
		cout << "the item is already in the tree\n";
}

/**************************************************************************************************
Name:			search_tree() (auxiliary function)
Pre-Conditon:	It is not known whether or where a given county's node is in the current object's
				bst
Post-Condition: The primary search_tree() function is called with the same "item" parameter
Description:		This search_tree() is an auxilary function to allow the user to search for a node
				in the bst without having to be involved with using the root pointer, which is a 
				private member. This function calls the primary search_tree() function with the 
				same given "item" but now with the root pointer included.
**************************************************************************************************/
treenode * bst::search_tree(string item)
{
	return search_tree(root, item);
}

/**************************************************************************************************
Name:			search_tree()
Pre-Conditon:	It is not known whether or where a given county's node is in the current object's
				bst
Post-Condition: It is known whether and where a given county's node is in the current object's
				bst
Description:		search_tree() searchs the current object's bst for the given county name.
				If the county is found, a pointer to it is returned. If the county
				is not found, a pointer pointing to 0 is returned.
**************************************************************************************************/
treenode * bst::search_tree(treenode * loc_ptr, string item)
{
	if (loc_ptr != 0)
	{
		if (loc_ptr->county_name == item)						//base case (item found in tree)
			return loc_ptr;
		else if (loc_ptr->county_name > item)					//recursive left branch search
			return search_tree(loc_ptr->lchild, item);
		else														//recursive right branch search
			return search_tree(loc_ptr->rchild, item);
	}
	else													//base case (item not in tree)
		return loc_ptr;
}

/**************************************************************************************************
Name:			del_name() (auxiliary function)
Pre-Conditon:	Current object's bst has n nodes
Post-Condition: The primary del_name() function is called with the same "item" parameter
Description:		This del_name() is an auxilary function to allow the user to delete a given 
				county's node in the bst without having to be involved with using the root pointer, 
				which is a private member. This function calls the primary del_name() function with the 
				same given "item" but now with the root pointer included.
**************************************************************************************************/
void bst::del_name(string item)
{
	del_name(root, item);
}

/**************************************************************************************************
Name:			del_name()
Pre-Conditon:	Current object's bst has n nodes
Post-Condition: Current object's bst has n - 1 nodes (if "item" is in bst) or n nodes (if 
				"item" is not in bst)
Description:		del_name() function searches through current object's bst for the given
				county name ("item"). If it is found, the county's node is removed and the
				bst's remaining nodes are readjusted accordingly. If the county name is 
				not found in the bst, a message saying so it outputted to the screen.
**************************************************************************************************/
void bst::del_name(treenode * & loc_ptr, string item)
{
	if (loc_ptr == 0)							  //base case, (item not in tree)
		cout << "item not in tree\n";

	else if (item < loc_ptr->county_name)		  //recursive left branch search
		del_name(loc_ptr->lchild, item);

	else if (item > loc_ptr->county_name)		  //recursive right branch search
		del_name(loc_ptr->rchild, item);

	else											  //if item found (loc_ptr->county_name == item)
	{
		treenode * ptr;

		if (loc_ptr->lchild == 0)				  //if item has no left child
		{
			ptr = loc_ptr->rchild;				  //set new ptr to item's right child
			delete loc_ptr;						  //delete item
			loc_ptr = ptr;						  //re-assign item's pointer to right child
		}
		else if (loc_ptr->rchild == 0)			  //if item has no right child
		{
			ptr = loc_ptr->lchild;				  //set new ptr to item's left child
			delete loc_ptr;						  //delete item
			loc_ptr = ptr;						  //re-assign item's pointer to left child
		}
		else										  //if item has both left and right child
		{
			ptr = inorder_succ(loc_ptr);					 //ptr points to item's successor
			loc_ptr->county_name = ptr->county_name;		 //item's node's info is replaced with successor's node's info
			loc_ptr->population_size = ptr->population_size;
			del_name(loc_ptr->rchild, ptr->county_name); //recursive call to delete successor's original node
		}
	}

}

/**************************************************************************************************
Name:			inorder_succ()
Pre-Conditon:	The address of the alphabetical successor of the node pointed to by 
				loc_ptr is not known
Post-Condition: The address of the alphabetical successor of the node pointed to by 
				loc_ptr is known
Description:		inorder_succ() determines the address of the node that is the alphabetical
				successor of the node pointed to by loc_ptr and returns a pointer pointing
				to this successor
**************************************************************************************************/
treenode * bst::inorder_succ(treenode * loc_ptr)
{
	treenode *ptr = loc_ptr->rchild;		//new ptr points to right child of loc_ptr

	while (ptr->lchild != 0)				//set new ptr to its left child until no more left children are found
	{
		ptr = ptr->lchild;
	}
	return ptr;
}

/**************************************************************************************************
Name:			county_ranges() (auxiliary function)
Pre-Conditon:	The counties within the given alphabetical range are not displayed to the
				screen
Post-Condition: The primary county_ranges() function is called with the same "min_name"
				and "max_name" parameters
Description:		This del_name() is an auxilary function to allow the user to output the counties
				in the bst within the given range between "min_name" and "max_name" (inclusive) 
				without having to be involved with using the root pointer, which is a private member. 
				This function calls the primary county_ranges() function with the same given "min_name" 
				and "max_name" but now with the root pointer included.
**************************************************************************************************/
void bst::county_ranges(const string& min_name, const string& max_name)
{
	county_ranges(root, min_name, max_name);
}

/**************************************************************************************************
Name:			county_ranges()
Pre-Conditon:	The counties within the given alphabetical range are not displayed to the
				screen
Post-Condition: The counties within the given alphabetical range are displayed to the
				screen
Description:		county_ranges() function traverses the current object's bst from the beginning up 
				until a node is found with a county name alphabetically greater than "max_name"
				When within the range in which min_name <= node's county's name <= max_name,
				each county's name and population size is outputted to the screen.
**************************************************************************************************/
void bst::county_ranges(treenode*& loc_ptr, const string& min_name, const string& max_name)
{
	if (loc_ptr != 0)
	{
		//Left recursive
		county_ranges(loc_ptr->lchild, min_name, max_name);

		//Visit and process node
		if (loc_ptr->county_name >= min_name && loc_ptr->county_name <= max_name) //only outputs node's county 
		{																		  //name if in given range
			cout << loc_ptr->county_name << endl;
		}

		//Right recursive
		county_ranges(loc_ptr->rchild, min_name, max_name);
	}
}

/**************************************************************************************************
Name:			print_tree() (auxiliary function)
Pre-Conditon:	The counties stored in the current object's bst are not outputted to the screen
Post-Condition: The primary print_tree() function is called
Description:		This print_tree() is an auxilary function to allow the user to output all the counties
				in the bst in alphabetical order (both county name and population size)
				without having to be involved with using the root pointer, which is a private member. 
				This function calls the primary print_tree() function but now with the root pointer 
				included.
**************************************************************************************************/
void bst::print_tree()
{
	print_tree(root);
}

treenode* bst::search_tree(int data)
{
	return nullptr;
}

/**************************************************************************************************
Name:			print_tree()
Pre-Conditon:	The counties stored in the current object's bst are not outputted to the screen
Post-Condition: The counties stored in the current object's bst are outputted to the screen
				in alphabetical order with both county name and population size included
Description:		print_tree() performs an inorder traversal of the current object's bst and
				outputs each node's county name and population size along the way. The counties 
				are displayed in alphabetical order.
**************************************************************************************************/
void bst::print_tree(treenode *& loc_ptr)
{
	if (loc_ptr != 0)
	{
		//left branch recursive function call
		print_tree(loc_ptr->lchild);
		//output current node's name and population size
		cout << loc_ptr->county_name << " " << loc_ptr->population_size << endl;
		//right branch recursive function call
		print_tree(loc_ptr->rchild);
	}
}

/**************************************************************************************************
Name:			sorted_info() (auxiliary function)
Pre-Conditon:	"county_info.txt" does not contain the names and populations of all counties
				in alphabetical order
Post-Condition: The primary sorted_info() function is called with root and an ofstream that
				opened "county_info.txt" as parameters
Description:		This sorted_info() is an auxilary function to allow the user to output all the counties
				in the bst in alphabetical order (both county name and population size)
				to the "county_info.txt" file without having to be involved with using the root pointer, 
				which is a private member. This function calls the primary sorted_info() function 
				but now with the root pointer and an ofstream that opened "county_info.txt" as 
				parameters.
**************************************************************************************************/
void bst::sorted_info()
{
	//declaring an ofstream and initializing it
	ofstream out_stream;
	out_stream.open("county_info.txt");
	if (out_stream.fail()) {
		cout << "Output file opening failed. Program will now exit." << endl;
		exit(1);
	}

	//setting ofstream formatting
	out_stream.setf(ios::fixed); //turns off scientific notation for output stream
	out_stream.precision(0);		 //removes trailing 0s from output

	//function call to primary sorted_info()
	sorted_info(out_stream, root);
}

/**************************************************************************************************
Name:			sorted_info()
Pre-Conditon:	"county_info.txt" does not contain the names and populations of all counties
				in alphabetical order
Post-Condition:	"county_info.txt" contains the names and populations of all counties
				in alphabetical order
Description:		sorted_info() function performs an inorder traversal of current object's bst 
				and outputs each node's county name and population size to "county_info.txt"
				along the way. The traversal concludes with "county_info.txt" containing 
				all county names and population sizes in alphabetical order
**************************************************************************************************/
void bst::sorted_info(ostream& out_stream, treenode*& loc_ptr)
{
	if (loc_ptr != 0)
	{
		//left branch recursive function call
		sorted_info(out_stream, loc_ptr->lchild);
		//output country name and population size to out_stream
		out_stream << loc_ptr->county_name << " " << loc_ptr->population_size << endl;
		//right branch recursive function call
		sorted_info(out_stream, loc_ptr->rchild);
	}
}

/**************************************************************************************************
Name:			empty_tree()
Pre-Conditon:	Current object's bst has n nodes
Post-Condition: Current object's bst has 0 nodes
Description:		empty_tree() deallocates all nodes in the current object's bst until
				no nodes remain. root is reset to 0.
**************************************************************************************************/
void bst::empty_tree()
{
	while (root != 0)
	{
		del_name(root->county_name);
	}
}