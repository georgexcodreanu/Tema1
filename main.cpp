#include <iostream>
#include <string>

const std::string Player1Name = "Player 1";
const std::string Player2Name = "Player 2";
const std::string Arma1 = "Pistol";
const std::string Arma2 = "Shotgun";
const int ViataInitiala = 100;
const int DamagePistol = 20;
const int DamageShotgun = 40;
const int gloanteIncarcatorPistol = 10;
const int totalPistol = 100;
const int gloanteIncarcatorShotgun = 2;
const int totalShotgun = 1;

class Munitie
{
private:
    int gloanteTotale;
    int gloanteInIncarcator;

public:
    Munitie(int gloanteTotale, int gloanteInIncarcator)
    {
        this->gloanteTotale = gloanteTotale;
        this->gloanteInIncarcator = gloanteInIncarcator;
    }

    Munitie(const Munitie& other)
    {
        this->gloanteTotale = other.gloanteTotale;
        this->gloanteInIncarcator = other.gloanteInIncarcator;
    }

    Munitie& operator=(const Munitie& other)
    {
        if (this == &other)
        {
            return *this;
        }
        gloanteTotale = other.gloanteTotale;
        gloanteInIncarcator = other.gloanteInIncarcator;
        return *this;
    }

    void reload(int capacitateIncarcator)
    {
        if (this->gloanteTotale > capacitateIncarcator)
        {
            gloanteTotale -= capacitateIncarcator;
            gloanteInIncarcator += capacitateIncarcator;
        }
        else
        {
            gloanteInIncarcator += gloanteTotale;
            gloanteTotale = 0;

        }
    }

    bool shoot()
    {
        if (gloanteInIncarcator > 0)
        {
            gloanteInIncarcator--;
            return true;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Munitie& ammo)
    {
        os << "Munitie rezerva: " << ammo.gloanteTotale << " . Munitie in incarcator : " << ammo.gloanteInIncarcator;
        return os;
    }
};

class Arma
{
private:
    std::string nume;
    int damage;
    int capacitateIncarcator;
    Munitie ammo;

public:
    friend std::ostream& operator<<(std::ostream& os, const Arma& arma)
    {
        os << "Arma: " << arma.nume << " (Damage: " << arma.damage << ")" << std::endl;
        os << arma.ammo;
        return os;
    }

    Arma(const std::string& numeArma, int damageArma, int munitieTotala, int gloanteIncarcator) : ammo(munitieTotala, gloanteIncarcator)
    {
        this->nume = numeArma;
        this->damage = damageArma;
    }

    Arma(const Arma& other) : ammo(other.ammo)
        {
            this->nume = other.nume;
            this->damage = other.damage;
            this->ammo = other.ammo;
        }

    Arma& operator=(const Arma& other)
    {
        if (this == &other)
        {
            return *this;
        }
        nume = other.nume;
        damage = other.damage;
        ammo = other.ammo;
        return *this;
    }

    bool fire()
    {
        if (ammo.shoot())
        {
            std::cout << "trage cu " << nume << " pentru " << damage << " damage!" << std::endl;
            return true;
        }

        std::cout<<"reincarca... ";
        this->ammo.reload(this->capacitateIncarcator);

        if (ammo.shoot())
        {
            std::cout << "trage cu " << nume << " pentru " << damage << " damage!" << std::endl;
            return true;
        }
        else
        {
            std::cout << " nu mai are gloante " << std::endl;
            return false;
        }
    }

    int getDamage() const
    {
        return damage;
    }


};

class Player
{
private:
    std::string nume;
    int viata;
    Arma arma;

public:

    std::string getNume() const
    {
        return nume;
    }

    int getViata() const
    {
        return viata;
    }

    Player(const std::string& numeJucator, const Arma& armaJucator) : arma(armaJucator)
        {
            this->nume = numeJucator;
            this->viata = ViataInitiala;
        }

    Player(const Player& other) : arma(other.arma)
        {
            this->nume = other.nume;
            this->viata = other.viata;
        }

    Player& operator=(const Player& other)
    {
        if (this == &other)
        {
            return *this;
        }
        nume = other.nume;
        viata = other.viata;
        arma = other.arma;
        return *this;
    }

    ~Player()
    {
        std::cout << nume << " a iesit din joc." << std::endl;
    }

    void shoot(Player& target)
    {
        std::cout << "Jucatorul " << this->nume << " ";
        if (arma.fire())
        {
            target.takeDamage(arma);
        }
    }

    void takeDamage(const Arma& armaAtacator)
    {
        int damage = armaAtacator.getDamage();
        viata -= damage;
        std::cout << nume << " pierde " << damage << " viata!" << std::endl;
    }

    bool inViata() const
    {
        return viata > 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player)
    {
        os << player.nume << " viata : " << player.viata << std::endl;
        os << player.arma;
        return os;
    }

};

int main()
{

    Arma pistol(Arma1, DamagePistol, totalPistol, gloanteIncarcatorPistol);
    Arma shotgun(Arma2, DamageShotgun, totalShotgun, gloanteIncarcatorShotgun);

    Player player1(Player1Name, pistol);
    Player player2(Player2Name, shotgun);

    std::cout << player1 << std::endl << std::endl;
    std::cout << player2 << std::endl << std::endl;

    while (player1.inViata() && player2.inViata())
    {
        player1.shoot(player2);
        std::cout << "Jucatorul " << player2.getNume() << " mai are " << player2.getViata() << " viata." << std::endl << std::endl;
        if (!player2.inViata())
        {
            std::cout << player1.getNume() << " castiga!" << std::endl;
            break;
        }


        player2.shoot(player1);
        std::cout << "Jucatorul " << player1.getNume() << " mai are " << player1.getViata() << " viata." << std::endl << std::endl;

        if (!player1.inViata())
        {
            std::cout << player2.getNume() << " wins!" << std::endl;
            break;
        }
    }

    return 0;
}
