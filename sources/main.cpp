///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>
#include <xrn/Language/Lexer.hpp>
#include <xrn/Language/Analyzer.hpp>
#include <xrn/Language/Compiler.hpp>
#include <xrn/Language/Token/Number.hpp>

///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
{
    // ::std::vector<::std::string> file{ "1 + 2 * 3 + 4 + 5" };
    ::xrn::language::Program program{ "tests/example.xrn" };

    ::xrn::language::Lexer::run(program);
    program.printTokens();

    if (
        !::xrn::language::Analyzer::run(program) ||
        !::xrn::language::Compiler::run(program)
    ) {
        program.printError();
        return EXIT_FAILURE;
    } else {
        program.printError();
        return EXIT_SUCCESS;
    }
}
