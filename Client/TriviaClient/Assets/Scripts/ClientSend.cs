using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TMPro;
using UnityEngine;

public class ClientSend : MonoBehaviour
{
    // wrapper
    private static void SendTCPData(Packet _packet)
    {
        Client.instance.tcp.SendData(_packet);
    }

    #region Packets
    public static void Signup()
    {
        if (UIManager.instance.usernameRegister.text == "" || UIManager.instance.passwordRegister.text == "" || UIManager.instance.emailRegister.text == "")
        {
            UIManager.instance.ShowError("Please fill all the inputs above", "register");
            return;
        }
        using (Packet _packet = new Packet((int)PacketsCodes.signupCode))
        {
            print("Signing up");

            SignupRequest request = new SignupRequest();
            request.username = UIManager.instance.usernameRegister.text.ToLower();
            request.password = UIManager.instance.passwordRegister.text;
            request.mail = UIManager.instance.emailRegister.text;

            string json = JsonUtility.ToJson(request);

            _packet.Write(json.Length);
            _packet.Write(json);

            SendTCPData(_packet);
        }
    }
    public static void Login()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.loginCode))
        {
            print("Logging in");

            LoginRequest request = new LoginRequest();
            request.username = UIManager.instance.usernameLogin.text.ToLower();
            request.password = UIManager.instance.passwordLogin.text;

            string json = JsonUtility.ToJson(request);

            _packet.Write(json.Length);
            _packet.Write(json);

            SendTCPData(_packet);
        }
    }
    public static void CreateRoom()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.createRoomCode))
        {
            print("Creating Room");
            if (UIManager.instance.roomName.text == "" || 
                UIManager.instance.maxPlayers.text == "" || 
                UIManager.instance.questionCount.text == "" || 
                UIManager.instance.answerTimeout.text == "" ||
                !(1 <= int.Parse(UIManager.instance.maxPlayers.text) && int.Parse(UIManager.instance.maxPlayers.text) <= 999) ||
                !(1 <= int.Parse(UIManager.instance.questionCount.text) && int.Parse(UIManager.instance.questionCount.text) <= 10) ||
                !(1 <= int.Parse(UIManager.instance.answerTimeout.text) && int.Parse(UIManager.instance.answerTimeout.text) <= 99))
            {
                UIManager.instance.ShowError("Please check your inputs above", "createRoom");
                return;
            }
            CreateRoomRequest request = new CreateRoomRequest();
            request.roomName = UIManager.instance.roomName.text;
            request.maxUsers = uint.Parse(UIManager.instance.maxPlayers.text); 
            request.questionCount = uint.Parse(UIManager.instance.questionCount.text); 
            request.answerTimeout = uint.Parse(UIManager.instance.answerTimeout.text);
            string json = JsonUtility.ToJson(request);

            _packet.Write(json.Length);
            _packet.Write(json);

            SendTCPData(_packet);
        }
    }

    public static void CloseRoom()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.closeRoomCode))
        {
            print("Closing Room");
            _packet.Write(0);

            SendTCPData(_packet);
        }
    }
    public static void GetRoomState()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.getRoomStateCode))
        {
            print("GetRoomState");

            _packet.Write(0);

            SendTCPData(_packet);
        }
    }
    public static void LeaveRoom()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.leaveRoomCode))
        {
            print("LeaveRoom");

            _packet.Write(0);

            SendTCPData(_packet);
        }
    }
    public static void JoinRoom()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.joinRoomCode))
        {
            print("Joining Room");

            JoinRoomRequest request = new JoinRoomRequest();

            request.roomId = UIManager.instance.currentRoom.GetComponent<Room>().roomId;
            
            string json = JsonUtility.ToJson(request);

            _packet.Write(json.Length);
            _packet.Write(json);

            SendTCPData(_packet);
        }
    }
    public static void GetRooms()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.getRoomsCode))
        {
            print("Get Rooms");

            _packet.Write(0);

            SendTCPData(_packet);
        }
    }
    public static void GetPlayersInRoom()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.getPlayersInRoomCode))
        {
            print("Getting Players In Room");

            JoinRoomRequest request = new JoinRoomRequest();
            if (UIManager.instance.currentRoom == null)
                return;
            request.roomId = UIManager.instance.currentRoom.GetComponent<Room>().roomId;

            string json = JsonUtility.ToJson(request);

            _packet.Write(json.Length);
            _packet.Write(json);

            SendTCPData(_packet);
        }
    }

    public static void Logout()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.logoutCode))
        {
            print("Logging out");

            _packet.Write(0);
            SendTCPData(_packet);
        }
    }

    public static void GetStatistics()
    {
        using (Packet _packet = new Packet((int)PacketsCodes.getStatisticsCode))
        {
            print("Getting Statistics");

            _packet.Write(0);
            SendTCPData(_packet);
        }
    }
    #endregion

    // we send these to the sevrer
    #region Requests

    [Serializable]
    public class LoginRequest
    {
        public string username;
        public string password;
    }
        
    [Serializable]
    public class SignupRequest
    {
        public string username;
        public string password;
        public string mail;
    }

    [Serializable]
    public class GetPlayersInRoomRequest
    {
        public uint roomId;
    }
        
    [Serializable]
    public class JoinRoomRequest
    {
        public uint roomId;
    }
        
    [Serializable]
    public class CreateRoomRequest
    {
        public string roomName;
        public uint maxUsers;
        public uint questionCount;
        public uint answerTimeout;
    }

    #endregion
}
