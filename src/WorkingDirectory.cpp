#include "WorkingDirectory.hpp"

#include <string>

WorkingDirectory::WorkingDirectory(const std::string& folder) {
  path = "../" + folder + "/";
}