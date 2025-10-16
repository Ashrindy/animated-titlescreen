#pragma once

class ObjUSMTitle : public hh::game::GameObject {
public:
	hh::fnd::Handle<hh::fmv::MovieHandleObj> movieHandle;

	virtual void AddCallback(hh::game::GameManager* gameManager) override;
	virtual void RemoveCallback(hh::game::GameManager* gameManager) override;

	GAMEOBJECT_CLASS_DECLARATION(ObjUSMTitle);
};
