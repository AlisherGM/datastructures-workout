#pragma onece
#include <utility>

template <typename Key, typename Value> struct Node {
  std::pair<Key, Value> p;
  Node *left;
  Node *right;
  Node *parent;

  Node() : left(nullptr), right(nullptr), parent(nullptr) {}

  Node(Key key, Value value, Node<Key, Value> *left, Node<Key, Value> *right,
       Node<Key, Value> *parent)
      : p(key, value), left(left), right(right), parent(parent) {}
};

template <typename Key, typename Value> struct MapIter {
  Node<Key, Value> *node;
  bool is_end;

  MapIter(Node<Key, Value> *node) : node(node), is_end(false) {}

  MapIter() : node(nullptr), is_end(true) {}

  std::pair<Key, Value> &operator*() { return node->p; }

  std::pair<Key, Value> *operator->() { return &node->p; }

  MapIter &operator++() {
    if (node->right) {
      node = node->right;
      while (node->left) {
        node = node->left;
      }
    } else {
      while (node->parent && node->parent->right == node) {
        node = node->parent;
      }
      if (node->parent) {
        node = node->parent;
      } else {
        is_end = true;
        node = nullptr;
      }
    }
    return *this;
  }

  bool operator!=(const MapIter &other) {
    return is_end != other.is_end || node != other.node;
  }

  bool operator==(const MapIter &other) {
    return is_end == other.is_end && node == other.node;
  }
};

template <typename Key, typename Value> struct Map {
  Map() : root(nullptr) {}
  Node<Key, Value> *root;

  Value &operator[](const Key &key);

  MapIter<Key, Value> begin() {
    Node<Key, Value> *head = root;
    while (head->left != nullptr) {
      head = head->left;
    }
    return MapIter<Key, Value>(head);
  }
  MapIter<Key, Value> end() { return MapIter<Key, Value>(); }

  ~Map();

private:
  Node<Key, Value> *find(const Key &key, Node<Key, Value> *node);
  Node<Key, Value> *insert(const Key &key, Node<Key, Value> *node);
  void dealloc(Node<Key, Value> *node);
};

template <typename Key, typename Value>
Node<Key, Value> *Map<Key, Value>::insert(const Key &key,
                                          Node<Key, Value> *node) {
  if (key < node->p.first) {
    if (node->left != nullptr) {
      return insert(key, node->left);
    } else {
      node->left = new Node<Key, Value>(key, Value(), nullptr, nullptr, node);
      return node->left;
    }
  } else if (key > node->p.first) {
    if (node->right != nullptr) {
      return insert(key, node->right);
    } else {
      node->right = new Node<Key, Value>(key, Value(), nullptr, nullptr, node);
      return node->right;
    }
  }
  return node;
}

template <typename Key, typename Value>
Node<Key, Value> *Map<Key, Value>::find(const Key &key,
                                        Node<Key, Value> *node) {
  if (node != nullptr) {
    if (node->p.first == key)
      return node;
    if (key < node->p.first)
      return find(key, node->left);
    else
      return find(key, node->right);
  }
  return nullptr;
}

template <typename Key, typename Value>
Value &Map<Key, Value>::operator[](const Key &key) {
  if (!root) {
    root = new Node<Key, Value>(key, Value(), nullptr, nullptr, nullptr);
  }
  auto node = insert(key, root);
  return node->p.second;
}

template <typename Key, typename Value>
void Map<Key, Value>::dealloc(Node<Key, Value> *node) {
  if (node != nullptr) {
    dealloc(node->left);
    dealloc(node->right);
    delete node;
  }
}

template <typename Key, typename Value> Map<Key, Value>::~Map() {
  dealloc(root);
}
