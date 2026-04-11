#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto sprite = CCSprite::createWithSpriteFrameName("GJ_playBtn_001.png");
        sprite->setScale(0.5f);

        auto btn = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MyMenuLayer::onMyCustomButton)
        );

        auto menu = this->getChildByID("main-menu");
        if (menu) {
            menu->addChild(btn);
            btn->setID("layout-button");
            menu->updateLayout();
        }

        return true;
    }

    void onMyCustomButton(CCObject* sender) {
        FLAlertLayer::create(
            "Layout Mod",
            "¡Botón funcionando!",
            "OK"
        )->show();
    }
};
