#include "Support.h"
#include <limits>

namespace ngn {
	
    Support::Support() {
    }

    bool Support::containsPoint(Vector3D const & point, Real tol) const {
        for (int unsigned i = 0; i < points_.size(); ++i) {
            Vector3D diff = Vector3D::sub(points_.operator[](i), point);
            Real dist = diff.length();

            if (dist < tol) {
                return true;
            }
        }

        return false;
    }

    
    void Support::addPoint(Vector3D const & point) {
        if (points_.size() < maxSize) {
            points_.push_back(point);
        } else {
            throw SupportPointNotAddedException("point not added as support has reached its maximum size");
        }
    }

    
    Vector3D const & Support::getPoint(int i) const {
        return points_.at(i);
    }

    
    void Support::setPoint(int i, Vector3D const & point) {
        points_.at(i) = point;
    }

    
    void Support::resize(int newSize) {
        points_.resize(newSize);
    }

    
    int unsigned Support::size() const {
        return points_.size();
    }

    
    Sphere Support::update(Vector3D const & point) {
        switch (size()) {
            case 1:
                return update1(point);

            case 2:
                return update2(point);

            case 3:
                return update3(point);

            case 4:
                return update4(point);

            default:
                throw SupportInvalidSizeException("size of the support set greater than 4!");
        }
    }

    
    Sphere Support::update1(Vector3D const & point) {
        Sphere sphere = Sphere::fromTwoPoints(getPoint(0), point);
        addPoint(point);

        return sphere;
    }

    
    Sphere Support::update2(Vector3D const & point) {
        Vector3D const & p0 = getPoint(0);
        Vector3D const & p1 = getPoint(1);
        Vector3D const & p2 = point;

        Sphere spheres[3];
        Real minRadius = std::numeric_limits<Real>::max();
        int index = -1;

        spheres[0] = Sphere::fromTwoPoints(p0, p2);

        if (spheres[0].contains(p1)) {
            minRadius = spheres[0].getRadius();
            index = 0;
        }

        spheres[1] = Sphere::fromTwoPoints(p1, p2);

        if (spheres[1].getRadius() < minRadius) {
            if (spheres[1].contains(p0)) {
                minRadius = spheres[1].getRadius();
                index = 1;
            }
        }

        if (index != -1) {
            setPoint(1 - index, p2);

            return spheres[index];
        } else {
            Sphere res = Sphere::fromThreePoints(p0, p1, p2);
            assert(res.getRadius() <= minRadius);
            addPoint(p2);

            return res;
        }
    }

    
    Sphere Support::update3(Vector3D const & point) {
        const Vector3D & p0 = getPoint(0);
        const Vector3D & p1 = getPoint(1);
        const Vector3D & p2 = getPoint(2);
        const Vector3D & p3 = point;

        Sphere spheres[6];
        Real minRadius = std::numeric_limits<Real>::max();
        int index = -1;

        spheres[0] = Sphere::fromTwoPoints(p0, p3);
        if (spheres[0].contains(p1) && spheres[0].contains(p2)) {
            minRadius = spheres[0].getRadius();
            index = 0;
        }

        spheres[1] = Sphere::fromTwoPoints(p1, p3);
        if (spheres[1].getRadius() < minRadius && spheres[1].contains(p0) && spheres[1].contains(p2)) {
            minRadius = spheres[1].getRadius();
            index = 1;
        }

        spheres[2] = Sphere::fromTwoPoints(p2, p3);
        if (spheres[2].getRadius() < minRadius && spheres[2].contains(p0) && spheres[2].contains(p1)) {
            minRadius = spheres[2].getRadius();
            index = 2;
        }

        spheres[3] = Sphere::fromThreePoints(p0, p1, p3);
        if (spheres[3].getRadius() < minRadius && spheres[3].contains(p2)) {
            minRadius = spheres[3].getRadius();
            index = 3;
        }

        spheres[4] = Sphere::fromThreePoints(p0, p2, p3);
        if (spheres[4].getRadius() < minRadius && spheres[4].contains(p1)) {
            minRadius = spheres[4].getRadius();
            index = 4;
        }

        spheres[5] = Sphere::fromThreePoints(p1, p2, p3);
        if (spheres[5].getRadius() < minRadius && spheres[5].contains(p0)) {
            minRadius = spheres[5].getRadius();
            index = 5;
        }

        switch (index) {
            case 0:
                setPoint(1, p3);
                resize(2);
                return spheres[0];

            case 1:
                setPoint(0, p3);
                resize(2);
                return spheres[1];

            case 2:
                setPoint(0, p2);
                setPoint(1, p3);
                resize(2);
                return spheres[2];

            case 3:
                setPoint(2, p3);
                return spheres[3];

            case 4:
                setPoint(1, p3);
                return spheres[4];

            case 5:
                setPoint(0, p3);
                return spheres[5];

            default:
                Sphere sphere = Sphere::fromFourPoints(p0, p1, p2, p3);
                assert(sphere.getRadius() <= minRadius);
                addPoint(p3);
                return sphere;
        }
    }

    
    Sphere Support::update4(Vector3D const & point) {
        const Vector3D & p4 = point;

        // permutations of type 1
        int i1[4][4] = {
            {0, /*4*/ 1, 2, 3},
            {1, /*4*/ 0, 2, 3},
            {2, /*4*/ 0, 1, 3},
            {3, /*4*/ 0, 1, 2}
        };

        // permutations of type 2
        int i2[6][4] = {
            {0, 1, /*4*/ 2, 3},
            {0, 2, /*4*/ 1, 3},
            {0, 3, /*4*/ 1, 2},
            {1, 2, /*4*/ 0, 3},
            {1, 3, /*4*/ 0, 2},
            {2, 3, /*4*/ 0, 1}
        };

        // permutations of type 3
        int i3[4][4] = {
            {0, 1, 2, /*4*/ 3},
            {0, 1, 3, /*4*/ 2},
            {0, 2, 3, /*4*/ 1},
            {1, 2, 3, /*4*/ 0}
        };

        Sphere spheres[14];
        Real minRadius = std::numeric_limits<Real>::max();
        int index = -1;
        Real dist = std::numeric_limits<Real>::max();
        Real minDist = std::numeric_limits<Real>::max();
        int minIndex = -1;
        int k = 0; // sphere index

        // permutations of type 1
        for (int j = 0; j < 4; j++, k++) {
            spheres[k] = Sphere::fromTwoPoints(getPoint(i1[j][0]), p4);

            if (spheres[k].getRadius() < minRadius) {
                std::pair<bool, Real> test1 = spheres[k].contains2(getPoint(i1[j][1]));
                std::pair<bool, Real> test2 = spheres[k].contains2(getPoint(i1[j][2]));
                std::pair<bool, Real> test3 = spheres[k].contains2(getPoint(i1[j][3]));

                if (test1.first && test2.first && test3.first) {
                    minRadius = spheres[k].getRadius();
                    index = k;
                } else {
                    if (!test1.first && test1.second < minDist) {
                        minDist = test1.second;
                        minIndex = k;
                    }

                    if (!test2.first && test2.second < minDist) {
                        minDist = test2.second;
                        minIndex = k;
                    }

                    if (!test3.first && test3.second < minDist) {
                        minDist = test3.second;
                        minIndex = k;
                    }
                }
            }
        }

        // permutations of type 2
        for (int j = 0; j < 6; j++, k++) {
            spheres[k] = Sphere::fromThreePoints(getPoint(i2[j][0]), getPoint(i2[j][1]), p4);

            if (spheres[k].getRadius() < minRadius) {
                std::pair<bool, Real> test1 = spheres[k].contains2(getPoint(i2[j][2]));
                std::pair<bool, Real> test2 = spheres[k].contains2(getPoint(i2[j][3]));

                if (test1.first && test2.first) {
                    minRadius = spheres[k].getRadius();
                    index = k;
                } else {
                    if (!test1.first && test1.second < minDist) {
                        minDist = dist;
                        minIndex = k;
                    }

                    if (!test2.second && test2.second < minDist) {
                        minDist = dist;
                        minIndex = k;
                    }
                }
            }
        }

        // permutations of type 3
        for (int j = 0; j < 4; j++, k++) {
            spheres[k] = Sphere::fromFourPoints(getPoint(i3[j][0]), getPoint(i3[j][1]), getPoint(i3[j][2]), p4);

            if (spheres[k].getRadius() < minRadius) {
                std::pair<bool, Real> test = spheres[k].contains2(getPoint(i3[j][3]));

                if (test.first) {
                    minRadius = spheres[k].getRadius();
                    index = k;
                } else if (test.second < minDist) {
                    minDist = dist;
                    minIndex = k;
                }
            }
        }

        // Theoretically, index >= 0 should happen, but floating point round-off
        // error can lead to this.  When this happens, the sphere is chosen that
        // has the minimum absolute errors between points (barely) outside the
        // sphere and the sphere.
        if (index == -1) {
            //std::cout << "index == -1!!!\n";
            index = minIndex;
        }

        switch (index) {
            case 0:
                setPoint(1, p4);
                resize(2);
                return spheres[0];

            case 1:
                setPoint(0, p4);
                resize(2);
                return spheres[1];

            case 2:
                setPoint(0, getPoint(2));
                setPoint(1, p4);
                resize(2);
                return spheres[2];

            case 3:
                setPoint(0, getPoint(3));
                setPoint(1, p4);
                resize(2);
                return spheres[3];

            case 4:
                setPoint(2, p4);
                resize(3);
                return spheres[4];

            case 5:
                setPoint(1, p4);
                resize(3);
                return spheres[5];

            case 6:
                setPoint(1, getPoint(3));
                setPoint(2, p4);
                resize(3);
                return spheres[6];

            case 7:
                setPoint(0, p4);
                resize(3);
                return spheres[7];

            case 8:
                setPoint(0, getPoint(3));
                setPoint(2, p4);
                resize(3);
                return spheres[8];

            case 9:
                setPoint(0, getPoint(3));
                setPoint(1, p4);
                resize(3);
                return spheres[9];

            case 10:
                setPoint(3, p4);
                return spheres[10];

            case 11:
                setPoint(2, p4);
                return spheres[11];

            case 12:
                setPoint(1, p4);
                return spheres[12];

            case 13:
                setPoint(0, p4);
                return spheres[13];

            default:
                throw SupportInvalidIndexException("index is superior to 13!!!");
        }
    }
}