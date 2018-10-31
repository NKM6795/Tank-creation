#include "GraphicForNotificationWindow.h"


void drawLine(RenderTexture &renderTexture, int x1, int y1, int x2, int y2, Color color)
{
	Vertex line[2] =
	{
		Vertex(Vector2f(float(x1), float(y1))),
		Vertex(Vector2f(float(x2), float(y2)))
	};
	line[0].color = color;
	line[1].color = line[0].color;

	renderTexture.draw(line, 2, Lines);
}

void drawRectangle(RenderTexture &renderTexture, int x1, int y1, int x2, int y2, Color color)
{
	drawLine(renderTexture, x1, y1, x2, y1, color);
	drawLine(renderTexture, x1 - 1, y2, x2 - 1, y2, color);
	drawLine(renderTexture, x1, y1, x1, y2, color);
	drawLine(renderTexture, x2, y1 + 1, x2, y2 + 1, color);
}

void drawFramework(RenderTexture &renderTexture, int x1, int y1, int x2, int y2)
{
	for (int i = 1; i <= 4; ++i)
	{
		drawRectangle(renderTexture, x1 - i + 1, y1 - i, x2 + i, y2 + i - 1, i != 4 ? Color(0, 0, 0) : Color(0, 0, 0, 30));
	}
}

Image *getForm(int width, int height)
{
	Image *result;

	RenderTexture renderTextureForResult;
	renderTextureForResult.create(width, height);
	renderTextureForResult.clear(Color(84, 63, 37));


	drawFramework(renderTextureForResult, 3, 3, width - 3, height - 3);
	renderTextureForResult.display();

	Texture textureForResult;
	textureForResult = renderTextureForResult.getTexture();

	result = new Image;
	result->create(width, height, Color(84, 63, 37));
	result->copy(renderTextureForResult.getTexture().copyToImage(), 0, 0, IntRect(0, 0, width, height), true);

	return result;
}