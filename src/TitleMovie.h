#pragma once

struct TitleMovie {
	bool switchOnSave;
	csl::ut::VariableString islandMovies[7];

	static const hh::fnd::RflClass rflClass;
	static const hh::fnd::RflTypeInfo rflTypeInfo;
};
