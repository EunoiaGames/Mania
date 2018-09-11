#include "Rendering\Display.h"
#include "Rendering\Renderer.h"

int main()
{
	Display display(800, 600);

	Renderer renderer;

	RenderInfo renderable;
	renderable.pos = Vector2f(-1.0f, -1.0f);
	renderable.size = Vector2f(1.0f, 1.0f);
	renderable.texture = 0;

	while (!display.IsCloseRequested())
	{
		renderer.StartFrame();

		renderer.BeginBatch();
		renderer.Submit(renderable);
		renderer.RenderBatch();

		renderer.EndFrame();
		display.Update();
	}
}