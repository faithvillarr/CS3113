#include "Scene.h"
#include <unordered_map>

class LevelA : public Scene {
private:
    std::string getCord();
    int coin_count = 0;
public:
    GLuint font_texture_id = Utility::load_texture("assets/font1.png");
    int ENEMY_COUNT = 4;
    int inventory_slot = 0;

    // string : entity pointer
    std::unordered_map<std::string, Entity*> tillMap;

    Entity* inventory;
    Entity* selection;
    Entity* house;
    Entity* popup;
    Entity* coin_display;
    
    ~LevelA();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override; 

    void till();    
    std::string water();
    void plant();
    std::string collect();

    std::string nextDay();

    int addCoin(int val) { coin_count += val; return coin_count; }
    int getCoinCount() { return coin_count; }
};
