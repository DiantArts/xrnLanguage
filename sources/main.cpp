///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>
#include <xrn/Language/Lexer.hpp>
#include <xrn/Language/Analyzer.hpp>
#include <xrn/Language/Compiler.hpp>

///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
{
    // auto file{ ::xrn::File::getContentAsVector("tests/example.xrn") };
    ::std::vector<::std::string> file{ "3 * 1 + 5" };
    ::xrn::language::Program program{ file };

    ::xrn::language::Lexer::run(program);
    program.printTokens();
    ::xrn::language::Analyzer::run(program);
    ::xrn::language::Compiler::run(program);

    return EXIT_SUCCESS;
}
