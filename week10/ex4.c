#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define FNAME_LEN 255

// Entry for my linked list of inodes
typedef struct entry {
    ino_t inode_num;
    size_t count;
    struct entry *next;
    char **filenames;
} entry;

void add_filename(entry *entry, char *filename) {
    ++entry->count;
    entry->filenames = (char **)realloc(entry->filenames, sizeof(char *) * entry->count);
    entry->filenames[entry->count - 1] = (char *)malloc(sizeof(char) * (FNAME_LEN + 1));
    strcpy(entry->filenames[entry->count - 1], filename);
}

entry *create_entry(ino_t inode_num, char *filename) {
    entry *res = (entry *)malloc(sizeof(entry));
    res->inode_num = inode_num;
    res->count = 0;
    res->next = NULL;
    res->filenames = NULL;
    add_filename(res, filename);
    return res;
}

void linked_list_add_entry(entry *root, entry *new) {
    if (root->next == NULL) {
        root->next = new;
    } else {
        linked_list_add_entry(root->next, new);
    }
}

entry *linked_list_find(entry *root, ino_t inode_num) {
    if (root->inode_num == inode_num) {
        return root;
    } else if (root->next != NULL) {
        return linked_list_find(root->next, inode_num);
    } else {
        return NULL;
    }
}

void free_linked_list(entry **root) {
    if ((*root)->next == NULL) {
        for (int i = 0; i < (*root)->count; ++i) {
            free((*root)->filenames[i]);
        }
        free((*root)->filenames);
        free(*root);
    } else {
        free_linked_list(&((*root)->next));
        free(*root);
    }
}

int main(int argc, char *argv[]) {
    char dirname[] = "tmp";
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        return EXIT_FAILURE;
    }

    struct dirent *dent;

    entry *root = NULL;

    while ((dent = readdir(dir)) != NULL) {
        if (root == NULL) {
            root = create_entry(dent->d_ino, dent->d_name);
        } else {
            entry *entry = linked_list_find(root, dent->d_ino);
            if (entry != NULL) {
                add_filename(entry, dent->d_name);
            }
        }
    }

    entry *cur = root;
    while (cur != NULL) {
        if (cur->count > 1) {
            printf("Inode number: %lld, filenames: ", cur->inode_num);
            for (int i = 0; i < cur->count; ++i) {
                printf("%s ", cur->filenames[i]);
            }
            printf("\n");
        }
        cur = cur->next;
    }

    free_linked_list(&root);
    closedir(dir);
    return EXIT_SUCCESS;
}
