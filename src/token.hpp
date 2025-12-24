#pragma once

enum class Token {
    // Literals
    Identifier, // main
    Number,     // 12345
    Digit,      // [0-9]
    Integer,    // 12345
    Double,     // double
    Float,      // float
    Character,  // 'a'
    String,     // "abc"
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

    Switch,   // switch
    Variable, // [A-Za-z_]+ [A-Za-z0-9_]*

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
    Eof,
    Comment,
    Id,
    Count
};
