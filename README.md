# Bank System (C++)

A console-based banking application developed in C++ as a beginner programming project. The application allows users to manage bank members and perform basic banking operations through a menu-driven interface.

## Features

- **Add Bank Members** – Register new members with a name, surname, bank account number, and initial balance.
- **Display All Members** – View all registered bank members and their account information.
- **Search Members** – Search for a bank member by name and surname.
- **Add Money** – Deposit money into an existing account using its bank account number.
- **Apply Taxes** – Deduct a specified amount from all registered accounts, after checking that every account has sufficient funds.
- **Input Validation** – Basic validation for menu choices and monetary values.

## Technologies and Concepts

- C++
- Standard Template Library (STL)
- `vector`
- `struct`
- Functions
- Loops and conditional statements
- Basic input validation

## Project Structure

```text
Bank-System-CPP/
│
├── banksystem.cpp
├── banksystem/
│   ├── banksystem.vcxproj
│   └── banksystem.vcxproj.filters
│
├── banksystem.slnx
├── README.md
└── .gitignore
```

## How to Run

### Requirements
- Windows
- Visual Studio with C++ development tools installed

### Steps

1. Clone or download this repository.
2. Open `banksystem.slnx` in Visual Studio.
3. Build the solution.
4. Run the application.

## Current Limitations

- Account information is stored in memory using a `vector`.
- Account information is not saved after the application closes.
- The application does not include user authentication.
- Input validation and account management can be improved.

## Future Improvements

- Save and load account information using files.
- Improve bank account number validation.
- Prevent duplicate account numbers.
- Improve input validation.
- Add more banking operations.

## Purpose

This project was created to practice fundamental C++ programming concepts, including data structures, functions, loops, and input validation.
