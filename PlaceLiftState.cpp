/*
 * Copyright 2010 Daniel Albano
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "PlaceLiftState.h"
#include <sstream>
#include "Game.h"
#include "ResourcePack.h"
#include "Language.h"
#include "LangString.h"
#include "Font.h"
#include "Palette.h"
#include "TextButton.h"
#include "Window.h"
#include "Text.h"
#include "BaseView.h"
#include "Base.h"
#include "BaseFacility.h"
#include "RuleBaseFacility.h"
#include "Ruleset.h"
#include "BasescapeState.h"

/**
 * Initializes all the elements in the Place Lift screen.
 * @param game Pointer to the core game.
 * @param base Pointer to the base to get info from.
 */
PlaceLiftState::PlaceLiftState(Game *game, Base *base) : State(game), _base(base)
{
	// Create objects
	_view = new BaseView(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 192, 192, 0, 8);
	_txtTitle = new Text(game->getResourcePack()->getFont("BIGLETS.DAT"), game->getResourcePack()->getFont("SMALLSET.DAT"), 180, 9, 10, 0);
	
	// Set palette
	_game->setPalette(_game->getResourcePack()->getPalette("PALETTES.DAT_1")->getColors());

	add(_view);
	add(_txtTitle);

	// Set up objects
	_view->setTexture(_game->getResourcePack()->getSurfaceSet("BASEBITS.PCK"));
	_view->setBase(_base);
	_view->setSelectable(_game->getRuleset()->getBaseFacility(STR_ACCESS_LIFT)->getSize());
	_view->onMouseClick((EventHandler)&PlaceLiftState::viewClick);

	_txtTitle->setColor(Palette::blockOffset(13)+10);
	_txtTitle->setText(_game->getResourcePack()->getLanguage()->getString(STR_SELECT_POSITION_FOR_ACCESS_LIFT));
}

/**
 *
 */
PlaceLiftState::~PlaceLiftState()
{
	
}

/**
 * Processes clicking on facilities.
 * @param ev Pointer to the SDL_Event.
 * @param scale Scale of the screen.
 */
void PlaceLiftState::viewClick(SDL_Event *ev, int scale)
{
	BaseFacility *fac = new BaseFacility(_game->getRuleset()->getBaseFacility(STR_ACCESS_LIFT), _view->getGridX(), _view->getGridY());
	fac->setBuildTime(0);
	_base->getFacilities()->push_back(fac);
	_game->popState();
	_game->pushState(new BasescapeState(_game, _base));
}
