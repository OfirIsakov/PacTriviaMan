using JetBrains.Annotations;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class ButtonController : MonoBehaviour
{
    public void onLoginPageButtonClick()
    {
        UIManager.instance.ChangeScreen("LoginScreen");
    }
    public void onRegisterePageButtonClick()
    {
        UIManager.instance.ChangeScreen("RegisterScreen");
    }
    public void onExitButtonClick()
    {
        print("Exit button was clicked");
        Application.Quit();
    }
    public void onBackButtonClick(string screen)
    {
        UIManager.instance.ChangeScreen(screen);
        print("Back button was clicked");
    }
    public void onLoginButtonClick()
    {
        print("Login");
        ClientSend.Login();
    }
    public void onRegisterButtonClick()
    {
        print("Register");
        
        ClientSend.Signup();
    }
    public void onRefreshButtonClick()
    {
        // Refresh of Best Players
        UIManager.instance.ChangeScreen("MainMenuScreen");  // Call the update function...
        print("Refresh");
    }
    public void onCreateRoomPageButtonClick()
    {
        print("Create Room Page");
        UIManager.instance.ChangeScreen("CreateRoomScreen");
    }
    public void onCreateRoom()
    {
        print("Create Room");
        ClientSend.CreateRoom();
    }
    public void onJoinRoomPageButtonClick()
    {
        print("Join Room Page");
        UIManager.instance.currentRoom = null;
        UIManager.instance.ChangeScreen("JoinRoomScreen");
    }
    public void onJoinRoomClick()
    {
        if (UIManager.instance.currentRoom != null)
        {
            ClientSend.JoinRoom();
        }
    }
    public void onLeaveRoomClick()
    {
        ClientSend.LeaveRoom();
        UIManager.instance.ChangeScreen("MainMenuScreen");
    }
    public void onLogoutButtonClick()
    {
        ClientSend.Logout();
    }
    public void onRetryButtonClick()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
    public void onRoomNameClick()
    {
        UIManager.instance.currentRoom = EventSystem.current.currentSelectedGameObject;
        ClientSend.GetPlayersInRoom();
    }
    public void onCloseRoomClick()
    {
        ClientSend.CloseRoom();
    }
}
