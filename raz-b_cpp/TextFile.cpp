#include "TextFile.h"

void TextFile::reloadFrom(const std::filesystem::path& path) {

	std::ifstream file(path);
	std::string line;

	if(!file.is_open()) 
		throw std::runtime_error(std::format("file isn't open: {}", path.c_str()));
	
	this->lines_.clear();

	while (std::getline(file, line)) {
		this->lines_.push_back(line);
	}
	file.close();
	this->loaded_ = true;
	this->path_ = path;
	
}

bool TextFile::saveAs(const std::filesystem::path& path) const {
	std::ofstream file(path);

	if (file.is_open()) {
		for (const auto& i : this->lines_) {
			file << i << '\n';
		}
		file.close();
		return true;
	}
	else {
		return false;
	}
}

size_t TextFile::sizeByCharacters() const {
	size_t out = 0;
	for (const auto& line : this->lines_) {
		out += line.size();
	}
	return out;
}
