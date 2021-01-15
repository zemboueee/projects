#pragma once

#include <iostream>
#include <memory>
#include <string>

extern std::shared_ptr<std::ostream> NULLOSTREAM;

void init_logs();

class Log
{
  public:
    static bool display;
    Log(std::string tag);
    Log(std::string tag, bool error);

    void title();
    void title(size_t step);

    std::ostream &operator<<(std::string message);

  private:
    std::string tag_;
    bool error_;
};
