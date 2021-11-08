#include <iostream>
using std::cout;
using std::endl;
using std::boolalpha;

#include <string>
using std::string;
#include <utility>
#include "my_unique_ptr.h"


// Just a dummy class containing a string, for testing your code.
class StringWrapper {
public:
	StringWrapper(string name) : name(name) {};

	~StringWrapper() {
		cout << name << " is destroyed." << endl;
	}

	string getName() const { return name; }

private:
	const string name;
};


int main() {
	cout << boolalpha; // cout will display bool values as "true" and "false" instead of "1" and "0".

	cout << "Constructor Tests: " << endl;

    cout << "Default Constructor... ";
    my_unique_ptr<int> p1;
    bool result = ((p1.get_pointer() == nullptr) && p1.is_empty());
    cout << result << endl;

    cout << "Parameterized Constructor... ";
    int* a1 = new int{404}; // File Not Found.
    my_unique_ptr<int> p2{a1};
    result = ((p2.get_pointer() == a1) && !p2.is_empty());
    cout << result << endl;

    cout << "Copy Constructor and Sharing... ";
    my_unique_ptr<int> p3{p2};
    my_unique_ptr<int> p4{p1};

    result = ((p2.get_pointer() == nullptr) && 
    		  (p3.get_pointer() == a1) &&
			  (p4.get_pointer() == nullptr));
    cout << result << endl;

    cout << endl; // End of Constructor Tests.

    cout << "Operator=() Tests: " << endl;

    cout << "Copy Assignment Operator... ";
    my_unique_ptr<int> pp5{new int};
    my_unique_ptr<int> p5 = pp5;

    p4 = p3;
    
    result = ((p3.get_pointer() == nullptr) &&
			  (p4.get_pointer() == a1) &&
			  !p5.is_empty() && pp5.is_empty());
    cout << result << endl;

    cout << endl; // End of Operator=() Tests.


    cout << "Reset Tests: " << endl;

    cout << "reset()... ";
    p5.reset();
    result = (p5.get_pointer() == nullptr);
    cout << result << endl;

    cout << "reset(T* p)... ";
    int* a2 = new int{503}; // Service Unavailable.
    p4.reset(a2);
    result = ((p4.get_pointer() == a2) && !p4.is_empty());
    cout << result << endl;

    cout << endl; // End of Reset Tests.

    cout << "Swap Test: " << endl;
    cout << "swap()... ";
    int* a3 = new int{418}; // I'm a teapot!!!
    p3.reset(a3);
    result = ((p3.get_pointer() == a3) && (p4.get_pointer() == a2));
    p4.swap(p3);
    result &= ((p3.get_pointer() == a2) && (p4.get_pointer() == a3));
    cout << result << endl;

    cout << endl; // End of Swap Test.

    cout << "Release Tests: " << endl;

    cout << "release()... ";
    int* a2_out = p3.release();
    int* a3_out = p4.release();
    result = ((a2_out == a2) && (*a2 == 503) &&
              (a3_out == a3) && (*a3 == 418) &&
              p3.is_empty() && p4.is_empty());
    cout << result << endl;

    cout << endl; // End of Release Tests.

    cout << "Dereference and Pointer-to-Member Operator Tests: " << endl;

    cout << "operator*()... ";
    string sw1_name = "sw1";
    StringWrapper* sw1 = new StringWrapper{sw1_name};
    my_unique_ptr<StringWrapper> sw1_p1{sw1};
    result = ((*sw1_p1).getName() == sw1_name);
    cout << result << endl;

    cout << "operator->()... ";
    string sw2_name = "sw2";
    StringWrapper* sw2 = new StringWrapper{sw2_name};
    my_unique_ptr<StringWrapper> sw2_p1{sw2};
    result = (sw2_p1->getName() == sw2_name);
    cout << result << endl;

    cout << endl; // End of Dereference and Pointer-to-Member Operator Tests.

    cout << "Destructor Tests: " << endl;

    cout << "sw_temp should invoke destructors from sw_temp0 to sw_temp9." << endl;
    for (int i = 0; i < 10; i++) {
    	string sw_temp_name = "sw_temp";
    	char index = '0' + i;
    	string sw_temp_name_index = sw_temp_name + index;
    	StringWrapper* sw_temp = new StringWrapper{sw_temp_name_index};
    	my_unique_ptr<StringWrapper> sw_temp_p{sw_temp};
    }
    cout << endl;

    cout << "sw1 and sw2 should invoke their destructors only once when main() exits." << endl;
    my_unique_ptr<StringWrapper> sw1_p2{sw1_p1};
    my_unique_ptr<StringWrapper> sw1_p3{sw1_p1};
    my_unique_ptr<StringWrapper> sw2_p2{sw2_p1};
    my_unique_ptr<StringWrapper> sw2_p3{sw2_p1};

    cout << endl; // End of Destructor Tests.

    return 0;
}
