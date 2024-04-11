WWW = -Wall -Wextra -lstdc++ -std=c++17
LIBS = -lgtest
FILES = console.cc hash_table.a self_balancing_binary_search_tree.a
TABLEFILES = hash_table/hash_table.cc record/record.cc
#TREEFILES = tree/self_balancing_binary_search_tree.cc tree/s21_map.cc tree/s21_map_main.cc tree/s21_map_support.cc tree/map_iterator.cc tree/map_node.cc record/record.cc
TREEFILES = tree/self_balancing_binary_search_tree.cc tree/s21_map.cc record/record.cc

all: hash_table.a self_balancing_binary_search_tree.a
	g++ $(WWW) $(FILES) -o application
	./application

run:
	./application

tests: hash_table.a self_balancing_binary_search_tree.a
	g++ $(WWW) -lgtest hash_table/unit_test.cc hash_table.a -o hash_test
	g++ $(WWW) -lgtest self_balancing_binary_search_tree.a tree/unit_test.cc -o tree_test
	./hash_test
	./tree_test

clean:
#	rm -rf *.a
#	rm -rf *.o
#	rm -rf tree_test
#	rm -rf hash_test
#   rm -rf application
	del *.a
	del *.o
	del tree_test
	del hash_test
	del application.exe

hash_table.a:
	g++ $(WWW) -c $(TABLEFILES)
	ar rcs hash_table.a hash_table.o record.o
	ranlib hash_table.a

self_balancing_binary_search_tree.a:
	g++ $(WWW) -c $(TREEFILES)
	ar rcs self_balancing_binary_search_tree.a self_balancing_binary_search_tree.o record.o s21_map.o
	ranlib self_balancing_binary_search_tree.a

sbbst.a: self_balancing_binary_search_tree.a
