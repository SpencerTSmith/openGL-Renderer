#ifndef APP_H
#define APP_H
#pragma once

#include "window.h"

namespace loglr{

class app {
public:		// interface
	app(std::string name);

	void run();
private:	// members
	static constexpr uint32_t width = 800;
	static constexpr uint32_t height = 600;
	std::string name;

	loglr_window window;

	void process_input();
};
} // namespace loglr

#endif // !APP_H

