/*
 * FancyBoardUI.h
 *
 *  Created on: Nov 18, 2019
 *      Author: erno
 */

#ifndef FANCYBOARDUI_DEFINED_H
#define FANCYBOARDUI_DEFINED_H

#include <string>
#include "Storyboard.h"

namespace codesmith {

class FancyBoardUI
{
	public: // Construct/desctruct
		/**
		 * Default constructor
		 */
		FancyBoardUI() : stories() { };

		// Desctructor
		virtual ~FancyBoardUI() { };

	public: // Methods
		/// Could be static since this class has member data
		void show();

	private:
		Storyboard stories;
}; // FancyBoardUI

} // Namespace codesmith

#endif // FANCYBOARDUI_DEFINED_H
