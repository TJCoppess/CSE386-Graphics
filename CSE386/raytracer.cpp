/****************************************************
 * 2016-2025 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/
#include "raytracer.h"
#include "ishape.h"
#include "io.h"

 /**
  * @fn	RayTracer::RayTracer(const color &defa)
  * @brief	Constructs a raytracers.
  * @param	defa	The clear color.
  */

RayTracer::RayTracer(const color& defa)
	: defaultColor(defa) {
}

/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 */

void RayTracer::raytraceScene(FrameBuffer& frameBuffer, int depth,
	const IScene& theScene, int N) const {
	const RaytracingCamera& camera = *theScene.camera;

	for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
			DEBUG_PIXEL = (x == xDebug && y == yDebug);
			if (DEBUG_PIXEL) {
				cout << "";
			}

			color sum = black;
			Ray ray = camera.getRay(x, y);

			for (int rayY = 0; rayY < N; rayY++) {
				for (int rayX = 0; rayX < N; rayX++) {
					ray = camera.getRay(static_cast<double>(x) + (rayX + 0.5) / static_cast<double>(N), static_cast<double>(y) + (rayY + 0.5) / static_cast<double>(N));
					sum += traceIndividualRay(ray, theScene, depth, true);
				}
			}

			color finalColor = sum / static_cast<double>(N * N);

			frameBuffer.setColor(x, y, finalColor);
			Ray centerRay = camera.getRay(static_cast<double>(x) + 0.5, static_cast<double>(y) + 0.5);
			frameBuffer.showAxes(x, y, centerRay, 0.25);
		}
	}

	frameBuffer.showColorBuffer();
}

/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray,
 *											const IScene &theScene,
 *											int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 */

color RayTracer::traceIndividualRay(const Ray& ray, const IScene& theScene, int recursionLevel, bool isPrimaryRay) const {
	const vector<VisibleIShapePtr>& opaqueObjs = theScene.opaqueObjs;
	const vector<TransparentIShapePtr>& transparentObjs = theScene.transparentObjs;
	const vector<LightSourcePtr>& lights = theScene.lights;

	dvec3 cameraOrigin = theScene.camera->getFrame().origin;

	OpaqueHitRecord opaqueHit;
	opaqueHit.t = FLT_MAX;
	VisibleIShape::findIntersection(ray, opaqueObjs, opaqueHit);

	TransparentHitRecord transparentHit;
	transparentHit.t = FLT_MAX;
	if (isPrimaryRay) {
		TransparentIShape::findIntersection(ray, transparentObjs, transparentHit);
	}

	color finalColor = defaultColor;

	if (transparentHit.t < opaqueHit.t) {
		color transColor = transparentHit.transColor;
		double alpha = transparentHit.alpha;

		color colorBehind = defaultColor;

		if (opaqueHit.t != FLT_MAX) {
			if (glm::dot(opaqueHit.normal, ray.dir) > 0.0) {
				opaqueHit.normal = -opaqueHit.normal;
			}
			color C = black;

			for (auto light : lights) {
				dvec3 movedPt = IShape::movePointOffSurface(opaqueHit.interceptPt, opaqueHit.normal);
				bool isInShadow = light->pointIsInAShadow(movedPt, opaqueHit.normal, opaqueObjs);
				C += light->illuminate(opaqueHit.interceptPt,
					opaqueHit.normal,
					opaqueHit.material,
					cameraOrigin,
					isInShadow);
			}
			if (opaqueHit.texture != nullptr) {
				color texel = opaqueHit.texture->getPixelUV(opaqueHit.u, opaqueHit.v);
				colorBehind = 0.5 * (texel + C);
			}
			else {
				colorBehind = C;
			}
			if (recursionLevel > 0) {
				color materialSpecular = opaqueHit.material.specular;
				if (glm::length(materialSpecular) > 0.0) {
					dvec3 regularVector = -ray.dir;
					dvec3 reflectionVector = glm::reflect(-regularVector, opaqueHit.normal);
					dvec3 reflectionStartPt = IShape::movePointOffSurface(opaqueHit.interceptPt, opaqueHit.normal);

					Ray reflectionRay(reflectionStartPt, reflectionVector);

					color reflectedColor = traceIndividualRay(reflectionRay, theScene, recursionLevel - 1, false);
					colorBehind += (materialSpecular * reflectedColor);
				}

			}
		}
		finalColor = (transColor * alpha) + (colorBehind * (1.0 - alpha));
	}
	else if (opaqueHit.t != FLT_MAX) {
		if (glm::dot(opaqueHit.normal, ray.dir) > 0.0) {
			opaqueHit.normal = -opaqueHit.normal;
		}
		color C = black;

		for (auto light : lights) {
			dvec3 movedPt = IShape::movePointOffSurface(opaqueHit.interceptPt, opaqueHit.normal);
			bool isInShadow = light->pointIsInAShadow(movedPt, opaqueHit.normal, opaqueObjs);
			C += light->illuminate(
				opaqueHit.interceptPt,
				opaqueHit.normal,
				opaqueHit.material,
				cameraOrigin,
				isInShadow);
		}
		color localColor;
		if (opaqueHit.texture != nullptr) {
			color texel = opaqueHit.texture->getPixelUV(opaqueHit.u, opaqueHit.v);
			localColor = 0.5 * (texel + C);
		}
		else {
			localColor = C;
		}
		if (recursionLevel == 0) {
			return glm::clamp(localColor, 0.0, 1.0);
		}

		color reflectedColor = black;
		color materialSpecular = opaqueHit.material.specular;

		if (glm::length(materialSpecular) > 0.0) {
			dvec3 regularVector = -ray.dir;
			dvec3 reflectionVector = glm::reflect(-regularVector, opaqueHit.normal);

			dvec3 reflectionStartPt = IShape::movePointOffSurface(opaqueHit.interceptPt, opaqueHit.normal);

			Ray reflectionRay(reflectionStartPt, reflectionVector);

			reflectedColor = traceIndividualRay(reflectionRay, theScene, recursionLevel - 1, false);
		}
		finalColor = localColor + (materialSpecular * reflectedColor);
	}
	else {
		finalColor = defaultColor;
	}
	return glm::clamp(finalColor, 0.0, 1.0);
}
