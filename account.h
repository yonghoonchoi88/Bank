#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "fund.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int Kfund = 8;

class Account
{
	friend ostream& operator<<(ostream& outStream, const Account& rhs);

public:

	Account();
	Account(string l_name, string f_name, int id);
	~Account();

	string getFirstName() const;
	string getLastName() const;

	int getID() const;
	int getFundBalance(int fund_num);

	Fund* getFund(const int& fund_num);

	void setFirstName(const string& f_name);
	void setLastName(const string& l_name);
	void setID(const int& id);

	void DisplayAllFund() const;
	void DisplayFund(const int& fund) const;

	bool operator==(const Account& rhs) const;
	bool operator!=(const Account& rhs) const;
	bool operator>(const Account& rhs) const;
	bool operator<(const Account& rhs) const;

private:

	string firstName_;
	string lastName_;
	int id_;
	Fund funds[Kfund];

};

#endif