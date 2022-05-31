#include "pch.hpp"

#include "Manager.hpp"

using namespace licmon;

TEST(EmptyManagerTests, HasNoFeatures) {
	Manager manager;
	// No features are available
	EXPECT_EQ(manager.Available("FOO"), 0);
	EXPECT_EQ(manager.Available("BAR"), 0);
}

TEST(EmptyManagerTests, CannotAllocate) {
	Manager manager;
	// Allocation fails
	EXPECT_FALSE(manager.Allocate("FOO"));
	// State does not change
	EXPECT_EQ(manager.Available("FOO"), 0);
}

TEST(SingleFeatureManagerTests, AllocateAndFree) {
	Manager manager;
	// Add a feature
	EXPECT_TRUE(manager.Add("FOO"));
	EXPECT_EQ(manager.Available("FOO"), 1);
	// Allocate it
	EXPECT_TRUE(manager.Allocate("FOO"));
	EXPECT_EQ(manager.Available("FOO"), 0);
	// Free it again
	EXPECT_TRUE(manager.Free("FOO"));
	EXPECT_EQ(manager.Available("FOO"), 1);
}

TEST(SingleFeatureManagerTests, CannotFreeBeforeAllocate) {
	Manager manager;
	ASSERT_TRUE(manager.Add("FOO"));
	ASSERT_EQ(manager.Available("FOO"), 1);
	// We cannot free something that was not allocated
	EXPECT_FALSE(manager.Free("FOO"));
	// State was not altered
	EXPECT_EQ(manager.Available("FOO"), 1);
}

TEST(SingleFeatureManagerTests, CannotAllocateTooMuch) {
	Manager manager;
	ASSERT_TRUE(manager.Add("FOO"));
	ASSERT_EQ(manager.Available("FOO"), 1);
	// First allocation is ok
	EXPECT_TRUE(manager.Allocate("FOO"));
	EXPECT_EQ(manager.Available("FOO"), 0);
	// Second allocation is not
	EXPECT_FALSE(manager.Allocate("FOO"));
	// State not altered
	EXPECT_EQ(manager.Available("FOO"), 0);
}


