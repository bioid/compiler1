#include <cstdio>
#include "NodeTree.h"

using namespace std;

void listChildren(Node* node);
void traverse(NodeTree* nt);

int main() 
{
	NodeTree nt;
	nt.addOperator(ADD, INTEGER, INTEGER, 1, 2);
	
	listChildren(nt.root);
	return 0; 
}

void listChildren(Node* node)
{	
	list<Node*>::iterator itr = node->children.begin();
	printf("Node type %d has %d children\n", node->nodeType, (int)node->children.size());
	while (itr != node->children.end()) 
	{
		listChildren(*itr);
		itr++;
	}
}


