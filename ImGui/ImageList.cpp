#include "pch.h"
#include "ImageList.h"

std::string ImageList::GetKey() {
	std::string name;
	if (key == IDLE) {
		name = "IDLE";
	}
	return name;
}