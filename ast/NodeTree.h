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
	OPERAND,
	TYPE,
	OPERATOR
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
	Node(NodeType nodeType)
		:nodeType(nodeType)
	{}
	~Node();
	void clear();
	void addChild(Node* child);
};

class OperatorNode : public Node {
public:
	Operator	oper;
	OperatorNode(Operator oper)
		:Node(OPERATOR), oper(oper)
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
	char const* val;				
	ValueNode(char const* value)
		:Node(VALUE), val(value) 
	{}
};

class OperandNode : public Node {
public:
	OperandNode(ValueType type, char const* value)	
		:Node(OPERAND)
	{
		this->addChild(new ValueNode(value));
		this->addChild(new TypeNode(type));
	}
};

class NameNode : public Node {
public:
	char const* name;				
	NameNode(char const* name)
		:Node(NAME), name(name) 
	{}
};

class DeclNode : public Node {
public:
	DeclNode(ValueType type, char const* name)	
		:Node(DECL)
	{
		this->addChild(new NameNode(name));
		this->addChild(new TypeNode(type));
	}
};


class NodeTree {
public:
	Node* root;
	NodeTree();
	void addOperator(Operator oper, ValueType lhs_type, ValueType rhs_type, char const* lhs_val, char const* rhs_val);
	void addDecl(ValueType type, char const* name);
 };

#endif
