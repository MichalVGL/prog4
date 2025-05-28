
#include <Minigin.h>

void Test();

int main(int, char* []) {

	dae::Window window{ .title = "Bomberman", .w = 640, .h = 480, .renderScale = 1.5f };

	dae::Minigin engine("../Data/", window);
	engine.Run(&Test);
	return 0;
}

void Test()
{

}