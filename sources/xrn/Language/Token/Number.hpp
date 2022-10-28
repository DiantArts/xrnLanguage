#pragma once

#include <xrn/Language/Token/Literal.hpp>

namespace xrn::language::token {

///////////////////////////////////////////////////////////////////////////
/// \brief Allows simple Number manipulations
/// \ingroup language
///
/// \include Number.hpp <xrn/Language/Number.hpp>
///
/// Compiles xrn code into an executable
///
/// Usage example:
/// \code
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeIdTemplate
> class Number
    : public ::xrn::language::AToken
{

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // static elements
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Number internally contained by the class
    ///
    ///////////////////////////////////////////////////////////////////////////
    using Type = T;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the enum value for the type
    ///
    ///////////////////////////////////////////////////////////////////////////
    static inline constexpr ::xrn::language::token::Type typeId{ typeIdTemplate };


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
    explicit Number(
        Number::Type value,
        ::std::size_t lineNumber = 0,
        ::std::size_t characterNumber = 0
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Conversion constructor
    ///
    /// modifies the m_type value
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit Number(
        ::xrn::language::AToken&& token
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
    [[ nodiscard ]] auto getValue() const
        -> Number::Type;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void setValue(
        Number::Type value
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Operator
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief compute and convert to correct type
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename RhsType,
        ::xrn::language::token::Type rhsTypeId
    > [[ nodiscard ]] auto operator*(
        ::xrn::language::token::Number<RhsType, rhsTypeId>& rhs
    ) -> ::std::shared_ptr<::xrn::language::AToken>;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief compute and convert to correct type
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename RhsType,
        ::xrn::language::token::Type rhsTypeId
    > [[ nodiscard ]] auto operator/(
        ::xrn::language::token::Number<RhsType, rhsTypeId>& rhs
    ) -> ::std::shared_ptr<::xrn::language::AToken>;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief compute and convert to correct type
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename RhsType,
        ::xrn::language::token::Type rhsTypeId
    > [[ nodiscard ]] auto operator+(
        ::xrn::language::token::Number<RhsType, rhsTypeId>& rhs
    ) -> ::std::shared_ptr<::xrn::language::AToken>;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief compute and convert to correct type
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename RhsType,
        ::xrn::language::token::Type rhsTypeId
    > [[ nodiscard ]] auto operator-(
        ::xrn::language::token::Number<RhsType, rhsTypeId>& rhs
    ) -> ::std::shared_ptr<::xrn::language::AToken>;



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Convert the value of the string into the internal type
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto convertFromString(
        ::std::string value
    ) -> Number::Type;



private:

    Number::Type m_value;

};

} // namespace xrn::language::token

namespace xrn::language::token {
    using Int8 = ::xrn::language::token::Number<::std::int8_t, ::xrn::language::token::Type::I8>;
    using Int16 = ::xrn::language::token::Number<::std::int16_t, ::xrn::language::token::Type::I16>;
    using Int32 = ::xrn::language::token::Number<::std::int32_t, ::xrn::language::token::Type::I32>;
    using Int64 = ::xrn::language::token::Number<::std::int64_t, ::xrn::language::token::Type::I64>;
    using Float8 = ::xrn::language::token::Number<float, ::xrn::language::token::Type::F8>;
    using Float16 = ::xrn::language::token::Number<float, ::xrn::language::token::Type::F16>;
    using Float32 = ::xrn::language::token::Number<float, ::xrn::language::token::Type::F32>;
    using Float64 = ::xrn::language::token::Number<double, ::xrn::language::token::Type::F64>;
} // namespace xrn::language::token

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Header-implementation
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
#include <xrn/Language/Token/Number.impl.hpp>