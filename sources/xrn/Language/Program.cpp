///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Language/Program.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::xrn::language::Program::Program(
    const ::std::string& filepath
) noexcept
    : m_filepath{ filepath }
    , m_lines{ ::xrn::File::getContentAsVector(m_filepath) }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters/Setters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Program::addError(
    ::std::shared_ptr<::xrn::language::AToken> token,
    const ::std::string& message,
    const ::std::string& compilerHelp
)
{
    m_error.push_back(::std::tuple<
        ::std::shared_ptr<::xrn::language::AToken>, ::std::string, Program::ErrorLevel, ::std::string
    >(token, message, Program::ErrorLevel::ERROR, compilerHelp));
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Program::addWarning(
    ::std::shared_ptr<::xrn::language::AToken> token,
    const ::std::string& message,
    const ::std::string& compilerHelp
)
{
    m_error.push_back(::std::tuple<
        ::std::shared_ptr<::xrn::language::AToken>, ::std::string, Program::ErrorLevel, ::std::string
    >(token, message, Program::ErrorLevel::WARNING, compilerHelp));
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Program::addNote(
    ::std::shared_ptr<::xrn::language::AToken> token,
    const ::std::string& message,
    const ::std::string& compilerHelp
)
{
    m_error.push_back(::std::tuple<
        ::std::shared_ptr<::xrn::language::AToken>, ::std::string, Program::ErrorLevel, ::std::string
    >(token, message, Program::ErrorLevel::NOTE, compilerHelp));
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Program::hasError() const
    -> bool
{
    for (const auto& [ tokenPtr, message, errorLevel, compilerHelp ] : m_error) {
        if (errorLevel == Program::ErrorLevel::ERROR) {
            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Program::printError() const
{
    for (const auto& [ tokenPtr, message, errorLevel, compilerHelp ] : m_error) {
        // position
        ::fmt::print(
            ::fmt::emphasis::bold | ::fmt::fg(::fmt::terminal_color::white), "{}:{}:{} ",
            m_filepath, tokenPtr->getLineNumber() + 1, tokenPtr->getCharacterNumber() + 1
        );

        // error level
        ::fmt::text_style color;
        switch (errorLevel) {
        case Program::ErrorLevel::NOTE:
            color = ::fmt::emphasis::bold | ::fmt::fg(::fmt::terminal_color::bright_cyan);
            ::fmt::print(color, "note:");
            break;
        case Program::ErrorLevel::WARNING:
            color = ::fmt::emphasis::bold | ::fmt::fg(::fmt::terminal_color::bright_magenta);
            ::fmt::print(color, "warning:");
            break;
        case Program::ErrorLevel::ERROR:
            color = ::fmt::emphasis::bold | ::fmt::fg(::fmt::terminal_color::bright_red);
            ::fmt::print(color, "error:");
            break;
        };
        ::fmt::print(::fmt::emphasis::bold, " {}\n", message);

        // error line number and print
        ::std::size_t allignmentSize{ ::std::to_string(m_maxCharacterNumber).size() + 3 };
        ::fmt::print("{:>{}} |   {}",
            tokenPtr->getLineNumber() + 1, allignmentSize,
            m_lines[tokenPtr->getLineNumber()].substr(0, tokenPtr->getCharacterNumber())
        );
        ::fmt::print(color, "{}", tokenPtr->getValueAsString());
        ::fmt::print("{}\n",
            m_lines[tokenPtr->getLineNumber()].substr(
                tokenPtr->getCharacterNumber() + tokenPtr->getValueAsString().size()
            )
        );

        ::std::string str;

        // line allignement
        str.insert(0, allignmentSize, ' ');
        ::fmt::print("{} |   ", str);

        // arrow
        str.clear();
        str.insert(0, tokenPtr->getCharacterNumber(), ' ');
        str.insert(tokenPtr->getCharacterNumber(), 1, '^');
        str.insert(tokenPtr->getCharacterNumber() + 1, tokenPtr->getValueAsString().size() - 1, '~');
        ::fmt::print(color, "{}\n", str);

        if (!compilerHelp.empty()) {
            // line allignement
            str.clear();
            str.insert(0, allignmentSize, ' ');
            ::fmt::print("{} |   ", str);

            // compilerHelp
            str.clear();
            str.insert(0, tokenPtr->getCharacterNumber(), ' ');
            ::fmt::print(
                ::fmt::emphasis::bold | ::fmt::fg(fmt::terminal_color::bright_green),
                "{}{}\n",
                str,
                compilerHelp
            );
        }
        ::fmt::print("\n");
    }
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Program::proposeMaxCharacterNumber(
    ::std::size_t i
)
{
    if (i > m_maxCharacterNumber) {
        m_maxCharacterNumber = i;
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters/Setters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Program::getLines() const
    -> const ::std::vector<::std::string>&
{
    return m_lines;
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Program::getTokens() const
    -> const ::xrn::language::TokenPool&
{
    return m_tokens;
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Program::getTokens()
    -> ::xrn::language::TokenPool&
{
    return m_tokens;
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Program::setTokens(
    ::xrn::language::TokenPool&& expressions
)
{
    m_tokens = ::std::move(expressions);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Print
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Program::printTokens() const
{
    for (const auto& tokenPtr : m_tokens) {
        if (tokenPtr) {
            ::fmt::print("{} ", tokenPtr->getAsString());
        } else {
            ::fmt::print("<INVALID> ");
        }
    }
    ::fmt::print("\n");
}
