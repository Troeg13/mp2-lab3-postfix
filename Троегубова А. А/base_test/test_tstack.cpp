#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, throws_when_stack_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_get_size)
{
	TStack<int> st(4);
	EXPECT_EQ(4, st.GetSize());
}

TEST(TStack, can_get_count_element_in_stack)
{
	TStack<int> st(4);
	st.Put(1);
	st.Put(2);
	st.Put(5);
	EXPECT_EQ(3, st.Cardinality());
}

TEST(TStack, can_view_the_top_element)
{
	TStack<int> st(4);
	st.Put(1);
	st.Put(2);
	st.Put(5);
	EXPECT_EQ(5, st.Head());
}

TEST(TStack, can_put_element)
{
	TStack<int> st(4);
	ASSERT_NO_THROW(st.Put(3));
	EXPECT_EQ(1, st.Cardinality());
	EXPECT_EQ(3, st.Head());
}

TEST(TStack, can_get_top_element)
{
	TStack<int> st(4);
	st.Put(1);
	st.Put(2);
	st.Put(3);
	ASSERT_NO_THROW(st.Get());
	EXPECT_EQ(2, st.Cardinality());
	EXPECT_EQ(2, st.Head());
}

TEST(TStack, true_when_stack_is_empty)//проверка на пустату стека
{
	TStack<int> st(3);
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, throws_when_put_element_in_full_stack)//исклющение когда добавляют элемент в полный стек
{
	TStack<int> st(2);
	st.Put(1);
	st.Put(2);
	ASSERT_ANY_THROW(st.Put(3));
}

TEST(TStack, true_when_stack_is_full)//проверка на пустату стека
{
	TStack<int> st(2);
	st.Put(1);
	st.Put(2);
	EXPECT_EQ(true, st.IsFull());
}

TEST(TStack, throws_when_get_element_in_empty_stack)
{
	TStack<int> st(3);
	ASSERT_ANY_THROW(st.Get());
}


