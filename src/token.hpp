#pragma once

#include <string>

enum class Types {
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

    // Special tokens
    Error,
    Eof,
    Comment,
    Id,
    Count
};

class Token {
  private:
    enum Types   type;
    std::string  literal;
    std::string  lexeme;
    unsigned int line;
    unsigned int column;
    size_t       position;

  public:
    Token( enum Types type, std::string literal, std::string lexeme,
           unsigned int line, unsigned int column, size_t position )
        : type( type ), literal( literal ), lexeme( lexeme ), line( line ),
          column( column ), position( position ) {}
};
