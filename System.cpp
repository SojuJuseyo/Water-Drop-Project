#include "pch.h"

#include "System.h"

void System::Initialize(CoreApplicationView^ AppView)
{
	_isOpen = true;
	// Set les events du programme
	AppView->Activated += ref new TypedEventHandler
		<CoreApplicationView^, IActivatedEventArgs^>(this, &System::OnActivated);
	CoreApplication::Suspending +=
		ref new EventHandler<SuspendingEventArgs^>(this, &System::Suspending);
	CoreApplication::Resuming +=
		ref new EventHandler<Object^>(this, &System::Resuming);
}

void System::SetWindow(CoreWindow^ Window)
{
	// Set les events de la fenêtre
	Window->PointerPressed += ref new TypedEventHandler
		<CoreWindow^, PointerEventArgs^>(this, &System::PointerPressed);
	Window->KeyDown += ref new TypedEventHandler
		<CoreWindow^, KeyEventArgs^>(this, &System::KeyDown);
	Window->KeyUp += ref new TypedEventHandler
		<CoreWindow^, KeyEventArgs^>(this, &System::KeyUp);
	Window->Closed += ref new TypedEventHandler
		<CoreWindow^, CoreWindowEventArgs^>(this, &System::Closed);
}

void System::OnActivated(CoreApplicationView^ CoreAppView, IActivatedEventArgs^ Args)
{
	CoreWindow^ Window = CoreWindow::GetForCurrentThread();
	Window->Activate();
}


// Si un clic de la souris est detecte
void System::PointerPressed(CoreWindow^ Window, PointerEventArgs^ Args)
{
	/*
	std::stringstream message;
	message << "Position X: " << Args->CurrentPoint->Position.X << " Y: " << Args->CurrentPoint->Position.Y;
	std::string s = message.str();
	std::wstring ws(s.begin(), s.end());
	MessageDialog Dialog(ref new Platform::String(ws.c_str()), "Water Drop");
	Dialog.ShowAsync();
	*/
}

// Si une touche est pressee
void System::KeyDown(CoreWindow^ Window, KeyEventArgs^ Args)
{
	if (Args->VirtualKey == VirtualKey::Escape)
	{
		_isOpen = false;
	}
}

// Si une touche est relevee
void System::KeyUp(CoreWindow^ Window, KeyEventArgs^ Args)
{
}

void System::Closed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	_isOpen = false;
}

void System::Run()
{
	Game.Initialize();
		
	CoreWindow^ Window = CoreWindow::GetForCurrentThread();
	while (_isOpen)
	{
		Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

		Game.Update();
		Game.Render();
	}
}