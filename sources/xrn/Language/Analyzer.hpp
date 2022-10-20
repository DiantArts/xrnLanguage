#pragma once

#include <xrn/Language/Program.hpp>

namespace xrn::language {

///////////////////////////////////////////////////////////////////////////
/// \brief Allows simple syntactical Analysis
/// \ingroup language
///
/// \include Analyzer.hpp <xrn/Language/Analyzer.hpp>
///
/// Compiles xrn code into an executable
///
/// Usage example:
/// \code
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
class Analyzer {

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
    Analyzer() = delete;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Run
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Run static analysis
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto run(
        ::xrn::language::Program& program
    ) -> bool;



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Syntactic analysis
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Process the literrals
    ///
    /// E.G.: 1f is processed to 1.0 float
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto processLiterals(
        ::xrn::language::Expression& expression
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Process the math expressions
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto processMathExpressions(
        ::xrn::language::Expression& expression
    ) -> bool;



};

} // namespace xrn::language