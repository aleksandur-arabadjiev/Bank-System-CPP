// banksystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
using namespace std;

struct Accounts 
{
    string name;
    string surname;
    string bankNumber;
    double amount;
};
void SaveAccounts(const vector<Accounts>& accounts)
{
    ofstream file("accounts.txt");

    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < accounts.size(); i++)
    {
        file << accounts[i].name << " "
            << accounts[i].surname << " "
            << accounts[i].bankNumber << " "
            << accounts[i].amount << endl;
    }

    file.close();

    cout << "Accounts saved successfully!" << endl;
}
void LoadAccounts(vector<Accounts>& accounts)
{
    accounts.clear();
    ifstream file("accounts.txt");

    if (!file.is_open())
    {
        cout << "No saved accounts found." << endl;
        return;
    }

    Accounts account;

    while (file >> account.name
        >> account.surname
        >> account.bankNumber
        >> account.amount)
    {
        accounts.push_back(account);
    }

    file.close();

    cout << "Accounts loaded successfully!" << endl;
}
struct Transaction
{
    string type;
    string senderBankNumber;
    string receiverBankNumber;
    double amount;
};
void SaveTransactions(const vector<Transaction>& transactions);
void AddTransaction(
    vector<Transaction>& transactions,
    string type,
    string senderBankNumber,
    string receiverBankNumber,
    double amount
);
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
        SaveAccounts(accounts);
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
void AddMoney(vector<Accounts>& accounts, vector<Transaction>& transactions)
{
    if (accounts.empty())
    {
        cout << "No bank members registered!" << endl;
        return;
    }
    bool found = false;
    string bankNumber;
    double money;
    cout << "Bank Number: ";
    cin >> bankNumber;
    cout << "Enter the amount of money u want to add: ";
    cin >> money;
    while (cin.fail()||money<=0)
    {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        cout << "Invalid amount! Enter a positive number: ";
        cin >> money;
    }
    for (int i = 0;i < accounts.size();i++)
    {
        if (bankNumber == accounts[i].bankNumber)
        {
            accounts[i].amount += money;
            SaveAccounts(accounts);
            AddTransaction(transactions, "Deposit", "-", bankNumber, money);
            SaveTransactions(transactions);
            found = true;
            cout << "Amount added successfully!" << endl;
            break;
        }

    }
    if (!found)
    {
        cout << "Bank Account not found!" << endl;
    }

}
void WithdrawMoney(vector<Accounts>& accounts,vector<Transaction>& transactions)
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
        cout << "Account was not found"<<endl;
        return;
    }

    cout << "How much money do you want to withdraw?";
    cin >> money;
    while (cin.fail() || money <= 0)
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            cout << "Invalid amount! Enter a positive number: ";
            cin >> money;
        }
    if (accounts[accountIndex].amount < money)
    {
        cout << "You cannot withdraw this amount of money!";
    }
    else
    {
        cout << "Money withdrawn successfully!" << endl;
        accounts[accountIndex].amount -= money;
        AddTransaction(transactions,"Withdrawal", bankNumber,"-", money);
        SaveTransactions(transactions);
        SaveAccounts(accounts);
    }


}
void TransferMoney(vector<Accounts>& accounts,vector<Transaction>& transactions)
{
    if (accounts.size() < 2)
    {
        cout << "You need at least two accounts!" << endl;
        return;
    }

    string senderBankNumber, receiverBankNumber;
    double money;

    int senderIndex = -1;
    int receiverIndex = -1;

    cout << "Enter sender bank number: ";
    cin >> senderBankNumber;

    for (int i = 0; i < accounts.size(); i++)
    {
        if (senderBankNumber == accounts[i].bankNumber)
        {
            senderIndex = i;
            break;
        }
    }
    if (senderIndex == -1)
    {
        cout << "Account was not found" << endl;
        return;
    }
    cout << "Enter receiver bank number: ";
    cin >> receiverBankNumber;

    for (int i = 0; i < accounts.size(); i++)
    {
        if (receiverBankNumber == accounts[i].bankNumber)
        {
            receiverIndex = i;
            break;
        }
    }
    if (receiverIndex == -1)
    {
        cout << "Receiver account was not found!" << endl;
        return;
    }
    if (senderIndex == receiverIndex)
    {
        cout << "You cannot transfer money to the same account!" << endl;
        return;
    }
    else 
    {
        cout << "How much money do you want to transfer? ";
        cin >> money;
        while (cin.fail() || money <= 0)
        {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            cout << "Invalid amount! Enter a positive number: ";
            cin >> money;
        }
        if (accounts[senderIndex].amount < money)
        {
            cout << "Not enough money!" << endl;
            return;
        }
        accounts[senderIndex].amount -= money;
        accounts[receiverIndex].amount += money;
        cout << "Money transferred successfully!" << endl;
        AddTransaction(transactions,"Transfer", senderBankNumber, receiverBankNumber, money);
        SaveTransactions(transactions);
        SaveAccounts(accounts);
    }
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
            SaveAccounts(accounts);
            cout << "Tax applied successfully!" << endl;
            break;

        case 2:
            cout << "Goodbye!" << endl;
            return;
        }

    } while (choice != 2);
}
void AddTransaction(
    vector<Transaction>& transactions,
    string type,
    string senderBankNumber,
    string receiverBankNumber,
    double amount)
{
    Transaction transaction;

    transaction.type = type;
    transaction.senderBankNumber = senderBankNumber;
    transaction.receiverBankNumber = receiverBankNumber;
    transaction.amount = amount;

    transactions.push_back(transaction);
}

void ShowTransactionHistory(const vector<Transaction>& transactions)
{
    if (transactions.empty())
    {
        cout << "No transactions found!" << endl;
        return;
    }

    for (int i = 0; i < transactions.size(); i++)
    {
        cout << "\nTransaction #" << i + 1 << endl;
        cout << "Type: " << transactions[i].type << endl;

        if (transactions[i].type == "Deposit")
        {
            cout << "Receiver: "
                << transactions[i].receiverBankNumber << endl;
        }
        else if (transactions[i].type == "Withdrawal")
        {
            cout << "Sender: "
                << transactions[i].senderBankNumber << endl;
        }
        else if (transactions[i].type == "Transfer")
        {
            cout << "Sender: "
                << transactions[i].senderBankNumber << endl;

            cout << "Receiver: "
                << transactions[i].receiverBankNumber << endl;\
        }

        cout << "Amount: " << transactions[i].amount << endl;
        cout << "------------------------" << endl;
    }
}

void SaveTransactions(const vector<Transaction>& transactions)
{
    ofstream file("transactions.txt");

    if (!file.is_open())
    {
        cout << "Error opening transactions file!" << endl;
        return;
    }

    for (int i = 0; i < transactions.size(); i++)
    {
        file << transactions[i].type << " "
            << transactions[i].senderBankNumber << " "
            << transactions[i].receiverBankNumber << " "
            << transactions[i].amount << endl;
    }

    file.close();

    cout << "Transactions saved successfully!" << endl;
}
void LoadTransactions(vector<Transaction>& transactions)
{
    transactions.clear();
    ifstream file("transactions.txt");

    if (!file.is_open())
    {
        cout << "No saved transactions found." << endl;
        return;
    }

    Transaction transaction;

    while (file >> transaction.type
        >> transaction.senderBankNumber
        >> transaction.receiverBankNumber
        >> transaction.amount)
    {
        transactions.push_back(transaction);
    }

    file.close();

    cout << "Transactions loaded successfully!" << endl;
}
int main()
{
    vector <Accounts> accounts;
    vector<Transaction> transactions;
    LoadAccounts(accounts);
    LoadTransactions(transactions);
    int choice;
    do
    {
        cout << "===== Bank SYSTEM =====" << endl;
        cout << "1. Add Bank Member" << endl;
        cout << "2. Show All Bank Members" << endl;
        cout << "3. Search Bank Member" << endl;
        cout << "4. Add Money To a Member" << endl;
        cout << "5. Add Tax" << endl;
        cout << "6. Withdraw Money" << endl;
        cout << "7. Transfer Money" << endl;
        cout << "8. Show Transaction History" << endl;
        cout << "0. Exit" << endl;

        cout << "Choose an option: ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 8)
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
            AddMoney(accounts, transactions);
            break;

        case 5:
            AddTax(accounts);
            break;
        case 6:
            WithdrawMoney(accounts, transactions);
            break;
        case 7:
            TransferMoney(accounts, transactions);
            break;
        case 8:
            ShowTransactionHistory(transactions);
            break;
        case 0:
            cout << "Goodbye!" << endl;
            SaveAccounts(accounts);
            SaveTransactions(transactions);
            break;

        default:
            cout << "Invalid option!" << endl;
            break;
        }

    } while (choice != 0);
}

