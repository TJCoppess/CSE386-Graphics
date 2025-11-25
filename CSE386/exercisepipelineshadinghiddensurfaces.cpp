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
#include "io.h"
#include "eshape.h"
#include "light.h"
#include "vertexops.h"

const int W = 600;
const int H = 300;

PositionalLightPtr theLight = new PositionalLight(dvec3(0, 10, 4), white);
vector<LightSourcePtr> lights = { theLight };
FrameBuffer frameBuffer(W, H);

PipelineMatrices pipeMats;
dmat4& viewingMatrix = pipeMats.viewingMatrix;
dmat4& projectionMatrix = pipeMats.projectionMatrix;
dmat4& viewportMatrix = pipeMats.viewportMatrix;

EShapeData board = EShape::createECheckerBoard(copper, polishedCopper, 10, 10, 10);
dvec4 A(-1, -1, 0, 1);
dvec4 B(+1, -1, 0, 1);
dvec4 C(0, +1, 0, 1);
EShapeData tri1 = EShape::createETriangle(gold, A, B, C);
EShapeData tri2 = EShape::createETriangle(polishedCopper, A, B, C);
EShapeData tri3 = EShape::createETriangle(cyanPlastic, A, B, C);
EShapeData cone = EShape::createECone(pewter, 8);

void renderObjects() {
	// The rendering should work regardless of the order in which
	// the objects are rendered.
	VertexOps::render(frameBuffer, board, lights, glm::dmat4(), pipeMats, true);
	VertexOps::render(frameBuffer, tri1, lights, T(0, 2, 0) * S(5, 2, 1), pipeMats, true);
	VertexOps::render(frameBuffer, tri2, lights, T(-1, 0, 0) * Ry(-PI_3) * S(10, 3, 1), pipeMats, true);
	VertexOps::render(frameBuffer, tri3, lights, T(0, 1, 0) * S(8, 1, 1) * Ry(PI_4) * Rz(PI_2), pipeMats, true);
	VertexOps::render(frameBuffer, cone, lights, T(-3, 0, 3), pipeMats, true);
}

void render(GLFWwindow* window) {
	frameBuffer.clearColorAndDepthBuffers();
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();

	double AR = (double)width / height;

	viewingMatrix = glm::lookAt(glm::dvec3(0, 5, 5), glm::dvec3(0, 0, 0), Y_AXIS);
	projectionMatrix = glm::perspective(PI_3, AR, 0.5, 80.0);
	viewportMatrix = VertexOps::getViewportTransformation(0, width, 0, height);

	renderObjects();
	frameBuffer.showAxes(viewingMatrix, projectionMatrix, viewportMatrix,
		BoundingBoxi(0, width, 0, height));
	frameBuffer.showColorBuffer();
}

int main(int argc, char* argv[]) {
	frameBuffer.setClearColor(paleGreen);
	initGraphics(W, H, username.c_str(), render, nullptr, keyboardUtility, nullptr);

	return 0;
}
