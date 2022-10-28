///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Language/Math.hpp>
#include <xrn/Language/Detail/Syntax.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Compute expression
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Math::shuntingYard(
    const ::xrn::language::TokenPool& tokens
) -> ::std::queue<::std::shared_ptr<::xrn::language::AToken>>
{
    ::std::queue<::std::shared_ptr<::xrn::language::AToken>> outputs;
    ::std::stack<::std::shared_ptr<::xrn::language::AToken>> operators;

    // While there are tokens to be read:
    for (auto& tokenPtr : tokens) {
        // Read a token
        if (tokenPtr->isNumber()) {
            // If the token is a number, then add it to the output queue
            outputs.push(tokenPtr);
        } else if (tokenPtr->getType() == ::xrn::language::token::Type::OPERATOR) {
            // If the token is operator, o1, then:
            auto& o1{ tokenPtr };

            // while there is an operator token,
            while (!operators.empty()) {
                // o2, at the top of stack, and
                auto& o2{ operators.top() };

                // o1 is left-associative and its precedence is
                // *less than or equal* to that of o2,
                if (
                    (
                        ::xrn::language::token::Type::OPERATOR == o2->getType() &&
                        ::xrn::language::detail::operators.at(o1->getValueAsString()) >=
                        ::xrn::language::detail::operators.at(o2->getValueAsString())
                    // ) || (
                        // !::xrn::language::token::Type::SEPARATOR == o2->getType()
                    )
                    // TODO: is right-associative (o1->rightAssociative && o1->precedence < o2->precedence)
                ) {
                    // then pop o2 off the stack,
                    operators.pop();
                    // onto the output queue;
                    outputs.push(o2);
                } else {
                    break;
                }
            }

            // push o1 onto the stack.
            operators.push(o1);
        } else if (
            tokenPtr->isType(::xrn::language::token::Type::SEPARATOR) && tokenPtr->getValueAsString() == "("
        ) {
            operators.push(tokenPtr);
        } else if (
            tokenPtr->isType(::xrn::language::token::Type::SEPARATOR) && tokenPtr->getValueAsString() == ")"
        ) {

            // If token is right parenthesis:
            auto match{ false };

            // Until the token at the top of the stack
            // is a left parenthesis,
            while (
                !operators.empty() &&
                !(
                    operators.top()->isType(::xrn::language::token::Type::SEPARATOR) &&
                    operators.top()->getValueAsString() == "("
                )
            ) {
                // pop operators off the stack
                // onto the output queue.
                outputs.push(operators.top());
                operators.pop();
                match = true;
            }

            // Pop the left parenthesis from the stack,
            // but not onto the output queue.
            operators.pop();

            if (!match && operators.empty()) {
                // If the stack runs out without finding a left parenthesis,
                // then there are mismatched parentheses.
                throw ::std::runtime_error{ "missmatched parenthesis 1" };
            }
        } else {
            throw ::std::runtime_error{ "invalid token type: '"s + tokenPtr->getValueAsString() + "'" };
        }
    }

    // When there are no more tokens to read:
    //   While there are still operator tokens in the stack:
    while (!operators.empty()) {
        // If the operator token on the top of the stack is a parenthesis,
        // then there are mismatched parentheses.
        if (
            operators.top()->isType(::xrn::language::token::Type::SEPARATOR) &&
            operators.top()->getValueAsString() == "("
        ) {
            throw ::std::runtime_error{ "missmatched parenthesis 2" };
        }

        // Pop the operator onto the output queue.
        outputs.push(::std::move(operators.top()));
        operators.pop();
    }

    return outputs;
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Math::computeMathOperation(
    ::std::shared_ptr<::xrn::language::AToken> lhs,
    const ::std::string& op,
    ::std::shared_ptr<::xrn::language::AToken> rhs
)
{
    switch (lhs->getType()) {
    case ::xrn::language::token::Type::I8: {
        auto lhsPtr{ static_pointer_cast<::xrn::language::token::Int8>(lhs) };
        return ::xrn::language::Math::computeMathOperationRhs(lhsPtr, op, rhs);
    } case ::xrn::language::token::Type::I16: {
        auto lhsPtr{ static_pointer_cast<::xrn::language::token::Int16>(lhs) };
        return ::xrn::language::Math::computeMathOperationRhs(lhsPtr, op, rhs);
    } case ::xrn::language::token::Type::I32: {
        auto lhsPtr{ static_pointer_cast<::xrn::language::token::Int32>(lhs) };
        return ::xrn::language::Math::computeMathOperationRhs(lhsPtr, op, rhs);
    } case ::xrn::language::token::Type::SIZE: {
    } case ::xrn::language::token::Type::I64: {
        auto lhsPtr{ static_pointer_cast<::xrn::language::token::Int32>(lhs) };
        return ::xrn::language::Math::computeMathOperationRhs(lhsPtr, op, rhs);
    } case ::xrn::language::token::Type::F8: {
        auto lhsPtr{ static_pointer_cast<::xrn::language::token::Float8>(lhs) };
        return ::xrn::language::Math::computeMathOperationRhs(lhsPtr, op, rhs);
    } case ::xrn::language::token::Type::F16: {
        auto lhsPtr{ static_pointer_cast<::xrn::language::token::Float8>(lhs) };
        return ::xrn::language::Math::computeMathOperationRhs(lhsPtr, op, rhs);
    } case ::xrn::language::token::Type::F32: {
        auto lhsPtr{ static_pointer_cast<::xrn::language::token::Float32>(lhs) };
        return ::xrn::language::Math::computeMathOperationRhs(lhsPtr, op, rhs);
    } case ::xrn::language::token::Type::F64: {
        auto lhsPtr{ static_pointer_cast<::xrn::language::token::Float64>(lhs) };
        return ::xrn::language::Math::computeMathOperationRhs(lhsPtr, op, rhs);
    } default:
        throw ::std::runtime_error{ "invalid type of operand: '"s + lhs->getAsString() + "'" };
    };
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::xrn::language::Math::computeMathExpression(
    ::xrn::language::TokenPool& tokens
) -> ::std::shared_ptr<::xrn::language::AToken>
{
    auto queue{ ::xrn::language::Math::shuntingYard(tokens) };
    ::std::stack<::std::shared_ptr<::xrn::language::AToken>> operands;

    while (!queue.empty()) {
        ::std::string op;
        auto tokenPtr{ queue.front() };
        queue.pop();
        if (tokenPtr->isNumber()) {
            operands.push(tokenPtr);
            op = "Push " + tokenPtr->getValueAsString();
        } else if (tokenPtr->isType(::xrn::language::token::Type::OPERATOR)) {
            const auto rhs{ operands.top() };
            operands.pop();
            const auto lhs{ operands.top() };
            operands.pop();
            operands.push(::xrn::language::Math::computeMathOperation(lhs, tokenPtr->getValueAsString(), rhs));
            op = "Push " + lhs->getValueAsString() + " " + tokenPtr->getValueAsString() + " " + rhs->getValueAsString();
        } else {
            throw ::std::runtime_error{ "invalid type of token to compute" };
        }
    }
    return operands.top();
}
