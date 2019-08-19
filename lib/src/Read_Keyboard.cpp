#include <IO.h>

void Read_Keyboard(sf::Event event,
                   bullet_c *bullet,
                   enum moving_e *move,
                   float time)
{
    //if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code)
        {
        case sf::Keyboard::Space:
            if (!bullet->Is_Active()) {
                *move = SHOOT_BUTT;
            }
            break;
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            *move = UP_BUTT;
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            *move = LEFT_BUTT;
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            *move = DOWN_BUTT;
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            *move = RIGHT_BUTT;
            break;
        default:
            break;
        }
    //}

    //if (event.type == sf::Event::KeyReleased) {
    //    switch (event.key.code)
    //    {
    //    case sf::Keyboard::W:
    //    case sf::Keyboard::Up:
    //        is_u_pressed = false;
    //        break;
    //    case sf::Keyboard::A:
    //    case sf::Keyboard::Left:
    //        is_l_pressed = false;
    //        break;
    //    case sf::Keyboard::S:
    //    case sf::Keyboard::Down:
    //        is_d_pressed = false;
    //        break;
    //    case sf::Keyboard::D:
    //    case sf::Keyboard::Right:
    //        is_r_pressed = false;
    //        break;
    //    default:
    //        break;
    //    }
    //}

    //if (is_l_pressed) {
    //    
    //}
    //if (is_r_pressed) {
    //    
    //}
    //if (is_u_pressed) {
    //    
    //}
    //if (is_d_pressed) {
    //    
    //}
    return;
}
