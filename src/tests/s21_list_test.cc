#include "../s21_containers/s21_list.h"

#include <gtest/gtest.h>

#include <list>

template <typename value_type>
bool CompareLists(s21::list<value_type> my_list,
                  std::list<value_type> std_list) {
  bool result = true;

  if (my_list.size() == std_list.size()) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();

    for (size_t i = 0; i != my_list.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      my_it++;
      std_it++;
    }
  } else {
    result = false;
  }

  return result;
}

TEST(ListConstructors, DefaultConstructor) {
  s21::list<int> basic;
  EXPECT_ANY_THROW(basic.front());
  EXPECT_ANY_THROW(basic.back());
  EXPECT_TRUE(basic.empty());
}

TEST(ListConstructors, SizeConstructor) {
  s21::list<int> basic(12);
  EXPECT_EQ(basic.front(), int());
  EXPECT_EQ(basic.back(), int());
  EXPECT_EQ(basic.size(), size_t(12));
  EXPECT_FALSE(basic.empty());
}

TEST(ListConstructors, InitializerListConstructor) {
  s21::list<int> basic({1, 2, 3, 4, 5});
  EXPECT_EQ(basic.front(), 1);
  EXPECT_EQ(basic.back(), 5);
  EXPECT_EQ(basic.size(), size_t(5));
  EXPECT_FALSE(basic.empty());
}

TEST(ListConstructors, CopyConstructor) {
  std::string element = "this";
  std::string element2 = "test";
  std::string element3 = "is";
  std::string element4 = "great";
  s21::list<std::string> basic({element, element2, element3, element4});
  s21::list<std::string> basic2(basic);
  EXPECT_TRUE(basic2.size() == 4);
  EXPECT_EQ(basic2.back(), element4);
  EXPECT_EQ(basic2.front(), element);
}

TEST(ListConstructors, MoveConstructorEmpty) {
  s21::list<std::string> basic;
  s21::list<std::string> basic2(basic);
  EXPECT_TRUE(basic2.empty());
}

TEST(ListConstructors, CopyConstructorEmpty) {
  s21::list<std::string> basic;
  s21::list<std::string> basic2(basic);
  EXPECT_TRUE(basic2.empty());
}

TEST(ListModifiers, PushBack) {
  s21::list<int> basic;
  basic.push_back(1);
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.back(), 1);
  EXPECT_EQ(basic.front(), 1);
}

TEST(ListModifiers, PushFront) {
  s21::list<int> basic;
  basic.push_front(1);
  EXPECT_TRUE(basic.size() == 1);
  EXPECT_EQ(basic.front(), 1);
}

TEST(ListModifiers, PopFront) {
  s21::list<std::string> basic;
  std::string element = "this";
  std::string element2 = "test";
  std::string element3 = "is";
  std::string element4 = "great";
  basic.push_front(element);
  basic.push_front(element2);
  basic.push_front(element3);
  basic.push_front(element4);
  basic.pop_front();
  EXPECT_TRUE(basic.size() == 3);
  EXPECT_EQ(basic.back(), element);
  EXPECT_EQ(basic.front(), element3);
}

TEST(ListModifiers, PopBack) {
  s21::list<std::string> basic;
  std::string element = "this";
  std::string element2 = "test";
  std::string element3 = "!!!";
  std::string element4 = "&";
  basic.push_front(element);
  basic.push_front(element2);
  basic.push_front(element3);
  basic.push_front(element4);
  basic.pop_back();
  EXPECT_TRUE(basic.size() == 3);
  EXPECT_EQ(basic.back(), element2);
  EXPECT_EQ(basic.front(), element4);
}

TEST(ListModifiers, Swap) {
  s21::list<std::string> basic({"1", "2", "3"});
  EXPECT_EQ(basic.front(), "1");
  s21::list<std::string> basic2({"this", "test"});
  EXPECT_EQ(basic2.front(), "this");
  basic.swap(basic2);
  EXPECT_EQ(basic.front(), "this");
  EXPECT_EQ(basic2.front(), "1");
}

TEST(ListConstructors, MoveAssignmentOperator) {
  s21::list<std::string> basic;
  s21::list<std::string> basic2({"this", "test", "is", "great!"});
  basic = std::move(basic2);
  EXPECT_EQ(basic.front(), "this");
  EXPECT_EQ(basic.back(), "great!");
  EXPECT_TRUE(basic2.empty());
}

TEST(ListConstructors, MoveConstructor) {
  s21::list<std::string> basic({"this", "test", "is", "great!"});
  s21::list<std::string> basic2(std::move(basic));
  EXPECT_EQ(basic2.front(), "this");
  EXPECT_EQ(basic2.back(), "great!");
  EXPECT_TRUE(basic.empty());
}

TEST(ListModifiers, IterIterator1) {
  s21::list<std::string> basic = {"this", "test", "is", "great!"};
  s21::list<std::string>::iterator it(basic.begin());
  EXPECT_EQ(*it, "this");
}

TEST(ListModifiers, IterIterator2) {
  s21::list<std::string> basic = {"this", "test", "is", "great!"};
  s21::list<std::string>::iterator it(basic.begin());
  EXPECT_EQ(*it++, "test");
}

TEST(ListModifiers, IterIterator3) {
  s21::list<std::string> basic = {"this", "test", "is", "great!"};
  s21::list<std::string>::iterator it(basic.end());
  EXPECT_EQ(*it++, "this");
}

TEST(ListModifiers, IterIterator4) {
  s21::list<std::string> basic = {"this", "test", "is", "great!"};
  s21::list<std::string>::iterator it(basic.begin());
  it++;
  it++;
  it++;
  EXPECT_EQ(*it, "great!");
}

TEST(ListModifiers, IterIterator5) {
  s21::list<std::string> basic = {"this", "test", "is", "great!"};
  s21::list<std::string>::iterator it(basic.begin());
  it++;
  it++;
  it++;
  it++;
  EXPECT_EQ(*it, "");
}

TEST(ListModifiers, IterIterator6) {
  s21::list<std::string> basic = {"this", "test", "is", "great!"};
  s21::list<std::string>::iterator it(basic.begin());
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, "this");
}

TEST(ListOperations, Unique) {
  s21::list<std::string> basic2 = {"this", "this", "test", "is", "great!"};
  basic2.unique();
  EXPECT_EQ(basic2.front(), "this");
  s21::list<std::string>::iterator it(basic2.begin());
  EXPECT_EQ(*it++, "test");
}

TEST(ListModifiers, Erase) {
  s21::list<std::string> basic2 = {"this", "test", "is", "great!"};
  auto it(basic2.begin());
  EXPECT_EQ(basic2.front(), "this");
  basic2.erase(it);
  EXPECT_EQ(basic2.front(), "test");
}

TEST(ListOperations, SpliceEq) {
  s21::list<std::string> basic = {"this", "test"};
  s21::list<std::string> basic2 = {"is", "great!"};
  s21::list<std::string>::const_iterator it;
  it = basic.begin();
  basic.splice(it, basic2);
  EXPECT_EQ(basic.front(), "is");
  EXPECT_EQ(basic.back(), "test");
  EXPECT_EQ(*it, "this");
  EXPECT_EQ(*it++, "test");
}

TEST(ListOperations, SpliceSecondEmpty) {
  s21::list<std::string> basic = {"this", "test"};
  s21::list<std::string> basic2 = {"is", "great!"};
  s21::list<std::string>::iterator it2(basic.begin());
  s21::list<std::string>::const_iterator it(it2.current);
  basic.splice(it++, basic2);
  it = basic.begin();
  EXPECT_EQ(*it++, "is");
  EXPECT_EQ(*it++, "great!");
  EXPECT_EQ(basic.front(), "this");
  EXPECT_EQ(basic.back(), "test");
}

TEST(ListOperations, SpliceBothEmpty) {
  s21::list<std::string> basic = {"this", "test"};
  s21::list<std::string> basic2 = {"is", "great!"};
  s21::list<std::string>::const_iterator it = basic.end();
  basic.splice(it, basic2);
  EXPECT_EQ(basic.front(), "this");
  EXPECT_EQ(basic.back(), "great!");
}

TEST(ListOperations, ReverseInitList) {
  s21::list<std::string> basic2 = {"this", "test", "is", "great!"};
  EXPECT_EQ(basic2.front(), "this");
  basic2.reverse();
  EXPECT_EQ(basic2.front(), "great!");
  auto it = basic2.begin();
  EXPECT_EQ(*it, "great!");
  EXPECT_EQ(*it--, "");
  EXPECT_EQ(*it--, "this");
}

TEST(ListOperations, ReverseEmpty) {
  s21::list<std::string> basic2;
  EXPECT_TRUE(basic2.empty());
  basic2.reverse();
  EXPECT_TRUE(basic2.empty());
}

TEST(ListOperations, ReverseSize) {
  s21::list<std::string> basic2({"1"});
  EXPECT_EQ(basic2.front(), "1");
  basic2.reverse();
  EXPECT_EQ(basic2.front(), "1");
}

TEST(ListOperations, ReverseCheckOne) {
  s21::list<int> basic2({1, 2, 3, 12312312, 100500});
  EXPECT_EQ(basic2.front(), 1);
  basic2.reverse();
  EXPECT_EQ(basic2.front(), 100500);
}

TEST(ListOperations, Sort) {
  s21::list<std::string> basic({"this", "test", "is", "great!"});
  EXPECT_EQ(basic.front(), "this");
  basic.sort();
  EXPECT_EQ(basic.front(), "great!");
  std::list<std::string> basic2({"this", "test", "is", "great!"});
  EXPECT_EQ(basic2.front(), "this");
  basic2.sort();
  EXPECT_EQ(basic2.front(), "great!");
}

TEST(ListOperations, MergeEq) {
  s21::list<int> basic(
      {-100, 12321, 123, -5124, 13, 0, -111, 17, 5125, 41349394, -31423434, 2});
  s21::list<int> basic2({1000000000, -1000000000});
  basic.sort();
  basic2.sort();
  basic.merge(basic2);
  EXPECT_EQ(basic.front(), -1000000000);
  EXPECT_EQ(basic.back(), 1000000000);
  EXPECT_TRUE(basic2.empty());
}

TEST(ListOperations, MergeSecondLess) {
  std::list<int> basic;
  std::list<int> basic2({1000000000, -1000000000});
  basic.sort();
  basic2.sort();
  basic.merge(basic2);
  EXPECT_EQ(basic.front(), -1000000000);
  EXPECT_EQ(basic.back(), 1000000000);
  EXPECT_TRUE(basic2.empty());
}

TEST(ListOperations, MergeFirstLess) {
  s21::list<int> basic;
  s21::list<int> basic2({1000000000, -1000000000});
  basic.sort();
  basic2.sort();
  basic.merge(basic2);
  EXPECT_EQ(basic.front(), -1000000000);
  EXPECT_EQ(basic.back(), 1000000000);
  EXPECT_TRUE(basic2.empty());
}

TEST(ListCapacity, MaxSize) {
  std::list<std::string> basic2({"this", "test", "is", "great!"});
  s21::list<std::string> basic({"this", "test", "is", "great!"});
  EXPECT_EQ(basic2.max_size(), basic.max_size());
}

// ---------BONUS-----------

TEST(ListBonus, InsertManyBack) {
  s21::list<int> my_list = {1, 2, 3};
  my_list.insert_many_back(4, 5);
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListBonus, InsertManyFront) {
  s21::list<int> my_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  EXPECT_TRUE(CompareLists(my_list, std_list));
}

TEST(ListBonus, InsertMany) {
  s21::list<int> my_list = {1, 2, 3};
  std::list<int> std_list = {4, 5, 6, 1, 2, 3};
  my_list.insert_many(my_list.begin(), 4, 5, 6);
  EXPECT_TRUE(CompareLists(my_list, std_list));
}
