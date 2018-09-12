#include "GameVariables.h"
#include "AssetHolder.hpp"
#include "Assets.h"
void AssetBank::loadAssets()
{
	fontHolder.loadAssetFromFile(font_opensans_bold, "fonts/OpenSans-Bold.ttf");	
	soundBufferHolder.loadAssetFromFile(soundBuffer_pew_buffer, "soundfx/pew.wav");	
	soundBufferHolder.loadAssetFromFile(soundBuffer_bloop_buffer, "soundfx/beep-02.wav");	
	textureHolder.loadAssetFromFile(background_texture, "images/background.png");
	textureHolder.loadAssetFromFile(tileset_texture, "images/tiles.png");	
	textureHolder.loadAssetFromFile(frame_texture, "images/frame.png");		
}