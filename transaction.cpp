#include "transaction.h"

Transaction::Transaction()
{
	transaction_type_ = "";
	first_name_ = "";
	last_name_ = "";
	amount_ = 0;
	account_number_ = 0;
	transfer_account_ = 0;
	fund_number_ = 0;
	transfer_fund_ = 0;
	check_trans_ = true;
}

Transaction::~Transaction()
{
}

string Transaction::getTransactionType() const
{
	return transaction_type_;
}

string Transaction::getFirstName() const
{
	return first_name_;
}

string Transaction::getLastName() const
{
	return last_name_;
}

int Transaction::getMainAcctID() const
{
	return account_number_;
}

int Transaction::getSecondAcctID() const
{
	return transfer_account_;
}

int Transaction::getMainFundTypeID() const
{
	return fund_number_;
}

int Transaction::getSecondFundTypeID() const
{
	return transfer_fund_;
}

int Transaction::getAmount() const
{
	return amount_;
}

bool Transaction::getValidTrans() const
{
	return check_trans_;
}

void Transaction::setTransactionType(const string& tans_type)
{
	transaction_type_ = tans_type;
	return;
}

void Transaction::setFirstName(const string& f_name)
{
	first_name_ = f_name;
	return;
}

void Transaction::setLastName(const string& l_name)
{
	last_name_ = l_name;
	return;
}

void Transaction::setMainAcctID(const int& acct_number)
{
	account_number_ = acct_number;
	return;
}

void Transaction::setSecondAcctID(const int& acct_number)
{
	transfer_account_ = acct_number;
	return;
}

void Transaction::setMainFundTypeID(const int& fund_number)
{
	fund_number_ = fund_number;
	return;
}

void Transaction::setSecondFundTypeID(const int& fund_number)
{
	transfer_fund_ = fund_number;
	return;
}

void Transaction::setAmount(const int& amount)
{
	amount_ = amount;
	return;
}

void Transaction::setValidTrans(const bool& check)
{
	check_trans_ = check;
	return;
}

ostream& operator<<(ostream& outStream, const Transaction& rhs)
{
	if (rhs.getTransactionType() == "D" || rhs.getTransactionType() == "W")
	{
		outStream << rhs.getTransactionType() << " " << rhs.getMainAcctID() << " " << rhs.getMainFundTypeID() << " " << rhs.getAmount();
	}

	else if (rhs.getTransactionType() == "T")
	{
		outStream << "T " << rhs.getMainAcctID() << " " << rhs.getMainFundTypeID() << " "
			<< rhs.getSecondAcctID() << " " << rhs.getSecondFundTypeID() << " " << rhs.getAmount();
	}
	return outStream;

}

istream& operator>>(istream& inStream, Transaction& rhs)
{
	string newTranType;
	inStream >> newTranType;
	rhs.transaction_type_ = newTranType;
	int fromAcctID = 0;
	int toAcctID = 0;

	if (newTranType == "O")
	{
		inStream >> rhs.account_number_ >> rhs.last_name_ >> rhs.first_name_;
	}

	else if (newTranType == "D" || newTranType == "W")
	{
		inStream >> rhs.account_number_ >> rhs.fund_number_ >> rhs.amount_;
	}

	else if (newTranType == "T")
	{
		inStream >> rhs.account_number_ >> rhs.fund_number_ >> rhs.transfer_account_ >> rhs.transfer_fund_ >> rhs.amount_;
	}

	else if (newTranType == "A")
	{
		inStream >> rhs.account_number_;
	}

	else if (newTranType == "F")
	{
		inStream >> rhs.account_number_ >> rhs.fund_number_;
	}

	return inStream;
}