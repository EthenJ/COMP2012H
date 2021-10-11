#include "gitlite.h"
#include "Utils.h"

using namespace std;

const string msg_initial_commit = "initial commit";

const string msg_no_changes_added = "No changes added to the commit.";

const string msg_no_reason_remove = "No reason to remove the file.";

const string msg_commit_does_not_exist = "No commit with that id exists.";

const string msg_file_does_not_exist = "File does not exist in that commit.";

const string msg_untracked_file = "There is an untracked file in the way; delete it, or add and commit it first.";

const string msg_branch_does_not_exist = "A branch with that name does not exist.";

const string msg_checkout_current = "No need to checkout the current branch.";

const string msg_branch_exists = "A branch with that name already exists.";

const string msg_remove_current = "Cannot remove the current branch.";

const string msg_merge_current = "Cannot merge a branch with itself.";

const string msg_exists_uncommitted_changes = "You have uncommitted changes.";

const string msg_given_is_ancestor_of_current = "Given branch is an ancestor of the current branch.";

const string msg_fast_forward = "Current branch fast-forwarded.";

const string msg_encountered_merge_conflict = "Encountered a merge conflict.";

const string status_branches_header = "=== Branches ===";

const string status_staged_files_header = "=== Staged Files ===";

const string status_removed_files_header = "=== Removed Files ===";

const string status_modifications_not_staged_header = "=== Modifications Not Staged For Commit ===";

const string msg_status_deleted = " (deleted)";

const string msg_status_modified = " (modified)";

const string status_untracked_files_header = "=== Untracked Files ===";

string get_merge_commit_message(const Blob *given_branch, const Blob *current_branch)
{
    string message("Merged " + given_branch->name + " into " + current_branch->name + ".");
    return message;
}

void init(Blob *&current_branch, List *&branches, List *&staged_files, List *&tracked_files, Commit *&head_commit)
{
    // 1. Initialize the linked lists: branches, staged_files, tracked_files.
    branches = list_new();      // braches
    staged_files = list_new();  // staged files
    tracked_files = list_new(); // tracked files

    // 2. Create the initial commit with message initial commit.
    head_commit = new Commit;                  // initial commit
    head_commit->message = msg_initial_commit; // message initial commit

    // Set the time string and compute the hash. This commit tracks no files (initialize commit->tracked_files as well) and has no parents.
    head_commit->time = get_time_string();                                      // time string
    head_commit->commit_id = get_sha1(head_commit->message, head_commit->time); // compute the hash
    head_commit->tracked_files = list_new();                                    // tracks no files (initialize commit->tracked_files as well)
    head_commit->parent = nullptr;                                              // has no parents

    // 3. Create a branch called master and set it as the current branch.
    current_branch = list_put(branches, "master", ""); // ref remains empty when representing a branch.
    // Add the initial commit to the branch. Set the head commit of the repository as well.
    current_branch->commit = head_commit; // Add the initial commit to the branch
                                          // Set the head commit of the repository as well.
}

bool add(const string &filename, List *staged_files, List *tracked_files, const Commit *head_commit)
{
    if (is_file_exist(filename))
    {
        // 1. Add content of the file to the repository by saving the content of the file to the currently tracked files of the repository.
        string ref = get_sha1(filename);        // get the file content
        list_put(tracked_files, filename, ref); // save the content of the file to the currently tracked files of the repository

        // 2. Perform one of the following:
        Blob *tracked_one = list_find_name(head_commit->tracked_files, filename);
        // If the file is tracked in the head commit of the repository, with the same content as the current file,
        if (tracked_one != nullptr)
        {
            if (tracked_one->ref == ref)
            {
                // then remove the file from the staging area (if it is staged). Return false.
                if (list_find_name(staged_files, filename) != nullptr)
                {
                    list_remove(staged_files, filename);
                }
                return false;
                // (This happens when a modified file was added, then restored to original version, and added again.
                // Since the file was restored, it should be removed from the staging area.)
            }
        }

        // In most cases, simply save the content of the file to the staging area as well. Return true.
        list_put(staged_files, filename, ref);
        stage_content(filename); // stupid!!!
        return true;
    }
    return false;
}

bool commit(const string &message, Blob *current_branch, List *staged_files, List *tracked_files, Commit *&head_commit)
{
    // 1. Failure check: If there are no files in the staging area, and no files staged for removal,
    if ((staged_files->head->next == staged_files->head)) // no files in the staging area
    {
        if (head_commit->tracked_files->head->next != nullptr)
        {
            for (Blob *this_file = head_commit->tracked_files->head->next;
                 this_file != head_commit->tracked_files->head; this_file = this_file->next)
            {
                if (list_find_name(tracked_files, this_file->name) != nullptr) // not staged for removal,
                {
                    continue;
                }
                // print No changes added to the commit. and return false.
                cout << msg_no_changes_added << endl;
                return false;
            }
        }
    }

    // 2. Create a new commit. Save the message, time and commit id.
    Commit *new_commit = new Commit;                                         // Create a new commit
    new_commit->message = message;                                           // Save the message
    new_commit->time = get_time_string();                                    // time
    new_commit->commit_id = get_sha1(new_commit->message, new_commit->time); // commit id

    // 3. Take a snapshot of the repository by copying the tracked files of the repository to the tracked files of this commit.
    // These files become the files that are tracked by this commit.
    new_commit->tracked_files = list_copy(tracked_files);

    // 4. Add this commit to the current branch and update the head commit of the repository.
    new_commit->parent = head_commit;
    current_branch->commit = new_commit; // Add this commit to the current branch
    head_commit = new_commit;            // update the head commit of the repository

    // 5. Clear the staging area and return true.
    list_clear(staged_files); // Clear the staging area
    return true;              // return true
}

bool remove(const string &filename, List *staged_files, List *tracked_files, const Commit *head_commit)
{
    // 1. If the file is tracked by the head commit of the repository, then remove it from the currently tracked files of the repository
    if (list_find_name(head_commit->tracked_files, filename) != nullptr) // If the file is tracked by the head commit of the repository
    {
        list_remove(tracked_files, filename); // remove it from the currently tracked files of the repository
        if (is_file_exist(filename))
        {
            restricted_delete(filename); // and remove the file from the current working directory (if it exists).
        }
        // The file is staged for removal.
        return true;
    }

    // 2. If the file was staged for addition, remove it from the tracked files of the repository and the staging area.
    else if (list_find_name(tracked_files, filename)) // not in head_commit->tracked_files, but in tracked_files
    {
        list_remove(tracked_files, filename); // remove it from the tracked files of the repository
        list_remove(staged_files, filename);  // remove it from the tracked files of the staging area
        return true;
    }

    // 3. If none of the above is satisfied, print No reason to remove the file. and return false. Otherwise, return true.
    cout << msg_no_reason_remove << endl;
    return false;
}

void log(const Commit *head_commit)
{
    // Starting from the head commit of the repository,
    // display information for each commit backwards until the initial commit,
    // by following the parent commit (ignore second parents).
    cout << "===" << endl;
    commit_print(head_commit);
    cout << endl;
    if (head_commit->parent != nullptr)
    {
        log(head_commit->parent);
    }
}

void status(const Blob *current_branch, const List *branches, const List *staged_files, const List *tracked_files,
            const List *cwd_files, const Commit *head_commit)
{
    // Branches: Display the names of all branches. Marks the current branch with *.
    // === Branches ===
    cout << status_branches_header << endl;
    for (Blob *this_branch = branches->head->next; this_branch != branches->head; this_branch = this_branch->next)
    {
        if (this_branch != current_branch)
        {
            // another-branch
            cout << this_branch->name << endl;
        }
        else
        {
            // *master
            cout << "*" << this_branch->name << endl;
        }
    }
    cout << endl;

    // Staged Files: Display the filenames of all files that are staged for addition.
    cout << status_staged_files_header << endl;
    if (staged_files->head->next != nullptr)
    {
        for (Blob *this_staged_file = staged_files->head->next;
             this_staged_file != staged_files->head; this_staged_file = this_staged_file->next)
        {
            if (is_file_exist(this_staged_file->name))
            {
                if (this_staged_file->ref == get_sha1(this_staged_file->name))
                {
                    cout << this_staged_file->name << endl;
                }
            }
        }
    }
    cout << endl;

    // Removed Files: Display the filenames of all files that are staged for removal.
    cout << status_removed_files_header << endl;
    if (head_commit->tracked_files->head->next != nullptr)
    {
        for (Blob *this_committed_file = head_commit->tracked_files->head->next;
             this_committed_file != head_commit->tracked_files->head; this_committed_file = this_committed_file->next)
        {
            if (list_find_name(tracked_files, this_committed_file->name) == nullptr)
            {
                cout << this_committed_file->name << endl;
            }
        }
    }
    cout << endl;

    // Modifications Not Staged For Commit: Display the filenames for the following files.
    cout << status_modifications_not_staged_header << endl;

    // Append (modified) for case 1 and 2. Append (deleted) for case 3 and 4.

    // 1. Unstaged files that are tracked in the head commit of the repository,
    // but the content recorded in the commit is different with the content in the current working directory (CWD).
    if (head_commit->tracked_files->head->next != nullptr)
    {
        for (Blob *this_committed_file = head_commit->tracked_files->head->next;
             this_committed_file != head_commit->tracked_files->head; this_committed_file = this_committed_file->next)
        {
            // Unstaged files that are tracked in the head commit of the repository
            if (list_find_name(staged_files, this_committed_file->name) == nullptr)
            {
                // but the content recorded in the commit is different with the content in the current working directory (CWD).
                if (is_file_exist(this_committed_file->name))
                {
                    if (this_committed_file->ref != get_sha1(this_committed_file->name))
                    {
                        cout << this_committed_file->name << msg_status_modified << endl;
                    }
                }
            }
        }
    }

    // 2. Files that were staged for addition, but the content recorded in the staging area is different with the content in CWD.
    if (staged_files->head->next != nullptr)
    {
        for (Blob *this_staged_file = staged_files->head->next;
             this_staged_file != staged_files->head; this_staged_file = this_staged_file->next)
        {
            if (is_file_exist(this_staged_file->name))
            {
                if (this_staged_file->ref != get_sha1(this_staged_file->name))
                {
                    cout << this_staged_file->name << msg_status_modified << endl;
                }
            }
        }
    }

    // 3. Files staged for addition but deleted in CWD.
    if (staged_files->head->next != nullptr)
    {
        for (Blob *this_staged_file = staged_files->head->next;
             this_staged_file != staged_files->head; this_staged_file = this_staged_file->next)
        {
            if (!(is_file_exist(this_staged_file->name)))
            {
                cout << this_staged_file->name << msg_status_deleted << endl;
            }
        }
    }

    // 4. Files not staged for removal but tracked in the head commit of the repository and deleted in CWD.
    if (head_commit->tracked_files->head->next != nullptr)
    { // tracked in the head commit
        for (Blob *this_committed_file = head_commit->tracked_files->head->next;
             this_committed_file != head_commit->tracked_files->head; this_committed_file = this_committed_file->next)
        {
            // Files not staged for removal
            if (list_find_name(tracked_files, this_committed_file->name) != nullptr)
            {
                // but the content recorded in the commit is different with the content in the current working directory (CWD).
                if (!(is_file_exist(this_committed_file->name)))
                {
                    cout << this_committed_file->name << msg_status_deleted << endl;
                }
            }
        }
    }

    cout << endl;

    // Untracked Files: Files exist in CWD but not currently tracked by the repository.
    cout << status_untracked_files_header << endl;
    if (cwd_files->head->next != nullptr)
    {
        for (Blob *cwd_file = cwd_files->head->next; cwd_file != cwd_files->head; cwd_file = cwd_file->next)
        {
            if (list_find_name(tracked_files, cwd_file->name) == nullptr)
            {
                cout << cwd_file->name << endl;
            }
        }
    }
    cout << endl;

    // Entries should be listed in ascending lexicographic order. The * of current branch does not count.
}

bool checkout(const string &filename, Commit *commit)
{
    return false;
}

bool checkout(const string &branch_name, Blob *&current_branch, const List *branches, List *staged_files,
              List *tracked_files, const List *cwd_files, Commit *&head_commit)
{
    return false;
}

bool reset(Commit *commit, Blob *current_branch, List *staged_files, List *tracked_files, const List *cwd_files,
           Commit *&head_commit)
{
    return false;
}

Blob *branch(const string &branch_name, List *branches, Commit *head_commit)
{
    return nullptr;
}

bool remove_branch(const string &branch_name, Blob *current_branch, List *branches)
{
    return false;
}

bool merge(const string &branch_name, Blob *&current_branch, List *branches, List *staged_files, List *tracked_files,
           const List *cwd_files, Commit *&head_commit)
{
    return false;
}
