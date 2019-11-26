/*
 * StoryboardTester.cpp
 *
 *  Created on: Nov 18, 2019
 *      Author: erno
 */

#include "StoryboardTester.h"
#include "Tag.h"
#include "Note.h"
#include "Storyboard.h"
#include "NoteNotFoundException.h"
#include "DebugLogger.h"

namespace codesmith {

// Test constants
const std::string const_noteTitle = "Note title";
const std::string const_noteDescription = "Note description";
const std::string const_updateTitle = "Updated note title";
const std::string const_foobarDescription = "Foobar description";
const std::string const_foobarTitle = "Foobar";
const Tag const_tag1("Tag1");
const Tag const_tag2("Tag2");
const Tag const_tag3("Tag3");

void StoryboardTester::RunAll()
{
	m_testFailCount = 0;
	m_testSuccessCount = 0;

	RunTagTests();
	std::cout << std::endl;
	RunNoteTests();
	std::cout << std::endl;
	RunStoryboardTests();
	std::cout << std::endl;
}

void StoryboardTester::RunTagTests(bool reset)
{
	m_testFailCount = !reset ? m_testFailCount : 0;
	m_testSuccessCount = !reset ? m_testSuccessCount : 0;

	LOG_INFO() << "Start Tag- Running Tag class test cases";
	TestCreateTagInstance();
	TestCompareTags();
	LOG_INFO() << "End: Tag";
}

void StoryboardTester::RunNoteTests(bool reset)
{
	m_testFailCount = !reset ? m_testFailCount : 0;
	m_testSuccessCount = !reset ? m_testSuccessCount : 0;

	LOG_INFO() << "Start Note - Running Note class test cases";
	TestNoteCreateInstanceEmpty();
	TestNoteCreateInstanceWithParams();
	TestNoteVerifyProperties();
	TestNoteVerifyTags();
	LOG_INFO() << "End: Note";
}

void StoryboardTester::RunStoryboardTests(bool reset)
{
	m_testFailCount = !reset ? m_testFailCount : 0;
	m_testSuccessCount = !reset ? m_testSuccessCount : 0;

	LOG_INFO() << "Start Storyboard - Running Storyboard class test cases";
	TestCreateStoryboard();
	TestStoryboardAddDeleteNote();
	TestStoryboardUpdateNote();
	TestStoryboardFindNote();
	LOG_INFO() << "End: Storyboard";
}

/**
 * Test cases for Tag
 */
void StoryboardTester::TestCreateTagInstance()
{
	LOG_INFO() << "TestCreateTagInstance() enter";

	Tag tag;
	Tag tag2("Tag");

	AssertCondition(tag.getName().empty(), "Tag should be empty");
	AssertCondition(tag2.getName() == "Tag", "Tag name should be Tag");
	LOG_INFO() << "TestCreateTagInstance() exit";
}

void StoryboardTester::TestCompareTags()
{
	LOG_INFO() << "TestCompareTags() enter";

	Tag tag1("Tag");
	Tag tag2("Tag");
	Tag tag3("AnotherTag");

	AssertCondition(tag1 == tag2, "Tags should be equal with operator==");
	AssertCondition(tag1 != tag3, "Tags should not be equal with operator==");

	LOG_INFO() << "TestCompareTags() exit";
}

/**
 * Test cases for Note
 */
void StoryboardTester::TestNoteCreateInstanceEmpty()
{
	LOG_INFO() << "TestNoteCreateInstanceEmpty() enter";

	Note emptyNote;
	AssertCondition(emptyNote.getId() != 0, "New note should have a negative id");
	LOG_INFO() << "TestNoteCreateInstanceEmpty() exit";
}

void StoryboardTester::TestNoteCreateInstanceWithParams()
{
	LOG_INFO() << "TestNoteCreateInstanceWithParams() enter";

	std::vector<Tag> tags; // empty list of tags

	// Validate a note with properties except the id
	Note note(const_noteTitle, const_noteDescription, tags);
	AssertCondition( (
			note.tagCount() == 0 && note.getId() < 0 &&
			note.getTitle() == const_noteTitle &&
			note.getDescription() == const_noteDescription),
			"Note should have Title, Description, negative id and no tags");

	std::vector<Tag> tags2 { const_tag1, const_tag2, const_tag3 };
	Note note2(const_noteTitle, const_noteDescription, tags2);

	AssertCondition( (
			note2.tagCount() == 3 && note2.getId() < 0 &&
			note2.getTitle() == const_noteTitle &&
			note2.getDescription() == const_noteDescription),
			"Note should have Title, Description, negative id and 3 tags");
	LOG_INFO() << "TestNoteCreateInstanceWithParams() exit";
}

void StoryboardTester::TestNoteVerifyProperties()
{
	LOG_INFO() << "TestNoteVerifyProperties() enter";
	const int tempNoteId = 42;

	// Test for empty note
	Note emptyNote;
	AssertCondition(emptyNote.getId() < 0, "Empty note should have negative id");
	AssertCondition(emptyNote.getTitle().empty(), "Empty note should have empty title");
	AssertCondition(emptyNote.getDescription().empty(), "Empty note should have empty description");
	AssertCondition(emptyNote.tagCount() == 0, "Empty note should not have any tags");

	// Test for specific note
	std::vector<Tag> tags { const_tag1, const_tag2, const_tag3 };
	Note note(const_noteTitle, const_noteDescription, tags);
	note.setId(tempNoteId);
	AssertCondition(note.getId() == tempNoteId &&
			note.getTitle() == const_noteTitle &&
			note.getDescription() == const_noteDescription,
			"Note should have specified title and description");

	// Verify tags
	AssertCondition(note.hasTag(const_tag1), "Note should have tag1");
	AssertCondition(note.hasTag(const_tag2), "Note should have tag2");
	AssertCondition(note.hasTag(const_tag3), "Note should have tag3");

	LOG_INFO() << "TestNoteVerifyProperties() exit";
}

void StoryboardTester::TestNoteVerifyTags()
{
	LOG_INFO() << "TestNoteVerifyTags() enter";

	std::vector<Tag> tags { const_tag1, const_tag2, const_tag3 };
	Note note(const_noteTitle, const_noteDescription, tags);
	AssertCondition(note.tagCount() == 3, "Note should have 3 tags");
	AssertCondition(note.hasTag(const_tag1), "Note should have a tag: " + const_tag1.getName());
	AssertCondition(note.hasTag(const_tag2), "Note should have a tag: " + const_tag2.getName());
	AssertCondition(note.hasTag(const_tag3), "Note should have a tag: " + const_tag3.getName());

	LOG_INFO() << "TestNoteVerifyTags() exit";
}

/**
 * Test cases for Storyboard
 */
void StoryboardTester::TestCreateStoryboard()
{
	LOG_INFO() << "TestCreateStoryboard() enter";
	Storyboard board;
	AssertCondition((board.size()==0), "New storyboard should be empty");
	LOG_INFO() << "TestCreateStoryboard() exit";
}

void StoryboardTester::TestStoryboardAddDeleteNote()
{
	LOG_INFO() << "TestStoryboardAddDeleteNote() enter";
	Storyboard board;
	AssertCondition((board.size()==0), "New storyboard should be empty");

	// Add 2 notes
	std::vector<Tag> tags { const_tag1, const_tag2, const_tag3 };
	Note note(const_noteTitle, const_noteDescription, tags);
	auto noteId = board.addNote(note);
	AssertCondition(noteId >= 0, "Note added to storyboard and new id was generated");
	AssertCondition(board.size()==1, "There should be one Note after adding it");

	Note foobarNote(const_foobarTitle, const_foobarDescription, tags);
	auto foobarId = board.addNote(foobarNote);

	AssertCondition(foobarId >= 0, "Second Note added to storyboard and new id was generated");
	AssertCondition(foobarId != noteId, "Second note should have a unique id");
	AssertCondition(board.size() == 2, "There should be two notes in Storyboard");

	board.deleteNote(noteId);
	AssertCondition(board.size() == 1, "There should be one note after deleting the first one");

	bool exceptionThrown = false;
	try {
		board.getNote(noteId);
	} catch (const NoteNotFoundException& /* e */) {
		exceptionThrown = true;
	}
	AssertCondition(exceptionThrown, "Note should not exist after deletion");


	LOG_INFO() << "TestStoryboardAddDeleteNote() exit";
}

void StoryboardTester::TestStoryboardUpdateNote()
{
	LOG_INFO() << "TestStoryboardUpdateNote() enter";

	Storyboard board;
	AssertCondition((board.size()==0), "New storyboard should be empty");

	// Add 2 notes
	std::vector<Tag> tags { const_tag1, const_tag2, const_tag3 };
	Note note(const_noteTitle, const_noteDescription, tags);
	// This note should not be changed
	auto noteId = board.addNote(note);
	Note foobarNote(const_foobarTitle, const_foobarDescription, tags);
	// This note should be changed
	auto foobarId = board.addNote(foobarNote);
	AssertCondition(board.size() == 2, "There should be two notes in Storyboard");

	// Update the second foobar note with new title
	Note newInfo(const_updateTitle, const_noteDescription, tags);
	board.updateNote(foobarId, newInfo);

	// Verify the amount of notes after update
	AssertCondition(board.size() == 2, "There should be two notes after update");
	std::vector<Note> shouldBeEmpty = board.searchByTitle(const_foobarTitle);
	AssertCondition(shouldBeEmpty.size()==0, "Original note should not exist after update");
	std::vector<Note> shouldHaveOneNote = board.searchByTitle(const_updateTitle);
	AssertCondition(shouldHaveOneNote.size()==1, "There should be one note with updated info");

	// Verify that the first note was not changed
	Note& originalNote = board.getNote(noteId);
	AssertCondition(note == originalNote, "The first note in Storyboard should not have changed");
	LOG_INFO() << "TestStoryboardUpdateNote() exit";
}

void StoryboardTester::TestStoryboardFindNote()
{
	LOG_INFO() << "TestStoryboardFindNote() enter";

	int count = 10;
	std::vector<Tag> tags { const_tag1, const_tag2, const_tag3 };
	Note note(const_noteTitle, const_noteDescription, tags);

	Storyboard board;
	// Create notes, 21 with one unique note
	for(int i=0; i<count; ++i) {
		board.addNote(note);
	}
	Note foobarNote(const_foobarTitle, const_foobarDescription, tags);
	auto foobarId = board.addNote(foobarNote);
	for(int i=0; i<count; ++i) {
		board.addNote(note);
	}

	// Get the unique foobar note by id
	Note& exact = board.getNote(foobarId);
	AssertCondition(exact == foobarNote, "Foobar note is found from Storyboard");

	// Find the unique foobar note
	std::vector<Note> searchFoobarRes = board.searchByTitle(const_foobarTitle);
	AssertCondition(searchFoobarRes.size()==1, "Search by title returns only one foobar note");
	AssertCondition(searchFoobarRes[0].getId() == foobarId, "Found foobar id is correct");

	// Find the nonunique notes, there should be 20
	std::vector<Note> searchRes = board.searchByTitle(const_noteTitle);
	AssertCondition(searchRes.size()==20, "Search by title returns 20 non unique notes");

	LOG_INFO() << "TestStoryboardFindNote() exit";
}

/**
 * Helper method implementation
 */
void StoryboardTester::TestFailure(const std::string& description)
{
	m_testFailCount++;
	std::string msg("Failure testing: " + description);
	LOG_ERROR() << msg;
}

void StoryboardTester::TestSuccess(const std::string& description)
{
	m_testSuccessCount++;
	std::string msg("Success testing: " + description);
	LOG_INFO() << msg;
}

void StoryboardTester::AssertCondition(bool condition, const std::string& testMessage)
{
	if(condition) {
		TestSuccess(testMessage);
	} else {
		TestFailure(testMessage);
	}
}


} // namespace codesmith

