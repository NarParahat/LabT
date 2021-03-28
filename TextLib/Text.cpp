#include "Text_Iter.h"
#include <fstream>
#include <cstring>

Text::Text(char* s)
{
    root = new TextNode(s, 1);
}

Text::~Text()
{
    TextNode::FreeMem();
}

TextIter Text::GetRoot()
{
    return TextIter(*this, root, TStack<TextNode*>());
}

TextIter Text::Find(char c)
{
    TextIter iter = TextIter(*this, root, TStack<TextNode*>());
        while (iter.GoNextChar())
        {
            if (iter.Get()->GetC() == c)
                return iter;
        }
    return iter;
}

TextIter Text::FindWord(char* c)
{
    TextIter iter = GetRoot();

    while (iter.GoNext())
    {
            TextIter result = iter;
            bool word = true;
            int i = 0;
            int n = strlen(c);

            while (iter.GoNext() && i < n)
            {

                if (iter.Get()->GetC() != c[i])
                {
                    word = false;
                    break;
                }
                i++;
            }

            if (word)
                return result;
    }
    
    return iter;      

}

TextIter Text::Find(char* s)
{
    TextIter iter = GetRoot();

    while (iter.GoNextChar())
    {
        TextIter result = iter;
        bool letter = true;
        bool next = true;
        int n = strlen(s);

        for (int i = 0; i < n; i++)
        {
            if (s[i] != result.Get()->GetC()) {
                letter = false;
                break;
            }
            next = result.GoNextChar();
        }

        if (letter)
            return iter;
    }
}


void Text::Insert(char* c, TextIter iter)
{
    TextNode* node = new TextNode(c, iter.Get()->GetLevel());
    TextNode* next = iter.Get()->GetNext();
    node->SetNext(next);
    iter.Get()->SetNext(node);
}

void Text::InsertData(char* c, TextIter i)
{
    int n = strlen(c);
    if (n == 1)
        Insert(c, i);
else 
{
    int level = 2;
    int space = 0;

    for (int q = 0; q < n; q++)
    {
        if (c[q] == ' ') 
        {
            level = 1;
            break;
        }
    }

    TextIter osn = i;
    TextNode* next = i.Get()->GetNext();

    if (next->GetC() == ' ') 
    {
        i.GoNextChar(); 
        char* t = new char[n + 1];
        t[n ++] = '\0';

        for (int j = 0; j < n; j++)
        {
            t[j] = c[j];
        }
        t[n] = ' ';

        TextNode* node = new TextNode(t, level);

        next->SetNext(node);
        i.Get()->SetNext(node);
    }
    else 
    {
        int cc = 0;
        char symbol = ' ';

        TextNode* cc_node = i.Get()->GetNext();


        while ((cc_node->GetC() != '.') && (cc_node->GetC() != ' ') && (cc_node->GetC() != '\n'))
        {
            cc++;
            cc_node = cc_node->GetNext();
        }

        if (cc_node->GetC() == '.')
            symbol = '.';

        if (cc_node->GetC() == '\n')
            symbol = '\n';

      
        char* temp = new char[strlen(c) + cc + 3];
        temp[n + cc + 3] = '\0';
        temp[0] = ' ';

        int j = 1;
        int k = 0;

        for (j; j < n + 1; j++, k++)
        {
            temp[j] = c[k];
        }
        temp[j] = ' ';

        TextNode* temp_node = i.Get()->GetNext();
        for (j = j + 1; j < n + cc + 2; j++)
        {
            temp[j] = temp_node->GetC();
            temp_node = temp_node->GetNext();
        }

        temp[n + cc + 2] = symbol;

        osn.GoNext();
        this->Delete(cc, osn);

        TextNode* node = new TextNode(temp, level);
        next->SetNext(node);
        i.Get()->SetNext(node);
    }
}
}

void Text::Delete(int count, TextIter iter)
{
    if (count == 0)
        return;

    TStack<TextNode*> stack[3];
    int del = 0;
    int level = iter.Get()->GetLevel();

    if (level < 3)
    {
        iter.GoNextChar();
    }

    if (level >= 1 && level <= 3)
    {
        stack[level - 1].Push(iter.Get());
        if (level == 3)
            del++;
    }

    TextIter it = iter;
    while (it.GoNext() && del < count)
    {
        level = it.Get()->GetLevel();

        if (level >= 1 && level <= 3)
        {
            stack[level - 1].Push(it.Get());

            if (level == 3)
            {
                del++;
            }
        }
    }

    if (del < count)
        throw logic_error("ERROR");

    if (stack[0].IsEmpty() && stack[1].IsEmpty())
    {
        TextIter prev = iter;
        prev.ResetToWord();
        while (prev.Get()->GetNext() != iter.Get() && prev.Get()->GetDown() != iter.Get())
            prev.GoNext();

        TextNode* last = stack[2].Get();

        if (prev.Get()->GetLevel() == 2)
            prev.Get()->SetDown(last->GetNext());
        else
            prev.Get()->SetNext(last->GetNext());

        delete last;
        return;
    }


    TextIter prev = iter;
    prev.ResetToWord();

    while (prev.Get()->GetNext() != iter.Get() && prev.Get()->GetDown() != iter.Get())
        prev.GoNext();

    if (prev.Get()->GetNext() == iter.Get())
        prev.Get()->SetNext(nullptr);

    else
        prev.Get()->SetDown(nullptr);

    if (stack[0].IsEmpty()) 
    {
        TextNode* last_word = stack[1].Get();
        TextNode* last_letter = stack[2].Get();
        TextIter cur = iter;
        cur.ResetToWord();
        cur.Get()->SetNext(last_word);
        last_word->SetDown(last_letter->GetNext());
        delete last_letter;

        for (int i = 1; i < 3; i++)
        {
            while (!stack[i].IsEmpty())
            {
                TextNode* del = stack[i].Get();
                delete del;
            }
        }
    }
    else 
    {
        TextNode* last_string = stack[0].Get();
        TextNode* last_word = stack[1].Get();
        TextNode* last_letter = stack[2].Get();
        TextIter cur = iter;
        cur.ResetToString();
        cur.Get()->SetNext(last_string);
        cur.ResetToWord();
        cur.Get()->SetNext(last_word);
        last_word->SetDown(last_letter->GetNext());
        delete last_letter;

        for (int i = 0; i < 3; i++)
        {
            while (!stack[i].IsEmpty())
            {
                TextNode* temp = stack[i].Get();
                delete temp;
            }
        }
    }
}

char* Text::Copy(int count, TextIter iter)
{
    if (count < 0)
        throw logic_error("Error");

    char* res = new char[count ++];

    while (iter.Get()->GetLevel() < 3)
        iter.GoNext();

    if (count > 0)
    {
        res[0] = iter.Get()->GetC();

        for (int i = 0; i < count; i++)
        {
            iter.GoNextChar();
            res[i] = iter.Get()->GetC();

        }
    }

    res[count] = 0;
    return res;
}

std::ostream& operator<<(std::ostream& out, Text& t)
{
    out << *(t.root);
    return out;
}
