#include <meo/cli/ArgParser.hpp>

Args ArgParser::parse(int argc, char* argv[]) {
    Args args;

    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];

      if (arg == "--help" or arg == "-h") {
        args.showHelp = 1;
      }

      else if (arg == "--version" or arg == "-v") {
        args.showVersion = 1;
      }

      else if (arg == "--input" or arg == "-i") {
        if (i + 1 < argc) {
          args.inputFilePath = argv[++i];
        } else {
          args.error = 1;
        }
      }

      else if (arg == "--output" or arg == "-o") {
        if (i + 1 < argc) {
          args.outputFilePath = argv[++i];
        } else {
          args.error = 1;
        }
      }

      else if (arg == "--debug-log" or arg == "-d") {
        if (i + 1 < argc) {
          args.debugLogPath = argv[++i];
        } else {
          args.error = 1;
        }
      }

      // Add more argument parsing logic here

      // Return error if an unknown/invalid argument is encountered
      else {
        args.error = 1;
      }
    }

    return args;
  }

// Currently everything is in the header file