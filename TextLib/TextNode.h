#pragma once
#include <iostream>
#include "Stack.h"

class TextNode
{
protected:
  static TextNode * firstFree; 
  static TextNode* textNodes;

  TextNode* next; 
  TextNode* down; 
  char c; 
  int level; //Уровень. 0 - текст, 1 - строка, 2 - слово, 3 - буква

public:
  TextNode(int _l = 3, char _c = 0);
  TextNode(char* s, int _l); 
  TextNode(const TextNode& _node); 
  ~TextNode();

  TextNode* GetNext();
  TextNode* GetDown();
  char GetC();
  int GetLevel();

  void SetNext(TextNode* _next);
  void SetDown(TextNode* _down);
  void SetC(char _c);
  void SetLevel(int _l);

  friend std::ostream& operator<<(std::ostream& o, TextNode& t);

  static void InitMem(int _size = 3); 
  static void FreeMem(); 

  void* operator new(size_t size);
  void operator delete(void* p);
};

TextNode* TextNode::firstFree = 0;
TextNode* TextNode::textNodes = 0;
