// banksystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Accounts 
{
    string name;
    string surname;
    string bankNumber;
    double amount;
};
void ShowAllBankMembers(const vector<Accounts>& accounts)
{
    if (accounts.empty())
    {
        cout << "No Bank Members registered." << endl;
    }
    else
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            cout << accounts[i].name << " "
                << accounts[i].surname << " "
                << accounts[i].bankNumber << " "
                << accounts[i].amount <<" $"<< endl;
        }
    }
}
void AddMember(vector<Accounts>& accounts) 
{
    string name, surname, bankNumber;
    double amount;
    cout << "Name: ";
    cin >> name;

    cout << "Surname: ";
    cin >> surname;

    cout << "Bank Number: ";
    cin >> bankNumber;

    cout << "Money Amount: ";
    cin >> amount;

    while (cin.fail() || amount < 0)
    {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        cout << "Invalid amount!" << endl;
        cout << "Enter valid amount: ";
        cin >> amount;
    }
    Accounts account;

    account.name = name;
    account.surname = surname;
    account.bankNumber = bankNumber;
    account.amount = amount;
    bool exists = false;
    for (int i = 0;i < accounts.size();i++)
    {
        if (name == accounts[i].name && surname == accounts[i].surname)
        {
            exists = true;
            cout << "You have already added this Bank Member" << endl;
            return;
        }
    }
    if (exists == false)
    {
        accounts.push_back(account);
    }

    cout << "Bank Member added successfully!" << endl;
}
void SearchBankMember(const vector<Accounts>& accounts)
{
    if (accounts.empty())
    {
        cout << "No members registered." << endl;
        return;
    }
    bool found = false;
    string name, surname;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter surname: ";
    cin >> surname;
    for (int i = 0;i < accounts.size();i++)
    {
        if (name == accounts[i].name && surname == accounts[i].surname)
        {
            found = true;
            cout << accounts[i].name << " "
                << accounts[i].surname << endl;
            cout << "Bank Number: " << accounts[i].bankNumber << endl;
            cout << "Amount: " << accounts[i].amount << endl;
            break;
        }

    }
    if (found == true)
    {
        cout << "Bank Member found!" << endl;
    }
    else
    {
        cout << "Bank Member not found!" << endl;
    }
}

void AddMoney(vector<Accounts>& accounts)
{
    if (accounts.empty())
    {
        cout << "No bank members registered!" << endl;
        return;
    }

    string bankNumber;
    double money;
    int accountIndex = -1;

    cout << "Bank Number: ";
    cin >> bankNumber;

    // Find the bank account
    for (int i = 0; i < accounts.size(); i++)
    {
        if (bankNumber == accounts[i].bankNumber)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        cout << "Bank Account not found!" << endl;
        return;
    }

    // Enter the amount of money
    cout << "Enter the amount of money you want to add: ";
    cin >> money;

    while (cin.fail() || money <= 0)
    {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        cout << "Invalid amount! Enter a positive number: ";
        cin >> money;
    }

    accounts[accountIndex].amount += money;

    cout << "Money added successfully!" << endl;
}

void AddTax(vector<Accounts>& accounts)
{
    if (accounts.empty())
    {
        cout << "No bank members registered!" << endl;
        return;
    }

    int choice;
    double tax;

    do
    {
        cout << "1. All Bank Members" << endl;
        cout << "2. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 2)
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            cout << "Invalid option!" << endl;
            cout << "Choose 1 or 2: ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter tax amount: ";
            cin >> tax;

            while (cin.fail() || tax <= 0)
            {
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');

                cout << "Invalid tax amount!" << endl;
                cout << "Enter a positive amount: ";
                cin >> tax;
            }

            for (int i = 0; i < accounts.size(); i++)
            {
                if (accounts[i].amount < tax)
                {
                    cout << "Not enough money in all accounts!" << endl;
                    return;
                }
            }

            for (int i = 0; i < accounts.size(); i++)
            {
                accounts[i].amount -= tax;
            }

            cout << "Tax applied successfully!" << endl;
            break;

        case 2:
            cout << "Goodbye!" << endl;
            return;
        }

    } while (choice != 2);
}
int main()
{
    vector <Accounts> accounts;
    int choice;
    do
    {
        cout << "===== Bank SYSTEM =====" << endl;
        cout << "1. Add Bank Member" << endl;
        cout << "2. Show All Bank Members" << endl;
        cout << "3. Search Bank Member" << endl;
        cout << "4. Add Money To a Member" << endl;
        cout << "5. Add Tax" << endl;
        cout << "0. Exit" << endl;

        cout << "Choose an option: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 5)
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "Invalid option!" << endl;
            cout << "Choose an option again: ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
            AddMember(accounts);
            break;

        case 2:
            ShowAllBankMembers(accounts);
            break;

        case 3:
            SearchBankMember(accounts);
            break;

        case 4:
            AddMoney(accounts);
            break;

        case 5:
            AddTax(accounts);
            break;

        case 0:
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid option!" << endl;
            break;
        }

    } while (choice != 0);
}

