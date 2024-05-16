#include "UI_Image.h"
#include "SpriteRenderer.h"

UI_Image::UI_Image(std::string textureFilePath) : UI_Object("UI_Image") {
	AddComponent<SpriteRenderer>(new SpriteRenderer(this, textureFilePath));
}