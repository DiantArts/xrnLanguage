#pragma once

#include <xrn/Language/Detail/Syntax.hpp>
#include <xrn/Language/Program.hpp>

namespace xrn::language {

///////////////////////////////////////////////////////////////////////////
/// \brief Allows simple Lexer manipulations
/// \ingroup language
///
/// \include Lexer.hpp <xrn/Language/Lexer.hpp>
///
/// Compiles xrn code into an executable
///
/// Usage example:
/// \code
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
class Lexer {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    Lexer() = delete;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Run
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs the lexer
    ///
    /// Parses the program's strings and set the tokens
    ///
    ///////////////////////////////////////////////////////////////////////////
    static void run(
        ::xrn::language::Program& program
    ) noexcept;



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Parsing
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Extract tokens vector from a string
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto extractExpression(
        ::std::vector<::std::string>& str,
        ::std::size_t& lineNumber
    ) -> ::xrn::language::Expression;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Extract single token from a string
    ///
    ///////////////////////////////////////////////////////////////////////////
    static void extractToken(
        ::std::string& str,
        ::std::string& tokenValue,
        ::xrn::language::token::Type& tokenType,
        ::std::size_t lineNumber,
        ::std::size_t characterNumber
    );

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto skipTillNextChar(
        ::std::vector<::std::string>& lines,
        ::std::size_t& i,
        ::std::size_t& j,
        ::std::vector<::std::string_view> vec
    ) -> ::std::string;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto matchIdentifiersAndKeywords(
        ::std::string& str,
        ::std::string& tokenValue,
        ::xrn::language::token::Type& tokenType
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto matchNumbers(
        ::std::string& str,
        ::std::string& tokenValue,
        ::xrn::language::token::Type& tokenType
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto matchWithList(
        ::std::string& str,
        ::std::string& tokenValue,
        ::xrn::language::token::Type& tokenType,
        const ::std::vector<::std::string_view>& vec,
        ::xrn::language::token::Type searchingTokenType
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto matchWithList(
        ::std::string& str,
        ::std::string& tokenValue,
        ::xrn::language::token::Type& tokenType,
        const ::std::map<::std::string_view, ::std::uint8_t>& map,
        ::xrn::language::token::Type searchingTokenType
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Lstrip every whitechars and return the number of char stripped
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto lstrip(
        ::std::string& str
    ) -> ::std::size_t;


    ///////////////////////////////////////////////////////////////////////////
    /// \brief Check whether a regex is at the begining of the string
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto startsWith(
        const ::std::string& str,
        ::std::smatch& regexMatch,
        const ::std::string& regexStr
    ) -> bool;

};

} // namespace xrn::language