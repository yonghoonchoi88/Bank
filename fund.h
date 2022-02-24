#ifndef FUND_H_
#define FUND_H_

#include "transaction.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Fund
{

	friend ostream& operator<<(ostream& outStream, const Fund& rhs);

public:

	Fund();
	Fund(string incFundName, int balance);
	~Fund();

	string getFundName() const;

	int getBalance() const;
	int getHistorySize() const;

	bool isHistoryEmpty() const;

	void setFundName(const string& fund_name);
	void setBalance(const int& balance);

	void Deposit(const int& amount);
	void Withdraw(const int& amount);
	void AddHistory(const Transaction& history);
	void DisplayHistory() const;

private:

	string fundName_;
	int balance_;
	vector<Transaction> history_;

};

#endif