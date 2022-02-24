#ifndef BS_TREE_H_
#define BS_TREE_H_

#include "account.h"
#include <iostream>

using namespace std;

class BSTree
{

public:

	BSTree();
	~BSTree();

	bool Insert(Account* acct);
	bool Remove(Account* acct);
	bool Retrieve(const int& account_number, Account*& account) const;

	void Display() const;

	bool Empty();
	bool isEmpty() const;


private:

	struct Node
	{
		Account* pAcct = NULL;
		Node* right = NULL;
		Node* left = NULL;
	};

	Node* root = NULL;

	Node* findMax(Node* root)
	{
		if (root == NULL)
		{
			return NULL;
		}

		while (root->right != NULL)
		{
			root = root->right;
		}
		return NULL;
	}

	bool insertHelper(Node* node, Account* acct);
	bool removeHelper(Node* node, Account* acct);
	bool retrieveHelper(const int& target, Account*& acct, Node* root) const;

	void displayHelper(Node* node) const;
	void emptyHelper(Node* node);

};
#endif