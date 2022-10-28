#pragma once

#include <xrn/Language/Token/AToken.hpp>

namespace xrn::language::token {

///////////////////////////////////////////////////////////////////////////
/// \brief Allows simple Literal manipulations
/// \ingroup language
///
/// \include Literal.hpp <xrn/Language/Literal.hpp>
///
/// Compiles xrn code into an executable
///
/// Usage example:
/// \code
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
class Literal
    : public ::xrn::language::AToken
{

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Literal(
        ::xrn::language::token::Type type,
        ::std::string value,
        ::std::size_t lineNumber,
        ::std::size_t characterNumber
    ) noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Virtual
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the token as string
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getValueAsString() const
        -> ::std::string override;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void setValue(
        ::std::string value
    );



protected:

    ::std::string m_value;

};

} // namespace xrn::language::token
