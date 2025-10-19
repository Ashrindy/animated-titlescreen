#include "USMTitle.h"
#include "TitleMovie.h"
#include <iostream>

using namespace hh::fmv;
using namespace hh::fnd;
using namespace hh::game;

using namespace app::save;

GameObject* ObjUSMTitle::Create(csl::fnd::IAllocator* allocator) {
	return new (std::align_val_t(16), allocator) ObjUSMTitle{ allocator };
}

GAMEOBJECT_CLASS(ObjUSMTitle);

ObjUSMTitle::ObjUSMTitle(csl::fnd::IAllocator* allocator) : GameObject{ allocator } {
	SetLayer(19);
	SetUpdateFlag(hh::fnd::UpdatingPhase::PRE_ANIM, true);
}

void ObjUSMTitle::AddCallback(GameManager* gameManager) {
	ResourceLoader resLoader{ GetAllocator() };
	InplaceTempUri<> uri{ "titlemovie.rfl" };
	ResourceLoader::Locale locale{};
	resLoader.LoadResource(uri, ResReflection::GetTypeInfo(), 0, 0, locale);

	const char* tmpMovieName = "titlescreen";
	if (auto* refl = ResourceManager::GetInstance()->GetResource<ResReflectionT<TitleMovie>>("titlemovie")) {
		auto* titleMovie = refl->GetData();
		tmpMovieName = titleMovie->islandMovies[0];
		if (titleMovie->switchOnSave) {
			auto& saveInterface = gameManager->GetService<SaveManager>()->saveInterface;
			UserElement* userElem;
			for (auto& userElement : saveInterface->userElements)
				if (userElement->userId.id == saveInterface->userId.id)
				{
					userElem = userElement;
					break;
				}

			if (userElem) {
				for (auto& x : userElem->mainSaveHeaderData) {
					if (x.index == 0 && (x.config & 1) != 0) {
						if (x.signature == 1396790853)
							tmpMovieName = titleMovie->islandMovies[(char)x.icon];
						break;
					}
				}
			}
		}
	}

	char movieName[1024];
	snprintf(movieName, sizeof(movieName), "%s.usm", tmpMovieName);

	auto* movie = gameManager->GetService<MovieManager>();
	if (movie) {
		MovieManager::MovieSetupData setupData{ { 1,1,1 } };
		setupData.pass = 7;
		setupData.priority = 0;
		setupData.flags.bits = 58;
		movieHandle = movie->CreateMovie(movieName, &setupData, MemoryRouter::GetModuleAllocator(), 1);
	}
}

void ObjUSMTitle::RemoveCallback(GameManager* gameManager)
{
	if (!*movieHandle) return;

	auto* movie = gameManager->GetService<MovieManager>();
	if (movie)
		movie->movies.remove(movie->movies.find(movieHandle));
	hh::fnd::HandleManager<MovieHandleObj>* handleMgr = RESOLVE_STATIC_VARIABLE(hh::fnd::HandleManager<MovieHandleObj>::instance);
	movieHandle->Free();
	handleMgr->RemoveObject(*movieHandle);
}
