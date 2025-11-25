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
#include <vector>
#include "eshape.h"
#include "io.h"
#include "light.h"
#include "vertexops.h"

const int W = 500;
const int H = 250;

PositionalLightPtr theLight = new PositionalLight(dvec3(0, 4, 0), white);
vector<LightSourcePtr> lights = { theLight };

PipelineMatrices pipeMats;
dmat4& viewingMatrix = pipeMats.viewingMatrix;
dmat4& projectionMatrix = pipeMats.projectionMatrix;
dmat4& viewportMatrix = pipeMats.viewportMatrix;

dvec3 position(0, 1, 5);
double angle = 0;
bool isMoving = true;
const double SPEED = 0.1;

FrameBuffer frameBuffer(W, H);

color brown(0.59, 0.29, 0.0);
color darkBrown = 0.7 * brown;
Material Y(yellow, yellow, yellow, 1.0);
Material G(green, green, green, 1.0);
Material B(brown, brown, brown, 1.0);
Material DB(darkBrown, darkBrown, darkBrown, 1.0);
Material LG(lightGray, lightGray, lightGray, 1.0);
Material C(cyan, cyan, cyan, 1.0);

EShapeData plane = EShape::createECheckerBoard(B, DB, 5, 5, 10);
EShapeData cone1 = EShape::createECone(Y, DEFAULT_SLICES);
EShapeData cone2 = EShape::createECone(Y, DEFAULT_SLICES);
EShapeData disk = EShape::createEDisk(G, DEFAULT_SLICES);
EShapeData cyl1 = EShape::createECylinder(LG, DEFAULT_SLICES);
EShapeData cyl2 = EShape::createECylinder(LG, DEFAULT_SLICES);
EShapeData tri = EShape::createETriangle(C,
				dvec4(0, 0, 0, 1), dvec4(1, 0, 0, 1), dvec4(1, 1, 0, 1));
//EShapeData mario = EShape::createEObj("mario.obj");
//EShapeData teapot = EShape::createEObj("teapot.obj");

void renderObjects() {
	VertexOps::render(frameBuffer, plane, lights, dmat4(), pipeMats, true);
	VertexOps::render(frameBuffer, cone1, lights, T(-1, 2, 0) * Rx(angle) * S(0.25), pipeMats, true);
	VertexOps::render(frameBuffer, cone2, lights, Ry(angle) * T(2, 1, 0) * Rx(angle), pipeMats, true);
	VertexOps::render(frameBuffer, disk, lights, T(0, 1, 0) * Ry(angle) * S(0.5), pipeMats, true);
	VertexOps::render(frameBuffer, cyl1, lights, T(2, 0, 0), pipeMats, true);
	VertexOps::render(frameBuffer, cyl2, lights, T(-2, 1, 0) * Rx(PI_2), pipeMats, true);
	VertexOps::render(frameBuffer, tri, lights, T(0, 2, 0) * Rx(angle), pipeMats, true);
	//VertexOps::render(frameBuffer, mario, lights, T(0, 0, 0) * Ry(angle) * S(0.01), pipeMats, true);
	//VertexOps::render(frameBuffer, teapot, lights, T(0, -1, 0), pipeMats, true);
}

static void render(GLFWwindow* window) {
	if (isMoving) {
		angle += glm::radians(5.0);
	}

	frameBuffer.clearColorAndDepthBuffers();
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();
	viewingMatrix = glm::lookAt(position, ORIGIN3D, Y_AXIS);
	double AR = (double)width / height;
	projectionMatrix = glm::perspective(PI_3, AR, 0.5, 80.0);
	viewportMatrix = VertexOps::getViewportTransformation(0, width, 0, height);
	renderObjects();
	frameBuffer.showAxes(viewingMatrix, projectionMatrix, viewportMatrix,
		BoundingBoxi(0, width, 0, height));
	frameBuffer.showColorBuffer();
}
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;

	switch (key) {
		case GLFW_KEY_P:
			isMoving = !isMoving;
			break;
		case GLFW_KEY_ESCAPE:
			exit(0);
	}
}

int main(int argc, char* argv[]) {
	frameBuffer.setClearColor(paleGreen);
	initGraphics(W, H, "coppestj", render, mouseUtility, keyboard, nullptr);
	return 0;
}