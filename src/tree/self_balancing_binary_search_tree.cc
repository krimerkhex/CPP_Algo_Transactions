#include "self_balancing_binary_search_tree.h"

namespace s21 {
SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree()
    : Methods(), Map() {}

SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(
    const SelfBalancingBinarySearchTree &other)
    : Methods(other), Map(other) {
  copy(other);
}

SelfBalancingBinarySearchTree::SelfBalancingBinarySearchTree(
    SelfBalancingBinarySearchTree &&other) noexcept {
  move(other);
}

SelfBalancingBinarySearchTree &SelfBalancingBinarySearchTree::operator=(
    const SelfBalancingBinarySearchTree &other) {
  if (this != &other) {
    copy(other);
  }
  return *this;
}

SelfBalancingBinarySearchTree &SelfBalancingBinarySearchTree::operator=(
    SelfBalancingBinarySearchTree &&other) noexcept {
  if (this != &other) {
    move(other);
  }
  return *this;
}

void SelfBalancingBinarySearchTree::copy(
    const SelfBalancingBinarySearchTree &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->set(it->first, it->second);
  }
}

unsigned SelfBalancingBinarySearchTree::getSize() { return this->size(); }

void SelfBalancingBinarySearchTree::move(SelfBalancingBinarySearchTree &other) {
  copy(other);
  other.clear();
}

void SelfBalancingBinarySearchTree::updateTime() {
  currentTime_ =
      std::chrono::system_clock::now().time_since_epoch().count() / 10e8;
}

bool SelfBalancingBinarySearchTree::set(std::string key, std::string lastName,
                                        std::string firstName, unsigned year,
                                        std::string city, unsigned coins,
                                        double seconds) {
  updateTime();
  return set(key, Record(lastName, firstName, year, city, coins,
                         currentTime_ + seconds, false));
}

bool SelfBalancingBinarySearchTree::set(std::string key, std::string lastName,
                                        std::string firstName, unsigned year,
                                        std::string city, unsigned coins) {
  return set(key, Record(lastName, firstName, year, city, coins, 0, true));
}

bool SelfBalancingBinarySearchTree::set(const std::string &key,
                                        const Record &value) {
  checkAllStruct();
  bool flag = false;
  auto temp = this->findPtr(key);
  if (!key.empty() && temp == nullptr) {
    this->insert(key, value);
    flag = true;
  } else {
    std::cout << "Key is clear or in tree" << std::endl;
  }
  return flag;
}

Record SelfBalancingBinarySearchTree::get(std::string key) {
  checkAllStruct();
  Record r_val;
  auto temp = this->findPtr(key);
  if (temp != nullptr) {
    std::cout << temp->value.second;
    r_val = temp->value.second;
  } else {
    std::cout << "(null)" << std::endl;
  }
  return r_val;
}

bool SelfBalancingBinarySearchTree::exists(std::string key) {
  checkAllStruct();
  bool flag = this->findPtr(key) != nullptr;
  std::cout << flag << std::endl;
  return flag;
}

bool SelfBalancingBinarySearchTree::del(std::string key) {
  checkAllStruct();
  auto temp = this->findPtr(key);
  if (temp != nullptr) {
    erase(temp->value.first);
    std::cout << "OK" << std::endl;
  } else {
    std::cout << "(null)" << std::endl;
  }
  return temp != nullptr;
}

bool SelfBalancingBinarySearchTree::update(std::string key,
                                           std::string lastName,
                                           std::string firstName, unsigned year,
                                           std::string city, unsigned coins) {
  checkAllStruct();
  auto temp = this->findPtr(key);
  if (temp != nullptr) {
    Record &node = temp->value.second;
    node.copyPass(Record(lastName, firstName, year, city, coins));
    std::cout << "OK" << std::endl;
  } else {
    std::cout << "(null)" << std::endl;
  }
  return temp != nullptr;
}

std::vector<std::string> SelfBalancingBinarySearchTree::keys() {
  return find("-", "-", '-', "-", '-');
}

bool SelfBalancingBinarySearchTree::rename(std::string src, std::string dest) {
  checkAllStruct();
  auto temp = this->findPtr(src);
  if (temp != nullptr) {
    Record value = temp->value.second;
    this->erase(temp->value.first);
    insert(dest, value);
    std::cout << "OK" << std::endl;
  } else {
    std::cout << "(null)" << std::endl;
  }
  return temp != nullptr;
}

double SelfBalancingBinarySearchTree::ttl(std::string key) {
  checkAllStruct();
  auto temp = this->findPtr(key);
  double ends(0);
  if (temp != nullptr) {
    updateTime();
    ends = temp->value.second.getTTL() - currentTime_;
    std::cout << ends << std::endl;
  } else {
    std::cout << "(null)" << std::endl;
  }
  return ends;
}

std::vector<std::string> SelfBalancingBinarySearchTree::find(
    std::string lastName, std::string firstName, unsigned birthyear,
    std::string city, unsigned coins) {
  checkAllStruct();
  Record temp(lastName, firstName, birthyear, city, coins, 0, true);
  std::vector<std::string> r_val;
  if (this->size() != 0) {
    long unsigned counter(0);
    auto it = this->begin();
    while (true) {
      if (it->second.checkForPass(temp)) {
        std::cout << counter++ << ") " << it->first << std::endl;
        r_val.push_back(it->first);
      }
      if (it == this->end()) {
        break;
      }
      it++;
    }
  } else {
    std::cout << "[INFO] Tree is empty" << std::endl;
  }
  return r_val;
}

void SelfBalancingBinarySearchTree::showall() {
  checkAllStruct();
  if (this->size()) {
    short unsigned counter = 0;
    std::cout << " № "
              << "|"
              << " Фамилия "
              << "|"
              << "   Имя   "
              << "|"
              << " Год "
              << "|"
              << "  Город  "
              << "|"
              << " Количество коинов " << std::endl;
    auto it = this->begin();
    while (true) {
      std::cout << it->first << " ";
      it->second.show(++counter);
      std::cout << "\n";
      if (it == this->end()) {
        break;
      }
      it++;
    }
  } else {
    std::cout << "No value's in tree" << std::endl;
  }
}

long long unsigned SelfBalancingBinarySearchTree::upload(std::string filepath) {
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

long long unsigned SelfBalancingBinarySearchTree::exportt(
    std::string filepath) {
  checkAllStruct();
  std::ofstream file(filepath);
  long long unsigned counter = 0;
  if (file.is_open()) {
    auto it = this->begin();
    while (true) {
      file << it->first << " ";
      file << it->second << "\n";
      ++counter;
      if (it == this->end()) {
        break;
      }
      it++;
    }
    //            for (auto &it: *this) {
    //                file << it.first << " ";
    //                file << it.second << "\n";
    //                ++counter;
    //            }
    std::cout << "OK " << counter << std::endl;
    file.close();
  } else {
    std::cout << "File opening failed." << std::endl;
  }
  return counter;
}

void SelfBalancingBinarySearchTree::checkAllStruct() {
  if (this->size()) {
    std::vector<std::string> stitched;
    //            for (auto &it: *this) {
    //                updateTime();
    //                if (it.second.checkTime(currentTime_)) {
    //                    stitched.push_back(it.first);
    //                }
    //            }
    auto it = this->begin();
    while (true) {
      updateTime();
      if (it->second.checkTime(currentTime_)) {
        stitched.push_back(it->first);
      }
      if (it == this->end()) {
        break;
      }
      it++;
    }
    for (const auto &keys : stitched) {
      erase(keys);
    }
  }
}

}  // namespace s21
