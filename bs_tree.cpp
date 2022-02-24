#include "bs_tree.h"

BSTree::BSTree()
{
}

BSTree::~BSTree()
{
	Empty();
}

bool BSTree::Insert(Account* acct)
{
	if (root == NULL)
	{
		Node* created_node = new Node();
		created_node->pAcct = new Account(*acct);
		created_node->left = created_node->right = NULL;
		root = created_node;
		return true;
	}

	else
	{
		return insertHelper(this->root, acct);
	}
	return false;
}

bool BSTree::Remove(Account* acct)
{
	if (root == NULL)
	{
		return true;
	}
	else if (acct->getID() <= root->pAcct->getID())
	{
		return removeHelper(this->root->left, acct);
	}

	else if (acct->getID() > root->pAcct->getID())
	{
		return removeHelper(this->root->right, acct);
	}
	return false;
}

bool BSTree::Retrieve(const int& target, Account*& acct) const
{
	Node* temp = root;
	return retrieveHelper(target, acct, temp);
}


void BSTree::Display() const
{
	displayHelper(root);
	return;
}

bool BSTree::isEmpty() const
{
	if (this->root == NULL)
	{
		return true;
	}
	return false;
}

bool BSTree::Empty()
{
	root = NULL;
	return true;
}

bool BSTree::insertHelper(Node* node, Account* acct)
{
	if (acct->getID() == node->pAcct->getID())
	{
		return true;
	}

	else if (acct->getID() < node->pAcct->getID())
	{
		if (node->left == NULL)
		{
			Node* created_node = new Node();
			created_node->pAcct = new Account(*acct);
			node->left = created_node;
			node->left->left = node->left->right = NULL;
			return true;
		}

		else
		{
			return insertHelper(node->left, acct);
		}
	}

	else if (acct->getID() > node->pAcct->getID())
	{
		if (node->right == NULL)
		{
			Node* created_node = new Node();
			created_node->pAcct = new Account(*acct);
			node->right = created_node;
			node->right->left = node->right->right = NULL;
			return true;
		}

		else
		{
			return insertHelper(node->right, acct);
		}
	}

	else
	{
		return false;
	}
}

bool BSTree::removeHelper(Node* node, Account* acct)
{
	if (root->right == NULL && root->left == NULL)
	{
		delete root->pAcct;
		delete root;
		root = NULL;
	}
	else if (root->right == NULL)
	{
		Node* temp = root;
		root = root->left;
		delete temp->pAcct;
		delete temp;
	}
	else if (root->left == NULL)
	{
		Node* temp = root;
		root = root->right;
		delete temp->pAcct;
		delete temp;
	}
	else
	{
		Node* temp = findMax(root->left);
		root->pAcct = new Account(*acct);
		removeHelper(root->left, temp->pAcct);
	}
	return false;
}

bool BSTree::retrieveHelper(const int& target, Account*& acct, Node* root) const
{
	if (root != NULL)
	{
		if (target == root->pAcct->getID())
		{
			acct = root->pAcct;
			return true;
		}
		else if (target < root->pAcct->getID())
		{

			return retrieveHelper(target, acct, root->left);
		}
		else
		{

			return retrieveHelper(target, acct, root->right);
		}
	}


	return false;
}


void BSTree::displayHelper(Node* node) const
{
	if (node == NULL)
	{
		return;
	}

	displayHelper(node->left);
	node->pAcct->DisplayAllFund();
	displayHelper(node->right);
}

void BSTree::emptyHelper(Node* node)
{
	if (node == NULL)
	{
		return;
	}

	emptyHelper(node->left);
	emptyHelper(node->right);
	delete node->pAcct;
	node->pAcct = NULL;
	delete node;
	node = NULL;
	return;
}