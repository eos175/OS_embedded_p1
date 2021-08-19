#include <stdint.h>


static inline double fast_sin(double x) {
    // Polynomial constants generated with sollya.
    // fpminimax(sin(x), [|1,3,5,7|], [|D...|], [-pi/2;pi/2]);
    // Both relative and absolute error is 9.39e-7.
    const double magicround =  6755399441055744.0;
    const double negpi      = -3.14159265358979323846264338327950288;
    const double invpi      =  0.31830988618379067153776752674502872;
    const double a          = -0.00018488140186756154724131984146140;
    const double b          =  0.00831189979755905285208061883395203;
    const double c          = -0.16665554092439083255783316417364403;
    const double d          =  0.99999906089941981157664940838003531;

    // Range-reduce to [-pi/2, pi/2] and store if period is odd.
    union { double x; uint64_t i; } u = { invpi*x + magicround };
    uint64_t odd_period = u.i << 63;
    u.x = x + negpi*(int32_t)(u.i & 0xffffffff);

    // 7th degree odd polynomial followed by IEEE754 sign flip on odd periods.
    double x2 = u.x*u.x;
    double p = d + x2*(c + x2*(b + x2*a));
    u.i ^= odd_period;
    return u.x * p;
}


static inline double fast_cos(double x) {
    const double pi_2 =  1.57079632679489661923132169163975144;
    return fast_sin(x + pi_2);
}


#define EXTRA_PRECISION     1

template<typename T>
inline T cos2(T x) noexcept
{
    constexpr T tp = 1./(2.*M_PI);
    x *= tp;
    x -= T(.25) + std::floor(x + T(.25));
    x *= T(16.) * (std::abs(x) - T(.5));
    #if EXTRA_PRECISION
    x += T(.225) * x * (std::abs(x) - T(1.));
    #endif
    return x;
}

