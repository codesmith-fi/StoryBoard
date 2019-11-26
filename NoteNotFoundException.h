/*
 * NoteNotFoundException.h
 *
 *  Created on: Nov 18, 2019
 *      Author: erno
 */

#ifndef NOTEDOESNOTEXISTEXCEPTION_H_
#define NOTEDOESNOTEXISTEXCEPTION_H_

#include <exception>

namespace codesmith {
	class NoteNotFoundException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Note does not exist exception";
		}
	}; // NoteNotFoundException
} // namespace codesmith

#endif /* NOTEDOESNOTEXISTEXCEPTION_H_ */
