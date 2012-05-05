#ifndef mpl_HPP__
#define mpl_HPP__

#include <type_traits>
#include <cstdlib>

namespace detail
{
  template 
  <
    template <typename> class Size,
    typename SoFar, 
    typename... Args
   >
  struct max_helper;

  template 
  <
    template <typename> class Size,
    typename SoFar
  >
  struct max_helper<Size, SoFar>
  {
    static constexpr decltype(Size<SoFar>::value) value = 
      Size<SoFar>::value;
    typedef SoFar type;
  };

  template 
  <
    template <typename> class Size,
    typename SoFar, 
    typename Next, 
    typename... Args
  >
  struct max_helper<Size, SoFar, Next, Args...>
  {
    private:
    typedef typename std::conditional
    <
      (Size<Next>::value > Size<SoFar>::value),
      max_helper<Size, Next, Args...>,
      max_helper<Size, SoFar, Args...>
    >::type m_next;

    public:
    static constexpr decltype(Size<SoFar>::value) value = 
      m_next::value;

    typedef typename m_next::type type;
  };
}

template <template <typename> class Size, typename... Args>
struct max;

template 
<
  template <typename> class Size, 
  typename First, 
  typename... Args
>
struct max<Size, First, Args...>
{
  private:
  typedef decltype(Size<First>::value) m_size_type;
  typedef detail::max_helper
  <
    Size, 
    First, 
    Args...
  > m_helper;

  public:
  static constexpr m_size_type value = m_helper::value;
  typedef typename m_helper::type type;
};

#endif // mpl_HPP__
