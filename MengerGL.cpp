/*
 * MIT License
 *
 * Copyright (c) 2018 Owen Pan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "MengerGL.h"

#include <cstdlib>

#include <GL/glu.h>

#include "MengerSponge.h"


static const Cube cube;
static const MengerSponge mengerSponge(cube, 3, false);
static const MengerSponge invertedSponge(cube, 5, true);


static void
Rotate(int angle, int order)
{
	switch (order) {
		case 0:
			glRotatef(angle, 1, 0, 0);
			glRotatef(angle, 0, 1, 0);
			glRotatef(angle, 0, 0, 1);
			break;
		case 1:
			glRotatef(angle, 1, 0, 0);
			glRotatef(angle, 0, 0, 1);
			glRotatef(angle, 0, 1, 0);
			break;
		case 2:
			glRotatef(angle, 0, 1, 0);
			glRotatef(angle, 1, 0, 0);
			glRotatef(angle, 0, 0, 1);
			break;
		case 3:
			glRotatef(angle, 0, 1, 0);
			glRotatef(angle, 0, 0, 1);
			glRotatef(angle, 1, 0, 0);
			break;
		case 4:
			glRotatef(angle, 0, 0, 1);
			glRotatef(angle, 1, 0, 0);
			glRotatef(angle, 0, 1, 0);
			break;
		default:
			glRotatef(angle, 0, 0, 1);
			glRotatef(angle, 0, 1, 0);
			glRotatef(angle, 1, 0, 0);
			break;
	}
}


static void
DrawCube(const Cube& cube)
{
	const float d = cube.a / 2.0;
	const float x = cube.x;
	const float y = cube.y;
	const float z = cube.z;

	glPushMatrix();
	glBegin(GL_QUADS);

	// -x-axis
	glColor3f(1, 1, 1);	// white
	glVertex3f(x - d, y + d, z + d);
	glVertex3f(x - d, y + d, z - d);
	glVertex3f(x - d, y - d, z - d);
	glVertex3f(x - d, y - d, z + d);

	// +x-axis
	glColor3f(0, 1, 0);	// green
	glVertex3f(x + d, y + d, z + d);
	glVertex3f(x + d, y + d, z - d);
	glVertex3f(x + d, y - d, z - d);
	glVertex3f(x + d, y - d, z + d);

	// -y-axis
	glColor3f(1, 0, 0);	// red
	glVertex3f(x + d, y - d, z + d);
	glVertex3f(x + d, y - d, z - d);
	glVertex3f(x - d, y - d, z - d);
	glVertex3f(x - d, y - d, z + d);

	// +y-axis
	glColor3f(1, 0, 1);	// magenta
	glVertex3f(x + d, y + d, z + d);
	glVertex3f(x + d, y + d, z - d);
	glVertex3f(x - d, y + d, z - d);
	glVertex3f(x - d, y + d, z + d);

	// -z-axis
	glColor3f(0, 1, 1);	// cyan
	glVertex3f(x + d, y + d, z - d);
	glVertex3f(x + d, y - d, z - d);
	glVertex3f(x - d, y - d, z - d);
	glVertex3f(x - d, y + d, z - d);

	// +z-axis
	glColor3f(1, 1, 0);	// yellow
	glVertex3f(x + d, y + d, z + d);
	glVertex3f(x + d, y - d, z + d);
	glVertex3f(x - d, y - d, z + d);
	glVertex3f(x - d, y + d, z + d);

	glEnd();
	glPopMatrix();
}


void
Restart()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 100);
}


void
Display()
{
	static int angle = 0;
	static int order = 0;
	static int min = 15;
	static int max = 55;
	static float d = max;
	static float delta = -0.2;
	static bool inverted = false;
	static const MengerSponge* sponge = &mengerSponge;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(d, d, d, 0, 0, 0, 0, 1, 0);

	if (d < min || d > max) {
		delta = -delta;
		order = random() % 6;

		if (d > max) {
			min = inverted ? 15 : 10;
			inverted = !inverted;
			sponge = inverted ? &invertedSponge : &mengerSponge;
		}
	}
	d += delta;

	angle += 5;
	Rotate(angle, order);

	for (int index = 0; index < sponge->Size(); index++)
		DrawCube(sponge->CubeAt(index));
}
