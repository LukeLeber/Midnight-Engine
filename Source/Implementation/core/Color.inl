namespace midnight
{

template<typename T, std::size_t N>
inline constexpr Color<T, N>::Color() noexcept : 
    Tuple<T, N>()
{

}

template<typename T, std::size_t N>
template<typename ...E>
inline constexpr Color<T, N>::Color(T element, E&&... elements) noexcept : 
    Tuple<T, N>(element, static_cast<T>(std::forward<E>(elements))...)
{

}

template<typename T, std::size_t N>
inline constexpr Color<T, N>::Color(const Tuple<T, N>& tuple) noexcept : 
    Tuple<T, N>(tuple)
{
    
}

template<typename T, std::size_t N>
inline constexpr Color<T, N>::Color(Tuple<T, N>&& tuple) noexcept : 
    Tuple<T, N>(std::move(tuple))
{
    
}

template<typename T, std::size_t N>
inline Color<T, N>& Color<T, N>::operator=(const Tuple<T, N>& tuple) noexcept
{
    return this->Tuple<T, N>::operator=(tuple);
}

template<typename T, std::size_t N>
inline Color<T, N>& Color<T, N>::operator=(Tuple<T, N>&& tuple) noexcept
{
    return dynamic_cast<Color<T, N>&>(this->Tuple<T, N>::operator=(std::move(tuple)));
}

}
