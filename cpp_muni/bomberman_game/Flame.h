#pragma once

#include "GameObjectBase.h"
#include "Config.h"
#include "Playground.h"

/**
 * Should destroy itself after a specific amount of ticks.
 */
class Flame : public GameObjectBase {
public:
	Flame();

	/* < IGameObject > */
	void visit(IObjectVisitor &visitor) override;
	void visit(IConstObjectVisitor &visitor) const override;
	void position(Position const &value) override;
	Position const &position() const override;
	TextureRef const &texture() const override;
	void texture(TextureRef const &texture) override;
	/* </IGameObject > */

	void gameTick() override;

	int ticksRemain();

private:
	Position position_{};
	TextureRef texture_;
	int tickstilldie;
};
