/* 
 lab1.cpp

 Name: JIANG Yicheng
   ID: 20760840
*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
	// Task 1
	// Define variables here
	int balance = 0;										  // Initial balance
	int coin_5_count = 3, coin_2_count = 3, coin_1_count = 3; // Initial coins
	int item_A_count = 3, item_B_count = 3;					  // Initial items

	const int ITEM_A_PRICE = 6, ITEM_B_PRICE = 4; // Prices

	int input_action = 0, input_coin = 0, input_item = 0; // Input

	int coin_5_return = 0, coin_2_return = 0, coin_1_return = 0; // Return

	while (!(input_action == 4))
	{
		// Task 2
		input_action = 0, input_coin = 0, input_item = 0;
		coin_5_return = 0, coin_2_return = 0, coin_1_return = 0;

		cout << "The balance is $" << balance << endl;
		cout << "Please choose an action:" << endl;
		cout << "1. Insert coin" << endl;
		cout << "2. Purchase" << endl;
		cout << "3. Return coins" << endl;
		cout << "4. Leave" << endl;
		cout << "Please enter 1-4: ";

		cin >> input_action;

		if (input_action == 1)
		{
			// Task 3
			while (!((input_coin == 1) || (input_coin == 2) || (input_coin == 5)))
			{
				cout << "Please insert a coin: $";
				cin >> input_coin;

				if (input_coin == 1)
				{
					++coin_1_count;
				}

				else if (input_coin == 2)
				{
					++coin_2_count;
				}

				else if (input_coin == 5)
				{
					++coin_5_count;
				}

				else
				{
					cout << "Only $5, $2 and $1 coins are accepted" << endl;
				}
			}

			balance += input_coin;
		}

		else if (input_action == 2)
		{
			while (!((input_item == 1) || (input_item == 2) || (input_item == 3)))
			{
				// Task 4
				cout << "Please select an item:" << endl;

				if (item_A_count == 0)
				{
					cout << "1. Item A - SOLD OUT" << endl;
				}
				else
				{
					cout << "1. Item A - $6" << endl;
				}

				if (item_B_count == 0)
				{
					cout << "2. Item B - SOLD OUT" << endl;
				}
				else
				{
					cout << "2. Item B - $4" << endl;
				}

				cout << "3. Go back" << endl;
				cout << "Please enter 1-3: ";
				cin >> input_item;

				if (input_item == 1)
				{
					if (item_A_count == 0)
					{
						input_item = 0;
						cout << "Item A has been sold out" << endl;
					}
					else if (balance - ITEM_A_PRICE < 0)
					{
						input_item = 0;
						cout << "Insufficient balance" << endl;
					}
					else
					{
						--item_A_count;
						balance -= ITEM_A_PRICE;
						cout << "Purchased item A" << endl;
					}
				}

				else if (input_item == 2)
				{
					if (item_B_count == 0)
					{
						input_item = 0;
						cout << "Item B has been sold out" << endl;
					}
					else if (balance - ITEM_B_PRICE < 0)
					{
						input_item = 0;
						cout << "Insufficient balance" << endl;
					}
					else
					{
						--item_B_count;
						balance -= ITEM_B_PRICE;
						cout << "Purchased item B" << endl;
					}
				}

				else if (!(input_item == 3))
				{
					cout << "Invalid choice" << endl;
				}
			}
		}

		else if (input_action == 3)
		{
			// Task 5
			coin_5_return = (coin_5_count < balance / 5) ? coin_5_count : balance / 5;
			coin_5_count -= coin_5_return;
			balance -= 5 * coin_5_return;

			coin_2_return = (coin_2_count < balance / 2) ? coin_2_count : balance / 2;
			coin_2_count -= coin_2_return;
			balance -= 2 * coin_2_return;

			coin_1_return = (coin_1_count < balance) ? coin_1_count : balance;
			coin_1_count -= coin_1_return;
			balance -= coin_1_return;

			for (int i = 0; i < coin_5_return; ++i)
			{
				cout << "Returned a $5 coin" << endl;
			}
			for (int i = 0; i < coin_2_return; ++i)
			{
				cout << "Returned a $2 coin" << endl;
			}
			for (int i = 0; i < coin_1_return; ++i)
			{
				cout << "Returned a $1 coin" << endl;
			}

			if (balance)
			{
				cout << "Oops... Not enough coins to return..." << endl;
			}
		}

		else if (input_action == 4)
		{
			// Task 6
			cout << "Bye" << endl;
		}

		else
		{
			cout << "Invalid choice" << endl;
		}
	}

	return 0;
}
