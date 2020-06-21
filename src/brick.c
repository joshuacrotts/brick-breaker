#include "../include/brick.h"

static void update_brick_status(entity_t *);
static char* get_string_enum(enum Brick);


entity_t* 
add_brick(float x, float y, uint32_t flags, int8_t identifier) {
    entity_t *b;
    b = malloc(sizeof(entity_t));
    memset(b, 0, sizeof(entity_t));
    
    b->x = x;
    b->y = y;
    b->id_flags |= ID_DEFAULT_BRICK_MASK;
    b->flags |= flags;
    b->life = 4;
    b->identifier = identifier;

    char* str_identifier = get_string_enum(identifier);
    char buffer[MAX_BUFFER_SIZE];

    // Firstly, load in the animation file.
    memset(buffer, 0, MAX_BUFFER_SIZE);
    strcat(buffer, "res/img/brick/");
    strcat(buffer, str_identifier);
    strcat(buffer, "/");
    strcat(buffer, str_identifier);
    strcat(buffer, "_animated.png");

    b->animation = add_spritesheet(buffer, 7, random_float(0.05f, 0.111f), 0, 0);
    memset(buffer, 0, MAX_BUFFER_SIZE);
    
    // Now, load in the default image file.
    memset(buffer, 0, MAX_BUFFER_SIZE);
    strcat(buffer, "res/img/brick/");
    strcat(buffer, str_identifier);
    strcat(buffer, "/");
    strcat(buffer, str_identifier);
    strcat(buffer, "_0.png");
    b->texture[0] = load_texture(buffer);
    
    memset(buffer, 0, MAX_BUFFER_SIZE);

    // Next, load in the three files for the damage image.
    for (int i = 1; i <= MAX_DEBRIS_IMGS; i++) {
        char intBuffer[3];
        itoa(i, intBuffer, 10);
        strcat(buffer, "res/img/brick/");
        strcat(buffer, str_identifier);
        strcat(buffer, "/");
        strcat(buffer, str_identifier);
        strcat(buffer, "_");
        strcat(buffer, intBuffer);   
        strcat(buffer, "_damaged.png");
        b->texture[i] = load_texture(buffer);
        
        memset(buffer, 0, MAX_BUFFER_SIZE);
    }

    SDL_QueryTexture(b->texture[0], NULL, NULL, &b->w, &b->h);
    free(buffer);
    
    return b;
}


void 
brick_update(entity_t *b) {
    int32_t randInt = random_int(1, 2000);
    if (!b->animation->cycle_once && randInt == 1 && b->life == 4) {
        b->animation->cycle_once = true;
        b->animation->flags |= ANIMATION_ACTIVE_MASK;
    }
    
    if (b->animation->cycle_once) {
        animation_update(b);
    } 

    update_brick_status(b);
}


void 
brick_draw(entity_t *b) {
    if (b->animation->cycle_once && b->life == 4) {
        animation_draw(b);
    } else {
        blit_texture(b->texture[0], b->x, b->y, false);
    }
}


void 
brick_die(entity_t *b) {
    free(b);
}


/*
 *
 */
static void 
update_brick_status(entity_t *b) {
    switch(b->life) {
        case 4: return;
        case 3: b->texture[0] = b->texture[1];
                break;
        case 2: b->texture[0] = b->texture[2];
                break;
        case 1: b->texture[0] = b->texture[3];
                break;
        case 0: b->flags |= DEATH_MASK;
                break;
    }
}


static char* 
get_string_enum(enum Brick b) {
    switch(b) {
        case RED: return "red";
        case BLUE: return "blue";
        case YELLOW: return "yellow";
        case PURPLE: return "purple";
        case ORANGE: return "orange";
        case LIGHT_BLUE: return "light_blue";
        case LIGHT_GREEN: return "light_green";
        case DARK_GREEN: return "dark_green";
        case BROWN: return "brown";
        case NULL_COLOR: return "NULL";
    }
}