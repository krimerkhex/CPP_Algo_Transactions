#include "s21_map.h"

using namespace s21;

Map::Map() {
  this->size_ = 0;
  this->root_ = nullptr;
  this->begin_ = new Nodes;
  this->begin_->IsBegin = true;
  this->end_ = new Nodes;
  this->end_->IsEnd = true;
}

Map::Map(std::initializer_list<value_type> const &items) : Map() {
  for (auto i : items) {
    insert(i);
  }
}

Map::Map(const Map &other) : Map() {
  for (auto i : other) {
    insert(i);
  }
  size_ = other.size_;
}

Map::Map(Map &&other) {
  if (*this != other) {
    root_ = other.root_;
    begin_ = other.begin_;
    end_ = other.end_;
    size_ = other.size_;
    other.root_ = other.begin_ = other.end_ = nullptr;
    other.size_ = 0;
  }
}

Map::Map(const Map &&other) : Map(other) { ; }

Map::~Map() {
  RemoveMap_(root_);
  if (this->begin_ != nullptr) {
    delete this->begin_;
  }
  if (this->end_ != nullptr) {
    delete this->end_;
  }
}

typename Map::Map &Map::operator=(Map &&other) {
  if (&other != this) {
    this->clear();
    this->root_ = other.root_;
    delete this->begin_;
    delete this->end_;
    this->begin_ = other.begin_;
    this->end_ = other.end_;
    this->size_ = other.size_;
    other.root_ = other.begin_ = other.end_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

typename Map::Map &Map::operator=(const Map &&other) {
  *this = other;
  return *this;
}

typename Map::Map &Map::operator=(const Map &other) {
  this->clear();
  if (other != *this) {
    for (auto i : other) insert(i);
  }
  return *this;
}

bool Map::operator==(Map &other) const { return root_ == other.root_; }

bool Map::operator!=(Map &other) const { return root_ != other.root_; }

typename Map::maped_type &Map::at(const key_type &key) {
  std::pair<Nodes *, bool> res = FindRead_(key, root_);
  maped_type nol = maped_type();
  return res.second == true ? res.first->data.second : nol;
}

typename Map::maped_type &Map::operator[](const key_type key) {
  auto result = FindWrite_(key);
  size_ += result.second;
  return result.first->data.second;
}

typename Map::iterator Map::begin() {
  return iterator(begin_->parent ? begin_->parent : end_);
}

typename Map::iterator Map::end() { return iterator(end_); }

typename Map::const_iterator Map::begin() const {
  return const_iterator(begin_->parent ? begin_->parent : end_);
}

typename Map::const_iterator Map::end() const { return const_iterator(end_); }

bool Map::empty() const { return root_ == nullptr; }

typename Map::size_type Map::size() const { return size_; }

typename Map::size_type Map::max_size() const { return MAXSIZE; }

void Map::clear() {
  RemoveMap_(root_);
  size_ = 0;
  root_ = nullptr;
  begin_->parent = begin_->left = begin_->right = nullptr;
  end_->parent = end_->left = end_->right = nullptr;
}

typename std::pair<typename Map::iterator, bool> Map::insert(
    const value_type &value) {
  bool res_bool = true;
  Node *res_node;
  if (root_ == nullptr) {
    root_ = new Nodes(value, nullptr, begin_, end_);
    begin_->parent = root_;
    end_->parent = root_;
    res_node = root_;
    res_node->Red = false;
  } else {
    std::pair<Nodes *, bool> temp = FindWrite_(value.first);
    if (temp.second) {
      temp.first->data.second = value.second;
    }
    res_bool = temp.second;
    res_node = temp.first;
  }
  if (res_bool) {
    FixUp_(res_node);
  }
  size_ += res_bool;
  iterator res(res_node);
  return std::make_pair(res, res_bool);
}

typename std::pair<typename Map::iterator, bool> Map::insert(
    const key_type &key, const maped_type &obj) {
  return insert(std::make_pair(key, obj));
}

typename std::pair<typename Map::iterator, bool> Map::insert_or_assign(
    const key_type &key, const maped_type &obj) {
  std::pair<iterator, bool> temp = this->insert(key, obj);
  FindRead_(temp.first->first, root_).first->data.second = obj;
  return temp;
}

void Map::erase(iterator pos) {
  auto remove = FindRead_(pos->first, this->root_);
  if (!remove.second) {
    throw std::out_of_range("Error: Attempt to remove the end element");
  }
  RemoveNode_(remove.first);
  size_--;
}

void Map::erase(Map::key_type key) {
  auto remove = FindRead_(key, this->root_);
  if (!remove.second) {
    throw std::out_of_range("Error: Attempt to remove the end element");
  }
  RemoveNode_(remove.first);
  size_--;
}

void Map::swap(Map &other) {
  Nodes *tmp_root = root_;
  size_type tmp_size_ = size_;
  Nodes *tmp_begin = begin_;
  Nodes *tmp_end = end_;
  root_ = other.root_;
  begin_ = other.begin_;
  end_ = other.end_;
  size_ = other.size_;
  other.root_ = tmp_root;
  other.begin_ = tmp_begin;
  other.end_ = tmp_end;
  other.size_ = tmp_size_;
}

void Map::merge(Map &other) {
  if (other.size()) {
    Map temp;
    for (auto i : other) {
      if (!insert(i).second) {
        temp.insert(i);
      }
    }
    other = temp;
  }
}

bool Map::contains(const key_type &key) const {
  return FindRead_(key, root_).second;
}

template <class... Args>
std::pair<typename Map::iterator, bool> Map::emplace(Args &&...args) {
  return (this->insert(args), ...);
}
