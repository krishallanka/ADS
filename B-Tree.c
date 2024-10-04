#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ORDER 5
typedef struct BTreeNode {
    int keys[ORDER - 1];
    struct BTreeNode* children[ORDER];
    int numKeys;
    bool isLeaf;
} BTreeNode;
void deleteNode(BTreeNode* root, int key);
BTreeNode* createNode(bool isLeaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < ORDER; i++) {
        node->children[i] = NULL;
    }
    return node;
}
void traverse(BTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i < root->numKeys; i++) {
            if (!root->isLeaf) {
                traverse(root->children[i]);
            }
            printf("%d ", root->keys[i]);
        }
        if (!root->isLeaf) {
            traverse(root->children[root->numKeys]);
        }
    }
}
BTreeNode* search(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }
    if (i < root->numKeys && root->keys[i] == key) {
        return root;
    }
    if (root->isLeaf) {
        return NULL;
    }
    return search(root->children[i], key);
}
void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->isLeaf);
    z->numKeys = ORDER / 2 - 1;

    for (int j = 0; j < ORDER / 2 - 1; j++) {
        z->keys[j] = y->keys[j + ORDER / 2];
    }
    if (!y->isLeaf) {
        for (int j = 0; j < ORDER / 2; j++) {
            z->children[j] = y->children[j + ORDER / 2];
        }
    }
    y->numKeys = ORDER / 2 - 1;
    for (int j = parent->numKeys; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = z;
    for (int j = parent->numKeys - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = y->keys[ORDER / 2 - 1];
    parent->numKeys += 1;
}
void insertNonFull(BTreeNode* root, int key) {
    int i = root->numKeys - 1;
    if (root->isLeaf) {
        while (i >= 0 && root->keys[i] > key) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = key;
        root->numKeys += 1;
    } else {
        while (i >= 0 && root->keys[i] > key) {
            i--;
        }
        if (root->children[i + 1]->numKeys == ORDER - 1) {
            splitChild(root, i + 1, root->children[i + 1]);
            if (root->keys[i + 1] < key) {
                i++;
            }
        }
        insertNonFull(root->children[i + 1], key);
    }
}
void insert(BTreeNode** root, int key) {
    if ((*root)->numKeys == ORDER - 1) {
        BTreeNode* s = createNode(false);
        s->children[0] = *root;
        splitChild(s, 0, *root);
        int i = 0;
        if (s->keys[0] < key) {
            i++;
        }
        insertNonFull(s->children[i], key);
        *root = s;
    } else {
        insertNonFull(*root, key);
    }
}
void merge(BTreeNode* root, int idx) {
    BTreeNode* child = root->children[idx];
    BTreeNode* sibling = root->children[idx + 1];
    child->keys[ORDER / 2 - 1] = root->keys[idx];
    for (int i = 0; i < sibling->numKeys; i++) {
        child->keys[i + ORDER / 2] = sibling->keys[i];
    }
    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->numKeys; i++) {
            child->children[i + ORDER / 2] = sibling->children[i];
        }
    }
    for (int i = idx + 1; i < root->numKeys; i++) {
        root->keys[i - 1] = root->keys[i];
    }
    for (int i = idx + 2; i <= root->numKeys; i++) {
        root->children[i - 1] = root->children[i];
    }
    child->numKeys += sibling->numKeys + 1;
    root->numKeys--;
    free(sibling);
}
void fill(BTreeNode* root, int idx) {
    if (idx != 0 && root->children[idx - 1]->numKeys >= ORDER / 2) {
        BTreeNode* child = root->children[idx];
        BTreeNode* sibling = root->children[idx - 1];
        for (int i = child->numKeys - 1; i >= 0; i--) {
            child->keys[i + 1] = child->keys[i];
        }
        if (!child->isLeaf) {
            for (int i = child->numKeys; i >= 0; i--) {
                child->children[i + 1] = child->children[i];
            }
        }
        child->keys[0] = root->keys[idx - 1];
        if (!child->isLeaf) {
            child->children[0] = sibling->children[sibling->numKeys];
        }
        root->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];
        child->numKeys += 1;
        sibling->numKeys -= 1;
    } else if (idx != root->numKeys && root->children[idx + 1]->numKeys >= ORDER / 2) {
        BTreeNode* child = root->children[idx];
        BTreeNode* sibling = root->children[idx + 1];
        child->keys[child->numKeys] = root->keys[idx];
        if (!child->isLeaf) {
            child->children[child->numKeys + 1] = sibling->children[0];
        }
        root->keys[idx] = sibling->keys[0];
        for (int i = 1; i < sibling->numKeys; i++) {
            sibling->keys[i - 1] = sibling->keys[i];
        }
        if (!sibling->isLeaf) {
            for (int i = 1; i <= sibling->numKeys; i++) {
                sibling->children[i - 1] = sibling->children[i];
            }
        }
        child->numKeys += 1;
        sibling->numKeys -= 1;
    } else {
        if (idx != root->numKeys) {
            merge(root, idx);
        } else {
            merge(root, idx - 1);
        }
    }
}
void removeFromLeaf(BTreeNode* root, int idx) {
    for (int i = idx + 1; i < root->numKeys; i++) {
        root->keys[i - 1] = root->keys[i];
    }
    root->numKeys--;
}
void removeFromNonLeaf(BTreeNode* root, int idx) {
    int key = root->keys[idx];
    if (root->children[idx]->numKeys >= ORDER / 2) {
        BTreeNode* cur = root->children[idx];
        while (!cur->isLeaf) {
            cur = cur->children[cur->numKeys];
        }
        int pred = cur->keys[cur->numKeys - 1];
        root->keys[idx] = pred;
        deleteNode(root->children[idx], pred);
    } else if (root->children[idx + 1]->numKeys >= ORDER / 2) {
        BTreeNode* cur = root->children[idx + 1];
        while (!cur->isLeaf) {
            cur = cur->children[0];
        }
        int succ = cur->keys[0];
        root->keys[idx] = succ;
        deleteNode(root->children[idx + 1], succ);
    } else {
        merge(root, idx);
        deleteNode(root->children[idx], key);
    }
}
void deleteNode(BTreeNode* root, int key) {
    int idx = 0;
    while (idx < root->numKeys && root->keys[idx] < key) {
        idx++;
    }
    if (idx < root->numKeys && root->keys[idx] == key) {
        if (root->isLeaf) {
            removeFromLeaf(root, idx);
        } else {
            removeFromNonLeaf(root, idx);
        }
    } else {
        if (root->isLeaf) {
            return;
        }
        bool flag = (idx == root->numKeys);
        if (root->children[idx]->numKeys < ORDER / 2) {
            fill(root, idx);
        }
        if (flag && idx > root->numKeys) {
            deleteNode(root->children[idx - 1], key);
        } else {
            deleteNode(root->children[idx], key);
        }
    }
}
void userInteraction(BTreeNode** root) {
    int choice, key;
    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Search for an element\n");
        printf("4. Traverse the B-Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &key);
                insert(root, key);
                printf("Element inserted.\n");
                break;
            case 2:
                printf("Enter the element to delete: ");
                scanf("%d", &key);
                deleteNode(*root, key);
                printf("Element deleted.\n");
                break;
            case 3:
                printf("Enter the element to search: ");
                scanf("%d", &key);
                BTreeNode* result = search(*root, key);
                if (result != NULL) {
                    printf("Element %d found in the B-Tree.\n", key);
                } else {
                    printf("Element %d not found in the B-Tree.\n", key);
                }
                break;
            case 4:
                printf("B-Tree traversal:\n");
                traverse(*root);
                printf("\n");
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
int main() {
    BTreeNode* root = createNode(true);
    int elements[100];
    for (int i = 0; i < 100; i++) {
        elements[i] = rand() % 1000;
        insert(&root, elements[i]);
    }
    userInteraction(&root);
    return 0;
}
