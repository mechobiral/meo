#pragma once

#include <string>

namespace Metadata {
  struct AuthorInfo {
    std::string name;
    std::string email;
  };

  struct VersionInfo {
    int major;
    int minor;
    int patch;
  };

  const AuthorInfo authors[] = {
    { "Mehedi Rahman Mahi", "mehedirm.mahi@proton.me" },
  };

  const VersionInfo version = { 0, 0, 1 };
}; // namespace Metadata