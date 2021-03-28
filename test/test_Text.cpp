#include <gtest.h>
#include "Text_Iter.h"
#include "TextNode.h"
#include "Text.cpp"
#include "TextIter.cpp"
#include "TextNode.cpp"

TEST(Text, can_create_empty_text)
{
  ASSERT_NO_THROW(Text A());
}

TEST(Text, get_the_first_character_of_the_next_word) {
    char* const temp = "Hello World";
    Text A(temp);
    TextIter iter = A.GetRoot();

    while (iter.Get()->GetC() != ' ')
    {
        iter.GoNextChar();
    }

    iter.GoNextChar();
    ASSERT_EQ(iter.Get()->GetC(), 'W');
}

TEST(Text, can_create_non_empty_text)
{
  char* const temp = "Hello World";
  ASSERT_NO_THROW(Text A(temp));
}

TEST(TextIter, get_the_first_character) 
{
  char* const temp = "Hello World";
  Text A(temp);
  TextIter iter = A.GetRoot();
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'H');
}


TEST(TextIter, cannot_get_the_next_character_if_there_is_none) 
{
  char* const temp = "A";
  Text A(temp);
  TextIter iter = A.GetRoot();
  iter.GoNextChar();

  ASSERT_EQ(iter.GoNextChar(), false);
}

TEST(TextIter, can_go_next) 
{
  char* const temp = "Hello World";
  Text A(temp);
  TextIter iter = A.GetRoot();
  ASSERT_EQ(iter.GoNext(), true);
}

TEST(Text, can_find_the_letter)
{
  char* const temp = "Hello World";
  Text A(temp);
  TextIter iter = A.Find('e');
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'l');
}

TEST(Text, can_insert_a_letter)
{
  char* const temp = "Hello World";
  Text A(temp);
  TextIter iter = A.GetRoot();
  
  ASSERT_NO_THROW(A.Insert("Q", iter));
}

TEST(Text, can_find_the_word) 
{
  char* const temp = "Hello World";
  Text A(temp);

  char* const temp_find = "Hello";
  TextIter iter = A.FindWord(temp_find);
  iter.GoNextChar();
  ASSERT_EQ(iter.Get()->GetC(), 'H');
}

TEST(Text, text_find_word_3)
{
  char* const temp = "Hello World";
  Text A(temp);

  char* const temp_find = "qwe";
  TextIter iter = A.FindWord(temp_find);
  ASSERT_EQ(iter.IsEnd(), true);
}

TEST(Text, text_delete_0)
{
  char* const temp = "Hello World";
  Text A(temp);

  char* const temp_find = "World";
  TextIter iter = A.FindWord(temp_find);
  ASSERT_NO_THROW(A.Delete(1, iter));
}

TEST(Text, can_copy) 
{
  char* const temp = "Hello World";
  Text A(temp);

  char temp_find = 'd';
  TextIter iter = A.Find(temp_find);
  
  ASSERT_NO_THROW(char* res = A.Copy(1, iter));
}