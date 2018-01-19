#pragma once

#include "GUITextComponent.h"
#include "DamageableComponent.h"

#include <sstream> // stringstream

class GUITextDamageComponent : public GUITextComponent
{
public:
	GUITextDamageComponent(DamageableComponent* dmg, int renderLayer);
	~GUITextDamageComponent();

	virtual void Draw(ICamera* cam) override;

private:
	DamageableComponent *			mDamageableComponent;
};

