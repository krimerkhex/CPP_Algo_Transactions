#ifndef SRC_RECORD_RECORD_H
#define SRC_RECORD_RECORD_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace s21 {
class Record {
 public:
  Record();
  Record(std::string lastName, std::string firstName, unsigned year,
         std::string city, unsigned coins);
  Record(std::string lastName, std::string firstName, unsigned year,
         std::string city, unsigned coins, double seconds, bool constant);
  Record(const Record &other);
  Record(Record &&other) noexcept;
  Record &operator=(const Record &other);
  Record &operator=(Record &&other) noexcept;
  ~Record() = default;

  std::string getLastName();
  std::string getFirstName();
  std::string getCity();
  unsigned getBirthYear() const;
  double getTTL() const;
  unsigned long long getCountCoins() const;
  bool getConstans() const;

  void setLastName(std::string lastName);
  void setFirstName(std::string firstName);
  void setCity(std::string city);
  void setBirthYear(unsigned year);
  void setCountCoins(unsigned long long count);
  void setTTL(double ttl);
  void show(const unsigned &counter) const;
  bool operator==(const Record &other) const;
  bool checkForPass(const Record &other) const;
  void clear();
  bool checkTime(double currentTime) const;
  friend std::ostream &operator<<(std::ostream &out, const Record &rec);
  static bool checkValidFunctionInput(const std::string &lastName,
                                      const std::string &firstName,
                                      unsigned year, const std::string &city,
                                      unsigned coins);
  void copyPass(const Record &other);

 private:
  std::string lastName_;
  std::string firstName_;
  unsigned year_;
  std::string city_;
  unsigned long long countCoins_;
  double ends_time_;
  bool constant_;

  void copy(const Record &other);
  void move(Record &other);
};
}  // namespace s21

#endif  // SRC_RECORD_RECORD_H
