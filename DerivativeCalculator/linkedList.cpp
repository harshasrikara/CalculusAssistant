//
//  linkedList.cpp
//  DerivativeCalculator
//
//  Created by Harsha Srikara on 4/30/19.
//  Copyright © 2019 Harsha Srikara. All rights reserved.
//

#include "linkedList.hpp"

//NODE CLASS - UNTIL LINE 144
Node::Node()
{
    outerCoefficient = 0;
    innerCoefficient = 0;
    exponent = 0;
    numerator = 0;
    denominator = 0;
    trigIdentifier = "";
    nextNode = nullptr;
}
Node::Node(int outer, int inner, int exp, std::string trig)
{
    outerCoefficient = outer;
    innerCoefficient = inner;
    exponent = exp;
    trigIdentifier = trig;
    nextNode = nullptr;
    numerator = 0;
    denominator = 0;
}
Node::Node(int outer, int inner, int exp, std::string trig, Node * pNext)
{
    outerCoefficient = outer;
    innerCoefficient = inner;
    exponent = exp;
    trigIdentifier = trig;
    nextNode = pNext;
    numerator = 0;
    denominator = 0;
}
Node::Node(int num, int den, int inner, int exp, std::string trig)
{
    numerator = num;
    denominator = den;
    outerCoefficient = 0;
    innerCoefficient = inner;
    exponent = exp;
    trigIdentifier = trig;
    nextNode = nullptr;
}
Node::Node(int num, int den, int inner, int exp, std::string trig, Node * pNext)
{
    numerator = num;
    denominator = den;
    outerCoefficient = 0;
    innerCoefficient = inner;
    exponent = exp;
    trigIdentifier = trig;
    nextNode = pNext;
}

//getters
int Node::getOuterCoefficient() const
{
    return outerCoefficient;
}
int Node::getInnerCoefficient() const
{
    return innerCoefficient;
}
int Node::getExponent() const
{
    return exponent;
}
int Node::getNumerator() const
{
    return numerator;
}
int Node::getDenominator() const
{
    return denominator;
}
std::string Node::getTrigIdentifier() const
{
    return trigIdentifier;
}
Node* Node::getNextNode() const
{
    return nextNode;
}

//setters
void Node::setOuterCoefficient(int outer)
{
    outerCoefficient = outer;
}
void Node::setInnerCoefficient(int inner)
{
    innerCoefficient = inner;
}
void Node::setExponent(int exp)
{
    exponent = exp;
}
void Node::setNumerator(int num)
{
    numerator = num;
}
void Node::setDenominator(int den)
{
    denominator = den;
}
void Node::setTrigIdentifier(std::string trig)
{
    trigIdentifier = trig;
}
void Node::setNextNode(Node* pNext)
{
    nextNode = pNext;
}

//functions
void Node::derive()
{
    //figure out eventually
}

//ostream operator overload
std::ostream &operator<<(std::ostream &out, const Node &node)
{
    out << "Expression Term\n"
    << "Outer Coefficient -> " << node.getOuterCoefficient()
    << "\nInner Coefficient -> " << node.getInnerCoefficient()
    << "\nNumerator -> " << node.getNumerator()
    << "\nDenominator -> " << node.getDenominator()
    << "\nTrig Identifier -> " << node.getTrigIdentifier()
    << "\nExponent -> " << node.getExponent()
    << "\nNextNode pointer -> " << node.getNextNode() << std::endl;
    return out;
}


//LINKED LIST CLASS
//constructors
LinkedList::LinkedList()
{
    head = nullptr;
    expressionCount = 0;
}
//assignment constructor/copy constructor
LinkedList::LinkedList(Node * pHead)
{
    clearList();
    head = pHead;
    expressionCount = getCount();
}
LinkedList::~LinkedList()
{
    clearList();
}

//getters
Node* LinkedList::getHead() const
{
    return head;
}
int LinkedList::getCount() const
{
    return expressionCount;
}

//setter
void LinkedList::setHead(Node *pNode)
{
    clearList();
    head = pNode;
}

//delete
void LinkedList::clearList()
{
    while(head!=nullptr)
    {
        pop();
    }
    expressionCount = 0;
}
void LinkedList::pop()
{
    Node * temp = head;
    head = head->getNextNode();
    delete temp;
    temp = nullptr;
}

//add
void LinkedList::addNode(Node *pNode)
{
    if(isEmpty())
    {
        head = pNode;
        head->setNextNode(nullptr);
        expressionCount++;
        return;
    }
    else
    {
        pNode->setNextNode(head);
        head = pNode;
        expressionCount++;
        return;
    }
}
void LinkedList::addNode(std::string expr)
{
    int outer = 1;
    int inner = 1;
    int exp = 1;
    std::string trigId = "";
}

//count/traverse
int LinkedList::calculateCount()
{
    int counter = 0;
    Node * ptr = head;
    while(ptr!=nullptr)
    {
        ptr = ptr->getNextNode();
        counter++;
    }
    return counter;
}
void LinkedList::traverse(void (*function)(Node *))
{
    Node * ptr = head;
    while(ptr!=nullptr)
    {
        function(ptr);
        ptr = ptr->getNextNode();
    }
}
bool LinkedList::isEmpty()
{
    if(expressionCount==0)
    {
        return true;
    }
    return false;
}
