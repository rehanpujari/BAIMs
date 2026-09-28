BAIM – Inventory & Billing Management System

A console-based Inventory and Billing Management System developed using the C programming language. This project demonstrates fundamental programming concepts such as structures, functions, file handling, input validation, and inventory management.

Features

Add new items to the inventory

Prevent duplicate item codes

Search for items using item codes

View all available inventory items

Process customer billing

Automatically update stock quantities after purchases

Calculate total bill amounts

Validate user input

Create an inventory backup

Store inventory data using file handling

Technologies Used

Programming Language: C

Libraries: stdio.h, stdlib.h, string.h

Concepts: Structures, Functions, File Handling, Loops, Conditional Statements, Input Validation

Project Structure
BAIM-Inventory-Billing-System/
│
├── main.c
├── README.md
└── .gitignore


The following files are generated automatically when the program runs:

items.txt
backup_items.txt

How It Works

The application provides a menu-driven interface:

============== BAIM System ==============
================= MENU =================
[1] Add Items
[2] Search Items
[3] View All Items
[4] Billing
[5] Exit

Add Items

Users can add new products by entering:

Item code

Item name

Quantity

Price

The program checks whether the item code already exists before adding a new item.

Search Items

Users can search for an inventory item by entering its unique item code.

View All Items

Displays all products currently stored in the inventory, including their:

Item code

Item name

Quantity

Price

Billing

The billing system allows users to purchase items by entering the item code and quantity. The program:

Checks whether the item exists.

Checks whether sufficient stock is available.

Calculates the subtotal.

Deducts the purchased quantity from inventory.

Calculates the total bill.

Data Backup

The program automatically creates backup_items.txt as a backup of the current inventory data.

File Handling

The project uses text files to store inventory information.

items.txt

Stores the current inventory data in the following format:

101,Laptop,5,75000.00
102,Mouse,20,1200.00
103,Keyboard,10,2500.00

backup_items.txt

Contains a backup copy of the inventory data.

These files are generated automatically by the program when required.

How to Compile

Make sure you have GCC installed.

Linux / macOS
gcc main.c -o baim


Run the program:

./baim

Windows
gcc main.c -o baim.exe


Run:

baim.exe

Learning Outcomes

Through this project, I practiced:

C programming fundamentals

Structure-based data management

Modular programming using functions

File input and output

Reading and writing text files

Input validation

Inventory and stock management

Basic billing logic

Data backup techniques

Problem-solving and debugging

Future Improvements

Possible future improvements include:

Support for item names containing spaces

Improved user interface

Customer information and invoice generation

Date and time for transactions

Sales history

Password-based authentication

Database integration

Graphical user interface

Author

Rehan Pujari

Bachelor's in Information Technology Student

Nepal

License

This project is created for educational and learning purposes.