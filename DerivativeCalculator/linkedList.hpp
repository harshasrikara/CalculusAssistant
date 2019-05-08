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
#include <vector>

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
    std::string getExpression() const;
    Node * getNextNode() const;
    
    //setters
    void setOuterCoefficient(int);
    void setInnerCoefficient(int);
    void setExponent(int);
    void setNumerator(int);
    void setDenominator(int);
    void setTrigIdentifier(std::string);
    void setNextNode(Node*);
    int check(std::string row,std::string wordToBeFound);
    
    //print
    void print();
    std::ostream &print(std::ostream &out) const;
    void debug();
    std::ostream &debug(std::ostream &out) const;
    
    //functions
    void derive();
    void setExpression();
};

std::ostream &operator<<(std::ostream &out, const Node &node);

class LinkedList
{
private:
    Node * head;
    Node blank; //this node that contains all values initialized to 0 will be returned with [] if out of bounds.
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
    
    //count/traverse/helper functions
    int calculateCount();
    void traverse(void (*function)(Node *));
    bool isEmpty();
    void print();
    void print() const;
    void sort();
    void reverse();
    std::ostream &print(std::ostream &out);
    std::ostream &print(std::ostream &out) const;
    int check(std::string row,std::string wordToBeFound);
    
    Node& operator[](int i);
};

std::ostream &operator<<(std::ostream &out, const LinkedList &link);

#endif /* linkedList_hpp */
