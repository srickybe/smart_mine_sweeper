#ifndef SUPPORT_H
#define SUPPORT_H

#include <exception>
#include <cassert>
#include <string>
#include <vector>
#include "Sphere.h"
#include "Vector3D.h"


namespace ngn {

    class Sphere;
	
    class Support {
    public:

        class SupportPointNotAddedException : public std::exception {
        public:

            SupportPointNotAddedException(std::string const & message) {
                message_ = message;
            }

        private:
            std::string message_;
        };

        class SupportInvalidSizeException : public std::exception {
        public:

            SupportInvalidSizeException(std::string const & message) {
                message_ = message;
            }

        private:
            std::string message_;
        };

        class SupportInvalidIndexException: public std::exception  {
        public:
            SupportInvalidIndexException(std::string const & message) {
                message_ = message;
            }

        private:
            std::string message_;
        };

        ////////////////////////////////////////////////////////////////////////

        Support();

        void addPoint(Vector3D const & point);
        bool containsPoint(Vector3D const & point, Real tol) const;
        Vector3D const & getPoint(int i) const;
        void resize(int newSize);
        void setPoint(int i, Vector3D const & point);
        int unsigned size() const;
        Sphere update(Vector3D const & point);
        Sphere update1(Vector3D const & point);
        Sphere update2(Vector3D const & point);
        Sphere update3(Vector3D const & point);
        Sphere update4(Vector3D const & point);

    private:
        std::vector<Vector3D > points_;
        int unsigned const maxSize = 4;
    };

    ////////////////////////////////////////////////////////////////////////////////
}

#endif /* SUPPORT_H */
