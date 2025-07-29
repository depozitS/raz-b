#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <format>
#include <stdexcept>
#include <map>

class TextFile{
private:
	std::vector<std::string> lines_;
	std::filesystem::path path_;
	bool loaded_ = false;

public:
	explicit TextFile(const std::filesystem::path& path) { reloadFrom(path); };

	/// I/O
	// 
	/// @brief To upload another file to an existing object
	void reloadFrom(const std::filesystem::path& path);
	//
	/// @brief Saves to own path
	bool save() const { return saveAs(this->path_); };
	//
	/// @brief Saves to the specified file
	bool saveAs(const std::filesystem::path& path) const;

	/// ACCESS
	//
	/// @brief Returns count lines in file
	size_t sizeByLines() const { return lines_.size(); };
	//
	/// @brief Returns the file size in characters
	size_t sizeByCharacters() const;
	//
	/// @brief Returns file
	const std::vector<std::string>& content() const { return lines_; };
	//
	/// @brief Returns path
	const std::filesystem::path& getPath() const { return path_; };
	// 
	/// @brief Returns filename
	std::string fileName() const { return path_.filename().string(); };
	//
	/// @brief Returns extension
	// TODO make an enum of supported formats
	
	/// STATUS
	//
	bool isLoaded() const { return loaded_; };
	//
	bool existsOnDisk() const { return std::filesystem::exists(this->path_); };
	// 
	bool isEmpty() const { return this->lines_.empty(); };

	/// MODIFICATION
	//
	/// @brief Appends a line to the end of the file content.
	void append(const std::string& line) { this->lines_.push_back(line); };
	//
	/// @brief Prepends a line to the beginning of the file content.
	void prepend(const std::string& line);
	//
	/// @brief Inserts a line at the specified index.
	void insert(size_t index, const std::string& line) { this->lines_.insert(this->lines_.begin() + index, line); };
	//
	/// @brief Removes a line at the specified index.
	void remove(size_t index) { this->lines_.erase(this->lines_.begin() + index); };
	//
	/// @brief Removes the first occurrence of the specified line.
	void remove(const std::string& line);
	//
	/// @brief Replaces all occurrences of `oldValue` with `newValue` in all lines
	void replaceAll(const std::string& oldValue, const std::string& newValue);
	//
	/// @brief Clears all lines, making the file content empty.
	void clear() { this->lines_.clear(); };
	//
	/// @brief Removes all empty lines from the content.
	void removeEmptyLines();
	//
	/// @brief Removes duplicate lines, keeping only the first occurrence.
	void removeDuplicateLines();
	//
	/// @brief Sorts lines in lexicographical (alphabetical) order.
	// TODO add enum class-orders 
	void sortLines();
	//
	/// @brief Pads all lines to the specified length using the given character.
	void padLinesToLength(size_t len, char pad = ' ');

	/// SORTING
	//
	/// @brief returns indices of lines containing the specified substring
	std::vector<size_t> findLinesContaining(const std::string& substr) const;
	//
	/// @brief returns all lines that contain the specified pattern (case-sensitive)
	std::vector<std::string> grep(const std::string& pattern) const;
	//
	/// @brief checks if any line in the file contains the specified substring
	bool contains(const std::string& substr) const;

	/// STATISTICS
	//
	/// @brief Counts the total number of words in all lines (split by whitespace).
	size_t countWords() const;
	//
	/// @brief Counts the number of unique words in the file (case-sensitive).
	size_t countUniqueWords() const;
	//
	/// @brief Returns a map of words and their occurrence frequency.
	std::map<std::string, size_t> wordFrequency() const;

	/// ITERATORS
	//
	/// @brief returns iterator to the beginning
	auto begin() { return lines_.begin(); }
	//
	/// @brief returns iterator to the end
	auto end() { return lines_.end(); }
	//
	/// @brief returns const iterator to the beginning
	auto begin() const { return lines_.cbegin(); }
	//
	/// @brief returns const iterator to the end
	auto end() const { return lines_.cend(); }

};

