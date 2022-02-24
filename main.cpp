#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{

	string file_name = argv[1];
	JollyBanker bank;

	bank.ReadTransaction(file_name);
	bank.ProcessQue();
	bank.DisplayAllAccount();

}
