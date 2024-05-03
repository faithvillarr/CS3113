#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Entity.h"

#define LOG(argument) std::cout << argument << '\n'


Entity::Entity()
{
    m_position     = glm::vec3(0.0f);
    m_velocity     = glm::vec3(0.0f);
    m_acceleration = glm::vec3(0.0f);
    
    m_movement = glm::vec3(0.0f);
    m_speed    = 0;
    
    m_model_matrix = glm::mat4(1.0f);
}

Entity::~Entity()
{
    delete [] m_animation_up;
    delete [] m_animation_down;
    delete [] m_animation_left;
    delete [] m_animation_right;
    delete [] m_walking;
}

void Entity::draw_sprite_from_texture_atlas(ShaderProgram *program, GLuint texture_id, int index)
{
    // Step 1: Calculate the UV location of the indexed frame
    float u_coord = (float) (index % m_animation_cols) / (float) m_animation_cols;
    float v_coord = (float) (index / m_animation_cols) / (float) m_animation_rows;
    
    // Step 2: Calculate its UV size
    float width = 1.0f / (float) m_animation_cols;
    float height = 1.0f / (float) m_animation_rows;
    
    // Step 3: Just as we have done before, match the texture coordinates to the vertices
    float tex_coords[] =
    {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };
    
    float vertices[] =
    {
        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
    };
    
    // Step 4: And render
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::ai_activate(float delta_time)
{
    float move_y = get_movement().y, 
          move_x = get_movement().x;
    if (get_movement().y < 0) {
         m_animation_indices = m_walking[DOWN];
    }
    else if (get_movement().y > 0) {
        m_animation_indices = m_walking[UP];
    }
    if (get_movement().x > 0) {
        m_animation_indices = m_walking[RIGHT];
    }
    else if (get_movement().x < 0) {
        m_animation_indices = m_walking[LEFT];
    }
    switch (m_ai_type)
    {
        case WALKER:
            ai_walker();
            break;
            
        case ROUND:
            ai_round(delta_time);
            break;
            
        default:
            break;
    }
}

void Entity::ai_walker()
{
    if (m_position.x < 7) {
        m_movement.x = 1.0f;
    }
    else if (m_position.x > 16) {
        m_movement.x = -1.0f;
    }
}

void Entity::ai_round(float delta_time) {
    static float move_time = 1.0f; // how long moving
    static float wait_time = 0.5f; // how long wait
    static float timer = 0.0f; // 
    static bool is_moving = false;

    timer += delta_time; 

    if (!is_moving) {
        if (timer >= wait_time) {
            timer = 0.0f;
            is_moving = true;

            int direction = rand() % 4; // 0-3 

            switch (direction) {
            case 0: // up
                m_movement.x = 0.0f;
                m_movement.y = 1.0f;
                break;
            case 1: // down
                m_movement.x = 0.0f;
                m_movement.y = -1.0f;
                break;
            case 2: // right
                m_movement.x = 1.0f;
                m_movement.y = 0.0f;
                break;
            case 3: // left
                m_movement.x = -1.0f;
                m_movement.y = 0.0f;
                break;
            }
        }
        else {
            m_movement = glm::vec3(0.0f);
        }
    }
    else if (is_moving) {
        if (timer >= move_time) {
            // reset timer 
            timer = 0.0f;
            is_moving = false;
        }
    }
}



Entity * Entity::update(float delta_time, Entity *player, Entity *objects, int object_count, Map *map)
{
    Entity * res = nullptr;
    if (!m_is_active) return res;
    if (get_entity_type() == LIVES || get_entity_type() == HOUSE) {
         m_model_matrix = glm::mat4(1.0f);
         m_model_matrix = glm::translate(m_model_matrix, m_position);
         return res;
    }
 
    m_collided_top    = false;
    m_collided_bottom = false;
    m_collided_left   = false;
    m_collided_right  = false;
    
    if (m_entity_type == ANIMAL) ai_activate(delta_time);
    
    if (m_animation_indices != NULL)
    {
        if (glm::length(m_movement) != 0)
        {
            m_animation_time += delta_time;
            float frames_per_second = (float) 1 / SECONDS_PER_FRAME;
            
            if (m_animation_time >= frames_per_second)
            {
                m_animation_time = 0.0f;
                m_animation_index++;
                
                if (m_animation_index >= m_animation_frames)
                {
                    m_animation_index = 0;
                }
            }
        }
    }
    
    // Our character moves from left to right, so they need an initial velocity
    m_velocity.x = m_movement.x * m_speed;
    m_velocity.y = m_movement.y * m_speed;
    
    // Now we add the rest of the gravity physics
    m_velocity += m_acceleration * delta_time;
    
    m_position.y += m_velocity.y * delta_time;
    Entity * res1 = check_collision_y(objects, object_count);
    check_collision_y(map);

    m_position.x += m_velocity.x * delta_time;
    Entity * res2 = check_collision_x(objects, object_count);
    check_collision_x(map);
    
    // Jump
    if (m_is_jumping)
    {
        // STEP 1: Immediately return the flag to its original false state
        m_is_jumping = false;
        
        // STEP 2: The player now acquires an upward velocity
        m_velocity.y += m_jumping_power;
    }
    
    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);

    if (res1) return res1;
    if (res2) return res2;
    return res;
}

Entity* const Entity::check_collision_y(Entity *collidable_entities, int collidable_entity_count)
{
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity *collidable_entity = &collidable_entities[i];
        
        if (check_collision(collidable_entity))
        {
            float y_distance = fabs(m_position.y - collidable_entity->get_position().y);
            float y_overlap = fabs(y_distance - (m_height / 2.0f) - (collidable_entity->m_height / 2.0f));
            if (y_overlap > 0) {
                m_collided_bottom = true;
                m_collided_top = true;
                return collidable_entity;
            }
        }
    }
    if ((m_collided_top || m_collided_bottom) && m_entity_type == PLAYER) {
        LOG("Collided with Animal!");
        //m_is_active = false;
    }
    return nullptr;
}

Entity * const Entity::check_collision_x(Entity *collidable_entities, int collidable_entity_count)
{
    for (int i = 0; i < collidable_entity_count; i++)
    {
        Entity *collidable_entity = &collidable_entities[i];
        
        if (check_collision(collidable_entity))
        {
            float x_distance = fabs(m_position.x - collidable_entity->get_position().x);
            float x_overlap = fabs(x_distance - (m_width / 2.0f) - (collidable_entity->get_width() / 2.0f));
            if (x_overlap > 0) {
                m_collided_right  = true;
                m_collided_left  = true;
                return collidable_entity;
            } 
        }
    }
    if ((m_collided_left || m_collided_right) && m_entity_type == PLAYER) {
        LOG("Collided with Animal!");
        //m_is_active = false;
    }
    return nullptr;
}

void const Entity::check_collision_y(Map *map)
{
    // Probes for tiles
    glm::vec3 top       = glm::vec3(m_position.x, m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_left  = glm::vec3(m_position.x - (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_right = glm::vec3(m_position.x + (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    
    glm::vec3 bottom = glm::vec3(m_position.x, m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_left = glm::vec3(m_position.x - (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_right = glm::vec3(m_position.x + (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    
    float penetration_x = 0;
    float penetration_y = 0;
    
    if (map->is_solid(top, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_left, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_right, &penetration_x, &penetration_y) && m_velocity.y > 0)
    {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    
    if (map->is_solid(bottom, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_left, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_right, &penetration_x, &penetration_y) && m_velocity.y < 0)
    {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
}

void const Entity::check_collision_x(Map *map)
{
    // Probes for tiles
    glm::vec3 left  = glm::vec3(m_position.x - (m_width / 2), m_position.y, m_position.z);
    glm::vec3 right = glm::vec3(m_position.x + (m_width / 2), m_position.y, m_position.z);
    
    float penetration_x = 0;
    float penetration_y = 0;
    
    if (map->is_solid(left, &penetration_x, &penetration_y) && m_velocity.x < 0)
    {
        m_position.x += penetration_x;
        m_velocity.x = 0;
        m_collided_left = true;
}
    if (map->is_solid(right, &penetration_x, &penetration_y) && m_velocity.x > 0)
    {
        m_position.x -= penetration_x;
        m_velocity.x = 0;
        m_collided_right = true;
    }
}

void Entity::render(ShaderProgram *program)
{
    if (!m_is_active) return;
    
    program->SetModelMatrix(m_model_matrix);

    if (m_animation_indices == NULL && m_animation_index != -1) {
        draw_sprite_from_texture_atlas(program, m_texture_id, m_animation_index);
        return;
    }
    
    if (m_animation_indices != NULL)
    {
        draw_sprite_from_texture_atlas(program, m_texture_id, m_animation_indices[m_animation_index]);
        return;
    }
    
    float vertices[]   = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float tex_coords[] = {  0.0,  1.0, 1.0,  1.0, 1.0, 0.0,  0.0,  1.0, 1.0, 0.0,  0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

bool const Entity::check_collision(Entity *other) const
{
    // If we are checking with collisions with ourselves, this should be false
    if (other == this || other == nullptr) return false;
    
    // If either entity is inactive, there shouldn't be any collision
    if (!m_is_active || !other->m_is_active) return false;
    
    float x_distance = fabs(m_position.x - other->get_position().x) - ((m_width  + other->get_width())  / 2.0f);
    float y_distance = fabs(m_position.y - other->get_position().y) - ((m_height + other->get_height()) / 2.0f);
    
    return x_distance < 0.0f && y_distance < 0.0f;
}


void Entity::grow() { 

    if (plant_phase != EMPTY ){
        incPhase();
        if (m_animation_index % 12 < 7) m_animation_index++;
        if (m_animation_index % 12 == 7) m_animation_index--;
        set_watered(false);
    }
}