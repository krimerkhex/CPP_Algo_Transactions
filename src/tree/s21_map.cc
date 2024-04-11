#include "s21_map.h"

namespace s21 {

Map::Node Map::Node::null(maped_type(key_type(), value_type()), false);

Map::Node::Node(const maped_type value, const bool color) {
  this->value = value;
  this->red = color;
  this->left = &null;
  this->right = &null;
}

Map::Map() {
  size_ = 0;
  root_ = &Node::null;
}

Map::~Map() { clear(root_); }

unsigned Map::size() const { return size_; }

Map::Node *Map::newNode(const maped_type value) {
  size_++;
  Node *node = new Node(value);
  return node;
}

void Map::delNode(Node *node) {
  size_--;
  delete node;
}

void Map::clear(Node *node) {
  if (node == &Node::null) return;
  clear(node->left);
  clear(node->right);
  delNode(node);
}

Map::Node *Map::rotateLeft(Node *node) {
  Node *right = node->right;
  Node *p21 = right->left;
  right->left = node;
  node->right = p21;
  return right;
}

Map::Node *Map::rotateRight(Node *node) {
  Node *left = node->left;
  Node *p12 = left->right;
  left->right = node;
  node->left = p12;
  return left;
}

void Map::balanceInsert(Node **root) {
  Node *left, *right, *px1, *px2;
  Node *node = *root;
  if (node->red) return;
  left = node->left;
  right = node->right;
  if (left->red) {
    if (left->right->red) left = node->left = rotateLeft(left);
    px1 = left->left;
    if (px1->red) {
      node->red = true;
      left->red = false;
      if (right->red) {
        px1->red = true;
        right->red = false;
        return;
      }
      *root = rotateRight(node);
      return;
    }
  }
  if (right->red) {
    if (right->left->red) right = node->right = rotateRight(right);
    px2 = right->right;
    if (px2->red) {
      node->red = true;
      right->red = false;
      if (left->red) {
        px2->red = true;
        left->red = false;
        return;
      }
      *root = rotateLeft(node);
      return;
    }
  }
}

bool Map::balanceRemoveLeft(Node **root) {
  Node *node = *root;
  Node *left = node->left;
  Node *right = node->right;
  if (left->red) {
    left->red = false;
    return false;
  }
  if (right->red) {
    node->red = true;
    right->red = false;
    node = *root = rotateLeft(node);
    if (balanceRemoveLeft(&node->left)) node->left->red = false;
    return false;
  }
  Node *p21 = right->left;
  Node *p22 = right->right;
  if (!p21->red && !p22->red) {
    right->red = true;
    return true;
  }
  if (p21->red) {
    right->red = true;
    p21->red = false;
    right = node->right = rotateRight(right);
    p22 = right->right;
  }
  if (p22->red) {
    right->red = node->red;
    p22->red = node->red = false;
    *root = rotateLeft(node);
  }
  return false;
}

bool Map::balanceRemoveRigth(Node **root) {
  Node *node = *root;
  Node *left = node->left;
  Node *right = node->right;
  if (right->red) {
    right->red = false;
    return false;
  }
  if (left->red) {
    node->red = true;
    left->red = false;
    node = *root = rotateRight(node);
    if (balanceRemoveRigth(&node->right)) node->right->red = false;
    return false;
  }
  Node *p11 = left->left;
  Node *p12 = left->right;
  if (!p12->red && !p11->red) {
    left->red = true;
    return true;
  }
  if (p12->red) {
    left->red = true;
    p12->red = false;
    left = node->left = rotateLeft(left);
    p11 = left->left;
  }
  if (p11->red) {
    left->red = node->red;
    p11->red = node->red = false;
    *root = rotateRight(node);
  }
  return false;
}

bool Map::find(const key_type value) {
  Node *node = root_;
  while (node != &Node::null) {
    if (node->value.first == value) return true;
    node = node->value.first > value ? node->left : node->right;
  }
  return false;
}

bool Map::insert(const maped_type &value, Node **root) {
  Node *node = *root;
  if (node == &Node::null)
    *root = newNode(value);
  else {
    if (value.first == node->value.first) return true;
    if (insert(value,
               value.first < node->value.first ? &node->left : &node->right))
      return true;
    balanceInsert(root);
    costil(root_);
  }
  return false;
}

bool Map::getMin(Node **root, Node **res) {
  Node *node = *root;
  if (node->left == &Node::null) {
    *root = node->right;
    *res = node;
    return !node->red;
  } else {
    if (getMin(&node->left, res)) return balanceRemoveLeft(root);
  }
  return false;
}

bool Map::erase(Node **root, const key_type value) {
  Node *t, *node = *root;
  if (node == &Node::null) return false;
  if (node->value.first < value) {
    if (erase(&node->right, value)) return balanceRemoveRigth(root);
  } else if (node->value.first > value) {
    if (erase(&node->left, value)) return balanceRemoveLeft(root);
  } else {
    bool res;
    if (node->right == &Node::null) {
      *root = node->left;
      res = !node->red;
    } else {
      res = getMin(&node->right, root);
      t = *root;
      t->red = node->red;
      t->left = node->left;
      t->right = node->right;
      if (res) res = balanceRemoveRigth(root);
    }
    delNode(node);
    costil(root_);
    return res;
  }
  return 0;
}

void Map::insert(const maped_type &value) {
  insert(value, &root_);
  root_->red = false;
}

void Map::insert(const key_type key, const value_type value) {
  insert(std::make_pair(key, value));
}

void Map::erase(const key_type value) { erase(&root_, value); }

void Map::clear() {
  clear(root_);
  root_ = 0;
}

Map::check_code Map::check(Node *tree, int d, int &h) {
  if (tree == &Node::null) {
    if (h < 0) h = d;
    return h == d ? ok : error_balance;
  }
  Node *left = tree->left;
  Node *right = tree->right;
  if (tree->red && (left->red || right->red)) return error_struct;
  if (left != &Node::null &&
      (tree->value.first < left->value.first || right != &Node::null) &&
      tree->value.first > right->value.first)
    return error_struct;
  if (!tree->red) d++;
  check_code n = check(left, d, h);
  if (n) return n;
  return check(right, d, h);
}

Map::check_code Map::check() {
  int d = 0;
  int h = -1;
  if (root_ == &Node::null) return ok;
  if (root_->red || Node::null.red) return error_struct;
  return check(root_, d, h);
}

typename Map::iterator Map::begin() {
  Node *tmp(root_);
  while (tmp->left != &Node::null) {
    tmp = tmp->left;
  }
  return iterator(tmp, root_);
}

typename Map::iterator Map::end() {
  Node *tmp(root_);
  while (tmp->right != &Node::null) {
    tmp = tmp->right;
  }
  return iterator(tmp, root_);
}

typename Map::const_iterator Map::begin() const {
  Node *tmp(root_);
  while (tmp->left != &Node::null) {
    tmp = tmp->left;
  }
  return const_iterator(tmp, root_);
}

typename Map::const_iterator Map::end() const {
  Node *tmp(root_);
  while (tmp->right != &Node::null) {
    tmp = tmp->right;
  }
  return const_iterator(tmp, root_);
}

void Map::costil(Node *node) {
  if (node->left != &Node::null) {
    node->left->parent = node;
    costil(node->left);
  }
  if (node->right != &Node::null) {
    node->right->parent = node;
    costil(node->right);
  }
}

typename Map::Node *Map::findPtr(const key_type key) {
  Node *tmp(root_);
  while (tmp->value.first != key && tmp != &Node::null) {
    if (tmp->value.first > key) {
      tmp = tmp->left;
    } else {
      tmp = tmp->right;
    }
  }
  return tmp == &Node::null ? nullptr : tmp;
}

bool Map::Iterator::operator==(const Iterator &it) {
  return this->iterator_ == it.iterator_;
}

bool Map::Iterator::operator!=(const Iterator &it) {
  return this->iterator_ != it.iterator_;
}

typename Map::Node *Map::Iterator::operator++() {
  return iterator_ = NextNode_(this->iterator_);
}

typename Map::Node *Map::Iterator::operator++(int) {
  return iterator_ = NextNode_(this->iterator_);
}

typename Map::Node *Map::Iterator::operator--() {
  return iterator_ = PreviousNode_(this->iterator_);
}

typename Map::Node *Map::Iterator::operator--(int) {
  return iterator_ = PreviousNode_(this->iterator_);
}

typename Map::Node *Map::Iterator::operator+=(int n) {
  while (n-- > 0) {
    iterator_ = NextNode_(iterator_);
  }
  return iterator_;
}

typename Map::Node *Map::Iterator::operator-=(int n) {
  while (n-- > 0) {
    iterator_ = PreviousNode_(iterator_);
  }
  return iterator_;
}

typename Map::Node *Map::Iterator::NextNode_(Node *node) {
  if (node == &Node::null) return node;
  if (node->right != &Node::null) {
    node = MinNode_(node->right);
  } else if (node == node->parent->left) {
    node = node->parent;
  } else {
    node = node->parent;
    while (node == node->parent->right) {
      node = node->parent;
    }
    node = node->parent;
  }
  return node;
}

typename Map::Node *Map::Iterator::PreviousNode_(Node *node) {
  if (node->left == &Node::null) {
    return node;
  }
  if (node->left != &Node::null) {
    node = MaxNode_(node->left);
  } else if (node == node->parent->right) {
    node = node->parent;
  } else {
    node = node->parent;
    while (node == node->parent->left) {
      node = node->parent;
    }
    node = node->parent;
  }
  return node;
}

typename Map::Node *Map::Iterator::MinNode_(Node *node) {
  while (node != &Node::null && node->left != &Node::null) {
    node = node->left;
  }
  return node;
}

typename Map::Node *Map::Iterator::MaxNode_(Node *node) {
  while (node != &Node::null && node->right != &Node::null) {
    node = node->right;
  }
  return node;
}

}  // namespace s21