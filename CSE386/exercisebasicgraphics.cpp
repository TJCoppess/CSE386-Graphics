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
	cout << areaOfTriangle(1, 1, 2, 2, 3, 3) << "          Expected: 0.0" << endl;
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

	return 0;

	frameBuffer.setClearColor(paleGreen);
	initGraphics(WINDOW_WIDTH, WINDOW_HEIGHT, username.c_str(), render, nullptr, keyboardUtility, nullptr);
	return 0;
}