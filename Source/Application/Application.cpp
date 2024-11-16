#include <pch.h>
#include <windows.h>
#include <iostream>
#include <vector>



void Application::Initialize(HMODULE _Module)
{
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    std::cout << "*************************\n";
    std::cout << "The Script is Up\n";


    InputsManager::Register(); 

    ScriptRegister(_Module, []

        {

            bool Invincible = false;
            bool Drunk = false;
            bool DeadEye = false;
            bool timeacce = false;


            while (true)
            {
                // controls menu
                if (Input::IsKeyJustPressed(KEY_F4))
                {
                    _PRINT_HELP("PRESS F4 FOR CONTROLS\n NUMPAD 1 = INVINCIBLE\n NUMPAD 2 = DRUNK\n NUMPAD 3 = INFINITE DEADEYE\n  NUMPAD 5 = TIME ACCELERATION\n NUMPAD 6 = DRUNK LASSO\n NUMPAD 9 = KILL LASSO\n", 10.0f, true, 1, 80, 0, 0, 0);
                }   



                int PlayerID = 0;
                Actor playerActor = GET_PLAYER_ACTOR(PlayerID);
                int actor = GET_LASSO_TARGET(playerActor);
                std::cout << "\r" << "actor id: " << actor << "     " << std::flush;

                





                if (Input::IsKeyJustReleased(KEY_NUMPAD_9))
                {
                    KILL_ACTOR(actor);
                   
                }




                //invincibility 
                if (Input::IsKeyJustPressed(KEY_NUMPAD_1)) {
                    if (IS_ACTOR_PLAYER(playerActor))
                    {
                        Invincible = !Invincible;
                        SET_ACTOR_INVULNERABILITY(playerActor, Invincible);
                        if (Invincible) {
                            _PRINT_SUBTITLE("<green>Invincible: On!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                        else { 
                            _PRINT_SUBTITLE("<red>Invincible: Off!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                    }
                }
                if (Invincible)
                {
                    SET_ACTOR_INVULNERABILITY(playerActor, true);
                }
                




                //drunk lasso
                if (Input::IsKeyJustPressed(KEY_NUMPAD_6))
                {
                        Drunk = !Drunk;
                        SET_ACTOR_DRUNK(actor, Drunk);
                        if (Drunk)
                        {
                            _PRINT_SUBTITLE("<green>Drunk: On!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                        else
                        {
                            _PRINT_SUBTITLE("<red>Drunk: Off!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                }


                //drunk player
                if (Input::IsKeyJustPressed(KEY_NUMPAD_2))
                {
                   if (IS_ACTOR_PLAYER(playerActor))
                    {
                        Drunk = !Drunk;
                        SET_ACTOR_DRUNK(playerActor, Drunk);
                        if (Drunk)
                        {
                            _PRINT_SUBTITLE("<green>Drunk: On!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                        else
                        {   
                            _PRINT_SUBTITLE("<red>Drunk: Off!", 0.5f, true, 1, 0, 0, 0, 0);
                        }
                    }
                }





                //deadeye
                if (Input::IsKeyJustPressed(KEY_NUMPAD_3))
                {
                    DeadEye = !DeadEye;
                    /////////SET_PLAYER_DEADEYE_POINTS(playerActor, 10.0f, DeadEye);
                    SET_INFINITE_DEADEYE(playerActor, DeadEye);
                    //SET_DEADEYE_TIMESCALE(playerActor, 0.5f);
                    if (DeadEye)
                    {
                        _PRINT_SUBTITLE("<green> Infinite DeadEye : On", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                    else
                    {
                        _PRINT_SUBTITLE("<red> Infinite DeadEye : Off", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                }
                if (DeadEye)
                {
                    SET_INFINITE_DEADEYE(playerActor, DeadEye);
                }
                //


                //time acceleration
                if (Input::IsKeyJustPressed(KEY_NUMPAD_5))
                {
                    timeacce = !timeacce;
                    if (timeacce)
                    {
                        SET_TIME_ACCELERATION(5000.0f);
                        _PRINT_SUBTITLE("Time Acceleration: On", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                    else
                    {
                        SET_TIME_ACCELERATION(30.0f);
                        _PRINT_SUBTITLE("Time Acceleration: Off", 0.5f, true, 1, 0, 0, 0, 0);
                    }
                }
                if (timeacce)
                {
                    SET_TIME_ACCELERATION(5000.0f);
                }
                //

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