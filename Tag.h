/*
 * Tag.h
 *
 *  Created on: Nov 18, 2019
 *      Author: erno
 */

#ifndef TAG_DEFINED_H
#define TAG_DEFINED_H

#include <string>

namespace codesmith {

class Tag
{
	public: // Construct/desctruct
		/**
		 * Default constructor, fails always
		 * @throw invalid_argument
		 */
		Tag() : m_name("") { };

		/**
		 *  Constructor which initializes tag with the given name
		 */
		Tag(const std::string& name) : m_name(name) { };

		// Desctructor
		virtual ~Tag() { };

	public: // Methods
		std::string getName() const { return m_name; };
		void setName(std::string name) { m_name = name; };
		virtual bool operator==(const Tag& rhs) const;
		virtual bool operator!=(const Tag& rhs) const;

	private:
		// Name of the tag
		std::string m_name;
}; // Tag

} // Namespace codesmith

#endif // TAG_DEFINED_H
