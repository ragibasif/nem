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

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace nem {

enum class TokenType {
    // Special tokens
    Error,
    Eof,
    Comment,

    // Literals
    Identifier, // main
    Number,     // 12345
    Digit,      // [0-9]
    Integer,    // 12345
    Double,
    Float,     // 123.45
    Character, // 'a'
    String,    // "abc"
    Constant,

    // Operators
    Plus,     // +
    Minus,    // -
    Multiply, // *
    Divide,   // /
    Modulo,   // %
    Invert,   // ~

    BitwiseAnd,        // &
    BitwiseOr,         // |
    BitwiseXor,        // ^
    BitwiseShiftLeft,  // <<
    BitwiseShiftRight, // >>

    PlusAssignment,     // +=
    MinusAssignment,    // -=
    MultiplyAssignment, // *=
    DivideAssignment,   // /=
    ModuloAssignment,   // %=
    InvertAssignment,   // ~=

    BitwiseAndAssignment,        // &=
    BitwiseOrAssignment,         // |=
    BitwiseXorAssignment,        // ^=
    BitwiseShiftLeftAssignment,  // <<=
    BitwiseShiftRightAssignment, // >>=

    LogicalAnd, // &&
    LogicalOr,  // ||
    Arrow,      // ->
    Increment,  // ++
    Decrement,  // --

    Equal,      // ==
    Less,       // <
    Greater,    // >
    Assignment, // =
    Not,        // !
    Question,   // ?

    NotEqual,     // !=
    LessEqual,    // <=
    GreaterEqual, // >=
    Ellipsis,     // ...
    Define,       // :=

    Pointer,
    TypeName,
    Typedef,

    // Delimiters
    OpenParenthesis,    // (
    OpenSquareBracket,  // [
    OpenCurlyBrace,     // {
    CloseParenthesis,   // )
    CloseSquareBracket, // ]
    CloseCurlyBrace,    // }

    Comma,       // ,
    Period,      // .
    Semicolon,   // ;
    Colon,       // :
    SingleQuote, // '
    DoubleQuote, // "

    // Keywords
    Asm,
    Auto,
    Break,
    Case,
    Const,
    Continue,
    Print,
    True,
    False,

    Default,
    Do,
    Else,
    For,
    Enum,
    Extern,
    Int,
    Char,
    Long,
    Register,
    Short,
    Signed,
    Sizeof,
    Static,
    Struct,
    Undef,
    Union,
    Unsigned,
    Volatile,
    While,

    Function,
    Goto,
    If,
    Import,

    Return,

    Switch,
    Variable, // [A-Za-z_]+ [A-Za-z0-9_]*
              // BUILT-in data types
    Void,
    Bool,
    Int8,   // char
    Uint8,  // unsigned char
    Int16,  // short
    Uint16, // unsigned short
    Int32,  // int
    Uint32, // unsigned int
    Int64,  // long long
    Uint64, // unsigned long long
    Flt32,  // float
    Flt64,  // double (64 bits)
            // Internal
    Id,
    Count
};

struct Token {
    enum TokenType   type;
    std::string      literal;
    std::string_view lexeme;
    unsigned int     line;
};

class Lexer {
  private:
    std::vector< Token > tokens;

    std::string            source;
    std::string            path;
    unsigned long long int line;
    unsigned long long int column;
    size_t                 position;

    void read() {
        constexpr auto read_size = std::size_t( 4096 );
        auto           stream    = std::ifstream( path.data() );
        stream.exceptions( std::ios_base::badbit );

        if ( not stream ) {
            throw std::ios_base::failure( "file does not exist" );
        }

        auto out = std::string();
        auto buf = std::string( read_size, '\0' );
        while ( stream.read( &buf[0], read_size ) ) {
            out.append( buf, 0, static_cast< size_t >( stream.gcount() ) );
        }
        out.append( buf, 0, static_cast< size_t >( stream.gcount() ) );
        source = out;
    }

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
    Lexer( std::string path ) : path( path ) {
        read();
        tokens   = std::vector< Token >();
        line     = 1;
        column   = 1;
        position = 0;
        dbg( source, line, column, position );
    }
};

} // namespace nem

int main( [[maybe_unused]] int argc, [[maybe_unused]] char **argv ) {

    auto wc_start  = std::chrono::high_resolution_clock::now();
    auto cpu_start = std::clock();

    nem::Token token;
    token.type    = nem::TokenType::Arrow;
    token.literal = "->";
    nem::Lexer lexer( "src/main.cpp" );

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
