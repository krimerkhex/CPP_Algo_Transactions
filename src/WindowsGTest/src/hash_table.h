#ifndef SRC_HASH_TABLE_H
#define SRC_HASH_TABLE_H

#include "methods.h"

namespace s21 {
class HashTable : Methods {
 public:
  HashTable();
  HashTable(const HashTable &other);
  HashTable(HashTable &&other) noexcept;
  HashTable &operator=(const HashTable &other);
  HashTable &operator=(HashTable &&other) noexcept;
  ~HashTable();

  unsigned getSize() const;

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

 private:
  std::vector<std::list<std::pair<std::string, Record>>> data_;
  unsigned size_;
  unsigned copasity_;
  double currentTime_;
  void updateTime() override;
  int hash(const std::string &key) const;
  void copy(const HashTable &other);
  void move(HashTable &other);
  void resize();
  void createDataStructs();
  void deleteDataStructs();
  void checkAllStruct() override;
  bool set(std::string key, Record value);
  Record *find(const std::string &key);
};
}  // namespace s21

#endif  // SRC_HASH_TABLE_H
