/**
* Linked list representing the body of the snake
*/
// #include<iostream>
// using namespace std;

struct SnakeBody
{
	SnakeBody *prev = nullptr, *next = nullptr;

	// Coordinates on the grid
	int x = 0, y = 0;
};

//Returns the head of the snake
SnakeBody *get_head(SnakeBody &body)
{
	// START OF YOUR IMPLEMENTATION
	// Hint: You can make it into a recursive function
	if (body.prev == nullptr)
	{
		return &body;
	}
	else
	{
		return get_head(*(body.prev));
	}

	// END OF YOUR IMPLEMENTATION
}

//Returns the tail of the snake
SnakeBody *get_tail(SnakeBody &body)
{
	// START OF YOUR IMPLEMENTATION
	if (body.next == nullptr)
	{
		return &body;
	}
	else
	{
		return get_tail(*body.next);
	}
	// END OF YOUR IMPLEMENTATION
}

//Returns the nth next snake body. In particular, returns the pointer to body (the input) if n=0. Returns the tail of the snake if n is too large.
SnakeBody *get_next_body(SnakeBody &body, int n)
{
	// START OF YOUR IMPLEMENTATION
	if (body.next == nullptr)
	{
		return &body;
	}
	else if (n <= 0)
	{
		return &body;
	}
	else
	{
		return get_next_body(*body.next, n - 1);
	}
	// END OF YOUR IMPLEMENTATION
}

/**
* Removes itself (the given argument) from the linked list. WARNING: Does not destroy (delete) itself from memory!
*/
void remove_self(SnakeBody &body)
{
	// START OF YOUR IMPLEMENTATION
	if (body.prev != nullptr)
		body.prev->next = body.next;
	if (body.next != nullptr)
		body.next->prev = body.prev;
	body.next = nullptr;
	body.prev = nullptr;
	// END OF YOUR IMPLEMENTATION
}

/**
* Assume that the linked list is locally ABC. 
* Then the list becomes ANBC. Make sure to consider the cases where this is the head/tail.
* This function assumes that N is not already in the list.
*/
void insert_into_previous(SnakeBody &B, SnakeBody *N)
{
	// START OF YOUR IMPLEMENTATION
	N->next = &B;
	if (B.prev != nullptr)
	{
		N->prev = B.prev;
		B.prev->next = N;
		// cout<<"c"<<endl;
	}
	else
	{
		N->prev = nullptr;
		// cout<<"d"<<endl;
	}
	B.prev = N;
	// END OF YOUR IMPLEMENTATION
}

/**
* Assume that the linked list is locally ABC.
* Then the list becomes ABNC
*/
void insert_into_next(SnakeBody &B, SnakeBody *N)
{
	// START OF YOUR IMPLEMENTATION
	N->prev = &B;
	if (B.next != nullptr)
	{
		N->next = B.next;
		B.next->prev = N;
		// cout<<"a"<<endl;
	}
	else
	{
		N->next = nullptr;
		// cout<<"b"<<endl;
	}
	B.next = N;
	// END OF YOUR IMPLEMENTATION
}