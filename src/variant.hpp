#ifndef variant_HPP__
#define variant_HPP__


#include <cassert>
#include <functional>
#include <new>
#include <type_traits>
#include <utility>

#include "mpl.hpp"

template <typename T>
class recursive_wrapper
{
public:
	~recursive_wrapper()
	{
		delete t_;
	}

	template <	typename U,
				typename Dummy = typename std::enable_if<std::is_convertible<U, T>::value, U>::type >
	recursive_wrapper( U const& u)
		: t_(new T(u))
	{}

	template < typename U,
				typename Dummy = typename std::enable_if<std::is_convertible<U, T>::value, U>::type 	>
	recursive_wrapper( U&& u )
		: t_( new T(std::forward<U>(u)) )
	{}

	recursive_wrapper(const recursive_wrapper& rhs)
		: t_( new T(rhs.get()) )
	{}

	recursive_wrapper(recursive_wrapper&& rhs)
		: t_(rhs.t_)
	{
		rhs.t_ = nullptr;
	}

	recursive_wrapper& operator=(const recursive_wrapper& rhs)
	{
		assign(rhs.get());
		return *this;
	}

	recursive_wrapper& operator=(recursive_wrapper&& rhs)
	{
		delete t_;
		t_ = rhs.t_;
		rhs.t_ = nullptr;
		return *this;
	}

	recursive_wrapper& operator=(const T& t)
	{
		assign(t);
		return *this;
	}

	recursive_wrapper& operator=(T&& t)
	{
		assign(std::move(t));
		return *this;
	}

	T& get()
	{
		return *t_;
	}

	const T& get() const
	{
		return *t_;
	}


private:

	T* t_;

	template <typename U>
	void assign(U&& u)
	{
		*t_ = std::forward<U>(u);
	}
};

struct true_ {};
struct false_ {};

namespace detail
{

template <typename T, typename Internal>
T& get_value(T& t, const Internal&)
{
	return t;
}

template <typename T>
T& get_value(recursive_wrapper<T>& t, const false_&)
{
	return t.get();
}

template <typename T>
const T& get_value(const recursive_wrapper<T>& t, const false_&)
{
	return t.get();
}

} //namespace detail

template < typename Internal, typename T, typename Storage, typename Visitor, typename... Args >
typename Visitor::result_type visitor_caller(Internal&& internal, Storage&& storage, Visitor&& visitor, Args&&... args)
{
	typedef typename std::conditional <
		std::is_const<
			typename std::remove_extent<
				typename std::remove_reference<Storage>::type>::type
			>::value,
		const T,
		T
	>::type ConstType;

  return visitor( detail::get_value(*reinterpret_cast<ConstType*>(storage), internal), std::forward<Args>(args)...);
}


template <typename First, typename... Types>
class variant_base
{
public:	//protected:		//private:

	template <typename... AllTypes>
	struct do_visit
	{
	template 
	<
		typename Internal, 
		typename VoidPtrCV, 
		typename Visitor, 
		typename... Args
	>
	typename Visitor::result_type
	operator()
	(
		Internal&& internal,
		size_t which, 
		VoidPtrCV&& storage, 
		Visitor& visitor, 
		Args&&... args
	)
	{
		typedef typename Visitor::result_type (*whichCaller)
		(Internal&&, VoidPtrCV&&, Visitor&&, Args&&...);

		static whichCaller callers[sizeof...(AllTypes)] =
		{
			&visitor_caller<Internal&&, AllTypes,
			VoidPtrCV&&, Visitor, Args&&...>...
		}
		;

		assert(which >= 0 && which < sizeof...(AllTypes));

		return (*callers[which])
		(
			std::forward<Internal>(internal),
			std::forward<VoidPtrCV>(storage), 
			std::forward<Visitor>(visitor), 
			std::forward<Args>(args)...
		);
	}
	};

	template <typename T>
	struct Sizeof
	{
	static constexpr size_t value = sizeof(T);
	};

	template <typename T>
	struct Alignof
	{
	static constexpr size_t value = alignof(T);
	};

	//size = max of size of each thing
	static constexpr size_t size_ = max<Sizeof, First, Types...>::value;

	struct constructor
	{
		typedef void result_type;

		constructor(variant_base& self)
			: self_(self)
		{
		}

		template <typename T>
		void operator()(const T& rhs) const
		{
			self_.construct(rhs);
		}

	private:
		variant_base& self_;
	};

	struct move_constructor
	{
		typedef void result_type;

		move_constructor(variant_base& self)
			: self_(self)
		{
		}

		template <typename T>
		void operator()(T& rhs) const
		{
			self_.construct(std::move(rhs));
		}

	private:
		variant_base& self_;
	};

	struct assigner
	{
		typedef void result_type;

		assigner(variant_base& self, int rhs_which)
			: self_(self), rhs_which_(rhs_which)
		{
		}

		template <typename Rhs>
		void operator()(const Rhs& rhs) const
		{
			if (self_.which() == rhs_which_)
			{
				//the types are the same, so just assign into the lhs
				*reinterpret_cast<Rhs*>(self_.address()) = rhs;
			}
			else
			{
				Rhs tmp(rhs);
				self_.destroy(); //nothrow
				self_.construct(std::move(tmp)); //nothrow (please)
			}
		}

	private:
		variant_base& self_;
		int rhs_which_;
	};
  
	struct move_assigner
	{
		typedef void result_type;

		move_assigner(variant_base& self, int rhs_which)
			: self_(self), rhs_which_(rhs_which)
		{
		}

		template <typename Rhs>
		void operator()(Rhs& rhs) const
		{
			typedef typename std::remove_const<Rhs>::type RhsNoConst;
			if (self_.which() == rhs_which_)
			{
				//the types are the same, so just assign into the lhs
				*reinterpret_cast<RhsNoConst*>(self_.address()) = std::move(rhs);
			}
			else
			{
				self_.destroy(); //nothrow
				self_.construct(std::move(rhs)); //nothrow (please)
			}
		}

	private:
		variant_base& self_;
		int rhs_which_;
	};

	struct destroyer
	{
		typedef void result_type;

		template <typename T>
		void operator()(T& t) const
		{
			t.~T();
		}
	};

	template <size_t Which, typename... MyTypes>
	struct initialiser;

	template <size_t Which, typename Current, typename... MyTypes>
	struct initialiser<Which, Current, MyTypes...> 
		: public initialiser<Which+1, MyTypes...>
	{
		typedef initialiser<Which+1, MyTypes...> base;
		using base::initialise;

		static void initialise(variant_base& v, Current&& current)
		{
			v.construct(std::forward<Current>(current));
			v.indicate_which(Which);
		}

		static void initialise(variant_base& v, const Current& current)
		{
			v.construct(current);
			v.indicate_which(Which);
		}
	};

	template <size_t Which>
	struct initialiser<Which>
	{
		//this should never match
		void initialise();
	};

public:

	variant_base()
	{
		//try to construct First
		//if this fails then First is not default constructible
		construct(First());
		indicate_which(0);
	}

	~variant_base()
	{
		destroy();
	}

	//enable_if disables this function if we are constructing with a Variant.
	//Unfortunately, this becomes variant_base(variant_base&) which is a better match
	//than variant_base(const variant_base& rhs), so it is chosen. Therefore, we disable
	//it.
	template 
	<
	typename T
	, typename Dummy =
		typename std::enable_if
		<
		!std::is_same
		<
			typename std::remove_reference<variant_base<First, Types...>>::type,
			typename std::remove_reference<T>::type
		>::value,
		T
		>::type
	>
	variant_base( T&& t )
	{
		static_assert( ! std::is_same<variant_base<First, Types...>&, T>::value, "why is variant_base(T&&) instantiated with a variant_base?");

		std::cout << "variant_base( T&& t )" << std::endl;

		//compile error here means that T is not unambiguously convertible to any of the types in (First, Types...)
		initialiser<0, First, Types...>::template initialise(*this, std::forward<T>(t));
	}

	//template < typename T >
	//variant( std::initializer_list<T> && t )
	//{
	//	//	  std::cout << "xxx: " << typeid(t).name() << std::endl;
	//	//	  std::forward<std::initializer_list<T>>(t);

	//	//compile error here means that T is not unambiguously convertible to any of the types in (First, Types...)
	//	initialiser<0, First, Types...>::initialise(*this, std::forward<std::initializer_list<T>>(t));
	//}


	variant_base( variant_base const& rhs )
	{
		constructor c(*this);
		rhs.apply_visitor_internal(c);
		indicate_which(rhs.which());
	}

	variant_base( variant_base&& rhs )
	{
		move_constructor mc(*this);
		rhs.apply_visitor_internal(mc);
		indicate_which(rhs.which());
	}

	variant_base& operator=(const variant_base& rhs)
	{
		if (this != &rhs)
		{
			assigner a(*this, rhs.which());
			rhs.apply_visitor_internal(a);
			indicate_which(rhs.which());
		}
		return *this;
	}

	variant_base& operator=(variant_base&& rhs)
	{
		if (this != &rhs)
		{
			move_assigner ma(*this, rhs.which());
			rhs.apply_visitor_internal(ma);
			indicate_which(rhs.which());
		}
		return *this;
	}

	int which() const 
	{
		return which_;
	}

	template <typename Internal, typename Visitor, typename... Args>
	typename Visitor::result_type
		apply_visitor(Visitor& visitor, Args&&... args)
	{
		return do_visit<First, Types...>()(Internal(), which_, storage_,
			visitor, std::forward<Args>(args)...);
	}

	template <typename Internal, typename Visitor, typename... Args>
	typename Visitor::result_type
		apply_visitor(Visitor& visitor, Args&&... args) const
	{
		return do_visit<First, Types...>()(Internal(), which_, storage_,
			visitor, std::forward<Args>(args)...);
	}

private:

	//TODO implement with alignas when it is implemented in gcc
	//alignas(max<Alignof, First, Types...>::value) char[size_];
	union
	{
		char storage_[size_]; //max of size + alignof for each of Types...
		//the type with the max alignment
		typename max<Alignof, First, Types...>::type align_;
	};

	int which_;

	static std::function<void(void*)> handlers_[1 + sizeof...(Types)];

	void indicate_which(int which) 
	{
		which_ = which;
	}

	void* address() 
	{
		return storage_;
	}
	
	const void* address() const 
	{
		return storage_;
	}

	template <typename Visitor>
	typename Visitor::result_type
		apply_visitor_internal(Visitor& visitor)
	{
		return apply_visitor<true_, Visitor>(visitor);
	}

	template <typename Visitor>
	typename Visitor::result_type
		apply_visitor_internal(Visitor& visitor) const
	{
		return apply_visitor<true_, Visitor>(visitor);
	}

	void destroy()
	{
		destroyer d;
		apply_visitor_internal(d);
	}

	template <typename T>
	void construct(T&& t)
	{
		typedef typename std::remove_reference<T>::type type;
		new(storage_) type(std::forward<T>(t));
	}
};

template <typename First, typename... Types>
struct variant : public variant_base<First, Types...>
{
	//typedef variant_base<First, Types...> base;

	//using typename variant_base<First, Types...>::initialiser;

	template <
		typename T
		, typename Dummy = typename std::enable_if<
								!std::is_same<
									typename std::remove_reference<variant<First, Types...>>::type,
									typename std::remove_reference<T>::type
								>::value,
								T
							>::type
		>
	variant( T&& t )
	{
		std::cout << "variant( T&& t )" << std::endl;
		static_assert( ! std::is_same<variant<First, Types...>&, T>::value, "why is variant(T&&) instantiated with a variant?");
		//static_cast<base*>(this);

		//compile error here means that T is not unambiguously convertible to any of the types in (First, Types...)
		//initialiser<0, First, Types...>::initialise(*this, std::forward<T>(t));

		//variant_base<First, Types...>::template initialiser<0, First, Types...>::initialise(*this, std::forward<T>(t));
		variant_base<First, Types...>::template initialiser<0, First, Types...>::initialise(*this, std::forward<T>(t));
	}


};


struct bad_get : public std::exception
{
	virtual const char* what() const throw()
	{
		return "bad_get";
	}
};

template <typename T>
struct get_visitor
{
	typedef T* result_type;

	result_type operator()(T& val) const
	{
		return &val;
	}

	template <typename U>
	result_type operator()(const U& u) const
	{
		return nullptr;
	}
};




template <typename Visitor, typename Visitable, typename... Args>
typename Visitor::result_type
apply_visitor(Visitor& visitor, Visitable& visitable, Args&&... args)
{
	return visitable.template apply_visitor<false_>(visitor, std::forward<Args>(args)...);
}

template <typename Visitor, typename Visitable, typename... Args>
typename Visitor::result_type
apply_visitor(const Visitor& visitor, Visitable& visitable, Args&&... args)
{
	return visitable.template apply_visitor<false_>(visitor, std::forward<Args>(args)...);
}




//template <typename T, typename First, typename... Types>
//T* get(variant_base<First, Types...>* var)
//{
//	return apply_visitor(get_visitor<T>(), *var);
//}
//
//template <typename T, typename First, typename... Types>
//const T* get(const variant_base<First, Types...>* var)
//{
//	return apply_visitor(get_visitor<const T>(), *var);
//}

template <typename T, typename First, typename... Types>
T& get ( variant_base<First, Types...>& var )
{
	T* t = apply_visitor(get_visitor<T>(), var);
	if (t == nullptr){throw bad_get();}

	return *t;
}

template <typename T, typename First, typename... Types>
const T& get ( variant_base<First, Types...> const& var)
{
	const T* t = apply_visitor(get_visitor<const T>(), var);
	if (t == nullptr) {throw bad_get();}

	return *t;
}


#endif // variant_HPP__
