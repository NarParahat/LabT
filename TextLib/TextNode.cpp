#include "TextNode.h"
#include <cstring>

std::ostream& operator<<(std::ostream& o, TextNode& t)
{
    if (t.level == 3)
    {
        o << t.c;
        if (t.next != nullptr)
            o << *(t.next);
    }
    else
    {
        if (t.down != nullptr)
            o << *(t.down);

        if (t.next != nullptr)
            o << *(t.next);
    }

    return o;
}

TextNode::TextNode(int _l, char _c)
{
    next = nullptr;
    down = nullptr;
    c = _c;
    level = _l;
}

TextNode::TextNode(char* s, int l) //Принимает слово
{
    next = nullptr;
    c = 0;
    level = l;
    down = nullptr;

    if (l < 1 || l > 3)
        throw std::exception();
    if (l == 1)
    {
        int sz = strlen(s);
        if (sz > 0) {
            int start = 0;
            TextNode* wcur = new TextNode(2);
            this->SetDown(wcur);
            for (int i = 0; i < sz; i++) {
                if (s[i] == ' ' || i == sz - 1) {
                    if (start != 0) {
                        wcur->SetNext(new TextNode(2));
                        wcur = wcur->GetNext();
                    }
                    TextNode* lcur = new TextNode(3, s[start]);
                    wcur->SetDown(lcur);
                    for (int j = start + 1; j <= i; j++) {
                        lcur->SetNext(new TextNode(3, s[j]));
                        lcur = lcur->GetNext();
                    }
                    lcur->SetNext(nullptr);
                    start = i + 1;
                }
            }
            wcur->SetNext(nullptr);
        }
    }
    if (l == 2)
    {
        next = nullptr;
        c = 0;
        level = l;
        int sz = strlen(s);
        if (sz > 0) {
            TextNode* lcur = new TextNode(3, s[0]);
            this->SetDown(lcur);
            for (int i = 1; i < sz; i++) {
                lcur->SetNext(new TextNode(3, s[i]));
                lcur = lcur->GetNext();
            }
            lcur->SetNext(nullptr);
        }
    }
    if (l == 3) 
    {
        c = s[0];
        level = l;
        next = nullptr;
    }
}

TextNode::TextNode(const TextNode& _node)
{
    next = nullptr;
    down = nullptr;
    c = _node.c;
    level = _node.level;
}

TextNode::~TextNode()
{
}

TextNode* TextNode::GetNext()
{
    return next;
}

TextNode* TextNode::GetDown()
{
    return down;
}

char TextNode::GetC()
{
    return c;
}

int TextNode::GetLevel()
{
    return level;
}

void TextNode::SetNext(TextNode* _next)
{
    next = _next;
}

void TextNode::SetDown(TextNode* _down)
{
    down = _down;
}

void TextNode::SetC(char _c)
{
    c = _c;
}

void TextNode::SetLevel(int _l)
{
    if (_l >= 1 && _l <= 3)
        level = _l;
    else
        throw logic_error("Error");
}

void TextNode::InitMem(int _size)
{
    if (_size <= 0)
        throw logic_error("Error");

    if ((firstFree == 0) && (textNodes == 0)) 
    {
        textNodes = new TextNode[_size];
        firstFree = textNodes;
    }
    else if ((firstFree != 0) && (textNodes == 0))
        throw logic_error("Error");

    else
        textNodes = new TextNode[_size * 2];
        firstFree = textNodes;
    
}

void TextNode::FreeMem() //Освобождение памяти
{
    if (textNodes != 0)
    {
        delete[] textNodes;
    }
    textNodes = 0;
    firstFree = 0;
}

void* TextNode::operator new(size_t size)
{
    if ((firstFree == 0) && (textNodes == 0))
        InitMem();

    if ((firstFree == 0) && (textNodes != 0)) //Вызвать довыделение памяти
        InitMem();

    TextNode* node = firstFree;
    firstFree = firstFree->next;

    node->next = 0;

    return node;
}

void TextNode::operator delete(void* p)
{
    TextNode* node = (TextNode*)p;

    if ((firstFree == 0) && (textNodes == 0))
        throw logic_error("Error");

    node->next = nullptr;
    node->down = nullptr;
    node->c = 0;
    node->level = 3;

    node->next = firstFree;
    firstFree = node;
}