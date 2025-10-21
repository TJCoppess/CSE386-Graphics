/****************************************************
 * 2016-2025 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <chrono>
#include "defs.h"
#include "io.h"
#include "ishape.h"
#include "framebuffer.h"
#include "raytracer.h"
#include "iscene.h"
#include "light.h"
#include "image.h"
#include "camera.h"
#include "rasterization.h"

using namespace std::chrono;

PositionalLightPtr posLight = new PositionalLight(dvec3(10, 10, 10), white);
SpotLightPtr spotLight = new SpotLight(dvec3(2, 5, -2), dvec3(0, -1, 0), PI_4, white);

vector<LightSourcePtr> lights = { posLight, spotLight };

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(paleGreen);

dvec3 cameraPos(0, 5, 10);
dvec3 cameraFocus(0, 5, 0);
dvec3 cameraUp = Y_AXIS;
double cameraFOV = PI_2;

IScene scene;

void render(GLFWwindow* window) {
	milliseconds frameStartTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);

	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();
	frameBuffer.clearColorBuffer();

	scene.camera = new PerspectiveCamera(cameraPos, cameraFocus, cameraUp, cameraFOV, width, height);
	rayTrace.raytraceScene(frameBuffer, 0, scene);
	frameBuffer.showColorBuffer();

	milliseconds frameEndTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);
	milliseconds totalTime = frameEndTime - frameStartTime;
	cout << "Render time: " << totalTime.count() << " ms." << endl;
}

void buildScene() {
	IShape* plane = new IPlane(dvec3(0.0, -2.0, 0.0), dvec3(0.0, 1.0, 0.0));
	ISphere* sphere1 = new ISphere(dvec3(0.0, 0.0, 0.0), 2.0);
	ISphere* sphere2 = new ISphere(dvec3(-2.0, 0.0, -8.0), 2.0);
	IEllipsoid* ellipsoid = new IEllipsoid(dvec3(4.0, 0.0, 3.0), dvec3(2.0, 1.0, 2.0));
	IDisk* disk = new IDisk(dvec3(15.0, 0.0, 0.0), dvec3(0.0, 0.0, 1.0), 5.0);
	IDisk* disk2 = new IDisk(dvec3(-15.0, 0.0, 0.0), dvec3(0.0, 1.0, 0.0), 1.0);

	scene.addOpaqueObject(new VisibleIShape(plane, tin));
	scene.addOpaqueObject(new VisibleIShape(sphere1, silver));
	scene.addOpaqueObject(new VisibleIShape(sphere2, bronze));
	scene.addOpaqueObject(new VisibleIShape(ellipsoid, redPlastic));
	scene.addOpaqueObject(new VisibleIShape(disk, cyanPlastic));
	scene.addOpaqueObject(new VisibleIShape(disk2, bronze));

	scene.addLight(lights[0]);
	//scene.addLight(lights[1]);
	//scene.addLight(lights[2]);
}
int main(int argc, char* argv[]) {
	buildScene();
	frameBuffer.setClearColor(paleGreen);
	initGraphics(WINDOW_WIDTH, WINDOW_HEIGHT, "coppestj -- exerciseraytrace.cpp", render, mouseUtility, keyboardUtility, nullptr);
	return 0;
}