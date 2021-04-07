#include "hashmap.hpp"
#include <cstring>
#include <gtest/gtest.h>

class MapTest : public ::testing::Test {};

TEST_F(MapTest, mapTest) {

  HashMap<std::string, int> h;
  h.insert("key1", 1);
  h.insert("key2", 2);
  h.insert("key3", 3);
  h.insert("key4", 4);
  h.insert("key5", 5);
  h.insert("key6", 6);
  h.insert("key7", 7);
  h.insert("key8", 8);
  h.insert("key9", 9);
  h.insert("key10", 10);
  h.insert("key11", 11);
  h.insert("key11", 110);
  h.insert("key12", 12);

  ASSERT_EQ(h.get("key12"), 12);

  std::vector<std::pair<std::string, int>> test_v = {
      {"key1", 1},   {"key2", 2},    {"key3", 3},  {"key4", 4}, {"key5", 5},
      {"key6", 6},   {"key7", 7},    {"key8", 8},  {"key9", 9}, {"key10", 10},
      {"key11", 11}, {"key11", 110}, {"key12", 12}};

  bool result;
  for (auto &i : h) {
    result = false;
    for (auto &j : test_v) {
      if (i.first == j.first)
        result = true;
    }
    ASSERT_TRUE(result);
  }

  h.remove("key12");
  for (auto &i : h) {
    ASSERT_NE(i.first, "key12");
  }
}