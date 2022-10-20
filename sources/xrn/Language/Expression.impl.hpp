#pragma once

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::Expression::add(
    auto&&... args
)
{
    m_expression.push_back(::std::make_unique<Expression::SubType>(
        ::std::forward<decltype(args)>(args)...
    ));
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::language::Expression::add(
    ::std::unique_ptr<T>&& arg
)
{
    m_expression.push_back(::std::move(arg));
}
