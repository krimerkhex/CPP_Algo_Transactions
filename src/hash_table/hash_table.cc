#include "hash_table.h"

namespace s21 {
HashTable::HashTable() : Methods() {
  this->copasity_ = 10;
  this->size_ = 0;
  createDataStructs();
}

HashTable::HashTable(const HashTable &other) : Methods(other) { copy(other); }

HashTable::HashTable(HashTable &&other) noexcept { move(other); }

HashTable &HashTable::operator=(const HashTable &other) {
  if (this != &other) {
    copy(other);
  }
  return *this;
}

HashTable &HashTable::operator=(HashTable &&other) noexcept {
  if (this != &other) {
    move(other);
  }
  return *this;
}

HashTable::~HashTable() {
  deleteDataStructs();
  size_ = copasity_ = 0;
}

void HashTable::createDataStructs() { this->data_.resize(copasity_); }

void HashTable::deleteDataStructs() { data_.clear(); }

void HashTable::copy(const HashTable &other) {
  this->size_ = other.size_;
  this->copasity_ = other.copasity_;
  this->data_.resize(copasity_);
  for (long unsigned i = 0; i < other.size_; ++i)
    this->data_[i] = other.data_[i];
  updateTime();
}

void HashTable::move(HashTable &other) {
  this->size_ = other.size_;
  this->copasity_ = other.copasity_;
  this->data_ = other.data_;
  other.size_ = other.copasity_ = 0;
  other.data_.resize(0);
  updateTime();
}

unsigned HashTable::getSize() const { return size_; }

void HashTable::resize() {
  if (size_ >= copasity_ * (0.6)) {
    int hash_value = 0;
    std::vector<std::list<std::pair<std::string, Record>>> temp;
    temp.resize(copasity_ * 2);
    this->copasity_ *= 2;
    for (const auto &it_vector : data_) {
      for (const auto &it_list : it_vector) {
        hash_value = hash(it_list.first);
        temp[hash_value].push_back(it_list);
      }
    }
    this->data_ = temp;
  }
}

bool HashTable::set(std::string key, std::string lastName,
                    std::string firstName, unsigned year, std::string city,
                    unsigned coins, double seconds) {
  updateTime();
  return set(key, Record(lastName, firstName, year, city, coins,
                         currentTime_ + seconds, false));
}

bool HashTable::set(std::string key, std::string lastName,
                    std::string firstName, unsigned year, std::string city,
                    unsigned coins) {
  return set(key, Record(lastName, firstName, year, city, coins, 0, true));
}

bool HashTable::set(std::string key, Record value) {
  int hash_value = this->hash(key);
  checkAllStruct();
  bool flag = false;
  if (!key.empty() && find(key) == nullptr) {
    this->data_[hash_value].push_back(
        std::make_pair(std::move(key), std::move(value)));
    size_++;
    resize();
    flag = true;
  } else {
    std::cout << "Key is clear or in hashtable" << key << std::endl;
  }
  return flag;
}

Record HashTable::get(std::string key) {
  checkAllStruct();
  Record *ret_v = find(key);
  if (ret_v != nullptr) {
    std::cout << *ret_v << std::endl;
  } else {
    std::cout << "(null)" << std::endl;
  }
  return ret_v ? *ret_v : Record();
}

bool HashTable::exists(std::string key) {
  checkAllStruct();
  bool flag = (find(key) != nullptr);
  std::cout << flag << std::endl;
  return flag;
}

bool HashTable::del(std::string key) {
  int hash_value = this->hash(key);
  bool flag = false;
  if (!key.empty() && find(key) != nullptr) {
    for (auto it = this->data_[hash_value].begin();
         it != this->data_[hash_value].end() && !flag; it++) {
      if (it->first == key) {
        this->data_[hash_value].erase(it);
        size_--;
        flag = true;
      }
    }
  }
  return flag;
}

bool HashTable::update(std::string key, std::string lastName,
                       std::string firstName, unsigned year, std::string city,
                       unsigned coins) {
  checkAllStruct();
  int hash_value(this->hash(key));
  bool flag(false);
  Record temp(lastName, firstName, year, city, coins);
  for (auto &it_list : this->data_[hash_value]) {
    if (it_list.first == key) {
      it_list.second.copyPass(temp);
      flag = true;
    }
  }
  return flag;
}

std::vector<std::string> HashTable::keys() {
  return find("-", "-", '-', "-", '-');
}

bool HashTable::rename(std::string src, std::string dest) {
  bool flag = false;
  checkAllStruct();
  Record *temp = this->find(src);
  if (temp != nullptr) {
    this->set(dest, *temp);
    del(src);
    flag = true;
  } else {
    std::cout << "(null)" << std::endl;
  }
  return flag;
}

double HashTable::ttl(std::string key) {
  checkAllStruct();
  Record *temp = find(key);
  double ends(0);
  if (temp != nullptr) {
    if (!temp->getConstans()) {
      updateTime();
      ends = temp->getTTL() - currentTime_;
      std::cout << ends << std::endl;
    } else {
      std::cout << "This record without timer" << std::endl;
    }
  }
  return ends;
}

std::vector<std::string> HashTable::find(std::string lastName,
                                         std::string firstName, unsigned year,
                                         std::string city, unsigned coins) {
  std::vector<std::string> r_val;
  Record temp(lastName, firstName, year, city, coins, 0, true);
  unsigned counter = 0;
  checkAllStruct();
  for (const auto &it_vector : this->data_) {
    for (const auto &it_list : it_vector) {
      if (it_list.second.checkForPass(temp)) {
        std::cout << ++counter << ") " << it_list.first << std::endl;
        r_val.push_back(it_list.first);
      }
    }
  }
  return r_val;
}

void HashTable::showall() {
  if (this->size_) {
    checkAllStruct();
    short unsigned counter = 1;
    std::cout << " N "
              << "|"
              << " Surname "
              << "|"
              << "   Name   "
              << "|"
              << " Year "
              << "|"
              << "  City  "
              << "|"
              << " Count Coins " << std::endl;
    for (const auto &it_vector : this->data_) {
      for (const auto &it_list : it_vector) {
        it_list.second.show(counter++);
        this->updateTime();
        std::cout << " |Minus  " << it_list.second.getTTL() - currentTime_
                  << " |checkTime " << it_list.second.checkTime(currentTime_)
                  << " |TTl " << it_list.second.getTTL() << " |Current "
                  << currentTime_ << std::endl;
      }
    }
  } else {
    std::cout << "No value's in hash table." << std::endl;
  }
}

long long unsigned HashTable::upload(std::string filepath) {
  std::ifstream file(filepath);
  checkAllStruct();
  long long unsigned counter = 0;
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      unsigned i = 0;
      for (const char element : line) {
        if (element == ' ') {
          i++;
        }
      }
      if (i <= 6) {
        std::string tokens[7];
        std::stringstream sline(line);
        int poz = 0;
        while (std::getline(sline, tokens[poz++], ' ')) {
        }
        if (tokens[6].empty()) {
          counter +=
              this->set(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]),
                        tokens[4], std::stoi(tokens[5]));
        } else {
          counter +=
              this->set(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3]),
                        tokens[4], std::stoi(tokens[5]), std::stod(tokens[6]));
        }
      }
    }
    std::cout << "OK " << counter << std::endl;
    file.close();
  } else {
    std::cout << "File opening failed." << std::endl;
  }
  return counter;
}

long long unsigned HashTable::exportt(std::string filepath) {
  std::ofstream file(filepath);
  checkAllStruct();
  long long unsigned counter = 0;
  if (file.is_open()) {
    for (const auto &it_vector : this->data_) {
      for (const auto &it_list : it_vector) {
        file << it_list.first << " ";
        file << it_list.second << " "
             << (!it_list.second.getConstans()
                     ? (it_list.second.getTTL() - currentTime_)
                     : 0)
             << std::endl;
        ++counter;
      }
    }
    std::cout << "OK" << counter << std::endl;
    file.close();
  } else {
    std::cout << "File opening failed." << std::endl;
  }
  return counter;
}

int HashTable::hash(const std::string &key) const {
  int hash = 0;
  for (char i : key)
    hash = abs((hash * (i > 96 ? i - 96 : i - 64) + i) % (int)this->copasity_);
  return hash;
}

void HashTable::updateTime() {
  currentTime_ =
      std::chrono::system_clock::now().time_since_epoch().count() / 10e8;
}

void HashTable::checkAllStruct() {
  bool flag = false;
  for (auto &iter : this->data_) {
    if (iter.empty()) {
      continue;
    }
    for (auto it_list = iter.begin(); it_list != iter.end() && !flag;
         it_list++) {
      updateTime();
      if (it_list->second.checkTime(currentTime_)) {
        iter.erase(it_list);
        size_--;
        if (iter.empty()) {
          flag = true;
        }
      }
    }
    flag = false;
  }
}

Record *HashTable::find(const std::string &key) {
  Record *r_value = nullptr;
  for (auto &it : this->data_[hash(key)]) {
    if (it.first == key) {
      r_value = &it.second;
    }
  }
  return r_value;
}
}  // namespace s21
