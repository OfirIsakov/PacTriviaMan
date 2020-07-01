using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.Video;
using TMPro;
using System.Runtime.ExceptionServices;

public class ClientHandle : MonoBehaviour
{
    public enum AnswersStatus
    {
        successStatus = 1,
        wrongDataStatus = 2,
        alreadyConnectedStatus = 3,
        roomIsFullStatus = 4,
        userExists = 5
    }
    public static void Signup(Packet _packet)
    {
        LoginAndSignupScreenManager(_packet, "LoginScreen", false);
    }
    public static void Login(Packet _packet)
    {
        LoginAndSignupScreenManager(_packet, "MainMenuScreen", true);
    }
    private static void LoginAndSignupScreenManager(Packet _packet, string nextScreen, bool login)
    {
        int ans = statusPackets(_packet);
        if (ans == (int)AnswersStatus.successStatus)
        {
            UIManager.instance.ChangeScreen(nextScreen);
        }
        else
        {
            try
            {
                UIManager.instance.ShowError(UIManager.errorCodes[ans], "login");
            }
            catch (Exception e)
            {
                UIManager.instance.ShowError("Unknown Error", "login");
                Debug.Log(e.ToString());
            }

        }
    }
    public static void Error(Packet _packet)
    {
        string json = _packet.ReadJson();

        Debug.Log($"Error Message from server: {json}");

        ErrorResponse response = JsonUtility.FromJson<ErrorResponse>(json);

        Debug.Log($"Message: {response.message}");
    }
    public static void CreateRoom(Packet _packet)
    {
        if (statusPackets(_packet) == (int)AnswersStatus.successStatus)
        {
            Debug.Log("Change screen to - MemberInRoomScreen");
            Debug.Log("Change screen to - WaitingRoomAdmin");
            UIManager.instance.ChangeScreen("WaitingRoomAdmin");
            ClientSend.GetRoomState();
        }
    }
    public static void CloseRoom(Packet _packet)
    {
        if (statusPackets(_packet) == (int)AnswersStatus.successStatus)
        {
            Debug.Log("Change screen to - MainMenuScreen");
            UIManager.instance.ChangeScreen("MainMenuScreen");
        }
    }
    public static void JoinRoom(Packet _packet)
    {
        if (statusPackets(_packet) == (int)AnswersStatus.successStatus)
        {
            UIManager.instance.errorJoinRoom.SetActive(false);
            Debug.Log("Change screen to - WaitingRoomMember");
            UIManager.instance.ChangeScreen("WaitingRoomMember");
            ClientSend.GetRoomState();
        }
        else
        {
            UIManager.instance.errorJoinRoom.SetActive(true);
        }
    }
    public static void Logout(Packet _packet)
    {
        if (statusPackets(_packet) == (int)AnswersStatus.successStatus)
        {
            UIManager.instance.ChangeScreen("LoginScreen");
        }

    }
    public static void Leave(Packet _packet)
    {
        if (statusPackets(_packet) == (int)AnswersStatus.successStatus)
        {
            UIManager.instance.ChangeScreen("leave");
        }

    }
    public static void StartRoom(Packet _packet)
    {
        if (statusPackets(_packet) == (int)AnswersStatus.successStatus)
        {
            UIManager.instance.ChangeScreen("LoginScreen");
        }

    }
    public static void GetRooms(Packet _packet)
    {
        string json = _packet.ReadJson();

        Debug.Log($"GetRooms Message from server: {json}");

        GetRoomsResponse response = JsonUtility.FromJson<GetRoomsResponse>(json);

        string[] rooms = response.Rooms.Split(',');
        DeleteClosedRooms(rooms); // delete the closed room
        // Adding only the new rooms (without touching the other rooms)
        GameObject copy;
        foreach (string room in rooms)
        {
            print("room: " + room);
            if (!RoomFoundInList(uint.Parse(room.Split(':')[1]))) // If it is a new room
            {
                copy = Instantiate(UIManager.instance.roomTemplate);
                copy.GetComponentInChildren<TextMeshProUGUI>().text = room.Split(':')[0];
                copy.GetComponent<Room>().roomId = uint.Parse(room.Split(':')[1]);
                copy.transform.parent = UIManager.instance.roomsList.transform;
            }
        }
    }
    private static void DeleteClosedRooms(string[] rooms)
    {
        try
        {
            int pos = 0;
            for (int i = 0; i < UIManager.instance.roomsList.transform.childCount; i++)
            {
                pos = Array.IndexOf(rooms, UIManager.instance.roomsList.transform.GetChild(i).gameObject.GetComponent<Room>().GetComponentInChildren<TextMeshProUGUI>().text);
                if (pos < 0) // not found
                {
                    Destroy(UIManager.instance.roomsList.transform.GetChild(i));
                }
            }
        }
        catch (Exception)
        {
            // we not do anything
        }
    }
    private static bool RoomFoundInList(uint id)
    {
        try
        {
            for (int i = 0; i < UIManager.instance.roomsList.transform.childCount; i++)
            {
                if (UIManager.instance.roomsList.transform.GetChild(i).gameObject.GetComponent<Room>().roomId == id)
                    return true;
            }
        }
        catch (Exception)
        {
            // we not do anything
        }
        return false;
    }
    public static int statusPackets(Packet _packet)
    {
        string json = _packet.ReadJson();

        Debug.Log($"Message from server: {json}");

        StatusResponse response = JsonUtility.FromJson<StatusResponse>(json);

        Debug.Log($"Status: {response.status}");
        return (int)response.status;
    }
    public static void GetPlayersInRoom(Packet _packet)
    {
        string json = _packet.ReadJson();

        Debug.Log($"GetPlayersInRoom Message from server: {json}");

        GetPlayersInRoomResponse response = JsonUtility.FromJson<GetPlayersInRoomResponse>(json);

        Debug.Log($"Players: {response.PlayersInRoom}");
        string[] players = response.PlayersInRoom.Split(',');
        UIManager.instance.SetPlayersInRoom(players);
    }
    public static void GetStatistics(Packet _packet)
    {
        string json = _packet.ReadJson();

        Debug.Log($"GetStatistics Message from server: {json}");

        GetStatisticsResponse response = JsonUtility.FromJson<GetStatisticsResponse>(json);

        UIManager.instance.UpdateStatsMainMenu(response.HighScores, response.UserStatistics);
        Debug.Log($"HighScores: {response.HighScores}");
        Debug.Log($"UserStatistics: {response.UserStatistics}");
    }
    public static void GetRoomState(Packet _packet)
    {
        string json = _packet.ReadJson();

        Debug.Log($"GetStatistics Message from server: {json}");

        RoomStateResponse response = JsonUtility.FromJson<RoomStateResponse>(json);

        UIManager.instance.UpdateStatsWaitingRoomMember(response.hasGameBegun, response.players, response.questionCount, response.answerTimeout);
        UIManager.instance.UpdateStatsWaitingRoomAdmin(response.hasGameBegun, response.players, response.questionCount, response.answerTimeout);
        Debug.Log($"status: {response.status}");
        Debug.Log($"hasGameBegun: {response.hasGameBegun}");
        Debug.Log($"players: {response.players}");
        Debug.Log($"questionCount: {response.questionCount}");
        Debug.Log($"answerTimeout: {response.answerTimeout}");
    }

    // we recieve these from the server
    #region Responses 

    [Serializable]
    public class StatusResponse
    {
        public uint status;
    }

    [Serializable]
    public class ErrorResponse
    {
        public string message;
    }

    [Serializable]
    public class GetRoomsResponse
    {
        public string Rooms;
    }

    [Serializable]
    public class GetPlayersInRoomResponse
    {
        public string PlayersInRoom;
    }

    [Serializable]
    public class GetStatisticsResponse
    {
        public string UserStatistics;
        public string HighScores;
    }

    [Serializable]
    public class JoinRoomResponse
    {
        public uint status;
    }

    [Serializable]
    public class CreateRoomResponse
    {
        public uint status;
    }
    [Serializable]
    public class RoomStateResponse
    {
        public uint status;
        public bool hasGameBegun;
        public string players;
        public uint questionCount;
        public uint answerTimeout;
    }
    #endregion
}
