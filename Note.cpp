#include <vector>
#include <string>
#include <algorithm>
#include "Note.h"

namespace codesmith
{
	bool Note::hasTag(const Tag& tag) const
	{
		return std::find(m_tags.begin(), m_tags.end(), tag) != m_tags.end();
	}

	/*
	 * Naive implementation for assignment purposes only, does not check for
	 * dupes
	 */
	void Note::addTag(const Tag& tag)
	{
		m_tags.push_back(tag);
	}

	Note& Note::operator=(const Note& other)
	{
		m_id = other.m_id;
		m_title = other.m_title;
		m_description = other.m_description;
		m_tags = other.m_tags;
		return *this;
	}

	bool Note::operator==(const Note& rhs) const
	{
		return m_tags == rhs.m_tags && m_title == rhs.m_title && m_description == rhs.m_description;
	}
} // namespace codesmith