
# Bank System (C++)

A console-based banking application developed in C++ to practice object-oriented programming fundamentals, data structures, file handling, and basic banking operations.

## Features

- **Add Bank Members** – Create new bank accounts with a name, surname, unique bank account number, and initial balance.
- **Display All Members** – View all registered bank accounts.
- **Search Members** – Find an account using the member's name and surname.
- **Deposit Money** – Add money to an existing bank account.
- **Apply Taxes** – Deduct a specified amount from all accounts after checking that every account has sufficient funds.
- **Withdraw Money** – Withdraw money from an account if sufficient funds are available.
- **Transfer Money** – Transfer money between two different accounts.
- **Transaction History** – View recorded deposits, withdrawals, and transfers.
- **File Handling** – Save and load account information and transaction history using text files.
- **Input Validation** – Validate user input and prevent invalid banking operations.

## Technologies & Concepts

- C++
- Standard Template Library (STL)
- `vector`
- `struct`
- Functions
- File handling (`ifstream`, `ofstream`)
- Loops and conditional statements
- Input validation

## Data Storage

The application uses two text files:

- `accounts.txt` – Stores account information.
- `transactions.txt` – Stores transaction history.

Account information and transaction history are loaded when the application starts and saved when changes are made.

## How to Run

### Requirements
- Windows
- Visual Studio with C++ development tools

### Steps
1. Clone or download this repository.
2. Open `banksystem.slnx` in Visual Studio.
3. Build the solution.
4. Run the application.

## Current Limitations

- The application does not include user authentication.
- Data is stored in local text files rather than a database.
- Input validation and account management can be further improved.

## Future Improvements

- Implement a database for persistent storage.
- Add user authentication and account security.
- Improve account number validation.
- Add more banking operations.
- Improve error handling and user experience.

## Purpose

This project was created as a practical way to improve my C++ programming skills through building a simple banking application and working with data structures, functions, file handling, and basic transaction management.
