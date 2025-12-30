#pragma once

#include "token.hpp"

#include <iostream>
#include <vector>

class Lexer {
  public:
    Lexer( std::string_view source ) : source( source ) {}

    std::vector< Token > tokenize() {
        std::vector< Token > tokens;

        while ( !end() ) {
            Token token = scan();
            if ( token.type != TokenType::Comment ) {
                tokens.emplace_back( token );
            }
        }

        tokens.emplace_back(
            Token{ TokenType::Eof, {}, "", position, line, column } );
        return tokens;
    }

  private:
    std::string_view source;
    size_t           start    = 0; // start of current lexeme
    size_t           current  = 0; // current character being looked at
    size_t           position = 0; // absolute offset
    unsigned int     line     = 1;
    unsigned int     column   = 1;

    static bool is_alpha( const char c ) {
        return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) || c == '_';
    }

    static bool is_alnum( const char c ) {
        return is_alpha( c ) || is_digit( c );
    }

    static bool is_digit( const char c ) { return c >= '0' && c <= '9'; }

    bool end() const { return current >= source.size(); }

    char next() {
        char c = source[current];
        current++;
        column++;
        position++;
        return c;
    }

    char peek() {
        if ( end() ) { return '\0'; }
        return source[current];
    }

    char peek_next() {
        if ( end() || ( current + 1 >= source.size() ) ) { return '\0'; }
        return source[current + 1];
    }

    bool match( char expected ) {
        if ( end() || source[current] != expected ) { return false; }
        current++;
        column++;
        return true;
    }

    Token make_token( TokenType type ) {
        std::string_view text = source.substr( start, current - start );
        return Token{ type, std::monostate{}, text, position, line, column };
    }

    // white space and comments
    void skip() {
        while ( true ) {
            char c = peek();
            switch ( c ) {
                case ' ': {
                    [[fallthrough]];
                }
                case '\r': {
                    [[fallthrough]];
                }
                case '\t': {
                    next();
                    break;
                }
                case '\n': {
                    line++;
                    column = 1;
                    next();
                    break;
                }
                case '/': {
                    if ( peek_next() == '/' ) {
                        // C++ style comments: //
                        while ( peek() != '\n' && !end() ) { next(); }
                    } else if ( peek_next() == '*' ) {
                        // C style comments-: /**/
                        next(); // '/'
                        next(); // '*'
                        while ( !( peek() == '*' && peek_next() == '/' ) &&
                                !end() ) {
                            if ( peek() == '\n' ) {
                                line++;
                                column = 1;
                            }
                            next();
                        }
                        if ( !end() ) {
                            next(); // '*'
                            next(); // '/'
                        }
                    } else {
                        return; // division operator
                    }
                    break;
                }
                default: return;
            }
        }
    }

    Token operators( const char c ) {
        switch ( c ) {
            // single-char operators
            case '(': {
                return make_token( TokenType::OpenParenthesis );
            }

            case ')': {
                return make_token( TokenType::CloseParenthesis );
            }

            case '[': {
                return make_token( TokenType::OpenSquareBracket );
            }

            case ']': {
                return make_token( TokenType::CloseSquareBracket );
            }

            case '{': {
                return make_token( TokenType::OpenCurlyBrace );
            }

            case '}': {
                return make_token( TokenType::CloseCurlyBrace );
            }

            case ';': {
                return make_token( TokenType::Semicolon );
            }

            case ',': {
                return make_token( TokenType::Comma );
            }

            case '?': {
                return make_token( TokenType::Question );
            }

            case '~': {
                return make_token( TokenType::Invert );
            }

            // multi-char operators
            case '.': {
                if ( match( '.' ) ) {
                    if ( match( '.' ) ) {
                        return make_token( TokenType::Ellipsis ); // ...
                    } else {
                        return make_token(
                            TokenType::Error ); // ".." is not a C token
                    }
                } else {
                    return make_token( TokenType::Dot );
                }
            }

            case '+': {
                if ( match( '+' ) ) {
                    return make_token( TokenType::Increment ); // ++
                } else if ( match( '=' ) ) {
                    return make_token( TokenType::AddAssignment ); // +=
                } else {
                    return make_token( TokenType::Add );
                }
            }

            case '-': {
                if ( match( '-' ) ) {
                    return make_token( TokenType::Decrement ); // --
                } else if ( match( '=' ) ) {
                    return make_token( TokenType::SubtractAssignment ); // -=
                } else if ( match( '>' ) ) {
                    return make_token( TokenType::Arrow ); // ->
                } else {
                    return make_token( TokenType::Subtract );
                }
            }

            case '>': {
                if ( match( '>' ) ) {
                    if ( match( '=' ) ) {
                        return make_token(
                            TokenType::BitwiseShiftRightAssignment ); // >>=
                    } else {
                        return make_token( TokenType::BitwiseShiftRight ); // >>
                    }
                } else if ( match( '=' ) ) {
                    return make_token( TokenType::GreaterEqual ); // >=
                } else {
                    return make_token( TokenType::Greater );
                }
            }

            case '<': {
                if ( match( '<' ) ) {
                    if ( match( '=' ) ) {
                        return make_token(
                            TokenType::BitwiseShiftLeftAssignment ); // <<=
                    } else {
                        return make_token( TokenType::BitwiseShiftLeft ); // <<
                    }
                } else if ( match( '=' ) ) {
                    return make_token( TokenType::LessEqual ); // <=
                } else {
                    return make_token( TokenType::Less );
                }
            }

            case '=': {
                return make_token( match( '=' ) ? TokenType::Equal
                                                : TokenType::Assignment );
            }

            case '!': {
                return make_token( match( '=' ) ? TokenType::NotEqual
                                                : TokenType::Not );
            }

            case '&': {
                if ( match( '&' ) ) {
                    return make_token( TokenType::LogicalAnd );
                } else if ( match( '=' ) ) {
                    return make_token( TokenType::BitwiseAndAssignment );
                } else {
                    return make_token( TokenType::BitwiseAnd );
                }
            }

            case '|': {
                if ( match( '|' ) ) {
                    return make_token( TokenType::LogicalOr );
                } else if ( match( '=' ) ) {
                    return make_token( TokenType::BitwiseOrAssignment );
                } else {
                    return make_token( TokenType::BitwiseOr );
                }
            }

            default: {
                return make_token( TokenType::Unknown );
            }
        }
    }

    TokenType keyword( int offset, int length, const char *rest,
                       TokenType type ) {
        std::string_view text = source.substr( start, current - start );

        // check length and remaining substring
        if ( static_cast< int >( text.size() ) == offset + length &&
             text.substr( static_cast< size_t >( offset ),
                          static_cast< size_t >( length ) ) == rest ) {
            return type;
        }
        return TokenType::Identifier;
    }

    void identifier() {}
    void number() {}
    void string() {}

    Token scan() {
        skip();
        start = current;

        const char c = next();

        if ( is_alpha( c ) ) {}
        if ( is_digit( c ) ) {}

        return operators( c );
    }
};

// const std::unordered_map< std::string, TokenType > keywords = {
//     { "auto", TokenType::Auto },         { "break", TokenType::Break },
//     { "case", TokenType::Case },         { "char", TokenType::Char },
//     { "const", TokenType::Const },       { "continue", TokenType::Continue },
//     { "default", TokenType::Default },   { "do", TokenType::Do },
//     { "double", TokenType::Double },     { "else", TokenType::Else },
//     { "enum", TokenType::Enum },         { "extern", TokenType::Extern },
//     { "float", TokenType::Float },       { "for", TokenType::For },
//     { "goto", TokenType::Goto },         { "if", TokenType::If },
//     { "int", TokenType::Int },           { "long", TokenType::Long },
//     { "register", TokenType::Register }, { "return", TokenType::Return },
//     { "short", TokenType::Short },       { "signed", TokenType::Signed },
//     { "sizeof", TokenType::Sizeof },     { "static", TokenType::Static },
//     { "struct", TokenType::Struct },     { "switch", TokenType::Switch },
//     { "typedef", TokenType::Typedef },   { "union", TokenType::Union },
//     { "unsigned", TokenType::Unsigned }, { "void", TokenType::Void },
//     { "volatile", TokenType::Volatile }, { "while", TokenType::While },
// };
