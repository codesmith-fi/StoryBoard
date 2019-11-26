#ifndef NOTE_DEFINED_H
#define NOTE_DEFINED_H

/*
 * Note.h
 *
 *  Created on: Nov 18, 2019
 *      Author: erno
 */

#include <string>
#include <vector>

#include "Tag.h"

namespace codesmith {
	class Note
	{
	public: // Constants
		const static int invalid_note_id = -1;

	public: // Construct/destruct
		/**
		 * Default constructor creates an uninitialized Note
		 */
		Note() : m_id(invalid_note_id), m_title(""), m_description(""), m_tags() { };

		/**
		 * Create a Note with all other info except it has an
		 * uninitialized id
		 */
		Note(std::string title, std::string description,
			std::vector<Tag>& tags) :
			Note(invalid_note_id, title, description, tags) {};

		/// Destructor
		virtual ~Note() { };
	private:
		/**
		 * Creates a story with all information
		 * Reason this is private is because the id is assigned automatically
		 * and id generation is handled by the class owning all notes
		 */
		Note(int id, std::string title, std::string description,
			std::vector<Tag>& tags) :
			m_id(id), m_title(title), m_description(description), m_tags(tags) { };

	public: // Methods
		int getId() const { return m_id; }
		void setId(int newId) { m_id = newId; }
		std::string getTitle() const { return m_title; }
		void setTitle(const std::string& title) { m_title = title; }
		std::string getDescription() const { return m_description; }
		void setDescription(const std::string& description) { m_description = description; }
		bool hasTag(const Tag& tag) const;
		void addTag(const Tag& tag);
		size_t tagCount() const { return m_tags.size(); }
		bool operator==(const Note& rhs) const;
		Note& operator=(const Note& other);
	private: // Methods

	private: // Data
		int m_id;
		std::string m_title;
		std::string m_description;
		std::vector<Tag> m_tags;
	}; // Note
} // Namespace codesmith

#endif // NOTE_DEFINED_H
