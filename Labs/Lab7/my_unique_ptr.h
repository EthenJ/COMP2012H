#ifndef MY_UNIQUE_PTR_H_
#define MY_UNIQUE_PTR_H_

#include <utility>

template <typename T>
class my_unique_ptr
{
public:
	/*******************************
	 * Constructors and Destructor *
	 *******************************/

	// Default Constructor, p is empty.

	/*Default constructor. The unique pointer is initialized as empty.
	 *p should be set to nullptr.*/
	my_unique_ptr() : p(nullptr) {}

	// Parameterized Constructor, takes ownership of p.
	/*
	 * Note: There exists the issue of 2 my_unique_ptrs thinking they have single and separate ownership of the same object.
	 * We ignore this for the sake of lab simplicity, as it is a complex problem to solve.
	 */

	/*Parametrized constructor from an existing raw pointer p.
	 *The unique pointer should point to p.
	 *Note: For the purpose of this lab, you can assume that there exists no other unique pointers that point to the same p when this constructor is called.*/
	my_unique_ptr(T *p) : p(p) {}

	// Copy Constructor - transfers ownership of object from u to this pointer

	/*Copy constructor from another unique pointer x. If x currently owns an object, the newly constructed unique pointer will take over ownership of that object.
	 *If x is not empty, initialize the unique pointer such that it now points to the object owned by x. Then, set x as empty.
	 *Otherwise, initialize the unique pointer as an empty pointer*/
	my_unique_ptr(my_unique_ptr<T> &x) : p(nullptr)
	{
		if (!x.is_empty())
		{
			p = x.get_pointer(); // initialize the unique pointer such that it now points to the object owned by x.
			x.release();		 // Then, set x as empty.
		}
	}

	// Destructor - deallocate p if it is not a nullptr.

	/*If the pointer is non-empty, delete the owned object.
	 *Otherwise, there is no need to deallocate anything.*/
	~my_unique_ptr()
	{
		if (!is_empty())
		{
			delete p;
		}
	}

	/************************
	 * Operator Overloading *
	 ************************/

	// Copy Assignment Operator.

	/*Copy assignment operator.
	 *The procedure is similar to the copy constructor; take over ownership of the object owned by x, and set x as empty.
	 *Additionally, remember to destroy the previously owned object if the pointer is originally non-empty.*/
	my_unique_ptr &operator=(my_unique_ptr<T> &x)
	{
		reset(x.get_pointer);
		return *this;
	}

	// Dereference Operators.

	/*Returns the managed object (i.e. the result of dereferencing p).
	 *You can assume that the unique pointer is not empty.
	 *For any non-empty unique pointer mptr, *mptr should be equivalent to *p.*/
	T &operator*() const
	{
		if (!is_empty())
		{
			return *p;
		}
		else
		{
			return NULL;
		}
	}

	/*Returns the stored raw pointer p.
	 *For any non-empty unique pointer mptr, mptr->foo() should be equivalent to p->foo().*/
	T *operator->() const
	{
		return p;
	}

	/*********************
	 * Utility Functions *
	 *********************/

	T *get_pointer() const { return p; }
	bool is_empty() const { return p == nullptr; }

	/*Releases ownership of the current owned object (if any), and returns the released pointer.
	 *After calling this method, the unique pointer should be empty.*/
	T *release()
	{
		reset();
		return p;
	}

	/*Resets the unique pointer to an empty pointer.
	 *If the unique pointer is previously non-empty, release and deallocate the previously owned object.*/
	void reset()
	{
		if (!is_empty())
		{
			delete p;
		}
		p = nullptr;
	}

	/*Resets the unique pointer to a unique pointer owning p.
	 *If the unique pointer is previously non-empty, release and deallocate the previously owned object.*/
	void reset(T *p)
	{
		if (!is_empty())
		{
			reset();
		}
		this->p = p;
	}

	/*Swaps the unique pointer with x.
	 *After swapping, the unique pointer should now own the object of x, and vice versa.*/
	void swap(my_unique_ptr<T> &x)
	{
		T *temp = x.get_pointer();
		x.reset(get_pointer());
		reset(temp);
	}

private:
	T *p;
};

#endif /* MY_UNIQUE_PTR_H_ */
