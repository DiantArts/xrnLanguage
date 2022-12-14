#pragma once

#include <xrn/Language/TokenPool.hpp>
#include <xrn/Language/Token/Number.hpp>

namespace xrn::language {

///////////////////////////////////////////////////////////////////////////
/// \brief Allows simple Math manipulations
/// \ingroup language
///
/// \include Math.hpp <xrn/Language/Math.hpp>
///
/// Compiles xrn code into an executable
///
/// Usage example:
/// \code
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
class Math {

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
    explicit Math() noexcept = delete;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Compute expression
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto shuntingYard(
        const ::xrn::language::TokenPool& tokens
    ) -> ::std::queue<::std::shared_ptr<::xrn::language::AToken>>;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto computeMathOperationImpl(
        auto lhs,
        const ::std::string& op,
        auto rhs
    ) -> ::std::shared_ptr<::xrn::language::AToken>;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto computeMathOperationRhs(
        auto lhs,
        const ::std::string& op,
        ::std::shared_ptr<::xrn::language::AToken> rhs
    ) -> ::std::shared_ptr<::xrn::language::AToken>;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto computeMathOperation(
        ::std::shared_ptr<::xrn::language::AToken> lhs,
        const ::std::string& op,
        ::std::shared_ptr<::xrn::language::AToken> rhs
    );

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto computeMathExpression(
        ::xrn::language::TokenPool& tokens
    ) -> ::std::shared_ptr<::xrn::language::AToken>;



private:

};

} // namespace xrn::language

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Header-implementation
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
#include <xrn/Language/Math.impl.hpp>
