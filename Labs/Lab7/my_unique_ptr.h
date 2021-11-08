#ifndef MY_UNIQUE_PTR_H_
#define MY_UNIQUE_PTR_H_

#include <utility>

template <typename T>
class my_unique_ptr {
public:
	/*******************************
	 * Constructors and Destructor *
	 *******************************/

	// Default Constructor, p is empty.
	my_unique_ptr() {
		// TODO
	}

	// Parameterized Constructor, takes ownership of p.
	/*
	 * Note: There exists the issue of 2 my_unique_ptrs thinking they have single and separate ownership of the same object.
	 * We ignore this for the sake of lab simplicity, as it is a complex problem to solve.
	 */
	my_unique_ptr(T* p) {
		// TODO
	}

	// Copy Constructor - transfers ownership of object from u to this pointer
	my_unique_ptr(my_unique_ptr<T>& x) {
		// TODO
	}

	// Destructor - deallocate p if it is not a nullptr.
	~my_unique_ptr() {
		// TODO
	}



	/************************
	 * Operator Overloading *
	 ************************/

	// Copy Assignment Operator.
	my_unique_ptr& operator=(my_unique_ptr<T>& x) {
		// TODO
	}

	// Dereference Operators.
	T& operator*() const {
		// TODO
	}

	T* operator->() const {
		// TODO
	}



	/*********************
	 * Utility Functions *
	 *********************/

	T* get_pointer() const { return p; }
	bool is_empty() const { return p == nullptr; }

	T* release() {
		// TODO
	}

	void reset() {
		// TODO
	}

	void reset(T* p) {
		// TODO
	}
	
	void swap(my_unique_ptr<T>& x) {
		// TODO
	}



private:
	T* p;
};

#endif /* MY_UNIQUE_PTR_H_ */
