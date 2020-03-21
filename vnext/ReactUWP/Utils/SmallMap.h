#pragma once
#include <algorithm>
#include <vector>

DECLSPEC_SELECTANY int g_small_map_count = 0;

template <typename K, typename V>
class small_map : public std::vector<std::pair<K, V>> {
 private:
  using pair_t = std::pair<K, V>;
  using super = std::vector<pair_t>;

 public:
  using super::super;
  small_map() {
    g_small_map_count++;
  }
  typename std::vector<pair_t>::iterator find(const K &k) noexcept {
    return std::find_if(this->begin(), this->end(), [k](pair_t &p) { return p.first == k; });
  }
  typename const std::vector<pair_t>::const_iterator find(const K &k) const noexcept {
    return std::find_if(this->cbegin(), this->cend(), [k](const pair_t &p) { return p.first == k; });
  }

  V &operator[](const K &k) {
    auto it = find(k);
    if (it == this->end()) {
      this->push_back(make_pair(k, V{}));
      it = find(k);
    }
    return it->second;
  }

  size_t count(const K &k) const {
    return this->find(k) == this->end() ? 0 : 1;
  }

  template <typename... Args>
  typename super::iterator emplace(K &k, V &&v) {
    this->push_back(std::make_pair(k, std::move(v)));
    auto it = this->end();
    it--;
    return it;
  }

  template <typename... Args>
  typename super::iterator emplace_back(K &k, V &&v) {
    return this->emplace(k, v);
  }

  V &at(const K &k) {
    auto it = std::find_if(this->begin(), this->end(), [k](pair_t &p) { return p.first == k; });

    if (it != this->end()) {
      return it->second;
    }
    throw std::out_of_range("small_map: out of range");
  }

  const V &at(const K &k) const {
    auto it = std::find_if(this->cbegin(), this->cend(), [k](pair_t &p) { return p.first == k; });

    if (it != this->cend()) {
      return it->second;
    }
    throw std::out_of_range("small_map: out of range");
  }

  size_t erase(const K &k) {
    auto it = find(k);
    if (it != this->end()) {
      super::erase(it);
      return 1;
    }
    return 0;
  }

  typename super::iterator erase(typename super::const_iterator it) {
    return this->super::erase(it);
  }

  void insert(pair_t &&p) {
    this->push_back(std::move(p));
  }
};

template <typename V>
class small_map<const char *, V> : public std::vector<std::pair<const char *, V>> {
 private:
  using pair_t = std::pair<const char *, V>;
  using super = std::vector<pair_t>;

 public:
  using super::super;
  small_map() {
    g_small_map_count++;
  }
  // small_map() {    s_count++;  }
  typename std::vector<pair_t>::iterator find(const char *k) noexcept {
    return std::find_if(this->begin(), this->end(), [k](pair_t &p) { return strcmp(p.first, k) == 0; });
  }
  typename const std::vector<pair_t>::const_iterator find(const char *k) const noexcept {
    return std::find_if(this->cbegin(), this->cend(), [k](const pair_t &p) { return strcmp(p.first, k) == 0; });
  }

  typename const std::vector<pair_t>::const_iterator find(const std::string &k) const noexcept {
    return find(k.c_str());
  }

  typename std::vector<pair_t>::iterator find(const std::string &k) noexcept {
    return find(k.c_str());
  }

  V &operator[](const char *k) {
    auto it = find(k);
    if (it == this->end()) {
      this->push_back(make_pair(k, V{}));
      it = find(k);
    }
    return it->second;
  }
};

// template <typename V> uint32_t small_map<const char *, V>::s_count = 0;

template <typename V>
class simple_map : public small_map<const char *, V> {};
