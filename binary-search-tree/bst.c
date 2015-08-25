#include "stddef.h"
#include "stdlib.h"
#include "bst.h"

typedef struct bst_T {
    uint32_t key;
    void *val;
    bst *parent;
    bst *left;
    bst *right;
} bst;

static bst *bst_create(uint32_t key, void *val) 
{
    bst *t;
    t = calloc(1, sizeof(bst));
    t->key = key;
    t->val = val;
    return t;
}

static bst* bst_find(bst *t, uint32_t key)
{
    while (t) {
        if (key == t->key)
            break;
        else if (key < t->key)
            t = t->left;
        else
            t = t->right;
    }

    return t;
}

static  bst* bst_min_tree(bst *t)
{
    if (!t)
        return NULL;

    while (t->left) 
        t = t->left;

    return t;
}

void bst_insert(bst **root, uint32_t key, void *val)
{
    bst *leaf;
    bst *t; 

    leaf = bst_create(key, val);

    t = *root;

    /*
     * Search for the parent node of the node that we will insert. To do this we
     * walk through the tree. t holds our current position in the tree. When
     * t is NULL we have found the leaf we want to store our new node at and
     * its parent. 
     */
    while (t) {
        leaf->parent = t; 
        if (key < t->key)
            t = t->left;
        else
            t = t->right;
    }

    if (!leaf->parent)
        *root = leaf;
    else if (key < leaf->parent->key) 
        leaf->parent->left = leaf;
    else
        leaf->parent->right = leaf;
}

void *bst_remove(bst **root, uint32_t key)
{
    void *ret;
    /* node to delete */
    bst *rm;
    /* node to replace rm in rm's parent */
    bst *rp;

    if (!root)
        return NULL;
    
    if (!*root)
       return NULL; 
    
    rm = bst_find(*root, key); 

    /* the key was not in the tree */
    if (!rm)
        return NULL;

    if (!rm->left && !rm->right) {
        rp = NULL;
    } else if (rm->left && !rm->right) {
        rp = rm->left;
    } else if (rm->right && !rm->left) {
        rp = rm->right;
    } else {
        rp = bst_min_tree(rm->right);
        /* make sure we're not creating a loop in out tree */
        if (rp != rm->right)
            rp->right = rm->right;
        rp->left = rm->left;
    }

    if (rm->right)
        rm->right->parent = rp;
    if (rm->left)
        rm->left->parent = rp;

    if (rp) {
        rp->parent = rm->parent;
    }
    
    if (rm->parent) {
        if (rm->parent->key > rm->key)
            rm->parent->left = rp;
        else
            rm->parent->right = rp;
    }

    /* Deleting the root node. Update the callers pointer */
    if (!rm->parent) {
        *root = rp;
    } 
        
    ret = rm->val;
    free(rm); 
    rm = NULL;

    return ret;
}

void *bst_lookup(bst *t, uint32_t key)
{
    void *ret = NULL;

    t = bst_find(t, key);

    if (t)
        ret = t->val;

    return ret;
}

void *bst_min(bst *t)
{
    if (!t)
        return NULL;

    while (t->left) 
        t = t->left;

    return t->val;
}

void *bst_max(bst *t)
{
    if (!t)
        return NULL;

    while (t->right)
        t = t->right;

    return t->val;
}

void bst_process(bst *t, proc_func f)
{
}
