#include <iostream>
#include <fstream>

#include <meo/cli/ArgParser.hpp>
#include <meo/common/Metadata.hpp>
#include <meo/core/Lexer.hpp>

void show_help() {
  std::cout << "Meo - (Supposed to be) a dirty scripting language for experimental purposes" << std::endl;

  std::cout << "Usage: " << std::endl \
            << "  meo [options] <script_file>" << std::endl \
            << "Options:" << std::endl \
            << "  -h, --help      Show this help message" << std::endl \
            << "  -v, --version   Show version information" << std::endl \
            << "  -i, --input     Specify input file path" << std::endl \
            << "  -o, --output    Specify output file path" << std::endl \
            << "  -d, --debug-log Specify debug log file path" << std::endl;
}

void show_version() {
  std::cout << "Meo - (Supposed to be) a dirty scripting language for experimental purposes" << std::endl;

  std::cout << "Version: " << Metadata::version.major \
            << "." << Metadata::version.minor \
            << "." << Metadata::version.patch << std::endl;

  std::cout << "Author: " << Metadata::authors[0].name \
            << " <" << Metadata::authors[0].email << ">" << std::endl;
}

int main(int argc, char* argv[]) {
  Args args = ArgParser::parse(argc, argv);
  
  if (args.error) {
    std::cerr << "Error: Invalid command line arguments" << std::endl;
    show_help();
    return 1;
  }

  if (args.showHelp) {
    show_help();
    return 0;
  }

  if (args.showVersion) {
    show_version();
    return 0;
  }

  if (!args.inputFilePath.empty()) {
    std::ifstream inputFile(args.inputFilePath);
    if (!inputFile) {
      std::cerr << "Error: Could not open input file: " << args.inputFilePath << std::endl;
      return 1;
    }

    std::string sourceCode(
      (std::istreambuf_iterator<char>(inputFile)),
      std::istreambuf_iterator<char>()
    );
    Lexer::lex(sourceCode);
  } else {
    std::cerr << "Error: No input file specified" << std::endl;
    show_help();

    return 1;
  }
}