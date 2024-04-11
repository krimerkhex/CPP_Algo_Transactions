#include <hash_table.h>

#include "windows.h"
#include "gtest/gtest.h"

class HashTest : public testing::Test {
protected:
    s21::Record empty;
    s21::HashTable tableWithoutTime;
    s21::HashTable tableWithTime;
    s21::HashTable tableCompinate;
};

TEST_F(HashTest, ImportWithTest) {
    std::cout << "HASHTABLE TEST STARTED" << std::endl;
    EXPECT_NE(0, tableWithTime.upload("C:\\Doing_somethings\\School_21\\A6_"
                                      "Transactions-1\\datasets\\withtime.txt"));
    tableWithTime.showall();
}

TEST_F(HashTest, ImportWithoutTest) {
    EXPECT_NE(
            0, tableWithoutTime.upload("C:\\Doing_somethings\\School_21\\A6_"
                                       "Transactions-1\\datasets\\withouttime.txt"));
    tableWithoutTime.showall();
}

TEST_F(HashTest, ImportCombinateTest) {
    EXPECT_NE(0,
              tableCompinate.upload("C:\\Doing_somethings\\School_21\\A6_"
                                    "Transactions-1\\datasets\\combinate.txt"));
    tableCompinate.showall();
}

TEST_F(HashTest, ShowAllTest) {
    tableWithTime.upload(
            "C:\\Doing_somethings\\School_21\\A6_Transactions-1\\datasets\\withtime."
            "txt");
    tableWithoutTime.upload(
            "C:\\Doing_somethings\\School_21\\A6_Transactions-"
            "1\\datasets\\withouttime.txt");
    tableCompinate.upload(
            "C:\\Doing_somethings\\School_21\\A6_Transactions-1\\datasets\\combinate."
            "txt");
    tableWithTime.showall();
    EXPECT_EQ(tableWithTime.getSize(), tableWithTime.keys().size());
    tableCompinate.showall();
    EXPECT_EQ(tableCompinate.getSize(), tableCompinate.keys().size());
    tableWithoutTime.showall();
    EXPECT_EQ(tableWithoutTime.getSize(), tableWithoutTime.keys().size());
}

TEST_F(HashTest, ExportWithTest) {
    tableWithTime.upload(
            "C:\\Doing_somethings\\School_21\\A6_Transactions-1\\datasets\\import_"
            "withtime.txt");
    EXPECT_EQ(tableWithTime.getSize(),
              tableWithTime.exportt("C:\\Doing_somethings\\School_21\\A6_"
                                    "Transactions-1\\datasets\\ex_withtime.txt"));
}

TEST_F(HashTest, ExportWithoutTest) {
    tableWithoutTime.upload(
            "C:\\Doing_somethings\\School_21\\A6_Transactions-1\\datasets\\import_"
            "withouttime.txt");
    EXPECT_EQ(
            tableWithoutTime.getSize(),
            tableWithoutTime.exportt("C:\\Doing_somethings\\School_21\\A6_"
                                     "Transactions-1\\datasets\\ex_withouttime.txt"));
}

TEST_F(HashTest, ExportCombinateTest) {
    tableCompinate.upload(
            "C:\\Doing_somethings\\School_21\\A6_Transactions-1\\datasets\\import_"
            "combinate.txt");
    EXPECT_EQ(
            tableCompinate.getSize(),
            tableCompinate.exportt("C:\\Doing_somethings\\School_21\\A6_Transactions-"
                                   "1\\datasets\\ex_combinate.txt"));
}

TEST_F(HashTest, SetTestWith) {
    EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(0, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableWithTime.set("boo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(0, tableWithTime.set("boo", "a", "b", 3, "c", 1, 100));
}

TEST_F(HashTest, SetTestWithout) {
    EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(0, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableWithoutTime.set("boo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(0, tableWithoutTime.set("boo", "a", "b", 3, "c", 1, 100));
}

TEST_F(HashTest, SetTestComb) {
    EXPECT_EQ(1, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(0, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableCompinate.set("boo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(0, tableCompinate.set("boo", "a", "b", 3, "c", 1, 100));
}

TEST_F(HashTest, GetTestWith) {
    EXPECT_NE(0, tableWithTime.get("foo") == empty);
    EXPECT_NE(0, tableWithTime.get("boo") == empty);
    EXPECT_EQ(true, tableWithTime.get("f00oo") == empty);
    EXPECT_EQ(true, tableWithTime.get("b00oo") == empty);
}

TEST_F(HashTest, GetTestWithout) {
    EXPECT_NE(0, tableWithoutTime.get("foo") == empty);
    EXPECT_NE(0, tableWithoutTime.get("boo") == empty);
    EXPECT_EQ(true, tableWithTime.get("fofebefbo") == empty);
    EXPECT_EQ(true, tableWithTime.get("boebefbo") == empty);
}

TEST_F(HashTest, GetTestComb) {
    EXPECT_NE(0, tableCompinate.get("foo") == empty);
    EXPECT_NE(0, tableCompinate.get("boo") == empty);
    EXPECT_EQ(true, tableWithTime.get("foqefqefqo") == empty);
    EXPECT_EQ(true, tableWithTime.get("boeqfqefo") == empty);
}

TEST_F(HashTest, ExistsTestWith) {
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

TEST_F(HashTest, ExistsTestWithout) {
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

TEST_F(HashTest, ExistsTestComb) {
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

TEST_F(HashTest, DelTestWith) {
    EXPECT_EQ(false, tableWithTime.exists("foo"));
    EXPECT_EQ(false, tableWithTime.exists("boo"));
    EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableWithTime.set("boo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(true, tableWithTime.del("foo"));
    EXPECT_EQ(true, tableWithTime.del("boo"));
    EXPECT_EQ(false, tableWithTime.exists("foo"));
    EXPECT_EQ(false, tableWithTime.exists("boo"));
}

TEST_F(HashTest, DelTestWithout) {
    EXPECT_EQ(false, tableWithoutTime.exists("foo"));
    EXPECT_EQ(false, tableWithoutTime.exists("boo"));
    EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableWithoutTime.set("boo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(true, tableWithoutTime.del("foo"));
    EXPECT_EQ(true, tableWithoutTime.del("boo"));
    EXPECT_EQ(false, tableWithoutTime.exists("foo"));
    EXPECT_EQ(false, tableWithoutTime.exists("boo"));
}

TEST_F(HashTest, DelTestComb) {
    EXPECT_EQ(false, tableCompinate.exists("foo"));
    EXPECT_EQ(false, tableCompinate.exists("boo"));
    EXPECT_EQ(1, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableCompinate.set("boo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(true, tableCompinate.del("foo"));
    EXPECT_EQ(true, tableCompinate.del("boo"));
    EXPECT_EQ(false, tableCompinate.exists("foo"));
    EXPECT_EQ(false, tableCompinate.exists("boo"));
}

TEST_F(HashTest, UpdateTestWith) {
    s21::Record temp("aqefqf", "bqefqef", 30000, "cegg", 100);
    EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1));
    EXPECT_EQ(true, tableWithTime.update("foo", "aqefqf", "bqefqef", 30000,
                                         "cegg", 100));
    EXPECT_TRUE(temp == tableWithTime.get("foo"));
}

TEST_F(HashTest, UpdateTestWithout) {
    s21::Record temp("aqefqf", "bqefqef", 30000, "cegg", 100);
    EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(true, tableWithoutTime.update("foo", "aqefqf", "bqefqef", 30000,
                                            "cegg", 100));
    EXPECT_TRUE(temp == tableWithoutTime.get("foo"));
}

TEST_F(HashTest, KeysTestWith) {
    EXPECT_EQ(tableWithTime.getSize(), tableWithTime.keys().size());
}

TEST_F(HashTest, KeysTestWithout) {
    EXPECT_EQ(tableCompinate.getSize(), tableCompinate.keys().size());
}

TEST_F(HashTest, KeysTestComb) {
    EXPECT_EQ(tableWithoutTime.getSize(), tableWithoutTime.keys().size());
}

TEST_F(HashTest, RenameTestWith) {
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

TEST_F(HashTest, RenameTestWithout) {
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

TEST_F(HashTest, RenameTestComb) {
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

TEST_F(HashTest, TTLTestWith) {
    for (const auto &it: tableCompinate.keys()) {
        EXPECT_TRUE((tableCompinate.ttl(it) > 0) ==
                    !(tableCompinate.get(it).getConstans()));
    }
}

TEST_F(HashTest, FindTestWith) {
    EXPECT_EQ(1, tableWithTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableWithTime.set("boo", "ab", "bc", 34, "cd", 12, 100));
    EXPECT_TRUE("foo" == tableWithTime.find("a", "b", 3, "c", 1)[0]);
    EXPECT_TRUE("boo" == tableWithTime.find("ab", "bc", 34, "cd", 12)[0]);
    EXPECT_TRUE(tableWithTime.keys() ==
                tableWithTime.find("-", "-", '-', "-", '-'));
}

TEST_F(HashTest, FindTestWithout) {
    EXPECT_EQ(1, tableWithoutTime.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableWithoutTime.set("boo", "ab", "bc", 34, "cd", 12, 100));
    EXPECT_TRUE("foo" == tableWithoutTime.find("a", "b", 3, "c", 1)[0]);
    EXPECT_TRUE("boo" == tableWithoutTime.find("ab", "bc", 34, "cd", 12)[0]);
    EXPECT_TRUE(tableWithoutTime.keys() ==
                tableWithoutTime.find("-", "-", '-', "-", '-'));
}

TEST_F(HashTest, FindTestComb) {
    EXPECT_EQ(1, tableCompinate.set("foo", "a", "b", 3, "c", 1, 100));
    EXPECT_EQ(1, tableCompinate.set("boo", "ab", "bc", 34, "cd", 12, 100));
    EXPECT_TRUE("foo" == tableCompinate.find("a", "b", 3, "c", 1)[0]);
    EXPECT_TRUE("boo" == tableCompinate.find("ab", "bc", 34, "cd", 12)[0]);
    EXPECT_TRUE(tableCompinate.keys() ==
                tableCompinate.find("-", "-", '-', "-", '-'));
    std::cout << "HASHTABLE TEST ENDED" << std::endl;
}

TEST_F(HashTest, TimeSinhroCheck) {
    tableCompinate.upload(
            "C:\\Doing_somethings\\School_21\\A6_Transactions-1\\datasets\\import_"
            "combinate.txt");
    tableCompinate.showall();
    std::cout << "\nOn start: " << tableCompinate.getSize() << "\n"
              << std::endl;
    Sleep((1000 * 60));
    tableCompinate.showall();
    std::cout << "\n1 min later(60): " << tableCompinate.getSize() << "\n"
              << std::endl;
    Sleep((6000 * 60));
    tableCompinate.showall();
    std::cout << "\n6 min later(360): " << tableCompinate.getSize() << "\n"
              << std::endl;
}
