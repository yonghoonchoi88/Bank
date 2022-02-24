#ifndef JOLLY_BANKER_H_
#define JOLLY_BANKER_H_

#include "bs_tree.h"
#include "account.h"
#include "transaction.h"
#include "fund.h"
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;
class JollyBanker

{

public:
	JollyBanker();
	~JollyBanker();

	void ReadTransaction(string filename);
	void ProcessQue();
	void DisplayAllAccount() const;

private:
	queue<Transaction> list_;
	BSTree account_tree_;

	bool OpenAccount(Transaction& trans);
	bool Deposit(Transaction& trans);
	bool Withdraw(Transaction& trans);
	bool Transfer(Transaction& trans);
	bool AccountHistory(Transaction& trans);
	bool FundHistory(Transaction& trans);

};

#endif

