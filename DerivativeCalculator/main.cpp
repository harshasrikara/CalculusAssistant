//
//  main.cpp
//  DerivativeCalculator
//
//  Created by Harsha Srikara on 4/30/19.
//  Copyright © 2019 Harsha Srikara. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "linkedList.hpp"

std::string readFile(std::string filename);
void readLine(std::string file);
std::string readExpression(std::string output);
int check(std::string row,std::string wordToBeFound);
bool ifMultipleX(std::string file);
bool ifMultipleOperator(std::string file);

int main(int argc, const char * argv[]) {
    
    std::cout<<"Enter the filename: ";
    std::string file;
    //std::getline(std::cin,file);
    file = "derive.txt";
    //exception handling. Actual file opening done by the getData function.
    std::ifstream myReadFile; //input stream
    myReadFile.open(file);
    if(myReadFile)
    {
        myReadFile.close();
        
        //calls function to extract data
        std::string extractedData;
        extractedData = readFile(file);
        
        std::cout<<extractedData<<std::endl;
        
        readLine(extractedData);
    }
    return 0;
}


std::string readFile(std::string filename)
{
    //temporary variables
    std::string line; //contains line by line strings from the txt file
    std::string output; //contains the concatnation of all lines
    std::ifstream myReadFile; //input stream
    
    //opens the input stream with the txt file
    myReadFile.open(filename);
    if(myReadFile.is_open()) //checks to see if the file opened successfully
    {
        std::cout<<filename<<" successfully opened\n\n"<<std::endl;
        while(!myReadFile.eof()) // To get you all the lines. eof - end of file
        {
            std::getline(myReadFile,line); // Saves the line in line. Gets one line at a time
            //std::cout<<line; // Prints the line.  (if you want to debug)
            output = output + line + "\n";
        }
    }
    else //if file opening failed
    {
        std::cout<<filename << " failed to open"<<std::endl;
    }
    myReadFile.close(); //ends the input stream
    return output;
}

void readLine(std::string file)
{
    //converts the string into a stream of characters. Easier to go through line by line.
    std::istringstream lineFinder(file);
    std::string output = "";
    
    //cycle through all the lines in a string
    for (std::string line; std::getline(lineFinder, line);)
    {
        //variables for creating the node
        
        //int outerCoeff = 1; //default
        //int innerCoeff = 1; //default
        //int exponent = 1; //default
        //std::string trigId = "";
        
        output = line;
        //adds a qualifying + sign to the beginning
        if(isdigit(output[0]) || output[0] == 's' || output[0] == 'c' || output[0] == 'x')
        {
            output = "+ " + output;
        }
        //break at end case
        
        if(output[0] != '+' && output[0] != '-')
        {
            break;
        }
        if(output[0] == ' ')
        {
            break;
        }
        std::cout << "Original Equation ->" << output <<std::endl;
        
        //BIG ERROR SOMEWHERE AROUND HERE
        while(check(output.substr(1),"+") != -1 || check(output.substr(1),"-") != -1)
        {
            std::string expression;
            if(check(output,"x") != -1)
            {
                expression = readExpression(output);
                //std::cout << "expression ->" << expression <<std::endl;
                //std::cout << expression.length();
                output = output.substr(expression.length());
                //std::cout << check(output,"x") << "remaining part ->" << output <<std::endl;
            }
            //final validity check
            if(check(expression,"x")!=-1 && !ifMultipleX(expression))
            {
                std::cout << "Element ->" << expression << std::endl;
            }
            if(check(output,"x")!=-1 && !ifMultipleX(output)
               && !(check(output.substr(1),"+") != -1 || check(output.substr(1),"-") != -1)
               && output[0] != ' ')
            {
                std::cout << "Element ->" << output <<std::endl;
            }
        }
    }
}

std::string readExpression(std::string output)
{
    std::string temp;
    bool firstOperator = false;
    bool exponent = false;
    
    for(char t:output)
    {
        if(!firstOperator)
        {
            temp = t;
            firstOperator = !firstOperator;
            continue;
        }
        if(t=='^')
        {
            exponent = true;
        }
        if(exponent)
        {
            if(t == ' ')
            {
                break;
            }
        }
        if(t == '+' || t == '-')
        {
            if(!exponent)
            {
                break;
            }
            else
            {
                exponent = !exponent;
            }
        }
        temp = temp + t;
    }
    return temp;
}

bool ifMultipleX(std::string file)
{
    int t = 0;
    for(char c:file) //for each character in str
    {
        if(c == 'x')
        {
            t++;
        }
    }
    if(t>1)
    {
        return true;
    }
    return false;
}
bool ifMultipleOperator(std::string file)
{
    int t = 0;
    for(char c:file) //for each character in str
    {
        if(c == 'x')
        {
            t++;
        }
    }
    return false;
}

//checks if one string is a substring of another and if yes returns the index of the first character else -1
int check(std::string row,std::string wordToBeFound)
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
