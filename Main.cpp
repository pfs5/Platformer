// SFML_project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include "DefaultState.h"

#include <SFML/Graphics.hpp>

int main() {	
	Application app{};
	app.addGameState(new DefaultState(app));

	app.runMainLoop();

    return 0;
}

