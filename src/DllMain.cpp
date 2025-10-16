#include "USMTitle.h"
#include <TitleMovie.h>

using namespace hh::fnd;
using namespace hh::game;

void HideBackground(hh::game::GameObject* self) {
	if (auto* scene = self->GetComponent<hh::ui::GOCSprite>()->GetProject()->GetScene("ui_title"))
		if (auto* layer = scene->GetLayer("Mainlayout"))
			if (auto* cast = layer->GetCast("obj_bg"))
				for (auto* y : cast->children) {
					y->flags |= 0x1000;
					y->transform->dirtyFlag.SetCellAll();
					y->transform->dirtyFlag.SetTransformAll();
				}
}

HOOK(uint64_t, __fastcall, GameModeBootInit, 0x1401AADF0, app::game::GameMode* self) {
	auto res = originalGameModeBootInit(self);
	registerRFL<TitleMovie>();
	return res;
}

HOOK(void, __fastcall, UITitleAddCallback, 0x140AD08E0, hh::game::GameObject* self, hh::game::GameManager* mgr) {
	originalUITitleAddCallback(self, mgr);

	auto* obj = GameObject::Create<ObjUSMTitle>(mgr->GetAllocator());
	WorldPosition pos{};
	mgr->AddGameObject(obj, "USMTitle", false, &pos, nullptr);

	HideBackground(self);
}

BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD reason, _In_ LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		INSTALL_HOOK(GameModeBootInit);
		INSTALL_HOOK(UITitleAddCallback);
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
