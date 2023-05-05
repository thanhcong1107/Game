#include <iostream>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
//#include <ctime>
//===========================================================================================================================
class HEROS{
        char *name;
        int health;
        int level;
        int gold;
        int damage;
        int shield;
        int dodgeRate;

        public:
        HEROS();
        HEROS(char*);
		void showInfo()
		{
			std::cout << "Status: " << std::endl;
			std::cout << std::setw(5) << std::left << "HP : " << std::setw(5) << std::left << health << std::endl;
			std::cout << std::setw(5) << std::left << "Damage : " << std::setw(5) << std::left << damage << std::endl;
			std::cout << std::setw(5) << std::left << "Shield : " << std::setw(5) << std::left << shield << std::endl;
			std::cout << std::setw(5) << std::left << "Gold : " << std::setw(5) << std::left << gold << std::endl;
		}
        friend class GAME;
        friend class SHOPEE;
};
HEROS::HEROS()
{
    level = 1;
    health = 8;
    damage = 2;
    shield = 0;
    dodgeRate = 0;
    gold = 0;
}

HEROS::HEROS(char *_name){
    name = _name;
    level = 1;
    health = 8;
    damage = 2;
    shield = 0;
    dodgeRate = 0;
    gold = 0;
}
//===========================================================================================================================
class MONSTER{
        char *name;
        int health;
        int goldKeeped;
        int damage;
        int dogdeRate;

        public:
        MONSTER(int);
        void pirntInfo();
        friend class GAME;
    };
MONSTER::MONSTER(int random){
    if (random == 0){
        char *_name = "Dragon";
        name = _name;
        health = 20;
        damage = 4;
        goldKeeped = 100;
        dogdeRate = 15;
    }

    else if (random == 1){
        char* _name = "Orc";
        name = _name;
        health = 10;
        damage = 4;
        goldKeeped = 50;
        dogdeRate = 8;
    }

    else if (random == 2){
        char* _name = "Crocodile";
        name = _name;
        health = 7;
        damage = 3;
        goldKeeped = 20;
        dogdeRate = 1;
    }

    else if (random == 3){
        char* _name = "Slime";
        name = _name;
        health = 1;
        damage = 1;
        goldKeeped = 10;
        dogdeRate = 0;
    }
}

void MONSTER::pirntInfo()
{
    std::cout << *name << " " << health << " " << goldKeeped;
}
//===========================================================================================================================
class SHOPEE{
        int buffAttack;
        int buffAttackPrice;
        int buffDefense;
        int buffDefensePrice;

        public:
        SHOPEE();
        void buyAttack(HEROS&);
        void buyDefense(HEROS&);
        void buy(HEROS&);
    };

SHOPEE::SHOPEE()
{
    buffAttack = 1;
    buffDefense = 1;
    buffAttackPrice = 10;
    buffDefensePrice = 10;
}

void SHOPEE::buyAttack (HEROS &hero)
{
    if (hero.gold < buffAttackPrice){
        std::cout << "\nNot enough gold";
        return;
    }
    hero.gold -= buffAttackPrice;
    hero.damage += buffAttack;

    buffAttackPrice += 5;
}

void SHOPEE::buyDefense (HEROS &hero)
{
    if (hero.gold < buffDefensePrice){
        std::cout << "\nNot enough gold";
        return;
    }
    hero.gold -= buffDefensePrice;
    hero.shield += buffDefense;

    buffDefensePrice += 5;
}

void SHOPEE::buy(HEROS &hero)
{
    std::cout << "\n-----------------------------\n";
    hero.showInfo();
    std::cout << "\nWant to buy something ??";
    std::cout << "\n1.Attack - (+" << buffAttack << " )dame - " << buffAttackPrice << " gold";
    std::cout << "\n2.Defense - (+" << buffDefense << " )shield - " << buffDefensePrice << " gold";
    std::cout << "\n3.No";
    std::cout << "\nChoose: ";
    int choose;
    std::cin >> choose;

    if (choose == 1){
        std::cout << "Buy Attack!";
        buyAttack (hero);
        //std::cout << "Done !!";
        //hero.showInfo();
    }
    else if (choose == 2){
        std::cout << "Buy Defense\n";
        buyDefense (hero);
        //std::cout << "Done !!";
    }

    else{
        std::cout << "Sad :( \n";
    }
}
//=========================================================================================================
class GAME{
        public:
        bool heroRun(HEROS&, const MONSTER&);
        bool ifRunSucess();
        void heroAttack(const HEROS&, MONSTER&);
        void monsterAttack(HEROS&, const MONSTER&);
        

        bool heroWin (HEROS&, const MONSTER&);
        bool monsterWin (const HEROS&, const MONSTER&);
        
        void aGameRound (HEROS&, MONSTER&);
        void runGame(HEROS &hero);
    };
bool GAME::ifRunSucess()
{
    srand(time(NULL));
    int ifDogde = rand();

    if (ifDogde & 1)
        return true;
    
    return false;
}

bool GAME::heroRun(HEROS &hero, const MONSTER &monster)
{
    if (ifRunSucess()){
        std::cout << "Run Successfully";
        hero.level += 1;
        hero.health += 3;
        hero.gold += monster.goldKeeped;
        return true;
    }

    else{
        std::cout << "Run Failed\n";
        hero.health -= monster.damage;
        return false;
    }
}

void GAME::heroAttack(const HEROS &hero, MONSTER &monster)
{
    srand(time(NULL));
    int monsterDodged = rand() % 100;

    if (monsterDodged < monster.dogdeRate)
        {std::cout << "Hero Attacks - Monster Dodged\n";
		sleep(1.5); } 
    else{
        std::cout << "Hero Attacks - Hitted\n";
        sleep(1.5);
        monster.health -= hero.damage;
    }
}

void GAME::monsterAttack(HEROS &hero, const MONSTER &monster)
{
    srand(time(NULL));
    int herosDodged = rand() % 100;

    if (herosDodged < hero.dodgeRate)
        {std::cout << "\nMonster Attacks - Hero Dodged";
        sleep(1.5);}
    else{
        if (hero.shield > monster.damage)
            {std::cout << "\nMonster Attacks - Hero Blocks";
            sleep(1.5);}
        else{
            std::cout << "\nMonster Attacks - Hitted";sleep(1);
            hero.health -= (monster.damage - hero.shield);
        }
    }
}

bool GAME::heroWin (HEROS &hero, const MONSTER &monster)
{
    if (monster.health <= 0){
        if (hero.level == 20){
            std::cout << "WIN !!!!!\n";
            std::cout << "Gold: " << hero.gold;
            exit(1);
        }

        else{
            std::cout << "\nTo next round :>";
        }

        hero.level += 1;
        hero.damage +=1;
        hero.health += 3;
        hero.gold += monster.goldKeeped;

        return true;
    }

    return false;
}

bool GAME::monsterWin (const HEROS &hero, const MONSTER &monster)
{
    if (hero.health <= 0){
        std::cout << "You Lose :>\n";
        std::cout << "Your level: " << hero.level;
        std::cout << "\nYour gold: " << hero.gold;
        return true;
    }

    return false;
}

void GAME::aGameRound(HEROS &hero, MONSTER &monster)
{
    std::cout << "\nFight against " << monster.name << "\n";

    char key;
    std::cout << "Run (R) or Fight (F): "; std::cin >> key;
    if (key == 'r' || key == 'R'){
         bool sucess = heroRun(hero, monster);
         if (sucess)
            return;
    }

    //if Hero runs failed
    int round = 1;
    while (1){
        std::cout << "Round " << round++ << "\n";
        heroAttack(hero, monster);
        std::cout << "Hero health: " << hero.health;
        std::cout << "- Monster health: " << monster.health;
        sleep(1.5);
        if (heroWin(hero, monster))
            break;

        monsterAttack (hero, monster);
        std::cout << "\nHero health: " << hero.health;
        std::cout << "- Monster health: " << monster.health << "\n";
        sleep(1.5);
        if (monsterWin(hero, monster))
            exit(1);
    }

}

void GAME::runGame (HEROS &hero)
{
    SHOPEE shop;

    srand(time(NULL));
    while (1){
        int createMonster = rand()%10;
        if (createMonster >= 0 && createMonster < 5){
            MONSTER monster(3);
            aGameRound (hero, monster);
        }

        else if (createMonster >= 5 && createMonster < 7){
            MONSTER monster(2);
            aGameRound (hero, monster);
        }

        else if (createMonster >= 7 && createMonster < 9){
            MONSTER monster(1);
            aGameRound (hero, monster);
        }

        else if (createMonster == 9){
            MONSTER monster(0);
            aGameRound (hero, monster);
        }

        shop.buy(hero);
    }
}
//===========================================================================================================================



int main()
{
    GAME game;
    char name[10] = "Virgo";
    HEROS hero(name);

    char monsterName[10] = "Orc";
    MONSTER monster (1);
    game.runGame (hero);
    return 0;
}












