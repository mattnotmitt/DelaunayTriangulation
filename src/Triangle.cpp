//
// Created by matt on 22/11/2019.
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>
#include <cmath>
#include <stdexcept>
#include <map>
#include "Triangle.hpp"
#include "Vec.hpp"

int Triangle::getIndex() const {
    return index;
}

void Triangle::setIndex(int i) {
    Triangle::index = i;
}

const std::vector<int> &Triangle::getVertices() const {
    return vertices;
}

void Triangle::setVertices(const std::vector<int> &v) {
    // If triangle already populated, remove old edge and vertex references from Mesh
    if (edges.size() == 3) owner->removeEdges(index, edges);
    if (vertices.size() == 3) owner->removeVertTri(index, vertices);
    // Ensure vector of vertex indices is 3 long
    if (v.size() != 3) throw std::runtime_error("v must be 3 vertices long.");
    Triangle::vertices = v;
    // Pre-calculate circumcircle
    calcCircumcircle();
    // Set edges and vertex references
    setEdges(owner->newEdges(index, v));
    owner->updateVertTri(index, v);
}

const std::vector<double> &Triangle::getAttributes() const {
    return attributes;
}

void Triangle::setAttributes(const std::vector<double> &a) {
    Triangle::attributes = a;
}

std::istream &operator>>(std::istream &is, Triangle &triangle) {
    std::vector<int> vertices;
    int vertexIndex;
    for (int i = 0; i < 3; i++) {
        is >> vertexIndex;
        vertices.push_back(vertexIndex);
    }
    triangle.setVertices(vertices);
    std::vector<double> attributes;
    double next;
    while (is >> next) {
        attributes.push_back(next);
    }
    triangle.setAttributes(attributes);
    return is;
}

std::ofstream &operator<<(std::ofstream &ofs, Triangle &triangle) {
    ofs << triangle.index << " " << triangle.vertices[0] << " " << triangle.vertices[1] << " "
       << triangle.vertices[2];
    for (int i = 0; i < triangle.attributes.size(); i++) {
        ofs << " " << std::setprecision(12) << triangle.attributes[i];
    }
    ofs << "\n";
    return ofs;
}

/**
 * @details Given a Triangle made up of points @f$r_1, r_2, r_3@f$ where @f$r_i = \left(\begin{matrix}x_i\\ y_i\end{matrix}\right)@f$,
 * the circumcentre of the triangle @f$(O_x, O_y)@f$ and the circumcircle's radius @f$R@f$ can be found from
 *  @f[
 *		\mathbf{O} = \left(\begin{matrix}
 *		2O_x \\
 *		2O_y \\
 *		R^2 - O_x^2 - O_y^2
 *		\end{matrix}\right)
 *	@f]
 *	@f[
 *		\left(\begin{matrix}
 *		x_0^2 + y_0^2 \\
 *		x_1^2 + y_1^2 \\
 *		x_2^2 + y_2^2
 *		\end{matrix}\right)
 *		=
 *		\mathbf{O}\left(\begin{matrix}
 *		x_0 & y_0 & 1 \\
 *		x_1 & y_1 & 1 \\
 *		x_2 & y_2 & 1
 *		\end{matrix}\right)
 *	@f]
 *	So by solving for @f$\mathbf{O}@f$ the circumcircle's data can be found
 */
// View documentation at https://mattnotmitt.github.io/DelaunayTriangulation/d2/d51/classTriangle.html#ae009162df6d89b748cda15a1bec1fd9a
void Triangle::calcCircumcircle() {
    // Fetch coordinates of triangle's points
    std::vector<Vec> vecs = owner->resolvePoints(vertices);
    Eigen::Matrix3d m;
    // Instantiate the rhs matrix
    m << vecs[0].getX(), vecs[0].getY(), 1,
            vecs[1].getX(), vecs[1].getY(), 1,
            vecs[2].getX(), vecs[2].getY(), 1;
    // Instantiate the lhs vector
    Eigen::Vector3d v(vecs[0].getX() * vecs[0].getX() + vecs[0].getY() * vecs[0].getY(),
                      vecs[1].getX() * vecs[1].getX() + vecs[1].getY() * vecs[1].getY(),
                      vecs[2].getX() * vecs[2].getX() + vecs[2].getY() * vecs[2].getY());
    Eigen::Vector3d o = m.colPivHouseholderQr().solve(v); // Solve for O
    Triangle::circumcircle circc = {};
    // Get circumcircle properties from O
    circc.x = o(0) / 2.;
    circc.y = o(1) / 2.;
    circc.radius = std::sqrt(o(2) + circc.x * circc.x + circc.y * circc.y);
    setCc(circc);
}
/**
 * @details Given a point @f$\mathbf{p}@f$ and the centre of a circumcirclecircle @f$\mathbf{c}@f$, its distance from the circumcentre can be found
 * @f[
 * d = |\mathbf{p}-\mathbf{c}|
 * @f]
 * If @f$d < @f$ @ref circumcircle.radius then the point is inside the circumcircle
 */
// View documentation at https://mattnotmitt.github.io/DelaunayTriangulation/d2/d51/classTriangle.html#a4c1a5a53120a1bab78d4c512978b48de
bool Triangle::circumcircleContainsPoint(const Eigen::Vector2d &p) const {
    Eigen::Vector2d c(cc.x, cc.y);
    float dist = (p - c).norm();
    return dist < (float) cc.radius;
}

/**
 * @details Given a point @f$r = \left(\begin{matrix}x \\ y\end{matrix}\right)@f$ and a Triangle made up of
 * points @f$r_1, r_2, r_3@f$ where @f$r_i = \left(\begin{matrix}x_i\\ y_i\end{matrix}\right)@f$,
 * the barycentric coordinates of p, @f$(\lambda_1, \lambda_2, \lambda_3)@f$ can be determined
 * @f[
 * \left(\begin{matrix}\lambda_1 \\ \lambda_2\end{matrix}\right) = \left(\begin{matrix}
 * x_1-x_3 & x_2-x_3 \\
 * y_1-y_3 & y_2-y_3 \\
 * \end{matrix}\right)^{-1} \left( \left(\begin{matrix}x \\ y\end{matrix}\right)-\left(\begin{matrix}x_3\\ y_3\end{matrix}\right) \right)
 * @f]
 * @f[
 * 	\lambda_3 = 1 - \lambda_1 - \lambda_2
 * @f]
 */
// View documentation at https://mattnotmitt.github.io/DelaunayTriangulation/d2/d51/classTriangle.html#a45f2f690e862dc66d21fabcf890bcfe5
Eigen::Vector3d Triangle::barycentric(const Eigen::Vector2d &p) const {
    // Barycentric Technique https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
    std::vector<Vec> resVerts = owner->resolvePoints(vertices);
    Eigen::Matrix2d T;
    T << resVerts[0].getX() - resVerts[2].getX(), resVerts[1].getX() - resVerts[2].getX(),
            resVerts[0].getY() - resVerts[2].getY(), resVerts[1].getY() - resVerts[2].getY();
    Eigen::Vector2d r3(resVerts[2].getX(), resVerts[2].getY());
    Eigen::Vector2d res = T.inverse() * (p - r3);
    return Eigen::Vector3d(res(0), res(1), 1 - res(0) - res(1));
}

/**
 * @details First checks if point is inside pre-computed circumcircle, if it is, computes barycentric coordinates of the point
 * If all barycentric coordinates @f$ \lambda_i >= 0@f$ then point is inside triangle
 */
// View documentation at https://mattnotmitt.github.io/DelaunayTriangulation/d2/d51/classTriangle.html#a4c1a5a53120a1bab78d4c512978b48de
bool Triangle::containsPoint(const Eigen::Vector2d &p) const {
    if (!circumcircleContainsPoint(p)) return false; // If not in circumcircle, definitely not in triangle, save computationally expensive vector maths
    Eigen::Vector3d bar = barycentric(p);
    return (bar(0) >= 0) && (bar(1) >= 0) && (bar(2) >= 0);
}

const Triangle::circumcircle &Triangle::getCc() const {
    return cc;
}

void Triangle::setCc(const Triangle::circumcircle &cc) {
    Triangle::cc = cc;
}

const std::vector<std::pair<int, int> > &Triangle::getEdges() const {
    return edges;
}

void Triangle::setEdges(const std::vector<std::pair<int, int> > &es) {
    Triangle::edges = es;
}

bool Triangle::operator==(const Triangle &rhs) const {
    return index == rhs.index &&
           owner == rhs.owner &&
           attributes == rhs.attributes &&
           vertices == rhs.vertices &&
           edges == rhs.edges;
}

bool Triangle::operator!=(const Triangle &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, Triangle &triangle) {
    std::vector<Vec> vecs = triangle.owner->resolvePoints(triangle.vertices);
    os << "Triangle " << triangle.index << " is made up of points "  << vecs[0] << ", " << vecs[1] << ", " << vecs[2] << ".";
    return os;
}

/**
 * @details Area of triangle can be computed given a triangle with points represented by vector @f$ \mathbf{A, B, C}@f$
 * @f[
 * A_T = \frac{|\mathbf{A}-\mathbf{B}| |\mathbf{B}-\mathbf{C}|}{2}
 * @f]
 */
// View documentation at https://mattnotmitt.github.io/DelaunayTriangulation/d2/d51/classTriangle.html#a5b86d43152f84325da7c657650e1f3f1
double Triangle::area() const {
    std::vector<Vec> verts = owner->resolvePoints(vertices);
    Eigen::Vector2d a(verts[0].getX(), verts[0].getY());
    Eigen::Vector2d b(verts[1].getX(), verts[1].getY());
    Eigen::Vector2d c(verts[2].getX(), verts[2].getY());
    return .5 * (a-b).norm()*(b-c).norm();
}

IMesh *Triangle::getOwner() const {
    return owner;
}

