# Bank

A banking application which processes transactions. This banking application consists of three phases.
1) The program will read in a string of transactions from a file into an in-memory queue.
These transactions can open accounts, withdraw funds, deposit funds, transfer funds, or ask for the transactional history to be printed.
2) The program will next read from the queue and process the transactions in order.
3) When the queue has been depleted the program will print out all open accounts and balances in those accounts.
4) A file will be passed in by an argument to the program on the command line. The file will contain a list of transactions that need to be executed.
Transactions of the format described below (see section on transactions) will be contained in this file. There will be one transaction per line

