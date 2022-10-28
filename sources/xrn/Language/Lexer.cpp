///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Language/Lexer.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Lexer::run(
    ::xrn::language::Program& program
) noexcept
{
    auto lines{ program.getLines() };
    auto& tokens{ program.getTokens() };
    ::std::size_t xPos{ 0 };

    for (auto i{ 0uz }; i < lines.size(); ++i) {
        xPos = 0;
        while (!lines[i].empty()) {
            xPos += Lexer::lstrip(lines[i]);
            if (!lines[i].empty()) {
                ::std::string tokenValue;
                ::xrn::language::token::Type tokenType;
                Lexer::extractToken(lines[i], tokenValue, tokenType, i, xPos);

                switch (tokenType) {
                case ::xrn::language::token::Type::LINE_COMMENT: {
                    lines[i].erase(0, lines[i].size());
                    break;
                } case ::xrn::language::token::Type::MULTI_LINE_COMMENT: {
                    tokenValue += Lexer::skipTillNextChar(lines, i, xPos, ::xrn::language::detail::endMultilineComments);
                    lines[i].erase(0, xPos);
                    break;
                } case ::xrn::language::token::Type::STRING: {
                    tokenValue += Lexer::skipTillNextChar(lines, i, xPos, ::xrn::language::detail::strings);
                    tokenValue.erase(0, 1);
                    if (tokenValue.size()) {
                        tokenValue.erase(tokenValue.size() - 1);
                    }
                    lines[i].erase(0, xPos);
                    tokens.add(::std::make_shared<::xrn::language::token::Literal>(
                        tokenType, tokenValue, i, xPos
                    ));
                    break;
                } case ::xrn::language::token::Type::CHARACTER: {
                    tokenValue += Lexer::skipTillNextChar(lines, i, xPos, ::xrn::language::detail::characters);
                    tokenValue.erase(0, 1);
                    if (tokenValue.size()) {
                        tokenValue.erase(tokenValue.size() - 1);
                    }
                    lines[i].erase(0, xPos);
                    tokens.add(::std::make_shared<::xrn::language::token::Literal>(
                        tokenType, tokenValue, i, xPos
                    ));
                    break;
                } default:
                    tokens.add(::std::make_shared<::xrn::language::token::Literal>(
                        tokenType, tokenValue, i, xPos
                    ));
                    xPos += tokenValue.size();
                    break;
                }
            }
        }
        program.proposeMaxCharacterNumber(xPos);
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Parsing
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Lexer::extractToken(
    ::std::string& str,
    ::std::string& tokenValue,
    ::xrn::language::token::Type& tokenType,
    ::std::size_t yPos,
    ::std::size_t xPos
)
{
    ::std::smatch regexMatch;

    if (!(
        Lexer::matchIdentifiersAndKeywords(str, tokenValue, tokenType) ||
        Lexer::matchNumbers(str, tokenValue, tokenType) ||
        Lexer::matchWithList(str, tokenValue, tokenType, ::xrn::language::detail::operators, ::xrn::language::token::Type::OPERATOR) ||
        Lexer::matchWithList(str, tokenValue, tokenType, ::xrn::language::detail::comparators, ::xrn::language::token::Type::COMPARATOR) ||
        Lexer::matchWithList(str, tokenValue, tokenType, ::xrn::language::detail::accessors, ::xrn::language::token::Type::ACCESSOR) ||
        Lexer::matchWithList(str, tokenValue, tokenType, ::xrn::language::detail::separators, ::xrn::language::token::Type::SEPARATOR) ||
        Lexer::matchWithList(str, tokenValue, tokenType, ::xrn::language::detail::strings, ::xrn::language::token::Type::STRING) ||
        Lexer::matchWithList(str, tokenValue, tokenType, ::xrn::language::detail::characters, ::xrn::language::token::Type::CHARACTER) ||
        Lexer::matchWithList(str, tokenValue, tokenType, ::xrn::language::detail::beginMultiLineComments, ::xrn::language::token::Type::MULTI_LINE_COMMENT) ||
        Lexer::matchWithList(str, tokenValue, tokenType, ::xrn::language::detail::lineComments, ::xrn::language::token::Type::LINE_COMMENT)
    )) {
        // if none of the remaning possible match
        tokenValue = str.substr(0, str.size());
        str.erase(0, tokenValue.size());
    }
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Lexer::skipTillNextChar(
    ::std::vector<::std::string>& lines,
    ::std::size_t& yRef,
    ::std::size_t& xRef,
    const ::std::vector<::std::string>& vec
) -> ::std::string
{
    for (const auto& str : vec) {
        ::std::size_t count{ 0 };
        ::std::string ret;

        for (auto y{ yRef }; y < lines.size(); ++y) {
            for (auto x{ 0uz }; x < lines[y].size(); ++x) {
                ret += lines[y][x];
                if (lines[y][x] == str[count]) {
                    ++count;
                    if (count == str.size()) {
                        yRef = y;
                        xRef = x + 1;
                        return ret;
                    }
                } else {
                    count = 0;
                }
            }
            ret += '\n';
        }
    }
    return {};
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Lexer::matchIdentifiersAndKeywords(
    ::std::string& str,
    ::std::string& tokenValue,
    ::xrn::language::token::Type& tokenType
) -> bool
{
    if (::std::smatch regexMatch; Lexer::startsWith(str, regexMatch, "^[a-zA-Z][a-zA-Z0-9]*\\s*[(]")) {
        tokenValue = str.substr(0, regexMatch.str().size() - 1);
        if (const auto strIt{ tokenValue.find_last_not_of(" \t") }; strIt != ::std::string::npos) {
            tokenValue.erase(strIt + 1);
        }
        str.erase(0, tokenValue.size());

        for (const auto& elem : ::xrn::language::detail::keywords) {
            if (tokenValue == elem) {
                tokenType = ::xrn::language::token::Type::KEYWORD;
                return true;
            }
        }
        tokenType = ::xrn::language::token::Type::FUNCTION;
        return true;
    } else if (Lexer::startsWith(str, regexMatch, "^[a-zA-Z][a-zA-Z0-9]*")) {
        tokenValue = str.substr(0, regexMatch.str().size());
        str.erase(0, tokenValue.size());

        for (const auto& elem : ::xrn::language::detail::keywords) {
            if (tokenValue == elem) {
                tokenType = ::xrn::language::token::Type::KEYWORD;
                return true;
            }
        }
        tokenType = ::xrn::language::token::Type::IDENTIFIER;
        return true;
    }
    ::std::smatch regexMatch;
    return false;
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Lexer::matchNumbers(
    ::std::string& str,
    ::std::string& tokenValue,
    ::xrn::language::token::Type& tokenType
) -> bool
{
    ::std::smatch regexMatch;

    // float with litterals
    // if (Lexer::startsWith(str, regexMatch, "^[0-9'_]*[.][0-9'_]*[0-9][a-zA-Z][a-zA-Z0-9]*")) {
        // if (!(str.size() < regexMatch.str().size() && ::std::isdigit(str[regexMatch.str().size()]))) {
            // tokenValue = str.substr(0, regexMatch.str().size());
            // str.erase(0, tokenValue.size());
            // tokenType = ::xrn::language::token::Type::FLOAT_LITERAL;
            // return true;
        // }
    // }

    // float
    if (Lexer::startsWith(str, regexMatch, "^[0-9'_]*[.][0-9'_]*[0-9]")) {
        if (!(str.size() < regexMatch.str().size() && ::std::isdigit(str[regexMatch.str().size()]))) {
            tokenValue = str.substr(0, regexMatch.str().size());
            str.erase(0, tokenValue.size());
            tokenType = ::xrn::language::token::Type::F32;
            return true;
        }
    }

    // int with litterals
    // if (Lexer::startsWith(str, regexMatch, "^[0-9'_]*[0-9][a-zA-Z][a-zA-Z0-9]*")) {
        // if (!(str.size() < regexMatch.str().size() && ::std::isdigit(str[regexMatch.str().size()]))) {
            // tokenValue = str.substr(0, regexMatch.str().size());
            // str.erase(0, tokenValue.size());
            // tokenType = ::xrn::language::token::Type::INT_LITERAL;
            // return true;
        // }
    // }

    // int
    if (Lexer::startsWith(str, regexMatch, "^[0-9'_]*[0-9]")) {
        if (!(str.size() < regexMatch.str().size() && ::std::isdigit(str[regexMatch.str().size()]))) {
            tokenValue = str.substr(0, regexMatch.str().size());
            str.erase(0, tokenValue.size());
            tokenType = ::xrn::language::token::Type::I32;
            return true;
        }
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Lexer::matchWithList(
    ::std::string& str,
    ::std::string& tokenValue,
    ::xrn::language::token::Type& tokenType,
    const ::std::vector<::std::string>& vec,
    ::xrn::language::token::Type searchingTokenType
) -> bool
{
    ::std::smatch regexMatch;

    ::std::string regexStr{ "^(" };
    for (const auto& w : vec) {
        regexStr += '(';
        for (auto c : w) {
            regexStr += "["s + ::std::string{ c } + "]";
        }
        regexStr += ")|";
    }
    regexStr = regexStr.substr(0, regexStr.length() - 1) + ")";

    if (Lexer::startsWith(str, regexMatch, regexStr)) {
        tokenValue = str.substr(0, regexMatch.str().size());
        str.erase(0, tokenValue.size());
        tokenType = searchingTokenType;
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Lexer::matchWithList(
    ::std::string& str,
    ::std::string& tokenValue,
    ::xrn::language::token::Type& tokenType,
    const ::std::map<::std::string, ::std::uint8_t>& map,
    ::xrn::language::token::Type searchingTokenType
) -> bool
{
    ::std::smatch regexMatch;

    ::std::string regexStr{ "^(" };
    for (const auto& [ w, _ ] : map) {
        regexStr += '(';
        for (auto c : w) {
            regexStr += "["s + ::std::string{ c } + "]";
        }
        regexStr += ")|";
    }
    regexStr = regexStr.substr(0, regexStr.length() - 1) + ")";

    if (Lexer::startsWith(str, regexMatch, regexStr)) {
        tokenValue = str.substr(0, regexMatch.str().size());
        str.erase(0, tokenValue.size());
        tokenType = searchingTokenType;
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Lexer::lstrip(
    ::std::string& str
) -> ::std::size_t
{
    ::std::size_t strSize{ str.size() };
    const auto strBegin{ str.find_first_not_of(" \t") };
    if (strBegin == ::std::string::npos) {
        return strSize; // everything stripped
    }
    str.erase(0, strBegin);
    return strBegin;
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Lexer::startsWith(
    const ::std::string& str,
    ::std::smatch& regexMatch,
    const ::std::string& regexStr
) -> bool
{
    try {
        ::std::regex_search(str, regexMatch, ::std::regex{ regexStr });
        return regexMatch.position() == 0;
    } catch(...) {
        return false;
    }
}
