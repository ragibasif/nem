// Debug - disabled by default, can be enabled with -DDEBUG=1
#ifndef DEBUG
#define DEBUG 0
#endif

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "src/lexer.hpp"
#include "src/token.hpp"

std::string read(std::string path) {
  constexpr auto read_size = std::size_t(4096);
  auto stream = std::ifstream(path.data());
  stream.exceptions(std::ios_base::badbit);

  if (not stream) {
    throw std::ios_base::failure("file does not exist");
  }

  auto out = std::string();
  auto buf = std::string(read_size, '\0');
  while (stream.read(&buf[0], read_size)) {
    out.append(buf, 0, static_cast<size_t>(stream.gcount()));
  }
  out.append(buf, 0, static_cast<size_t>(stream.gcount()));
  return out;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  auto wc_start = std::chrono::high_resolution_clock::now();
  auto cpu_start = std::clock();

  std::string buffer = read("tests/main.c");

  using namespace nem;

  Lexer lexer(buffer);
  std::vector<nem::Token> tokens = lexer.tokenize();

  auto wc_end = std::chrono::high_resolution_clock::now();
  auto cpu_end = std::clock();
  double wc_duration =
      std::chrono::duration<double, std::milli>(wc_end - wc_start).count();
  double cpu_duration =
      (static_cast<double>(cpu_end - cpu_start) / CLOCKS_PER_SEC) * 1000.0;

  std::cerr << "\n[Wall Clock] Finished in: " << wc_duration
            << " milliseconds.\n"
            << "[CPU Time] Finished in: " << cpu_duration << " milliseconds.\n"
            << std::flush;

  return EXIT_SUCCESS;
}
