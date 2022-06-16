
// Copyright 2022 AlexNov nikolay.sasha@mail.ru

#include <gtest/gtest.h>
#include <work_dir.hpp>

#include <algorithm>
#include <vector>

TEST(Unordered_Map, Construct) {
  // empty constructor
  unordered_map<int, std::string> ans2, second;
  EXPECT_EQ(ans2.empty(), second.empty());
  // copy constructor
  std::pair<int,int> b = std::make_pair(1, 2);
  unordered_map<int, int> ans3({b}), third(ans3);
  EXPECT_EQ(third, ans3);
  // initializer list constructor
  unordered_map<int,int> c {std::make_pair(1, 2), std::make_pair(1, 2), std::make_pair(1, 2)};
  unordered_map<int,int> d {std::make_pair(1, 2), std::make_pair(1, 2), std::make_pair(1, 2)};
  EXPECT_EQ(c, d);
}

TEST(Unordered_Map, Assign) {
  // assign
  unordered_map<int, int> ans, first({std::make_pair(1, 44), std::make_pair(-1, 44)}), l(first);
  ans = l;
  EXPECT_EQ(first, ans);
}

TEST(Unordered_Map, Size) {
  // size
  unordered_map<char, int> first;
  EXPECT_EQ(first.size(), 0);
  first.insert({std::make_pair('1', 30), std::make_pair('2', 40), std::make_pair('1', 50)});
  EXPECT_EQ(first.size(), 3);
}

TEST(Unordered_Map, Empty) {
  // empty
  unordered_map<std::string, int> first;
  EXPECT_TRUE(first.empty());
  first.insert(std::make_pair("HaHaHA", 40));
  EXPECT_FALSE(first.empty());
}

TEST(Unordered_Map, Operator_) {
  // operator[]
  unordered_map<int,int> c {std::make_pair(1, 2)};
  EXPECT_EQ((c[std::make_pair(1, 2)]).second, 2);
  unordered_map<int,int> a {std::make_pair(2, 2)};
  EXPECT_EQ((a[std::make_pair(1, 2)]).second, 2);
}

TEST(Unordered_Map, At) {
  // at
  unordered_map<int,int> c {std::make_pair(1, 2)};
  EXPECT_THROW(c.at(std::make_pair(2, 2)), std::exception);
  EXPECT_EQ((*(&c.at(std::make_pair(1, 2)))).second, 2);
}

TEST(Unordered_Set, Insert) {
  // insert with initializer list
  unordered_map<char, int> first, second = {std::make_pair('1', 30), std::make_pair('2', 40), std::make_pair('1', 50)};
  first.insert({std::make_pair('1', 30), std::make_pair('2', 40), std::make_pair('1', 50)});
  EXPECT_EQ(first, second);
  unordered_map<char, int> third = {std::make_pair('1', 30), std::make_pair('2', 40), std::make_pair('1', 50), std::make_pair('6', 30)};
  // insert new value
  first.insert({std::make_pair('6', 30)});
  EXPECT_EQ(first, third);
  // insert an existing value -> no changes
  first.insert({std::make_pair('6', 30)});
  EXPECT_EQ(first, third);
}

TEST(Unordered_Set, Erase) {
  unordered_map<int, int> first = {std::make_pair(1, 2), std::make_pair(2, 3), std::make_pair(3, 10)};
  // erase by value
  EXPECT_TRUE(first.has(std::make_pair(1, 2)));
  first.erase(std::make_pair(1, 2));
  EXPECT_FALSE(first.has(std::make_pair(1, 2)));
  // erase by iterator
  EXPECT_TRUE(first.has(std::make_pair(2, 3)));
  first.erase(first.find(std::make_pair(2, 3)));
  EXPECT_FALSE(first.has(std::make_pair(2, 3)));
}

TEST(Unordered_Set, Clear) {
  // clear
  unordered_map<int, std::string> first = {std::make_pair(1, "30"), std::make_pair(2, "30"), std::make_pair(3, "30")};
  EXPECT_FALSE(first.empty());
  first.clear();
  EXPECT_TRUE(first.empty());
}

TEST(Unordered_Set, Swap) {
  // swap
  unordered_map<char, int> first = {std::make_pair('1', 3), std::make_pair('5', 7), std::make_pair('8', -2)}, second(first), ans(first);
  second.insert({'9', 101});
  swap(first, second);
  EXPECT_EQ(second, ans);
}

TEST(Unordered_Set, Find) {
  // find
  unordered_map<int, int> first = {std::make_pair(1, 2), std::make_pair(2, 3), std::make_pair(3, 10)};
  EXPECT_EQ(first.find(std::make_pair(10, 2)), first.end());
  EXPECT_EQ((*first.find(std::make_pair(1, 2))).second, 2);
  first.insert(std::make_pair(10, 2));
  EXPECT_EQ((*first.find(std::make_pair(10, 2))).second, 2);
}
