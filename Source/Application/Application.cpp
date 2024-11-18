#include <pch.h>
#include <windows.h>
#include <iostream>
#include <vector>



using namespace UNSORTED;
using namespace HEALTH;


void Application::Initialize(HMODULE _Module)
{
	
	//logging
	#if 1
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    std::cout << "****************\n";
    std::cout << "The Script is Up\n";
    std::cout << "****************\n";
	#endif

    InputsManager::Register(); 

    ScriptRegister(_Module, []

        {
            bool Invincible = false;
            bool Drunk = false;
            bool DeadEye = false;
            bool timeacce = false;

            // Drunk/kill Lasso variable
            bool setLassoTargetDrunk = false;
            bool KillLassoTarget = false;

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

                WAIT(0);

            }
        });
}


void Application::Shutdown(HMODULE _Module)
{
    ScriptUnregister(_Module);
	
	#if 1
    std::cout << "Game is Closed";
    FreeConsole();
	#endif
	
    InputsManager::Unregister();
}