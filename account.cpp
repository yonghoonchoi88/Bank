#include "account.h"

Account::Account()
{
	firstName_ = "";
	lastName_ = "";
	id_ = 0;
}

Account::Account(string l_name, string f_name, int id)
{
	lastName_ = l_name;
	firstName_ = f_name;
	id_ = id;
	funds[0].setFundName("Money Market");
	funds[1].setFundName("Prime Money Market");
	funds[2].setFundName("Long-Term Bond");
	funds[3].setFundName("Short-Term Bond");
	funds[4].setFundName("500 Index Fund");
	funds[5].setFundName("Capital Value Fund");
	funds[6].setFundName("Growth Equity Fund");
	funds[7].setFundName("Growth Index Fund");
}

Account::~Account()
{
}

string Account::getFirstName() const
{
	return firstName_;
}

string Account::getLastName() const
{
	return lastName_;
}

int Account::getID() const
{
	return id_;
}

Fund* Account::getFund(const int& fund_number)
{
	return &funds[fund_number];
}

int Account::getFundBalance(int fund_number)
{
	return funds[fund_number].getBalance();
}

void Account::setFirstName(const string& f_name)
{
	firstName_ = f_name;
	return;
}

void Account::setLastName(const string& l_name)
{
	lastName_ = l_name;
	return;
}

void Account::setID(const int& id)
{
	id_ = id;
	return;
}

void Account::DisplayAllFund() const
{
	cout << this->getFirstName() << " " << this->getLastName() << " Account ID: " << this->getID() << endl;
	cout << "    Money Market: $" << funds[0].getBalance() << endl;
	cout << "    Prime Money Market: $" << funds[1].getBalance() << endl;
	cout << "    Long-Term Bond: $" << funds[2].getBalance() << endl;
	cout << "    Short-Term Bond: $" << funds[3].getBalance() << endl;
	cout << "    500 Index Fund: $" << funds[4].getBalance() << endl;
	cout << "    Capital Value Fund: $" << funds[5].getBalance() << endl;
	cout << "    Growth Equity Fund: $" << funds[6].getBalance() << endl;
	cout << "    Growth Index Fund: $" << funds[7].getBalance() << endl;
	cout << endl;
}

void Account::DisplayFund(const int& fund) const
{
	switch (fund)
	{
	case 0:
		cout << "Money Market: " << funds[0].getBalance() << endl;
		break;

	case 1:
		cout << "Prime Money Market: " << funds[1].getBalance() << endl;
		break;

	case 2:
		cout << "Long-Term Bond: " << funds[2].getBalance() << endl;
		break;

	case 3:
		cout << "Short-Term Bond: " << funds[3].getBalance() << endl;
		break;

	case 4:
		cout << "500 Index Fund: " << funds[4].getBalance() << endl;
		break;

	case 5:
		cout << "Capital Value Fund: " << funds[5].getBalance() << endl;
		break;

	case 6:
		cout << "Growth Equity Fund: " << funds[6].getBalance() << endl;
		break;

	case 7:
		cout << "Growth Index Fund: " << funds[7].getBalance() << endl;
		break;
	}
}

ostream& operator<<(ostream& outStream, const Account& rhs)
{
	outStream << rhs.id_ << ", " << rhs.firstName_ << ", " << rhs.lastName_ << endl;
	return outStream;
}

bool Account::operator==(const Account& rhs) const
{
	return ((this->id_) == (rhs.id_));
}

bool Account::operator!=(const Account& rhs) const
{
	return !(*this == rhs);
}

bool Account::operator>(const Account& rhs) const
{
	return ((this->id_) > (rhs.id_));
}

bool Account::operator<(const Account& rhs) const
{
	return ((this->id_) < (rhs.id_));
}
