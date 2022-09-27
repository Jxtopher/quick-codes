#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Describe the unique version numbers.
 * It's compose in two part: version numbers and tags.
 * The version numbers is compose by: major, minor and patch
 * For example:
 *  - 2.1.2-beta
 *  - 2.2-alpine-apache
 * cf. https://en.wikipedia.org/wiki/Software_versioning
 */
class Version {
public:
  Version(const std::vector<unsigned long> &version,
          const std::vector<std::string> &tags)
      : m_version(version), m_tags(tags) {}

  Version(const std::string &version) {
    if (version.find("-") == std::string::npos) {
      split(version, '.', m_version);
    } else {
      split(version, '-', m_tags);
      split(m_tags[0], '.', m_version);
      m_tags.erase(m_tags.begin());
    }
  }

  std::string operator()() {
    std::string result;
    result += std::to_string(m_version[0]);
    for (uint i = 1; i < m_version.size(); i++)
      result += "." + std::to_string(m_version[i]);
    return result;
  }

  bool operator==(const Version &v) const {
    if (this->m_version.size() != v.m_version.size())
      return false;

    for (uint i = 0; i < this->m_version.size(); i++) {
      if (this->m_version[i] != v.m_version[i])
        return false;
    }
    return true;
  }

  bool operator!=(const Version &v) const { return !this->operator==(v); }

  bool operator<(const Version &v) const {
    assert(v.m_version.size() != 0);
    assert(this->m_version.size() != 0);

    uint i = this->m_version.size();
    uint j = v.m_version.size();

    while (i != 0 && j != 0) {
      if (this->m_version[this->m_version.size() - i] <
          v.m_version[v.m_version.size() - j]) {
        return true;
      } else if (this->m_version[this->m_version.size() - i] >
                 v.m_version[v.m_version.size() - j]) {
        return false;
      }
      i--;
      j--;
    }

    return false;
  }

  bool operator<=(const Version &v) const {
    return this->operator<(v) || this->operator==(v);
  }

  bool operator>(const Version &v) const { return !this->operator<(v); }

  bool operator>=(const Version &v) const {
    return this->operator>(v) || this->operator==(v);
  }

  unsigned long major() const { return this->m_version[0]; }

  void major(unsigned long val) {
    while (this->m_version.size() < 1)
      this->m_version.push_back(0);
    this->m_version[0] = val;
  }

  unsigned long minor() const { return this->m_version[1]; }

  void minor(unsigned long val) {
    while (this->m_version.size() < 2)
      this->m_version.push_back(0);
    this->m_version.at(1) = val;
  }

  unsigned long patch() const { return this->m_version[2]; }

  void patch(unsigned long val) {
    while (this->m_version.size() < 3)
      this->m_version.push_back(0);
    this->m_version[2] = val;
  }

  friend std::ostream &operator<<(std::ostream &out, const Version &version) {
    out << version.m_version[0];
    for (uint i = 1; i < version.m_version.size(); i++)
      out << "." << version.m_version[i];
    return out;
  }

private:
  // see: https://stackoverflow.com/a/16749483
  void split(const std::string &s, char delim,
             std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      if (item.length() > 0) {
        elems.push_back(item);
      }
    }
  }

  void split(const std::string &s, char delim,
             std::vector<unsigned long> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
      if (item.length() > 0) {
        elems.push_back(std::stoul(item));
      }
    }
  }

  std::vector<unsigned long> m_version;
  std::vector<std::string> m_tags;
};

void test() {
  Version v1{"44.33.22"};
  Version v2{"44.33.22"};
  assert(v1 == v2);
  assert(!(v1 != v2));
  assert(!(v1 < v2));
  Version v3{"44.33.22"};
  Version v4{"44.33.10"};
  assert(v4 < v3);
  assert(!(v4 > v3));

  Version v5{"2.1"};
  Version v6{"2.0.1"};
  assert(v6 < v5);

  Version v7("44.33.22-apache-full");
}

int main() {
  test();
  return 0;
}