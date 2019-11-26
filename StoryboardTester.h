/*
 * StoryboardTester.h
 *
 *  Created on: Nov 18, 2019
 *      Author: erno
 */

#ifndef STORYBOARDTESTER_H_
#define STORYBOARDTESTER_H_

#include <string>

namespace codesmith {
	/**
	 * Simple "unit" test for Storyboard project classes
	 * This runner class is a singleton and contains operations to run tests cases
	 * and get the success and failure counts after running
	 */
	class StoryboardTester {
	public: // Singleton accessor
		static StoryboardTester& instance() {
			static StoryboardTester tester;
			return tester;
		}

	private: //
		StoryboardTester() : m_testFailCount(0), m_testSuccessCount(0) { };

	public: // helpers
		int FailCount() { return m_testFailCount; };
		int SuccessCount() { return m_testSuccessCount; };
		void TestFailure(const std::string& description);
		void TestSuccess(const std::string& description);
		void AssertCondition(bool condition, const std::string& testMessage);

	public: // Test runners
		void RunAll();
		void RunStoryboardTests(bool reset = false);
		void RunTagTests(bool reset = false);
		void RunNoteTests(bool reset = false);

	private: // Test cases for Tag class
		void TestCreateTagInstance();
		void TestCompareTags();

	private: // Test cases for Note class
		void TestNoteCreateInstanceEmpty();
		void TestNoteCreateInstanceWithParams();
		void TestNoteVerifyProperties();
		void TestNoteVerifyTags();

	private: // Test cases for Storyboard class
		void TestCreateStoryboard();
		void TestStoryboardAddDeleteNote();
		void TestStoryboardUpdateNote();
		void TestStoryboardFindNote();

	private: // Data
		int m_testFailCount;
		int m_testSuccessCount;
	};
} /* namespace codesmith */

#endif /* STORYBOARDTESTER_H_ */
