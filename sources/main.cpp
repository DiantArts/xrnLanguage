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
    auto file{ ::xrn::File::getContentAsVector("tests/example.xrn") };
    ::xrn::language::Program program{ file };

    ::xrn::language::Lexer::run(program);
    program.printTokens();

    if (!::xrn::language::Analyzer::run(program)) {
        program.printError();
        return EXIT_FAILURE;
    }

    if (!::xrn::language::Compiler::run(program)) {
        program.printError();
        ::fmt::print("Compilation error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
