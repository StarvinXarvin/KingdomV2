#pragma once
#include "Engine_Module.h"
#include "Engine_Globals.h"
#include "SDL2/SDL.h"
#include <glm/gtc/type_ptr.hpp>

#include "GL/glew.h"//testing
#include <list>
#include <vector>
#include "Mesh.h"
#include "MeshLoader.h"
#include "GameObject.h"

#include "Primitive.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cone.h"

class Engine_ModuleRenderer3D : public Engine_Module
{
public:
	Engine_ModuleRenderer3D(GameEngine* gEngine, bool start_enabled = true);
	~Engine_ModuleRenderer3D();

	bool Init();
	engine_status PreUpdate();
	engine_status Update();
	engine_status PostUpdate();
	bool CleanUp();

	void OnResize(int width, int height);

	void DrawGrid(int size, int step, bool xzAxis = true, bool xyAxis = false, bool zyAxis = false);

	void SetTargetWindow(SDL_Window* target) {
		targetWindow = target;
	}
	void SetScreenSize(int width, int height) {
		screen_width = width;
		screen_height = height;
	}
	void SetVsync(bool active) {
		vsync = active;
	}

	void SwapDepthTest();
	void SwapCullFace();
	void SwapLighting();
	void SwapColorMaterial();
	void SwapLineSmooth();
	void SwapPolygonSmooth();

public:

	std::vector<vec3> origins, ends, camPos, nearPlanes; //temporary, only debug

	SDL_GLContext context;
	glm::mat3x3 NormalMatrix;
	glm::mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	bool depth_test;
	bool cull_face;
	bool lighting;

	bool line_smooth;

	bool polygon_smooth;

	bool color_material;

	bool debugRayCast;

private:

	SDL_Window* targetWindow;
	bool vsync;
	int screen_width;
	int screen_height;

	void drawQuadFaceTriangles(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
		glVertex3fv(&a.x);
		glVertex3fv(&b.x);
		glVertex3fv(&c.x);

		glVertex3fv(&c.x);
		glVertex3fv(&d.x);
		glVertex3fv(&a.x);
	}
	void drawCubeTest() {
		glm::vec3 a = glm::vec3(-1, -1, 1);
		glm::vec3 b = glm::vec3(1, -1, 1);
		glm::vec3 c = glm::vec3(1, 1, 1);
		glm::vec3 d = glm::vec3(-1, 1, 1);
		glm::vec3 e = glm::vec3(-1, -1, -1);
		glm::vec3 f = glm::vec3(1, -1, -1);
		glm::vec3 g = glm::vec3(1, 1, -1);
		glm::vec3 h = glm::vec3(-1, 1, -1);

		glBegin(GL_TRIANGLES);
		//front
		glColor3f(255, 0, 0);
		drawQuadFaceTriangles(a, b, c, d);
		//back
		glColor3f(0, 255, 0);
		drawQuadFaceTriangles(h, g, f, e);
		//left
		glColor3f(0, 0, 255);
		drawQuadFaceTriangles(e, a, d, h);
		//right
		glColor3f(255, 255, 0);
		drawQuadFaceTriangles(b, f, g, c);
		//top
		glColor3f(255, 255, 255);
		drawQuadFaceTriangles(d, c, g, h);
		//bottom
		glColor3f(0, 0, 0);
		drawQuadFaceTriangles(b, a, e, f);
		glEnd();
	}
	void drawAxis()
	{
		glLineWidth(4.0);
		glBegin(GL_LINES);
		//Red
		glColor3ub(255, 0, 0);
		glVertex3d(0, 0, 0);
		glVertex3d(0.8, 0, 0);
		//Green
		glColor3ub(0, 255, 0);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0.8, 0);
		//Blue
		glColor3ub(0, 0, 255);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, 0.8);
		glEnd();
	}
};