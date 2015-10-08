#pragma once

#include <sstream>

#include "Game.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;

ref class System sealed : public IFrameworkView
{
public:

	virtual void Initialize(CoreApplicationView^ AppView);
	virtual void SetWindow(CoreWindow^ Window);
	virtual void Load(String^ EntryPoint) {}
	virtual void Run();
	virtual void Uninitialize() {}
	virtual void Suspending(Object^ Sender, SuspendingEventArgs^ Args) {}
	virtual void Resuming(Object^ Sender, Object^ Args) {}
	virtual void OnActivated(CoreApplicationView^ CoreAppView, IActivatedEventArgs^ Args);
	virtual void PointerPressed(CoreWindow^ Window, PointerEventArgs^ Args);
	virtual void KeyDown(CoreWindow^ Window, KeyEventArgs^ Args);
	virtual void KeyUp(CoreWindow^ Window, KeyEventArgs^ Args);
	virtual void Closed(CoreWindow^ sender, CoreWindowEventArgs^ args);

private:
	bool _isOpen;
	CGame Game;
};

