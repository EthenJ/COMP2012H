#include "Commit.h"
#include "Utils.h"

using namespace std;

// Part 1: Linked List Operations

List *list_new() {
    return nullptr;
}

void list_push_back(List *list, Blob *blob) {

}

Blob *list_find_name(const List *list, const string &name) {
    return nullptr;
}

Blob *list_put(List *list, const string &name, const string &ref) {
    return nullptr;
}

Blob *list_put(List *list, const string &name, Commit *commit) {
    return nullptr;
}

bool list_remove(List *list, const string &target) {
    return false;
}

int list_size(const List *list) {
    return 0;
}

void list_clear(List *list) {

}

void list_delete(List *list) {

}

void list_replace(List *list, const List *another) {

}

List *list_copy(const List *list) {
    return nullptr;
}

// Part 2: Gitlite Commands

// Print out the commit info. Used in log.
void commit_print(const Commit *commit) {
    cout << "commit " << commit->commit_id << endl;

    if (commit->second_parent != nullptr) {
        cout << "Merge: " << commit->parent->commit_id.substr(0, 7)
             << " " << commit->second_parent->commit_id.substr(0, 7) << endl;
    }

    cout << "Date: " << commit->time << endl << commit->message;
}

Commit *get_lca(Commit *c1, Commit *c2) {
    return nullptr;
}
