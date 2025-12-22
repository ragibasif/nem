#pragma once

// Debug - disabled by default, can be enabled with -DDEBUG=1
#ifndef DEBUG
#define DEBUG 0
#endif

// Test - disabled by default, can be enabled with -DTEST=1
#ifndef TEST
#define TEST 0
#endif

#include "dbg.h"
#include "token.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace nem {

class Lexer {
  private:
    std::vector< Token > tokens;

    std::string            source;
    std::string            path;
    unsigned long long int line;
    unsigned long long int column;
    size_t                 position;

    static bool is_alpha( const char ch ) {
        return ( 'a' <= ch && ch <= 'z' ) || ( 'A' <= ch && ch <= 'Z' ) ||
               ch == '_';
    }

    static bool is_digit( const char ch ) { return '0' <= ch && ch <= '9'; }

    static bool is_alnum( const char ch ) {
        return is_alpha( ch ) || is_digit( ch );
    }

    char next() { return source[position++]; }

    void scan(); // TODO

    char peek() {
        if ( position >= source.size() ) { return '\0'; }
        return source[position];
    }

    char double_peek() {
        if ( position + 1 >= source.size() ) { return '\0'; }
        return source[position + 1];
    }

  public:
    Lexer( std::string source ) : source( source ) {
        tokens   = std::vector< Token >();
        line     = 1;
        column   = 1;
        position = 0;
        dbg( source, line, column, position );
    }
};

} // namespace nem

std::string read( std::string path ) {
    constexpr auto read_size = std::size_t( 4096 );
    auto           stream    = std::ifstream( path.data() );
    stream.exceptions( std::ios_base::badbit );

    if ( not stream ) { throw std::ios_base::failure( "file does not exist" ); }

    auto out = std::string();
    auto buf = std::string( read_size, '\0' );
    while ( stream.read( &buf[0], read_size ) ) {
        out.append( buf, 0, static_cast< size_t >( stream.gcount() ) );
    }
    out.append( buf, 0, static_cast< size_t >( stream.gcount() ) );
    return out;
}

int main( [[maybe_unused]] int argc, [[maybe_unused]] char **argv ) {

    auto wc_start  = std::chrono::high_resolution_clock::now();
    auto cpu_start = std::clock();

    nem::Lexer lexer( read( "src/main.cpp" ) );

    auto   wc_end  = std::chrono::high_resolution_clock::now();
    auto   cpu_end = std::clock();
    double wc_duration =
        std::chrono::duration< double, std::milli >( wc_end - wc_start )
            .count();
    double cpu_duration =
        ( static_cast< double >( cpu_end - cpu_start ) / CLOCKS_PER_SEC ) *
        1000.0;

    std::cerr << "\n[Wall Clock] Finished in: " << wc_duration
              << " milliseconds.\n"
              << "[CPU Time] Finished in: " << cpu_duration
              << " milliseconds.\n"
              << std::flush;

    return EXIT_SUCCESS;
}
