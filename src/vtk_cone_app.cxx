// ============================================================================
//
// File:        vtk_cone_app.cpp
// Description: Main application file for the VTK Cone Tutorial App
//
// This file is part of `C++ Playground'
//
// Copyright (C) 2025 Ljubomir Kurij <ljubomir_kurij@proton.me>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// This file incorporates code from Visualization Toolkit,
// Copyright (c) 1993-2015 Ken Martin, Will Schroeder, Bill Lorensen
// All rights reserved.
// Licensed under the BSD 3-Clause License.
// See vtkCopyright.txt or https://gitlab.kitware.com/vtk/vtk for details.
// 
// ============================================================================

// ============================================================================
//
// 2025-11-11 Ljubomir Kurij <ljubomir_kurij@proton.me>
//
// * vtk_cone_app.cpp: created.
//
// ============================================================================


// ============================================================================
// Headers Include Section
// ============================================================================

// Project library headers

// Standard library headers
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>

#include <emscripten.h>
#define DEBUG_LOG(msg) EM_ASM({ console.log(UTF8ToString($0)); }, msg)

// VTK library headers
#include <vtkActor.h>
#include <vtkBoxWidget.h>
#include <vtkCamera.h>
#include <vtkCommand.h>
#include <vtkConeSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTransform.h>

namespace {
	enum class Viewport
	{
		Left,
		Right
	};

	class vtkOnLeftMouseClick: public vtkCommand
	{
	public:
		static vtkOnLeftMouseClick* New()
		{
			return new vtkOnLeftMouseClick;
		}

		void Execute(vtkObject* caller, unsigned long, void*) override
		{
			auto windowInteractor
				= reinterpret_cast<vtkRenderWindowInteractor*> (caller);
			int xPos{0}, yPos{0}, xSize{0}, ySize{0};
			windowInteractor->GetEventPosition(xPos, yPos);
			windowInteractor->GetSize(xSize, ySize);

			auto ClickedViewport = [](const int& xSize, const int& xPos)
				-> Viewport
			{
				const int leftViewportExtent{xSize / 2};
				return leftViewportExtent < xPos
					? Viewport::Right : Viewport::Left;
			};

			auto ViewportStyle = [&viewportStyle = this->_viewportStyle](
				const Viewport viewport
			) -> vtkInteractorStyle*
			{
				if (0 != viewportStyle.count(viewport))
				{
					return const_cast<vtkInteractorStyle*> (
						viewportStyle[viewport]
					);
				}
				else
				{
					return nullptr;
				}
			};

			auto SetInteractorStyle = [](
				vtkRenderWindowInteractor* interactor,
				vtkInteractorStyle* style
			) -> void
			{
				if (style)
				{
					interactor->SetInteractorStyle(style);
				}
			};

			SetInteractorStyle(
				windowInteractor,
				ViewportStyle(ClickedViewport(xSize, xPos))
			);
		}

		vtkOnLeftMouseClick() = default;

		void addViewportInteractorStyle(
			Viewport viewport,
			vtkInteractorStyle* style
		)
		{
			_viewportStyle.insert({viewport, style});
		}

	private:
		std::map<const Viewport, const vtkInteractorStyle*> _viewportStyle;
	};

	class vtkOnInteractionEvent : public vtkCommand
	{
	public:
		static vtkOnInteractionEvent* New()
		{
			return new vtkOnInteractionEvent;
		}

		void Execute(vtkObject* caller, unsigned long, void*) override
		{
			vtkNew<vtkTransform> t;
			auto widget = reinterpret_cast<vtkBoxWidget*>(caller);
			widget->GetTransform(t);
			widget->GetProp3D()->SetUserTransform(t);
		}
	};
}  // namespace

int main(int argc, char* argv[])
{
	// Create an instance of vtkNamedColors to select colours for the object
	// and background
	vtkNew<vtkNamedColors> colors;
	
	// Now we create an instance of vtkConeSource and set some of its
	// properties. The instance of vtkConeSource "cone" is part of a
	// visualization pipeline (it is a source process object); it produces data
	// (output type is vtkPolyData) which other filters may process
	vtkNew<vtkConeSource> cone;
	cone->SetHeight(3.0);
	cone->SetRadius(1.0);
	cone->SetResolution(100);

	// Terminate the pipeline with a mapper process object
	vtkNew<vtkPolyDataMapper> coneMapper;
	coneMapper->SetInputConnection(cone->GetOutputPort());

	// Create an actor to represent the cone. The actor orchestrates rendering
	// of the mapper's graphics primitives. An actor also refers to properties
	// via a vtkProperty instance, and includes an internal transformation
	// matrix. We set this actor's mapper to be coneMapper which we created
	// above.
	vtkNew<vtkActor> coneActor;
	coneActor->SetMapper(coneMapper);
	coneActor->GetProperty()->SetColor(
		colors->GetColor3d("Magenta").GetData()
	);

	// Create the Renderer and assign actors to it. A renderer is like a
	// viewport. It is part or all of a window on the screen and it is
	// responsible for drawing the actors it has.  We also set the background
	// color here.
	vtkNew<vtkRenderer> rendererA;
	rendererA->AddActor(coneActor);
	rendererA->SetBackground(
		colors->GetColor3d("RoyalBlue").GetData()
	);
	rendererA->SetViewport(0.0, 0.0, 0.5, 1.0);

	vtkNew<vtkRenderer> rendererB;
	rendererB->AddActor(coneActor);
	rendererB->SetBackground(
		colors->GetColor3d("DodgerBlue").GetData()
	);
	rendererB->SetViewport(0.5, 0.0, 1.0, 1.0);

	// Create the render window which will show up on the screen. We put our
	// renderer into the render window using AddRenderer. We also
	// set the size to be 300 pixels by 300.
	vtkNew<vtkRenderWindow> renderWindow;
	renderWindow->AddRenderer(rendererA);
	renderWindow->AddRenderer(rendererB);
	renderWindow->SetSize(600, 300);
	renderWindow->SetWindowName("VTK Cone Tutorial");

	// Make one view 90 degrees from other
	rendererA->ResetCamera();
	rendererA->GetActiveCamera()->Azimuth(90);

	// Create interactor
	vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkNew<vtkInteractorStyleTrackballCamera> styleA;
	styleA->SetDefaultRenderer(rendererA);
	vtkNew<vtkInteractorStyleTrackballCamera> styleB;
	styleB->SetDefaultRenderer(rendererB);

	renderWindowInteractor->SetInteractorStyle(styleB);

	vtkNew<vtkOnLeftMouseClick> onLeftMouseClick;
	onLeftMouseClick->addViewportInteractorStyle(Viewport::Left, styleA);
	onLeftMouseClick->addViewportInteractorStyle(Viewport::Right, styleB);
	renderWindowInteractor->AddObserver(
	 	vtkCommand::LeftButtonPressEvent,
	 	onLeftMouseClick
	);

	// Create box widget
	vtkNew<vtkBoxWidget> boxWidget;
	boxWidget->SetInteractor(renderWindowInteractor);
	boxWidget->SetPlaceFactor(1.25);
	boxWidget->GetOutlineProperty()->SetColor(
		colors->GetColor3d("Gold").GetData()
	);
	boxWidget->SetProp3D(coneActor);
	boxWidget->PlaceWidget();
	vtkNew<vtkOnInteractionEvent> onInteractionEvent;
	boxWidget->AddObserver(vtkCommand::InteractionEvent, onInteractionEvent);

	// Create pipeline
	cone->Update();

	// Start event loop
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}

// End of `vtk_cone_app.cpp`
