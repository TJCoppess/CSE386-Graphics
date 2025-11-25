/****************************************************
 * 2016-2025 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <iostream>
#include "defs.h"
#include "utilities.h"
#include "io.h"

 /**
  * @fn	vector<dvec4> multiplyMatrixAndVertices(const dmat4 &M, const vector<dvec4> &verts)
  * @brief	Returns the vector containing: <M*verts[0], M*verts[1], ... M*verts[n-1]>
  * @param	M	 	A dmat4 to process.
  * @param	verts	The vertices.
  * @return	Returns the vector: <M*verts[0], M*verts[1], ... M*verts[n-1]>
  */

vector<dvec4> multiplyMatrixAndVertices(const dmat4& M, const vector<dvec4>& verts) {
    vector<dvec4> result;
    for (const dvec4& v : verts) {
        result.push_back(M * v);
    }
    return result;
}

// Corners of 2x2x2 cube centered on origin.
vector<dvec4> cubeVerts = {
    dvec4(-1, -1, -1, 1),
    dvec4(-1, 1,-1, 1),
    dvec4(1, 1,-1, 1),
    dvec4(1,-1,-1, 1),
    dvec4(-1,-1, 1, 1),
    dvec4(-1, 1, 1, 1),
    dvec4(1, 1, 1, 1),
    dvec4(1,-1, 1, 1),
};

void processVertices(const dmat4& modelMat,
                    const dmat4& viewMat,
                    const dmat4& projMat,
                    const dmat4& viewportMat,
                    const vector<dvec4>& verts) {

    cout << "THE MATRICES" << endl;
    cout << "Modeling\n" << modelMat << endl;
    cout << "Viewing\n" << viewMat << endl;
    cout << "Projection\n" << projMat << endl;
    cout << "Viewport\n" << viewportMat << endl;

    // Stage 1.
    vector<dvec4> world = multiplyMatrixAndVertices(modelMat, verts);            // set world to the proper values
    cout << "WORLD COORDINATES\n" << world << endl;

    // Stage 2.
    vector<dvec4> eye = multiplyMatrixAndVertices(viewMat, world);              // set eye to the proper values
    cout << "EYE COORDINATES\n" << eye << endl;

    // Stage 3.
    vector<dvec4> projected = multiplyMatrixAndVertices(projMat, eye);       // set projected to the proper values
    cout << "PROJECTED COORDINATES\n" << projected << endl;

    // Stage 4. Perspective division.
    vector<dvec4> ndc;            // set ndc to the proper values
    for (const dvec4& v : projected) {
        ndc.push_back(v / v.w);
    }
    cout << "NORMALIZED DEVICE COORDINATES (after perspective division)\n" << ndc << endl;

    // Stage 5.
    vector<dvec4> window = multiplyMatrixAndVertices(viewportMat, ndc);        // set window to the proper values
    cout << "WINDOW COORDINATES\n" << window << endl;
}

int main(int argc, char* argv[]) {
    double NX = 500;
    double NY = 250;

    dmat4 modelMat = T(2, 0, 3) * S(0.5, 1.0, 1.0);
    dmat4 viewMat = lookAt(glm::vec3(3, 3, 3),
                            glm::vec3(0, 0, 0),
                            glm::vec3(0, 1, 0));;
    // dmat4 projMat = glm::ortho(-4.0, +4.0, -3.0, +3.0, 0.0, 7.0);
    dmat4 projMat = glm::perspective(glm::radians(125.0f), 2.0f, 0.1f, 5.0f);
    dmat4 viewportMat = T(0, 0, 0)*S(NX / 2, NY / 2, 1)*T(1, 1, 0);

    processVertices(modelMat, viewMat, projMat, viewportMat, cubeVerts);
    
    return 0;
}
/* OUTPUT (PERSPECTIVE PROJECTION)
THE MATRICES
Modeling
[ [ 0.5 0 0 2 ]
[ 0 1 0 0 ]
[ 0 0 1 3 ]
[ 0 0 0 1 ]
]
Viewing
[ [ 0.707107 0 -0.707107 -0 ]
[ -0.408248 0.816497 -0.408248 -0 ]
[ 0.57735 0.57735 0.57735 -5.19615 ]
[ 0 0 0 1 ]
]
Projection
[ [ 0.260283 0 0 0 ]
[ 0 0.520567 0 0 ]
[ 0 0 -1.04082 -0.204082 ]
[ 0 0 -1 0 ]
]
Viewport
[ [ 250 0 0 250 ]
[ 0 125 0 125 ]
[ 0 0 1 0 ]
[ 0 0 0 1 ]
]
WORLD COORDINATES
[
        [ 1.5 -1 2 1 ]
        [ 1.5 1 2 1 ]
        [ 2.5 1 2 1 ]
        [ 2.5 -1 2 1 ]
        [ 1.5 -1 4 1 ]
        [ 1.5 1 4 1 ]
        [ 2.5 1 4 1 ]
        [ 2.5 -1 4 1 ]
]
EYE COORDINATES
[
        [ -0.353553 -2.24537 -3.75278 1 ]
        [ -0.353553 -0.612372 -2.59808 1 ]
        [ 0.353553 -1.02062 -2.02073 1 ]
        [ 0.353553 -2.65361 -3.17543 1 ]
        [ -1.76777 -3.06186 -2.59808 1 ]
        [ -1.76777 -1.42887 -1.44338 1 ]
        [ -1.06066 -1.83712 -0.866025 1 ]
        [ -1.06066 -3.47011 -2.02073 1 ]
]
PROJECTED COORDINATES
[
        [ -0.0920241 -1.16886 3.70187 3.75278 ]
        [ -0.0920241 -0.318781 2.50004 2.59808 ]
        [ 0.0920241 -0.531301 1.89912 2.02073 ]
        [ 0.0920241 -1.38138 3.10095 3.17543 ]
        [ -0.460121 -1.5939 2.50004 2.59808 ]
        [ -0.460121 -0.743822 1.29821 1.44338 ]
        [ -0.276072 -0.956343 0.697292 0.866025 ]
        [ -0.276072 -1.80642 1.89912 2.02073 ]
]
NORMALIZED DEVICE COORDINATES (after perspective division)
[
        [ -0.0245216 -0.311466 0.986435 1 ]
        [ -0.0354201 -0.122699 0.962265 1 ]
        [ 0.0455401 -0.262926 0.939822 1 ]
        [ 0.0289801 -0.435023 0.976547 1 ]
        [ -0.1771 -0.613494 0.962265 1 ]
        [ -0.318781 -0.515335 0.899424 1 ]
        [ -0.318781 -1.10429 0.805163 1 ]
        [ -0.13662 -0.893949 0.939822 1 ]
]
WINDOW COORDINATES
[
        [ 243.87 86.0667 0.986435 1 ]
        [ 241.145 109.663 0.962265 1 ]
        [ 261.385 92.1342 0.939822 1 ]
        [ 257.245 70.6221 0.976547 1 ]
        [ 205.725 48.3132 0.962265 1 ]
        [ 170.305 60.5831 0.899424 1 ]
        [ 170.305 -13.0362 0.805163 1 ]
        [ 215.845 13.2564 0.939822 1 ]
]
*/
