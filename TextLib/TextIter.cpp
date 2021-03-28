#include "Text_Iter.h"
#include <fstream>
#include <cstring>


TextIter::TextIter(Text& _text, TextNode* _node, TStack<TextNode*> _st) : text(_text) {
    node = _node;
    st = _st;
}

TextIter::TextIter(const TextIter& t) : text(t.text)
{
    node = t.node;
    st = t.st;
    text = t.text;
}

bool TextIter::GoNext() 
{
    if (node->GetLevel() == 3)
    {
        if (node->GetNext() != 0)
            node = node->GetNext();
        else
        {
            node = st.Get();
            if (node->GetNext() != 0)
                node = node->GetNext();
            else
            {
                node = st.Get();
                if (node->GetNext() != 0)
                    node = node->GetNext();
                else
                {
                    node = 0;
                    return false;
                }
            }
        }
    }
    else
    {
        st.Push(node);
        node = node->GetDown();
    }
    return true;
}

bool TextIter::GoNextChar()
{
    if (node->GetLevel() == 1)
    {
        if (node->GetDown() == nullptr)
            return false;
        else 
        {
            st.Push(node);
            node = node->GetDown();
            st.Push(node);
            node = node->GetDown();
            return true;
        }
    }
    if (node->GetLevel() == 2)
    {
        if (node->GetDown() == nullptr)
            return false;
        else
        {
            st.Push(node);
            node = node->GetDown();
            return true;
        }
    }
    if (node->GetLevel() == 3 && node->GetNext() != nullptr)
    {
        if (node->GetNext() == nullptr)
            return false;
        else 
        {
            node = node->GetNext();
            return true;

        }
    }

    if (node->GetLevel() == 3 && node->GetNext() == nullptr)
    {
        if (st.IsEmpty())
            throw logic_error("Error");

        TextNode* temp = st.Get();

        if (temp->GetNext() != nullptr)
        {
            st.Push(temp->GetNext());
            node = temp->GetNext()->GetDown();
            return true;
        }

    }
    return false;
}



bool TextIter::IsEnd()
{
    if (node == nullptr)
        return true;

    if (node->GetLevel() == 1 || node->GetLevel() == 2)
        return false;

    if (node->GetLevel() == 3 && node->GetNext() != nullptr)
        return false;

    if (node->GetLevel() == 3 && node->GetNext() == nullptr)
    {
        if (st.IsEmpty())
            throw logic_error("Error");

        TextNode* prev = st.Get();
        if (prev->GetNext() != nullptr)
        return true;
    }

    return true;
}

void TextIter::ResetToString()
{
    while (node->GetLevel() > 1) {
        st.Get();
        if (st.IsEmpty()) 
            throw logic_error("Error");
        node = st.Get();
    }
}

void TextIter::ResetToWord()
{
    if (node->GetLevel() == 1)
    {
        st.Push(node);
        node = node->GetDown();
    }
    else if (node->GetLevel() == 3)
        node = st.Get();
}

TextNode* TextIter::Get() {
    return this->node;
}
