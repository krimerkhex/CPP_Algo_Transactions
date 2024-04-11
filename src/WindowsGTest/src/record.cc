#include "methods.h"

namespace s21 {
Record::Record()
    : lastName_(""), firstName_(""), year_(0), city_(""), countCoins_(0) {
  constant_ = true;
  ends_time_ = 0;
}

Record::Record(std::string lastName, std::string firstName, unsigned year,
               std::string city, unsigned coins) {
  this->lastName_ = std::move(lastName);
  this->firstName_ = std::move(firstName);
  this->year_ = year;
  this->city_ = std::move(city);
  this->countCoins_ = coins;
  this->ends_time_ = 0;
  this->constant_ = true;
}

Record::Record(std::string lastName, std::string firstName, unsigned year,
               std::string city, unsigned coins, double seconds,
               bool constant) {
  this->lastName_ = std::move(lastName);
  this->firstName_ = std::move(firstName);
  this->year_ = year;
  this->city_ = std::move(city);
  this->countCoins_ = coins;
  this->ends_time_ = seconds;
  this->constant_ = constant;
}

Record::Record(const Record &other) : Record() { this->copy(other); }

Record::Record(Record &&other) noexcept { this->move(other); }

Record &Record::operator=(const Record &other) {
  if (this != &other) {
    this->copy(other);
  }
  return *this;
}

Record &Record::operator=(Record &&other) noexcept {
  if (this != &other) {
    this->move(other);
  }
  return *this;
}

void Record::copy(const Record &other) {
  this->lastName_ = other.lastName_;
  this->firstName_ = other.firstName_;
  this->year_ = other.year_;
  this->city_ = other.city_;
  this->countCoins_ = other.countCoins_;
  this->ends_time_ = other.ends_time_;
  this->constant_ = other.constant_;
}

void Record::move(Record &other) {
  copy(other);
  other.clear();
}

void Record::copyPass(const Record &other) {
  if (other.lastName_ != "-") {
    this->lastName_ = other.lastName_;
  }
  if (other.firstName_ != "-") {
    this->firstName_ = other.firstName_;
  }
  if (other.year_ != '-') {
    this->year_ = other.year_;
  }
  if (other.city_ != "-") {
    this->city_ = other.city_;
  }
  if (other.countCoins_ != '-') {
    this->countCoins_ = other.countCoins_;
  }
}

bool Record::getConstans() const { return this->constant_; }

bool Record::operator==(const Record &other) const {
  return (this->lastName_ == other.lastName_) &&
         (this->firstName_ == other.firstName_) &&
         (this->year_ == other.year_) && (this->city_ == other.city_) &&
         (this->countCoins_ == other.countCoins_);
}

bool Record::checkForPass(const Record &other) const {
  bool flag = true;
  if (other.lastName_ != "-") {
    flag = this->lastName_ == other.lastName_;
  }
  if (other.firstName_ != "-" && flag) {
    flag = this->firstName_ == other.firstName_;
  }
  if (other.year_ != '-' && flag) {
    flag = this->year_ == other.year_;
  }
  if (other.city_ != "-" && flag) {
    flag = this->city_ == other.city_;
  }
  if (other.countCoins_ != '-' && flag) {
    flag = this->countCoins_ == other.countCoins_;
  }
  return flag;
}

void Record::show(const unsigned &counter) const {
  std::cout << counter << " \"" << this->lastName_ << "\" "
            << " \"" << this->firstName_ << "\" "
            << " \"" << this->year_ << "\" "
            << " \"" << this->city_ << "\" "
            << " " << this->countCoins_ << " ";
}
void Record::clear() {
  lastName_.clear();
  firstName_.clear();
  city_.clear();
  year_ = countCoins_ = 0;
  ends_time_ = 0;
}

bool Record::checkTime(double currentTime) const {
  bool flag = this->constant_;
  if (!flag) {
    flag = (this->ends_time_ - currentTime) > 0;
  }
  return !flag;
}

std::string Record::getLastName() { return this->lastName_; }

std::string Record::getFirstName() { return this->firstName_; }
std::string Record::getCity() { return this->city_; }
unsigned Record::getBirthYear() const { return year_; }
double Record::getTTL() const { return ends_time_; }
unsigned long long Record::getCountCoins() const { return countCoins_; }

void Record::setLastName(std::string lastName) {
  this->lastName_ = std::move(lastName);
}
void Record::setFirstName(std::string firstName) {
  this->firstName_ = std::move(firstName);
}
void Record::setCity(std::string city) { this->city_ = std::move(city); }
void Record::setBirthYear(unsigned year) { this->year_ = year; }
void Record::setCountCoins(unsigned long long count) {
  this->countCoins_ = count;
}
void Record::setTTL(double ttl) { this->ends_time_ = ttl; }

std::ostream &operator<<(std::ostream &out, const Record &rec) {
  out << rec.lastName_ << " " << rec.firstName_ << " " << rec.year_ << " "
      << rec.city_ << " " << rec.countCoins_;
  return out;
}

bool Record::checkValidFunctionInput(const std::string &lastName,
                                     const std::string &firstName,
                                     unsigned year, const std::string &city,
                                     unsigned coins) {
  return lastName == "-" && firstName == "-" && year == '-' && city == "-" &&
         coins == '-';
}
}  // namespace s21