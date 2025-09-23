/****************************************************
 * 2016-2025 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <vector>
#include "defs.h"
#include "utilities.h"
#include "framebuffer.h"
#include "colorandmaterials.h"
#include "rasterization.h"
#include "io.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

void render(GLFWwindow* window) {
	frameBuffer.clearColorBuffer();
	drawLine(frameBuffer, 0, 0, 100, 100, red);
	drawLine(frameBuffer, 100, 100, 200, 100, blue);
	frameBuffer.showColorBuffer();
}

int main(int argc, char* argv[]) {
	// Swap
	cout << "Swap Test Cases" << endl;
	double x = 24.3;
	double y = 99.9;
	double expected_x_after = y;
	double expected_y_after = x;
	cout << "Before: " << x << ' ' << y << endl;
	swap(x, y);
	cout << "After: " << x << ' ' << y << "          Expected: " << expected_x_after << ' ' << expected_y_after << endl;
	x = -5.6;
	y = 7.8;
	expected_x_after = y;
	expected_y_after = x;
	cout << "Before: " << x << ' ' << y << endl;
	swap(x, y);
	cout << "After: " << x << ' ' << y << "          Expected: " << expected_x_after << ' ' << expected_y_after << endl;
	x = 0.0;
	y = 0.0;
	expected_x_after = y;
	expected_y_after = x;
	cout << "Before: " << x << ' ' << y << endl;
	swap(x, y);
	cout << "After: " << x << ' ' << y << "          Expected: " << expected_x_after << ' ' << expected_y_after << endl;
	
	// Approximately Equal
	cout << "Approximately Equal Test Cases" << endl;
	cout << approximatelyEqual(3.0, 3.0) << "          Expected: 1" << endl;
	cout << approximatelyEqual(3.0, 4.0) << "          Expected: 0" << endl;
	cout << approximatelyEqual(3.000000, 3.0000000001) << "          Expected: 1" << endl;
	cout << approximatelyEqual(3.000000, 3.1) << "          Expected: 0" << endl;
	cout << approximatelyEqual(-3.0, -3.0) << "          Expected: 1" << endl;
	cout << approximatelyEqual(-3.0, 3.0) << "          Expected: 0" << endl;
	cout << approximatelyEqual(0.0, 0.0000001) << "          Expected: 1" << endl;
	cout << approximatelyEqual(1e10, 1e10 + 1e-5) << "          Expected: 1" << endl;
	
	// Approximately Zero
	cout << "Approximately Zero Test Cases" << endl;
	cout << approximatelyZero(0.0000001) << "          Expected: 1" << endl;
	cout << approximatelyZero(0.1) << "          Expected: 0" << endl;
	cout << approximatelyZero(-0.0000001) << "          Expected: 1" << endl;
	cout << approximatelyZero(0.0) << "          Expected: 1" << endl;
	cout << approximatelyZero(1e-10) << "          Expected: 1" << endl;
	cout << approximatelyZero(1e-2) << "          Expected: 0" << endl;
	
	// Normalize Degrees
	cout << "Normalize Degrees Test Cases" << endl;
	cout << normalizeDegrees(0) << "          Expected: 0" << endl;
	cout << normalizeDegrees(1.75) << "          Expected: 1.75" << endl;
	cout << normalizeDegrees(-1) << "          Expected: 359" << endl;
	cout << normalizeDegrees(-721) << "          Expected: 359" << endl;
	cout << normalizeDegrees(361) << "          Expected: 1" << endl;
	cout << normalizeDegrees(720) << "          Expected: 0" << endl;
	cout << normalizeDegrees(-360) << "          Expected: 0" << endl;
	cout << normalizeDegrees(450) << "          Expected: 90" << endl;
	
	// Normalize Radians
	cout << "Normalize Radians Test Cases" << endl;
	cout << normalizeRadians(0) << "          Expected: 0" << endl;
	cout << normalizeRadians(1) << "          Expected: 1" << endl;
	cout << normalizeRadians(3 * PI) << "          Expected: " << PI << endl;
	cout << normalizeRadians(-31 * PI) << "          Expected: " << PI << endl;
	cout << normalizeRadians(2 * PI) << "          Expected: 0" << endl;
	cout << normalizeRadians(-2 * PI) << "          Expected: 0" << endl;
	cout << normalizeRadians(PI / 2) << "          Expected: " << PI / 2 << endl;
	cout << normalizeRadians(7 * PI) << "          Expected: " << PI << endl;
	
	// Radians to Degrees
	cout << "Radians to Degrees Test Cases" << endl;
	cout << rad2deg(0.0) << "          Expected: 0.0" << endl;
	cout << rad2deg(PI) << "          Expected: 180.0" << endl;
	cout << rad2deg(2.0 * PI) << "          Expected: 360.0" << endl;
	cout << rad2deg(PI / 2.0) << "          Expected: 90.0" << endl;
	cout << rad2deg(PI / 4.0) << "          Expected: 45.0" << endl;
	cout << rad2deg(3.0 * PI / 2.0) << "          Expected: 270.0" << endl;
	cout << rad2deg(-PI) << "          Expected: -180.0" << endl;
	cout << rad2deg(-PI / 2.0) << "          Expected: -90.0" << endl;
	cout << rad2deg(100.0 * PI) << "          Expected: 18000.0" << endl;
	cout << rad2deg(-100.0 * PI) << "          Expected: -18000.0" << endl;
	cout << rad2deg(1e-9) << "          Expected: 5.72957e-8" << endl;
	cout << rad2deg(-1e-9) << "          Expected: -5.72957e-8" << endl;
	cout << rad2deg(1.0) << "          Expected: 57.2958" << endl;
	cout << rad2deg(10.0) << "          Expected: 572.958" << endl;
	cout << rad2deg(1.2345) << "          Expected: 70.7258" << endl;
	
	// Degrees to Radians
	cout << "Degrees to Radians Test Cases" << endl;
	cout << deg2rad(0.0) << "          Expected: 0.0" << endl;
	cout << deg2rad(180) << "          Expected: " << PI << endl;
	cout << deg2rad(360) << "          Expected: " << 2*PI << endl;
	cout << deg2rad(90) << "          Expected: " << PI / 2 << endl;
	cout << deg2rad(45) << "          Expected: " << PI / 4 << endl;
	cout << deg2rad(270) << "          Expected: " << 3*PI / 2 << endl;
	cout << deg2rad(-180) << "          Expected: " << -PI << endl;
	cout << deg2rad(-90) << "          Expected: " << -PI / 2 << endl;
	cout << deg2rad(18000.0) << "          Expected: " << 100*PI << endl;
	cout << deg2rad(-18000.0) << "          Expected: " << -100*PI << endl;
	cout << deg2rad(1e-8) << "          Expected: 1.74533e-10" << endl;
	cout << deg2rad(-1e-8) << "          Expected: -1.74533e-10" << endl;
	cout << deg2rad(1.0) << "          Expected: 0.0174533" << endl;
	cout << deg2rad(10.0) << "          Expected: 0.174533" << endl;
	cout << deg2rad(70.7258) << "          Expected: 1.2345" << endl;
	
	// Minimum
	cout << "Minimum Test Cases" << endl;
	cout << min(12.2, 3.11, 0.2) << "          Expected: 0.2" << endl;
	cout << min(-1.0, -2.0, -3.0) << "          Expected: -3.0" << endl;
	cout << min(5.5, 5.5, 5.5) << "          Expected: 5.5" << endl;
	cout << min(100.0, 0.0, -100.0) << "          Expected: -100.0" << endl;
	cout << min(1e10, 1e-10, 0.0) << "          Expected: 0" << endl;
	
	// Maximum
	cout << "Maximum Test Cases" << endl;
	cout << max(12.2, 3.11, 0.2) << "          Expected: 12.2" << endl;
	cout << max(-1.0, -2.0, -3.0) << "          Expected: -1.0" << endl;
	cout << max(5.5, 5.5, 5.5) << "          Expected: 5.5" << endl;
	cout << max(100.0, 0.0, -100.0) << "          Expected: 100.0" << endl;
	cout << max(1e10, 1e-10, 0.0) << "          Expected: 1e10" << endl;
	
	// Distance From Origin
	cout << "Distance From Origin Test Cases" << endl;
	cout << distanceFromOrigin(0, 0) << "          Expected: 0.0" << endl;
	cout << distanceFromOrigin(0, 1) << "          Expected: 1.0" << endl;
	cout << distanceFromOrigin(1, 0) << "          Expected: 1.0" << endl;
	cout << distanceFromOrigin(1, 1) << "          Expected: 1.41421" << endl;
	cout << distanceFromOrigin(-10, 30) << "          Expected: 31.6228" << endl;
	cout << distanceFromOrigin(-30, -30) << "          Expected: 42.4264" << endl;

	// Distance Between
	cout << "Distance Between Test Cases" << endl;
	cout << distanceBetween(0, 0, 0, 0) << "          Expected: 0.0" << endl;
	cout << distanceBetween(0, 0, 1, 1) << "          Expected: 1.41421" << endl;
	cout << distanceBetween(1, 1, 0, 0) << "          Expected: 1.41421" << endl;
	cout << distanceBetween(10, 10, 11, 11) << "          Expected: 1.41421" << endl;
	cout << distanceBetween(100, 100, 99, 99) << "          Expected: 1.41421" << endl;
	cout << distanceBetween(54, 1, -34, -99) << "          Expected: 133.207" << endl;

	// Area Of Triangle
	cout << "Area Of 3 Sided Triangle Test Cases" << endl;
	cout << areaOfTriangle(3, 4, 5) << "          Expected: 6.0" << endl;
	cout << areaOfTriangle(-3, 4, 5) << "          Expected: -1.0" << endl;
	cout << areaOfTriangle(3, 4, 50) << "          Expected: -1.0" << endl;
	cout << areaOfTriangle(5, 5, 5) << "          Expected: 10.8253" << endl;
	cout << areaOfTriangle(1, 1, 1) << "          Expected: 0.433013" << endl;
	cout << areaOfTriangle(0, 0, 0) << "          Expected: -1.0" << endl;
	cout << areaOfTriangle(1, 2, 3) << "          Expected: -1.0" << endl;
	cout << "Area Of 6 Vertex Triangle Test Cases" << endl;
	cout << areaOfTriangle(0, 0, 3, 0, 0, 4) << "          Expected: 6.0" << endl;
	cout << areaOfTriangle(0, 0, 1, 0, 0, 1) << "          Expected: 0.5" << endl;
	cout << areaOfTriangle(1, 1, 2, 2, 3, 3) << "          Expected: -1.0" << endl;
	cout << areaOfTriangle(-1, -1, 1, -1, 0, 1) << "          Expected: 2.0" << endl;
	cout << areaOfTriangle(0, 0, 0, 0, 0, 0) << "          Expected: -1.0" << endl;
	cout << areaOfTriangle(5, 5, 10, 5, 7.5, 9) << "          Expected: 10.0" << endl;

	// Point On Unit Circle Test Cases
	cout << "Point On Unit Circle Test Cases" << endl;
	double a, b;
	pointOnUnitCircle(0, a, b);
	cout << "(" << a << ", " << b << ")          Expected: (1.0, 0.0)" << endl;
	pointOnUnitCircle(PI / 2, a, b);
	cout << "(" << a << ", " << b << ")          Expected: (0.0, 1.0)" << endl;
	pointOnUnitCircle(PI, a, b);
	cout << "(" << a << ", " << b << ")          Expected: (-1.0, 0.0)" << endl;
	pointOnUnitCircle(3 * PI / 2, a, b);
	cout << "(" << a << ", " << b << ")          Expected: (0.0, -1.0)" << endl;
	pointOnUnitCircle(PI / 4, a, b);
	cout << "(" << a << ", " << b << ")          Expected: (0.707107, 0.707107)" << endl;
	pointOnUnitCircle(3 * PI / 4, a, b);
	cout << "(" << a << ", " << b << ")          Expected: (-0.707107, 0.707107)" << endl;
	pointOnUnitCircle(5 * PI / 4, a, b);
	cout << "(" << a << ", " << b << ")          Expected: (-0.707107, -0.707107)" << endl;
	pointOnUnitCircle(7 * PI / 4, a, b);
	cout << "(" << a << ", " << b << ")          Expected: (0.707107, -0.707107)" << endl;

	// Point On Circle Test Cases
	cout << "Point On Circle Test Cases" << endl;
	dvec2 result;
	result = pointOnCircle(dvec2(0, 0), 1, 0);
	cout << "(" << result.x << ", " << result.y << ")          Expected: (1.0, 0.0)" << endl;
	result = pointOnCircle(dvec2(0, 0), 1, PI / 2);
	cout << "(" << result.x << ", " << result.y << ")          Expected: (0.0, 1.0)" << endl;
	result = pointOnCircle(dvec2(0, 0), 1, PI);
	cout << "(" << result.x << ", " << result.y << ")          Expected: (-1.0, 0.0)" << endl;
	result = pointOnCircle(dvec2(0, 0), 1, 3 * PI / 2);
	cout << "(" << result.x << ", " << result.y << ")          Expected: (0.0, -1.0)" << endl;
	result = pointOnCircle(dvec2(5, 5), 2, 0);
	cout << "(" << result.x << ", " << result.y << ")          Expected: (7.0, 5.0)" << endl;
	result = pointOnCircle(dvec2(5, 5), 2, PI / 2);
	cout << "(" << result.x << ", " << result.y << ")          Expected: (5.0, 7.0)" << endl;
	result = pointOnCircle(dvec2(-3, 2), 3, PI / 4);
	cout << "(" << result.x << ", " << result.y << ")          Expected: (-0.878679, 4.12132)" << endl;
	result = pointOnCircle(dvec2(0, 0), 5, PI / 6);
	cout << "(" << result.x << ", " << result.y << ")          Expected: (4.33013, 2.5)" << endl;

	// Direction In Radians (dvec2 to dvec2)
	cout << "Direction In Radians (dvec2 to dvec2) Test Cases" << endl;
	cout << directionInRadians(dvec2(0, 0), dvec2(2, 2)) << "          Expected: 0.7853981634" << endl;
	cout << directionInRadians(dvec2(2, 10), dvec2(3, 11)) << "          Expected: 0.7853981634" << endl;
	cout << directionInRadians(dvec2(2, 2), dvec2(2, 0)) << "          Expected: 4.7123889804" << endl;
	cout << directionInRadians(dvec2(1, -1), dvec2(1.3420, -1.93969)) << "          Expected: 5.06144" << endl;
	cout << directionInRadians(dvec2(0, 0), dvec2(1, 0)) << "          Expected: 0.0" << endl;
	cout << directionInRadians(dvec2(0, 0), dvec2(0, 1)) << "          Expected: 1.5708" << endl;
	cout << directionInRadians(dvec2(0, 0), dvec2(-1, 0)) << "          Expected: 3.14159" << endl;
	cout << directionInRadians(dvec2(0, 0), dvec2(0, -1)) << "          Expected: 4.71239" << endl;

	// Direction In Radians (dvec2 from origin)
	cout << "Direction In Radians (dvec2 from origin) Test Cases" << endl;
	cout << directionInRadians(dvec2(2, 2)) << "          Expected: 0.7853981634" << endl;
	cout << directionInRadians(dvec2(0, -2)) << "          Expected: 4.7123889804" << endl;
	cout << directionInRadians(dvec2(1, 0)) << "          Expected: 0.0" << endl;
	cout << directionInRadians(dvec2(0, 1)) << "          Expected: 1.5708" << endl;
	cout << directionInRadians(dvec2(-1, 0)) << "          Expected: 3.14159" << endl;
	cout << directionInRadians(dvec2(-1, -1)) << "          Expected: 3.92699" << endl;

	// Direction In Radians (double coordinates)
	cout << "Direction In Radians (double coordinates) Test Cases" << endl;
	cout << directionInRadians(0, 0, 2, 2) << "          Expected: 0.7853981634" << endl;
	cout << directionInRadians(2, 10, 3, 11) << "          Expected: 0.7853981634" << endl;
	cout << directionInRadians(2, 2, 2, 0) << "          Expected: 4.7123889804" << endl;
	cout << directionInRadians(0, 0, 1, 0) << "          Expected: 0.0" << endl;
	cout << directionInRadians(0, 0, 0, 1) << "          Expected: 1.5708" << endl;
	cout << directionInRadians(0, 0, -1, 0) << "          Expected: 3.14159" << endl;
	cout << directionInRadians(0, 0, 0, -1) << "          Expected: 4.71239" << endl;
	cout << directionInRadians(5, 5, 4, 4) << "          Expected: 3.92699" << endl;

	// Map
	cout << "Map Test Cases" << endl;
	cout << map(2, 0, 5, 10, 11) << " " << 10.4 << endl;

	// Basic mapping
	cout << map(0, 0, 1, 0, 10) << " " << 0 << endl;            // start to start
	cout << map(1, 0, 1, 0, 10) << " " << 10 << endl;           // end to end
	cout << map(0.5, 0, 1, 0, 10) << " " << 5 << endl;          // midpoint

	// Negative and mixed ranges
	cout << map(-5, -10, 0, 0, 100) << " " << 50 << endl;       // mid of negative range
	cout << map(5, -5, 5, -100, 100) << " " << 100 << endl;     // end maps to end
	cout << map(-5, -5, 5, -100, 100) << " " << -100 << endl;   // start maps to start
	cout << map(0, -5, 5, -100, 100) << " " << 0 << endl;       // center maps to center

	// Reversed target range (inversion)
	cout << map(0, 0, 10, 10, 0) << " " << 10 << endl;          // start maps to high
	cout << map(10, 0, 10, 10, 0) << " " << 0 << endl;          // end maps to low
	cout << map(2.5, 0, 10, 10, 0) << " " << 7.5 << endl;       // linear inversion

	// Reversed source range (allowed mathematically, decreasing domain)
	cout << map(0, 10, 0, 0, 10) << " " << 5 << endl;           // mid between reversed domain
	cout << map(10, 10, 0, 0, 10) << " " << 0 << endl;          // start (10) maps to low
	cout << map(0, 10, 0, 0, 10) << " " << 10 << endl;          // end (0) maps to high

	// Out-of-range extrapolation
	cout << map(15, 0, 10, 0, 100) << " " << 150 << endl;       // above high
	cout << map(-5, 0, 10, 0, 100) << " " << -50 << endl;       // below low

	// Degenerate intervals (fromLo == fromHi) — note: your function will divide by zero
	// These are included to highlight undefined behavior; if you later guard, you can validate behavior.
	// cout << map(1, 5, 5, 0, 10) << " " << /* undefined */ 0 << endl;

	// Large values
	cout << map(1e9, 0, 1e9, 0, 1) << " " << 1 << endl;
	cout << map(5e8, 0, 1e9, -1, 1) << " " << 0 << endl;

	// Quadratic (A, B, C) returning vector
	cout << "Quadratic (A, B, C)" << endl;
	cout << quadratic(1, 4, 3) << " " << "[-3, -1]" << endl;
	cout << quadratic(1, 0, 0) << " " << "[0]" << endl;
	cout << quadratic(-4, -2, -1) << " " << "[]" << endl;

	// Two distinct real roots, ordering ascending
	cout << quadratic(1, -3, 2) << " " << "[1, 2]" << endl;         // roots 1 and 2
	cout << quadratic(2, -5, -3) << " " << "[-0.5, 3]" << endl;     // check sort

	// One real root (double root)
	cout << quadratic(1, 2, 1) << " " << "[-1]" << endl;            // (x+1)^2

	// No real roots (positive discriminant check)
	cout << quadratic(1, 0, 1) << " " << "[]" << endl;              // x^2 + 1

	// Edge cases with zeros
	cout << quadratic(0, 2, -4) << " " << "[2]" << endl;            // 2x - 4 = 0 -> x=2 (Note: your implementation assumes quadratic; A=0 becomes linear, discrim calc still works: B^2 - 4AC = 4 - 0 => 2 roots formula divides by 0 if discrim>0. Your current code will divide by 0 if A==0 and discrim>=0.)
	cout << quadratic(0, 0, 5) << " " << "[]" << endl;              // 5 = 0 -> no roots (but your code divides by 0; included to flag behavior)

	// Negative A with two real roots
	cout << quadratic(-1, 0, 1) << " " << "[-1, 1]" << endl;

	// Large coefficients
	cout << quadratic(1e6, -3e6, 2e6) << " " << "[1, 2]" << endl;

	// Quadratic (A, B, C, Roots)
	cout << "Quadratic (A, B, C, Roots)" << endl;
	double ary[2];

	cout << quadratic(1, 4, 3, ary) << " " << 2 << " " << "and fills in ary with : [-3, -1]" << endl;
	cout << quadratic(1, 0, 0, ary) << " " << 1 << " " << "and fills in ary with : [0]     " << endl;
	cout << quadratic(-4, -2, -1, ary) << " " << 0 << " " << "and does not modify ary.        " << endl;

	// Distinct roots and ordering
	int n;
	n = quadratic(1, -3, 2, ary);
	cout << n << " " << 2 << " " << "and fills in ary with : [1, 2]" << endl;

	n = quadratic(2, -5, -3, ary);
	cout << n << " " << 2 << " " << "and fills in ary with : [-0.5, 3]" << endl;

	// Double root
	n = quadratic(1, 2, 1, ary);
	cout << n << " " << 1 << " " << "and fills in ary with : [-1]" << endl;

	// No real roots
	n = quadratic(1, 0, 1, ary);
	cout << n << " " << 0 << " " << "and does not modify ary.        " << endl;

	// A == 0 edge cases (linear or invalid) — your implementation will divide by zero when A==0 and discrim>=0.
	// These are included to highlight current behavior; you may add guards to return 0 or handle linear case.
	// n = quadratic(0, 2, -4, ary); // expected 1 root x=2 if handled as linear
	// n = quadratic(0, 0, 5, ary);  // expected 0 roots (inconsistent equation) if handled

	// Large coefficients
	n = quadratic(1e6, -3e6, 2e6, ary);
	cout << n << " " << 2 << " " << "and fills in ary with : [1, 2]" << endl;

	// Symmetric coefficients
	n = quadratic(-1, 0, 1, ary);
	cout << n << " " << 2 << " " << "and fills in ary with : [-1, 1]" << endl;

	// Not printing these as expected numeric matches, but calling to ensure function behavior under extremes
	// Map with infinities (behavior undefined but included as robustness probes)
	// cout << map(1, 0, 1, -INF, INF) << " " << /* undefined */ 0 << endl;


	// doubleIt Test Cases
	cout << "doubleIt Test Cases" << endl;
	cout << "doubleIt(dvec2(1.0, 2.0)): " << doubleIt(dvec2(1.0, 2.0)).x << ", " << doubleIt(dvec2(1.0, 2.0)).y << "          Expected: 2.0, 4.0" << endl;
	cout << "doubleIt(dvec2(0.0, 0.0)): " << doubleIt(dvec2(0.0, 0.0)).x << ", " << doubleIt(dvec2(0.0, 0.0)).y << "          Expected: 0.0, 0.0" << endl;
	cout << "doubleIt(dvec2(-3.5, 7.2)): " << doubleIt(dvec2(-3.5, 7.2)).x << ", " << doubleIt(dvec2(-3.5, 7.2)).y << "          Expected: -7.0, 14.4" << endl;
	cout << "doubleIt(dvec2(1e-10, -1e10)): " << doubleIt(dvec2(1e-10, -1e10)).x << ", " << doubleIt(dvec2(1e-10, -1e10)).y << "          Expected: 2e-10, -2e10" << endl;
	cout << "doubleIt(dvec2(0.333333, -0.666666)): " << doubleIt(dvec2(0.333333, -0.666666)).x << ", " << doubleIt(dvec2(0.333333, -0.666666)).y << "          Expected: 0.666666, -1.333332" << endl;

	// myNormalize Test Cases
	cout << "myNormalize Test Cases" << endl;
	dvec3 norm1 = myNormalize(dvec3(3.0, 4.0, 0.0));
	cout << "myNormalize(dvec3(3.0, 4.0, 0.0)): " << norm1.x << ", " << norm1.y << ", " << norm1.z << "          Expected: 0.6, 0.8, 0.0" << endl;

	dvec3 norm2 = myNormalize(dvec3(1.0, 0.0, 0.0));
	cout << "myNormalize(dvec3(1.0, 0.0, 0.0)): " << norm2.x << ", " << norm2.y << ", " << norm2.z << "          Expected: 1.0, 0.0, 0.0" << endl;

	dvec3 norm3 = myNormalize(dvec3(1.0, 1.0, 1.0));
	cout << "myNormalize(dvec3(1.0, 1.0, 1.0)): " << norm3.x << ", " << norm3.y << ", " << norm3.z << "          Expected: 0.577350, 0.577350, 0.577350" << endl;

	dvec3 norm4 = myNormalize(dvec3(-2.0, -2.0, -1.0));
	cout << "myNormalize(dvec3(-2.0, -2.0, -1.0)): " << norm4.x << ", " << norm4.y << ", " << norm4.z << "          Expected: -0.666667, -0.666667, -0.333333" << endl;

	dvec3 norm5 = myNormalize(dvec3(1e-10, 1e-10, 1e-10));
	cout << "myNormalize(dvec3(1e-10, 1e-10, 1e-10)): " << norm5.x << ", " << norm5.y << ", " << norm5.z << "          Expected: 0.577350, 0.577350, 0.577350" << endl;

	dvec3 norm6 = myNormalize(dvec3(1e10, 0.0, 0.0));
	cout << "myNormalize(dvec3(1e10, 0.0, 0.0)): " << norm6.x << ", " << norm6.y << ", " << norm6.z << "          Expected: 1.0, 0.0, 0.0" << endl;

	// isOrthogonal Test Cases
	cout << "isOrthogonal Test Cases" << endl;
	cout << "isOrthogonal(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)): " << isOrthogonal(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) << "          Expected: 1 (true)" << endl;
	cout << "isOrthogonal(dvec3(1.0, 1.0, 0.0), dvec3(1.0, -1.0, 0.0)): " << isOrthogonal(dvec3(1.0, 1.0, 0.0), dvec3(1.0, -1.0, 0.0)) << "          Expected: 1 (true)" << endl;
	cout << "isOrthogonal(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)): " << isOrthogonal(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)) << "          Expected: 0 (false)" << endl;
	cout << "isOrthogonal(dvec3(1.0, 2.0, 3.0), dvec3(2.0, -1.0, 0.0)): " << isOrthogonal(dvec3(1.0, 2.0, 3.0), dvec3(2.0, -1.0, 0.0)) << "          Expected: 1 (true)" << endl;
	cout << "isOrthogonal(dvec3(3.0, 4.0, 0.0), dvec3(4.0, -3.0, 0.0)): " << isOrthogonal(dvec3(3.0, 4.0, 0.0), dvec3(4.0, -3.0, 0.0)) << "          Expected: 1 (true)" << endl;
	cout << "isOrthogonal(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 1.0, 1.0)): " << isOrthogonal(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 1.0, 1.0)) << "          Expected: 0 (false)" << endl;
	cout << "isOrthogonal(dvec3(-1.0, 0.0, 0.0), dvec3(0.0, -1.0, 0.0)): " << isOrthogonal(dvec3(-1.0, 0.0, 0.0), dvec3(0.0, -1.0, 0.0)) << "          Expected: 1 (true)" << endl;
	cout << "isOrthogonal(dvec3(1e-10, 1.0, 0.0), dvec3(1.0, -1e-10, 0.0)): " << isOrthogonal(dvec3(1e-10, 1.0, 0.0), dvec3(1.0, -1e-10, 0.0)) << "          Expected: 1 (true)" << endl;

	// formAcuteAngle Test Cases
	cout << "formAcuteAngle Test Cases" << endl;
	cout << "formAcuteAngle(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)): " << formAcuteAngle(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)) << "          Expected: 1 (true)" << endl;
	cout << "formAcuteAngle(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)): " << formAcuteAngle(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) << "          Expected: 0 (false)" << endl;
	cout << "formAcuteAngle(dvec3(1.0, 0.0, 0.0), dvec3(-1.0, 0.0, 0.0)): " << formAcuteAngle(dvec3(1.0, 0.0, 0.0), dvec3(-1.0, 0.0, 0.0)) << "          Expected: 0 (false)" << endl;
	cout << "formAcuteAngle(dvec3(1.0, 1.0, 0.0), dvec3(1.0, 0.0, 0.0)): " << formAcuteAngle(dvec3(1.0, 1.0, 0.0), dvec3(1.0, 0.0, 0.0)) << "          Expected: 1 (true)" << endl;
	cout << "formAcuteAngle(dvec3(1.0, 1.0, 1.0), dvec3(-1.0, -1.0, -1.0)): " << formAcuteAngle(dvec3(1.0, 1.0, 1.0), dvec3(-1.0, -1.0, -1.0)) << "          Expected: 0 (false)" << endl;
	cout << "formAcuteAngle(dvec3(2.0, 3.0, 1.0), dvec3(1.0, 1.0, 1.0)): " << formAcuteAngle(dvec3(2.0, 3.0, 1.0), dvec3(1.0, 1.0, 1.0)) << "          Expected: 1 (true)" << endl;
	cout << "formAcuteAngle(dvec3(-1.0, 2.0, 0.0), dvec3(1.0, 1.0, 0.0)): " << formAcuteAngle(dvec3(-1.0, 2.0, 0.0), dvec3(1.0, 1.0, 0.0)) << "          Expected: 1 (true)" << endl;
	cout << "formAcuteAngle(dvec3(1.0, -1.0, 0.0), dvec3(-1.0, 1.0, 0.0)): " << formAcuteAngle(dvec3(1.0, -1.0, 0.0), dvec3(-1.0, 1.0, 0.0)) << "          Expected: 0 (false)" << endl;

	// cosBetween (dvec2) Test Cases
	cout << "cosBetween (dvec2) Test Cases" << endl;
	cout << "cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 0.0)): " << cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 0.0)) << "          Expected: 1.0" << endl;
	cout << "cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 1.0)): " << cosBetween(dvec2(1.0, 0.0), dvec2(1.0, 1.0)) << "          Expected: 0.707107" << endl;
	cout << "cosBetween(dvec2(-1.0, sqrt(3.0)), dvec2(-1.0, 0.0)): " << cosBetween(dvec2(-1.0, sqrt(3.0)), dvec2(-1.0, 0.0)) << "          Expected: 0.5" << endl;
	cout << "cosBetween(dvec2(-1.0, sqrt(3.0)), dvec2(1.0, sqrt(3.0))): " << cosBetween(dvec2(-1.0, sqrt(3.0)), dvec2(1.0, sqrt(3.0))) << "          Expected: 0.5" << endl;
	cout << "cosBetween(dvec2(1.0, 0.0), dvec2(-1.0, 0.0)): " << cosBetween(dvec2(1.0, 0.0), dvec2(-1.0, 0.0)) << "          Expected: -1.0" << endl;
	cout << "cosBetween(dvec2(0.0, 1.0), dvec2(1.0, 0.0)): " << cosBetween(dvec2(0.0, 1.0), dvec2(1.0, 0.0)) << "          Expected: 0.0" << endl;
	cout << "cosBetween(dvec2(3.0, 4.0), dvec2(4.0, 3.0)): " << cosBetween(dvec2(3.0, 4.0), dvec2(4.0, 3.0)) << "          Expected: 0.96" << endl;
	cout << "cosBetween(dvec2(-2.0, -2.0), dvec2(1.0, 1.0)): " << cosBetween(dvec2(-2.0, -2.0), dvec2(1.0, 1.0)) << "          Expected: -1.0" << endl;

	// cosBetween (dvec3) Test Cases
	cout << "cosBetween (dvec3) Test Cases" << endl;
	cout << "cosBetween(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)): " << cosBetween(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)) << "          Expected: 1.0" << endl;
	cout << "cosBetween(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)): " << cosBetween(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) << "          Expected: 0.0" << endl;
	cout << "cosBetween(dvec3(1.0, 0.0, 0.0), dvec3(-1.0, 0.0, 0.0)): " << cosBetween(dvec3(1.0, 0.0, 0.0), dvec3(-1.0, 0.0, 0.0)) << "          Expected: -1.0" << endl;
	cout << "cosBetween(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 1.0, 1.0)): " << cosBetween(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 1.0, 1.0)) << "          Expected: 1.0" << endl;
	cout << "cosBetween(dvec3(1.0, 1.0, 0.0), dvec3(1.0, 0.0, 1.0)): " << cosBetween(dvec3(1.0, 1.0, 0.0), dvec3(1.0, 0.0, 1.0)) << "          Expected: 0.5" << endl;
	cout << "cosBetween(dvec3(2.0, 3.0, 6.0), dvec3(1.0, 2.0, 3.0)): " << cosBetween(dvec3(2.0, 3.0, 6.0), dvec3(1.0, 2.0, 3.0)) << "          Expected: 0.992685" << endl;
	cout << "cosBetween(dvec3(-1.0, -1.0, -1.0), dvec3(1.0, 1.0, 1.0)): " << cosBetween(dvec3(-1.0, -1.0, -1.0), dvec3(1.0, 1.0, 1.0)) << "          Expected: -1.0" << endl;

	// cosBetween (dvec4) Test Cases
	cout << "cosBetween (dvec4) Test Cases" << endl;
	cout << "cosBetween(dvec4(1.0, 0.0, 0.0, 0.0), dvec4(1.0, 0.0, 0.0, 0.0)): " << cosBetween(dvec4(1.0, 0.0, 0.0, 0.0), dvec4(1.0, 0.0, 0.0, 0.0)) << "          Expected: 1.0" << endl;
	cout << "cosBetween(dvec4(1.0, 0.0, 0.0, 0.0), dvec4(0.0, 1.0, 0.0, 0.0)): " << cosBetween(dvec4(1.0, 0.0, 0.0, 0.0), dvec4(0.0, 1.0, 0.0, 0.0)) << "          Expected: 0.0" << endl;
	cout << "cosBetween(dvec4(1.0, 1.0, 1.0, 1.0), dvec4(1.0, 1.0, 1.0, 1.0)): " << cosBetween(dvec4(1.0, 1.0, 1.0, 1.0), dvec4(1.0, 1.0, 1.0, 1.0)) << "          Expected: 1.0" << endl;
	cout << "cosBetween(dvec4(1.0, 0.0, 0.0, 0.0), dvec4(-1.0, 0.0, 0.0, 0.0)): " << cosBetween(dvec4(1.0, 0.0, 0.0, 0.0), dvec4(-1.0, 0.0, 0.0, 0.0)) << "          Expected: -1.0" << endl;
	cout << "cosBetween(dvec4(1.0, 1.0, 0.0, 0.0), dvec4(1.0, 0.0, 1.0, 0.0)): " << cosBetween(dvec4(1.0, 1.0, 0.0, 0.0), dvec4(1.0, 0.0, 1.0, 0.0)) << "          Expected: 0.5" << endl;
	cout << "cosBetween(dvec4(2.0, 3.0, 1.0, 4.0), dvec4(1.0, 1.0, 1.0, 1.0)): " << cosBetween(dvec4(2.0, 3.0, 1.0, 4.0), dvec4(1.0, 1.0, 1.0, 1.0)) << "          Expected: 0.912871" << endl;
	cout << "cosBetween(dvec4(-1.0, -2.0, -3.0, -4.0), dvec4(1.0, 2.0, 3.0, 4.0)): " << cosBetween(dvec4(-1.0, -2.0, -3.0, -4.0), dvec4(1.0, 2.0, 3.0, 4.0)) << "          Expected: -1.0" << endl;

	// areaOfParallelogram Test Cases
	cout << "areaOfParallelogram Test Cases" << endl;
	cout << "areaOfParallelogram(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)): " << areaOfParallelogram(dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) << "          Expected: 1.0" << endl;
	cout << "areaOfParallelogram(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 0.0, 1.0)): " << areaOfParallelogram(dvec3(1.0, 1.0, 1.0), dvec3(1.0, 0.0, 1.0)) << "          Expected: 1.41421" << endl;
	cout << "areaOfParallelogram(dvec3(2.0, 0.0, 0.0), dvec3(0.0, 3.0, 0.0)): " << areaOfParallelogram(dvec3(2.0, 0.0, 0.0), dvec3(0.0, 3.0, 0.0)) << "          Expected: 6.0" << endl;
	cout << "areaOfParallelogram(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)): " << areaOfParallelogram(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)) << "          Expected: 0.0" << endl;
	cout << "areaOfParallelogram(dvec3(3.0, 4.0, 0.0), dvec3(0.0, 0.0, 5.0)): " << areaOfParallelogram(dvec3(3.0, 4.0, 0.0), dvec3(0.0, 0.0, 5.0)) << "          Expected: 25.0" << endl;
	cout << "areaOfParallelogram(dvec3(-1.0, 2.0, 0.0), dvec3(3.0, 1.0, 0.0)): " << areaOfParallelogram(dvec3(-1.0, 2.0, 0.0), dvec3(3.0, 1.0, 0.0)) << "          Expected: 7.0" << endl;
	cout << "areaOfParallelogram(dvec3(1.0, 2.0, 3.0), dvec3(4.0, 5.0, 6.0)): " << areaOfParallelogram(dvec3(1.0, 2.0, 3.0), dvec3(4.0, 5.0, 6.0)) << "          Expected: 7.34847" << endl;

	// areaOfTriangle Test Cases
	cout << "areaOfTriangle Test Cases" << endl;
	cout << "areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)): " << areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0)) << "          Expected: 0.5" << endl;
	cout << "areaOfTriangle(dvec3(-10.0, -10.0, -10.0), dvec3(-11.0, -10.0, -10.0), dvec3(-10.0, -11.0, -10.0)): " << areaOfTriangle(dvec3(-10.0, -10.0, -10.0), dvec3(-11.0, -10.0, -10.0), dvec3(-10.0, -11.0, -10.0)) << "          Expected: 0.5" << endl;
	cout << "areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(2.0, 0.0, 0.0), dvec3(0.0, 3.0, 0.0)): " << areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(2.0, 0.0, 0.0), dvec3(0.0, 3.0, 0.0)) << "          Expected: 3.0" << endl;
	cout << "areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(0.0, 0.0, 0.0), dvec3(1.0, 1.0, 0.0)): " << areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(0.0, 0.0, 0.0), dvec3(1.0, 1.0, 0.0)) << "          Expected: 0.0" << endl;
	cout << "areaOfTriangle(dvec3(1.0, 1.0, 1.0), dvec3(2.0, 1.0, 1.0), dvec3(1.0, 2.0, 1.0)): " << areaOfTriangle(dvec3(1.0, 1.0, 1.0), dvec3(2.0, 1.0, 1.0), dvec3(1.0, 2.0, 1.0)) << "          Expected: 0.5" << endl;
	cout << "areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(3.0, 4.0, 0.0), dvec3(0.0, 0.0, 5.0)): " << areaOfTriangle(dvec3(0.0, 0.0, 0.0), dvec3(3.0, 4.0, 0.0), dvec3(0.0, 0.0, 5.0)) << "          Expected: 12.5" << endl;
	cout << "areaOfTriangle(dvec3(1.0, 2.0, 3.0), dvec3(4.0, 5.0, 6.0), dvec3(7.0, 8.0, 9.0)): " << areaOfTriangle(dvec3(1.0, 2.0, 3.0), dvec3(4.0, 5.0, 6.0), dvec3(7.0, 8.0, 9.0)) << "          Expected: 0.0" << endl;

	// pointingVector Test Cases
	cout << "pointingVector Test Cases" << endl;
	dvec3 pv1 = pointingVector(dvec3(0.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0));
	cout << "pointingVector(dvec3(0.0, 0.0, 0.0), dvec3(1.0, 0.0, 0.0)): " << pv1.x << ", " << pv1.y << ", " << pv1.z << "          Expected: 1.0, 0.0, 0.0" << endl;

	dvec3 pv2 = pointingVector(dvec3(1.0, 1.0, 1.0), dvec3(2.0, 2.0, 2.0));
	cout << "pointingVector(dvec3(1.0, 1.0, 1.0), dvec3(2.0, 2.0, 2.0)): " << pv2.x << ", " << pv2.y << ", " << pv2.z << "          Expected: 0.577350, 0.577350, 0.577350" << endl;

	dvec3 pv3 = pointingVector(dvec3(0.0, 0.0, 0.0), dvec3(3.0, 4.0, 0.0));
	cout << "pointingVector(dvec3(0.0, 0.0, 0.0), dvec3(3.0, 4.0, 0.0)): " << pv3.x << ", " << pv3.y << ", " << pv3.z << "          Expected: 0.6, 0.8, 0.0" << endl;

	dvec3 pv4 = pointingVector(dvec3(5.0, 3.0, 1.0), dvec3(2.0, 7.0, 1.0));
	cout << "pointingVector(dvec3(5.0, 3.0, 1.0), dvec3(2.0, 7.0, 1.0)): " << pv4.x << ", " << pv4.y << ", " << pv4.z << "          Expected: -0.6, 0.8, 0.0" << endl;

	dvec3 pv5 = pointingVector(dvec3(-1.0, -1.0, -1.0), dvec3(1.0, 1.0, 1.0));
	cout << "pointingVector(dvec3(-1.0, -1.0, -1.0), dvec3(1.0, 1.0, 1.0)): " << pv5.x << ", " << pv5.y << ", " << pv5.z << "          Expected: 0.577350, 0.577350, 0.577350" << endl;

	dvec3 pv6 = pointingVector(dvec3(10.0, 20.0, 30.0), dvec3(10.0, 20.0, 31.0));
	cout << "pointingVector(dvec3(10.0, 20.0, 30.0), dvec3(10.0, 20.0, 31.0)): " << pv6.x << ", " << pv6.y << ", " << pv6.z << "          Expected: 0.0, 0.0, 1.0" << endl;

	dvec3 pv7 = pointingVector(dvec3(0.0, 0.0, 0.0), dvec3(-5.0, 0.0, 0.0));
	cout << "pointingVector(dvec3(0.0, 0.0, 0.0), dvec3(-5.0, 0.0, 0.0)): " << pv7.x << ", " << pv7.y << ", " << pv7.z << "          Expected: -1.0, 0.0, 0.0" << endl;

	return 0;

	frameBuffer.setClearColor(paleGreen);
	initGraphics(WINDOW_WIDTH, WINDOW_HEIGHT, username.c_str(), render, nullptr, keyboardUtility, nullptr);
	return 0;
}