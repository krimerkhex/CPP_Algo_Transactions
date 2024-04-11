#ifndef S21_MAP_H
#define S21_MAP_H

#include <string>

#include "methods.h"

namespace s21 {
class Map {
 public:
  using key_type = std::string;
  using value_type = Record;
  using maped_type = std::pair<key_type, value_type>;
  using reference = value_type &;
  enum check_code { error_balance, error_struct, ok };

  struct Node {
    static Node null;
    Node *left, *right, *parent;
    maped_type value;
    bool red;
    Node(const maped_type, const bool red = true);
  };

  class Iterator {
   protected:
    Node *iterator_;
    Node *root_;

   public:
    Iterator(Node *node, Node *root) : iterator_(node), root_(root) {}
    bool operator==(const Iterator &it);
    bool operator!=(const Iterator &it);
    Node *operator++();
    Node *operator++(int);
    Node *operator--();
    Node *operator--(int);
    Node *operator+=(int n);
    Node *operator-=(int n);

   private:
    Node *NextNode_(Node *node);
    Node *PreviousNode_(Node *node);
    Node *MinNode_(Node *node);
    Node *MaxNode_(Node *node);
  };

  class MapIterator : public Iterator {
   public:
    MapIterator(Node *node, Node *root) : Iterator(node, root) {}
    maped_type &operator*() { return this->iterator_->value; }
    const maped_type *operator->() { return &this->iterator_->value; }
  };

  class ConstMapIterator : public Iterator {
   public:
    ConstMapIterator(Node *node, Node *root) : Iterator(node, root) {}
    const maped_type &operator*() { return this->iterator_->value; }
    const maped_type *operator->() { return &this->iterator_->value; }
  };

  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;

  Map();
  ~Map();
  void clear();
  bool find(const key_type);
  Node *findPtr(const key_type);
  void insert(const maped_type &);
  void insert(const key_type, const value_type);
  void erase(const key_type);
  unsigned size() const;
  void show();
  check_code check();
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

 private:
  Node *root_;
  unsigned size_;

  Node *newNode(const maped_type);
  void delNode(Node *);
  void clear(Node *);
  Node *rotateLeft(Node *);
  Node *rotateRight(Node *);
  void balanceInsert(Node **);
  bool balanceRemoveLeft(Node **);
  bool balanceRemoveRigth(Node **);
  bool insert(const maped_type &, Node **);
  bool getMin(Node **, Node **);
  bool erase(Node **, const key_type);
  void show(Node *, int, char);
  check_code check(Node *, int, int &);
  void costil(Node *node);
};
};  // namespace s21

#endif  // S21_MAP_H
