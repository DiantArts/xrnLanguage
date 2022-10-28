#pragma once

///////////////////////////////////////////////////////////////////////////
void ::xrn::language::TokenPool::add(
    auto&&... args
)
{
    m_expression.push_back(::std::make_shared<TokenPool::SubType>(
        ::std::forward<decltype(args)>(args)...
    ));
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::language::TokenPool::add(
    ::std::shared_ptr<T>&& arg
)
{
    m_expression.push_back(::std::move(arg));
}
