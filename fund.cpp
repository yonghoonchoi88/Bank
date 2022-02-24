#include "fund.h"

Fund::Fund()
{
	fundName_ = "";
	balance_ = 0;
}

Fund::Fund(string fund_name, int balance)
{
	fundName_ = fund_name;
	balance_ = balance;
}

Fund::~Fund()
{
}

string Fund::getFundName() const
{
	return fundName_;
}

int Fund::getBalance() const
{
	return balance_;
}

int Fund::getHistorySize() const
{
	return history_.size();
}

void Fund::setFundName(const string& fund_name)
{
	fundName_ = fund_name;
	return;
}

void Fund::setBalance(const int& balance)
{
	balance_ = balance;
	return;
}

void Fund::Deposit(const int& amount)
{
	balance_ += amount;
	return;
}

void Fund::Withdraw(const int& amount)
{
	balance_ -= amount;
	return;
}

void Fund::AddHistory(const Transaction& trans)
{
	history_.push_back(trans);
	return;
}

void Fund::DisplayHistory() const
{
		for (int i = 0; i < history_.size(); i++)
		{
			cout << " " << history_[i];

			if (history_[i].getValidTrans() == false)
			{
				cout << " (Failed)";
			}

			cout << endl;
		}
	return;
}

bool Fund::isHistoryEmpty() const
{
	return !(history_.size() > 0);
}

ostream& operator<<(ostream& outStream, const Fund& rhs)
{
	outStream << rhs.getFundName() << ": $" << rhs.getBalance();
	return outStream;
}