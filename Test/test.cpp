#include <iostream>
#include <cstdlib>

class BankAccount {
private:
  static unsigned long nextAccountNumber;
  unsigned long accountNumber;
  double balance;
public:
  unsigned long getAccountNumber() const {
    return accountNumber;
  }
  void deposit(double amount) {
    balance += amount;
  }
  double withdraw(double desiredAmount) {
    if (desiredAmount <= balance) {
      balance -= desiredAmount;
      return desiredAmount;
    }
    else {
      double actualAmount = balance;
      balance = 0;
      return actualAmount;
    }
  }
  double getBalance() const {
    return balance;
  }
  void initAccount() {
    accountNumber = nextAccountNumber;
    nextAccountNumber++;
    balance = 0;
  }
};

unsigned long BankAccount::nextAccountNumber = 0;


int main () {
  BankAccount b1;
  b1.initAccount();
  b1.deposit(1000);
  BankAccount b2;
  b2.initAccount();
  b2.deposit(500);
  b1.deposit(b2.withdraw(700));
  std::cout << "\n";
  std::cout << "Account 1:\n" << "- account number: " << b1.getAccountNumber() << "\n" << "- balance: " << b1.getBalance() << "\n\n";
  std::cout << "Account 2:\n" << "- account number: " << b2.getAccountNumber() << "\n" << "- balance: " << b2.getBalance() << "\n\n";
  return 1;
}
