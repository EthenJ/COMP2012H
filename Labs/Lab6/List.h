#ifndef _LIST
#define _LIST

class List {
private:
    struct Node {
        int data;
        Node* next;
        Node(int data);
    };
    Node* head;
protected:
    List();
    List(const List& rhs);
    ~List();
    
    bool empty() const;
    int size() const;

    void print() const;

    List& assign(const List& rhs);
    void insertAt(int data, int index);
    void removeAt(int index);               
    int get(int index) const;
    void set(int index, int data);
};

#endif