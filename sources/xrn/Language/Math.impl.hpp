#pragma once

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Math::computeMathOperationImpl(
    auto lhs,
    const ::std::string& op,
    auto rhs
) -> ::std::shared_ptr<::xrn::language::AToken>
{
    if (op == "*") {
        return *lhs * *rhs;
    } else if (op == "/") {
        return *lhs / *rhs;
    } else if (op == "+") {
        return *lhs + *rhs;
    } else if (op == "-") {
        return *lhs - *rhs;
    } else if (op == "**") {
        throw ::std::runtime_error{ "Operator power is not supported" };
    } else {
        throw ::std::runtime_error{ "invalid operator: '"s + op + "'" };
    }
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Math::computeMathOperationRhs(
    auto lhs,
    const ::std::string& op,
    ::std::shared_ptr<::xrn::language::AToken> rhs
) -> ::std::shared_ptr<::xrn::language::AToken>
{
    switch (rhs->getType()) {
    case ::xrn::language::token::Type::I8: {
        auto rhsPtr{ static_pointer_cast<::xrn::language::token::Int8>(rhs) };
        return ::xrn::language::Math::computeMathOperationImpl(lhs, op, rhsPtr);
    } case ::xrn::language::token::Type::I16: {
        auto rhsPtr{ static_pointer_cast<::xrn::language::token::Int16>(rhs) };
        return ::xrn::language::Math::computeMathOperationImpl(lhs, op, rhsPtr);
    } case ::xrn::language::token::Type::I32: {
        auto rhsPtr{ static_pointer_cast<::xrn::language::token::Int32>(rhs) };
        return ::xrn::language::Math::computeMathOperationImpl(lhs, op, rhsPtr);
    } case ::xrn::language::token::Type::SIZE: {
    } case ::xrn::language::token::Type::I64: {
        auto rhsPtr{ static_pointer_cast<::xrn::language::token::Int32>(rhs) };
        return ::xrn::language::Math::computeMathOperationImpl(lhs, op, rhsPtr);
    } case ::xrn::language::token::Type::F8: {
        auto rhsPtr{ static_pointer_cast<::xrn::language::token::Float8>(rhs) };
        return ::xrn::language::Math::computeMathOperationImpl(lhs, op, rhsPtr);
    } case ::xrn::language::token::Type::F16: {
        auto rhsPtr{ static_pointer_cast<::xrn::language::token::Float8>(rhs) };
        return ::xrn::language::Math::computeMathOperationImpl(lhs, op, rhsPtr);
    } case ::xrn::language::token::Type::F32: {
        auto rhsPtr{ static_pointer_cast<::xrn::language::token::Float32>(rhs) };
        return ::xrn::language::Math::computeMathOperationImpl(lhs, op, rhsPtr);
    } case ::xrn::language::token::Type::F64: {
        auto rhsPtr{ static_pointer_cast<::xrn::language::token::Float64>(rhs) };
        return ::xrn::language::Math::computeMathOperationImpl(lhs, op, rhsPtr);
    } default:
        throw ::std::runtime_error{ "invalid type of operand: '"s + rhs->getAsString() + "'" };
    };
}
