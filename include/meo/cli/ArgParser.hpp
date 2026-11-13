#pragma once

#include <string>
#include <filesystem>

struct Args {
  bool showHelp         = 0;
  bool showVersion      = 0;
  bool error            = 0;

  std::filesystem::path inputFilePath;
  std::filesystem::path outputFilePath;
  std::filesystem::path debugLogPath;
};

namespace ArgParser {
  // Implementation of ArgParser functions

  Args parse(int argc, char* argv[]);
}; // namespace ArgParser
