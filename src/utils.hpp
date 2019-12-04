#include <string>
#include <stdexcept>
#include "Triangle.hpp"
/**
 * @file utils.hpp
 * @brief Utils namespace header
 */

/**
 * Namespace of utility functions
 */
namespace Utils {
    /**
     * Find number of parameters in file import lines
     * @param line
     * @return number of parameters in line
     */
    int lineLength(const std::string &line);

    /**
     * Opens a stream with the specified file and verifies it has been opened correctly
     * @tparam Stream Stream of type std::ifstream or std::ofstream
     * @param gStream Reference to stream to be opened
     * @param fileName Name of file for stream to be opened with
     * @throws std::runtime_error File cannot be opened
     */
    template<typename Stream>
    void loadFile(Stream &gStream, const std::string &fileName) {
        gStream.open(fileName.c_str(), std::ios::binary);
        if (not gStream.is_open()) {
            std::stringstream ss;
            ss << "Could not open file \"" << fileName << "\".";
            throw std::runtime_error(ss.str());
        }
    }

    /**
     * Approximates integral of func over triangle using constant value approximation
     * @details The integral of @f$ f(x,y) @f$ can be approximated as the value of the function at
     * the circumcentre of the triangle @f$(O_{xT}, O_{yT})@f$ weighted by the triangle's area @f$ A_T @f$
     * @f[
     * \iint_T dxdy f(x,y) \approx A_T f(O_{xT}, O_{yT})
     * @f]
     * @tparam T function of signature double(double, double)
     * @param func numerical function returning value at point @f$(x,y)@f$
     * @param triangle Triangle to approximate integral over
     * @return approximated integral of function over triangle
     */
    // View documentation at https://mattnotmitt.github.io/DelaunayTriangulation/d4/d3d/namespaceUtils.html#aea35446b52e730679709eefcdf6fc8e2
    template<typename T>
    double constantValueApprox(T func, const Triangle &triangle) {
        return triangle.area() * func(triangle.getCc().x, triangle.getCc().y);
    }

    /**
     * Approximates integral of func over triangle using linear interpolation approximation
     * @details The integral of @f$ f(x,y) @f$ can be approximated as the value of the function at
     * any point in the triangle weighted by the triangle's area @f$ A_T @f$
     * Given the barymetric coordinates of the point in the triangle @f$(\lambda_1, \lambda_2, \lambda_3)@f$
     * and a Triangle made up of points @f$r_1, r_2, r_3@f$ where @f$r_i = (x_i, y_i)@f$,
     * @f[
     * \iint_T dxdy f(x,y) \approx \lambda_1\frac{f(x_1,y_1)}{A_T} + \lambda_2\frac{f(x_2,y_2)}{A_T} + \lambda_3f\frac{(x_3,y_3)}{A_T}
     * @f]
     * @tparam T function of signature double(double, double)
     * @param func numerical function returning value at point @f$(x,y)@f$
     * @param triangle Triangle to approximate integral over
     * @return approximated integral of function over triangle
     */
    // View documentation at https://mattnotmitt.github.io/DelaunayTriangulation/d4/d3d/namespaceUtils.html#a5795be8719aeb33bdfe657d70ed61207
    template<typename T>
    double linearInterpolationApprox(T func, const Triangle &triangle) {
        std::vector<Vec> vecs = triangle.getOwner()->resolvePoints(triangle.getVertices());
        Eigen::Vector3d bar = triangle.barycentric(Eigen::Vector2d(triangle.getCc().x, triangle.getCc().y));
        double area = triangle.area();
        return ((bar(0) * (func(vecs[0].getX(), vecs[0].getY()) / area)) +
                (bar(1) * (func(vecs[1].getX(), vecs[1].getY()) / area)) +
                (bar(2) * (func(vecs[2].getX(), vecs[2].getY()) / area)));
    }
}