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

#include "MengerSaver.h"

#include <private/screen_saver/DefaultSettingsView.h>


void
MengerSaver::StartConfig(BView *view)
{
	BPrivate::BuildDefaultSettingsView(view, "Menger Sponge and Its Complement",
		B_UTF8_COPYRIGHT " 2018 Owen Pan");
}


status_t
MengerSaver::StartSaver(BView* view, bool preview)
{
	fMengerView = new MengerView(view->Bounds(), B_FOLLOW_NONE,
		BGL_RGB | BGL_DEPTH | BGL_DOUBLE);
	view->AddChild(fMengerView);
	return B_OK;
}


void
MengerSaver::StopSaver()
{
	if (fMengerView != NULL)
		fMengerView->EnableDirectMode(false);
}


void
MengerSaver::DirectConnected(direct_buffer_info* info)
{
	if (fMengerView != NULL) {
		fMengerView->DirectConnected(info);
		fMengerView->EnableDirectMode(true);
	}
}


extern "C" _EXPORT BScreenSaver*
instantiate_screen_saver(BMessage* msg, image_id id)
{
	return new MengerSaver(msg, id);
}
