#pragma once
#include "TextNode.h"
#include <fstream>
#include <string>

class TextIter;

class Text {
protected:
    TextNode* root;
public:
    Text(char* s = 0);
    ~Text();

    TextIter GetRoot(); 
    TextIter Find(char c); 
    TextIter Find(char* c); 
    TextIter FindWord(char* c); 


    void Insert(char* c, TextIter i);
    void InsertData(char* c, TextIter i);
    void Delete(int count, TextIter i); 
    char* Copy(int count, TextIter i); 

    friend std::ostream& operator<<(std::ostream& o, Text& t);
};

class TextIter {
protected:
    Text& text;
    TextNode* node;
    TStack<TextNode*> st;
public:
    TextIter(Text& _text, TextNode* _node, TStack<TextNode*> _st);
    TextIter(const TextIter& t);

    bool GoNext(); 
    bool GoNextChar();
    bool IsEnd(); //Првоерка конца

    void ResetToString();
    void ResetToWord();

    TextNode* Get();    
};