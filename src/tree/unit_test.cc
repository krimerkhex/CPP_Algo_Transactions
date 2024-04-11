#include <self_balancing_binary_search_tree.h>

#include "gtest/gtest.h"

class TreeTest : public testing::Test {
 protected:
  s21::Record empty;
  s21::SelfBalancingBinarySearchTree tableWithoutTime;
  s21::SelfBalancingBinarySearchTree tableWithTime;
  s21::SelfBalancingBinarySearchTree tableCompinate;
};

TEST_F(TreeTest, ImportWithTest) {
  std::cout << "TREE TEST STARTED" << std::endl;
  EXPECT_NE(0, tableWithTime.upload("../../datasets/withtime.txt"));
  tableWithTime.showall();
}

TEST_F(TreeTest, ImportWithoutTest) {
  EXPECT_NE(0, tableWithoutTime.upload("../../datasets/withouttime.txt"));
  tableWithoutTime.showall();
}

TEST_F(TreeTest, ImportCombinateTest) {
  EXPECT_NE(0, tableCompinate.upload("../../datasets/combinate.txt"));
  tableCompinate.showall();
}

TEST_F(TreeTest, ShowAllTest) {
  tableWithTime.showall();
  EXPECT_EQ(tableWithTime.getSize(), tableWithTime.keys().size());
  tableCompinate.showall();
  EXPECT_EQ(tableCompinate.getSize(), tableCompinate.keys().size());
  tableWithoutTime.showall();
  EXPECT_EQ(tableWithoutTime.getSize(), tableWithoutTime.keys().size());
}

TEST_F(TreeTest, ExportWithTest) {
  tableWithTime.upload("../../datasets/import_withtime.txt");
  tableWithTime.showall();
  std::cout << tableWithTime.end()->first << std::endl;
  EXPECT_EQ(tableWithTime.getSize(),
            tableWithTime.exportt("../../datasets/ex_withtime.txt"));
}

TEST_F(TreeTest, ExportWithoutTest) {
  tableWithoutTime.upload("../../datasets/import_withouttime.txt");
  tableWithoutTime.showall();
  EXPECT_EQ(tableWithoutTime.getSize(),
            tableWithoutTime.exportt("../../datasets/ex_withouttime.txt"));
}

TEST_F(TreeTest, ExportCombinateTest) {
  tableCompinate.upload("../../datasets/import_combinate.txt");
  tableCompinate.showall();
  EXPECT_EQ(tableCompinate.getSize(),
            tableCompinate.exportt("../../datasets/ex_combinate.txt"));
}

TEST_F(TreeTest, SetTestWith) {
  EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableWithTime.set("foo", "a", "j", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableWithTime.set("boo", "a", "j", 3, "c", 1, 100));
  tableWithTime.showall();
}

TEST_F(TreeTest, SetTestWithout) {
  EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableWithoutTime.set("foo", "a", "j", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithoutTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableWithoutTime.set("boo", "a", "j", 3, "c", 1, 100));
}

TEST_F(TreeTest, SetTestComb) {
  EXPECT_EQ(1, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableCompinate.set("foo", "a", "j", 3, "c", 1, 100));
  EXPECT_EQ(1, tableCompinate.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableCompinate.set("boo", "a", "j", 3, "c", 1, 100));
}

TEST_F(TreeTest, GetTestWith) {
  EXPECT_NE(false, tableWithTime.get("foo") == empty);
  EXPECT_NE(false, tableWithTime.get("boo") == empty);
  std::cout << "f00oo " << tableWithTime.get("f00oo") << std::endl;
  std::cout << "b00oo " << tableWithTime.get("b00oo") << std::endl;
  EXPECT_EQ(true, tableWithTime.get("f00oo") == empty);
  EXPECT_EQ(true, tableWithTime.get("b00oo") == empty);
}

TEST_F(TreeTest, GetTestWithout) {
  EXPECT_NE(false, tableWithoutTime.get("foo") == empty);
  EXPECT_NE(false, tableWithoutTime.get("boo") == empty);
  std::cout << "fofebefbo " << tableWithTime.get("fofebefbo") << std::endl;
  std::cout << "boebefbo " << tableWithTime.get("boebefbo") << std::endl;
  EXPECT_EQ(true, tableWithTime.get("fofebefbo") == empty);
  EXPECT_EQ(true, tableWithTime.get("boebefbo") == empty);
}

TEST_F(TreeTest, GetTestComb) {
  EXPECT_NE(false, tableCompinate.get("foo") == empty);
  EXPECT_NE(false, tableCompinate.get("boo") == empty);
  std::cout << "foqefqefqo " << tableWithTime.get("foqefqefqo") << std::endl;
  std::cout << "boeqfqefo " << tableWithTime.get("boeqfqefo") << std::endl;
  EXPECT_EQ(true, tableWithTime.get("foqefqefqo") == empty);
  EXPECT_EQ(true, tableWithTime.get("boeqfqefo") == empty);
}

TEST_F(TreeTest, ExistsTestWith) {
  EXPECT_EQ(false, tableWithTime.exists("foefego"));
  EXPECT_EQ(false, tableWithTime.exists("boqergeo"));
  EXPECT_EQ(false, tableWithTime.exists("foo"));
  EXPECT_EQ(false, tableWithTime.exists("boo"));
  EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableWithTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(false, tableWithTime.exists("foefego"));
  EXPECT_EQ(false, tableWithTime.exists("boqergeo"));
  EXPECT_EQ(true, tableWithTime.exists("foo"));
  EXPECT_EQ(true, tableWithTime.exists("boo"));
}

TEST_F(TreeTest, ExistsTestWithout) {
  EXPECT_EQ(false, tableWithoutTime.exists("foo"));
  EXPECT_EQ(false, tableWithoutTime.exists("boo"));
  EXPECT_EQ(false, tableWithTime.exists("fofebefbo"));
  EXPECT_EQ(false, tableWithTime.exists("boebefbo"));
  EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithoutTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableWithoutTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(true, tableWithoutTime.exists("foo"));
  EXPECT_EQ(true, tableWithoutTime.exists("boo"));
  EXPECT_EQ(false, tableWithTime.exists("fofebefbo"));
  EXPECT_EQ(false, tableWithTime.exists("boebefbo"));
}

TEST_F(TreeTest, ExistsTestComb) {
  EXPECT_EQ(false, tableCompinate.exists("foo"));
  EXPECT_EQ(false, tableCompinate.exists("boo"));
  EXPECT_EQ(false, tableCompinate.exists("foqefqefqo"));
  EXPECT_EQ(false, tableCompinate.exists("boeqfqefo"));
  EXPECT_EQ(1, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableCompinate.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(0, tableCompinate.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableCompinate.set("gog", "a", "b", 3, "c", 1));
  EXPECT_EQ(0, tableCompinate.set("foo", "a", "b", 3, "c", 1));
  EXPECT_EQ(1, tableCompinate.set("yoy", "a", "b", 3, "c", 1));
  EXPECT_EQ(0, tableCompinate.set("boo", "a", "b", 3, "c", 1));
  EXPECT_EQ(true, tableCompinate.exists("foo"));
  EXPECT_EQ(true, tableCompinate.exists("boo"));
  EXPECT_EQ(true, tableCompinate.exists("gog"));
  EXPECT_EQ(true, tableCompinate.exists("yoy"));
  EXPECT_EQ(false, tableCompinate.exists("foqefqefqo"));
  EXPECT_EQ(false, tableCompinate.exists("boeqfqefo"));
}

TEST_F(TreeTest, DelTestWith) {
  EXPECT_EQ(false, tableWithTime.exists("foo"));
  EXPECT_EQ(false, tableWithTime.exists("boo"));
  EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(true, tableWithTime.del("foo"));
  EXPECT_EQ(true, tableWithTime.del("boo"));
  EXPECT_EQ(false, tableWithTime.exists("foo"));
  EXPECT_EQ(false, tableWithTime.exists("boo"));
}

TEST_F(TreeTest, DelTestWithout) {
  EXPECT_EQ(false, tableWithoutTime.exists("foo"));
  EXPECT_EQ(false, tableWithoutTime.exists("boo"));
  EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithoutTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(true, tableWithoutTime.del("foo"));
  EXPECT_EQ(true, tableWithoutTime.del("boo"));
  EXPECT_EQ(false, tableWithoutTime.exists("foo"));
  EXPECT_EQ(false, tableWithoutTime.exists("boo"));
}

TEST_F(TreeTest, DelTestComb) {
  EXPECT_EQ(false, tableCompinate.exists("foo"));
  EXPECT_EQ(false, tableCompinate.exists("boo"));
  EXPECT_EQ(1, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableCompinate.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(true, tableCompinate.del("foo"));
  EXPECT_EQ(true, tableCompinate.del("boo"));
  EXPECT_EQ(false, tableCompinate.exists("foo"));
  EXPECT_EQ(false, tableCompinate.exists("boo"));
}

TEST_F(TreeTest, UpdateTestWith) {
  s21::Record temp("aqefqf", "bqefqef", 30000, "cegg", 100);
  EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1));
  EXPECT_EQ(true, tableWithTime.update("foo", "aqefqf", "bqefqef", 30000,
                                       "cegg", 100));
  EXPECT_TRUE(temp == tableWithTime.get("foo"));
}

TEST_F(TreeTest, UpdateTestWithout) {
  s21::Record temp("aqefqf", "bqefqef", 30000, "cegg", 100);
  EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(true, tableWithoutTime.update("foo", "aqefqf", "bqefqef", 30000,
                                          "cegg", 100));
  EXPECT_TRUE(temp == tableWithoutTime.get("foo"));
}

TEST_F(TreeTest, KeysTestWith) {
  EXPECT_EQ(tableWithTime.getSize(), tableWithTime.keys().size());
}

TEST_F(TreeTest, KeysTestWithout) {
  EXPECT_EQ(tableCompinate.getSize(), tableCompinate.keys().size());
}

TEST_F(TreeTest, KeysTestComb) {
  EXPECT_EQ(tableWithoutTime.getSize(), tableWithoutTime.keys().size());
}

TEST_F(TreeTest, RenameTestWith) {
  EXPECT_EQ(false, tableWithTime.exists("foo"));
  EXPECT_EQ(false, tableWithTime.exists("boo"));
  EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithTime.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(true, tableWithTime.exists("foo"));
  EXPECT_EQ(true, tableWithTime.exists("boo"));
  EXPECT_EQ(true, tableWithTime.rename("foo", "foo2"));
  EXPECT_EQ(true, tableWithTime.rename("boo", "boo2"));
  EXPECT_EQ(false, tableWithTime.exists("foo"));
  EXPECT_EQ(false, tableWithTime.exists("boo"));
  EXPECT_TRUE(tableWithTime.get("foo2") == tableWithTime.get("boo2"));
}

TEST_F(TreeTest, RenameTestWithout) {
  EXPECT_EQ(false, tableWithoutTime.exists("foo"));
  EXPECT_EQ(false, tableWithoutTime.exists("boo"));
  EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1));
  EXPECT_EQ(1, tableWithoutTime.set("boo", "a", "b", 3, "c", 1));
  EXPECT_EQ(true, tableWithoutTime.exists("foo"));
  EXPECT_EQ(true, tableWithoutTime.exists("boo"));
  EXPECT_EQ(true, tableWithoutTime.rename("foo", "foo2"));
  EXPECT_EQ(true, tableWithoutTime.rename("boo", "boo2"));
  EXPECT_EQ(false, tableWithoutTime.exists("foo"));
  EXPECT_EQ(false, tableWithoutTime.exists("boo"));
  EXPECT_TRUE(tableWithoutTime.get("foo2") == tableWithoutTime.get("boo2"));
}

TEST_F(TreeTest, RenameTestComb) {
  EXPECT_EQ(false, tableCompinate.exists("foo"));
  EXPECT_EQ(false, tableCompinate.exists("boo"));
  EXPECT_EQ(1, tableCompinate.set("foo", "a", "b", 3, "c", 1));
  EXPECT_EQ(1, tableCompinate.set("boo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(true, tableCompinate.exists("foo"));
  EXPECT_EQ(true, tableCompinate.exists("boo"));
  EXPECT_EQ(true, tableCompinate.rename("foo", "foo2"));
  EXPECT_EQ(true, tableCompinate.rename("boo", "boo2"));
  EXPECT_EQ(false, tableCompinate.exists("foo"));
  EXPECT_EQ(false, tableCompinate.exists("boo"));
  std::cout << "foo2" << tableCompinate.get("foo2") << std::endl;
  std::cout << "boo2" << tableCompinate.get("boo2") << std::endl;
  EXPECT_TRUE(tableCompinate.get("foo2") == tableCompinate.get("boo2"));
}

TEST_F(TreeTest, TTLTestWith) {
  for (const auto &it : tableCompinate.keys()) {
    EXPECT_TRUE((tableCompinate.ttl(it) > 0) ==
                !(tableCompinate.get(it).getConstans()));
  }
}

TEST_F(TreeTest, FindTestWith) {
  EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithTime.set("boo", "ab", "bc", 34, "cd", 12, 100));
  EXPECT_TRUE("boo" == tableWithTime.find("ab", "bc", 34, "cd", 12)[0]);
  EXPECT_TRUE("foo" == tableWithTime.find("a", "b", 3, "c", 1)[0]);
  EXPECT_TRUE(tableWithTime.keys() ==
              tableWithTime.find("-", "-", '-', "-", '-'));
}

TEST_F(TreeTest, FindTestWithout) {
  EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableWithoutTime.set("boo", "ab", "bc", 34, "cd", 12, 100));
  EXPECT_TRUE("boo" == tableWithoutTime.find("ab", "bc", 34, "cd", 12)[0]);
  EXPECT_TRUE("foo" == tableWithoutTime.find("a", "b", 3, "c", 1)[0]);
  EXPECT_TRUE(tableWithoutTime.keys() ==
              tableWithoutTime.find("-", "-", '-', "-", '-'));
}

TEST_F(TreeTest, FindTestComb) {
  EXPECT_EQ(1, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
  EXPECT_EQ(1, tableCompinate.set("boo", "ab", "bc", 34, "cd", 12, 100));
  EXPECT_TRUE("foo" == tableCompinate.find("a", "b", 3, "c", 1)[0]);
  EXPECT_TRUE("boo" == tableCompinate.find("ab", "bc", 34, "cd", 12)[0]);
  EXPECT_TRUE(tableCompinate.keys() ==
              tableCompinate.find("-", "-", '-', "-", '-'));
  std::cout << "TREE TEST ENDED" << std::endl;
}

TEST_F(TreeTest, TimeSinhroCheck) {
  tableCompinate.upload("../../datasets/import_combinate.txt");
  tableCompinate.showall();
  std::cout << "\n\nOn start: " << tableCompinate.getSize() << "\n\n"
            << std::endl;
  Sleep((6000));
  tableCompinate.showall();
  std::cout << "\n\n1 min later(60): " << tableCompinate.getSize() << "\n\n"
            << std::endl;
  Sleep((7000));
  tableCompinate.showall();
  std::cout << "\n\n1 min later(70): " << tableCompinate.getSize() << "\n\n"
            << std::endl;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
