/****************************************************
 * 2016-2025 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <iostream>
#include "defs.h"
#include "colorandmaterials.h"
#include "framebuffer.h"
#include "utilities.h"
#include "rasterization.h"
#include "io.h"

const int WINDOW_SZ = 500;
FrameBuffer frameBuffer(WINDOW_SZ, WINDOW_SZ);
const int N = 50;

vector<dvec3> triangleVertices = { dvec3(-2 * N,2 * N,1), dvec3(-N,2 * N,1), dvec3(-1.5 * N,3 * N,1) };
vector<dvec3> square1Vertices = { dvec3(-N,-N,1), dvec3(N,-N,1),
											dvec3(N,N,1), dvec3(-N,N,1) };
vector<dvec3> square2Vertices = { dvec3(3 * N,-2 * N,1), dvec3(3 * N,-3 * N,1),
											dvec3(2 * N,-3 * N,1), dvec3(2 * N,-2 * N,1) };

int displayedProblem = 0;

vector<dvec3> transformVertices(const dmat3& transMatrix, const vector<dvec3>& vertices) {
	vector<dvec3> transformedVertices;

	for (size_t i = 0; i < vertices.size(); i++) {
		dvec3 vt(transMatrix * vertices[i]);
		transformedVertices.push_back(vt);
	}

	return transformedVertices;
}

void drawWirePolygonWithShift(vector<dvec3> verts, const color& C) {
	int W2 = frameBuffer.getWindowWidth() / 2;
	int H2 = frameBuffer.getWindowHeight() / 2;
	for (unsigned int i = 0; i < verts.size(); i++) {
		verts[i].x += W2;
		verts[i].y += H2;
	}
	drawWirePolygon(frameBuffer, verts, C);
}

void drawObjectOnly(const vector<dvec3>& verts, bool drawAxis = true) {
	if (drawAxis) {
		drawAxisOnWindow(frameBuffer);
	}
	drawWirePolygonWithShift(verts, black);
}

void drawObjAndOneTransformation(const dmat3& TM, const vector<dvec3>& verts, bool drawAxis = true) {
	vector<dvec3> vertsTransformed = transformVertices(TM, verts);
	if (drawAxis) {
		drawAxisOnWindow(frameBuffer);
	}
	drawWirePolygonWithShift(verts, black);
	drawWirePolygonWithShift(vertsTransformed, red);
}

void drawObjectAndAllTransformations(const dmat3& TM) {
	drawObjAndOneTransformation(TM, triangleVertices, false);
	drawObjAndOneTransformation(TM, square1Vertices, false);
	drawObjAndOneTransformation(TM, square2Vertices, false);
	drawAxisOnWindow(frameBuffer);
}

// Draw all the shapes, transformed by S(2, 0.5)
void doScaleBy2xOneHalf() {
	dmat3 TM = S(2, 0.5);
	drawObjectAndAllTransformations(TM);
}

// Draw all the shapes, transformed by T(50, 50)
void doTranslate50_50() {
	dmat3 TM = T(50,50);
	drawObjectAndAllTransformations(TM);
}

// Draw all the shapes, rotated 45 degrees
void doRotate45Degrees() {
	dmat3 TM = R(deg2rad(45));
	drawObjectAndAllTransformations(TM);
}

// Draw all shapes, reflected across the Y axis
void doReflectAcrossYaxis() {
	dmat3 TM = S(-1, 1);
	drawObjectAndAllTransformations(TM);
}

// Draw all shapes, reflected across the origin
void doReflectAcrossOrigin() {
	dmat3 TM = S(-1, -1);
	drawObjectAndAllTransformations(TM);
}

// Draw all the shapes, first rotations by 45, then scaled by 1.5 in x direction
void doRotateThenScale() {
	dmat3 TM = S(1.5, 1) * R(deg2rad(45));
	drawObjectAndAllTransformations(TM);
}

// Draw all the shapes, first scale by 1.5X in the x direction, then rotation by 45
void doScaleThenRotate() {
	dmat3 TM = R(deg2rad(45)) * S(1.5, 1);
	drawObjectAndAllTransformations(TM);
}

// Draw only triangle, scaled 2X about its center (-1.5*N, 2.5*N)
void doScale2XAboutCenterOfTriangle() {
	dmat3 TM = T(-1.5*N, 2.5*N) * S(2, 2) * T(1.5*N, -2.5*N);
	drawObjAndOneTransformation(TM, triangleVertices);
}

// Draw all shapes, reflected across y=x+50
void doReflectAcrossLineYeqXplus50() {
	dmat3 TM = T(0, 50) * R(deg2rad(45)) * S(1, -1) * R(deg2rad(-45)) * T(0, -50);
	drawObjectAndAllTransformations(TM);
}

// Render square1 so that it rotates about its own axis, and then orbits the origin.
void doSquareRotatingAroundOwnAxisAndAroundSun() {
	static double angleInDegs = 0;
	angleInDegs += 0.25;

	double angleInRads = glm::radians(angleInDegs);
	dmat3 TM = R(angleInRads) * T(2*N, 2*N) * R(2 * angleInRads);
	vector<dvec3> square1VerticesTransformed = transformVertices(TM, square1Vertices);
	drawWirePolygonWithShift(square1VerticesTransformed, red);
	drawAxisOnWindow(frameBuffer);
}

typedef void(*TRANS)();

struct DisplayFunc {
	TRANS func;
	string name;
	DisplayFunc(TRANS t, string n) : func(t), name(n) {}
};

vector<DisplayFunc> funcs = {
								DisplayFunc(doScaleBy2xOneHalf, "0. Scale by 2 and 1/2"),
								DisplayFunc(doTranslate50_50, "1. Trans 50 50"),
								DisplayFunc(doRotate45Degrees, "2. Rotate 45"),
								DisplayFunc(doReflectAcrossYaxis, "3. Reflect across Y"),
								DisplayFunc(doReflectAcrossOrigin, "4. Reflect across origin"),
								DisplayFunc(doRotateThenScale, "5. Rotate 45, then scale (1.5, 1)"),
								DisplayFunc(doScaleThenRotate, "6. Scale (1.5, 1), then Rotate 45"),
								DisplayFunc(doScale2XAboutCenterOfTriangle, "7. Scale 2X about tri center point"),
								DisplayFunc(doReflectAcrossLineYeqXplus50, "8. Reflect across y=x+50"),
								DisplayFunc(doSquareRotatingAroundOwnAxisAndAroundSun, "9. Orbiting planet"),
};

GLFWwindow* window = nullptr;

void render(GLFWwindow* window) {
	if (window != nullptr) {
		glfwSetWindowTitle(window, funcs[displayedProblem].name.c_str());
	}
	frameBuffer.clearColorAndDepthBuffers();
	(*funcs[displayedProblem].func)();				// call the correct function
	frameBuffer.showColorBuffer();
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;

	if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9) {
		displayedProblem = key - GLFW_KEY_0;
	} else if (key == GLFW_KEY_ESCAPE) {
		exit(0);
	}
}

int main(int argc, char* argv[]) {
	for (int i = 0; i <= 9; i++) {
		cout << funcs[i].name << endl;
	}
	frameBuffer.setClearColor(white);
	initGraphics(WINDOW_SZ, WINDOW_SZ, __FILE__, render, nullptr, keyboard, nullptr);

	return 0;
}