#include <rangers-sdk.h>
#include "USMTitle.h"

using namespace hh::fnd;
using namespace hh::game;

HOOK(void, __fastcall, UITitleAddCallback, 0x140AD08E0, hh::game::GameObject* self, hh::game::GameManager* mgr) {
	originalUITitleAddCallback(self, mgr);

	auto* obj = GameObject::Create<ObjUSMTitle>(mgr->GetAllocator());
	WorldPosition pos{};
	mgr->AddGameObject(obj, "USMTitle", false, &pos, nullptr);
	auto* scene = self->GetComponent<hh::ui::GOCSprite>()->GetProject()->GetScene("ui_title");
	auto* layer = scene->GetLayer("Mainlayout");
	for (auto* x : layer->casts[0]->children)
		if (strcmp(x->castData->name, "obj_bg") == 0) {
			for (auto* y : x->children) {
				y->flags |= 0x1000;
				y->transform->dirtyFlag.SetCellAll();
				y->transform->dirtyFlag.SetTransformAll();
			}
			break;
		}
}

BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD reason, _In_ LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		INSTALL_HOOK(UITitleAddCallback);
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
