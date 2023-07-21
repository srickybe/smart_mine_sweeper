#include "Quaternion.h"

namespace ngn {
	
    Real const Quaternion::EPS = 1.0e-6;

    
    Quaternion Quaternion::identity() {
        return Quaternion(1.0, 0.0, 0.0, 0.0);
    }

    
    Quaternion Quaternion::zero() {
        return Quaternion(0.0, 0.0, 0.0, 0.0);
    }

    
    Quaternion::Quaternion()
    : cmp() {
    }

    
    Quaternion::Quaternion(Quaternion const & q)
    : Quaternion(
    q.getW(),
    q.getX(),
    q.getY(),
    q.getZ()
    ) {
    }

    
    Quaternion::Quaternion(Real fW, Real fX, Real fY, Real fZ) {
        cmp[0] = fW;
        cmp[1] = fX;
        cmp[2] = fY;
        cmp[3] = fZ;
    }

    
    void Quaternion::setX(Real x) {
        cmp[1] = x;
    }

    
    void Quaternion::setY(Real y) {
        cmp[2] = y;
    }

    
    void Quaternion::setZ(Real z) {
        cmp[3] = z;
    }

    
    void Quaternion::setW(Real w) {
        cmp[0] = w;
    }

    
    void Quaternion::set(int i, Real val) {
        cmp[i] = val;
    }

    
    Real Quaternion::getX() const {
        return cmp[1];
    }

    
    Real Quaternion::getY() const {
        return cmp[2];
    }

    
    Real Quaternion::getZ() const {
        return cmp[3];
    }

    
    Real Quaternion::getW() const {
        return cmp[0];
    }

    
    Real Quaternion::get(int i) const {
        return cmp[i];
    }

    
    Quaternion Quaternion::add(
            Quaternion const & lhs,
            Quaternion const & rhs
            ) {
        return Quaternion(
                lhs.getW() + rhs.getW(),
                lhs.getX() + rhs.getX(),
                lhs.getY() + rhs.getY(),
                lhs.getZ() + rhs.getZ()
                );
    }

    
    Quaternion & Quaternion::add(Quaternion const & rhs) {
        setW(getW() + rhs.getW());
        setX(getX() + rhs.getX());
        setY(getY() + rhs.getY());
        setZ(getZ() + rhs.getZ());

        return *this;
    }

    
    Quaternion & Quaternion::conj() {
        setX(-getX());
        setY(-getY());
        setZ(-getZ());

        return *this;
    }

    
    Quaternion Quaternion::conj(Quaternion const & q) {
        return Quaternion(q.getW(), -q.getX(), -q.getY(), -q.getZ());
    }

    
    bool Quaternion::isUnit() const {
        return Math<Real>::abs(length() - 1.0) < EPS;
    }

    
    Quaternion Quaternion::fromAxisAngle(
            AxisAngle const & axisAngle
	) {
        Real angle = axisAngle.getAngle();
        Real cos = Math<Real>::cos(angle / 2.0);
        Real sin = Math<Real>::sin(angle / 2.0);
        Quaternion res;
        res.setW(cos);

        Vector3D axis = axisAngle.getAxis();
        res.setX(axis.getX() * sin);
        res.setY(axis.getY() * sin);
        res.setZ(axis.getZ() * sin);

        return res;
    }

    
    AxisAngle Quaternion::toAxisAngle() const {
        if (isUnit()) {
            if (Math<Real>::abs(getW()) == 1.0) {
                return AxisAngle(Vector3D(1.0, 0.0, 0.0), 0.0);
            } else {
                Real angle = 2 * Math<Real>::acos(getW());
                Vector3D axis(getX(), getY(), getZ());
                axis.mult(1.0 / Math<Real>::sqrt(1 - getW() * getW()));

                return AxisAngle(axis, angle);
            }
        } else {
            throw UnsupportedOperationException(
                    "Quaternion is not a rotation"
                    );
        }
    }

    
    Matrix3D Quaternion::toRotationMatrix() const {
        Real xx = getX() * getX();
        Real xy = getX() * getY();
        Real xz = getX() * getZ();
        Real xw = getX() * getW();

        Real yy = getY() * getY();
        Real yz = getY() * getZ();
        Real yw = getY() * getW();

        Real zz = getZ() * getZ();
        Real zw = getZ() * getW();

        return Matrix3D(
                1 - 2 * (yy + zz),
                2 * (xy - zw),
                2 * (xz + yw),
                2 * (xy + zw),
                1 - 2 * (xx + zz),
                2 * (yz - xw),
                2 * (xz - yw),
                2 * (yz + xw),
                1 - 2 * (xx + yy));
    }

    
    Quaternion & Quaternion::invert() {
        Real lenSq = lengthSquared();

        if (lenSq == 0.0) {
            throw UnsupportedOperationException(
                    "Length squared of quaternion is equal to zero"
                    );
        }

        conj();
        mult(1.0 / lengthSquared());

        return *this;
    }

    
    Quaternion Quaternion::invert(Quaternion const & q) {
        Quaternion res(q);
        res.invert();

        return res;
    }

    
    Real Quaternion::length() const {
        return Math<Real>::sqrt(lengthSquared());
    }

    
    Real Quaternion::lengthSquared() const {
        return getX() * getX()
                + getY() * getY()
                + getZ() * getZ()
                + getW() * getW();
    }

    
    Quaternion & Quaternion::mult(Real rhs) {
        setW(getW() * rhs);
        setX(getX() * rhs);
        setY(getY() * rhs);
        setZ(getZ() * rhs);

        return *this;
    }

    
    Quaternion Quaternion::mult(Quaternion const & lhs, Real rhs) {
        return Quaternion(
                lhs.getW() * rhs,
                lhs.getX() * rhs,
                lhs.getY() * rhs,
                lhs.getZ() * rhs
                );
    }

    
    Quaternion Quaternion::mult(Quaternion const & rhs) const {
        return Quaternion(
                getW() * rhs.getW() - getX() * rhs.getX()
                - getY() * rhs.getY() - getZ() * rhs.getZ(),
                getW() * rhs.getX() + getX() * rhs.getW()
                + getY() * rhs.getZ() - getZ() * rhs.getY(),
                getW() * rhs.getY() - getX() * rhs.getZ()
                + getY() * rhs.getW() + getZ() * rhs.getX(),
                getW() * rhs.getZ() + getX() * rhs.getY()
                - getY() * rhs.getX() + getZ() * rhs.getW()
                );
    }

    
    Quaternion & Quaternion::negate() {
        setW(-getW());
        setX(-getX());
        setY(-getY());
        setZ(-getZ());

        return *this;
    }

    
    Quaternion Quaternion::negate(Quaternion const & rhs) {
        return Quaternion(-rhs.getW(), -rhs.getX(), -rhs.getY(), -rhs.getZ());
    }

    
    Quaternion & Quaternion::norm() {
        Real len = length();

        if (len == 0.0) {
            throw new UnsupportedOperationException("Length of quaternion is equal to zero");
        }

        mult(1.0 / len);

        return *this;
    }

    
    Quaternion Quaternion::norm(Quaternion const & q) {
        Quaternion res(q);
        res.norm();

        return res;
    }

    
    std::ostream & operator<<(std::ostream & out, Quaternion const & q) {
        out << std::right << std::setw(12) << std::setprecision(6)
                << q.getW();
        out << std::right << std::setw(12) << std::setprecision(6)
                << q.getX();
        out << std::right << std::setw(12) << std::setprecision(6)
                << q.getY();
        out << std::right << std::setw(12) << std::setprecision(6)
                << q.getZ();

        return out;
    }

    
    void testToRotationMatrix() {
        AxisAngle aa(
                Vector3D(0.0, 0.0, 1.0),
                Math<Real>::PI / 2
                );
        Matrix3D mat;
        mat = Matrix3D::fromAxisAngle(aa);
        std::cout << "aa = " << aa << "\n";
        std::cout << "mat = " << mat << "\n";
        Quaternion quat(Quaternion::fromAxisAngle(aa));
        std::cout << "quat = " << quat << "\n";
        Matrix3D mat1 = quat.toRotationMatrix();
        std::cout << "mat1 = " << mat1 << "\n";
        std::cout << "mat.equals(mat1) ? " << mat.equalsWithTol(mat1, (Real)1.0e-6) << "\n";
        ;
    }

    
    void testQuaternion() {
        Quaternion q = Quaternion::zero();
        Real coord = 1.0 / Math<Real>::sqrt(3.0);
        Vector3D axis(coord, coord, coord);
        Real angle = Math<Real>::PI / 2.5;
        AxisAngle aa(axis, angle);
        std::cout << "axis = " << axis << "\n";
        std::cout << "angle = " << angle << "\n";
        q = Quaternion::fromAxisAngle(aa);
        std::cout << "q = " << q << "\n";
        std::cout << "q.length() = " << q.length() << "\n";
        AxisAngle axisAngle = q.toAxisAngle();
        std::cout << "pair = " << axisAngle << "\n";
        axis = Vector3D(
                util::Rand<Real>::getInstance().next(),
                util::Rand<Real>::getInstance().next(),
                util::Rand<Real>::getInstance().next()
                );
        axis.norm();
        std::cout << "axis = " << axis << "\n";
        angle = 2.0 * Math<Real>::PI * util::Rand<Real>::getInstance().next();
        std::cout << "angle = " << angle << "\n";
        aa = AxisAngle(axis, angle);
        q.fromAxisAngle(aa);
        std::cout << "q = " << q << "\n";
        axisAngle = q.toAxisAngle();
        std::cout << "axisAngle = " << axisAngle << "\n";
    }
}