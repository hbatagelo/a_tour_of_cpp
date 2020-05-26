#include <filesystem>
#include <iostream>

void print_directory(const std::filesystem::path& p) {
  try {
    if (std::filesystem::is_directory(p)) {
      std::cout << p << ":\n";
      for (const std::filesystem::directory_entry& x :
           std::filesystem::directory_iterator{p}) {
        std::cout << " " << x.path() << '\n';
      }
    }
  } catch (const std::filesystem::filesystem_error& ex) {
    std::cerr << ex.what() << '\n';
  }
}

////////////////////////////////////////////////////////////////////////////////

void test(const std::filesystem::path& p) {
  try {
    if (std::filesystem::is_directory(p)) {
      std::cout << p << ":\n";
      for (const std::filesystem::directory_entry& x :
           std::filesystem::directory_iterator{p}) {
        // Refer to the path part of a directory entry
        const std::filesystem::path& f{x};
        if (f.extension() == ".exe") {
          std::cout << f.stem() << " is a Windows executable\n";
        } else {
          std::string n = f.extension().string();
          if (n == ".cpp" || n == ".C" || n == ".cxx") {
            std::cout << f.stem() << " is a C++ source file\n";
          }
        }
      }
    }
  } catch (const std::filesystem::filesystem_error& ex) {
    std::cerr << ex.what() << '\n';
  }
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  print_directory(".");   // Current directory
  print_directory("..");  // Parent directory
  print_directory("/");   // Unix root directory
  print_directory("c:");  // Windows volume C

  for (std::string s; std::cin >> s;) {
    print_directory(s);
  }

  test(".");
}
