#include "GameState.h"

void GameState::init(EntitySystem * _ents, ResourceManager * _rm, Input * _input, View * _view)
{
	ents = _ents;
	rm = _rm;
	input = _input;
	view = _view;
}
