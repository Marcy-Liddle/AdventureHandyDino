#include "userInterface.h"

 userInterface::userInterface()
{
     //"C:\Users\Marcy\105_solo_project\Coursework\CMP105App\gfx\UI_spritsheet.png"
     //if (!m_UITexture.loadFromFile("gfx/UI_spriteSheet.png"))
     if (!m_UITexture.loadFromFile("C:/Users/Marcy/105_solo_project/Coursework/CMP105App/gfx/UI_spritsheet.png"))
        Utils::printMsg("No UI ", MessageType::ERROR);

     m_banner.setTexture(&m_UITexture);
     m_banner.setTextureRect({ {6,206} , {252 , 36} });
     m_banner.setSize({ 504,72 });
     m_banner.setPosition({ 10,10 });


     int originX = 7;
     int originY = 672;
   
     for (int i = 0; i <3; i++)
     {
         sf::RectangleShape newIcon;
         newIcon.setTexture(&m_UITexture);
         newIcon.setSize({ 32, 32 });

         newIcon.setTextureRect({ {originX + (i *16),originY} , {16,16}});
         m_heartIcons.push_back(newIcon);

         newIcon.setTextureRect({ {originX + (i * 16),originY + 16} , {16,16} });
         m_energyIcons.push_back(newIcon);

         newIcon.setTextureRect({ {originX + (i * 16),originY +32} , {16,16} });
         m_levelIcons.push_back(newIcon);
     }
     
     m_energyIcons[1].setTextureRect({{167,703},{16,16}});

  }

 void userInterface::drawUI(sf::RenderWindow& window, Player& player)
 {


     // step one: get the references
     sf::View world_view = window.getView();
     sf::Vector2f middle = world_view.getCenter();
     sf::Vector2f vSize = world_view.getSize();

     // step two: set to default view
     window.setView(window.getDefaultView());


     float cornerX = 28;
     float cornerY = 30;
     window.draw(m_banner);

     float activeHearts = player.getCurrentHealth() / 5;
     int activeEnergy = player.dashAmount();
     bool isDashing = player.isDashing();
     int currentLevel = player.getLevel();

     int icon = 0;



     for (int i = 0; i < 5; i++)
     {
         sf::RectangleShape heart;
         if (i <= activeHearts)
         {
             heart = m_heartIcons[0];
         }
         else
         {
             heart = m_heartIcons[2];
         }
    

    
         heart.setPosition({ cornerX + (32.f * i)  , cornerY });
         window.draw(heart);
         //Utils::printMsg(std::to_string(heart.getPosition().x) , MessageType::DEBUG);
         
     }



     for (int i = 0; i < 3; i++)
     {
         sf::RectangleShape energy;
         if (isDashing)
         {
             energy = m_energyIcons[1];
 
         }
         else if (i <= activeEnergy)
         {
             energy = m_energyIcons[0];
         }
         else
         {
             energy = m_energyIcons[2];
         }
         energy.setPosition({ (cornerX * i) + 192.f, cornerY });
         window.draw(energy);
         icon +=i;

       // Utils::printMsg(std::to_string(energy.getPosition().x)), MessageType::DEBUG);

     }


     for (int i = 0; i < 6; i++)
     {
         sf::RectangleShape star;
         if (i <= currentLevel)
         {
             star = m_levelIcons[0];
         }
         else
         {
             star = m_levelIcons[2];
         }
         star.setPosition({ (cornerX * icon) + 288.f , cornerY });
        window.draw(star);
         icon = +i;

         //Utils::printMsg(std::to_string(star.getPosition().x) + "," + std::to_string(star.getPosition().y), MessageType::DEBUG);

     }


     //Utils::printMsg("End");
    window.setView(world_view);
}
