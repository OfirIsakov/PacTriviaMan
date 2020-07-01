using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using System;

public class UIManager : MonoBehaviour
{
    public static UIManager instance;

    public static Dictionary<int, string> errorCodes;

    public GameObject exitButton;
    public GameObject retryButton;
    public GameObject errorLoading;
    public GameObject connectingText;
    public GameObject loadingGif;

    public GameObject errorLogin;
    public GameObject errorSignup;

    public GameObject[] screens;

    public TMP_InputField usernameLogin;
    public TMP_InputField passwordLogin;

    public TMP_InputField usernameRegister;
    public TMP_InputField passwordRegister;
    public TMP_InputField emailRegister;

    public GameObject loggedUser;
    // My Stats
    public GameObject gamesPlayed;
    public GameObject totalAnswers;
    public GameObject correctAnswers;
    public GameObject avgTime;
    // High Scores
    public GameObject[] highScoresMenu;
    // Create Room
    public TMP_InputField roomName;
    public TMP_InputField maxPlayers;
    public TMP_InputField questionCount;
    public TMP_InputField answerTimeout;
    public GameObject errorCreateRoom;
    // Join Room
    public GameObject roomsList;
    public GameObject playersList;
    public GameObject roomTemplate;
    public GameObject playerTemplate;
    public GameObject errorJoinRoom;
    public GameObject currentRoom;
    // waiting room member 
    public GameObject errorWaitingMemberRoom;
    public GameObject currPlayersWaitingMember;
    public GameObject questionCountWaitingMember;
    public GameObject answerTimeoutWaitingMember;
    public GameObject playersListWaitingMember;
    // waiting room member 
    public GameObject errorWaitingAdminRoom;
    public GameObject currPlayersWaitingAdmin;
    public GameObject questionCountWaitingAdmin;
    public GameObject answerTimeoutWaitingAdmin;
    public GameObject playersListWaitingAdmin;

    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else if (instance != this)
        {
            Debug.Log("Instance already exists, destroying object!");
            Destroy(this);
        }
    }

    public void ShowConnecting()
    {
        connectingText.SetActive(true);
        loadingGif.SetActive(true);
        errorLoading.SetActive(false);
        exitButton.SetActive(false);
        retryButton.SetActive(false);
    }
    public void ShowErrorLoadingScreen(string error)
    {
        errorLoading.SetActive(true);
        exitButton.SetActive(true);
        retryButton.SetActive(true);
        connectingText.SetActive(false);
        loadingGif.SetActive(false);
        errorLoading.GetComponent<TextMeshProUGUI>().text = error;
    }
    public void ShowError(string error, string type)
    {
        switch (type)
        {
            case "login":
                errorLogin.SetActive(true);
                errorLogin.GetComponent<TextMeshProUGUI>().text = error;
                break;
            case "register":
                errorSignup.SetActive(true);
                errorSignup.GetComponent<TextMeshProUGUI>().text = error;
                break;
            case "createRoom":
                errorCreateRoom.SetActive(true);
                errorCreateRoom.GetComponent<TextMeshProUGUI>().text = error;
                break;
            default:
                break;
        }
    }
    public void ChangeScreen(string screen)
    {
        foreach (var screenView in screens)
        {
            screenView.SetActive(screenView.name.Equals(screen));
        }
        resetNextScreen(screen);
        if (screen.Equals("MainMenuScreen"))
        {
            ClientSend.GetStatistics();
        }
    }
    public void UpdateStatsMainMenu(string highScores, string userStatistics)
    {
        string[] highScoresArr = highScores.Split(',');
        string[] userStatsArr = userStatistics.Split(':');
        for (int i = 0; i < 5; i++)
        {
            highScoresMenu[i].GetComponent<TextMeshProUGUI>().text = $"#{i + 1} ";
            if (highScoresArr[i].Split(':')[0] != "")
            {
                highScoresMenu[i].GetComponent<TextMeshProUGUI>().text += highScoresArr[i];
            }
        }
        loggedUser.GetComponent<TextMeshProUGUI>().text = userStatsArr[0];
        gamesPlayed.GetComponent<TextMeshProUGUI>().text = $"games played:{userStatsArr[1]}";
        totalAnswers.GetComponent<TextMeshProUGUI>().text = $"total answers:{userStatsArr[2]}";
        correctAnswers.GetComponent<TextMeshProUGUI>().text = $"correct answers:{userStatsArr[3]}";
        print(string.Format("{0:0.00}", float.Parse(userStatsArr[4])));
        avgTime.GetComponent<TextMeshProUGUI>().text = $"average time:{string.Format("{0:0.00}", float.Parse(userStatsArr[4]))}";
    }
    public void UpdateStatsWaitingRoomMember(bool hasGameBegun, string players, uint questionCount, uint answerTimeout)
    {
        string[] playersList = players.Split(',');
        SetPlayersInRoomWaitingMember(playersList);
        currPlayersWaitingMember.GetComponent<TextMeshProUGUI>().text = $"{players.Length}/???";
        questionCountWaitingMember.GetComponent<TextMeshProUGUI>().text = $"{questionCount}";
        answerTimeoutWaitingMember.GetComponent<TextMeshProUGUI>().text = $"{answerTimeout}";
    }
    public void UpdateStatsWaitingRoomAdmin(bool hasGameBegun, string players, uint questionCount, uint answerTimeout)
    {
        string[] playersList = players.Split(',');
        SetPlayersInRoomWaitingAdmin(playersList);
        currPlayersWaitingAdmin.GetComponent<TextMeshProUGUI>().text = $"{players.Length}/???";
        questionCountWaitingAdmin.GetComponent<TextMeshProUGUI>().text = $"{questionCount}";
        answerTimeoutWaitingAdmin.GetComponent<TextMeshProUGUI>().text = $"{answerTimeout}";
    }

    public void resetNextScreen(string destScreen)
    {
        switch (destScreen)
        {
            case "LoginScreen":
                errorLogin.SetActive(false);
                usernameLogin.text = "";
                passwordLogin.text = "";
                break;
            case "RegisterScreen":
                errorSignup.SetActive(false);
                usernameRegister.text = "";
                passwordRegister.text = "";
                emailRegister.text = "";
                break;
            case "CreateRoomScreen":
                errorCreateRoom.SetActive(false);
                roomName.text = "";
                maxPlayers.text = "";
                questionCount.text = "";
                answerTimeout.text = "";
                break;
            case "JoinRoomScreen":
                errorJoinRoom.SetActive(false);
                break;
            case "WaitingRoomMember":
                errorWaitingMemberRoom.SetActive(false);
                break;
            case "WaitingRoomAdmin":
                errorWaitingAdminRoom.SetActive(false);
                break;
            default:
                break;
        }


    }
    public void SetPlayersInRoom(string[] players)
    {
        GameObject copy;
        DeletePaticipantLeftRoom(players);
        foreach (string player in players)
        {
            if (Array.IndexOf(players, player) >= 0) // not found
            {
                copy = Instantiate(playerTemplate);
                copy.GetComponent<TextMeshProUGUI>().text = player;
                copy.transform.parent = playersList.transform;
            }
        }
    }
    public void DeletePaticipantLeftRoom(string[] players)
    {
        for (int i = 0; i < playersList.transform.childCount; i++)
        {
            GameObject player = playersList.transform.GetChild(i).gameObject;
            if (Array.IndexOf(players, player.GetComponentInChildren<TextMeshProUGUI>().text) < 0) // not found
            {
                Destroy(player);
            }
        }
    }
    public void SetPlayersInRoomWaitingMember(string[] players)
    {
        GameObject copy;
        DeletePaticipantLeftRoomWaitingMember(players);
        foreach (string player in players)
        {
            if (Array.IndexOf(players, player) >= 0) // not found
            {
                copy = Instantiate(playerTemplate);
                copy.GetComponent<TextMeshProUGUI>().text = player;
                copy.transform.parent = playersListWaitingMember.transform;
            }
        }
    }
    public void DeletePaticipantLeftRoomWaitingMember(string[] players)
    {
        for (int i = 0; i < playersListWaitingMember.transform.childCount; i++)
        {
            GameObject player = playersListWaitingMember.transform.GetChild(i).gameObject;
            if (Array.IndexOf(players, player.GetComponentInChildren<TextMeshProUGUI>().text) < 0) // not found
            {
                Destroy(player);
            }
        }
    }
    public void SetPlayersInRoomWaitingAdmin(string[] players)
    {
        GameObject copy;
        DeletePaticipantLeftRoomWaitingAdmin(players);
        foreach (string player in players)
        {
            if (Array.IndexOf(players, player) >= 0) // not found
            {
                copy = Instantiate(playerTemplate);
                copy.GetComponent<TextMeshProUGUI>().text = player;
                copy.transform.parent = playersListWaitingAdmin.transform;
            }
        }
    }
    public void DeletePaticipantLeftRoomWaitingAdmin(string[] players)
    {
        for (int i = 0; i < playersListWaitingAdmin.transform.childCount; i++)
        {
            GameObject player = playersListWaitingAdmin.transform.GetChild(i).gameObject;
            if (Array.IndexOf(players, player.GetComponentInChildren<TextMeshProUGUI>().text) < 0) // not found
            {
                Destroy(player);
            }
        }
    }

    public void InitializeErrorCodes()
    {
        errorCodes = new Dictionary<int, string>()
        {
            { (int)ClientHandle.AnswersStatus.wrongDataStatus, "Wrong Details" },
            { (int)ClientHandle.AnswersStatus.alreadyConnectedStatus, "This User Is Already Connected" },
            { (int)ClientHandle.AnswersStatus.roomIsFullStatus, "The Room Is Full" },
            { (int)ClientHandle.AnswersStatus.userExists, "User Is Already Exists" }
        };
        Debug.Log("Initialized Error Codes.");
    }
}

