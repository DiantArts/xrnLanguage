#pragma once

namespace xrn::language::detail {

static inline const ::std::vector<::std::string> keywords{
    "Int", "I8", "I16", "I32", "I64",
    "Float", "F8", "F16", "F32", "F64",
    "Char", "Bool", "true", "false", "Size", "String", "Auto",
    "Vector", "Array", "View",
    "class", "ability",
    "if", "else", "for", "while", "in", "return",
    "import", "export"
};

static inline const ::std::vector<::std::string> specialMemberFunctions{
    "__new",
    "__delete",
    "__new_copy",
    "__copy",
    "__new_move",
    "__move",
    "__op",
    "__type",
    "__print"
};

// value, precedent
static inline const ::std::map<::std::string, ::std::uint8_t> operators{
    { "!", 2 },
    { "*", 3 },
    { "/", 3 },
    { "%", 3 },
    { "+", 4 },
    { "-", 4 },
    { "=", 14 }
};

static inline const ::std::map<::std::string, ::std::uint8_t> comparators{
    { ">", 6 },
    { ">=", 6 },
    { "<", 6 },
    { "<=", 6 },
    { "==", 7 },
    { "!=", 7 },
    { "&", 11 }, // logical and
    { "|", 12 } // logical or
};
static inline const ::std::map<::std::string, ::std::uint8_t> accessors{
    { ".", 1 },
    { "->", 1 },
    { "::", 1 }
};
static inline const ::std::map<::std::string, ::std::uint8_t> separators{
    { "(", 1 },
    { "[", 1 },
    { "{", 0 },
    { "}", 0 },
    { "]", 1 },
    { ")", 1 },
    { ":", 0 }, // type assignator
    { ";", 0 },
    { ",", 15 }
};

static inline const ::std::vector<::std::string> strings{ "\"" };
static inline const ::std::vector<::std::string> characters{ "'" };
static inline const ::std::vector<::std::string> lineComments{ "#" };
static inline const ::std::vector<::std::string> beginMultiLineComments{ "#*" };
static inline const ::std::vector<::std::string> endMultilineComments{ "*#" };

} // namespace xrn::language
