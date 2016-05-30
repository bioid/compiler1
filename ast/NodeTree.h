#ifndef __NODE_TREE_H
#define __NODE_TREE_H

#include <list>

enum NodeType {
	ROOT,
	STATEMENT,
	DECL,
	ASSIGN,
	NAME,
	VALUE,
	NUM,
	TYPE,
	OPER
};

enum ValueType {
	INTEGER
};

enum Operator {
	ADD,
	SUB,
	DIV,
	MUL
};

class Node {
public:
	NodeType 		nodeType;
	std::list<Node*> 	children;
	Node(NodeType nodeType, Node* left, Node* right); 
	Node(NodeType nodeType)
		:nodeType(nodeType)
	{}
	void addChild(Node* child);
};

class OperatorNode : public Node {
public:
	Operator	oper;
	OperatorNode(Operator oper)
		:Node(OPER), oper(oper)
	{}
	
};

class TypeNode : public Node {
public:
	ValueType	type;
	TypeNode(ValueType type)
		:Node(TYPE), type(type)
	{}
};

class ValueNode : public Node {
public:
	int val;				// only an int for now
	ValueNode(int value)
		:Node(VALUE), val(value) 
	{}
};

class OperandNode : public Node {
public:
	OperandNode(ValueType type, int value)	// only an int for now
		:Node(NUM)
	{
		this->addChild(new ValueNode(value));
		this->addChild(new TypeNode(type));
	}
};

class NodeTree {
public:
	Node* root;
	NodeTree();
	void addOperator(Operator oper, ValueType lhs_type, ValueType rhs_type, int lhs_val, int rhs_val);
 };

#endif
