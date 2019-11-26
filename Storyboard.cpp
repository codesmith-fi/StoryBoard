#include <algorithm>
#include <exception>
#include "Storyboard.h"
#include "NoteNotFoundException.h"

namespace codesmith
{
	void Storyboard::clear()
	{
		m_stories.empty();
	}

	int Storyboard::addNote(Note& newNote)
	{
		auto id = generateUniqueId();
		newNote.setId(id);
		m_stories.push_back(newNote);
		return id;
	}

	void Storyboard::updateNote(int id, const Note& newNote)
	{
		std::vector<Note>::iterator it = getNoteIterById(id);

		if (it == m_stories.end()) {
			throw NoteNotFoundException();
		}
		else {
			// Update the found Note but preserve the original id. Assignment operator
			// copies all contents including id.
			auto oldId = (*it).getId();
			(*it) = newNote;
			(*it).setId(oldId);
		}
	}

	Note& Storyboard::getNote(int id)
	{
		std::vector<Note>::iterator it = getNoteIterById(id);

		if (it == m_stories.end()) {
			throw NoteNotFoundException();
		}
		return *it;
	}

	void Storyboard::deleteNote(int id)
	{
		auto it = getNoteIterById(id);
		if (it != m_stories.end()) {
			m_stories.erase(it);
		}
	}

	std::vector<Note> Storyboard::searchByTitle(const std::string& title) const
	{
		std::vector<Note> result;
		for (auto& note : m_stories) {
			if (note.getTitle() == title) {
				result.emplace_back(note);
			}
		}
		return result;
	}

	std::vector<Note> Storyboard::searchByDescription(const std::string& description) const
	{
		std::vector<Note> result;
		for (auto& note : m_stories) {
			if (note.getDescription() == description) {
				result.emplace_back(note);
			}
		}
		return result;
	}

	std::vector<Note> Storyboard::searchByTag(const Tag& tag) const
	{
		std::vector<Note> result;
		for (auto& note : m_stories) {
			if (note.hasTag(tag)) {
				result.emplace_back(note);
			}
		}
		return result;
	}

	std::vector<Note> Storyboard::searchByTags(std::vector<Tag> tags) const
	{
		std::vector<Note> result;
		for (auto& note : m_stories) {
			bool hastags = true;
			for (auto tag : tags) {
				if (!note.hasTag(tag)) {
					hastags = false;
				}
			}

			if (!hastags) {
				break;
			}
			else {
				result.emplace_back(note);
			}
		}
		return result;
	}

	std::vector<Note>::iterator Storyboard::getNoteIterById(int id)
	{
		auto it = m_stories.begin();
		for (; it != m_stories.end(); it++) {
			if ((*it).getId() == id) {
				break;
			}
		}
		return it;
	}

	int Storyboard::generateUniqueId()
	{
		return ++m_lastNoteId;
	}
} // namespace codesmith