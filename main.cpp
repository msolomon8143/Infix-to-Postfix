/********************************************
 * Name: Michael Solomon
 * File: Project 1 - Stacks
 * Class: COP4415.01
 * Date: 3/5/22
 * *******************************************/
// CPP program to convert infix to Postfix
#include <iostream>
#include <string>
#include<bits/stdc++.h>
using namespace std;
#define MAX 100

class Stack {
public:
    int top;
    char exp[MAX];
    Stack() { top = -1;}
    bool push(char item);     //function prototypes
    char pop();
    char peek();
    bool isEmpty();
};

int prec(char c);
string infixToPostfix(string s);
int evaluatePostfix(string exp);

string infixToPostfix(string s){ //Convert an infix to post fix
    class Stack st;
    string result;
    for(int i = 0; i < s.length(); i++) {
        char c = s[i];
        if((c >= '0' && c <= '9'))
            result += c;
        else if(c == '(')
            st.push('(');
        else if(c == ')') {
            while(st.peek() != '(')
            {
                result += st.peek();
                st.pop();
            }
            st.pop();
        }
        else {
            while(!st.isEmpty() && prec(s[i]) <= prec(st.peek())) {
                result += st.peek();
                st.pop();
            }
            st.push(c);
        }
    }
    while(!st.isEmpty()) { //pop elements from stack
        result += st.peek();
        st.pop();
    }
    return result;
}

int prec(char c) { //Returns integer for corresponding character
    switch(c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    } return -1;
}

int evaluatePostfix(string s){
    char c = s.back();
    s.pop_back();
    int num1,num2;
    if(prec(s.back()) > 0){
        num1 = evaluatePostfix(s);
    }else{
        num1 = s.back()-48;
        s.pop_back();
    }
    if(prec(s.back()) > 0){
        num2 = evaluatePostfix(s);
    }else{
        num2 = s.back()-48;
        s.pop_back();
    }
    switch (c){
        case '*':
            return num1*num2;
        case '/':
            return num1/num2;
        case '+':
            return num1+num2;
        case '-':
            return num1-num2;
    }return 0;
}

bool Stack::push(char item) { // push element out of stack
    if(top >= (MAX - 1 )){
        cout << "Stack Overflow";
        return false;
    }else{
        top++;
        exp[top]=item;
        return true;
    }
}

char Stack::pop() {  // pop element into stack
    if (top < 0) {
        cout << "Stack Underflow";
        return 0;
    }else {
        int x = exp[top];
        top--;
        return x;
    }
}

char Stack::peek(){ //fecthes top of stack
    if (top < 0) {
        return 0;
    }
    else {
        char x = exp[top];
        return x;
    }
}

bool Stack::isEmpty(){ //checks if stack is empty
    return (top < 0);
}

int main() {
    string exp;
    cout<<"Enter expression: ";
    cin>>exp;
    string postfix;
    int evaluation;
    cout<<"Infix to Postfix: ";
    postfix = infixToPostfix(exp);
    cout<<postfix<<"\n";
    cout<<"Postfix Evaluation: ";
    evaluation = evaluatePostfix(postfix);
    cout<<evaluation<<"\n";
    return 0;
}


