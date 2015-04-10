#ifndef UTILITIES_MUT_ARGUMENTS_HPP
#define UTILITIES_MUT_ARGUMENTS_HPP

namespace util {
inline namespace mut_arguments {

template<typename T>
class mut_arg {
public:
	// Get rid of implicit duplications at first:
	mut_arg()                          = delete;
	mut_arg(const mut_arg&)            = delete;
	mut_arg& operator=(const mut_arg&) = delete;
	mut_arg& operator=(mut_arg&&)      = delete;
	
	// But get back the move constructor:
	// since it is impossible to create a mut_arg
	// from an rvalue this shouldn't restrict the
	// checking:
	mut_arg(mut_arg&&)                 = default;
	
	T& operator*() & {return m_ref;}
	T* operator->() & {return &m_ref;}
	
	template<typename T2>
	friend mut_arg<T2> mut(T2& ref);
	template<typename T2>
	friend mut_arg<T2> mut(mut_arg<T2>& ref);
private:
	mut_arg(T& ref): m_ref{ref} {}
	T& m_ref;
};

template<typename T>
mut_arg<T> mut(T& ref) {return mut_arg<T>{ref};}

template<typename T>
mut_arg<T> mut(mut_arg<T>& ref) {return mut_arg<T>{ref.m_ref};}

} // namespace mut_arguments
} // namespace Util

#endif
