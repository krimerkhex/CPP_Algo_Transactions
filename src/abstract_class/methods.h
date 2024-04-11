#ifndef SRC_ABSTRACT_CLASS_METHODS_H
#define SRC_ABSTRACT_CLASS_METHODS_H

#include "../record/record.h"

namespace s21 {
class Methods {
 public:
  virtual ~Methods() = default;
  ;

  virtual bool set(std::string key, std::string lastName, std::string firstName,
                   unsigned year, std::string city, unsigned coins,
                   double seconds) = 0;

  virtual bool set(std::string key, std::string lastName, std::string firstName,
                   unsigned year, std::string city, unsigned coins) = 0;

  virtual Record get(std::string key) = 0;

  virtual bool exists(std::string key) = 0;

  virtual bool del(std::string key) = 0;

  virtual bool update(std::string key, std::string lastName,
                      std::string firstName, unsigned year, std::string city,
                      unsigned coins) = 0;

  virtual std::vector<std::string> keys() = 0;

  virtual bool rename(std::string src, std::string dest) = 0;

  virtual double ttl(std::string key) = 0;

  virtual std::vector<std::string> find(std::string lastName,
                                        std::string firstName, unsigned year,
                                        std::string city, unsigned coins) = 0;

  virtual void showall() = 0;

  virtual long long unsigned upload(std::string filepath) = 0;

  virtual long long unsigned exportt(std::string filepath) = 0;

  virtual void updateTime() = 0;

  virtual void checkAllStruct() = 0;
};

}  // namespace s21

#endif  // SRC_ABSTRACT_CLASS_METHODS_H
