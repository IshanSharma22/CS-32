//
//  eval.cpp
//  HomeWork 2
//
//  Created by Ishan Sharma on 2/4/17.
//  Copyright © 2017 Ishan Sharma. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;


int precedence(char c);
bool syntax(string infix);

int evaluate(string infix, const bool values[], string& postfix, bool& result)
// Evaluates a boolean expression
// Postcondition: If infix is a syntactically valid infix boolean
//   expression, then postfix is set to the postfix form of that
//   expression, result is set to the value of the expression (where
//   in that expression, each digit k represents element k of the
//   values array), and the function returns zero.  If infix is not a
//   syntactically valid expression, the function returns 1.  (In that
//   case, postfix may or may not be changed, but result must be
//   unchanged.)
{
    
    string amendedString="";
    
    for (int i=0; i<infix.size(); i++){         //Remove Spaces
        char c = infix[i];
        if ( c != ' ')
            amendedString +=c;
    }
    
    if (amendedString=="")                      //If empty return 1
        return 1;
    
    if (!syntax(amendedString)){           //Check Syntax
        return 1;
    }

    // Infix to Postfix conversion, assuming coreect syntax
    postfix="";
    stack <char> CharStack;
    for (int j=0; j<amendedString.size(); j++){
        
        switch(amendedString[j]){
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    postfix+=amendedString[j];
                    break;
                
                case '(':
                    CharStack.push(amendedString[j]);
                    break;
                
                case ')':
                    if(postfix.empty())
                        return 1;
                    while (CharStack.top()!= '('){
                        postfix+= CharStack.top();
                        CharStack.pop();
                        if(CharStack.empty()){
                            return 1;
                        }
                }
                CharStack.pop();
                break;
                
                case '!':
                    CharStack.push(amendedString[j]);
                    break;
                case '&':
                case '|':
                while (!CharStack.empty() && CharStack.top()!='(' && (precedence(amendedString[j]) <= precedence(CharStack.top()) ) ){
                    postfix+=CharStack.top();
                    CharStack.pop();
                }
                CharStack.push(amendedString[j]);
                break;
        }
    }
    
    while (!CharStack.empty()){
        if(CharStack.top() == '(')
            return 1;
        postfix+=CharStack.top();
        CharStack.pop();
    }
    
    // Evaluation
    
    stack <bool> OperStack;
    for (int i=0; i<postfix.size(); i++){
        char c=postfix[i];
        if (isdigit(c)){
            int n = c - '0';
            OperStack.push(values[n]);
        }
        else{
            bool operand2 = OperStack.top();
            OperStack.pop();
            if (c == '!'){
                OperStack.push(!operand2);
                continue;
            }
            bool operand1 = OperStack.top();
            OperStack.pop();
            if (c== '|')
                OperStack.push(operand1 || operand2);
            else if (c == '&')
                OperStack.push(operand1 && operand2);
        }
            
    }
    
    if (OperStack.size() != 1)
        return 1;
    result=OperStack.top();
    return 0;
}

int precedence(char c){
    switch (c) {
        case '!':
            return 3;
            break;
        case '&':
            return 2;
            break;
        case '|':
            return 1;
            break;
    }
    return -1;
}

bool syntax(string amendedInfix) // Returns true if the infix string is syntactically valid
{
    int open=0;
    int close=0;
    
    
    if(amendedInfix[amendedInfix.size()-1] == '&' || amendedInfix[amendedInfix.size()-1] == '|')
    {
        return false;
    }
    
    
    if(amendedInfix[amendedInfix.size()-1] == '!')
    {
        return false;
    }
    
    if(amendedInfix[0] == '&' || amendedInfix[0] == '|')
    {
        return false;
    }

    
    for(int k = 0; k < amendedInfix.size(); k++)
    {
        char x = amendedInfix[k];

        if(x == '|' || x == '&')
        {
            if (k==0){
                return false;
            }
            
            if(!isdigit(amendedInfix[k-1]) && (amendedInfix[k-1] != ')') )
            {
                return false;
            }
        }


        if(isdigit(x))
        {
            if (k!=0){
                if(isdigit(amendedInfix[k-1]))
                {
                    return false;
                }
            }
        }
        
        if(x == '(')
            open++;
        
        
        if(x== ')')
            close++;
    }
    
    if (open != close){ // if number of open parantheses does not equal number of close parentheses
        return false;
    }

    return true;
    
    
}


