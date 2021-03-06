#include <iostream>
#include <string>
#include <gtest.h>
#include "postfix.h"

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p());
}

TEST(TPostfix, can_create_postfix_with_the_parameter)
{
	ASSERT_NO_THROW(TPostfix p("a + d / cos ( u - r )"));
}

TEST(TPostfix, can_create_postfix_with_the_constant)
{
	ASSERT_NO_THROW(TPostfix p("a + d / cos ( pi / 3 )"));
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p("a + d / cos ( u - r )");
	EXPECT_EQ("a + d / cos ( u - r )" , p.GetInfix());
}

TEST(TPostfix, can_get_infix_with_the_constant)
{
	TPostfix p("a + d / cos ( pi / c )");
	EXPECT_EQ("a + d / cos ( pi / c )", p.GetInfix());
}


TEST(TPostfix, can_get_postfix)
{
	TPostfix p("a + d / cos ( u - r )");
	EXPECT_EQ("a d u r - cos / + ", p.GetPostfix());
}

TEST(TPostfix, can_get_postfix_with_the_const)
{
	TPostfix p("- cos ( pi / a ) + b");
	EXPECT_EQ("pi a / cos - b + ", p.GetPostfix());
}

TEST(TPostfix, can_calculate_the_expression)
{
	TPostfix p("a + d / cos ( u - r )");
	EXPECT_EQ(8, p.Calculate());//if a = d = u = r = 4
}

TEST(TPostfix, can_calculate_the_expression_with_the_const)
{
	TPostfix p("- cos ( pi / a ) + b");
	EXPECT_EQ(4, p.Calculate());//if a = 1; b = 3
}


