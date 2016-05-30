#include "NodeTree.h"

/* Node */
Node::Node(NodeType nodeType, Node* left, Node* right) 
	: nodeType(nodeType)
{
	this->children.push_back(left);
	this->children.push_back(right);
}


void Node::addChild(Node* child) {
	this->children.push_back(child);
}


/* NodeTree */

NodeTree::NodeTree() {
	this->root = new Node(ROOT);
}

void NodeTree::addOperator(Operator oper, ValueType lhs_type, ValueType rhs_type, int lhs_val, int rhs_val) {
	OperatorNode* opNode = new OperatorNode(oper);
	opNode->addChild(new OperandNode(lhs_type, lhs_val));
	opNode->addChild(new OperandNode(rhs_type, rhs_val));
	this->root->addChild(opNode);
}

