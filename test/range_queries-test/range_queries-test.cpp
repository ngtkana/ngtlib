#include <catch2/catch.hpp>
#include <bits/stdc++.h>
#include <range_queries/binary_indexed_tree.hpp>
#include <range_queries/segment_tree.hpp>
#include <range_queries/lazy_segment_tree.hpp>
#include "../utility.hpp"

struct binary_indexed_tree_tag{};
struct segment_tree_tag{};
struct lazy_segment_tree_tag{};

/*
  Range Minimum Query
*/

template <typename DispatchTag>
struct range_minimum_query_engine{};

template <>
struct range_minimum_query_engine<segment_tree_tag>{
  segment_tree<int, min_fn_t> storage;
  range_minimum_query_engine(int n): storage(n, min_fn, inf){}
  int  query (int l, int r) const {return storage.query(l, r);}
  void update(int i, int x)       {storage.update(i, x);}
};

template <>
struct range_minimum_query_engine<lazy_segment_tree_tag>{
  lazy_segment_tree<int, int, min_fn_t, update_fn_t, update_fn_t, id_fn_t, id_fn_t> storage;
  range_minimum_query_engine(int n):
    storage(n, min_fn, update_fn, update_fn, inf, -1, id_fn, id_fn){}
  int  query (int l, int r) {return storage.query(l, r);}
  void update(int i, int x) {storage.act(i, i + 1, x);}
};


TEMPLATE_TEST_CASE
(
  "Range minimum Query Test",
  "[Segment Tree, Lazy Segment Tree]",
  segment_tree_tag,
  lazy_segment_tree_tag
)
{
  SECTION("From he Sample Input 1 of AOJ DSL_2_A")
  {
    auto engine = range_minimum_query_engine<TestType>(3);
    engine.update(0, 1);
    engine.update(1, 2);
    engine.update(2, 3);
    REQUIRE(engine.query(0, 2) == 1);
    REQUIRE(engine.query(1, 2) == 2);
  }

  SECTION("From he Sample Input 2 of AOJ DSL_2_A")
  {
    auto engine = range_minimum_query_engine<TestType>(1);
    REQUIRE(engine.query(0, 1) == std::numeric_limits<int>::max());
    engine.update(0, 5);
    REQUIRE(engine.query(0, 1) == 5);
  }
}

/*
  Range Sum Query
*/

template <typename DispatchTag>
struct range_sum_query_engine{};

template <>
struct range_sum_query_engine<binary_indexed_tree_tag>{
  binary_indexed_tree<int, sum_fn_t, dif_fn_t> storage;
  range_sum_query_engine(int n): storage(n, sum_fn, dif_fn, 0){}
  int  query (int l, int r) const {return storage.query(l, r);}
  void update(int i, int x)       {storage.update(i, x);}
};

template <>
struct range_sum_query_engine<segment_tree_tag>{
  segment_tree<int, sum_fn_t> storage;
  range_sum_query_engine(int n): storage(n, sum_fn, 0) {}
  int  query (int l, int r) const {return storage.query(l, r);}
  void update(int i, int x)       {storage.update(i, x);}
};

template <>
struct range_sum_query_engine<lazy_segment_tree_tag>{
  lazy_segment_tree<int, int, sum_fn_t, update_fn_t, update_fn_t, twice_fn_t, half_fn_t> storage;
  range_sum_query_engine(int n):
    storage(n, sum_fn, update_fn, update_fn, 0, -1, twice_fn, half_fn){}
  int  query (int l, int r) {return storage.query(l, r);}
  void update(int i, int x) {storage.act(i, i + 1, x);}
};

TEMPLATE_TEST_CASE
(
  "Range Sum Query Test from the Sample Input 1 of AOJ DSL_2_B",
  "[Binary Indexed Tree,Segment Tree]",
  binary_indexed_tree_tag,
  segment_tree_tag,
  lazy_segment_tree_tag
)
{
  auto engine = range_sum_query_engine<TestType>(3);
  engine.update(0, 1);
  engine.update(1, 2);
  engine.update(2, 3);
  REQUIRE(engine.query(0, 2) == 3);
  REQUIRE(engine.query(1, 2) == 2);
}
