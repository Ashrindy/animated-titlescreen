#include <TitleMovie.h>

using namespace hh::fnd;

CAPTION_ATTRIBUTE(switchOnSave)
CAPTION_ATTRIBUTE(islandMovies)

const RflClassMember members[]{
	RFL_MEMBER(switchOnSave, TitleMovie, BOOL),
	RFL_MEMBER_ARRAY(islandMovies, TitleMovie, STRING, 7)
};

RFL_CLASS(TitleMovie);

void* constructTitleMovie(void* instance, csl::fnd::IAllocator* allocator) {
	auto* self = static_cast<TitleMovie*>(instance);
	self->switchOnSave = false;
	new (&self->islandMovies[0]) csl::ut::VariableString{ "titlescreen", allocator };
	for (auto x = 1; x < 7; x++) new (&self->islandMovies[x]) csl::ut::VariableString{ allocator };
	return self;
}

void finishTitleMovie(void* instance) {
	auto* self = static_cast<TitleMovie*>(instance);
	for (auto x = 0; x < 7; x++) self->islandMovies[x].~VariableString();
}

void cleanTitleMovie(void* instance) {
}

RFL_TYPE_INFO(TitleMovie)
