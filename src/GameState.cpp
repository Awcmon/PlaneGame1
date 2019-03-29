#include "GameState.h"

void GameState::init(EntitySystem * _ents, ResourceManager * _rm, Input * _input, View * _view, GameState** _curGameState)
{
	ents = _ents;
	rm = _rm;
	input = _input;
	view = _view;
	curGameState = _curGameState;
}

void changeGameState(GameState * newGameState, EntitySystem* ents, ResourceManager* rm, Input* input, View* view, GameState** curGameState)
{
	if (*curGameState != nullptr)
	{
		GameState* oldGameState = *curGameState;
		*curGameState = newGameState;
		delete oldGameState;
		oldGameState = nullptr;
	}
	else
	{
		*curGameState = newGameState;
	}
	(*curGameState)->init(ents, rm, input, view, curGameState);
	(*curGameState)->setup();
}
