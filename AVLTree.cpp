
//============================================================================
// Name        : AVLTree
// Author      : Bonnie Bell
// Version     :
// Copyright   : Your copyright notice
// Description : AVL Tree functions
//============================================================================

#include "AVLTree.h"

#include <iostream>

using namespace std;
//************** already implemented helper functions
AVLTree::AVLTree(int t_data, AVLTree* t_parent, AVLTree* t_left, AVLTree* t_right) {
	data = t_data;
	height = 0;
	parent = t_parent;
	left = t_left;
	right = t_right;
}

bool AVLTree::isLeaf() {
	return ((left == nullptr) and (right == nullptr));
}

uint32_t AVLTree::getHeight() {
	return height;
}

//******************************************************

int AVLTree::getBalance() {
    int left_height = (left != nullptr) ? left->getHeight() : -1;
    int right_height = (right != nullptr) ? right->getHeight() : -1;
    return left_height - right_height;
}

AVLTree* AVLTree::rotateRight() {
    AVLTree* new_root = left;
    left = new_root->right;
    if (new_root->right != nullptr) {
        new_root->right->parent = this;
    }
    new_root->right = this;
    new_root->parent = parent;
    parent = new_root;
    if (new_root->parent != nullptr) {
        if (new_root->parent->left == this) {
            new_root->parent->left = new_root;
        } else {
            new_root->parent->right = new_root;
        }
    }
    updateHeight();
    new_root->updateHeight();
    return new_root;
}

AVLTree* AVLTree::rotateLeft() {
    AVLTree* new_root = right;
    right = new_root->left;
    if (new_root->left != nullptr) {
        new_root->left->parent = this;
    }
    new_root->left = this;
    new_root->parent = parent;
    parent = new_root;
    if (new_root->parent != nullptr) {
        if (new_root->parent->left == this) {
            new_root->parent->left = new_root;
        } else {
            new_root->parent->right = new_root;
        }
    }
    updateHeight();
    new_root->updateHeight();
    return new_root;
}

AVLTree* AVLTree::rebalance() {
    updateHeight();
    int balance = getBalance();
    if (balance > 1) {
        if (left->getBalance() < 0) {
            left = left->rotateLeft();
        }
        return rotateRight();
    }
    if (balance < -1) {
        if (right->getBalance() > 0) {
            right = right->rotateRight();
        }
        return rotateLeft();
    }
    return this;
}

AVLTree* AVLTree::insert(int new_data) {
    if (new_data < data) {
        if (left == nullptr) {
            left = new AVLTree(new_data, this);
        } else {
            left = left->insert(new_data);
        }
    } else {
        if (right == nullptr) {
            right = new AVLTree(new_data, this);
        } else {
            right = right->insert(new_data);
        }
    }
    return rebalance();
}


//***************************
//Do not edit code below here
uint32_t AVLTree::countNodes() {
	if (isLeaf()) {
		return 1;
	}
	if (left != nullptr) {
		if (right != nullptr) {
			return 1 + left->countNodes() + right->countNodes();
		}
		return 1+ left->countNodes();
	}
	return 1 + right->countNodes();
}

void AVLTree::updateHeight() {
	if (isLeaf()) {
		height = 0;
		return;
	}
	if (left != nullptr) {
		left->updateHeight();
		if (right != nullptr) {
			right->updateHeight();
			height = (1 + max(left->getHeight(), right->getHeight()));
			return;
		}
		height = 1 + left->getHeight();
		return;
	}
	right->updateHeight();
	height = 1 + right->getHeight();
	return;
}

bool AVLTree::isBalanced() {
	if ( isLeaf() ) {
		return true;
	}
	updateHeight();
	if (left == nullptr) {
		return ( right->getHeight() < 1 );
	}
	if (right == nullptr) {
		return ( left->getHeight() < 1 );
	}
	return ( left->isBalanced() and right->isBalanced() and (getBalance() < 2) and (getBalance() > -2) );
}
