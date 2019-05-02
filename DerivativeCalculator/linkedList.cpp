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

void Node::debug()
{
    std::cout << "Expression Term\n"
    << "Current Node pointer -> " << this
    << "\nOuter Coefficient -> " << getOuterCoefficient()
    << "\nInner Coefficient -> " << getInnerCoefficient()
    << "\nNumerator -> " << getNumerator()
    << "\nDenominator -> " << getDenominator()
    << "\nTrig Identifier -> " << getTrigIdentifier()
    << "\nExponent -> " << getExponent()
    << "\nNextNode pointer -> " << getNextNode() << std::endl;
}
std::ostream& Node::debug(std::ostream &out) const
{
    out << "Expression Term\n"
    << "Current Node pointer -> " << this
    << "\nOuter Coefficient -> " << getOuterCoefficient()
    << "\nInner Coefficient -> " << getInnerCoefficient()
    << "\nNumerator -> " << getNumerator()
    << "\nDenominator -> " << getDenominator()
    << "\nTrig Identifier -> " << getTrigIdentifier()
    << "\nExponent -> " << getExponent()
    << "\nNextNode pointer -> " << getNextNode() << std::endl;
    return out;
}

//functions
void Node::derive()
{
    if(getTrigIdentifier()!="")
    {
        if(check(getTrigIdentifier(),"sin") != -1)
        {
            setTrigIdentifier("cos");
        }
        if(check(getTrigIdentifier(),"cos") != -1)
        {
            outerCoefficient = outerCoefficient*-1;
            setTrigIdentifier("sin");
        }
        if(check(getTrigIdentifier(),"tan") != -1)
        {
            setTrigIdentifier("sec^2");
        }
        outerCoefficient = outerCoefficient*innerCoefficient;
    }
    outerCoefficient = outerCoefficient*exponent;
    exponent = exponent-1;
    //figure out eventually
}

int Node::check(std::string row,std::string wordToBeFound)
{
    std::string temp;
    int i = (int)row.size()+1;
    int j = (int)wordToBeFound.size();
    int checkStart = 0;
    while((checkStart+j)<i)
    {
        temp =row.substr(checkStart,j);
        if(temp==wordToBeFound)
        {
            return checkStart;
        }
        checkStart +=1;
    }
    return -1;
}

//ostream operator overload
std::ostream &operator<<(std::ostream &out, const Node &node)
{
    return node.debug(out);
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
    //std::cout<<"Entered"<<std::endl;
    //std::cout<<pNode<<std::endl;

    if(isEmpty())
    {
        head = pNode;
        head->setNextNode(nullptr);
        expressionCount++;
    }
    else
    {
        pNode->setNextNode(head);
        head = pNode;
        expressionCount++;
    }
    //std::cout<<head<<std::endl;
    //std::cout<<head->getNextNode()<<std::endl;
}
void LinkedList::addNode(std::string expr)
{
    int outer = 1;
    int inner = 1;
    int exp = 1;
    std::string trigId = "";
    
    //find if positive or negative
    if(expr[0] == '-')
    {
        outer = outer*-1;
    }
    
    //find if there exists an outer coefficient
    if(std::isdigit(expr[2]))
    {
        int num = (int)expr[2] - 48;
        if(num == 1)
        {
            if(expr[3] == '0')
            {
                num = 10;
            }
        }
        outer = outer*num;
    }
    
    //check for trig functions
    if(check(expr,"sin")!=-1)
    {
        trigId = "sin";
    }
    if(check(expr,"cos")!=-1)
    {
        trigId = "cos";
    }
    if(check(expr,"tan")!=-1)
    {
        trigId = "tan";
    }
    
    if(check(expr,"^")!=-1)
    {
        int num;
        if(expr[check(expr,"^")+1] == '-')
        {
            exp = exp*-1;
            
            num = (int)expr[check(expr,"^")+2] - 48;
            if(num == 1)
            {
                if(expr[check(expr,"^")+3] == '0')
                {
                    num = 10;
                }
            }
            
        }
        else
        {
            num = (int)expr[check(expr,"^")+1] - 48;
            if(num == 1)
            {
                if(expr[check(expr,"^")+2] == '0')
                {
                    num = 10;
                }
            }
        }
        exp = exp*num;
    }
    
    if(std::isdigit(expr[check(expr,"x")-1]))
    {
        if(expr[check(expr,"x")-1] == '0')
        {
            if(expr[check(expr,"x")-2] == '1')
            {
                inner = 10;
            }
        }
        else
        {
            inner = (int)expr[check(expr,"x")-1] -48;
        }
    }
    
    if(outer == inner || outer == (inner*-1))
    {
        inner = 1;
    }
    
    //debug
//    std::cout<<"outer ->" <<outer <<std::endl;
//    std::cout<<"inner ->" <<inner <<std::endl;
//    std::cout<<"trigID ->" <<trigId <<std::endl;
//    std::cout<<"exponent ->" <<exp <<std::endl;
    
    Node * node = new Node(outer,inner,exp,trigId);
    addNode(node);
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
void LinkedList::print()
{
    print(std::cout);
}
void LinkedList::print() const
{
    print(std::cout);
}
std::ostream &LinkedList::print(std::ostream &out)
{
    Node * hold = head;
    while(hold!=nullptr)
    {
        out << *hold << std::endl;
        hold = hold->getNextNode();
    }
    return out;
}
std::ostream &LinkedList::print(std::ostream &out) const
{
    //std::cout<<"Entered"<<std::endl;

    Node * hold = head;
    //std::cout<<hold<<std::endl;
    while(hold!=nullptr)
    {
        //std::cout<<"Entered"<<std::endl;

        out << *hold << std::endl;
        hold = hold->getNextNode();
    }
    return out;
}

int LinkedList::check(std::string row,std::string wordToBeFound)
{
    std::string temp;
    int i = (int)row.size()+1;
    int j = (int)wordToBeFound.size();
    int checkStart = 0;
    while((checkStart+j)<i)
    {
        temp =row.substr(checkStart,j);
        if(temp==wordToBeFound)
        {
            return checkStart;
        }
        checkStart +=1;
    }
    return -1;
}

std::ostream &operator<<(std::ostream &out, const LinkedList &link)
{
    //std::cout<<"Entered"<<std::endl;
    return link.print(out);
}
