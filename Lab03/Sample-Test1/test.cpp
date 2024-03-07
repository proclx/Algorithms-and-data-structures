#include "pch.h"
#include "../TableDataStructure/Table.h"

TEST(Table_IsFull, TableTest) {
	Table A{ 1 };
	EXPECT_EQ(A.IsFull(), false);
	A.TableAdd(101, 17, "Ivan");
	EXPECT_EQ(A.IsFull(), true);
}