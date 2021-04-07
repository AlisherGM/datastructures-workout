#include "map.hpp"
#include <gtest/gtest.h>

class MapTest : public ::testing::Test {};

TEST_F(MapTest, mapTest) {
    
  Map<int, std::string> map;
  map[4] = "Value4";
  map[1] = "Value1";
  map[2] = "Value2";
  map[6] = "Value6";
  map[3] = "Value3";
  map[8] = "Value8";

  ASSERT_EQ(map[4], "Value4");

  std::vector<std::pair<int, std::string>> expected_values {
        {1, "Value1"},
        {2, "Value2"},
        {3, "Value3"},
        {4, "Value4"},
        {6, "Value6"},
        {8, "Value8"},

    };

  auto m_iter = map.begin();
  auto v_iter = expected_values.begin();
  for(; m_iter != map.end() && v_iter != expected_values.end(); ++m_iter, ++v_iter) {
    ASSERT_EQ(*m_iter, *v_iter);
  }
}