#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "car.h"
#include "Traffic.h"
#include "Bullet.h"

class Player : public Car 
{
	private:
		sf::Text tScore;
		sf::Font font;
		int score;

		sf::Vector2f topLeftCorner;
		sf::Vector2f topRightCorner;
		sf::Vector2f bottomLeftCorner;
		sf::Vector2f bottomRightCorner;
		sf::VertexArray* collisionArea;

		static int lvl;
		///sf::Vector2i dirY;

		int bulletAmount = 0;
		int bulletMaxAmount = 5;
		std::vector<Bullet> bullet;
		bool reloading;

	public:
		Player(float sX = 12.0, float sY = 0.0);

		virtual void setTexture() { tCar.loadFromFile("sprites/car1.png"); }
		void setText();
		sf::Text getText() { return tScore; }
	
		void lvlUp();
		static int getLvl() { return lvl; }

		virtual void startPoint(sf::Vector2i, int);
		virtual void moveCar(sf::Vector2i, float);

		void calculateSpriteVertexes();
		void showCollisionArea();
		sf::VertexArray getCollisionArea() { return *collisionArea; }

		bool collisionSAT(std::vector<Traffic*>);

		void scoreUp() { score++; }
		int getPoints() { return score; }

		/// shooting methods *------------------------------------------------------------------------------------------------------------------------------
		void shoot();
		void reload(float dt);
		void bulletMove(sf::Vector2i, float dt); /// tego nie powino byc chyba wgl. To powinna byc metoda klasy Game
		int getBulletSize() { return bullet.size(); } /// tego tez chyba nie powinno wgl byc
		sf::CircleShape& getBulletSprite(int i) { return bullet[i].getBullet(); }
		sf::CircleShape& getMagazine() { return magazine; }
		
		void setReloading(bool logic) { reloading = logic; }
		bool getReloading() { return reloading; }

		Bullet& getBulletObj(int i) { return bullet[i]; }
		vector<Bullet>& getBulletVect() { return bullet; }
		/// *------------------------------------------------------------------------------------------------------------------------------------------------
};

#endif
