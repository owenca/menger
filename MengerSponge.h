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

#ifndef MENGER_SPONGE_H
#define MENGER_SPONGE_H


#include <vector>
using namespace std;


struct Cube
{
	float x, y, z;

	Cube(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) { }
};


class MengerSponge
{
public:
			MengerSponge(float cubeSize, int level, bool inverted);

	int		Size()					const { return fCubes.size(); }
	float	CubeSize()				const { return fCubeSize; }
	const	Cube& CubeAt(int index)	const { return fCubes[index]; }

private:
	void	ComputeCubes(const Cube& cube, float cubeSize, int level,
				bool inverted);

	int				fMaxLevel;
	float			fCubeSize;
	vector<Cube>	fCubes;
};


#endif
