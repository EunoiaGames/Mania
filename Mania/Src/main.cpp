#include "Rendering\Display.h"
#include "Rendering\Renderer.h"
#include "Rendering\Chart.h"
#include "Rendering\Skin.h"

void draw_stage(const Skin& skin, Renderer* pRenderer)
{
	uint32 stageSize = skin.noteInfo.size * 4 + skin.noteInfo.gap * 3;
	RenderInfo stage;
	stage.pos = Vector2f(200, 0);
	stage.size = Vector2f(stageSize, 600);
	stage.color = skin.stageInfo.color;
	stage.texture = 0;
	pRenderer->Render(stage);
}

RenderInfo create_stage_render_info(const Skin& skin)
{
	uint32 stageSize = skin.noteInfo.size * 4 + skin.noteInfo.gap * 3;
	RenderInfo stage;
	stage.pos = Vector2f(200, 0);
	stage.size = Vector2f(stageSize, 600);
	stage.color = skin.stageInfo.color;
	stage.texture = 0;
	return stage;
}

RenderInfo create_note_render_ingo(const Skin& skin)
{
	RenderInfo note;
	note.pos = Vector2f(0, 0);
	note.size = Vector2f(skin.noteInfo.size, skin.noteInfo.size);
	note.color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	note.texture = 0;
	return note;
}

int main()
{
	Display display(800, 600);

	Renderer renderer;

	renderer.SetProjection(mat4_create_orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f));

	Skin skin;
	load_skin_from_folder(&skin, "Res/Skins/Test");

	Chart chart;
	load_chart(&chart, "Res/Charts/Test.chart");

	float dt = 1.0f / 60.0f;

	RenderInfo stageInfo = create_stage_render_info(skin);
	RenderInfo noteInfo = create_note_render_ingo(skin);

	float t = 0.0;

	while (!display.IsCloseRequested())
	{
		renderer.StartFrame();

		renderer.Render(stageInfo);
		

		
		renderer.EndFrame();

		display.GetInput()->Update();
		display.Update();
	}
}