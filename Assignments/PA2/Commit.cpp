#include "Commit.h"
#include "Utils.h"

using namespace std;

// Part 1: Linked List Operations

List *list_new()
{
    List *new_list = new List;   // create a new list
    (*new_list).head = new Blob; // create its head

    (*((*new_list).head)).name = ""; // For Blob sentinel nodes, you should set name and ref to empty strings, and commit to nullptr
    (*((*new_list).head)).ref = "";
    (*((*new_list).head)).commit = nullptr;

    (*((*new_list).head)).prev = ((*new_list).head); // The head is the only blob in the new list
    (*((*new_list).head)).next = ((*new_list).head); // Its prev and next are pointing at itself

    return new_list;
}

void list_push_back(List *list, Blob *blob)
{                                            // the blob is the last one in the list
    (*blob).next = (*list).head;             // blob -> head
    (*blob).prev = ((*((*list).head)).prev); // last <- blob
    (*((*((*list).head)).prev)).next = blob; // last -> blob
    (*((*list).head)).prev = blob;           // blob <- head
}

Blob *list_find_name(const List *list, const string &name)
{
    for (Blob *this_blob = list->head->next; this_blob != list->head; this_blob = this_blob->next) // search until reach the head
    {
        if (this_blob->name == name) // if the blob with the wanted name is found
        {
            return this_blob; // return the pointer to the blob
        }
    }
    // if no blobs were found.
    return nullptr;
}

Blob *list_put(List *list, const string &name, const string &ref) // Put a blob with the given name and content (ref or commit) to the linked list.
{
    Blob *new_blob = list_find_name(list, name);
    if (new_blob != nullptr) //If a blob with the same name exists in the linked list,
    {
        (*new_blob).ref = ref; //update the blob by replacing the content (ref or commit) with the given content (ref or commit).
        return new_blob;
    }

    //If no blobs with the same name exists in the linked list
    //create a new blob with the given content (ref or commit)
    new_blob = new Blob;
    (*new_blob).name = name;
    (*new_blob).ref = ref;
    //and insert it to the linked list with the name following ascending lexicographic order.

    if (name < (*((*((*list).head)).next)).name) // head < new < 1st
    {
        (*new_blob).prev = (*list).head;             // head <- new
        (*new_blob).next = (*((*list).head)).next;   // new -> 1st
        (*((*((*list).head)).next)).prev = new_blob; // new <- 1st
        (*((*list).head)).next = new_blob;           // head -> new
        return new_blob;
    }

    for (Blob *this_blob = (*((*list).head)).next; this_blob != (*((*list).head)).prev; this_blob = (*this_blob).next)
    {
        if (((*this_blob).name < name) && (name < (*((*this_blob).next)).name)) // this < new < next
        {
            (*new_blob).prev = this_blob;           // this <- new
            (*new_blob).next = (*this_blob).next;   // new -> next
            (*((*this_blob).next)).prev = new_blob; // new <- next
            (*this_blob).next = new_blob;           // this -> new
            return new_blob;
        }
    }

    // this => last
    (*new_blob).prev = (*((*list).head)).prev;   // last <- new
    (*new_blob).next = (*list).head;             // new -> head
    (*((*((*list).head)).prev)).next = new_blob; // last -> new
    (*((*list).head)).prev = new_blob;           // new <- head
    return new_blob;
}

Blob *list_put(List *list, const string &name, Commit *commit)
{
    Blob *new_blob = list_find_name(list, name);
    if (new_blob != nullptr) //If a blob with the same name exists in the linked list,
    {
        (*new_blob).commit = commit; //update the blob by replacing the content (ref or commit) with the given content (ref or commit).
        return new_blob;
    }

    //If no blobs with the same name exists in the linked list
    //create a new blob with the given content (ref or commit)
    new_blob = new Blob;
    (*new_blob).name = name;
    (*new_blob).commit = commit;
    //and insert it to the linked list with the name following ascending lexicographic order.

    if (name < (*((*((*list).head)).next)).name) // head < new < 1st
    {
        (*new_blob).prev = (*list).head;             // head <- new
        (*new_blob).next = (*((*list).head)).next;   // new -> 1st
        (*((*((*list).head)).next)).prev = new_blob; // new <- 1st
        (*((*list).head)).next = new_blob;           // head -> new
        return new_blob;
    }

    for (Blob *this_blob = (*((*list).head)).next; this_blob != (*((*list).head)).prev; this_blob = (*this_blob).next)
    {
        if (((*this_blob).name < name) && (name < (*((*this_blob).next)).name)) // this < new < next
        {
            (*new_blob).prev = this_blob;           // this <- new
            (*new_blob).next = (*this_blob).next;   // new -> next
            (*((*this_blob).next)).prev = new_blob; // new <- next
            (*this_blob).next = new_blob;           // this -> new
            return new_blob;
        }
    }

    // this => last
    list_push_back(list, new_blob);
    return new_blob;
}

bool list_remove(List *list, const string &target)
{
    Blob *blob_remove = list_find_name(list, target);
    if (blob_remove == nullptr)
    {
        return false;
    }
    (*((*blob_remove).prev)).next = (*blob_remove).next;
    (*((*blob_remove).next)).prev = (*blob_remove).prev;
    delete blob_remove;
    blob_remove = nullptr;
    return true;
}

int list_size(const List *list)
{
    int size = 0;
    for (Blob *this_blob = (*((*list).head)).next; this_blob != (*list).head; this_blob = (*this_blob).next) // search until reach the head
    {
        size++;
    }
    return size;
}

void list_clear(List *list)
{
    for (Blob *this_blob = (*((*list).head)).next, *next_blob; this_blob != (*list).head; this_blob = next_blob) // search until reach the head
    {
        next_blob = (*this_blob).next;
        delete this_blob;
        this_blob = nullptr;
    }
    (*((*list).head)).next = (*list).head;
    (*((*list).head)).prev = (*list).head;
}

void list_delete(List *list)
{
    list_clear(list);
    delete (*list).head;
    delete list;
    list = nullptr;
}

void list_replace(List *list, const List *another) //Replace the linked list with the given another linked list, maintaining the order of blobs. Deep copy the blobs in the process.
{
    list_clear(list);
    for (Blob *this_blob = (*((*another).head)).next; this_blob != (*another).head; this_blob = (*this_blob).next) // search until reach the head
    {
        Blob *copied_blob = new Blob;
        copied_blob->name = this_blob->name;
        copied_blob->ref = this_blob->ref;
        copied_blob->commit = this_blob->commit;
        list_push_back(list, copied_blob);
    }
}

List *list_copy(const List *list)
{
    List *copied_list = list_new();
    list_replace(copied_list, list);
    return copied_list;
}

// Part 2: Gitlite Commands

// Print out the commit info. Used in log.
void commit_print(const Commit *commit)
{
    cout << "commit " << commit->commit_id << endl;

    if (commit->second_parent != nullptr)
    {
        cout << "Merge: " << commit->parent->commit_id.substr(0, 7)
             << " " << commit->second_parent->commit_id.substr(0, 7) << endl;
    }

    cout << "Date: " << commit->time << endl
         << commit->message;
}

// Check whether a is b's ancestor (including themselves)
void is_ancestor(Commit *a, Commit *b, bool &m)
{
    if (m || a == nullptr || b == nullptr)
    {
        return;
    }
    if (a == b)
    {
        m = true;
        return;
    }
    if (b->parent != nullptr)
    {
        is_ancestor(a, b->parent, m);
    }
    if (b->second_parent != nullptr)
    {
        is_ancestor(a, b->second_parent, m);
    }
}

//  Find ancestor(consider first parent first, including themselves)
void find_ancestor_f(Commit *a, Commit *b, Commit *&ancestor_f)
{
    if (ancestor_f != nullptr || a == nullptr || b == nullptr)
    {
        return;
    }
    bool a_is_ancestor = false;
    is_ancestor(a, b, a_is_ancestor);
    if (a_is_ancestor)
    {
        ancestor_f = a;
        return;
    }
    if (a->parent != nullptr)
    {
        find_ancestor_f(a->parent, b, ancestor_f);
    }
    if (a->second_parent != nullptr)
    {
        find_ancestor_f(a->second_parent, b, ancestor_f);
    }
}

//  Find ancestor(consider second parent first, including themselves)
void find_ancestor_s(Commit *a, Commit *b, Commit *&ancestor_s)
{
    if (ancestor_s != nullptr || a == nullptr || b == nullptr)
    {
        return;
    }
    bool a_is_ancestor = false;
    is_ancestor(a, b, a_is_ancestor);
    if (a_is_ancestor)
    {
        ancestor_s = a;
        return;
    }
    if (a->second_parent != nullptr)
    {
        find_ancestor_f(a->second_parent, b, ancestor_s);
    }
    if (a->parent != nullptr)
    {
        find_ancestor_f(a->parent, b, ancestor_s);
    }
}

Commit *get_lca(Commit *c1, Commit *c2)
{
    Commit *ancestor_f = nullptr;
    Commit *ancestor_s = nullptr;
    find_ancestor_f(c1, c2, ancestor_f);
    find_ancestor_s(c1, c2, ancestor_s);
    if (ancestor_f == ancestor_s)
    {
        return ancestor_f;
    }
    bool m = false; // indicate whether f is s's ancestor
    is_ancestor(ancestor_f, ancestor_s, m);
    if (m) // f is s's ancestor => f is older than s
    {
        return ancestor_s;
    }
    else
    {
        return ancestor_f;
    }
}
