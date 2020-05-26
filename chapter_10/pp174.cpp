#include <cassert>
#include <filesystem>
#include <fstream>
#include <gsl/gsl>
#include <iostream>

void use1() {
  std::filesystem::path f{"dir/hypothetical.cpp"};  // Naming a file
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(std::filesystem::exists(f));  // f must exit

  if (std::filesystem::is_regular_file(f)) {  // Is f an ordinary file?
    std::cout << f << " is a file; its size is "
              << std::filesystem::file_size(f) << '\n';
  }
}

////////////////////////////////////////////////////////////////////////////////

void use2(const std::filesystem::path& p) {
  std::ofstream f{p};
  if (!f) {
    std::cerr << "bad file name: " << p << '\n';
    return;
  }
  f << "Hello, file!";
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char* argv[]) {
  if (argc < 2) {
    std::cerr << "arguments expected\n";
    return 1;
  }
  gsl::span<const char*> args(argv, static_cast<std::size_t>(argc));

  // Create a path from the command line
  std::filesystem::path p{args[1]};

  // Note: a path can be printed like a string
  std::cout << p << " " << std::filesystem::exists(p) << '\n';

  use2("test.txt");
}
