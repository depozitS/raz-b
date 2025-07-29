#include "TextFile.h"

void TextFile::reloadFrom(const std::filesystem::path& path) {

	this->lines_.clear();

	std::ifstream file(path);
	std::string line;

	if (file.is_open()) {

		while (std::getline(file, line)) {
			this->lines_.push_back(line);
		}
		file.close();
		this->loaded_ = true;
		this->path_ = path;
	}
	else {
		throw std::runtime_error(std::format("file isn't open: {}", path.c_str()));
	}
}

bool TextFile::saveAs(const std::filesystem::path& path) const {
	std::ofstream file(path);

	if (file.is_open()) {
		for (const auto& i : this->lines_) {
			file << i << "\n";
		}
		file.close();
		return true;
	}
	else {
		return false;
	}
}