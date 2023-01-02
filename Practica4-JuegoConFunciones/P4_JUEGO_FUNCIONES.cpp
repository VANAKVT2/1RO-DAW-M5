#include <iostream>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#include<mmsystem.h>

using namespace std;

/*HERO ATRIBUTES*/
string heroname;
int heroHP = 1000;
int heroDMG = 25;
int heromagicDMG;
int heroSPD = 25;
bool heroalive;
int magiccounter = 3;

/*GOBLIN ATRIBUTES (enemy with crit possibility)*/
string goblinname = "Goblin";
int goblinHP = 120;
int goblinDMG = 60;
int goblinSPD = 20;
int goblincrit = goblinDMG;/*DMG SAVER TO CRIT POSIBILITY CREATED IN MAIN FUNCTION*/
bool goblinalive;

/*WIZARD ATRIBUTES (enemy with random magic damage)*/
string wizardname = "Wizard";
int wizardHP = 250;
int wizardDMG;
int wizardSPD = 0; /*I personally want the wizard to be always the last one to move*/
bool wizardalive;

/*GENERAL ATRIBUTES*/
int turns = 0;
int enemyselect = 0;
int critposibility;
int attackselect = 0;

void gamestarter() {

    PlaySound(TEXT("START.wav"), NULL, SND_ASYNC);

    /*Initzializing random numbers*/
    srand(time(NULL));
    

    /*Introducing the name of the hero*/
    cout << "What's the name of the hero?\n";
    cin >> heroname;



    /*Initzializing alive stat for active entities*/
    goblinalive = true;
    heroalive = true;
    wizardalive = true;



}

int wizardaahero() {
    heroHP = heroHP - wizardDMG;
    return heroHP;
}

int goblinaahero() {
    heroHP = heroHP - goblinDMG;
    return heroHP;
}

int heroaawizard() {
    wizardHP = wizardHP - heroDMG;
    return wizardHP;
}

int heroaagoblin() {
    goblinHP = goblinHP - heroDMG;
    return goblinHP;
}

void gamestarter2(){
    turns++;
    system("cls");
    cout << "WIZARD HP ||" << wizardHP << "||\n";
    cout << "GOBLIN HP ||" << goblinHP << "||\n";
    cout << heroname << " ||" << heroHP << "||\n";
    cout << "--------------------------\n";
    /*RANDOM GENERATORS*/
    critposibility = (1 + rand() % 100);

    /*RANDOM DMG FOR WIZARD*/
    wizardDMG = (1 + rand() % 175);

    /*RANDOM MAGIC DMG FOR HERO*/
    heromagicDMG = (1 + rand() % 130);

    /*RANDOM DMG FOR GOBLIN*/
    if ((turns > 1) && (critposibility >= 0) && ((critposibility == (32, 51, 36, 97, 23, 12, 57, 87, 53, 86)))) {
        goblinDMG = goblinDMG * 1.75;
        cout << "The goblin makes a critical attack!\n";

    }

    /*TURN CHECKER*/
    cout << "TURN " << turns << "\n";

    /*SPEED SYSTEM DECLARING ON GOBLIN*/
    if ((turns == 1) && (heroSPD >= goblinSPD)) {
        cout << "You are faster than the " << goblinname << " so you attack first\n";
    }
    else if ((turns == 1) && (heroSPD <= goblinSPD)) {
        cout << "You are slower than the " << goblinname << ", he attacks first\n";
    }

}

void attackselecting(){
    /*HERO ATTACK SELECTOR*/
    
    cout << "How do you want to attack?\n";
    cout << "[1]-FISTS\n[2]-SWORD\n[3]-MAGIC (" << magiccounter << " magical attacks resting)\n";
    cin >> attackselect;
    PlaySound(TEXT("menuselect.wav"), NULL, SND_ASYNC);

    while ((attackselect != 1) && (attackselect != 2) && (attackselect != 3)) {
        cout << "Please input numbers 1, 2 , or 3, to attack.\n";
        cin >> attackselect;
        PlaySound(TEXT("menuselect.wav"), NULL, SND_ASYNC);

    }


    /*WHEN MAGIC IS NOT 0 YOU CAN ATTACK WITH MAGIC*/
    if (magiccounter != 0) {
        switch (attackselect) {
        case 1:
            cout << "You are attacking with your fists!\n";
            heroDMG = 20;
            break;
        case 2:
            cout << "You are attacking with your sword\n";
            heroDMG = 50;
            break;
        case 3:
            cout << "You are attacking with magic!\n";
            heroDMG = heromagicDMG;

        }
    }

    /*WHEN MAGIC COUNTER IS 0 YOU CANNOT ATTACK WITH MAGIC*/
    if (magiccounter == 0) {
        while (attackselect == 3) {
            cout << "You used all your magic! Select another attack\n";
            cin >> attackselect;
            PlaySound(TEXT("menuselect.wav"), NULL, SND_ASYNC);
        }
        while ((attackselect != 1) && (attackselect != 2)) {
            cout << "That attack does not exist!\n";
            cin >> attackselect;
            PlaySound(TEXT("menuselect.wav"), NULL, SND_ASYNC);
        }
        switch (attackselect) {
        case 1:
            cout << "You attack with your fists!\n";
            heroDMG = 20;
            break;
        case 2:
            cout << " You attack with your sword\n";
            heroDMG = 50;
            break;
        }

    }

}

int enemyselecting() {
    if ((goblinHP >= 1) && (wizardHP >= 1)) {
        cout << "Who do you want to attack?\n" << "[1]-WIZARD\n[2]-GOBLIN\n";
        cin >> enemyselect;
        PlaySound(TEXT("menuselect.wav"), NULL, SND_ASYNC);
        while ((enemyselect != (1)) && (enemyselect != (2))) {
            cout << "You can only write 1 or 2 to select the enemy, the value you introduced is not valid\n";
            cin >> enemyselect;
            PlaySound(TEXT("menuselect.wav"), NULL, SND_ASYNC);
        }
    }

    /*YOU CANT SELECT AN ENEMY THAT IS DEAD*/
    else if ((goblinHP >= 1) && (wizardHP <= 0)) {
        cout << "The dead corpse of the wizard smells badly\n";
        enemyselect = 2;
    }
    else if ((goblinHP <= 0) && (wizardHP >= 1)) {
        cout << "The dead corpse of the goblin smells badly\n";
        enemyselect = 1;
    }
    return enemyselect;
}

boolean goblinfightback() {
    if (goblinHP >= 1) {
        cout << "The enemy is still alive, with " << goblinHP << " health points, and it fights back with" << goblinDMG << " attack points\n";
        goblinaahero();

        /*IT FIGHTS BACK BUT YOU SURVIVE*/
        if (heroHP >= 1) {
            cout << "You survive the attack of the " << goblinname << " with " << heroHP << " HP\n";
            bool heroalive = true;
        }

        /*IT FIGHTS BACK AND YOU DIE*/
        else if (heroHP <= 0) {
            cout << "The " << goblinname << "gets to stomp you.\n";
            bool heroalive = false;
        }
    }
    return heroalive;
}

boolean heroattackgoblin() {
    if ((enemyselect == 2) && (goblinalive = true)) {
        heroaagoblin();
        cout << "You attack the " << goblinname << " with " << heroDMG << " attack points.\n";

        /*YOU SELECT TO ATTACK GOBLIN BUT IT SURVIVES AND FIGHTS BACK*/
        goblinfightback();

        /*GOBLIN DIES FROM YOUR PREVIOUS ATTACK*/
        if (goblinHP <= 0) {
            cout << "The " << goblinname << " dies by your hands\n";
            bool goblinalive = false;
        }

        /*WIZARD ATTACKS AFTER GOBLIN AND HERO*/
        cout << "The " << wizardname << " attacks (" << wizardDMG << " magic damage)\n";
        wizardaahero();

        /*YOU SURVIVE THE WIZARD'S ATTACK AND FIGHT BACK*/
        if (heroHP > 0) {
            cout << "The attack of the wizard was not strong enough to end you! (" << heroHP << " health points remaining)\n You fight back!\n";
            

            /*WIZARD SURVIVES YOUR COUNTER ATTACK*/
            if (wizardHP > 0) {
                cout << "The wizard is still alive. (" << wizardHP << " health points)\n";
            }

            /*WIZARD DIES FROM YOUR COUNTER ATTACK*/
            else if (wizardHP <= 0) {
                cout << "The wizard dies";
                wizardalive = false;
            }
        }   
    }
    return wizardalive;
    return goblinalive;
    return heroalive;
}

boolean heroattackwizard() {
    if ((enemyselect == 1) && (wizardHP > 0)) {
        cout << "The " << wizardname << " receives your attack! (" << heroDMG << " attack damage)\n";
        heroaawizard();

        /*WIZARD DIES FROM YOUR ATTACK*/
        if (wizardHP <= 0) {
            cout << "The wizard dies";
            wizardalive = false;
        }

        /*WIZARD SURVIVES AND FIGHTS BACK*/
        else if (wizardHP >= 1) {
            cout << "The wizard survives and casts a spell on you! (" << wizardDMG << " magic damage)\n";
            wizardaahero();

            /*WIZARD KILLS YOU ON COUNTERATTACK*/
            if (heroHP <= 0) {
                cout << "You die\n";
                heroalive = false;
            }

            /*YOU SURVIVE WIZARD'S ATTACK*/
            else if (heroHP >= 1) {
                cout << "You survive the attack of the evil wizard with " << heroHP << " health points\n";
            }
        }

        /*THE GOBLIN ATTACKS AFTER YOU*/
        if (goblinHP > 0) {
            cout << "The enemy " << goblinname << " attacks you with " << goblinDMG << " attack points.\n";
            goblinaahero();

            /*YOU FIGHT BACK IF SURVIVING THE HIT*/
            if (heroHP >= 1) {
                cout << "You survive the hit on " << heroHP << " HP, and you fight back!\n";
                heroaagoblin();

                /*GOBLIN SURVIVES COUNTER ATTACK*/
                if (goblinHP >= 1) {
                    cout << "Enemy survives with " << goblinHP << " health points\n";
                }

                /*GOBLIN DOES NOT SURVIVE THE COUNTER ATTACK*/
                else if (goblinHP <= 0) {
                    cout << "The " << goblinname << " dies.\n";
                    bool goblinalive = false;
                }

            }
        }
        }

    /*HERO DOES NOT SURVIVE THE HIT*/
    if (heroHP <= 0 && goblinHP >= 1) {
        cout << "The " << goblinname << " absolutely ends you\n";
        bool heroalive = false;
    }
    return heroalive;
    return goblinalive;
    return wizardalive;

}

boolean wizardturn() {
    if ((wizardHP > 0) && (heroHP > 0)) {
        cout << "The wizard finally attacks! (" << wizardDMG << " magic damage)\n";
        wizardaahero();

        /*WIZARD DOES NOT KILL YOU*/
        if (heroHP <= 0) {
            cout << "Hero dies\n";
            heroalive = false;
        }

        /*WIZARD KILLS YOU*/
        if (heroHP >= 1) {
            cout << "You survive the attack of the wizard (" << heroHP << " health points remaining)\n";
        }
   
    }
    return heroalive;
}

boolean herofightback(){
    if (heroHP >= 1) {
        cout << "You survive the hit on " << heroHP;
        cout << " HP, and you fight back!\n";
        heroaagoblin;

        /*GOBLIN SURVIVES THE COUNTER ATTACK*/
        if (goblinHP > 0) {
            cout << "Enemy survives with " << goblinHP << " health points\n";
        }

        /*GOBIN DIES FROM HERO'S COUNTER ATTACK*/
        else if (goblinHP <= 0) {
            cout << "The " << goblinname << " dies.\n";
            bool goblinalive = false;
        }
    } return goblinalive;
}

boolean goblinturn() {
    if (goblinHP >= 0) {
        cout << "The enemy " << goblinname << " attacks you with " << goblinDMG << " attack points.\n";
        goblinaahero();
        /*HERO SURVIVES AND FIGHTS BACK*/
        herofightback();

        /*HERO DOES NOT SURVIVE THE ATTACK OF THE GOBLIN*/
        if (heroHP <= 0) {
            cout << "The" << goblinname << " absolutely ends you\n";
            bool heroalive = false;

        }
    }
    return heroalive;
}

void endgame() {

    /*EXIT PROGRAM IF HERO DEAD OR ALL ENEMIES DEAD*/
    if ((heroHP <= 0)) {
        cout << "GAME OVER";
    }
    if ((wizardHP <= 0) && (goblinHP <= 0)) {
        cout << "GAME OVER";
    }
    if (attackselect == 3) {
        magiccounter = magiccounter - 1;
    }
    system("pause");
    cout << "Press Any Key to go to next Turn";
}

int main() {

    gamestarter();

    /*RPG TURN SYSTEM CREATING*/
    while ((goblinHP >= 1) || (wizardHP >= 1) && (heroHP >= 1)) {

        gamestarter2();

        attackselecting();

        /*ENEMY SELECTOR*/
        enemyselecting();

        /*FIGHT SYSTEM ON GOBLIN*/

        /*IF HERO IS FASTER THAN THE GOBLIN*/
        if (heroSPD >= goblinSPD) {
            heroSPD = 0;
            goblinSPD = 100;

            /*IF YOU SELECT TO ATTACK GOBLIN*/
           
            heroattackgoblin();

            /*IF YOU SELECT TO ATTACK WIZARD*/
            
            heroattackwizard();

            /*GOBLIN'S TURN*/

            goblinturn();

            /*WIZARD'S TURN*/
           
            wizardturn();
        }

        /*IF HERO IS SLOWER THAN THE GOBLIN*/
        else if (heroSPD <= goblinSPD) {
            heroSPD = 100;
            goblinSPD = 0;

            /*THE GOBLIN ATTACKS*/

            goblinturn();

                /*IF U SELECTED GOBLIN*/

            heroattackgoblin();            

            /*IF U SELECTED WIZARD*/
          
            heroattackwizard();

            /*WIZARD'S TURN*/

            wizardturn();
        }

        /*RESET DAMAGE FOR GOBLIN IF THIS TURN MATE ATTACKED CRITICALLY*/
        if (turns > 1) {
            goblinDMG = goblincrit;
        }
        endgame();

    }

}