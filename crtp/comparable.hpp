#ifndef CRTP_COMPARABLE
#define CRTP_COMPARABLE

#include "meta/check.hpp"
#include "meta/sfinae.hpp"

#include "utility/forward.hpp"

namespace stl {

class comparable_access {
    template <class D, class C> friend class comparable;

    template <class T, class U>
    static auto compare(T &&t, U &&u) { return t.compare(forward<U>(u)); }
};

template <class Derived, class Compared>
class comparable {
private:
          Derived& derived()       noexcept { return *static_cast<Derived*>(this); }
    const Derived& derived() const noexcept { return *static_cast<const Derived*>(this); }
private:
    using access = comparable_access;
public:
    comparable() noexcept = default;

    bool operator<(const Compared &com) const { return access::compare(derived(), com) < 0; }
    bool operator>(const Compared &com) const { return access::compare(derived(), com) > 0; }
    bool operator==(const Compared &com) const { return access::compare(derived(), com) == 0; }
    bool operator!=(const Compared &com) const { return !operator==(com); }
    bool operator<=(const Compared &com) const { return !operator>(com); }
    bool operator>=(const Compared &com) const { return !operator<(com); }
};

template <class T, class Compared>
enable_if_t<!is_same_v<T, Compared>, bool> operator<(const Compared &com, const comparable<T, Compared> &obj) { return obj > com; }
template <class T, class Compared>
enable_if_t<!is_same_v<T, Compared>, bool> operator>(const Compared &com, const comparable<T, Compared> &obj) { return obj < com; }
template <class T, class Compared>
enable_if_t<!is_same_v<T, Compared>, bool> operator==(const Compared &com, const comparable<T, Compared> &obj) { return obj == com; }
template <class T, class Compared>
enable_if_t<!is_same_v<T, Compared>, bool> operator!=(const Compared &com, const comparable<T, Compared> &obj) { return !(obj == com); }
template <class T, class Compared>
enable_if_t<!is_same_v<T, Compared>, bool> operator<=(const Compared &com, const comparable<T, Compared> &obj) { return !(com > obj); }
template <class T, class Compared>
enable_if_t<!is_same_v<T, Compared>, bool> operator>=(const Compared &com, const comparable<T, Compared> &obj) { return !(com < obj); }

} // namespace stl

#endif // CRTP_COMPARABLE
