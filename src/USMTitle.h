#pragma once
#include <rangers-sdk.h>

using namespace hh;

class ObjUSMTitle : public hh::game::GameObject {
public:
	virtual void* GetRuntimeTypeInfo() override;
	virtual bool ProcessMessage(hh::fnd::Message& message) override;
	virtual void AddCallback(hh::game::GameManager* gameManager) override;
	virtual void RemoveCallback(hh::game::GameManager* gameManager) override;

	hh::fnd::Handle<hh::fmv::MovieHandleObj> movieHandle;

	GAMEOBJECT_CLASS_DECLARATION(ObjUSMTitle);
};