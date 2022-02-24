#include "jolly_banker.h"

JollyBanker::JollyBanker()
{
}

JollyBanker::~JollyBanker()
{
}

void JollyBanker::ReadTransaction(string file)
{
	ifstream inFile;
	inFile.open(file);

	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			Transaction trans;
			inFile >> trans;
			list_.push(trans);
		}
		inFile.close();
		return;
	}
}

void JollyBanker::ProcessQue()
{

	while (list_.size() != 0)
	{
		string trans = list_.front().getTransactionType();

		if (trans == "O")
		{
			OpenAccount(list_.front());
		}

		if (trans == "D")
		{
			Deposit(list_.front());
		}

		if (trans == "W")
		{
			Withdraw(list_.front());
		}

		if (trans == "T")
		{
			Transfer(list_.front());
		}

		if (trans == "A")
		{
			AccountHistory(list_.front());
		}

		if (trans == "F")
		{
			FundHistory(list_.front());
		}

		list_.pop();
	}
	return;
}

void JollyBanker::DisplayAllAccount() const
{
	cout << endl;
	cout << "FINAL BALANCES: " << endl;
	this->account_tree_.Display();
	return;
}

bool JollyBanker::OpenAccount(Transaction& trans)
{
	Account* acct = NULL;
	int account_number = trans.getMainAcctID();
	bool check_acct = account_tree_.Retrieve(account_number, acct);

	if (check_acct)
	{
		cerr << "ERROR: Account " << account_number << " is already opened. Transaction refused." << endl;
		return false;
	}

	if (account_number < 0)
	{
		cerr << "ERROR: Account " << account_number << " is a negative number. Transaction refused." << endl;
		return false;
	}

	else
	{
			Account new_acct(trans.getLastName(), trans.getFirstName(), trans.getMainAcctID());
			this->account_tree_.Insert(&new_acct);
			return true;
	}

}

bool JollyBanker::Deposit(Transaction& trans)
{
	Account* acct = NULL;
	int acct_number = trans.getMainAcctID();
	int fund_number = trans.getMainFundTypeID();
	bool acctAvailable = account_tree_.Retrieve(acct_number, acct);

	if (acctAvailable && trans.getAmount() >= 0 && trans.getMainFundTypeID() >= 0 && trans.getMainFundTypeID() < 8)
	{
		acct->getFund(trans.getMainFundTypeID())->Deposit(trans.getAmount());
		acct->getFund(trans.getMainFundTypeID())->AddHistory(trans);
		return true;
	}

	else
	{
		if (trans.getAmount() < 0)
		{
			trans.setValidTrans(false);
			acct->getFund(fund_number)->AddHistory(trans);
			cerr << "ERROR: $" << trans.getAmount() << " is not possible amount to make transaction. Deposit refused. " << endl;
			return false;
		}

		else if (trans.getMainFundTypeID() < 0 || trans.getMainFundTypeID() > 7)
		{
			cerr << "ERROR: Fund ID " << trans.getMainFundTypeID() << " have not been found. Deposit refused." << endl;
			return false;
		}

		else
		{
			cerr << "ERROR: Account ID " << acct_number << " was not found. Deposit refused. " << endl;
			return false;
		}
	}
}

bool JollyBanker::Withdraw(Transaction& trans)
{
	Account* acct = NULL;
	int acct_number = trans.getMainAcctID();
	int fund_number = trans.getMainFundTypeID();
	bool check = account_tree_.Retrieve(acct_number, acct);

	if (check && trans.getAmount() >= 0 && trans.getMainFundTypeID() >= 0 && trans.getMainFundTypeID() < 8)
	{
		if (acct->getFund(fund_number)->getBalance() < trans.getAmount())
		{
			if (fund_number == 0 || fund_number == 2)
			{
				int sumTwoBalance = acct->getFund(fund_number)->getBalance() + acct->getFund(fund_number + 1)->getBalance();
				int remainAmount = trans.getAmount() - acct->getFund(fund_number)->getBalance();

				if (sumTwoBalance < trans.getAmount())
				{
					trans.setValidTrans(false);
					acct->getFund(fund_number)->AddHistory(trans);
					cerr << "ERROR: Not enough fund to Withdraw " << trans.getAmount() << " from " << " " << acct->getFirstName() << " " << acct->getLastName() << " " 
						<< acct->getFund(fund_number)->getFundName() << "." << endl;
					return false;
				}

				else
				{
					acct->getFund(fund_number)->setBalance(0);
					acct->getFund(fund_number + 1)->Withdraw(remainAmount);
					trans.setAmount(trans.getAmount() - remainAmount);
					acct->getFund(fund_number)->AddHistory(trans);
					trans.setAmount(remainAmount);
					trans.setMainFundTypeID(trans.getMainFundTypeID() + 1);
					acct->getFund(fund_number + 1)->AddHistory(trans);
					return true;
				}
			}

			else if (fund_number == 1 || fund_number == 3)
			{
				int sumTwoBalance = acct->getFund(fund_number)->getBalance() + acct->getFund(fund_number - 1)->getBalance();
				int remainAmount = trans.getAmount() - acct->getFund(fund_number)->getBalance();
				if (sumTwoBalance < trans.getAmount())
				{
					trans.setValidTrans(false);
					acct->getFund(fund_number)->AddHistory(trans);
					cerr << "ERROR: Not enough fund to Withdraw " << trans.getAmount() << " from " << " " << acct->getFirstName() << " " << acct->getLastName() << " "
						<< acct->getFund(fund_number)->getFundName() << "." << endl;
					return false;
				}

				else
				{
					acct->getFund(fund_number)->setBalance(0);
					acct->getFund(fund_number - 1)->Withdraw(remainAmount);
					trans.setAmount(trans.getAmount() - remainAmount);
					acct->getFund(fund_number)->AddHistory(trans);
					trans.setAmount(remainAmount);
					trans.setMainFundTypeID(trans.getMainFundTypeID() - 1);
					acct->getFund(fund_number - 1)->AddHistory(trans);
					return true;
				}
			}

			else
			{
				trans.setValidTrans(false);
				acct->getFund(fund_number)->AddHistory(trans);
				cerr << "ERROR: Not enough fund to Withdraw " << trans.getAmount() << " from " << " " << acct->getFirstName() << " " << acct->getLastName() << " "
					<< acct->getFund(fund_number)->getFundName() << "." << endl;
				return false;
			}
		}

		else
		{
			acct->getFund(fund_number)->Withdraw(trans.getAmount());
			acct->getFund(fund_number)->AddHistory(trans);
			return true;
		}
	}

	else
	{
		if (trans.getAmount() < 0)
		{
			trans.setValidTrans(false);
			acct->getFund(fund_number)->AddHistory(trans);
			cerr << "ERROR: $" << trans.getAmount() << " is not possible amount to make transaction. Withdraw refused. " << endl;
			return false;
		}

		else if (trans.getMainFundTypeID() < 0 || trans.getMainFundTypeID() > 7)
		{
			cerr << "ERROR: Fund ID " << trans.getMainFundTypeID() << " have not been found. Withdraw refused." << endl;
			return false;
		}

		else
		{
			cerr << "ERROR: Account ID " << acct_number << " was not found. Withdraw refused. " << endl;
			return false;
		}
	}
}

bool JollyBanker::Transfer(Transaction& trans)
{

	Account* acct = NULL;
	int acct_number = trans.getMainAcctID();
	int fund_number = trans.getMainFundTypeID();
	bool check = account_tree_.Retrieve(acct_number, acct);
	
	Account* transfer_acct = NULL;
	int trans_acct = trans.getSecondAcctID();
	int trans_fund = trans.getSecondFundTypeID();
	bool check2 = account_tree_.Retrieve(trans_acct, transfer_acct);

		if (!check)
		{
			cerr << "ERROR: Account " << acct_number << " was not found. Transfer refused. " << endl;
			return false;
		}

		if (trans.getMainFundTypeID() < 0 || trans.getMainFundTypeID() > 7)
		{
			cerr << "ERROR: Fund ID " << trans.getMainFundTypeID() << " have not been found in accout " << acct_number  << ". Transfer refused." << endl;
			return false;
		}

		if (!check2)
		{
			trans.setValidTrans(false);
			acct->getFund(fund_number)->AddHistory(trans);
			cerr << "ERROR: Account " << trans_acct << " was not found to transfer. Transfer refused. " << endl;
			return false;
		}

		if (trans.getSecondFundTypeID() < 0 || trans.getSecondFundTypeID() > 7)
		{
			trans.setValidTrans(false);
			acct->getFund(fund_number)->AddHistory(trans);
			cerr << "ERROR: Fund ID " << trans.getSecondFundTypeID() << " have not been found in accout " << trans_acct << ". Transfer refused." << endl;
			return false;
		}

		if (trans.getAmount() < 0)
		{
			trans.setValidTrans(false);
			acct->getFund(fund_number)->AddHistory(trans);
			cerr << "ERROR: $" << trans.getAmount() << " is not possible amount to make transaction. Transfer refused. " << endl;
			return false;
		}

		if (acct->getFund(fund_number)->getBalance() < trans.getAmount())
		{
			int remain = trans.getAmount() - acct->getFund(fund_number)->getBalance();

			if (fund_number == 0 || fund_number == 2)
			{
				if (remain <= (acct->getFund(fund_number + 1)->getBalance()))
				{
					acct->getFund(fund_number)->Withdraw(trans.getAmount() - remain);
					acct->getFund(fund_number + 1)->Withdraw(remain);
					transfer_acct->getFund(trans_fund)->Deposit(trans.getAmount());
					trans.setAmount(trans.getAmount() - remain);
					acct->getFund(fund_number)->AddHistory(trans);
					transfer_acct->getFund(trans_fund)->AddHistory(trans);
					trans.setAmount(remain);
					trans.setMainFundTypeID(trans.getMainFundTypeID() + 1);
					acct->getFund(fund_number + 1)->AddHistory(trans);
					transfer_acct->getFund(trans_fund)->AddHistory(trans);
					return true;
				}
			}

			else if (fund_number == 1 || fund_number == 3)
			{
				if ((remain <= (acct->getFund(fund_number - 1)->getBalance())))
				{
					acct->getFund(fund_number)->Withdraw(trans.getAmount() - remain);
					acct->getFund(fund_number - 1)->Withdraw(remain);
					transfer_acct->getFund(trans_fund)->Deposit(trans.getAmount());
					trans.setAmount(trans.getAmount() - remain);
					acct->getFund(fund_number)->AddHistory(trans);
					transfer_acct->getFund(trans_fund)->AddHistory(trans);
					trans.setAmount(remain);
					trans.setMainFundTypeID(trans.getMainFundTypeID() - 1);
					acct->getFund(fund_number - 1)->AddHistory(trans);
					transfer_acct->getFund(trans_fund)->AddHistory(trans);
					return true;
				}
			}

			trans.setValidTrans(false);
			acct->getFund(fund_number)->AddHistory(trans);

			if (acct_number != trans_acct)
			{
				transfer_acct->getFund(trans_fund)->AddHistory(trans);
			}

			cerr << "ERROR: Not enough funds to transfer " << acct->getFirstName() << " " << acct->getLastName() << " " << acct->getFund(fund_number)->getFundName()
				<< " to Account ID " << trans_acct << " " << acct->getFund(trans_fund)->getFundName() << ". Transfer refused." << endl;
			return false;
		}

		else
		{
			Account* acct = NULL;
			Account* trans_acct = NULL;
			int acct_number = trans.getMainAcctID();
			int fund_number = trans.getMainFundTypeID();
			int trans_number = trans.getSecondAcctID();
			int trans_fund = trans.getSecondFundTypeID();
			bool check = account_tree_.Retrieve(acct_number, acct);
			bool check2 = account_tree_.Retrieve(trans_number, trans_acct);
			int remain = trans.getAmount() - acct->getFund(fund_number)->getBalance();
			acct->getFund(fund_number)->Withdraw(trans.getAmount());
			trans_acct->getFund(trans_fund)->Deposit(trans.getAmount());
			acct->getFund(fund_number)->AddHistory(trans);

			if (acct_number != trans_number)
			{
				trans_acct->getFund(trans_fund)->AddHistory(trans);
			}

			else if (fund_number != trans_fund)
			{
				acct->getFund(trans_fund)->AddHistory(trans);
			}
			return true;
		}
}

bool JollyBanker::AccountHistory(Transaction& trans)
{
	Account* acct = NULL;
	int acct_number = trans.getMainAcctID();
	int fund_number = trans.getMainFundTypeID();
	bool check = account_tree_.Retrieve(acct_number, acct);

	if (check)
	{
		cout << "Transaction History for " << acct->getFirstName() << " " << acct->getLastName() << " by fund." << endl;
	
		for (int i = 0; i < 8; i++)
		{
		
			if (acct->getFund(i)->getHistorySize() > 0)
			{
				cout  << acct->getFund(i)->getFundName() << ": $" << acct->getFundBalance(i) << endl;
				acct->getFund(i)->DisplayHistory();
			}
		}
			cout << endl;
			return true;
	}

	else
	{
		cerr << "ERROR: Account " << acct_number << " was not found. Process history refused. " << endl;
		return false;
	}
}


bool JollyBanker::FundHistory(Transaction& trans)
{
	Account* acct = NULL;
	int acct_number = trans.getMainAcctID();
	int fund_number = trans.getMainFundTypeID();
	bool check = account_tree_.Retrieve(acct_number, acct);

	if (check)
	{
			cout << "Transaction History for " << acct->getFirstName() << " " << acct->getLastName()
				<< " " << acct->getFund(fund_number)->getFundName() << ": $" << acct->getFundBalance(fund_number) << endl;
			acct->getFund(fund_number)->DisplayHistory();
			cout << endl;
			return true;
	}

	else
	{
		cerr << "ERROR: Account " << acct_number << " was not found. Process history refused. " << endl;
		return false;
	}
}
