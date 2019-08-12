#include <SFML/Graphics.hpp>
#include <map.h>
#include <cursedtanks.h>
#include <iostream>
#include <malloc.h>
#include <server.h>

#define SIZE_SERV sizeof(serv)

pthread_mutex_t recv_msg;

using namespace sf;

int main()
{
    float time;
    Clock clock;

// INITIAL INET_________________________________________________

    char serv_ip[IP_LENGTH];
    char serv_port[PORT_LENGTH];
    struct sockaddr_in serv;
    socklen_t serv_len = SIZE_SERV;

    int sock;
    char number;
    int ret;

    pthread_t tid;

    struct info_to_player_s info;
    struct info_to_server_s sending;
    struct msg_to_recv_s msg;

    pthread_mutex_init(&recv_msg, NULL);

//get info to connect server
    Get_IP((char*)"91.196.245.199", serv_ip);
    Get_Port((char*)"12345", serv_port);

    serv.sin_family = AF_INET;
    inet_pton(AF_INET, serv_ip, &(serv.sin_addr.s_addr));
    serv.sin_port = htons(atoi(serv_port));

//connect to server's thread
    ret = Connect_To_Server(&sock, &serv, &serv_len, &number);
    if (ret == -1) {
        perror("connect to server");
        return 0;
    }
    sending.cli_num = number;
    msg.cli_num = number;
    printf("%d\n", number);

//get start info
    msg.socket = sock;
    msg.info = &info;

    serv_len = SIZE_SERV;
    if (recvfrom(msg.socket, (char *) &info, sizeof(info), MSG_WAITALL,
                 (struct sockaddr *)&serv, &serv_len) < 1) {
                    perror("recv message from server");
                    return 0;
    }
// !INITIAL INET_________________________________________________


// Initial window
    RenderWindow window(VideoMode(704, 704), "CursedTanks");
    View view(FloatRect(0,0,352,352));
    window.setView(view);

// Initial map sprite
    char **micro_tile = NULL;
    micro_tile =(char** ) malloc(sizeof(char*) * SIZE_MICRO_MAP_Y);
    for (int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
            micro_tile[i] = (char* ) malloc(sizeof(char) * SIZE_MICRO_MAP_X);
    }
    Image map_image;
    Texture map_texture;
    Sprite map_sprite;
    map_image.loadFromFile("textures/texture_map.png");
    map_image.createMaskFromColor(Color(0,0,0,255), 0);
    map_texture.loadFromImage(map_image);
    map_sprite.setTexture(map_texture);
    map_sprite.setTextureRect(sf::IntRect(336, 0, 4, 4));
    for(int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
        memcpy(micro_tile[i], info.map[i], SIZE_MICRO_MAP_X);
    }
    msg.map = micro_tile;

// Initial world object's sprites
    tank_s tmp_tank;
    bullet_s tmp_bullet;
    Color color(255,255,255);
    tank_c tanks[NUM_CLIENTS];
    bullet_c bullets[NUM_CLIENTS];
    for(int i = 0; i < NUM_CLIENTS; i++) {
        tanks[i].Init("textures/texture_map.png", info.tanks[i].coord.x,
                      info.tanks[i].coord.y, i, info.tanks[i].direct);
        tanks[i].Set_Speed(0.020);
        tanks[i].Set_Health(info.tanks[i].health);

        bullets[i].Init("textures/texture_map.png", 0, 0,
                        info.bullets[i].direct);
        bullets[i].Set_Active(0);
        bullets[i].Set_Speed(0.075);
    }
    msg.tanks = tanks;
    msg.bullets = bullets;
//create recv thread
    pthread_create(&tid, NULL, Recv_From_Server, &msg);
// Game cycle
    while (window.isOpen()) {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed){
                window.close();
            }
            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Space) {
                    if (!bullets[(int)number].Is_Active()) {
                        Spawn_Bullet(event, tanks[(int)number],
                                     &bullets[(int)number]);
                        bullets[(int)number].Set_Speed(0.075);
                    }
                }
            }
        }
        Read_Keyboard(&tanks[(int)number], time);
        Validate_Tank(micro_tile, &tanks[(int)number]);
        Handling_Bullet(&bullets[(int)number], time);
        Validate_Bullet(micro_tile, bullets, tanks, NUM_CLIENTS, number);
//Mutex_IN
        pthread_mutex_lock(&recv_msg);
//fill map
        for(int i = 0; i < SIZE_MICRO_MAP_Y; i++) {
            memcpy(&(sending.map[i]), micro_tile[i], SIZE_MICRO_MAP_X);
        }
//fill tank info
        tanks[(int)number].Get_Structure(&tmp_tank);
        memcpy(&(sending.tank), &(tmp_tank), SIZE_TANK);
//fill bullet info
        bullets[(int)number].Get_Structure(&tmp_bullet);
        memcpy(&(sending.bullet), &(tmp_bullet), SIZE_BULLET);
//Mutex_OUT
        pthread_mutex_unlock(&recv_msg);
        if (tanks[(int)number].Get_Health() > 0)
            Send_To_Server(sock, &serv, &serv_len, &sending);
        window.clear();
        Draw_Map(&window, micro_tile, map_sprite);
        Draw_Objects(&window, tanks, bullets, NUM_CLIENTS);
        for(int i = 0; i < NUM_CLIENTS; i++) {
            Draw_First_Plan(&window, map_sprite, micro_tile,
                            tanks[i].sprite.getPosition(), 16);
            Draw_First_Plan(&window, map_sprite, micro_tile,
                            bullets[i].sprite.getPosition(), 4);
        }
        window.display();
    }

    pthread_cancel(tid);
// Free memory
    for (int i =0; i < SIZE_MICRO_MAP_Y; i++) {
        free(micro_tile[i]);
    }
    free(micro_tile);

    return 0;
}
