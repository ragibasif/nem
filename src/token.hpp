#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>

// Debug macro - disabled by default, can be enabled with -DDEBUG=1
#ifndef DEBUG
#define DEBUG 0
#endif

#define TRACE fprintf(stderr, "[%s:%d (%s)]\n", __FILE__, __LINE__, __func__);

namespace nem {

enum class TokenType {
  // Literals
  Identifier,
  Integer,
  Floating,
  Character,
  String,
  Constant,

  // Operators
  Add,
  Subtract,
  Multiply,
  Divide,
  Remainder,
  Invert,
  BitwiseAnd,
  BitwiseOr,
  BitwiseXor,
  BitwiseShiftLeft,
  BitwiseShiftRight,
  AddAssignment,
  SubtractAssignment,
  MultiplyAssignment,
  DivideAssignment,
  RemainderAssignment,
  InvertAssignment,
  BitwiseAndAssignment,
  BitwiseOrAssignment,
  BitwiseXorAssignment,
  BitwiseShiftLeftAssignment,
  BitwiseShiftRightAssignment,
  LogicalAnd,
  LogicalOr,
  Arrow,
  Increment,
  Decrement,
  Equal,
  Less,
  Greater,
  Assignment,
  Not,
  Question,
  NotEqual,
  LessEqual,
  GreaterEqual,
  Ellipsis,
  Pointer,
  TypeName,
  Typedef,

  // Delimiters
  OpenParenthesis,
  OpenSquareBracket,
  OpenCurlyBrace,
  CloseParenthesis,
  CloseSquareBracket,
  CloseCurlyBrace,
  Comma,
  Dot,
  Semicolon,
  Colon,
  SingleQuote,
  DoubleQuote,

  // Keywords
  Asm,
  Auto,
  Break,
  Case,
  Const,
  Continue,
  Bool,
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
  Double,
  Float,
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
  Void,
  Volatile,
  While,
  Function,
  Goto,
  If,
  Import,
  Return,
  Switch,

  // Fixed-width types
  Int8,
  Uint8,
  Int16,
  Uint16,
  Int32,
  Uint32,
  Int64,
  Uint64,
  Flt32,
  Flt64,

  // Special tokens
  Unknown,
  Error,
  Eof,
  Comment,
  Count
};

inline std::string id(TokenType type) {
#if DEBUG
  TRACE;
#endif
  static const std::unordered_map<TokenType, std::string> types = {
      // Literals
      {TokenType::Identifier, "Identifier"},
      {TokenType::Integer, "Integer"},
      {TokenType::Floating, "Floating"},
      {TokenType::Character, "Character"},
      {TokenType::String, "String"},
      {TokenType::Constant, "Constant"},

      // Keywords
      {TokenType::Auto, "auto"},
      {TokenType::Case, "case"},
      {TokenType::Const, "const"},
      {TokenType::Default, "default"},
      {TokenType::Double, "double"},
      {TokenType::Enum, "enum"},
      {TokenType::Float, "float"},
      {TokenType::Goto, "goto"},
      {TokenType::Int, "int"},
      {TokenType::Register, "register"},
      {TokenType::Short, "short"},
      {TokenType::Sizeof, "sizeof"},
      {TokenType::Struct, "struct"},
      {TokenType::Typedef, "typedef"},
      {TokenType::Unsigned, "unsigned"},
      {TokenType::Volatile, "volatile"},
      {TokenType::Break, "break"},
      {TokenType::Char, "char"},
      {TokenType::Continue, "continue"},
      {TokenType::Do, "do"},
      {TokenType::Else, "else"},
      {TokenType::Extern, "extern"},
      {TokenType::For, "for"},
      {TokenType::If, "if"},
      {TokenType::Long, "long"},
      {TokenType::Return, "return"},
      {TokenType::Signed, "signed"},
      {TokenType::Static, "static"},
      {TokenType::Switch, "switch"},
      {TokenType::Union, "union"},
      {TokenType::Void, "void"},
      {TokenType::While, "while"},
      {TokenType::Asm, "asm"},
      {TokenType::Bool, "bool"},
      {TokenType::True, "true"},
      {TokenType::False, "false"},
      {TokenType::Undef, "undef"},
      {TokenType::Function, "function"},
      {TokenType::Import, "import"},

      // Fixed-width Types
      {TokenType::Int8, "int8_t"},
      {TokenType::Uint8, "uint8_t"},
      {TokenType::Int16, "int16_t"},
      {TokenType::Uint16, "uint16_t"},
      {TokenType::Int32, "int32_t"},
      {TokenType::Uint32, "uint32_t"},
      {TokenType::Int64, "int64_t"},
      {TokenType::Uint64, "uint64_t"},
      {TokenType::Flt32, "float32"},
      {TokenType::Flt64, "float64"},

      // Operators
      {TokenType::Ellipsis, "..."},
      {TokenType::BitwiseShiftRightAssignment, ">>="},
      {TokenType::BitwiseShiftLeftAssignment, "<<="},
      {TokenType::AddAssignment, "+="},
      {TokenType::SubtractAssignment, "-="},
      {TokenType::MultiplyAssignment, "*="},
      {TokenType::DivideAssignment, "/="},
      {TokenType::RemainderAssignment, "%="},
      {TokenType::BitwiseAndAssignment, "&="},
      {TokenType::BitwiseXorAssignment, "^="},
      {TokenType::BitwiseOrAssignment, "|="},
      {TokenType::BitwiseShiftRight, ">>"},
      {TokenType::BitwiseShiftLeft, "<<"},
      {TokenType::Increment, "++"},
      {TokenType::Decrement, "--"},
      {TokenType::Arrow, "->"},
      {TokenType::LogicalAnd, "&&"},
      {TokenType::LogicalOr, "||"},
      {TokenType::LessEqual, "<="},
      {TokenType::GreaterEqual, ">="},
      {TokenType::Equal, "=="},
      {TokenType::NotEqual, "!="},
      {TokenType::Semicolon, ";"},
      {TokenType::OpenCurlyBrace, "{"},
      {TokenType::CloseCurlyBrace, "}"},
      {TokenType::Comma, ","},
      {TokenType::Colon, ":"},
      {TokenType::Assignment, "="},
      {TokenType::OpenParenthesis, "("},
      {TokenType::CloseParenthesis, ")"},
      {TokenType::OpenSquareBracket, "["},
      {TokenType::CloseSquareBracket, "]"},
      {TokenType::Dot, "."},
      {TokenType::BitwiseAnd, "&"},
      {TokenType::Not, "!"},
      {TokenType::Invert, "~"},
      {TokenType::Subtract, "-"},
      {TokenType::Add, "+"},
      {TokenType::Multiply, "*"},
      {TokenType::Divide, "/"},
      {TokenType::Remainder, "%"},
      {TokenType::Less, "<"},
      {TokenType::Greater, ">"},
      {TokenType::BitwiseXor, "^"},
      {TokenType::BitwiseOr, "|"},
      {TokenType::Question, "?"},
      {TokenType::SingleQuote, "'"},
      {TokenType::DoubleQuote, "\""},
      {TokenType::Pointer, "* (pointer)"},
      {TokenType::TypeName, "typename"},
      {TokenType::InvertAssignment, "~="},

      // Special
      {TokenType::Unknown, "Unknown"},
      {TokenType::Error, "Error"},
      {TokenType::Eof, "EOF"},
      {TokenType::Comment, "Comment"},
      {TokenType::Count, "Count"}};

  auto it = types.find(type);
  return (it != types.end()) ? it->second : "Undefined_Token";
}

struct Token {
  TokenType type;
  std::variant<std::monostate, std::string, double, long long> literal;
  std::string_view lexeme;
  size_t position;
  unsigned int line;
  unsigned int column;

  void print() const {
#if DEBUG
    TRACE;
#endif

    std::cout << "<Token> ";
    std::cout << "type: " << id(type) << " | ";
    std::cout << "lexeme: " << lexeme << " | ";
    std::cout << "position: " << position << " | ";
    std::cout << "line: " << line << " | ";
    std::cout << "column: " << column << '\n';
  }
};

}  // namespace nem
