#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeId
> ::xrn::language::token::Number<T, typeId>::Number(
    Number::Type value,
    ::std::size_t lineNumber,
    ::std::size_t characterNumber
) noexcept
    : ::xrn::language::AToken{ typeId, lineNumber, characterNumber }
    , m_value{ value }
{}

///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeId
> ::xrn::language::token::Number<T, typeId>::Number(
    ::xrn::language::AToken&& token
) noexcept
    : ::xrn::language::AToken{ ::std::move(token) }
    , m_value{ static_cast<Number::Type>(
        ::std::strtol(token.getValueAsString().c_str(), nullptr, 10)
    )}
{
    m_type = typeId;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Virtual
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeId
> [[ nodiscard ]] auto ::xrn::language::token::Number<T, typeId>::getValueAsString() const
    -> ::std::string
{
    return ::std::string{ ::std::to_string(m_value) };
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeId
> auto ::xrn::language::token::Number<T, typeId>::getValue() const
    -> Number::Type
{
    return m_value;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeId
> void ::xrn::language::token::Number<T, typeId>::setValue(
    Number::Type value
)
{
    m_value = value;
}



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
    typename T,
    ::xrn::language::token::Type typeId
> template <
    typename RhsType,
    ::xrn::language::token::Type rhsTypeId
> auto ::xrn::language::token::Number<T, typeId>::operator*(
    ::xrn::language::token::Number<RhsType, rhsTypeId>& rhs
) -> ::std::shared_ptr<::xrn::language::AToken>
{
    if (typeId < rhsTypeId) {
        if constexpr (rhsTypeId <= ::xrn::language::token::Type::I64) {
            if constexpr (rhsTypeId == ::xrn::language::token::Type::I8) {
                return ::std::make_shared<::xrn::language::token::Int8>(
                    static_cast<::std::int8_t>(m_value) * rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I16) {
                return ::std::make_shared<::xrn::language::token::Int16>(
                    static_cast<::std::int16_t>(m_value) * rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I32) {
                return ::std::make_shared<::xrn::language::token::Int32>(
                    static_cast<::std::int32_t>(m_value) * rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I64) {
                return ::std::make_shared<::xrn::language::token::Int64>(
                    static_cast<::std::int64_t>(m_value) * rhs.getValue()
                );
            }
        } else {
            if constexpr (rhsTypeId == ::xrn::language::token::Type::F8) {
                return ::std::make_shared<::xrn::language::token::Float8>(
                    static_cast<float>(m_value) * rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F16) {
                return ::std::make_shared<::xrn::language::token::Float16>(
                    static_cast<float>(m_value) * rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F32) {
                return ::std::make_shared<::xrn::language::token::Float32>(
                    static_cast<float>(m_value) * rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F64) {
                return ::std::make_shared<::xrn::language::token::Float64>(
                    static_cast<double>(m_value) * rhs.getValue()
                );
            }
        }
    } else {
        if constexpr (typeId <= ::xrn::language::token::Type::I64) {
            if constexpr (typeId == ::xrn::language::token::Type::I8) {
                return ::std::make_shared<::xrn::language::token::Int8>(
                    m_value * static_cast<::std::int8_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I16) {
                return ::std::make_shared<::xrn::language::token::Int16>(
                    m_value * static_cast<::std::int16_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I32) {
                return ::std::make_shared<::xrn::language::token::Int32>(
                    m_value * static_cast<::std::int32_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I64) {
                return ::std::make_shared<::xrn::language::token::Int64>(
                    m_value * static_cast<::std::int64_t>(rhs.getValue())
                );
            }
        } else {
            if constexpr (typeId == ::xrn::language::token::Type::F8) {
                return ::std::make_shared<::xrn::language::token::Float8>(
                    m_value * static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F16) {
                return ::std::make_shared<::xrn::language::token::Float16>(
                    m_value * static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F32) {
                return ::std::make_shared<::xrn::language::token::Float32>(
                    m_value * static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F64) {
                return ::std::make_shared<::xrn::language::token::Float64>(
                    m_value * static_cast<double>(rhs.getValue())
                );
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
/// \brief compute and convert to correct type
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeId
> template <
    typename RhsType,
    ::xrn::language::token::Type rhsTypeId
> auto ::xrn::language::token::Number<T, typeId>::operator/(
    ::xrn::language::token::Number<RhsType, rhsTypeId>& rhs
) -> ::std::shared_ptr<::xrn::language::AToken>
{
    if (typeId < rhsTypeId) {
        if constexpr (rhsTypeId <= ::xrn::language::token::Type::I64) {
            if constexpr (rhsTypeId == ::xrn::language::token::Type::I8) {
                return ::std::make_shared<::xrn::language::token::Int8>(
                    static_cast<::std::int8_t>(m_value) / rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I16) {
                return ::std::make_shared<::xrn::language::token::Int16>(
                    static_cast<::std::int16_t>(m_value) / rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I32) {
                return ::std::make_shared<::xrn::language::token::Int32>(
                    static_cast<::std::int32_t>(m_value) / rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I64) {
                return ::std::make_shared<::xrn::language::token::Int64>(
                    static_cast<::std::int64_t>(m_value) / rhs.getValue()
                );
            }
        } else {
            if constexpr (rhsTypeId == ::xrn::language::token::Type::F8) {
                return ::std::make_shared<::xrn::language::token::Float8>(
                    static_cast<float>(m_value) / rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F16) {
                return ::std::make_shared<::xrn::language::token::Float16>(
                    static_cast<float>(m_value) / rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F32) {
                return ::std::make_shared<::xrn::language::token::Float32>(
                    static_cast<float>(m_value) / rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F64) {
                return ::std::make_shared<::xrn::language::token::Float64>(
                    static_cast<double>(m_value) / rhs.getValue()
                );
            }
        }
    } else {
        if constexpr (typeId <= ::xrn::language::token::Type::I64) {
            if constexpr (typeId == ::xrn::language::token::Type::I8) {
                return ::std::make_shared<::xrn::language::token::Int8>(
                    m_value / static_cast<::std::int8_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I16) {
                return ::std::make_shared<::xrn::language::token::Int16>(
                    m_value / static_cast<::std::int16_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I32) {
                return ::std::make_shared<::xrn::language::token::Int32>(
                    m_value / static_cast<::std::int32_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I64) {
                return ::std::make_shared<::xrn::language::token::Int64>(
                    m_value / static_cast<::std::int64_t>(rhs.getValue())
                );
            }
        } else {
            if constexpr (typeId == ::xrn::language::token::Type::F8) {
                return ::std::make_shared<::xrn::language::token::Float8>(
                    m_value / static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F16) {
                return ::std::make_shared<::xrn::language::token::Float16>(
                    m_value / static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F32) {
                return ::std::make_shared<::xrn::language::token::Float32>(
                    m_value / static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F64) {
                return ::std::make_shared<::xrn::language::token::Float64>(
                    m_value / static_cast<double>(rhs.getValue())
                );
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
/// \brief compute and convert to correct type
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeId
> template <
    typename RhsType,
    ::xrn::language::token::Type rhsTypeId
> auto ::xrn::language::token::Number<T, typeId>::operator+(
    ::xrn::language::token::Number<RhsType, rhsTypeId>& rhs
) -> ::std::shared_ptr<::xrn::language::AToken>
{
    if (typeId < rhsTypeId) {
        if constexpr (rhsTypeId <= ::xrn::language::token::Type::I64) {
            if constexpr (rhsTypeId == ::xrn::language::token::Type::I8) {
                return ::std::make_shared<::xrn::language::token::Int8>(
                    static_cast<::std::int8_t>(m_value) + rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I16) {
                return ::std::make_shared<::xrn::language::token::Int16>(
                    static_cast<::std::int16_t>(m_value) + rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I32) {
                return ::std::make_shared<::xrn::language::token::Int32>(
                    static_cast<::std::int32_t>(m_value) + rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I64) {
                return ::std::make_shared<::xrn::language::token::Int64>(
                    static_cast<::std::int64_t>(m_value) + rhs.getValue()
                );
            }
        } else {
            if constexpr (rhsTypeId == ::xrn::language::token::Type::F8) {
                return ::std::make_shared<::xrn::language::token::Float8>(
                    static_cast<float>(m_value) + rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F16) {
                return ::std::make_shared<::xrn::language::token::Float16>(
                    static_cast<float>(m_value) + rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F32) {
                return ::std::make_shared<::xrn::language::token::Float32>(
                    static_cast<float>(m_value) + rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F64) {
                return ::std::make_shared<::xrn::language::token::Float64>(
                    static_cast<double>(m_value) + rhs.getValue()
                );
            }
        }
    } else {
        if constexpr (typeId <= ::xrn::language::token::Type::I64) {
            if constexpr (typeId == ::xrn::language::token::Type::I8) {
                return ::std::make_shared<::xrn::language::token::Int8>(
                    m_value + static_cast<::std::int8_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I16) {
                return ::std::make_shared<::xrn::language::token::Int16>(
                    m_value + static_cast<::std::int16_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I32) {
                return ::std::make_shared<::xrn::language::token::Int32>(
                    m_value + static_cast<::std::int32_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I64) {
                return ::std::make_shared<::xrn::language::token::Int64>(
                    m_value + static_cast<::std::int64_t>(rhs.getValue())
                );
            }
        } else {
            if constexpr (typeId == ::xrn::language::token::Type::F8) {
                return ::std::make_shared<::xrn::language::token::Float8>(
                    m_value + static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F16) {
                return ::std::make_shared<::xrn::language::token::Float16>(
                    m_value + static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F32) {
                return ::std::make_shared<::xrn::language::token::Float32>(
                    m_value + static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F64) {
                return ::std::make_shared<::xrn::language::token::Float64>(
                    m_value + static_cast<double>(rhs.getValue())
                );
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
/// \brief compute and convert to correct type
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T,
    ::xrn::language::token::Type typeId
> template <
    typename RhsType,
    ::xrn::language::token::Type rhsTypeId
> auto ::xrn::language::token::Number<T, typeId>::operator-(
    ::xrn::language::token::Number<RhsType, rhsTypeId>& rhs
) -> ::std::shared_ptr<::xrn::language::AToken>
{
    if (typeId < rhsTypeId) {
        if constexpr (rhsTypeId <= ::xrn::language::token::Type::I64) {
            if constexpr (rhsTypeId == ::xrn::language::token::Type::I8) {
                return ::std::make_shared<::xrn::language::token::Int8>(
                    static_cast<::std::int8_t>(m_value) - rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I16) {
                return ::std::make_shared<::xrn::language::token::Int16>(
                    static_cast<::std::int16_t>(m_value) - rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I32) {
                return ::std::make_shared<::xrn::language::token::Int32>(
                    static_cast<::std::int32_t>(m_value) - rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::I64) {
                return ::std::make_shared<::xrn::language::token::Int64>(
                    static_cast<::std::int64_t>(m_value) - rhs.getValue()
                );
            }
        } else {
            if constexpr (rhsTypeId == ::xrn::language::token::Type::F8) {
                return ::std::make_shared<::xrn::language::token::Float8>(
                    static_cast<float>(m_value) - rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F16) {
                return ::std::make_shared<::xrn::language::token::Float16>(
                    static_cast<float>(m_value) - rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F32) {
                return ::std::make_shared<::xrn::language::token::Float32>(
                    static_cast<float>(m_value) - rhs.getValue()
                );
            } else if constexpr (rhsTypeId == ::xrn::language::token::Type::F64) {
                return ::std::make_shared<::xrn::language::token::Float64>(
                    static_cast<double>(m_value) - rhs.getValue()
                );
            }
        }
    } else {
        if constexpr (typeId <= ::xrn::language::token::Type::I64) {
            if constexpr (typeId == ::xrn::language::token::Type::I8) {
                return ::std::make_shared<::xrn::language::token::Int8>(
                    m_value - static_cast<::std::int8_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I16) {
                return ::std::make_shared<::xrn::language::token::Int16>(
                    m_value - static_cast<::std::int16_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I32) {
                return ::std::make_shared<::xrn::language::token::Int32>(
                    m_value - static_cast<::std::int32_t>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::I64) {
                return ::std::make_shared<::xrn::language::token::Int64>(
                    m_value - static_cast<::std::int64_t>(rhs.getValue())
                );
            }
        } else {
            if constexpr (typeId == ::xrn::language::token::Type::F8) {
                return ::std::make_shared<::xrn::language::token::Float8>(
                    m_value - static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F16) {
                return ::std::make_shared<::xrn::language::token::Float16>(
                    m_value - static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F32) {
                return ::std::make_shared<::xrn::language::token::Float32>(
                    m_value - static_cast<float>(rhs.getValue())
                );
            } else if constexpr (typeId == ::xrn::language::token::Type::F64) {
                return ::std::make_shared<::xrn::language::token::Float64>(
                    m_value - static_cast<double>(rhs.getValue())
                );
            }
        }
    }
}
