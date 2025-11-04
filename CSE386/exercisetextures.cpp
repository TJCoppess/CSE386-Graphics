/****************************************************
 * 2016-2025 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <utility>
#include <cctype>
#include <ctime>
#include <chrono>

#include "colorandmaterials.h"
#include "framebuffer.h"
#include "iscene.h"
#include "ishape.h"
#include "raytracer.h"
#include "camera.h"
#include "image.h"
#include "io.h"
using namespace std::chrono;

const int W = 400;
const int H = 400;

FrameBuffer frameBuffer(W, H);
Image im("usflag.ppm");

double angle = 0.0;
bool isAnimated = true;

double cameraFOV = PI_2;

IScene theScene;

RayTracer rayTrace(paleGreen);

PositionalLightPtr posLight = new PositionalLight(dvec3(10.0, 15.0, 15.0), white);

void buildScene() {
	IShapePtr cylinder1 = new ICylinderY(dvec3(0, 0, 0), 3.0, 10.0);
	IShapePtr cylinder2 = new ICylinderY(dvec3(6, 0, -8), 2.0, 5.0);
	IShapePtr cylinder3 = new ICylinderY(dvec3(10, 0, 0), 3.0, 5.0);
	IShapePtr disk1 = new IDisk(dvec3(-5, 0, 6), dvec3(0, 0, 1), 3);
	IShapePtr disk2 = new IDisk(dvec3(-9, 0, 5), dvec3(0, 0, 1), 3);

	theScene.addOpaqueObject(new VisibleIShape(cylinder1, gold, &im));
	theScene.addOpaqueObject(new VisibleIShape(cylinder2, brass));
	theScene.addOpaqueObject(new VisibleIShape(cylinder3, gold, &im));
	theScene.addOpaqueObject(new VisibleIShape(disk1, gold, &im));
	theScene.addOpaqueObject(new VisibleIShape(disk2, brass));

	theScene.addLight(posLight);
}
void render(GLFWwindow* window) {
	milliseconds frameStartTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);

	if (isAnimated) {
		angle += 5;
	}

	double R = 12;
	double rads = glm::radians(angle);
	dvec3 cameraPos = dvec3(R * std::cos(-rads), R, R * std::sin(-rads));
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();

	theScene.camera = new PerspectiveCamera(cameraPos, ORIGIN3D, Y_AXIS, cameraFOV, width, height);

	frameBuffer.clearColorBuffer();
	rayTrace.raytraceScene(frameBuffer, 0, theScene);
	frameBuffer.showColorBuffer();

	milliseconds frameEndTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);
	milliseconds totalTime = frameEndTime - frameStartTime;
	cout << "Render time: " << totalTime.count() << " ms." << endl;
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;

	if (key == GLFW_KEY_P) {
		isAnimated = !isAnimated;
	}
}

int main(int argc, char* argv[]) {
	buildScene();
	frameBuffer.setClearColor(paleGreen);
	initGraphics(W, H, username.c_str(), render, mouseUtility, keyboard, nullptr);
	return 0;
}