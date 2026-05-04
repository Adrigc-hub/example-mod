#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

// --- CLASE DEL BOTÓN MOVIBLE ---
class IAButtonMovible : public CCMenuItemSpriteExtra {
public:
    bool m_estaArrastrando = false;

    static IAButtonMovible* create(CCNode* sprite) {
        auto ret = new IAButtonMovible();
        if (ret && ret->init(sprite, nullptr, ret, menu_selector(IAButtonMovible::alTocar))) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    // Lo que pasa al tocar el botón (sin arrastrar)
    void alTocar(CCObject*) {
        if (!m_estaArrastrando) {
            // Ventana simple para la interfaz de IA
            FLAlertLayer::create(
                "IA EDITOR", 
                "Escribe tu comando (ej: 'decora este layout')\n[Funcionalidad de IA en desarrollo]", 
                "OK"
            )->show();
        }
    }

    // Lógica para mover el botón con el dedo
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event) override {
        m_estaArrastrando = true;
        
        // Convertir la posición del toque al espacio del menú
        CCPoint puntoMapa = this->getParent()->convertTouchToNodeSpace(touch);
        this->setPosition(puntoMapa);
    }

    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event) override {
        CCMenuItemSpriteExtra::ccTouchEnded(touch, event);
        
        // Pequeño delay para que no se abra la ventana justo al dejar de arrastrar
        this->scheduleOnce(schedule_selector(IAButtonMovible::resetArrastre), 0.1f);
    }

    void resetArrastre(float dt) {
        m_estaArrastrando = false;
    }
};

// --- INYECTAR EL BOTÓN EN EL EDITOR ---
class $modify(MyEditorUI, EditorUI) {
    bool init(LevelEditorLayer* editor) {
        if (!EditorUI::init(editor)) return false;

        // Crear el aspecto visual (Texto "IA")
        auto etiqueta = CCLabelBMFont::create("IA", "bigFont.fnt");
        etiqueta->setScale(0.6f);
        etiqueta->setColor({ 0, 255, 255 }); // Color cyan para que resalte

        // Crear el botón usando nuestra clase especial
        auto btnIA = IAButtonMovible::create(etiqueta);
        
        // Crear el contenedor (Menú)
        auto menuIA = CCMenu::create();
        menuIA->addChild(btnIA);
        
        // Posición inicial (puedes cambiarla después moviéndolo en el juego)
        menuIA->setPosition({ 100, 150 });
        menuIA->setID("ia-helper-menu"_spr);

        // Añadir el menú a la interfaz del editor
        this->addChild(menuIA, 1000); 

        return true;
    }
};
