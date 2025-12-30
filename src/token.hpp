#pragma once

#include <string>
#include <variant>

enum class TokenType {
    // Literals
    Identifier, // main, [A-Za-z_]+ [A-Za-z0-9_]*
    Integer,    // 12345
    Floating,   // 2.34
    Character,  // 'a'
    String,     // "abc"
    Constant,

    // Operators
    Add,       // +
    Subtract,  // -
    Multiply,  // *
    Divide,    // /
    Remainder, // %
    Invert,    // ~

    BitwiseAnd,        // &
    BitwiseOr,         // |
    BitwiseXor,        // ^
    BitwiseShiftLeft,  // <<
    BitwiseShiftRight, // >>

    AddAssignment,       // +=
    SubtractAssignment,  // -=
    MultiplyAssignment,  // *=
    DivideAssignment,    // /=
    RemainderAssignment, // %=
    InvertAssignment,    // ~=

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

    Pointer,
    TypeName,
    Typedef, // typedef

    // Delimiters
    OpenParenthesis,    // (
    OpenSquareBracket,  // [
    OpenCurlyBrace,     // {
    CloseParenthesis,   // )
    CloseSquareBracket, // ]
    CloseCurlyBrace,    // }

    Comma,       // ,
    Dot,         // .
    Semicolon,   // ;
    Colon,       // :
    SingleQuote, // '
    DoubleQuote, // "

    // Keywords
    Asm,
    Auto,     // auto
    Break,    // break
    Case,     // case
    Const,    // const
    Continue, // continue
    Bool,     // bool
    True,     // true
    False,    // false
    Default,  // default
    Do,       // do
    Else,     // else
    For,      // for
    Enum,     // enum
    Extern,   // extern
    Int,      // int
    Char,     // char
    Double,   // double
    Float,    // float
    Long,     // long
    Register, // register
    Short,    // short
    Signed,   // signed
    Sizeof,   // sizeof
    Static,   // static
    Struct,   // struct
    Undef,    // undef
    Union,    // union
    Unsigned, // unsigned
    Void,     // void
    Volatile, // volatile
    While,    // while

    Function,
    Goto, // goto
    If,   // if
    Import,

    Return, // return

    Switch, // switch

    // built-in data types
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

    // Special tokens
    Unknown,
    Error,
    Eof,
    Comment,
    Count
};

struct Token {
    TokenType                                                      type;
    std::variant< std::monostate, std::string, double, long long > literal;
    std::string_view                                               lexeme;
    size_t                                                         position;
    unsigned int                                                   line;
    unsigned int                                                   column;
};
