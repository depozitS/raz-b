#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <format>
#include <stdexcept>

class TextFile{
private:
	std::vector<std::string> lines_;
	std::filesystem::path path_;
	bool loaded_ = false;

public:
	explicit TextFile(const std::filesystem::path& path) { reloadFrom(path); };

	/// I/O
	// 
	/// @brief to upload another file to an existing object
	void reloadFrom(const std::filesystem::path& path);
	//
	/// @brief saves to own path
	bool save() const { return saveAs(this->path_); };
	//
	/// @brief saves to the specified file
	bool saveAs(const std::filesystem::path& path) const;

	/// ACCESS
	//
	/// @brief returns the file size in lines
	size_t getSize() const { return lines_.size(); };
	//
	/// @brief returns the file size in characters
	size_t sizeByCharacters() const;
	//
	/// @brief returns file
	const std::vector<std::string>& content() const { return lines_; };
	//
	/// @brief returns path
	std::filesystem::path getPath() const { return path_; };
	// 
	/// @brief returns filename
	std::string fileName() const { return path_.filename().string(); };
	//
	/// @brief returns extension
	// TODO make an enum of supported formats
	
	/// STATUS
	//
	bool isLoaded() const { return loaded_; };
	//
	bool existsOnDisk() const;
	// 
	bool isEmpty() const;

};

