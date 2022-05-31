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

TEST(SingleFeatureManagerTests, CannotAllocateTooMuch1) {
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

TEST(SingleFeatureManagerTests, CannotAllocateTooMuch2) {
	Manager manager;
	ASSERT_TRUE(manager.Add("FOO", 2));
	ASSERT_EQ(manager.Available("FOO"), 2);
	// Cannot allocate more than we have
	EXPECT_FALSE(manager.Allocate("FOO", 3));
	// State not altered
	EXPECT_EQ(manager.Available("FOO"), 2);
}

TEST(SingleFeatureManagerTests, CannotFreeTooMuch) {
	Manager manager;
	ASSERT_TRUE(manager.Add("FOO", 4));
	ASSERT_EQ(manager.Available("FOO"), 4);
	// Allocate a few
	EXPECT_TRUE(manager.Allocate("FOO", 3));
	EXPECT_EQ(manager.Available("FOO"), 1);
	// Cannot free more than is allocated
	EXPECT_FALSE(manager.Free("FOO", 4));
	// State not altered
	EXPECT_EQ(manager.Available("FOO"), 1);
}

TEST(SingleFeatureManagerTests, PartialFree) {
	Manager manager;
	ASSERT_TRUE(manager.Add("FOO", 4));
	ASSERT_EQ(manager.Available("FOO"), 4);
	// Allocate a few
	EXPECT_TRUE(manager.Allocate("FOO", 3));
	EXPECT_EQ(manager.Available("FOO"), 1);
	// Free some but not all
	EXPECT_TRUE(manager.Free("FOO", 2));
	EXPECT_EQ(manager.Available("FOO"), 3);
	// Free the rest
	EXPECT_TRUE(manager.Free("FOO", 1));
	EXPECT_EQ(manager.Available("FOO"), 4);
}
