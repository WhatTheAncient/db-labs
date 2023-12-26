#pragma once

#include <string>

class Sample {
  private:
    std::string name;
  public:
    Sample() = default;
    Sample(std::string name): name(std::move(name)){};
    Sample(const Sample& other): name(other.name) {};
    Sample& operator=(const Sample& other) { name = other.name; return *this; };
    Sample(Sample&&) noexcept = default;
    Sample& operator=(Sample&&) noexcept = default;
    ~Sample() = default;

    friend bool operator==(const Sample& lha, const Sample& rha) {
      return lha.name == rha.name;
    }

    friend bool operator!=(const Sample& lha, const Sample& rha) {
      return lha.name != rha.name;
    }
};
