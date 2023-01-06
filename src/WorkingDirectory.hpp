#ifndef WORKINGDIRECTORY_HPP
#define WORKINGDIRECTORY_HPP

#include <string>

class WorkingDirectory {
 public:
  WorkingDirectory(const std::string& folder);
  inline const std::string& Get() { return path; }

 private:
  std::string path;
};

#endif