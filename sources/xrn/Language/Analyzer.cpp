///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Language/Analyzer.hpp>
#include <xrn/Language/Token/Number.hpp>
#include <xrn/Language/Math.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Analyzer::run(
    ::xrn::language::Program& program
) -> bool
{
    Analyzer::processNumbers(program);
    Analyzer::processMathExpressions(program);
    return !program.hasError();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Syntactic analysis
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Analyzer::processNumbers(
    ::xrn::language::Program& program
) -> bool
{
    auto& tokenPool{ program.getTokens() };
    for (auto i{ 0uz }; i < tokenPool.size(); ++i) {
        auto& tokenPtr{ tokenPool[i] };
        program.addError(tokenPtr, "lol incorrect");
        switch (tokenPtr->getType()) {
        case ::xrn::language::token::Type::I8:
            tokenPtr = ::std::make_shared<::xrn::language::token::Int8>(::std::move(*tokenPtr));
            continue;
        case ::xrn::language::token::Type::I16:
            tokenPtr = ::std::make_shared<::xrn::language::token::Int16>(::std::move(*tokenPtr));
            continue;
        case ::xrn::language::token::Type::I32:
            tokenPtr = ::std::make_shared<::xrn::language::token::Int32>(::std::move(*tokenPtr));
            continue;
        case ::xrn::language::token::Type::I64:
            tokenPtr = ::std::make_shared<::xrn::language::token::Int64>(::std::move(*tokenPtr));
            continue;
        case ::xrn::language::token::Type::F8:
            tokenPtr = ::std::make_shared<::xrn::language::token::Float8>(::std::move(*tokenPtr));
            continue;
        case ::xrn::language::token::Type::F16:
            tokenPtr = ::std::make_shared<::xrn::language::token::Float16>(::std::move(*tokenPtr));
            continue;
        case ::xrn::language::token::Type::F32:
            tokenPtr = ::std::make_shared<::xrn::language::token::Float32>(::std::move(*tokenPtr));
            continue;
        case ::xrn::language::token::Type::F64:
            tokenPtr = ::std::make_shared<::xrn::language::token::Float64>(::std::move(*tokenPtr));
            continue;
        default: break;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::language::Analyzer::processMathExpressions(
    ::xrn::language::Program& program
) -> bool
{
    auto& tokenPool{ program.getTokens() };
    return true;
    ::fmt::print("{}\n", ::xrn::language::Math::computeMathExpression(tokenPool)->getAsString());
}
