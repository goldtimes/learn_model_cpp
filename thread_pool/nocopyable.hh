#pragma once

namespace lihang
{
  class nocopyable
  {
  public:
    nocopyable(const nocopyable& other) = delete;
    void operator=(const nocopyable& other) = delete;

  protected:
    nocopyable() = default;
    ~nocopyable() = default;
  };
} // namespace lihang