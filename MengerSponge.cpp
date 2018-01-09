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

#include "MengerSponge.h"

#include <cstdlib>


MengerSponge::MengerSponge(const Cube& cube, int level, bool inverted)
{
	if (inverted)
		fMaxLevel = 5;
	else if (level == 4)
		fMaxLevel = level;
	else
		fMaxLevel = 3;
	
	ComputeCubes(cube, 0, inverted);
}


void
MengerSponge::ComputeCubes(const Cube& cube, int level, bool inverted)
{
	if (level >= fMaxLevel) {
		fCubes.push_back(cube);
		return;
	}

	vector<Cube> subcubes;
	const float a = cube.a / 3.0;

	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
			for (int k = -1; k < 2; k++) {
				bool test = abs(i) + abs(j) + abs(k) > 1;
				if (inverted)
					test = !test;

				if (test)
					subcubes.push_back(Cube(a, cube.x + a * i, cube.y + a * j,
						cube.z + a * k));
			}

	for (unsigned index = 0; index < subcubes.size(); index++)
		ComputeCubes(subcubes[index], level + 1, inverted);
}
