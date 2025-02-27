#include "USMTitle.h"
#include <iostream>

using namespace hh::fnd;
using namespace hh::game;

void* ObjUSMTitle::GetRuntimeTypeInfo()
{
	return nullptr;
}

bool ObjUSMTitle::ProcessMessage(hh::fnd::Message& message)
{
	return true;
}

GameObject* ObjUSMTitle::Create(csl::fnd::IAllocator* allocator) {
	return new (std::align_val_t(16), allocator) ObjUSMTitle{ allocator };
}

const GameObjectClass ObjUSMTitle::gameObjectClass{
	"USMTitle",
	"USMTitle",
	sizeof(ObjUSMTitle),
	&ObjUSMTitle::Create,
	0,
	{},
	nullptr,
};

ObjUSMTitle::ObjUSMTitle(csl::fnd::IAllocator* allocator) : GameObject{ allocator } {
	SetLayer(19);
	SetUpdateFlag(hh::fnd::UpdatingPhase::PRE_ANIM, true);
}

const GameObjectClass* ObjUSMTitle::GetClass() {
	return &gameObjectClass;
}

void ObjUSMTitle::AddCallback(hh::game::GameManager* gameManager)
{
	auto* movie = gameManager->GetService<hh::fmv::MovieManager>();
	if (movie) {
		hh::fmv::MovieManager::MovieSetupData setupData{};
		setupData.unkvector = { 1,1,1 };
		setupData.pass = 7;
		setupData.priority = 0;
		setupData.flags.bits = 58;
		movieHandle = movie->CreateMovie("titlescreen.usm", &setupData, hh::fnd::MemoryRouter::GetModuleAllocator(), 1);
	}
}

void ObjUSMTitle::RemoveCallback(hh::game::GameManager* gameManager)
{
	auto* movie = gameManager->GetService<hh::fmv::MovieManager>();
	if (movie)
		movie->movies.remove(movie->movies.find(movieHandle));
	hh::fnd::HandleManager<hh::fmv::MovieHandleObj>* handleMgr = RESOLVE_STATIC_VARIABLE(hh::fnd::HandleManager<hh::fmv::MovieHandleObj>::instance);
	movieHandle->Free();
	handleMgr->RemoveObject(*movieHandle);
}