#pragma once

#include <string>
#include <unordered_map>
#include <variant>

enum class TokenType {
    // Literals
    Identifier, // main, [A-Za-z_]+ [A-Za-z0-9_]*
    Number,     // 12345
    Double,     // double
    Float,      // float
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
    Print,
    True,  // true
    False, // false

    Default,  // default
    Do,       // do
    Else,     // else
    For,      // for
    Enum,     // enum
    Extern,   // extern
    Int,      // int
    Char,     // char
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
    Volatile, // volatile
    While,    // while

    Function,
    Goto, // goto
    If,   // if
    Import,

    Return, // return

    Switch, // switch

    // built-in data types
    Void,   // void
    Bool,   // bool
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
    Error,
    Unknown,
    Eof,
    Comment,
    Count
};

struct Token {
    TokenType                                                      type;
    std::variant< std::monostate, std::string, double, long long > literal;
    std::string_view                                               lexeme;
    int                                                            position;
    int                                                            line;
    int                                                            column;
};

inline const std::unordered_map< std::string, TokenType > keywords = {
    { "auto", TokenType::Auto },         { "break", TokenType::Break },
    { "case", TokenType::Case },         { "char", TokenType::Char },
    { "const", TokenType::Const },       { "continue", TokenType::Continue },
    { "default", TokenType::Default },   { "do", TokenType::Do },
    { "double", TokenType::Double },     { "else", TokenType::Else },
    { "enum", TokenType::Enum },         { "extern", TokenType::Extern },
    { "float", TokenType::Float },       { "for", TokenType::For },
    { "goto", TokenType::Goto },         { "if", TokenType::If },
    { "int", TokenType::Int },           { "long", TokenType::Long },
    { "register", TokenType::Register }, { "return", TokenType::Return },
    { "short", TokenType::Short },       { "signed", TokenType::Signed },
    { "sizeof", TokenType::Sizeof },     { "static", TokenType::Static },
    { "struct", TokenType::Struct },     { "switch", TokenType::Switch },
    { "typedef", TokenType::Typedef },   { "union", TokenType::Union },
    { "unsigned", TokenType::Unsigned }, { "void", TokenType::Void },
    { "volatile", TokenType::Volatile }, { "while", TokenType::While },
};

inline const std::unordered_map< std::string, TokenType > operators = {

    { "...", TokenType::Ellipsis },
    { ">>=", TokenType::BitwiseShiftRightAssignment },
    { "<<=", TokenType::BitwiseShiftLeftAssignment },
    { "+=", TokenType::AddAssignment },
    { "-=", TokenType::SubtractAssignment },
    { "*=", TokenType::MultiplyAssignment },
    { "/=", TokenType::DivideAssignment },
    { "%=", TokenType::RemainderAssignment },
    { "&=", TokenType::BitwiseAndAssignment },
    { "^=", TokenType::BitwiseXorAssignment },
    { "|=", TokenType::BitwiseOrAssignment },
    { ">>", TokenType::BitwiseShiftLeft },
    { "<<", TokenType::BitwiseShiftRight },
    { "++", TokenType::Increment },
    { "--", TokenType::Decrement },
    { "->", TokenType::Arrow },
    { "&&", TokenType::LogicalAnd },
    { "||", TokenType::LogicalOr },
    { "<=", TokenType::LessEqual },
    { ">=", TokenType::GreaterEqual },
    { "==", TokenType::Equal },
    { "!=", TokenType::NotEqual },
    { ";", TokenType::Semicolon },
    { "{", TokenType::OpenCurlyBrace },
    { "}", TokenType::CloseCurlyBrace },
    { ",", TokenType::Comma },
    { ":", TokenType::Colon },
    { "=", TokenType::Assignment },
    { "(", TokenType::OpenParenthesis },
    { ")", TokenType::CloseParenthesis },
    { "[", TokenType::OpenSquareBracket },
    { "]", TokenType::CloseSquareBracket },
    { ".", TokenType::Dot },
    { "&", TokenType::BitwiseAnd },
    { "!", TokenType::Not },
    { "~", TokenType::Invert },
    { "-", TokenType::Subtract },
    { "+", TokenType::Add },
    { "*", TokenType::Multiply },
    { "/", TokenType::Divide },
    { "%", TokenType::Remainder },
    { "<", TokenType::Less },
    { ">", TokenType::Greater },
    { "^", TokenType::BitwiseXor },
    { "|", TokenType::BitwiseOr },
    { "?", TokenType::Question },

};
