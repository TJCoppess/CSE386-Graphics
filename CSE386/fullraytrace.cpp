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

Image im1("usflag.ppm");

int currLight = 0;
double angle = 0.5;
const int MINZ = -10;
const int MAXZ = 4;
double z = MINZ;
double inc = 0.8;
bool isAnimated = false;
int numReflections = 0;
int antiAliasing = 1;
bool multiViewOn = false;
double spotDirX = 0;
double spotDirY = -1;
double spotDirZ = 0;

dvec3 cameraPos(6, 6, 6);
dvec3 cameraFocus = ORIGIN3D;
dvec3 cameraUp = Y_AXIS;

double cameraFOV = glm::radians(120.0);

vector<PositionalLightPtr> lights = {
						new PositionalLight(dvec3(15, 15, 15), white),
						new SpotLight(dvec3(-15, 5, 10),
										dvec3(spotDirX,spotDirY,spotDirZ),
										glm::radians(90.0),
										white)
};

const int W = 600;
const int H = 400;

PositionalLightPtr posLight = lights[0];
SpotLightPtr spotLight = (SpotLightPtr)lights[1];

FrameBuffer frameBuffer(W, H);

RayTracer rayTrace(paleGreen);
IScene scene;

IPlane* plane = new IPlane(dvec3(0.0, -2.0, 0.0), dvec3(0.0, 1.0, 0.0));
IPlane* clearPlane = new IPlane(dvec3(0.0, 0.0, MINZ), dvec3(0.0, 0.0, 1.0));
ISphere* sphere1 = new ISphere(dvec3(0.0, 0.0, 0.0), 4.0);
IEllipsoid* ellipsoid = new IEllipsoid(dvec3(4, 0, 5), dvec3(1, 1, 2.5));
ICylinderY* cylinderY = new ICylinderY(dvec3(8.0, 3.0, -2.0), 1.5, 3.0);
IDisk* disk = new IDisk(dvec3(-8, 0, 10), dvec3(1, 0, 0), 3);

void buildScene() {
	scene.addOpaqueObject(new VisibleIShape(plane, tin));
	scene.addTransparentObject(new TransparentIShape(clearPlane, red, 0.25));

	scene.addOpaqueObject(new VisibleIShape(sphere1, silver));
	scene.addOpaqueObject(new VisibleIShape(ellipsoid, copper));

	scene.addOpaqueObject(new VisibleIShape(cylinderY, gold, &im1));
	scene.addOpaqueObject(new VisibleIShape(disk, redPlastic));

	// scene.addOpaqueObject(new VisibleIShape(new IPlane(dvec3(0, 0, 0), dvec3(0, 1, 0)), tin));
	// scene.addOpaqueObject(new VisibleIShape(new IPlane(dvec3(0, 0, 0), dvec3(0, -1, 0)), tin));

	// scene.addLight(lights[0]);
	scene.addLight(lights[1]);
	lights[1]->isOn = true;
}
void render(GLFWwindow* window) {
	if (isAnimated) {
		z += inc;
		if (z <= MINZ) {
			inc = -inc;
		}
		else if (z >= MAXZ) {
			inc = -inc;
		}
	}

	clearPlane->a = dvec3(0, 0, z);

	milliseconds frameStartTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);

	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();
	frameBuffer.clearColorBuffer();


	int left = 0;
	int right = frameBuffer.getWindowWidth() - 1;
	int bottom = 0;
	int top = frameBuffer.getWindowHeight() - 1;
	double N = 6.0;
	scene.camera = new PerspectiveCamera(cameraPos, cameraFocus, cameraUp, cameraFOV, width, height);
	cout << clearPlane->a << endl;
	rayTrace.raytraceScene(frameBuffer, numReflections, scene);

	frameBuffer.showColorBuffer();
	milliseconds frameEndTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);

	milliseconds totalTime = frameEndTime - frameStartTime;
	cout << "Render time: " << totalTime.count() << " ms." << endl;
	if (isAnimated) {
		cout << "Transparent plane's z value: " << clearPlane->a.z << endl;
	}
}
void incrementClamp(double& v, double delta, double lo, double hi) {
	v = glm::clamp(v + delta, lo, hi);
}

void incrementClamp(int& v, int delta, int lo, int hi) {
	v = glm::clamp(v + delta, lo, hi);
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;

	bool isUpperCase = (mods & GLFW_MOD_SHIFT) != 0;

	const double INC = 0.5;
	switch (key) {
	case GLFW_KEY_A:	
		currLight = 0;
		cout << *lights[0] << endl;
		break;
	case GLFW_KEY_B:
		currLight = 1;
		cout << *lights[1] << endl;
		break;
	case GLFW_KEY_O:
		lights[currLight]->isOn = !lights[currLight]->isOn;
		cout << (lights[currLight]->isOn ? "ON" : "OFF") << endl;
		break;
	case GLFW_KEY_X:
		lights[currLight]->pos.x += (isUpperCase ? INC : -INC);
		cout << lights[currLight]->pos << endl;
		break;
	case GLFW_KEY_Y:
		lights[currLight]->pos.y += (isUpperCase ? INC : -INC);
		cout << lights[currLight]->pos << endl;
		break;
	case GLFW_KEY_Z:
		lights[currLight]->pos.z += (isUpperCase ? INC : -INC);
		cout << lights[currLight]->pos << endl;
		break;
	case GLFW_KEY_J:
		spotDirX += (isUpperCase ? INC : -INC);
		spotLight->setDir(spotDirX, spotDirY, spotDirZ);
		cout << spotLight->spotDir << endl;
		break;
	case GLFW_KEY_K:
		spotDirY += (isUpperCase ? INC : -INC);
		spotLight->setDir(spotDirX, spotDirY, spotDirZ);
		cout << spotLight->spotDir << endl;
		break;
	case GLFW_KEY_L:
		spotDirZ += (isUpperCase ? INC : -INC);
		spotLight->setDir(spotDirX, spotDirY, spotDirZ);
		cout << spotLight->spotDir << endl;
		break;
	case GLFW_KEY_F:
		incrementClamp(spotLight->fov, isUpperCase ? 0.2 : -0.2, 0.1, PI);
		cout << spotLight->fov << endl;
		break;
	case GLFW_KEY_EQUAL:	
		if (isUpperCase)
			antiAliasing = 3;
		cout << "Anti aliasing: " << antiAliasing << endl;
		break;
	case GLFW_KEY_MINUS:	
		antiAliasing = 1;
		cout << "Anti aliasing: " << antiAliasing << endl;
		break;
	case GLFW_KEY_P:
		isAnimated = !isAnimated;
		cout << "Animation: " << (isAnimated ? "on" : "off") << endl;
		break;
	case GLFW_KEY_0:
	case GLFW_KEY_1:
	case GLFW_KEY_2:
		numReflections = key - '0';
		cout << "Num reflections: " << numReflections << endl;
		break;
	case GLFW_KEY_ESCAPE:
		exit(0);
		break;
	default:
		cout << (int)key << "unmapped key pressed." << endl;
	}
}
int main(int argc, char* argv[]) {
	buildScene();
	initGraphics(W, H, username.c_str(), render, mouseUtility, keyboard, nullptr);
	return 0;
}