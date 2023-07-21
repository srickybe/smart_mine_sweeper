#ifndef MATH_H
#define MATH_H


#include <algorithm>
#include <cmath>

namespace ngn {
	
	template <class Real>
    class Math {
    public:
        static Real abs(Real a);
        static Real acos(Real a);
        static bool areEqualWithTol(Real a, Real b, Real eps);
		static Real atan(Real x);
        static Real atan2(Real x, Real y);
        static Real cos(Real a);
		static Real const E;
		static Real radToDeg(Real a);
		static Real exp(Real a);
        static Real const GOLDEN_RATIO;
		static Real min(Real a, Real b);
        static Real max(Real a, Real b);
        static Real const PI;
        static Real pow(Real base, Real exponent);
        static Real sin(Real a);
        static Real sqr(Real a);
        static Real sqrt(Real a);
    };
	
	template <class Real>
	Real Math<Real>::abs(Real a) {
        return std::abs(a);
    }

    template <class Real>
    Real Math<Real>::acos(Real a) {
        return std::acos(a);
    }

    template <class Real>
    bool Math<Real>::areEqualWithTol(Real a, Real b, Real eps) {
        return std::abs(a - b) < eps;
    }
	
    template <class Real>
    Real Math<Real>::atan(Real x) {
        return std::atan(x);
    }
	
	template <class Real>
    Real Math<Real>::atan2(Real x, Real y) {
        return std::atan2(x, y);
    }

    template <class Real>
    Real Math<Real>::cos(Real a) {
        return std::cos(a);
    }

	template <class Real>
	Real Math<Real>::radToDeg(Real angle) {
		return angle * 180.0 / Math<Real>::PI;
	}
	
	template <class Real>
	Real const Math<Real>::E 
	= (Real) 2.71828182845904523536028747135266249775724709369995957496696762772407663035354759; //80 digits
    
    template <class Real>
    Real Math<Real>::exp(Real a) {
        return std::exp(a);
    }
	
	template <class Real>
    Real const Math<Real>::GOLDEN_RATIO
    = (Real) 1.61803398874989484820458683436563811772030917980576286213544862270526046281890;

    template <class Real>
    Real Math<Real>::max(Real a, Real b) {
        return std::max(a, b);
    }

	template <class Real>
    Real Math<Real>::min(Real a, Real b) {
		return std::min(a, b);
	}
	
	template <class Real>
    Real const Math<Real>::PI
    = (Real) 3.141592653589793238462643383279502884197169399375105820974944592307816406286;

    template <class Real>
    Real Math<Real>::pow(Real base, Real exponent) {
        return std::pow(base, exponent);
    }

    template <class Real>
    Real Math<Real>::sin(Real a) {
        return std::sin(a);
    }

    template <class Real>
    Real Math<Real>::sqr(Real a) {
        return a * a;
    }

    template <class Real>
    Real Math<Real>::sqrt(Real a) {
        return std::sqrt(a);
    }
	
}

#endif // MATH_H
