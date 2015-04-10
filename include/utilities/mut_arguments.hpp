#ifndef UTILITIES_MUT_ARGUMENTS_HPP
#define UTILITIES_MUT_ARGUMENTS_HPP

namespace util {

/**
 * If this is used everywhere throughout the project,
 * it is probably desirable to permit pulling it into the
 * global namespace. In order to allow that in an easy and
 * (relatively) clean way, we put all of it into an inline-
 * namespace, just like the stdlib does with it's literals.
 *
 * That than permits
 *
 *   using namespace util::mut_arguments;
 */
inline namespace mut_arguments {

/**
 * The mut-reference-wrapper. This class-template cannot
 * in any classical way be copied, assigned or created other
 * than using the function-template `mut` below (aside from
 * cheating with some kind of cast; if you do that, you are
 * someone I don't want to work with and should feel bad).
 *
 * Intended usage: Take the reference by Value like this:
 *
 *      void fun(mut_arg<int> arg) { ... }
 *
 * In order to pass something to this function, you need a
 * mutable reference to that value, usually by having it inside
 * the current scope. you than wrap that in a call to mut(),
 * whose returnvalue you can than directly pass into the function.
 * Important note: You CANNOT save the returnvalue and pass it later;
 * this is by design.
 *
 *     int var = 42;
 *     fun(mut(var));       // how to pass the variable
 *     auto ref = mut(var); // this will work, but
 *     fun(ref);            // this won't.
 *
 * When you want to change the referenced value (if you never
 * want to do that, take the argument by normal const-reference!),
 * you can get the referenced value by the normal dereference-syntax:
 *
 *     *arg = 23;
 *
 * If you want to pass it to another function that also requires a
 * mutable reference, you can call mut directly on the wrapped argument:
 *
 *     void fun2(mut_arg<int> arg) {
 *         fun(mut(arg));
 *
 * Please note that there isn't yet real experience with this facility
 * in practical use; The existing background is this:
 * Google requires output-parameters being passed by pointer, in
 * order to make the possible change visible at the call-side by forcing
 * the use of the adressof-operator. This is in several ways problematic
 * and not recommendable, but the basic idea of pointing out possible
 * changes does have it's merits. the set of stuff provided here is intended
 * to be a cleaner, library-based approach to that.
 */
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
