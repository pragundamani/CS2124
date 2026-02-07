/*
Pragun Damani pd2752
  rec03.cpp
  spring 2026
*/

// Provided
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
    string holderName;
    int accNum = 0;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
class ClassyAccounts{
    friend ostream& operator<<(ostream& os, const ClassyAccounts& classyaccount);
    string holderName;
    int accNum = 0;
public:

    ClassyAccounts(const string& name, int num):holderName(name),accNum(num){ }
    const string& getName()const{return holderName;}
    int getAccNum()const{return accNum;}
};

ostream& operator<<(ostream& os, const ClassyAccounts& classyaccount);

// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".

class Transaction {
    friend ostream& operator<<(ostream& os, const Transaction& transaction);
public:
    string transType;
    int amount = 0;
    Transaction(const string& transType, int amount):transType(transType),amount(amount){ }
};

class ClassyTransactAccount{
    friend ostream& operator<<(ostream& os, const ClassyTransactAccount& output);
    string holderName;
    int accNum = 0;
    int balance = 0;
    vector<Transaction> transHist;

    public:
    ClassyTransactAccount(const string& name, int num):holderName(name),accNum(num){ }
    const string& getName()const{return holderName;}
    int getAccNum()const{return accNum;}

    void deposit(int amount){
        balance += amount;
        Transaction addToHist("deposit",amount);
        transHist.push_back(addToHist);
    }

    void withdrawal(int amount){
        if(balance<amount){
            cout << "transaction cannot go through";
        }
        else{
            balance -= amount;
            Transaction addToHist("withdrawal",amount);
            transHist.push_back(addToHist);
        }
    }
};

ostream& operator<<(ostream& os, const Transaction& transaction);

// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class NestedClassyTransactAccount{
public:
    class NestedTransaction {
                friend ostream& operator<<(ostream& os, const NestedClassyTransactAccount::NestedTransaction& transaction);
        public:
            string transType;
            int amount = 0;
            NestedTransaction(const string& transType, int amount):transType(transType),amount(amount){ }
        };
private:
friend ostream& operator<<(ostream& os, const NestedClassyTransactAccount& outputAccount);
    string holderName;
    int accNum = 0;
    int balance = 0;
    vector<NestedTransaction> transHist;

public:
    // vector<NestedTransaction> transHist;
    NestedClassyTransactAccount(const string& name, int num):holderName(name),accNum(num){ }
    const string& getName()const{return holderName;}
    int getAccNum()const{return accNum;}

    void deposit(int amount){
        balance += amount;
        NestedTransaction addToHist("deposit",amount);
        transHist.push_back(addToHist);
    }

    void withdrawal(int amount){
        if(balance<amount){
            cout << "transaction cannot go through";
        }
        else{
            balance -= amount;
            NestedTransaction addToHist("withdrawal",amount);
            transHist.push_back(addToHist);
        }

};

// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.


int main()
{
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";

    vector<Account> accountsVect;
    ifstream externalAccounts("accounts.txt");
    string tempAccountName;
    int tempAccountNumber;
    Account tempAccount;
    if (!externalAccounts){
        cerr << "accounts not found";
        exit(1);
    }

    while(externalAccounts>>tempAccountName>>tempAccountNumber){
        tempAccount.holderName = tempAccountName;
        tempAccount.accNum = tempAccountNumber;
        accountsVect.push_back(tempAccount);
        // cout << "adding account for " << tempAccountName
        //      << " with number "<< tempAccountNumber << endl;
    }
    for(const Account& outputAccount : accountsVect){
        cout << "added account for " << outputAccount.holderName
             << " with number "<< outputAccount.accNum << endl;
    }
    cout << "number of accounts: " << accountsVect.size() << endl;
    externalAccounts.close();

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";

    accountsVect.clear();
    externalAccounts.open("accounts.txt");

    if (!externalAccounts){
            cerr << "accounts not found";
            exit(1);
        }

    while(externalAccounts>>tempAccountName>>tempAccountNumber){
        Account tempInitAccount {tempAccountName,tempAccountNumber};
        accountsVect.push_back(tempInitAccount);
    }
    for(const Account& outputAccount : accountsVect){
        cout << "added account for " << outputAccount.holderName
             << " with number "<< outputAccount.accNum << endl;
    }
    cout << "number of accounts: " << accountsVect.size() << endl;
    externalAccounts.close();



    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
    vector<ClassyAccounts> classyAccountsVect;
    externalAccounts.open("accounts.txt");

    if (!externalAccounts){
                cerr << "accounts not found";
                exit(1);
            }

    // while(externalAccounts>>tempAccountName>>tempAccountNumber){
    //     classyAccountsVect.emplace_back(tempAccountName,tempAccountNumber);
    // }
    while(externalAccounts>>tempAccountName>>tempAccountNumber){
        ClassyAccounts tempInitAccount {tempAccountName,tempAccountNumber};
        classyAccountsVect.push_back(tempInitAccount);
    }

    for(const ClassyAccounts& outputClassyAccount : classyAccountsVect){
        cout << "added account for " << outputClassyAccount.getName()
             << " with number "<< outputClassyAccount.getAccNum() << endl;

    }
    cout << "number of accounts: " << accountsVect.size() << endl;
    externalAccounts.close();


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

   for(const ClassyAccounts& outputclassy : classyAccountsVect){
       cout << outputclassy;
   }

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
    for(const ClassyAccounts& outputclassy : classyAccountsVect){
        cout << outputclassy;
    }

    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
    classyAccountsVect.clear();

    externalAccounts.open("accounts.txt");

        if (!externalAccounts){
                    cerr << "accounts not found";
                    exit(1);
                }


        while(externalAccounts>>tempAccountName>>tempAccountNumber){
            classyAccountsVect.push_back(ClassyAccounts(tempAccountName,tempAccountNumber));
        }
        for(const ClassyAccounts& outputClassyAccount : classyAccountsVect){
            cout << "added account for " << outputClassyAccount.getName()
                 << " with number "<< outputClassyAccount.getAccNum() << endl;

        }
        cout << "number of accounts: " << accountsVect.size() << endl;
        externalAccounts.close();


    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
         classyAccountsVect.clear();

         externalAccounts.open("accounts.txt");

            if (!externalAccounts){
                         cerr << "accounts not found";
                         exit(1);
            }

            while(externalAccounts>>tempAccountName>>tempAccountNumber){
                    classyAccountsVect.emplace_back(tempAccountName,tempAccountNumber);
            }

             for(const ClassyAccounts& outputClassyAccount : classyAccountsVect){
                 cout << "added account for " << outputClassyAccount.getName()
                      << " with number "<< outputClassyAccount.getAccNum() << endl;

             }
             cout << "number of accounts: " << accountsVect.size() << endl;
             externalAccounts.close();

    cout << "==============\n"
        << "\nTask 3:\nAccounts and Transaction:\n";

    ifstream transactions("transactions.txt");
    vector<ClassyTransactAccount> classyTranactsVect;
    string token,name;
    int accNum = 0, amount = 0;

    if (!transactions){
        cerr<<"file not found";
         exit(1);
    }
    while(transactions>>token){
        if (token == "Account"){
           transactions >> name >> accNum;
           ClassyTransactAccount pushToVect(name,accNum);
           classyTranactsVect.push_back(pushToVect);
           cout << "added account " << name << " account number " << accNum << endl;
        }
        else if(token == "Deposit"){
            transactions >> accNum >> amount;
            for(ClassyTransactAccount& ind_acc: classyTranactsVect){
                if (accNum == ind_acc.getAccNum()){
                    ind_acc.deposit(amount);
                    cout << "deposit " << amount << " in account " << ind_acc.getAccNum() << " of " << ind_acc.getName() << endl;
                }
            }
        }
        else if (token == "Withdraw"){
            transactions >> accNum >> amount;
            for(ClassyTransactAccount& ind_acc: classyTranactsVect){
                if (accNum == ind_acc.getAccNum()){
                    ind_acc.withdrawal(amount);
                    cout << "withdrawal " << amount << " in account " << ind_acc.getAccNum() << " of " << ind_acc.getName() << endl;
                }
            }
        }

    }
    transactions.close();



    cout << "==============\n" << "\nTask 4:\nTransaction nested in public section of Account:\n";
    transactions.open("transactions.txt");
    vector<NestedClassyTransactAccount> nestedclassyTranactsVect;

    if (!transactions){
        cerr<<"file not found";
         exit(1);
    }
    while(transactions>>token){
        if (token == "Account"){
           transactions >> name >> accNum;
           NestedClassyTransactAccount pushToVect(name,accNum);
           nestedclassyTranactsVect.push_back(pushToVect);
           cout << "added account " << name << " account number " << accNum << endl;
        }
        else if(token == "Deposit"){
            transactions >> accNum >> amount;
            for(NestedClassyTransactAccount& ind_acc: nestedclassyTranactsVect){
                if (accNum == ind_acc.getAccNum()){
                    ind_acc.deposit(amount);
                    cout << "deposit " << amount << " in account " << ind_acc.getAccNum() << " of " << ind_acc.getName() << endl;
                }
            }
        }
        else if (token == "Withdraw"){
            transactions >> accNum >> amount;
            for(NestedClassyTransactAccount& ind_acc: nestedclassyTranactsVect){
                if (accNum == ind_acc.getAccNum()){
                    ind_acc.withdrawal(amount);
                    cout << "withdrawal " << amount << " in account " << ind_acc.getAccNum() << " of " << ind_acc.getName() << endl;
                }
            }
        }

    }
    transactions.close();

    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";


} // main

ostream& operator<<(ostream& os, const ClassyAccounts& classyaccount){
    os << "Holder: " << classyaccount.getName() /*classyaccount.holderName*/ << endl
       << "Number: " << classyaccount.getAccNum() /*classyaccount.accNum*/ << endl;
    return os;
}

ostream& operator<<(ostream& os, const ClassyTransactAccount& output){
    os << "Holder: " << /*classyaccount.getName()*/ output.holderName << endl
       << "Number: " << /*classyaccount.getAccNum()*/ output.accNum << endl;
    return os;
}

ostream& operator<<(ostream& os, const Transaction& transaction){
    os << "type: " << transaction.transType
       << "amnt: " << transaction.amount;

    return os;
}

ostream& operator<<(ostream& os, const NestedClassyTransactAccount& output){
    os << "Holder: " << /*classyaccount.getName()*/ output.holderName << endl
       << "Number: " << /*classyaccount.getAccNum()*/ output.accNum << endl;
    return os;
}

ostream& operator<<(ostream& os, const NestedClassyTransactAccount::NestedTransaction& transaction){
    os << "type: " << transaction.transType
       << "amnt: " << transaction.amount;

    return os;
}
