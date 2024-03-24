
//============================================================================
// Name        :
// Author      : Bonnie Bell
// Version     :
// Copyright   : Your copyright notice
// Description : BAlanced AVL Tree
//============================================================================

#include <fstream>
#include <iostream>
#include <cmath>
#include <time.h>
#include <stack>
#include <queue>

#include "AVLTree.h"

using namespace std;


int main() {

	AVLTree* tree1Root = new AVLTree(50, nullptr);
	srand(time(NULL));
	uint32_t numNodes = 10;
	for (uint32_t i=1; i < numNodes; i++ ) {
		tree1Root = tree1Root->insert(( rand() % 10000));

		//Uncomment to help debug lost nodes
		if (tree1Root->countNodes() != i+1) {
			std::cout<<"Lost node "<<std::endl;
			return 1;
		}

		//uncomment to help debug unbalanced trees
		tree1Root->updateHeight();
		if ( ! tree1Root->isBalanced() ) {
			std::cout<<"Tree1Root balanced: FAILED at node insertion "<<i<<std::endl;
			return 1;
		}

	}

	if (tree1Root->countNodes() == numNodes) {
		std::cout<<"tree1Root lost Nodes: PASSED"<<std::endl;
	}
	else {
		std::cout<<"tree1Root lost Nodes: FAILED expected: 100 actual: "<<tree1Root->countNodes()<<std::endl;
	}

	tree1Root->updateHeight();
	float expectedHeight = log2(numNodes) * 1.5;
	if (tree1Root->getHeight() < expectedHeight) {
		std::cout<<"tree1Root height: PASSED"<<std::endl;
	}
	else {
		std::cout<<"tree1Root height: FAILED expected: <" <<expectedHeight<<" actual: "<<tree1Root->getHeight()<<std::endl;
	}

	if ( tree1Root->isBalanced()) {
		std::cout<<"Tree1Root is balanced: PASSED"<<std::endl;
	}
	else {
		std::cout<<"Tree1Root is balanced: FAILED"<<std::endl;
	}
}

