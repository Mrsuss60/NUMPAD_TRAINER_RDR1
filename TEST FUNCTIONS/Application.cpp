#include <pch.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>


using namespace UNSORTED;
using namespace HEALTH;





void Application::Initialize(HMODULE _Module)
{
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    std::cout << "****************\n";
    std::cout << "The Script is Up\n";
    std::cout << "****************\n";


    InputsManager::Register(); 

    ScriptRegister(_Module, []

        {
            bool Invincible = false;
            bool Drunk = false;
            bool DeadEye = false;
            bool timeacce = false;
            bool weatherr = false;
            bool changeModel = false;
            bool LoopFire = false;
            bool ExplodingLasso = false;

            // Drunk/kill Lasso variable
            bool setLassoTargetDrunk = false;
            bool KillLassoTarget = false;


            int FireHandle = FIRE_CREATE_HANDLE();


            PRINT_HELP_B(
                "PRESS F4 FOR CONTROLS\n"
                "<blue>NUMPAD 1 = INVINCIBLE\n"
                "<blue>NUMPAD 2 = DRUNK\n"
                "<blue>NUMPAD 3 = INFINITE DEADEYE\n"
                "<blue>NUMPAD 4 = TIME ACCELERATION\n"
                "<blue>NUMPAD 7 = DRUNK LASSO\n"
                "<blue>NUMPAD 8 = KILL LASSO\n",
                10.0f, true, 1, 0, 0, 0, 0
            );



            while (true)
            {
                // controls menu
                if (Input::IsKeyJustPressed(KEY_F4))
                {
                    PRINT_HELP_B(
                        "PRESS F4 FOR CONTROLS\n"
                        "<blue>NUMPAD 1 = INVINCIBLE\n"
                        "<blue>NUMPAD 2 = DRUNK\n"
                        "<blue>NUMPAD 3 = INFINITE DEADEYE\n"
                        "<blue>NUMPAD 4 = TIME ACCELERATION\n"
                        "<blue>NUMPAD 7 = DRUNK LASSO\n"
                        "<blue>NUMPAD 8 = KILL LASSO\n",
                        10.0f, true, 1, 0, 0, 0, 0
                    );
                
                }       

                // Get player actor
                int PlayerID = 0;
                Actor playerActor = GET_PLAYER_ACTOR(PlayerID);

                //invincibility 
                if (Input::IsKeyJustPressed(KEY_NUMPAD_1)) {
                    if (IS_ACTOR_PLAYER(playerActor))
                    {
                        Invincible = !Invincible;
                        SET_ACTOR_INVULNERABILITY(playerActor, Invincible);
                        if (Invincible) {
                            PRINT_OBJECTIVE_B("<green>Invincible: On!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                        else {
                            PRINT_OBJECTIVE_B("<red>Invincible: Off!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                    }
                }
                if (Invincible)
                {
                    SET_ACTOR_INVULNERABILITY(playerActor, true);
                }
                

                // Drunk Lasso
                if (Input::IsKeyJustPressed(KEY_NUMPAD_7))
                {
                    setLassoTargetDrunk = !setLassoTargetDrunk;
                    if (setLassoTargetDrunk)
                    {
                        PRINT_OBJECTIVE_B("<green>Drunk Lasso: On!", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                    else
                    {
                        PRINT_OBJECTIVE_B("<red>Drunk Lasso: Off!", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                }
                Actor lassotarget = GET_LASSO_TARGET(playerActor);
                SET_ACTOR_DRUNK(lassotarget, setLassoTargetDrunk);

                // Kill Lasso Target
                if (Input::IsKeyJustPressed(KEY_NUMPAD_8))
                {
                    KillLassoTarget = !KillLassoTarget;
                    if (KillLassoTarget)
                    {
                        PRINT_OBJECTIVE_B("<green>Kill Lasso Target: On!", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                    else
                    {
                        PRINT_OBJECTIVE_B("<red>Kill Lasso Target: Off!", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                }
                if (KillLassoTarget)
                {
                    Actor lassotarget = GET_LASSO_TARGET(playerActor);
                    KILL_ACTOR(lassotarget);
                }


                // Drunk Player
                if (Input::IsKeyJustPressed(KEY_NUMPAD_2))
                {
                    if (IS_ACTOR_PLAYER(playerActor))
                    {
                        Drunk = !Drunk;
                        SET_ACTOR_DRUNK(playerActor, Drunk);
                        if (Drunk)
                        {
                            PRINT_OBJECTIVE_B("<green>Drunk: On!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                        else
                        {
                            PRINT_OBJECTIVE_B("<red>Drunk: Off!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                    }
                }


                // Deadeye
                if (Input::IsKeyJustPressed(KEY_NUMPAD_3))
                {
                    DeadEye = !DeadEye;
                    SET_INFINITE_DEADEYE(playerActor, DeadEye);
                    if (DeadEye)
                    {
                        SET_PLAYER_DEADEYE_MODE(playerActor, DeadEye);
                        ADD_PLAYER_DEADEYE_POINTS(playerActor, 10, true);
                        PRINT_OBJECTIVE_B("<green> Infinite DeadEye : On", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                    else
                    {
                        PRINT_OBJECTIVE_B("<red> Infinite DeadEye : Off", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                }
                if (DeadEye)
                {
                    
                    SET_INFINITE_DEADEYE(playerActor, DeadEye);
                }

                // Time Acceleration
                if (Input::IsKeyJustPressed(KEY_NUMPAD_4))
                {
                    timeacce = !timeacce;
                    if (timeacce)
                    {
                        SET_TIME_ACCELERATION(5000.0f);
                        PRINT_OBJECTIVE_B("Time Acceleration: On", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                    else
                    {
                        SET_TIME_ACCELERATION(30.0f);
                        PRINT_OBJECTIVE_B("Time Acceleration: Off", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                }
                if (timeacce)
                {
                    SET_TIME_ACCELERATION(5000.0f);
                }


                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                Layout layout = GET_AMBIENT_LAYOUT();


                if (Input::IsKeyJustPressed(KEY_F2))
                {
                    Vector3 coords = GET_OBJECT_POSITION(playerActor);
                    Vector3 rot;
                    GET_OBJECT_ORIENTATION(playerActor, &rot);
                    const char* actorname = std::to_string(rand()).c_str();
                    ActorModel Acspawn = ACTOR_MPPLAYER_DLC01;

                    CREATE_ACTOR_IN_LAYOUT(layout, actorname, Acspawn , Vector2{ coords.x, coords.y }, coords.z, Vector2{ rot.x, rot.y }, 10.0f);

                    PRINT_OBJECTIVE_B("NPC", 0.5f, true, 0, 0, 0, 0, 0);
                }


                
                if (Input::IsKeyJustPressed(KEY_NUMPAD_0))
                {
                    changeModel = !changeModel;
                   if (changeModel)
                    {

                        Vector3 coords = GET_OBJECT_POSITION(playerActor);
                        Vector3 rot;
                        GET_OBJECT_ORIENTATION(playerActor, &rot);
                        const char* actorname = "actor";
                        ActorModel Acspawn = ACTOR_MPPLAYER01;

                        _CHANGE_ACTOR_MODEL_IN_LAYOUT(layout, playerActor, actorname, Acspawn, Vector2{ coords.x, coords.y }, coords.z, Vector2{ rot.x, rot.y }, 0.0f, 0);
                        int playrID = Acspawn;
                        Actor camera1 = GET_PLAYER_ACTOR(playrID);
                        SET_CAMERA_FOLLOW_ACTOR(camera1);
                        SET_PLAYER_CONTROL(playrID, true, 0, 0);
                        PRINT_OBJECTIVE_B("NPC", 0.5f, true, 0, 0, 0, 0, 0);
                   }
#if 1
                else
                {
                    Vector3 coords = GET_OBJECT_POSITION(playerActor);
                    Vector3 rot;
                    GET_OBJECT_ORIENTATION(playerActor, &rot);
                    const char* actorname = "actor";
                    ActorModel Acspawn = ACTOR_PLAYER;

                    _CHANGE_ACTOR_MODEL_IN_LAYOUT(layout, playerActor, actorname, Acspawn, Vector2{ coords.x, coords.y }, coords.z, Vector2{ rot.x, rot.y }, 0.0f, 0);
                    int playrID = Acspawn;
                    Actor camera1 = GET_PLAYER_ACTOR(playrID);
                    SET_CAMERA_FOLLOW_ACTOR(camera1);
                    SET_PLAYER_CONTROL(playrID, true, 0, 0);
                }
#endif




                }


                //weather
                if (Input::IsKeyPressed(KEY_NUMPAD_PERIOD) && Input::IsKeyJustPressed(KEY_NUMPAD_ENTER))
                {
                    weatherr = !weatherr;
                    if (weatherr)
                    {
                        SET_WEATHER(WEATHER_STORMY, 0.0F);
                        SET_RAIN_AMOUNT(100.0f);
                        SET_LIGHTNING_AMOUNT(1000000.0f); //  SET_LIGHTNING_AMOUNT
                        PRINT_OBJECTIVE_B("Rainy", 1.0f, true, 1, 0, 0, 0, 0);
                        
                    }

                    else
                    {
                        SET_WEATHER(WEATHER_CLEAR, 0.0f);
                        SET_RAIN_AMOUNT(0.0f);
                        PRINT_OBJECTIVE_B("clear", 1.0f, true, 1, 0, 0, 0, 0);
                    }
                }


                //FIRE
                bool firedamage = false;
                if (Input::IsKeyJustPressed(KEY_NUMPAD_PLUS))
                {
                    LoopFire = !LoopFire;
                    if (LoopFire)
                    {
                        FIRE_CREATE_ON_ACTOR(FireHandle, playerActor); // create fire on actor
                        FIRE_SET_DAMAGE_ALLOWED(FireHandle, firedamage); // fire damage
                        FIRE_SET_GROW_RATE(FireHandle, 9999.9f); // fire grow rate
                    }
                    else
                    {

                    }
                }
                if(LoopFire)
                {
                    FIRE_CREATE_ON_ACTOR(FireHandle, playerActor); // create fire on actor
                    FIRE_SET_DAMAGE_ALLOWED(FireHandle, firedamage); // fire damage
                    FIRE_SET_GROW_RATE(FireHandle, 9999.9f);
                }

                
#if 0
                int Zoomed = IS_PLAYER_WEAPON_ZOOMED(playerActor);
                bool Shooting = IS_ACTOR_SHOOTING(playerActor);
                Vector3 Excoords;
                if (Zoomed)
                {
                    GET_RETICLE_TARGET_POINT(playerActor,&Excoords);
                        if (Shooting)
                        {
                            _CREATE_EXPLOSION(&Excoords, "CannonballExplosion", 1, &Excoords, 1);
                        }
                }
#endif


#if 1
                bool WZoomed = IS_PLAYER_WEAPON_ZOOMED(playerActor);
                bool AShooting = IS_ACTOR_SHOOTING(playerActor);
                Vector3 Excoords;
                float heading = GET_HEADING(playerActor);
                int Height = GET_ACTOR_HEIGHT(playerActor);

                if (WZoomed)
                {
                    GET_RETICLE_TARGET_POINT(playerActor,&Excoords);
                    Excoords.z -= Height;
                        if (AShooting)
                        {
                            //_CREATE_EXPLOSION(&Excoords, "CannonballExplosion", 10, &Excoords, 10);
                            
                            TELEPORT_ACTOR_WITH_HEADING(playerActor, &Excoords, heading, false, false, false);
                        }
                }
#endif


                if (Input::IsKeyJustPressed(KEY_F1))
                {
                    ExplodingLasso = !ExplodingLasso;
                    if (ExplodingLasso)
                    {

                        PRINT_OBJECTIVE_B("Boom lasso!: On", 0.5f, true, 0, 0, 0, 0, 0);
                    }
                    else
                    {
                        PRINT_OBJECTIVE_B("Boom lasso!: Off", 0.5f, true, 0, 0, 0, 0, 0);
                    }
                }
                if (ExplodingLasso)
                {
                    Actor lassotarget = GET_LASSO_TARGET(playerActor);
                    Vector3 coords = GET_OBJECT_POSITION(lassotarget);
                    _CREATE_EXPLOSION(&coords, "CannonballExplosion", 1, &coords, 1);
                }





               WAIT(0);

            }
        });
}


void Application::Shutdown(HMODULE _Module)
{
    ScriptUnregister(_Module);
    std::cout << "Game is Closed";
    FreeConsole();
    InputsManager::Unregister();
}
