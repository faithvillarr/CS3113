#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH  25
#define LEVEL_HEIGHT 25
# define TILLED_COUNT 50

#define ENEMY_COUNT 4

unsigned int LEVELA_DATA[] =
{
55, 57, 68, 68, 67, 67, 56, 66, 57, 57, 55, 67, 68, 56, 68, 56, 68, 57, 66, 55, 56, 55, 66, 68, 68,
56, 67, 57, 67, 57, 68, 55, 57, 67, 67, 55, 67, 57, 68, 66, 67, 56, 67, 55, 68, 56, 57, 57, 66, 56,
68, 68, 57, 67, 56, 66, 66, 68, 55, 55, 67, 66, 66, 56, 67, 56, 67, 66, 68, 66, 55, 55, 57, 56, 67,
56, 57, 66, 57, 55, 56, 57, 57, 55, 68, 55, 55, 56, 56, 56, 56, 67, 57, 67, 56, 57, 67, 55, 66, 57,
68, 68, 66, 67, 57, 55, 66, 56, 55, 57, 67, 68, 56, 67, 66, 68, 68, 68, 66, 55, 57, 68, 57, 68, 55,
56, 66, 57, 55, 57, 56, 55, 56, 56, 57, 66, 68, 68, 55, 56, 68, 67, 55, 67, 57, 68, 56, 67, 56, 57,
68, 66, 55, 67, 66, 57, 55, 56, 66, 56, 56, 56, 56, 68, 56, 57, 66, 67, 67, 55, 56, 68, 66, 55, 55,
68, 68, 55, 57, 55, 68, 66, 68, 68, 66, 66, 66, 56, 56, 56, 55, 57, 68, 66, 68, 56, 66, 68, 67, 67,
55, 68, 66, 67, 66, 55, 56, 67, 56, 67, 68, 68, 57, 68, 56, 66, 57, 57, 57, 57, 55, 57, 67, 56, 57,
55, 68, 55, 56, 57, 55, 68, 57, 66, 67, 56, 56, 66, 56, 56, 66, 55, 67, 66, 56, 57, 68, 66, 56, 55,
68, 67, 66, 67, 67, 55, 56, 57, 56, 66, 68, 56, 57, 67, 67, 56, 55, 66, 66, 67, 68, 67, 67, 55, 67,
56, 57, 67, 57, 66, 55, 57, 57, 56, 55, 66, 57, 57, 68, 55, 56, 57, 57, 55, 66, 66, 57, 57, 55, 67,
55, 55, 55, 68, 67, 67, 55, 68, 68, 67, 56, 67, 56, 55, 56, 68, 68, 66, 55, 68, 56, 56, 68, 66, 56,
66, 57, 68, 56, 55, 66, 56, 67, 56, 66, 67, 55, 56, 68, 57, 66, 57, 57, 67, 67, 68, 57, 66, 56, 68,
66, 57, 57, 56, 56, 55, 57, 68, 55, 57, 55, 68, 56, 66, 57, 55, 57, 55, 68, 55, 67, 57, 68, 66, 67,
66, 67, 68, 66, 57, 68, 68, 56, 56, 67, 56, 56, 68, 66, 67, 56, 67, 55, 66, 55, 68, 56, 56, 66, 67,
66, 57, 67, 67, 56, 68, 55, 67, 57, 67, 66, 67, 56, 57, 68, 66, 67, 68, 68, 55, 68, 57, 56, 57, 57,
68, 68, 56, 56, 57, 67, 55, 66, 57, 57, 66, 68, 66, 68, 67, 55, 67, 57, 56, 67, 56, 67, 55, 57, 57,
56, 55, 67, 67, 56, 66, 55, 56, 67, 55, 66, 56, 67, 55, 56, 57, 67, 55, 55, 55, 57, 57, 56, 55, 57,
67, 68, 66, 57, 66, 56, 68, 68, 68, 55, 67, 67, 56, 56, 57, 66, 56, 57, 55, 68, 56, 67, 55, 56, 67,
68, 56, 68, 55, 68, 68, 67, 66, 68, 57, 57, 56, 66, 55, 68, 57, 68, 68, 66, 56, 66, 56, 55, 67, 67,
57, 56, 67, 55, 67, 56, 66, 67, 68, 57, 56, 67, 55, 68, 57, 55, 68, 56, 56, 57, 67, 66, 66, 68, 57,
68, 55, 56, 57, 67, 68, 57, 56, 67, 56, 68, 67, 67, 55, 55, 66, 68, 56, 68, 57, 66, 68, 67, 67, 55,
55, 66, 57, 67, 67, 55, 57, 55, 67, 67, 57, 57, 55, 68, 57, 67, 56, 66, 66, 66, 67, 68, 56, 68, 56,
56, 67, 68, 66, 55, 67, 56, 57, 67, 55, 56, 57, 68, 57, 56, 57, 66, 56, 68, 68, 67, 68, 68, 68, 67,
};

unsigned int LEVELA_FENCE[] =
{
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12,  1, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,  3, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  4, 12, 12, 12,
12, 12, 12,  9, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 11, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};

Entity * collided_entity;


LevelA::~LevelA()
{
    // delete house;
    delete [] m_state.enemies;
    delete [] m_state.tilled;
    
    delete [] inventory;
    delete selection;
    delete popup;
    delete coin_display;

    delete    m_state.player;
    delete    m_state.map;
    delete    m_state.grass;
    delete    m_state.fences;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
    Mix_FreeChunk(m_state.sleep_sfx);
}

void LevelA::initialise()
{
    selection = new Entity();
    selection->set_position(glm::vec3(0.0f));
    selection->set_movement(glm::vec3(0.0f));
    selection->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    selection->m_texture_id = Utility::load_texture("assets/selection-frame.png");

    m_state.next_scene_id = -1;

    GLuint grass_texture_id = Utility::load_texture("assets/SproutLands/Tilesets/Grass.png");
    m_state.grass = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, grass_texture_id, 1.0f, 11, 7);

    GLuint fence_texture_id = Utility::load_texture("assets/SproutLands/Tilesets/Fences.png");
    m_state.fences = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_FENCE, fence_texture_id, 1.0f, 4, 4);

    /* --- INVENTORY --- */
    {
        inventory = new Entity[8];
        int temp[8] = { 7, 8, 4, 5, 6, 1, 1, 1 };
        for (size_t i = 0; i < 8; i++)
        {
            inventory[i].set_entity_type(LIVES);
            inventory[i].set_position(glm::vec3(10.0f + i, -10.0f, 0.0f));
            inventory[i].set_movement(glm::vec3(0.0f));
            inventory[i].m_speed = 5.0f;
            inventory[i].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
            inventory[i].m_texture_id = Utility::load_texture("assets/inventory_sheet.png");
            inventory[i].m_animation_cols = 12;
            inventory[i].m_animation_rows = 1;
            inventory[i].m_animation_index = temp[i];

        }
    }
    /* --- HOUSE --- */
    {
        house = new Entity;
        house->set_entity_type(HOUSE);
        house->set_position(glm::vec3(9.0f, -4.0f, 0.0f));
        house->m_texture_id = Utility::load_texture("assets/house.png");
        house->set_width(5.0f);
        house->set_height(4.0f);
        house->set_entity_type(HOUSE);
    }

    /* --- POP UP --- */
    {
        popup = new Entity();
        popup->set_entity_type(LIVES);
        popup->set_position(glm::vec3(10.0f, -10.0f, 0.0f));
        popup->m_texture_id = Utility::load_texture("assets/popup.png");
        popup->m_animation_cols = 1;
        popup->m_animation_rows = 4;
        popup->m_animation_index = 0;
        popup->deactivate();
    }

    /* --- COIN DISPLAY --- */
    {
        coin_display = new Entity();
        coin_display->set_position(glm::vec3(0.0f));
        coin_display->m_texture_id = popup->m_texture_id;
        coin_display->m_animation_cols = 1;
        coin_display->m_animation_rows = 4;
        coin_display->m_animation_index = 3;
    }

    /* --- PLAYER --- */
    {
        m_state.player = new Entity();
        m_state.player->set_entity_type(PLAYER);
        m_state.player->set_position(glm::vec3(10.0f, -10.0f, 0.0f));
        m_state.player->set_movement(glm::vec3(0.0f));
        m_state.player->m_speed = 4.0f;
        m_state.player->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
        m_state.player->m_texture_id = Utility::load_texture("assets/player.png");

        m_state.player->m_walking[m_state.player->LEFT] = new int[4] { 1, 5, 9, 13 };
        m_state.player->m_walking[m_state.player->RIGHT] = new int[4] { 3, 7, 11, 15 };
        m_state.player->m_walking[m_state.player->UP] = new int[4] { 2, 6, 10, 14 };
        m_state.player->m_walking[m_state.player->DOWN] = new int[4] { 0, 4, 8, 12 };

        m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
        m_state.player->m_animation_frames = 4;
        m_state.player->m_animation_index = 0;
        m_state.player->m_animation_time = 0.0f;
        m_state.player->m_animation_cols = 4;
        m_state.player->m_animation_rows = 4;
        m_state.player->set_height(1.0f);
        m_state.player->set_width(1.0f);
    }

    /* -- TILLED SPOTS -- */
    {
        m_state.tilled = new Entity[50];
        for (size_t i = 0; i < TILLED_COUNT; i++)
        {
            m_state.tilled[i].set_entity_type(PLOT);
            m_state.tilled[i].set_position(glm::vec3(10.0f, -10.0f, 0.0f));
            m_state.tilled[i].m_texture_id = Utility::load_texture("assets/my-sprites.png");
            m_state.tilled[i].m_animation_rows = 9;
            m_state.tilled[i].m_animation_cols = 12;
            m_state.tilled[i].m_animation_index = 60;

            m_state.tilled[i].set_height(1.0f);
            m_state.tilled[i].set_width(1.0f);

        }
        m_state.tilled[0].m_animation_index = 0;
    }

    /**
     Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture("assets/my-sprites.png");
    
    m_state.enemies = new Entity[ENEMY_COUNT];
    /* --- COWS --- */
    m_state.enemies[0].set_entity_type(ANIMAL);
    m_state.enemies[0].set_ai_type(ROUND);
    m_state.enemies[0].set_ai_state(IDLE);
    m_state.enemies[0].m_texture_id = enemy_texture_id;
    m_state.enemies[0].set_position(glm::vec3(18.0f, -15.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].m_speed = 1.0f;
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    // Walking
    m_state.enemies[0].m_walking[m_state.enemies[0].LEFT] =     new int[4] { 52, 53, 54, 55 };
    m_state.enemies[0].m_walking[m_state.enemies[0].UP] =       new int[4] { 40, 41, 42, 43 };
    m_state.enemies[0].m_walking[m_state.enemies[0].DOWN] =     new int[4] { 16, 17, 18, 19};
    m_state.enemies[0].m_walking[m_state.enemies[0].RIGHT] =    new int[4] { 28, 29, 30, 31};
             
    m_state.enemies[0].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].RIGHT];  
    m_state.enemies[0].m_animation_frames = 4;
    m_state.enemies[0].m_animation_index = 52;
    m_state.enemies[0].m_animation_time = 0.0f;
    m_state.enemies[0].m_animation_cols = 12;
    m_state.enemies[0].m_animation_rows = 9;
    m_state.enemies[0].set_height(1.0f);
    m_state.enemies[0].set_width(1.0f);

    // COW #2
    m_state.enemies[1].set_entity_type(ANIMAL);
    m_state.enemies[1].set_ai_type(WALKER);
    m_state.enemies[1].set_ai_state(IDLE);
    m_state.enemies[1].m_texture_id = enemy_texture_id;
    m_state.enemies[1].set_position(glm::vec3(12.0f, -12.0f, 0.0f));
    m_state.enemies[1].set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    m_state.enemies[1].m_speed = 0.75f;
    m_state.enemies[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    // Walking
    m_state.enemies[1].m_walking[m_state.enemies[1].LEFT] =     new int[4] { 52, 53, 54, 55 };
    m_state.enemies[1].m_walking[m_state.enemies[1].UP] =       new int[4] { 40, 41, 42, 43 };
    m_state.enemies[1].m_walking[m_state.enemies[1].DOWN] =     new int[4] { 16, 17, 18, 19};
    m_state.enemies[1].m_walking[m_state.enemies[1].RIGHT] =    new int[4] { 28, 29, 30, 31};

    m_state.enemies[1].m_animation_indices = m_state.enemies[1].m_walking[m_state.enemies[1].RIGHT];
    m_state.enemies[1].m_animation_frames = 4;
    m_state.enemies[1].m_animation_index = 52;
    m_state.enemies[1].m_animation_time = 0.0f;
    m_state.enemies[1].m_animation_cols = 12;
    m_state.enemies[1].m_animation_rows = 9;
    m_state.enemies[1].set_height(1.0f);
    m_state.enemies[1].set_width(1.0f);

    /* --- SHEEP --- */
    m_state.enemies[2].set_entity_type(ANIMAL);
    m_state.enemies[2].set_ai_type(WALKER);
    m_state.enemies[2].set_ai_state(IDLE);
    m_state.enemies[2].m_texture_id = enemy_texture_id;
    m_state.enemies[2].set_position(glm::vec3(11.0f, -11.0f, 0.0f));
    m_state.enemies[2].set_movement(glm::vec3(-1, 0, 0));
    m_state.enemies[2].m_speed = 1.0f;
    m_state.enemies[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    // Walking
    m_state.enemies[2].m_walking[m_state.enemies[2].LEFT] =  new int[4] { 12, 13, 14, 15 };
    m_state.enemies[2].m_walking[m_state.enemies[2].UP] =    new int[4] { 48, 49, 50, 51 };
    m_state.enemies[2].m_walking[m_state.enemies[2].DOWN] =  new int[4] { 36, 37, 38, 39 };
    m_state.enemies[2].m_walking[m_state.enemies[2].RIGHT] = new int[4] { 24, 25, 26, 27 };

    m_state.enemies[2].m_animation_indices = m_state.enemies[2].m_walking[m_state.enemies[2].RIGHT];
    m_state.enemies[2].m_animation_frames = 4;
    m_state.enemies[2].m_animation_index = 52;
    m_state.enemies[2].m_animation_time = 0.0f;
    m_state.enemies[2].m_animation_cols = 12;
    m_state.enemies[2].m_animation_rows = 9;
    m_state.enemies[2].set_height(1.0f);
    m_state.enemies[2].set_width(1.0f);

    /* --- HOUSE IN ENEMIES --- */
    m_state.enemies[3] = *house;

    
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/cafemusic-new.mp3");
    if (!m_state.bgm) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
    }
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(10.0f);

    m_state.jump_sfx = Mix_LoadWAV("assets/coin.wav");
    if (!m_state.jump_sfx) {
        std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
    }

    m_state.sleep_sfx = Mix_LoadWAV("assets/honk mimi.wav");
    if (!m_state.sleep_sfx) {
        std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
    }
}

void LevelA::update(float delta_time)
{

    collided_entity = m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.fences);
    if (collided_entity != nullptr) popup->activate();
    else popup->deactivate();
    
    if (collided_entity == &m_state.enemies[3]) popup->m_animation_index = 1; //house
    else if (collided_entity == &m_state.enemies[2]) popup->m_animation_index = 2;//sheep
    else if (collided_entity == &m_state.enemies[1] || collided_entity == &m_state.enemies[0]) popup->m_animation_index = 0;

    
    

    float player_x = m_state.player->get_position().x;
    float player_y = m_state.player->get_position().y;

    /* INVENTORY */
    for (size_t i = 0; i < 8; i++)
    {
        float offset = (i * 0.75) - 2.5;
        inventory[i].set_position(glm::vec3(player_x + offset, player_y - 3.f, 0.0f));
        inventory[i].update(delta_time, m_state.player, NULL, 0, NULL);
        inventory[i].scale(glm::vec3(0.75, 0.75, 0.0f));
    }

    selection->set_position(inventory[inventory_slot].get_position());
    selection->update(delta_time, m_state.player, NULL, 0, m_state.fences);
    selection->scale(glm::vec3(0.75, 0.75, 0.0f));

    popup->set_position(glm::vec3(m_state.player->get_position().x, m_state.player->get_position().y + 1.25, 0.0f));
    popup->update(delta_time, m_state.player, NULL, 0, m_state.fences);
    popup->scale(glm::vec3(2.5, 1.25, 0.0f));

    coin_display->set_position(glm::vec3(m_state.player->get_position().x + 3.5, m_state.player->get_position().y + 2.5, 0.0f));
    coin_display->update(delta_time, m_state.player, NULL, 0, m_state.fences);
    coin_display->scale(glm::vec3(3, 2, 0.0));


    house->update(delta_time, m_state.player, house, 0, NULL);
    house->scale(glm::vec3(5.0, 4.0, 0.0f));

    /* SETTING TILLED */
    if (m_state.player->get_movement().x < 0) player_x = floor(player_x);
    else player_x = ceil(player_x);
    player_y = floor(player_y);
    m_state.tilled[m_state.player->get_till_index()].set_position(glm::vec3(player_x, player_y, 0.0f));
  
    m_state.tilled[m_state.player->get_till_index()].update(delta_time, m_state.player, NULL, 0, m_state.fences);

    /* ENEMY*/
    for (int i = 0; i < ENEMY_COUNT; i++)
        m_state.enemies[i].update(delta_time, m_state.player, NULL, 0, m_state.fences);

}

void LevelA::render(ShaderProgram *program)
{
    m_state.grass->render(program);
    m_state.fences->render(program);

    for (size_t i = 0; i < m_state.player->get_till_index(); i++)
    {
        m_state.tilled[i].render(program);
    }
    m_state.tilled[m_state.player->get_till_index()].render(program);

    for (int i = 0; i < ENEMY_COUNT; i++) m_state.enemies[i].render(program);
    
    house->render(program);
    
    m_state.player->render(program);

    for (size_t i = 0; i < 8; i++)
    {
         inventory[i].render(program);
    }
    selection->render(program);
    popup->render(program);
    coin_display->render(program);

    Utility::draw_text(program, 
        font_texture_id,
        std::to_string(coin_count), 
        0.5f, -0.2f, 
        glm::vec3(m_state.player->get_position().x + 3.3f, m_state.player->get_position().y + 2.5f, 0.0f));
}   

void LevelA::till() {

    int till_index = m_state.player->get_till_index();
    
    if (till_index == 49) return;
    
    std::string coord = getCord();
    
    if (tillMap.find(coord) == tillMap.end()) {
        m_state.tilled[till_index].m_animation_index = 60;
    
        tillMap.emplace(coord, &m_state.tilled[till_index]);
    
        m_state.player->inc_till_index();
        m_state.tilled[m_state.player->get_till_index()].m_animation_index = 0;
    
    }
}

std::string LevelA::water() {
    
    std::string coord = getCord();

    // see if tilled exists at that location
    auto mapped_val = tillMap.find(coord);
        //change sprite and set to watered
    if (mapped_val != tillMap.end()) { // if its in the map

        Entity* curr_entity = tillMap[coord];
        if (curr_entity->get_plant_phase() == PHASE4) {
            //collect();
            coord = "PHASE4 FOUND";
        }

        if (!curr_entity->check_watered()) {
            if (curr_entity->m_animation_index % 12 < 7) curr_entity->m_animation_index++;
            curr_entity->water();
        }

    }
    
    return coord;
}

std::string LevelA::nextDay() {
    for (size_t i = 0; i < m_state.player->get_till_index(); i++)
    {
        if (m_state.tilled[i].get_plant_phase() != EMPTY && m_state.tilled[i].check_watered()) {
            m_state.tilled[i].grow();
        }
        
    }
    for (size_t i = 0; i < ENEMY_COUNT - 1; i++)
    {
        m_state.enemies[i].set_treat_status(true);
    }
    
    Mix_PlayChannel(-1, m_state.sleep_sfx, 0);

    return std::to_string(m_state.player->get_till_index());
}

void LevelA::plant() {
    std::string coord = getCord();

    if (tillMap.find(coord) != tillMap.end()) { // if its in the map
        Entity * curr_entity = tillMap[coord];
        switch (inventory_slot) {
        case 2:
            curr_entity->m_animation_index = 72;
            curr_entity->set_plant_phase(PHASE1);
            curr_entity->set_plant_type(CARROT);
            if (curr_entity->check_watered() && curr_entity->m_animation_index % 12 < 7)
                curr_entity->m_animation_index++;
            break;
        case 3:
            curr_entity->m_animation_index = 84;
            curr_entity->set_plant_phase(PHASE1);
            curr_entity->set_plant_type(TURNIP);
            if (curr_entity->check_watered() && curr_entity->m_animation_index % 12 < 7) 
                curr_entity->m_animation_index++;
            break;
        case 4:
            curr_entity->m_animation_index = 96;
            curr_entity->set_plant_phase(PHASE1);
            curr_entity->set_plant_type(CABBAGE);
            if (curr_entity->check_watered() && curr_entity->m_animation_index % 12 < 7) 
                curr_entity->m_animation_index++;
            break;
        default:
            break;
        }
    }
}

std::string LevelA::getCord() {
    std::string str = "";
    int till_index = m_state.player->get_till_index();

    // grab coords
    float tile_x = m_state.tilled[till_index].get_position().x;
    float tile_y = m_state.tilled[till_index].get_position().y;
    std::string coord = "(" + std::to_string(tile_x) + ", " + std::to_string(tile_y) + ")";
    str += coord;

    return str;
}

std::string LevelA::collect() {
    //if popup
    if (popup->is_active()) {
        // collided_entity is a pointer to animal in question
        if (popup->m_animation_index == 0) {
            // milk
            if (collided_entity->get_treat_status()) {
                collided_entity->set_treat_status(false);
                addCoin(20);
                Mix_PlayChannel(-1, m_state.jump_sfx, 0);
            }
            popup->deactivate();
        }
        else if (popup->m_animation_index == 1) {
            // house
            nextDay();
            popup->deactivate();
        }
        else if (popup->m_animation_index == 2) {
            // sheep
            if (collided_entity->get_treat_status()) {
                collided_entity->set_treat_status(false);
                addCoin(40);
                Mix_PlayChannel(-1, m_state.jump_sfx, 0);
            }
            popup->deactivate();

        }
    }
    // else we're tryna acces a tile

    std::string coord = getCord();

    auto mapped_val = tillMap.find(coord);

    if (mapped_val != tillMap.end()) { // if its in the map
        // clear out tile.
        auto tile = tillMap[coord];
        if (tile->get_plant_phase() == PHASE4) {
            tile->m_animation_index = 60;
            tile->set_plant_phase(EMPTY);
            addCoin(30);
            Mix_PlayChannel(-1, m_state.jump_sfx, 0);
        }
    }
    return std::to_string(getCoinCount());
}
