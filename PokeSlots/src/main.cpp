#include "pch.h"
#include "application.h"

int main()
{
	using namespace slots;

	// Todo: Letterbox the view.
	Application app(256 * 3, 192 * 3, "Pokemon Slots");
	app.Run();

	return EXIT_SUCCESS;
}