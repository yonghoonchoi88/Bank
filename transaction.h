#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Transaction
{

	friend ostream& operator<<(ostream& outStream, const Transaction& rhs);
	friend istream& operator>>(istream& inStream, Transaction& rhs);

public:

	Transaction();
	~Transaction();

	string getTransactionType() const;
	string getFirstName() const;
	string getLastName() const;

	int getMainAcctID() const;
	int getSecondAcctID() const;
	int getMainFundTypeID() const;
	int getSecondFundTypeID() const;
	int getAmount() const;
	bool getValidTrans() const;

	void setTransactionType(const string& tans_type);
	void setFirstName(const string& f_name);
	void setLastName(const string& l_name);
	void setMainAcctID(const int& acct_number);
	void setSecondAcctID(const int& acct_number);
	void setMainFundTypeID(const int& fund_number);
	void setSecondFundTypeID(const int& fund_number);
	void setAmount(const int& amount);
	void setValidTrans(const bool& check);

private:

	string transaction_type_;
	string first_name_;
	string last_name_;

	int account_number_;
	int transfer_account_;
	int fund_number_;
	int transfer_fund_;
	int amount_;

	bool check_trans_;

};

#endif
