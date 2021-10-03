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
{   // the blob is the last one in the list;
    (*((*((*list).head)).prev)).next = blob; // it should be the next of the previous last blob
    (*blob).prev = ((*((*list).head)).prev); // the prev of the blob should be the previous last blob
    (*((*list).head)).prev = blob; // the prev of the head should be the blob
    (*blob).next = (*list).head; // the next one of the blob should be the head of the list
}

Blob *list_find_name(const List *list, const string &name)
{
    return nullptr;
}

Blob *list_put(List *list, const string &name, const string &ref)
{
    return nullptr;
}

Blob *list_put(List *list, const string &name, Commit *commit)
{
    return nullptr;
}

bool list_remove(List *list, const string &target)
{
    return false;
}

int list_size(const List *list)
{
    return 0;
}

void list_clear(List *list)
{
}

void list_delete(List *list)
{
}

void list_replace(List *list, const List *another)
{
}

List *list_copy(const List *list)
{
    return nullptr;
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

Commit *get_lca(Commit *c1, Commit *c2)
{
    return nullptr;
}
