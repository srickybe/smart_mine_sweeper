#include "Mobile.h"
#include <iostream>
#include "Matrix2D.h"
#include "RGBColor.h"
#include "MobileTestClass.h"

namespace ngn {
	
	Mobile::Mobile(Vector3D const & position, Real ang) {
		this->position = position;
		this->angle = ang;
		this->orientation = Matrix3D(Matrix2D::fromAngle(this->angle));
	}

	Real Mobile::getAngle() const {
		return angle;
	}
	
	void Mobile::setAngle(Real ang) {
		angle = ang;
		setOrientation(Matrix3D(Matrix2D::fromAngle(this->angle)));
	}
		
	Vector3D const & Mobile::getPosition() const {
		return position;
	}

	void Mobile::setPosition(Vector3D const & position) {
		this->position = position;
	}

	Matrix3D const & Mobile::getOrientation() const {
		return orientation;
	}

	void Mobile::setOrientation(Matrix3D const & orient) {
		orientation = orient;
	}

	void Mobile::print(std::ostream & out) const {
		out << "Vehicle{"; 
		out << "\nposition=" << position; 
		out << ", \norientation=\n" << orientation; 
		out << "\n}";
	}

	void Mobile::test() {
		Vector3D position(Vector3D(0.0, 0.0, 0.0));
		Real angle = 0.0;
		//Matrix3D orientation(Matrix3D::identity());
		std::shared_ptr<Mobile> v1(new MobileTestClass(position, angle));//orientation));
		std::cout << "*v1=\n" << *v1 << "\n";
		
		/*try {
			try (FileOutputStream fileOut = new FileOutputStream("/tmp/vehicle.ser")) {
				ObjectOutputStream out = new ObjectOutputStream(fileOut);
				out.writeObject(v1);
				out.close();
			}
			System.out.printf("Serialized data is saved in /tmp/vehicle.ser");
		} catch (IOException i) {
			System.err.println("SerializeDemo IOException");
			System.err.println("i.getClass() = " + i.getClass());
			System.err.println("i.getMessage() = " + i.getMessage());
		}
		
		std::shared_ptr<Mobile> v2 = nullptr;
		
		try {
			try (FileInputStream fileIn = new FileInputStream("/tmp/vehicle.ser")) {
				ObjectInputStream in = new ObjectInputStream(fileIn);
				v2 = (Mobile) in.readObject();
				in.close();
			}
		} catch (IOException i) {
			System.err.println("DeserializeDemo IOException");
			System.err.println("i.getMessage() = " + i.getMessage());
			return;
		} catch (ClassNotFoundException c) {
			System.err.println("Vehicle class not found");
			return;
		}

		System.out.println("Deserialized Simulation...");
		System.out.println("vehicle: \n" + v2);*/        
	}
	
	std::ostream & operator <<(std::ostream & out, Mobile const & mobile) {
		mobile.print(out);
		
		return out;
	}
}