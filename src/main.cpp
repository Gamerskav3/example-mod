#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(HelloMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		// Round green button with "Hi" on it
		auto label = CCLabelBMFont::create("Hi", "bigFont.fnt");
		auto sprite = CircleButtonSprite::create(label);

		auto button = CCMenuItemSpriteExtra::create(
			sprite,
			this,
			menu_selector(HelloMenuLayer::onHelloButton)
		);
		button->setID("hello-button"_spr);

		// Prefer the bottom menu from Geode's node IDs
		if (auto bottomMenu = this->getChildByID("bottom-menu")) {
			bottomMenu->addChild(button);
			bottomMenu->updateLayout();
		}
		else {
			// Fallback: own menu in the bottom-left corner
			auto winSize = CCDirector::get()->getWinSize();
			auto menu = CCMenu::create();
			menu->setID("hello-button-menu"_spr);
			menu->setPosition({0.f, 0.f});
			button->setPosition({40.f, winSize.height * 0.5f});
			menu->addChild(button);
			this->addChild(menu);
		}

		return true;
	}

	void onHelloButton(CCObject*) {
		FLAlertLayer::create("Hello Button", "Hello!", "OK")->show();
	}
};
