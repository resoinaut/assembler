#pragma once

namespace ansi {

const char *const reset      = "\033[0m";

namespace colour {
	const char *const red    = "\033[31m";
	const char *const green  = "\033[32m";

namespace bright {
	const char *const yellow = "\033[93m";
	const char *const white  = "\033[97m";
}

}

namespace cursor {
	const char *const up     = "\033[A";
}

}
