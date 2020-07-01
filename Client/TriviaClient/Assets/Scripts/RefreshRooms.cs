using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;
using System;

public class RefreshRooms : MonoBehaviour
{
    private bool check = true;
    void Update()
    {
        if (check)
        {
            check = false;
            StartCoroutine(Wait());
        }
    }
    IEnumerator Wait()
    {
        ClientSend.GetRooms();
        UIManager.instance.SetPlayersInRoom(new string[0]);
        ClientSend.GetPlayersInRoom();
        yield return new WaitForSeconds(3f);
        check = true;
    }
}
