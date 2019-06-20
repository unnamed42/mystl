#ifndef CRTP_COMPARABLE
#define CRTP_COMPARABLE

#include "meta/bits/is_same.hpp"
#include "meta/bits/enable_if.hpp"

#include "utility/bits/forward.hpp"

namespace stl {

class comparable_access {
    template <class D, class C> friend class comparable;

    template <class T, class U>
    static constexpr auto compare(T &&t, U &&u) { return t.compare(forward<U>(u)); }
};

template <class Derived, class Compared>
class comparable {
private:
    constexpr       Derived& derived()       noexcept { return *static_cast<Derived*>(this); }
    constexpr const Derived& derived() const noexcept { return *static_cast<const Derived*>(this); }
private:
    using access = comparable_access;
public:
    constexpr comparable() noexcept = default;

    constexpr bool operator<(const Compared &com) const { return access::compare(derived(), com) < 0; }
    constexpr bool operator>(const Compared &com) const { return access::compare(derived(), com) > 0; }
    constexpr bool operator==(const Compared &com) const { return access::compare(derived(), com) == 0; }
    constexpr bool operator!=(const Compared &com) const { return !operator==(com); }
    constexpr bool operator<=(const Compared &com) const { return !operator>(com); }
    constexpr bool operator>=(const Compared &com) const { return !operator<(com); }
};

template <class T, class Compared>
constexpr enable_if_t<!is_same_v<T, Compared>, bool> operator<(const Compared &com, const comparable<T, Compared> &obj) { return obj > com; }
template <class T, class Compared>
constexpr enable_if_t<!is_same_v<T, Compared>, bool> operator>(const Compared &com, const comparable<T, Compared> &obj) { return obj < com; }
template <class T, class Compared>
constexpr enable_if_t<!is_same_v<T, Compared>, bool> operator==(const Compared &com, const comparable<T, Compared> &obj) { return obj == com; }
template <class T, class Compared>
constexpr enable_if_t<!is_same_v<T, Compared>, bool> operator!=(const Compared &com, const comparable<T, Compared> &obj) { return !(obj == com); }
template <class T, class Compared>
constexpr enable_if_t<!is_same_v<T, Compared>, bool> operator<=(const Compared &com, const comparable<T, Compared> &obj) { return !(com > obj); }
template <class T, class Compared>
constexpr enable_if_t<!is_same_v<T, Compared>, bool> operator>=(const Compared &com, const comparable<T, Compared> &obj) { return !(com < obj); }

} // namespace stl

#endif // CRTP_COMPARABLE
