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
        // stage_content(filename); // stupid!!!
        return true;
    }
    return false;
}

bool commit(const string &message, Blob *current_branch, List *staged_files, List *tracked_files, Commit *&head_commit)
{
    // 1. Failure check: If there are no files in the staging area, and no files staged for removal,
    if ((staged_files->head->next == staged_files->head)) // no files in the staging area
    {
        bool staged_for_removal = false;
        for (Blob *this_file = head_commit->tracked_files->head->next;
             this_file != head_commit->tracked_files->head; this_file = this_file->next)
        {
            if (list_find_name(tracked_files, this_file->name) == nullptr) // staged for removal,
            {
                staged_for_removal = true;
                break;
            }
        }
        if (staged_for_removal == false)
        {
            // print No changes added to the commit. and return false.
            cout << msg_no_changes_added << endl;
            return false;
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
    bool remove = false;
    // 1. If the file is tracked by the head commit of the repository, then remove it from the currently tracked files of the repository
    if (list_find_name(head_commit->tracked_files, filename) != nullptr) // If the file is tracked by the head commit of the repository
    {
        list_remove(tracked_files, filename); // remove it from the currently tracked files of the repository
        if (is_file_exist(filename))
        {
            restricted_delete(filename); // and remove the file from the current working directory (if it exists).
        }
        // The file is staged for removal.
        remove = true;
    }

    // 2. If the file was staged for addition, remove it from the tracked files of the repository and the staging area.
    if (list_find_name(tracked_files, filename) != nullptr) // not in head_commit->tracked_files, but in tracked_files
    {
        list_remove(tracked_files, filename); // remove it from the tracked files of the repository
        list_remove(staged_files, filename);  // remove it from the tracked files of the staging area
        remove = true;
    }

    // 3. If none of the above is satisfied, print No reason to remove the file. and return false. Otherwise, return true.
    if (!remove)
    {
        cout << msg_no_reason_remove << endl;
    }
    return remove;
}

void log(const Commit *head_commit)
{
    // Starting from the head commit of the repository,
    // display information for each commit backwards until the initial commit,
    // by following the parent commit (ignore second parents).
    cout << "===" << endl;
    commit_print(head_commit);
    cout << endl;
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
    for (Blob *this_staged_file = staged_files->head->next;
         this_staged_file != staged_files->head; this_staged_file = this_staged_file->next)
    {
        // if (is_file_exist(this_staged_file->name))
        // {
        //     if (this_staged_file->ref == get_sha1(this_staged_file->name))
        //     {
        cout << this_staged_file->name << endl;
        //     }
        // }
    }
    cout << endl;

    // Removed Files: Display the filenames of all files that are staged for removal.
    cout << status_removed_files_header << endl;
    for (Blob *this_committed_file = head_commit->tracked_files->head->next;
         this_committed_file != head_commit->tracked_files->head; this_committed_file = this_committed_file->next)
    {
        if (list_find_name(tracked_files, this_committed_file->name) == nullptr)
        {
            cout << this_committed_file->name << endl;
        }
    }

    cout << endl;

    // Modifications Not Staged For Commit: Display the filenames for the following files.
    cout << status_modifications_not_staged_header << endl;

    // Append (modified) for case 1 and 2. Append (deleted) for case 3 and 4.
    List *not_staged = list_new();

    // 1. Unstaged files that are tracked in the head commit of the repository,
    // but the content recorded in the commit is different with the content in the current working directory (CWD).
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
                    list_put(not_staged, this_committed_file->name, msg_status_modified);
                }
            }
        }
    }

    // 2. Files that were staged for addition, but the content recorded in the staging area is different with the content in CWD.
    for (Blob *this_staged_file = staged_files->head->next;
         this_staged_file != staged_files->head; this_staged_file = this_staged_file->next)
    {
        if (is_file_exist(this_staged_file->name))
        {
            if (this_staged_file->ref != get_sha1(this_staged_file->name))
            {
                list_put(not_staged, this_staged_file->name, msg_status_modified);
            }
        }
    }

    // 3. Files staged for addition but deleted in CWD.
    for (Blob *this_staged_file = staged_files->head->next;
         this_staged_file != staged_files->head; this_staged_file = this_staged_file->next)
    {
        if (!(is_file_exist(this_staged_file->name)))
        {
            list_put(not_staged, this_staged_file->name, msg_status_deleted);
        }
    }

    // 4. Files not staged for removal but tracked in the head commit of the repository and deleted in CWD.
    // tracked in the head commit
    for (Blob *this_committed_file = head_commit->tracked_files->head->next;
         this_committed_file != head_commit->tracked_files->head; this_committed_file = this_committed_file->next)
    {
        // Files not staged for removal
        if (list_find_name(tracked_files, this_committed_file->name) != nullptr)
        {
            // but the content recorded in the commit is different with the content in the current working directory (CWD).
            if (!(is_file_exist(this_committed_file->name)))
            {
                list_put(not_staged, this_committed_file->name, msg_status_deleted);
            }
        }
    }

    // print these files in the correct order

    for (Blob *this_not_staged_file = not_staged->head->next;
         this_not_staged_file != not_staged->head; this_not_staged_file = this_not_staged_file->next)
    {
        cout << this_not_staged_file->name << this_not_staged_file->ref << endl;
    }

    list_delete(not_staged); // release memory

    cout << endl;

    // Untracked Files: Files exist in CWD but not currently tracked by the repository.
    cout << status_untracked_files_header << endl;
    for (Blob *cwd_file = cwd_files->head->next; cwd_file != cwd_files->head; cwd_file = cwd_file->next)
    {
        if (list_find_name(tracked_files, cwd_file->name) == nullptr)
        {
            cout << cwd_file->name << endl;
        }
    }

    // Entries should be listed in ascending lexicographic order. The * of current branch does not count.
}

bool checkout(const string &filename, Commit *commit)
{
    Blob *committed_file = list_find_name(commit->tracked_files, filename);
    // 1. Failure check:
    //      If commit is nullptr, then the wrapper function cannot find the commit with the commit id.
    if (commit == nullptr)
    {
        //       Print No commit with that id exists. and return false.
        cout << msg_commit_does_not_exist << endl;
        return false;
    }

    //      If the file is not tracked by the commit,
    else if (committed_file == nullptr)
    {
        //       print File does not exist in that commit. and return false.
        cout << msg_file_does_not_exist << endl;
        return false;
    }

    // 2. Take the version of the file as it exists in the given commit
    //  and write the content to the current working directory. Overwrite any existing file.
    write_file(filename, committed_file->ref);

    // 3. No need to update the currently tracked files of the repository and the staging area. Return true.
    return true;
}

bool checkout(const string &branch_name, Blob *&current_branch, const List *branches, List *staged_files,
              List *tracked_files, const List *cwd_files, Commit *&head_commit)

{
    Blob *target_branch = list_find_name(branches, branch_name);
    // 1. Failure check:
    //      If the given branch does not exist, print A branch with that name does not exist. and return false.
    if (target_branch == nullptr)
    {
        cout << msg_branch_does_not_exist << endl;
        return false;
    }
    //      If the given branch is the current branch, print No need to checkout the current branch. and return false.
    if (branch_name == current_branch->name)
    {
        cout << msg_checkout_current << endl;
        return false;
    }

    //  If there exists untracked files in the current working directory that would be overwritten
    //  (see below for the files that would be overwritten), print There is an untracked file in the way;
    //  delete it, or add and commit it first. and return false.
    for (Blob *cwd_file = cwd_files->head->next; cwd_file != cwd_files->head; cwd_file = cwd_file->next)
    {
        string ref = get_sha1(cwd_file->name);
        Blob *tracked_file = list_find_name(tracked_files, cwd_file->name);
        if (tracked_file == nullptr) // untracked file
        {
            Blob *target_file = list_find_name(target_branch->commit->tracked_files, cwd_file->name);
            if ((target_file != nullptr) && (target_file->ref != ref))
            {
                cout << msg_untracked_file << endl;
                return false;
            }
        }
    }

    // 2. Take all files in the head commit of the branch and write the content of them to the current working directory.
    // Overwrite any existing files.

    for (Blob *this_file = target_branch->commit->tracked_files->head->next;
         this_file != target_branch->commit->tracked_files->head; this_file = this_file->next)
    {
        write_file(this_file->name, this_file->ref);
    }

    // 3. Any files that are tracked in the head commit of the repository but not the head commit of the given branch are deleted.
    for (Blob *this_file = head_commit->tracked_files->head->next;
         this_file != head_commit->tracked_files->head; this_file = this_file->next)
    // Any files that are tracked in the head commit of the repository
    {
        if (list_find_name(target_branch->commit->tracked_files, this_file->name) == nullptr)
        // but not the head commit of the given branch
        {
            restricted_delete(this_file->name); // delete
        }
    }

    // 4. Set the currently tracked files of the repository to those that are tracked by the head commit of the given branch.
    // Clear the staging area as well.
    // Set the currently tracked files of the repository to those that are tracked by the head commit of the given branch
    list_replace(tracked_files, target_branch->commit->tracked_files);

    list_clear(staged_files); // Clear the staging area as well.

    // 5. The given branch becomes the current branch. Also update the head commit of the repository.
    current_branch = target_branch;      // The given branch becomes the current branch
    head_commit = target_branch->commit; // update the head commit of the repository

    // 6. Return true.
    return true;
}

bool reset(Commit *commit, Blob *current_branch, List *staged_files, List *tracked_files, const List *cwd_files,
           Commit *&head_commit)
{
    // 1. Failure check:
    //      If commit is nullptr, then the wrapper cannot find the commit with the commit id.
    //          Print No commit with that id exists. and return false.
    if (commit == nullptr) // If commit is nullptr
    {
        cout << msg_commit_does_not_exist << endl; // Print No commit with that id exists.
        return false;                              // return false
    }

    //      If there exists untracked files in the current working directory that would be overwritten (see below for the files that would be overwritten),
    //          print There is an untracked file in the way; delete it, or add and commit it first. and return false.
    for (Blob *cwd_file = cwd_files->head->next; cwd_file != cwd_files->head; cwd_file = cwd_file->next)
    {
        string ref = get_sha1(cwd_file->name);
        if (list_find_name(tracked_files, cwd_file->name) == nullptr) // untracked file
        {
            Blob *target_file = list_find_name(commit->tracked_files, cwd_file->name);
            if ((target_file != nullptr) && (target_file->ref != ref))
            {
                cout << msg_untracked_file << endl;
                return false;
            }
        }
    }

    // 2. Take all files in the given commit and write the content of them to the current working directory.
    //      Overwrite any existing files.
    for (Blob *reset_file = commit->tracked_files->head->next;
         reset_file != commit->tracked_files->head; reset_file = reset_file->next)
    {
        write_file(reset_file->name, reset_file->ref);
    }

    // 3. Any files that are tracked in the head commit of the repository but not by the given commit are deleted.
    for (Blob *delete_file = head_commit->tracked_files->head->next;
         delete_file != head_commit->tracked_files->head; delete_file = delete_file->next)
    // files that are tracked in the head commit of the repository
    {
        if (list_find_name(commit->tracked_files, delete_file->name) == nullptr)
        // but not by the given commit
        {
            restricted_delete(delete_file->name);
        }
    }

    // 4. Updated October 8: Set the currently tracked files of the repository to
    //      those that are tracked by the given commit. Clear the staging area as well.
    list_replace(tracked_files, commit->tracked_files); // Set the currently tracked files of the repository to those that are tracked by the given commit
    list_clear(staged_files);                           // Clear the staging area

    // 5. The given commit becomes the head commit of the current branch. Also update the head commit of the repository.
    current_branch->commit = commit;
    head_commit = commit;

    // 6. Return true.
    return true;
}

Blob *branch(const string &branch_name, List *branches, Commit *head_commit)
{
    // Failure check: If a branch with the given name already exists,
    if (list_find_name(branches, branch_name) != nullptr)
    {
        //      print A branch with that name already exists. and return nullptr.
        cout << msg_branch_exists << endl;
        return nullptr;
    }

    // The head commit of the repository becomes the head commit of the new branch.
    Blob *new_branch = list_put(branches, branch_name, head_commit);

    // Return a pointer to the new branch.
    return new_branch;
}

bool remove_branch(const string &branch_name, Blob *current_branch, List *branches)
{
    // 1. Failure check:
    //      If the given branch does not exist, print A branch with that name does not exist. and return false.
    if (list_find_name(branches, branch_name) == nullptr)
    {
        cout << msg_branch_does_not_exist << endl;
        return false;
    }
    //      If trying to remove the current branch, print Cannot remove the current branch. and return false.
    else if (branch_name == current_branch->name)
    {
        cout << msg_remove_current << endl;
        return false;
    }

    // 2. Delete the branch from the repository. Do not delete any commits.
    list_remove(branches, branch_name);
    return true;
}

bool merge(const string &branch_name, Blob *&current_branch, List *branches, List *staged_files, List *tracked_files,
           const List *cwd_files, Commit *&head_commit)
{
    cerr << 1 << endl;
    Blob *given_branch = list_find_name(branches, branch_name);
    // 1. Failure check:
    //      If the given branch does not exist, print A branch with that name does not exist., and return false.
    if (given_branch == nullptr) // If the given branch does not exist
    {
        cout << msg_branch_does_not_exist << endl; // print A branch with that name does not exist
        return false;                              // return false
    }
    //      If trying to merge the current branch, print Cannot merge a branch with itself. and return false.
    if (branch_name == current_branch->name) // If trying to merge the current branch
    {
        cout << msg_merge_current << endl; // print Cannot merge a branch with itself
        return false;                      // return false
    }
    //      If there exists uncommitted changes, print You have uncommitted changes. and return false.
    bool uncommitted_changes = false;
    if (staged_files->head->next != staged_files->head) // exist files in staged area
    // staged for addition
    {
        uncommitted_changes = true;
    }
    for (Blob *this_committed_file = head_commit->tracked_files->head->next;
         this_committed_file != head_commit->tracked_files->head; this_committed_file = this_committed_file->next)
    {
        if (list_find_name(tracked_files, this_committed_file->name) == nullptr)
        // staged for removal
        {
            uncommitted_changes = true;
        }
    }
    if (uncommitted_changes)
    {
        cout << msg_exists_uncommitted_changes << endl;
        return false;
    }
    cerr << 2 << endl;

    /* 2. Otherwise, proceed to compute the split point of the current branch and the given branch.
     *  The split point is a latest common ancestor of the head commit of the current branch and the head commit of the given branch:
     *initial commit --- c1 --- c2 --- c3 --- c4 (head of master)
     *                           \
     *                             --- n1 --- n2 (head of new)*/
    Commit *split_point = get_lca(current_branch->commit, given_branch->commit);

    /* 3. If the split point is the head commit of the given branch, then all changes in the given branch exist in the current branch
     *      (the current branch is ahead of the given branch). So there is nothing to be done in the current branch.
     *      Simply print Given branch is an ancestor of the current branch. and return true.*/
    if (split_point == given_branch->commit) // If the split point is the head commit of the given branch
    {
        cout << msg_given_is_ancestor_of_current << endl; // Simply print Given branch is an ancestor of the current branch.
        return true;                                      // and return true.
    }
    cerr << 3 << endl;
    /* 4. If the split point is the head commit of the current branch, then all changes in the current branch exist in the given branch
     *      (the given branch is ahead of the current branch). Simply set the state of the repository to the head commit of the given branch (using one command above).
     *      If it succeeded, print Current branch fast-forwarded. and return true. If it failed, return false.*/
    if (split_point == current_branch->commit) // If the split point is the head commit of the current branch
    {
        bool merge_succeeded = false;
        merge_succeeded = reset(given_branch->commit, current_branch, staged_files, tracked_files, cwd_files, head_commit);
        if (merge_succeeded)
        {
            cout << msg_fast_forward << endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    cerr << 4 << endl;
    /* 5. Otherwise, the split point is neither the head commit of the current branch and the head commit of the given branch.
     *      Their history has diverged, like the above example. We need to incorporate the latest changes from both branches.*/

    /* 6. Failure check: Traverse cwd_files,if there exists a file that is not tracked in the head commit of the current branch
     *      but tracked in the head commit of the given branch, print There is an untracked file in the way; delete it, or add and commit it first. and return false.*/
    for (Blob *cwd_file = cwd_files->head->next; cwd_file != cwd_files->head; cwd_file = cwd_file->next) // Traverse cwd_files
    {
        if ((list_find_name(current_branch->commit->tracked_files, cwd_file->name) == nullptr) && // not tracked in the head commit of the current branch
            (list_find_name(given_branch->commit->tracked_files, cwd_file->name) != nullptr))     // but tracked in the head commit of the given branch
        {
            cout << msg_untracked_file << endl; // print There is an untracked file in the way; delete it, or add and commit it first
            return false;                       // return false
        }
    }
    cerr << 5 << endl;
    /* 7. Otherwise, proceed to merge the two branches with rules below. A general idea is to incorporate the latest changes from both branches.*/

    List *conflict_files = list_new();
    for (Blob *lca_file = split_point->tracked_files->head->next; lca_file != split_point->tracked_files->head; lca_file = lca_file->next)
    {
        Blob *given_file = list_find_name(given_branch->commit->tracked_files, lca_file->name);
        Blob *current_file = list_find_name(current_branch->commit->tracked_files, lca_file->name);

        /*      1. Any files that have been modified in the given branch but not modified in the current branch
         *         since the split point should be changed to their versions in the given branch.
         *          · Checkout the files and stage the files for addition.
         *          · In addition, you need to call stage_content(filename) explicitly to modify the index in the .gitlite directory.*/
        if ((given_file != nullptr) && (current_file != nullptr))
        {
            if ((lca_file->ref != given_file->ref) && // have been modified in the given branch
                (lca_file->ref == current_file->ref)) // but not modified in the current branch
            {
                checkout(lca_file->name, given_branch->commit);                // Checkout the file
                add(lca_file->name, staged_files, tracked_files, head_commit); // stage the file for addition
                stage_content(lca_file->name);                                 // modify the index in the .gitlite directory
            }

            /*      2. Any files that have been modified in the current branch but not modified in the given branch since the split point should remain unchanged.*/
            else if ((lca_file->ref != current_file->ref) && // have been modified in the current branch
                     (lca_file->ref == given_file->ref))     // but not modified in the given branch
            {
                /*remain unchanged*/
            }

            /*      3. Any files that have been modified in both the current branch and the given branch in the same way
             *         (both modified with same content or both removed), should remain unchanged.*/
            else if ((lca_file->ref != current_file->ref) && // have been modified in the current branch
                     (lca_file->ref != given_file->ref))     // have been modified in the given branch
            {
                if (current_file->ref == given_file->ref) // both modified with same content
                {
                    /*remain unchanged*/
                }
                else
                {
                    /* in conflict
                     * It is changed in both branches with different content.*/
                    list_put(conflict_files, lca_file->name, given_file->ref);
                }
            }
        }
        else if ((given_file == nullptr) && (current_file == nullptr)) // both removed
        {
            /*remain unchanged*/
        }
        else if ((given_file != nullptr) && (current_file == nullptr) && // It is changed in one branch but deleted in another branch
                 (given_file->ref != lca_file->ref))
        {
            list_put(conflict_files, lca_file->name, given_file->ref);
        }
        else if ((current_file != nullptr) && (given_file == nullptr) && // It is changed in one branch but deleted in another branch
                 (current_file->ref != lca_file->ref))
        {
            list_put(conflict_files, lca_file->name, string());
        }

        // 6. Any files present at the split point, unmodified in the current branch, and absent in the given branch should be staged for removal.
        else if ((current_file != nullptr) && (given_file == nullptr) && // absent in the given branch
                 (current_file->ref == lca_file->ref))                   // present at the split point, unmodified in the current branch
        {
            remove(current_file->name, staged_files, tracked_files, head_commit); // staged for removal
        }
        // 7. Any files present at the split point, unmodified in the given branch, and absent in the current branch should remain absent
        else if ((current_file == nullptr) && (given_file != nullptr) && // absent in the current branch
                 (given_file->ref == lca_file->ref))                     // unmodified in the given branch
        {
            /*remain absent*/
        }
    }
    cerr << 6 << endl;
    /*      4. Any files that were not present at the split point and are present only in the current branch should remained unchanged.*/
    for (Blob *current_file = current_branch->commit->tracked_files->head->next;
         current_file != current_branch->commit->tracked_files->head; current_file = current_file->next)
    {
        Blob *lca_file = list_find_name(split_point->tracked_files, current_file->name);
        Blob *given_file = list_find_name(given_branch->commit->tracked_files, current_file->name);
        if (lca_file == nullptr) // not present at the split point
        {
            if ((given_file == nullptr) && (current_file != nullptr)) // present only in the current branch
            {
                /*remained unchanged*/
            }
            else if ((given_file != nullptr) && (current_file != nullptr))
            {
                if (given_file->ref != current_file->ref) // It was absent at the split point but present in both branches with different content.
                {
                    list_put(conflict_files, given_file->name, given_file->ref);
                }
            }
        }
    }
    cerr << 7 << endl;
    /*      5. Any files that were not present at the split point and are present only in the given branch should be added with their versions in the given branch.
     *          · Checkout the files and stage the files for addition.
     *          · In addition, you need to call stage_content(filename) explicitly to modify the index in the .gitlite directory.*/
    for (Blob *given_file = given_branch->commit->tracked_files->head->next;
         given_file != given_branch->commit->tracked_files->head; given_file = given_file->next)
    {
        cerr << 11 << endl;
        Blob *lca_file = list_find_name(split_point->tracked_files, given_file->name);
        cerr << 12 << endl;
        Blob *current_file = list_find_name(current_branch->commit->tracked_files, given_file->name);
        cerr << 13 << endl;
        if (lca_file == nullptr) // not present at the split point
        {
            cerr << 16 << endl;
            if ((current_file == nullptr) && (given_file != nullptr)) // present only in the given branch
            {
                cerr << 14 << endl;
                checkout(given_file->name, given_branch->commit); // Checkout the file
                cerr << 15 << endl;
                add(given_file->name, staged_files, tracked_files, head_commit); // stage the file for addition
                stage_content(given_file->name);                                 // modify the index in the .gitlite directory
            }
            // else if ((given_file != nullptr) && (current_file != nullptr))
            // {
            //     if (given_file->ref != current_file->ref) // It was absent at the split point but present in both branches with different content.
            //     {
            //         list_put(conflict_files, given_file->name, "");
            //     }
            // }
        }
    }
    cerr << 8 << endl;
    /*      6. Any files present at the split point, unmodified in the current branch, and absent in the given branch should be staged for removal.*/

    /*      7. Any files present at the split point, unmodified in the given branch, and absent in the current branch should remain absent.*/

    /*      8. Any files modified in different ways in the current branch and the given branch are in conflict.
     *          · A file is modified in different ways if:
     *              a. It is changed in both branches with different content.
     *              b. It is changed in one branch but deleted in another branch.
     *              c. It was absent at the split point but present in both branches with different content.
     *          · Replace the content of these files in the current working directory by the conflict resolution marker: (See add_conflict_marker(filename, ref) in Utils.cpp)
     *
     *              <<<<<<< HEAD
     *              contents of the file in the current branch
     *              =======
     *              contents of the file in the given branch
     *              >>>>>>>
     *
     *          · Stage these files for addition.
     *          · In addition, you need to call stage_content(filename) explicitly to modify the index in the .gitlite directory.*/
    for (Blob *conflict_file = conflict_files->head->next; conflict_file != conflict_files->head; conflict_file = conflict_file->next)
    {
        add_conflict_marker(conflict_file->name, conflict_file->ref);       // conflict resolution marker
        add(conflict_file->name, staged_files, tracked_files, head_commit); // Stage these files for addition
        stage_content(conflict_file->name);                                 // modify the index in the .gitlite directory
    }
    cerr << 9 << endl;
    /* 8. After processing the files, create a merge commit with message Merged [given branch name] into [current branch name].
     *      · The first parent of the merge commit is the head commit of the current branch.
     *      · The second parent of the merge commit is the head commit of the given branch.*/
    commit(get_merge_commit_message(given_branch, current_branch), current_branch, staged_files, tracked_files, head_commit);
    head_commit->second_parent = given_branch->commit; // second parent

    // 9. If a conflict was ever encountered, print Encountered a merge conflict. (once is enough)
    if (conflict_files->head->next != conflict_files->head)
    {
        cout << msg_encountered_merge_conflict << endl;
    }

    // 10. Return true.
    // 11. If a commit error occurred, just print the error, ignore it and still return true.

    list_delete(conflict_files);

    return true;
}
