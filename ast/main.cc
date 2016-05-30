#include <cstdio>
#include "NodeTree.h"

using namespace std;

void listChildren(Node* node);

int main() 
{
	NodeTree nt;
	nt.addOperator(ADD, INTEGER, INTEGER, "1", "2");
	
	listChildren(nt.root);
	return 0; 
}

void listChildren(Node* node)
{
	printf("Node type %d has %d children\n", node->nodeType, (int)node->children.size());
	
	list<Node*>::iterator itr = node->children.begin();
	while (itr != node->children.end()) 
	{
		listChildren(*itr++);
	}
}


