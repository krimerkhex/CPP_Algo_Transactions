#ifndef SRC_TREE_SELF_BALANCING_BINARY_SEARCH_TREE_H
#define SRC_TREE_SELF_BALANCING_BINARY_SEARCH_TREE_H

#include "../abstract_class/methods.h"
#include "s21_map.h"

namespace s21 {
class SelfBalancingBinarySearchTree : public Methods, public Map {
 public:
  SelfBalancingBinarySearchTree();
  SelfBalancingBinarySearchTree(const SelfBalancingBinarySearchTree &other);
  SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree &&other) noexcept;
  SelfBalancingBinarySearchTree &operator=(
      const SelfBalancingBinarySearchTree &other);
  SelfBalancingBinarySearchTree &operator=(
      SelfBalancingBinarySearchTree &&other) noexcept;

  bool set(std::string key, std::string lastName, std::string firstName,
           unsigned year, std::string city, unsigned coins,
           double seconds) override;
  bool set(std::string key, std::string lastName, std::string firstName,
           unsigned year, std::string city, unsigned coins) override;
  Record get(std::string key) override;
  bool exists(std::string key) override;
  bool del(std::string key) override;
  bool update(std::string key, std::string lastName, std::string firstName,
              unsigned year, std::string city, unsigned coins) override;
  std::vector<std::string> keys() override;
  bool rename(std::string src, std::string dest) override;
  double ttl(std::string key) override;
  std::vector<std::string> find(std::string lastName, std::string firstName,
                                unsigned year, std::string city,
                                unsigned coins) override;
  void showall() override;
  long long unsigned upload(std::string filepath) override;
  long long unsigned exportt(std::string filepath) override;

  unsigned getSize();

 private:
  double currentTime_;
  bool set(const std::string &key, const Record &value);
  void checkAllStruct() override;
  void copy(const SelfBalancingBinarySearchTree &other);
  void move(SelfBalancingBinarySearchTree &other);
  void updateTime() override;
};
}  // namespace s21

#endif  // SRC_TREE_SELF_BALANCING_BINARY_SEARCH_TREE_H
