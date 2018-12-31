#include <sstream>
#include "Object.h"

namespace Geno3D
{
    void Object::load(std::istream& stream) {
        std::string line;
        std::vector<Eigen::Vector3f> tempVerts;
        while (std::getline(stream, line)) {
            std::istringstream ss{line};
            char ch;
            ss >> ch;
            switch (ch) {
                case 'v': {
                    Eigen::Vector3f vert;
                    ss >> vert(0) >> vert(1) >> vert(2);
                    tempVerts.push_back(vert);
                    break;
                }
                case 'f': {
                    Eigen::Vector3i face;
                    ss >> face(0) >> face(1) >> face(2);
                    faces.push_back(face);
                    break;
                }
            }
        }
        verts = Eigen::Matrix3Xf(3, tempVerts.size());
        for (unsigned i=0; i < verts.cols(); ++i) {
            auto tv = tempVerts[i];
            for (unsigned j=0; j < verts.rows(); ++j) {
                verts(j, i) = tv(j);
            }
        }
        calcNormals();
    }

    void Object::load(std::string str) {
        std::istringstream stream{str};
        this->load(stream);
    }

    void Object::sortFaces(const Eigen::Matrix3Xf& projected) {
        std::sort(faces.begin(), faces.end(), [projected](auto lhs, auto rhs) {
            float totl = projected(2, lhs(0) - 1) + projected(2, lhs(1) - 1) + projected(2, lhs(2) - 1);
            float totr = projected(2, rhs(0) - 1) + projected(2, rhs(1) - 1) + projected(2, rhs(2) - 1);
            return totl > totr;
        });
    }

    void Object::transform(Eigen::Matrix3f t) {
        verts = t * verts;
        normals = t * normals / t.determinant();
    }

    void Object::calcNormals() {
        normals = Eigen::Matrix3Xf::Zero(3, verts.cols());
        for (int i=0; i<verts.cols(); i++) {
            auto face = faces[i];
            int f0 = face(0) - 1;
            int f1 = face(1) - 1;
            int f2 = face(2) - 1;
            auto pointA = verts.col(f0);
            auto pointB = verts.col(f1);
            auto pointC = verts.col(f2);
            auto crossProd = (pointC - pointA).cross(pointB - pointA);
            normals.col(f0) += crossProd;
            normals.col(f1) += crossProd;
            normals.col(f2) += crossProd;
        }
        normals.colwise().normalize();
    }
}