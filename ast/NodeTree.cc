#include "NodeTree.h"

/* Node */

Node::~Node() {
	std::list<Node*>::iterator itr = this->children.begin();
	while (!this->children.empty()) {
		delete *itr++;
	}
}

void Node::addChild(Node* child) {
	this->children.push_back(child);
}


/* NodeTree */

NodeTree::NodeTree() {
	this->root = new Node(ROOT);
}

void NodeTree::addOperator(Operator oper, ValueType lhs_type, ValueType rhs_type, char const* lhs_val, char const* rhs_val) {
	OperatorNode* opNode = new OperatorNode(oper);
	opNode->addChild(new OperandNode(lhs_type, lhs_val));
	opNode->addChild(new OperandNode(rhs_type, rhs_val));
	this->root->addChild(opNode);
}

void NodeTree::addDecl(ValueType type, char const* name) {
	this->root->addChild(new DeclNode(type, name));
}

