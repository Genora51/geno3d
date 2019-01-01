#include <sstream>
#include "Object.h"
#include "vecsort.h"

namespace Geno3D
{
    void Object::load(std::istream& stream) {
        std::string line;
        std::vector<Eigen::Vector3f> tempVerts;
        uvMap.push_back(sf::Vector2f(0, 0));
        while (std::getline(stream, line)) {
            std::istringstream ss{line};
            std::string ch;
            ss >> ch;
            if (ch == "v") {
                Eigen::Vector3f vert;
                for (int i=0; i<3; i++) {
                    ss >> vert(i);
                }
                tempVerts.push_back(vert);
            }
            else if (ch == "vt") {
                sf::Vector2f uv;
                ss >> uv.x >> uv.y;
                uvMap.push_back(uv);
            }
            else if (ch == "f") {
                Eigen::Vector3i face;
                Eigen::Vector3i texCoord(0, 0, 0);
                for (int i=0; i<3; i++) {
                    ss >> face(i);
                    if (ss.get() == '/') {
                        ss >> texCoord(i);
                    }
                }
                faces.push_back(face);
                texCoords.push_back(texCoord);
            }
        }
        verts = Eigen::Matrix3Xf(3, tempVerts.size());
        for (unsigned i=0; i < verts.cols(); ++i) {
            verts.col(i) = tempVerts[i];
        }
        calcNormals();
    }

    void Object::load(std::string str) {
        std::istringstream stream{str};
        this->load(stream);
    }

    void Object::sortFaces(const Eigen::Matrix3Xf& projected) {
        vecsort::sortVectors(faces, [projected](auto lhs, auto rhs) {
            float totl = projected(2, lhs(0) - 1) + projected(2, lhs(1) - 1) + projected(2, lhs(2) - 1);
            float totr = projected(2, rhs(0) - 1) + projected(2, rhs(1) - 1) + projected(2, rhs(2) - 1);
            return totl > totr;
        }, faces, texCoords);
    }

    void Object::transform(Eigen::Matrix3f t) {
        verts = t * verts;
        normals = t * normals / t.determinant();
    }

    void Object::calcNormals() {
        normals = Eigen::Matrix3Xf::Zero(3, verts.cols());
        for (int i=0; i<faces.size(); i++) {
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

    sf::VertexArray Object::render(Light *light, Camera *camera, int winHeight) {
        Eigen::Matrix3Xf projected = camera->project(verts);
        sortFaces(projected);
        Eigen::VectorXf lighting = light->vertexLighting(normals);
        sf::VertexArray shape(sf::Triangles, faces.size() * 3);
        int j = 0;
        for (int fn=0; fn<faces.size(); ++fn) {
            auto face = faces[fn];
            auto tc = texCoords[fn];
            for (int i=0; i<3; ++i) {
                int f = face(i) - 1;
                auto vec = projected.col(f);
                shape[j].position = sf::Vector2f(vec(0), winHeight - vec(1));
                float lightStrength = lighting(f) * 255;
                shape[j].color = sf::Color(lightStrength, lightStrength, lightStrength);
                if (textured) shape[j].texCoords = uvTexMap[tc(i)];
                ++j;
            }
        }
        return shape;
    }

    void Object::loadTexture(sf::Texture texture) {
        this->texture = texture;
        uvTexMap = std::vector<sf::Vector2f>();
        auto ts = texture.getSize();
        for (sf::Vector2f uv : uvMap) {
            uvTexMap.push_back(sf::Vector2f(uv.x * ts.x, (1-uv.y) * ts.y));
        }
        textured = true;
    }
}