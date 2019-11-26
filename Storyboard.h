/*
 * Storyboard.h
 *
 *  Created on: Nov 18, 2019
 *      Author: erno
 */

#ifndef STORYBOARD_DEFINED_H
#define STORYBOARD_DEFINED_H

#include <vector>
#include <iterator>
#include "Note.h"
#include "Tag.h"

namespace codesmith {
	class Storyboard
	{
	public: // Construct/desctruct
		/**
		 * Default constructor
		 */
		Storyboard() : m_stories(), m_lastNoteId(-1) { };

		// Desctructor
		virtual ~Storyboard() { };

	public: // Methods
		/**
		 * Get the size of this storyboard
		 */
		size_t size() const { return m_stories.size(); };

		/**
		 * Delete all notes contained in this storyboard
		 */
		void clear();

		/**
		 * Add a new note to the board
		 * @param (By Ref)note the note to be added, id will be generated
		 * @return (int) id of the newly added note and the note has
		 * 	an updated id as well
		 */
		int addNote(Note& note);

		/**
		 * Get a note by id
		 * @param id Id of the note to be fetched
		 * @return note
		 * @throw invalid_argument if the note does not exist
		 */
		Note& getNote(int id);

		/**
		 * Get all notes
		 * @return vector of Notes
		 */
		const std::vector<Note>& getAllNotes() const { return m_stories; };

		/**
		 * Delete a note by id, does nothing if Note does not exist
		 * @param id Id of the note to be deleted
		 */
		void deleteNote(int id);

		/**
		 * Update an existing note with new info
		 * @param id id of the note to be updated
		 * @param note New note data (note id is ignored)
		 * @throw NoteNotFoundException if note does not exist
		 */
		void updateNote(int id, const Note& note);

		/**
		 * Search a note by given title (exact match)
		 * @param title Title of a note to be searched
		 * @return vector of notes matching the given criteria
		 * @note Returns copies in a vector, this can be hugely improved by returning
		 *		list of references instead copies of Notes in a vector
		 */
		std::vector<Note> searchByTitle(const std::string& title) const;

		/**
		 * Search a note by given description (exact match)
		 * @param description Description of a note to be searched
		 * @return vector of notes matching the given criteria
		 * @note Returns copies in a vector, this can be hugely improved by returning
		 *		list of references instead copies of Notes in a vector
		 */
		std::vector<Note> searchByDescription(const std::string& description) const;

		/**
		 * Search a note having one given Tag
		 * @param Tag Tag which is to be searched
		 * @return vector of notes having the tag
		 * @note Returns copies in a vector, this can be hugely improved by returning
		 *		list of references instead copies of Notes in a vector
		 */
		std::vector<Note> searchByTag(const Tag& tag) const;

		/**
		 * Search a note having all of the given tags
		 * @param Tag Vector of tags to be matched
		 * @return vector of notes having all given tags
		 * @note Returns copies in a vector, this can be hugely improved by returning
		 *		list of references instead copies of Notes in a vector
		 */
		std::vector<Note> searchByTags(const std::vector<Tag> tags) const;

	private: // Methods
		int generateUniqueId();
		std::vector<Note>::iterator getNoteIterById(int id);

	private:
		// List of stories contained in this storyboard
		std::vector<Note> m_stories;
		int m_lastNoteId;
	}; // Storyboard
} // Namespace codesmith

#endif // STORYBOARD_DEFINED_H
