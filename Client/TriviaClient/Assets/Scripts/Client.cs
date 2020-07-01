using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
using System.Net;
using System.Net.Sockets;
using System;

public class Client : MonoBehaviour
{
    public static Client instance;
    public static int dataBufferSize = 4096;

    public string ip = "127.0.0.1";
    public int port = 8820;
    public TCP tcp;

    private delegate void PacketHandler(Packet _packet);
    private static Dictionary<int, PacketHandler> packetHandlers;

    public GameObject clientManager;

    private void Start()
    {
        print("loading");
        UIManager.instance.ChangeScreen("LoadingScreen");
        UIManager.instance.ShowConnecting();
        tcp = new TCP();
        ConnectToServer();
    }
    private void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else if (instance != this)
        {
            Destroy(instance);
            instance = this;
            Debug.Log("Instance already exists, destroying old!");
        }
    }

    public void ConnectToServer()
    {
        InitializeClientData();
        UIManager.instance.InitializeErrorCodes();

        tcp.Connect();
    }

    public class TCP
    {
        public TcpClient socket;

        private NetworkStream stream;
        private Packet receivedData;
        private byte[] receiveBuffer;

        public void Connect()
        {
            socket = new TcpClient
            {
                ReceiveBufferSize = dataBufferSize,
                SendBufferSize = dataBufferSize
            };

            receiveBuffer = new byte[dataBufferSize];
            socket.BeginConnect(instance.ip, instance.port, ConnectCallback, socket);
        }

        private void ConnectCallback(IAsyncResult _result)
        {
            print(_result);

            if (!socket.Connected)
            {
                ThreadManager.ExecuteOnMainThread(() =>
                {
                    UIManager.instance.ShowErrorLoadingScreen("Could not find a server, is it running?");
                });
                return;
            }
            ThreadManager.ExecuteOnMainThread(() =>
            {
                UIManager.instance.ChangeScreen("LoginScreen");
            });

            stream = socket.GetStream();

            receivedData = new Packet();

            stream.BeginRead(receiveBuffer, 0, dataBufferSize, ReceiveCallback, null);
        }

        public void SendData(Packet _packet)
        {
            try
            {
                if (socket != null)
                {
                    stream.BeginWrite(_packet.ToArray(), 0, _packet.Length(), null, null);
                }
            }
            catch (Exception _ex)
            {
                Debug.Log($"Error sending data to server via TCP: {_ex}");
            }
        }

        private void ReceiveCallback(IAsyncResult _result)
        {
            try
            {
                int _byteLength = stream.EndRead(_result);
                if (_byteLength <= 0)
                {
                    // TODO: disconnect
                    return;
                }

                byte[] _data = new byte[_byteLength];
                Array.Copy(receiveBuffer, _data, _byteLength);

                HandleData(_data);
                stream.BeginRead(receiveBuffer, 0, dataBufferSize, ReceiveCallback, null);
            }
            catch
            {
                // TODO: disconnect
            }
        }

        private void HandleData(byte[] _data)
        {
            receivedData.SetBytes(_data);

            print(receivedData.ReadCode());

            ThreadManager.ExecuteOnMainThread(() =>
            {
                using (Packet _packet = new Packet(_data))
                {
                    int _packetCode = _packet.ReadCode();
                    packetHandlers[_packetCode](_packet);
                }
            });
        }
    }

    private void InitializeClientData()
    {
        packetHandlers = new Dictionary<int, PacketHandler>()
        {
            { (int)PacketsCodes.signupCode, ClientHandle.Signup },
            { (int)PacketsCodes.loginCode, ClientHandle.Login },
            { (int)PacketsCodes.errorCode, ClientHandle.Error },
            { (int)PacketsCodes.createRoomCode, ClientHandle.CreateRoom },
            { (int)PacketsCodes.getRoomsCode, ClientHandle.GetRooms },
            { (int)PacketsCodes.getPlayersInRoomCode, ClientHandle.GetPlayersInRoom },
            { (int)PacketsCodes.joinRoomCode, ClientHandle.JoinRoom },
            { (int)PacketsCodes.getStatisticsCode, ClientHandle.GetStatistics },
            { (int)PacketsCodes.logoutCode, ClientHandle.Logout },
            { (int)PacketsCodes.closeRoomCode, ClientHandle.CloseRoom },
            { (int)PacketsCodes.getRoomStateCode, ClientHandle.GetRoomState },
            { (int)PacketsCodes.leaveRoomCode, ClientHandle.Leave },
            { (int)PacketsCodes.startGameCode, ClientHandle.StartRoom }
        };
        Debug.Log("Initialized packets.");
    }
}
