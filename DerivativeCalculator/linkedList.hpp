//
//  linkedList.hpp
//  DerivativeCalculator
//
//  Created by Harsha Srikara on 4/30/19.
//  Copyright © 2019 Harsha Srikara. All rights reserved.
//

#ifndef linkedList_hpp
#define linkedList_hpp

#include <string>
#include <iostream>

class Node
{
private:
    //variables
    int outerCoefficient;
    int innerCoefficient; //only for trig functions
    int exponent;
    int numerator;
    int denominator;
    std::string trigIdentifier; //only sin/cos/tan
    std::string outputExpr;
    Node * nextNode;
    
public:
    //constructors
    Node(); //default
    Node(int outer, int inner, int exp, std::string trig); //pointer = nullptr
    Node(int outer, int inner, int exp, std::string trig, Node * pNext); //regular
    Node(int num, int den, int inner, int exp, std::string trig); //pointer = nullptr
    Node(int num, int den, int inner, int exp, std::string trig, Node * pNext); //bonus
    
    //getters
    int getOuterCoefficient() const;
    int getInnerCoefficient() const;
    int getExponent() const;
    int getNumerator() const;
    int getDenominator() const;
    std::string getTrigIdentifier() const;
    Node * getNextNode() const;
    
    //setters
    void setOuterCoefficient(int);
    void setInnerCoefficient(int);
    void setExponent(int);
    void setNumerator(int);
    void setDenominator(int);
    void setTrigIdentifier(std::string);
    void setNextNode(Node*);
    
    //functions
    void derive();
};

std::ostream &operator<<(std::ostream &out, const Node &node);

class LinkedList
{
private:
    Node * head;
    int expressionCount;
    
public:
    //constructor
    LinkedList();
    LinkedList(Node * pHead);
    
    //destructor
    ~LinkedList();
    
    //getters
    Node *getHead() const;
    int getCount() const;
    
    //setters
    void setHead(Node *pNode);
    
    //delete
    void clearList();
    void pop();
    
    //add
    void addNode(Node *pNode);
    void addNode(std::string expr);
    
    //count/traverse
    int calculateCount();
    void traverse(void (*function)(Node *));
    bool isEmpty();
};

#endif /* linkedList_hpp */
