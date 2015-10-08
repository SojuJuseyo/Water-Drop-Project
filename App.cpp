#include "pch.h"

#include "App.h"
#include "Game.h"

[MTAThread]
int main(Array<String^>^ args)
{
	CoreApplication::Run(ref new AppSource());
	return 0;
}