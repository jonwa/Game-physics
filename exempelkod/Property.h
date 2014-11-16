#pragma once

#include <functional>

template<typename T>
class Property
{
public:
	typedef std::function<T&(T& current_value, const T& in_value)> setter_t;
	typedef std::function<T&(T& current_value)> getter_t;
	typedef std::function<const T&(const T& current_value)> const_getter_t;

	T& operator = (const T &v){ return setter_(value, v); }
	operator const T& () const{ return const_getter_(value); }
	operator T& () { return getter_(value); }
	T& operator()() { return getter_(value); }

	void set_const_getter(const_getter_t getter)
	{
		const_getter_ = getter;
	}

	void set_getter(getter_t getter)
	{
		getter_ = getter;
	}

	void set_setter(setter_t setter)
	{
		setter_ = setter;
	}

	Property(const T& val)
		: value(val)
	{
		set_getter([&](T& v) -> T&{return v; });
		set_const_getter([&](const T& v) -> const T&{ return v; });
		set_setter([&](T& c_v, const T& i_v) ->T& { return c_v = i_v; });
	}

	Property()
		:value()
	{
		set_getter([&](T& v) -> T&{return v; });
		set_const_getter([&](const T& v) -> const T&{ return v; });
		set_setter([&](T& c_v, const T& i_v) ->T& { return c_v = i_v; });
	}

private:
	T value;
	setter_t setter_;
	getter_t getter_;
	const_getter_t const_getter_;
};