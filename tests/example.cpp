
// Copyright 2022 roflanpotsan l1sZ@ya.ru

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
  EXPECT_EQ(first.size(), 3); ///second++ ---???
}

TEST(Unordered_Map, Empty) {
  // empty
  unordered_map<std::string, int> first;
  EXPECT_TRUE(first.empty());
  first.insert(std::make_pair("HaHaHA", 40));
  EXPECT_FALSE(first.empty());
}

//TEST(Unordered_Map, Operator_) {
//  unordered_map<int,int> c {std::make_pair(1, 2)};
//  EXPECT_EQ(c[std::make_pair(1, 2)], 2);
//}

TEST(Unordered_Map, At) {
  unordered_map<int,int> c {std::make_pair(1, 2)};
  EXPECT_THROW(c.at(std::make_pair(2, 2)), std::exception);
}

/*
TEST(Unordered_Set, Has) {
  // has
  unordered_set<int> first = {1, 2, 3};
  EXPECT_FALSE(first.has(99));
  first.insert(99);
  EXPECT_TRUE(first.has(99));
}
 */
/*
TEST(Unordered_Set, Insert) {
  unordered_set<int> ans = {-1, 3, 5, 7, 8, -2}, ans2 = {-1, 3, 5, 9, 7, 8, -2},
                     ans3 = {-1, 3, 5, 7, 8, -2, 9, 111, 222, 333}, first;
  unordered_set<std::string> ans4 = {"hello", "world", "[24 hour cinderella]"},
                             second;
  std::vector<std::string> v1 = {"hello", "world", "[24 hour cinderella]"};
  // insert with iterators range
  first.insert(ans.begin(), ans.end());
  EXPECT_EQ(first, ans);
  // insert an existing value -> no changes
  first.insert(5);
  EXPECT_EQ(first, ans);
  // insert new value
  first.insert(9);
  EXPECT_EQ(first, ans2);
  // insert with initializer list
  first.insert({111, 222, 333});
  EXPECT_EQ(first, ans3);
  // insert with iterators range, different iterator type
  second.insert(v1.begin(), v1.end());
  EXPECT_EQ(second, ans4);
}
 */
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
/*
TEST(Unordered_Set, STL) {
  unordered_set<int> first = {1, 11, 3, 5, 4, 7, 9};
  EXPECT_EQ(*std::find_if(first.begin(), first.end(),
                          [](int val) { return val % 2 == 0; }),
            4);
}
*/