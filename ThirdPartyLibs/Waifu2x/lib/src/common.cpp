/*
* The MIT License (MIT)
* Copyright (c) 2015 amigo(white luckers), tanakamura, DeadSix27, YukihoAA and contributors
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "common.hpp"
#include <math.h>
#include <stdint.h>
#ifdef _WIN32
#if _MSC_VER>=1900
#include <algorithm>
#endif
#include <windows.h>
#else
#include <sys/stat.h>
#endif

namespace w2xc
{

void pack_mat(float *out, std::vector<W2Mat> &inputPlanes, int w, int h, int nplane)
{
	for (int i=0; i<nplane; i++)
	{
		for (int yi=0; yi<h; yi++)
		{
			const float *mat_line = inputPlanes[i].ptr<float>(yi);
			float *packed_line = out + i + (yi * nplane * w);

			for (int xi=0; xi<w; xi++)
			{
				packed_line[xi*nplane] = mat_line[xi];
			}
		}
	}
}

void pack_mat_bgr(float *out, W2Mat &inputPlane, int w, int h)
{
#pragma omp parallel for
	for (int yi=0; yi<h; yi++)
	{
		const unsigned char *mat_line = inputPlane.ptr<unsigned char>(yi);
		float *packed_line = out + (yi * 3 * w);

		for (int xi=0; xi<w; xi++)
		{
			packed_line[xi*3 + 0] = mat_line[xi*3 + 2] * (1.0f/255.0f);
			packed_line[xi*3 + 1] = mat_line[xi*3 + 1] * (1.0f/255.0f);
			packed_line[xi*3 + 2] = mat_line[xi*3 + 0] * (1.0f/255.0f);
		}
	}
}
void
pack_mat_rgb(float *out, W2Mat &inputPlane, int w, int h)
{
#pragma omp parallel for
	for (int yi=0; yi<h; yi++)
	{
		const unsigned char *mat_line = inputPlane.ptr<unsigned char>(yi);
		float *packed_line = out + (yi * 3 * w);

		for (int xi=0; xi<w; xi++)
		{
			packed_line[xi*3 + 0] = mat_line[xi*3 + 0] * (1.0f/255.0f);
			packed_line[xi*3 + 1] = mat_line[xi*3 + 1] * (1.0f/255.0f);
			packed_line[xi*3 + 2] = mat_line[xi*3 + 2] * (1.0f/255.0f);
		}
	}
}

void
pack_mat_rgb_f32(float *out, W2Mat &inputPlane, int w, int h)
{
#pragma omp parallel for
	for (int yi=0; yi<h; yi++)
	{
		const float *mat_line = inputPlane.ptr<float>(yi);
		float *packed_line = out + (yi * 3 * w);

		for (int xi=0; xi<w; xi++)
		{
			packed_line[xi*3 + 0] = mat_line[xi*3 + 0];
			packed_line[xi*3 + 1] = mat_line[xi*3 + 1];
			packed_line[xi*3 + 2] = mat_line[xi*3 + 2];
		}
	}
}


void unpack_mat(std::vector<W2Mat> &outputPlanes, const float *in, int w, int h, int nplane)
{
	for (int i=0; i<nplane; i++)
	{
		for (int yi=0; yi<h; yi++)
		{
			float *mat_line = outputPlanes[i].ptr<float>(yi);
			const float *packed_line = in + i + (yi * nplane * w);

			for (int xi=0; xi<w; xi++)
			{
				mat_line[xi] = packed_line[xi*nplane];
			}
		}
	}
}

void unpack_mat1(W2Mat &outputMat, const float *in, int w, int h)
{
#pragma omp parallel for
	for (int yi=0; yi<h; yi++)
	{
		float *mat_line = outputMat.ptr<float>(yi);
		const float *packed_line = in + (yi * w);

		for (int xi=0; xi<w; xi++)
		{
			mat_line[xi] = packed_line[xi];
		}
	}
}


void unpack_mat_bgr(W2Mat &outputMat, const float *in, int w, int h)
{
#pragma omp parallel for
	for (int yi=0; yi<h; yi++)
	{
		unsigned char *mat_line = outputMat.ptr<unsigned char>(yi);
		const float *packed_line = in + (yi * w * 3);

		for (int xi=0; xi<w; xi++)
		{
			mat_line[xi*3 + 2] = (unsigned char)(std::max)(0.0f, (std::min)(255.0f, roundf(packed_line[xi*3 + 0] * 255.0f)));
			mat_line[xi*3 + 1] = (unsigned char)(std::max)(0.0f, (std::min)(255.0f, roundf(packed_line[xi*3 + 1] * 255.0f)));
			mat_line[xi*3 + 0] = (unsigned char)(std::max)(0.0f, (std::min)(255.0f, roundf(packed_line[xi*3 + 2] * 255.0f)));
		}
	}
}

void unpack_mat_rgb(W2Mat &outputMat, const float *in, int w, int h)
{
#pragma omp parallel for
	for (int yi=0; yi<h; yi++)
	{
		unsigned char *mat_line = outputMat.ptr<unsigned char>(yi);
		const float *packed_line = in + (yi * w * 3);

		for (int xi=0; xi<w; xi++)
		{
			mat_line[xi*3 + 0] = (unsigned char)(std::max)(0.0f, (std::min)(255.0f, roundf(packed_line[xi*3 + 0] * 255.0f)));
			mat_line[xi*3 + 1] = (unsigned char)(std::max)(0.0f, (std::min)(255.0f, roundf(packed_line[xi*3 + 1] * 255.0f)));
			mat_line[xi*3 + 2] = (unsigned char)(std::max)(0.0f, (std::min)(255.0f, roundf(packed_line[xi*3 + 2] * 255.0f)));
		}
	}
}

void unpack_mat_rgb_f32(W2Mat &outputMat, const float *in, int w, int h)
{
#pragma omp parallel for
	for (int yi=0; yi<h; yi++)
	{
		float *mat_line = outputMat.ptr<float>(yi);
		const float *packed_line = in + (yi * w * 3);

		for (int xi=0; xi<w; xi++)
		{
			mat_line[xi*3 + 0] = (std::max)(0.0f, (std::min)(1.0f, packed_line[xi*3 + 0]));
			mat_line[xi*3 + 1] = (std::max)(0.0f, (std::min)(1.0f, packed_line[xi*3 + 1]));
			mat_line[xi*3 + 2] = (std::max)(0.0f, (std::min)(1.0f, packed_line[xi*3 + 2]));
		}
	}
}

}